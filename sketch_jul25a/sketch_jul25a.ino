#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ESP8266 WiFi module
SoftwareSerial esp8266(2, 3); // RX, TX

// Sensors
#define PH_SENSOR A0
#define TDS_SENSOR A1
#define FLOW_METER_PIN 4
#define FLOW_METER_POUT 8
#define ULTRASONIC_TRIG 5
#define ULTRASONIC_ECHO 6
#define TEMP_SENSOR_PIN 7

// Constants
#define VREF 5.0
#define SCOUNT 30

// Variables
float ph_value, tds_value, flow_rate, distance, water_temp;
int analogBuffer[SCOUNT];
int analogBufferIndex = 0;

// OneWire instance for temperature sensor
OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature tempSensor(&oneWire);

// ThingSpeak settings
const char* ssid = "Samsung m32";
const char* password = "Adithya@135";
const char* apiKey = "UBTERIK22HONRV5J";
const char* server = "api.thingspeak.com";

void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  
  pinMode(FLOW_METER_PIN, INPUT);
  pinMode(FLOW_METER_POUT, OUTPUT);
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
  
  tempSensor.begin();
  
  initWiFi();
}

void loop() {
  readSensors();
  updateThingSpeak();
  delay(15000); // Wait for 15 seconds before next update
}

void readSensors() {
  // Read pH sensor
  ph_value = analogRead(PH_SENSOR) * 5.0 / 1024;
  ph_value = 3.5 * ph_value;

  // Read TDS sensor
  for (int i = 0; i < SCOUNT; i++) {
    analogBuffer[analogBufferIndex] = analogRead(TDS_SENSOR);
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT) analogBufferIndex = 0;
    delay(40);
  }
  int averageVoltage = getMedianNum(analogBuffer, SCOUNT) * (float)VREF / 1024.0;
  float compensationCoefficient = 1.0 + 0.02 * (water_temp - 25.0);
  float compensationVoltage = averageVoltage / compensationCoefficient;
  tds_value = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;

  // Read flow meter
  flow_rate = pulseIn(FLOW_METER_PIN, HIGH);
  flow_rate = flow_rate / 7.5;
  flow_rate = pulseIn(FLOW_METER_POUT, LOW);
  flow_rate = flow_rate / 7.5;
  // Read ultrasonic sensor
  digitalWrite(ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);
  long duration = pulseIn(ULTRASONIC_ECHO, HIGH);
  distance = duration * 0.034 / 2;

  // Read water temperature sensor
  tempSensor.requestTemperatures();
  water_temp = tempSensor.getTempCByIndex(0);
}

void updateThingSpeak() {
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += server;
  cmd += "\",80";
  esp8266.println(cmd);
  
  if (esp8266.find("Error")) {
    Serial.println("AT+CIPSTART error");
    return;
  }
  
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr += "&field1=";
  getStr += String(ph_value);
  getStr += "&field2=";
  getStr += String(tds_value);
  getStr += "&field3=";
  getStr += String(flow_rate);
  getStr += "&field4=";
  getStr += String(distance);
  getStr += "&field5=";
  getStr += String(water_temp);
  
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  esp8266.println(cmd);
  
  if (esp8266.find(">")) {
    esp8266.print(getStr);
  }
  else {
    esp8266.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }
}

void initWiFi() {
  esp8266.println("AT+RST");
  delay(1000);
  esp8266.println("AT+CWMODE=1");
  delay(1000);
  esp8266.println("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"");
  delay(5000);
}

int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}
