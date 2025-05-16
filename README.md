# IoT-Based-Water-Quality-Monitoring-ESP
This Arduino-ESP8266 system tracks pH, TDS, flow rate, water level, and temperature using multiple sensors. Data is sent to ThingSpeak for real-time monitoring 📊. Helps in water purification, agriculture &amp; industrial safety by preventing contamination 🚰💧. 

🌊 IoT-Based Water Quality Monitoring System 📡🚰
This Arduino-powered system ensures real-time water quality analysis using pH, TDS, flow rate, ultrasonic water level, and temperature sensors. It transmits data to ThingSpeak for continuous monitoring, making it ideal for agriculture, industrial water processing, and environmental safety 🌍💧.

🛠️ Components Overview
🔬 pH Sensor (A0) – Water Acidity Measurement
- Monitors pH levels to assess water purity 🏭.
- Ensures safe drinking water & optimal agriculture irrigation 🚜.
💧 TDS Sensor (A1) – Total Dissolved Solids Detection
- Measures mineral concentration in water ⚗️.
- Helps detect contaminants & pollution 🌍.
📡 Flow Meter (Pin 4 & Pin 8) – Water Usage Tracking
- Calculates real-time flow rate in liters per second ⏳.
- Prevents water wastage by tracking consumption efficiently 💧.
📏 Ultrasonic Sensor (Trig: Pin 5, Echo: Pin 6) – Water Level Measurement
- Determines tank water level via echo pulses 📡.
- Helps in automated water filling 🚰.
🌡️ Temperature Sensor (Pin 7) – Water Heat Monitoring
- Uses Dallas DS18B20 for precise temperature readings ⚡.
- Ensures boiling point detection & optimal irrigation conditions 🌾.
🎛️ ESP8266 Wi-Fi Module – Wireless Connectivity
- Sends sensor data to ThingSpeak cloud for real-time analysis 📊.
- Enables remote monitoring of water health 🚀.

📌 Pin Configuration Diagram
| Component | Arduino Pin | Type | 
| pH Sensor | A0 | Analog (Input) | 
| TDS Sensor | A1 | Analog (Input) | 
| Flow Meter Sensor | 4 & 8 | Digital (Input & Output) | 
| Ultrasonic Sensor - Trig | 5 | Digital (Output) | 
| Ultrasonic Sensor - Echo | 6 | Digital (Input) | 
| Temperature Sensor (DS18B20) | 7 | Digital (OneWire Input) | 
| ESP8266 Wi-Fi TX | Pin 3 | Software Serial (TX) | 
| ESP8266 Wi-Fi RX | Pin 2 | Software Serial (RX) | 



📚 Libraries Used
- SoftwareSerial.h – Enables serial communication with ESP8266.
- OneWire.h – Supports Dallas DS18B20 temperature sensor.
- DallasTemperature.h – Extracts temperature values.

🔄 Step-by-Step Approach
🏗️ Step 1: Hardware Setup
🔌 Connect Sensors – Attach pH, TDS, flow meter, ultrasonic, & temp sensors properly 🔧.
📡 Set Up ESP8266 Wi-Fi – Define SSID & Password for network connection 🌐.
🖥️ Step 2: Software Configuration
📜 Define Constants – Assign sensor input ranges & calibration values ⚙️.
🛠️ Initialize Sensors – Activate OneWire temp sensor & ultrasonic readings.
📊 Configure ThingSpeak API – Store real-time sensor readings online 📡.
📡 Step 3: Data Collection & Processing
💧 Read pH & TDS Values – Convert analog readings into precise measurements 📊.
📏 Measure Water Level – Detect distance using ultrasonic sensor.
🌡️ Extract Water Temperature – Use DS18B20 OneWire protocol.
🚀 Step 4: IoT Communication
📢 Send Data to ThingSpeak – Upload readings every 15 seconds for remote tracking 📊.
⚡ Check Wi-Fi Status – Ensure ESP8266 is properly connected 🌐.
🔄 Step 5: Optimization & Enhancements
🔍 Calibrate Sensor Accuracy – Adjust thresholds for precise monitoring 🔬.
📲 Integrate Notifications – Use alerts for unsafe water conditions 🚨.
🧠 AI-Based Water Quality Prediction – Implement machine learning for contamination forecasting 🤖.

🚀 Final Thoughts
This IoT-based Water Quality Monitoring System ensures safe, clean, and optimized water usage 🚰. By leveraging ESP8266 Wi-Fi & cloud analytics, it provides smart environmental protection, minimizing pollution risks 🌍.
