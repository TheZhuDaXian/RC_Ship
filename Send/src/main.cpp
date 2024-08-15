#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN PA3
#define CSN_PIN PA4
#define SCK_PIN PA5
#define MOSI_PIN PA7
#define MISO_PIN PA6
#define X_pin PB0
#define Y_pin PB1

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";  // 通信地址

struct Data {
  int X_Value;
  int Y_Value;
};

void setup() {

  pinMode (X_pin, INPUT);
  pinMode (Y_pin, INPUT);

  Serial.begin(9600);
  Serial.println("NRF24L01 SPI 通信测试");

  // 检查引脚定义
  Serial.print("CE_PIN: ");
  Serial.println(CE_PIN);
  Serial.print("CSN_PIN: ");
  Serial.println(CSN_PIN);
  Serial.print("SCK_PIN: ");
  Serial.println(SCK_PIN);
  Serial.print("MOSI_PIN: ");
  Serial.println(MOSI_PIN);
  Serial.print("MISO_PIN: ");
  Serial.println(MISO_PIN);

  if (!radio.begin()) {
    Serial.println("NRF24L01 初始化失败，请检查连接!");
    while (1);
  } else {
    Serial.println("NRF24L01 初始化成功!");
  }

  // 设置 NRF24L01
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  // 打印 NRF24L01 的详细信息
  radio.printDetails();
}

void loop() {
  // 读取模拟引脚的值
  Data data;
  data.X_Value = analogRead(X_pin);
  data.Y_Value = analogRead(Y_pin);

  // 打印读取到的值
  Serial.print("X: ");
  Serial.print(data.X_Value);
  Serial.print(" Y: ");
  Serial.println(data.Y_Value);

  // 发送数据
  bool success = radio.write(&data, sizeof(data));

  if (success) {  
    Serial.println("数据发送成功");
  } else {
    Serial.println("数据发送失败");
  }

  delay(50);  // 每秒发送一次数据
}