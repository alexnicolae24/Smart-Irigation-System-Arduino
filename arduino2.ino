#include <Wire.h>
#include <LiquidCrystal.h>
#define I2C_SLAVE_ADDRESS 0x09
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int x = 0;

//Funcție ce primește valoarea de la Master
void receiveEvent(int numBytes) {
  x = Wire.read();
}

void setup(){
  Serial.begin(9600);
  Wire.begin(I2C_SLAVE_ADDRESS);
  
  //Afisarea pe LCD a numelui aplicației
  lcd.begin(16, 2);
  lcd.print("Sistem de");
  lcd.setCursor(0,1);
  lcd.print("irigatii smart");
  delay(500);
  lcd.clear();
  //lcd.setCursor(7,0);
  //lcd.print("ml/min");
  //lcd.setCursor(0,0);
  //Serial.println("Scrie debitul:");     
  //Serial.println(Serial.read());
  //lcd.print(Serial.read());
  Wire.onReceive(receiveEvent);
}

void loop(){
  //Afișarea stării pompei pe LCD
  lcd.setCursor(0,1);
  if (x == HIGH)
     lcd.print("Pompa: ON");
  else
     lcd.print("Pompa:OFF");
  delay(50);
}