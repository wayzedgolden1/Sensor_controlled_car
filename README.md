## Kết nối dây trên xe mô hình

Dựa trên thông tin trước đó, bạn đang sử dụng **ESP32 thường (ESP-WROOM-32) + L298** để điều khiển xe, đồng thời lắp thêm **OV7670** để nhận diện màu đỏ và kích hoạt động cơ bắn. Dưới đây là sơ đồ kết nối cơ bản:

### 1. Kết nối ESP32 với Driver L298 (Điều khiển động cơ xe)

| ESP32 | L298 |
|--------|------|
| 3.3V | 5V (qua Buck Converter 5V) |
| GND | GND |
| D5 | IN1 |
| D18 | IN2 |
| D19 | IN3 |
| D21 | IN4 |
| D23 | ENA (PWM) |
| D22 | ENB (PWM) |

- **Motor 1 (trái):** Cắm vào OUT1, OUT2 của L298.
- **Motor 2 (phải):** Cắm vào OUT3, OUT4 của L298.
- **Nguồn động cơ:** Cắm 7V - 12V vào VCC của L298.

### 2. Kết nối Cảm biến Gia tốc ADXL345 (Gắn trên tay để điều khiển xe)

Cảm biến **ADXL345** sử dụng giao tiếp **I2C**, kết nối như sau:

| ESP32 | ADXL345 (I2C) |
|--------|--------------|
| 3.3V | VCC |
| GND | GND |
| D22 | SCL |
| D21 | SDA |

Nếu bạn dùng **SPI** thay vì **I2C**, kết nối như sau:

| ESP32 | ADXL345 (SPI) |
|--------|--------------|
| 3.3V | VCC |
| GND | GND |
| D18 | CS |
| D19 | SDO |
| D23 | SDA |
| D5 | SCL |

Sau khi kết nối dây, bạn có thể sử dụng thư viện **Adafruit_ADXL345** hoặc **SparkFun_ADXL345** để đọc dữ liệu gia tốc, rồi gửi tín hiệu về **ESP32 trên xe** qua **WiFi** hoặc **Bluetooth**.
