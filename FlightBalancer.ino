#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <NewTone.h>

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); //Change to (0x27,16,2) for 1602 LCD 


#define LIGHT_RED     2
#define LIGHT_YELLOW  3
#define LIGHT_GREEN   4
#define BUZZER        7
// Define pins and max distance:
#define trigPin  8
#define echoPin  9
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
float duration, distance;

void setup() 
{
    Serial.begin(9600);
    
    lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
    lcd.backlight();//To Power ON the back light

    pinMode(BUZZER, OUTPUT);

    pinMode(LIGHT_RED,OUTPUT);
    pinMode(LIGHT_YELLOW,OUTPUT);
    pinMode(LIGHT_GREEN,OUTPUT);

    digitalWrite(LIGHT_RED,LOW);
    digitalWrite(LIGHT_YELLOW,LOW);
    digitalWrite(LIGHT_GREEN,LOW);
}

void loop() 
{
    checkDistance();  //check distance 
        
    while(distance >= 8)
    {
        lcd.setCursor(0,0); //Defining positon to write from first row,first column .
        lcd.print("Still Far...    "); 
        delay(1000); 

        lcd.setCursor(0,1);  
        lcd.print("Dist = ");
        lcd.print(distance); // Prints the measured distance
        lcd.print(" cm ");

        //LED Green Light Up
        digitalWrite(LIGHT_GREEN,HIGH);
        digitalWrite(LIGHT_YELLOW,LOW);
        digitalWrite(LIGHT_RED,LOW);

        //Sound buzzer?
        //playBuzzerOnce();

        //check distance again
        checkDistance();       
    }

    while(distance >= 6 && distance < 8)
    {
        lcd.setCursor(0,0); //Defining positon to write from first row,first column .
        lcd.print("Getting Near... "); 
        delay(1000); 

        lcd.setCursor(0,1);  
        lcd.print("Dist = ");
        lcd.print(distance); // Prints the measured distance
        lcd.print(" cm ");

        //LED Green Light Up
        digitalWrite(LIGHT_GREEN,HIGH);
        digitalWrite(LIGHT_YELLOW,LOW);
        digitalWrite(LIGHT_RED,LOW);

        //Sound buzzer?
        //playBuzzerOnce();

        //check distance again
        checkDistance();       
    }

    while(distance >= 4 && distance < 6)
    {
        lcd.setCursor(0,0); //Defining positon to write from first row,first column .
        lcd.print("Nearer...       "); 
        delay(1000); 

        lcd.setCursor(0,1);  
        lcd.print("Dist = ");
        lcd.print(distance); // Prints the measured distance
        lcd.print(" cm ");

        //LED Yellow Light Up
        digitalWrite(LIGHT_GREEN,LOW);
        digitalWrite(LIGHT_YELLOW,HIGH);
        digitalWrite(LIGHT_RED,LOW);

        //Sound buzzer?
        playBuzzerOneSecond();

        //check distance again
        checkDistance();       
    }

    /*while(distance >= 20 && distance < 30)
    {
        lcd.setCursor(0,0); //Defining positon to write from first row,first column .
        lcd.print("Almost..."); 
        delay(1000); 

        lcd.setCursor(0,1);  
        lcd.print("Distance = ");
        lcd.print(distance); // Prints the measured distance
        lcd.print(" cm");

        //LED Yellow Light Up
        digitalWrite(LIGHT_GREEN,LOW);
        digitalWrite(LIGHT_YELLOW,HIGH);
        digitalWrite(LIGHT_RED,LOW);

        //Sound buzzer?
        //playBuzzerOnce();

        //check distance again
        checkDistance();       
    }*/

    while(distance > 0 && distance < 4)
    {
        lcd.setCursor(0,0); //Defining positon to write from first row,first column .
        lcd.print("Spot On...      "); 
        delay(1000); 

        lcd.setCursor(0,1);  
        lcd.print("Dist = ");
        lcd.print(distance); // Prints the measured distance
        lcd.print(" cm ");

        //LED Yellow Light Up
        digitalWrite(LIGHT_GREEN,LOW);
        digitalWrite(LIGHT_YELLOW,LOW);
        digitalWrite(LIGHT_RED,HIGH);

        //Sound buzzer?
        playBuzzerCont();

        //check distance again
        checkDistance();       
    }
     
}

void checkDistance(void){
    duration = sonar.ping();
    distance = (duration / 2) * 0.0343;
  
    Serial.print("Distance = ");
    Serial.print(distance); // Distance will be 0 when out of set max range.
    Serial.println(" cm");
    delay(500); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.  
}

void playBuzzerOneSecond(void){
    NewTone(BUZZER, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noNewTone(BUZZER);     // Stop sound...
    delay(1000);        // ...for 1sec
}

void playBuzzerCont(void){
    NewTone(BUZZER, 1000); // Send 1KHz sound signal...
    delay(5000);        // ...for 1 sec
    noNewTone(BUZZER);     // Stop sound...
    delay(1000);        // ...for 1sec
}
