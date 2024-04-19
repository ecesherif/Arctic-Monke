#include <Adafruit_LiquidCrystal.h>
#include <Wire.h>

const int sensorPin = A0;      
const int motor1Pin = 2;        
const int motor2Pin = 3;        
const int transistor1Pin = 4;   
const int transistor2Pin = 5;   
const int redPin = 11;          
const int greenPin = 9;         
const int bluePin = 10;         

const int coolingThreshold = 25; 
const int normalThreshold = 20;  

Adafruit_LiquidCrystal lcd_1(0);

void setup() 
{
  Serial.begin(9600);
  
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  
  pinMode(transistor1Pin, OUTPUT);
  pinMode(transistor2Pin, OUTPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  lcd_1.begin(16, 2);
}

void loop() 
{
  int sensorValue = analogRead(sensorPin);
  
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0; 
  
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  
  if (temperatureC >= coolingThreshold) 
  {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    
    analogWrite(motor1Pin, 255);
    analogWrite(motor2Pin, 255);   
  }
  else if (temperatureC >= normalThreshold) 
  {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    
    analogWrite(motor1Pin, 0);
    analogWrite(motor2Pin, 0);
  } 
  else 
  {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
    
    analogWrite(motor1Pin, 0);
    analogWrite(motor2Pin, 0);
  }

  lcd_1.setCursor(0, 0);
  lcd_1.print("Temp: ");
  lcd_1.print(temperatureC);
  lcd_1.print(" C  ");
  
  delay(1000);
}
