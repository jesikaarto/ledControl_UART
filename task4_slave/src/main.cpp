#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial mySerial(1); // use UART2
String data;
int LED = 15;

void setup()
{
  Serial.begin(115200);
  mySerial.begin(15200, SERIAL_8N1, 16, 17);
  pinMode(LED, OUTPUT);
}

void loop()
{
  // berikut data yang dibaca dari serial monitor sendiri, kemudian dikirim ke perangkat lain
  while (Serial.available() > 0)
  {
    delay(10);
    char d = Serial.read();
    data += d;
  }

  if (data.length() > 0)
  {
    mySerial.print(data);
    data = "";
  }

  // berikut code untuk membaca data dari perangkat lain
  while (mySerial.available() > 0)
  {
    delay(10);
    char d = mySerial.read();
    data += d;

    if (data == "OFF" || data == "off")
    {
      digitalWrite(LED, LOW);
      Serial.println("Lampu mati!");
    }
    if (data == "ON" || data == "on")
    {
      digitalWrite(LED, HIGH);
      Serial.println("Lampu nyala!");
    }
  }
  if (data.length() > 0)
  {
    Serial.println(data);
    data = "";
  }
}