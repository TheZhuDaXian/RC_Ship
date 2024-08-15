#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN PA3
#define CSN_PIN PA4
#define SCK_PIN PA5
#define MOSI_PIN PA7
#define MISO_PIN PA6
#define X_pin PB3
#define Y_pin PB4

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";  // 通信地址

struct Data {
  int X_Value;
  int Y_Value;
};

void setup() {
  Serial.begin(9600);
  Serial.println("NRF24L01 SPI 通信测试");

  if (!radio.begin()) {
    Serial.println("NRF24L01 初始化失败，请检查连接!");
    while (1);
  } else {
    Serial.println("NRF24L01 初始化成功!");
  }

  // 设置 NRF24L01
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // 打印 NRF24L01 的详细信息
  radio.printDetails();
}

void loop() {
  if (radio.available()) {
    Data data;  // 定义接收数据的结构体
    radio.read(&data, sizeof(data));

    Serial.print("接收到的数据 - X: ");
    Serial.print(data.X_Value);
    Serial.print(" Y: ");
    Serial.println(data.Y_Value);
  }
}