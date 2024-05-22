#include <SoftwareSerial.h>
#include <Wire.h>
#include <dht.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
dht DHT;

#define DHT11_PIN 5
SoftwareSerial bt(8, 9); // RX, TX
int sensor_pin = A0; // Soil Sensor input at Analog PIN A0
int output_value ;
int relay_pin = 7;

void setup(){
  bt.begin(9600);   
  lcd.init();
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setBacklight(HIGH);
  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  
  
}

void loop(){
  float h=DHT.humidity;
  float t=DHT.temperature;
  float m=analogRead(sensor_pin);
  m = map(m, 550,10,0,100);
  String temp = String(t);
  String hum = String(h);
  String moistt = String(m);
  char message1[30];
  (temp+","+moistt+","+hum+",").toCharArray(message1,30);
  char message2[30];
  (temp+","+moistt+","+hum+",").toCharArray(message2,30);
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  
  lcd.setCursor(0,1); 
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(2000);
  
  lcd.setCursor(23,0);
  lcd.autoscroll();
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,10,0,100);
  lcd.print("Mositure: ");
  lcd.print(output_value);
  lcd.print("%");
  
  lcd.setCursor(23,1);
  if(output_value<-30){
  digitalWrite(relay_pin, LOW);
  lcd.print("Motor ON");
 }
 else
 {
  digitalWrite(relay_pin, HIGH);
  lcd.print("Motor OFF");       
 }
  bt.write(message1);
  bt.write(message2);
  delay(2500);
  lcd.noAutoscroll();
  lcd.clear();
}
