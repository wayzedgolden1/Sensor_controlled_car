#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <WiFi.h>
#include <WebSocketsClient.h>


const char* ssid = "ESP32_Car";      
const char* password = "12345678";
const char* serverAddress = "192.168.4.1";
const int carPort = 81; 


Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);


WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);


  if (!accel.begin()) {
    Serial.println("Không tìm thấy ADXL345, kiểm tra kết nối!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);  


  WiFi.begin(ssid, password);
  Serial.print("Đang kết nối WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nKết nối WiFi thành công!");


  webSocket.begin(serverAddress, carPort, "/"); 
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket Client bắt đầu kết nối...");
}

String getGesture(float x, float y) {
  
  if (y > 5) return "BACKWARD";
  if (y < -5) return "FORWARD";
  if (x > 5) return "LEFT";
  if (x < -5) return "RIGHT";
  return "STOP";
}


void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  String command = getGesture(event.acceleration.x, event.acceleration.y);
  Serial.println("Command: " + command);
  

  webSocket.sendTXT(command);
  

  webSocket.loop();
  
  delay(200);
}


void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_CONNECTED) {
    Serial.println("WebSocket kết nối thành công!");
  }
}
