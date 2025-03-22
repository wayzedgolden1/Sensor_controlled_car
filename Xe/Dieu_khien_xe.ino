#include <WiFi.h>
#include <WebSocketsServer.h>

// **Khai báo chân L298N theo sơ đồ của bạn**
#define IN1 16  // Điều khiển động cơ trái lùi
#define IN2 17  // Điều khiển động cơ trái tiến
#define IN3 18  // Điều khiển động cơ phải tiến
#define IN4 19  // Điều khiển động cơ phải lùi

// **WiFi Access Point cho ESP32 trên xe**
const char* ssid = "ESP32_Car";
const char* password = "12345678";

// **Tạo WebSocket server**
WebSocketsServer webSocket(81);

void setup() {
  Serial.begin(115200);

  // **Thiết lập chân điều khiển động cơ**
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // **Tạo WiFi Access Point cho ESP32 trên xe**
  WiFi.softAP(ssid, password);
  Serial.print("ESP32 Car IP: ");
  Serial.println(WiFi.softAPIP());  // In địa chỉ IP của xe

  // **Bắt đầu WebSocket server**
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

// **Hàm nhận lệnh từ WebSocket**
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String command = (char*)payload;
    Serial.println("Lệnh nhận được: " + command);
    controlCar(command);
  }
}

// **Hàm điều khiển xe**
void controlCar(String command) {
  if (command == "FORWARD") {      // Tiến tới
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } 
  else if (command == "BACKWARD") { // Lùi
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } 
  else if (command == "LEFT") {     // Rẽ trái
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } 
  else if (command == "RIGHT") {    // Rẽ phải
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } 
  else {                            // Dừng lại
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

void loop() {
  webSocket.loop(); // Lắng nghe WebSocket để nhận lệnh
}
