#define MQ2pin A0
#define buzzerPin 5
#define LED1 11
#define LED2 12
#include <LiquidCrystal.h>

int thresholdValue = 300;

LiquidCrystal lcd(13, 10, 4, 6, 7, 8);

#include <Servo.h>
Servo servoWindow; // Define our Servo for Window
Servo servoDoor; // Define our Servo for Door
float sensorValue;  //variable to store sensor value


byte blFire[] = {
  B11111,
  B11111,
  B11111,
  B01111,
  B01111,
  B00111,
  B00011,
  B00001
};
byte brFire[] = {
  B11101,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100,
  B11000,
  B10000
};
byte trFire[] = {
  B10000,
  B00000,
  B10000,
  B10000,
  B11000,
  B11000,
  B11100,
  B11100
};
byte tlFire[] = {
  B00000,
  B00001,
  B00011,
  B00011,
  B00111,
  B00111,
  B10111,
  B11111
};

void setup() {
  Serial.begin(9600); // sets the serial port to 9600
  servoWindow.write(60);
  lcd.begin(16,2);
  //create new characters
  lcd.createChar(0, tlFire);
  lcd.createChar(1, trFire);
  lcd.createChar(2, blFire);
  lcd.createChar(3, brFire);
  lcd.setCursor(4,0);
  lcd.print("All safe");
  delay(5000);
  lcd.clear();
 
  pinMode(buzzerPin,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  servoWindow.attach(9);  
  Serial.println("MQ2 warming up!");
  delay(200); // allow the MQ2 to warm up
 
}

void loop() {
  int a= 400;
  int b = 0;
  sensorValue = analogRead(MQ2pin); // read analog input pin A0
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue); // prints sensor reading value
  if(sensorValue>a){      
      alarm();
      servoWindow.write(0);  
      digitalWrite(LED2,HIGH);
      lcdAnimation();
      lcdAnimationAddress();
      }
  else{
    servoWindow.write(60);
  } //  wait 2s for next reading
}

void alarm(){
digitalWrite(LED1,HIGH);
tone(buzzerPin, 1000);
delay(500);
digitalWrite(LED1,LOW);
digitalWrite(LED2,LOW);
tone(buzzerPin, 500);
delay(500);
}

void lcdAnimationAddress(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  24 Rail Park");
  lcd.setCursor(0,1);
  lcd.print("Joe blogs House");
  delay(5000);
  lcd.clear();
}


void lcdAnimation(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("   WARNING");
  lcd.setCursor(0, 0);
  lcd.write((byte)0);
  lcd.setCursor(1, 0);
  lcd.write((byte)1);
  lcd.setCursor(0, 1);
  lcd.write((byte)2);
  lcd.setCursor(1, 1);
  lcd.write((byte)3);
  lcd.print("    FIRE");
  lcd.setCursor(14, 0);
  lcd.write((byte)0);
  lcd.setCursor(15, 0);
  lcd.write((byte)1);
  lcd.setCursor(14, 1);
  lcd.write((byte)2);
  lcd.setCursor(15, 1);
  lcd.write((byte)3);
  delay(5000);
  lcd.clear();
}
