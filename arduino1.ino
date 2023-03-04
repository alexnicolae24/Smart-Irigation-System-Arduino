
#include <Wire.h>

#define I2C_SLAVE_ADDRESS 0x09
 
//Inițializarea valorilor
const int TS = A0;
const int SMS = A1;
const int LS = A2;
const int motor = 11;
volatile int n = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(motor, OUTPUT);
  delay(200);
}

void loop() {
  //Calcularea si afișarea valorilor transmise de senzori
  int value1 = analogRead(TS);
  float Temp = value1 * 500.0 / 1023.0;
  int value2 = analogRead(SMS);
  float Moist = value2 * 500.0 /1023.0;
  float Light = analogRead(LS);
  Serial.println(Temp);
  Serial.println(Moist);
  Serial.println(Light);
  
  //Condițiile de funcționare ale pompei
  if ((Temp > 40) || (Moist < 300) || (Light < 250)){
    digitalWrite(motor, HIGH);
    n = HIGH;
    
    //Transmiterea către Slave
    Wire.beginTransmission(I2C_SLAVE_ADDRESS);
    Wire.write(n);
    Wire.endTransmission();
  }
  else {
    digitalWrite(motor, LOW); 
    n = LOW;
    
    //Transmiterea către Slave
    Wire.beginTransmission(I2C_SLAVE_ADDRESS);
    Wire.write(n);
    Wire.endTransmission();
  }
   delay(100);
}