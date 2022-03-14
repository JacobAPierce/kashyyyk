#include "LiquidCrystal.h" //header file for liquid crystal display (lcd)
#include "ph_grav.h" //header file for Atlas Scientific gravity pH sensor

//Arduino pin assignment (Arduino Pin:Module Pin)
int redPin=11;
int greenPin=10;
int bluePin=9;
Gravity_pH pH = A0; //A0:Po
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //(2:RS, 3:E, 4:D4, 5:D5, 6:D6, 7:D7)

void setup() {
  int x = 0;
  Serial.begin(9600); //enable serial port
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  while (x < 15) { //blink to notify of setup
    x++;
    phLed('C');
    delay(200);
    phLed('W');
    delay(200);
  }
  lcd.begin(16, 2); //start lcd interface and define lcd size (20 columns and 4 rows)
  lcd.setCursor(0,0); //place cursor on screen at column 6, row 2
  lcd.print("pH Value:    000"); //display "pH Reading" 
  delay(1000);
}

void loop() {
  printPh();
  delay(1000);
}

void printPh() {
  float phOff = 14.61;
  float phVal = pH.read_ph() + phOff;
  if (phVal < 5){
    phLed('R');
  } else if (phVal > 6) {
    phLed('B');
  } else {
    phLed('X');
  }
  lcd.setCursor(12,0);
  lcd.print(phVal);
}

void phLed (char color) {
  switch (color) {
    case 'B':
      analogWrite(redPin,0);
      analogWrite(greenPin,0);
      analogWrite(bluePin,255);
      break;
    case 'C':
      analogWrite(redPin,0);
      analogWrite(greenPin,255);
      analogWrite(bluePin,255);
      break;
    case 'G':
      analogWrite(redPin,0);
      analogWrite(greenPin,255);
      analogWrite(bluePin,0);
      break;
    case 'M':
      analogWrite(redPin,255);
      analogWrite(greenPin,0);
      analogWrite(bluePin,255);
      break;
    case 'O':
      analogWrite(redPin,255);
      analogWrite(greenPin,55);
      analogWrite(bluePin,0);
      break;
    case 'R':
      analogWrite(redPin,255);
      analogWrite(greenPin,0);
      analogWrite(bluePin,0);
      break;
    case 'W':
      analogWrite(redPin,255);
      analogWrite(greenPin,255);
      analogWrite(bluePin,255);
      break;
    case 'Y':
      analogWrite(redPin,255);
      analogWrite(greenPin,255);
      analogWrite(bluePin,0);
      break;
    default:
      analogWrite(redPin,LOW);
      analogWrite(greenPin,LOW);
      analogWrite(bluePin,LOW);
  }
}