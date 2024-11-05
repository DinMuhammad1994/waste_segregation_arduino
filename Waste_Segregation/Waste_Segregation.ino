// Code is written by : Engr Din Muhammad
// +92 333 7012372  | www.projexels.com

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <Servo.h>

Servo servodrop;  // create servo object to control a servo
Servo servosort;  // create servo object to control a servo


int pos = 0;    // variable to store the servo position


int IRsensor = 12;
int Indsensor = A0;
int wastestate = 0;
int wls = A1;
void setup() {
  Serial.begin(9600);
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Automatic  Waste");
  lcd.setCursor(0, 1);
  lcd.print("    Segregation   ");

  lcd.setCursor(0, 2);
  lcd.print("      System");
  servodrop.attach(2);  // attaches the servo on pin 9 to the servo object
  servosort.attach(3);  // attaches the servo on pin 9 to the servo object
  pinMode(IRsensor, INPUT);
  pinMode(Indsensor, INPUT);
  pinMode(wls, INPUT);
  drop(90);
  delay(1000);
  drop(20);
  delay(1000);
  drop(90);
  delay(1000);
 sort(80);

  lcd.clear();



}

void loop()
{




  int IRsensorstate = digitalRead(IRsensor);
  int Indsensorstate = digitalRead(Indsensor);
  int WetSensor = analogRead(wls);
  WetSensor = map(WetSensor, 0, 900, 0, 100);

  // print out the state of the button:
  Serial.print("IR        : ") ; Serial.println(IRsensorstate);
  Serial.print("INDUCTIVE : ") ; Serial.println(Indsensorstate);
  Serial.print("WET SENSor: "); Serial.println(WetSensor);
  delay(10);

  lcd.setCursor(0, 0);
  lcd.print("INFRARED   :");
  lcd.setCursor(0, 1);
  lcd.print("INDUCTIVE  :"); lcd.print("NO      ");
  lcd.setCursor(0, 2);
  lcd.print("WET SENSOR :"); lcd.print("NO      ");
  lcd.setCursor(0, 3);
  lcd.print("OTHER WASTE:"); lcd.print("NO      ");

  lcd.setCursor(12, 0);
  if (IRsensorstate ==  0)
  {
    lcd.print("IN...");
    wastestate = 1;

    delay(2000);


  }
  else
  {
    lcd.print("READY");
  }
  Serial.print("waste state = "); Serial.println(wastestate);


  if (wastestate == 1)
  {
    for (int i = 0; i < 30; i++) {

      Indsensorstate = digitalRead(Indsensor);
      WetSensor = analogRead(wls);
      WetSensor = map(WetSensor, 0, 900, 0, 100);
      Serial.print("INDUCTIVE : ") ; Serial.println(Indsensorstate);
      Serial.print("WET SENSor: "); Serial.println(WetSensor);
      delay(100);
    }


    if ( WetSensor > 30 && Indsensorstate == 0)
    {
      Serial.println("Wet waste");
      lcd.setCursor(12, 2);
      lcd.print("Detected");
      Serial.println("sorting right");
      sort(180);
      delay(1000);
      Serial.println("drop Open");
      drop(10);
      delay(1000);
      Serial.println("drop close");
      drop(90);
      delay(2000);
     sort(80);
      wastestate = 0;
      delay(2000);
    }
    else if  (Indsensorstate == 1)
    {
      Serial.println("inductive waste");
      lcd.setCursor(12, 1);
      lcd.print("Detected");
      Serial.println("sorting left");
      sort(0);
      delay(1000);
      Serial.println("drop Open");
      drop(10);
      delay(1000);
      Serial.println("drop close");
      drop(90);
      delay(1000);

     sort(80);
      wastestate = 0;
      delay(2000);
    }
    else
    {
      Serial.println("Other waste");
      lcd.setCursor(12, 3);
      lcd.print("Detected");

      Serial.println("drop Open");
      drop(10);
      delay(1000);
      drop(90);
      Serial.println("drop close");
      delay(500);
      wastestate = 0;
      delay(2000);
    }

  }

  delay(300);


}

void drop(int x) {
  servodrop.write(x);

}

void sort(int y) {
  servosort.write(y);

}
