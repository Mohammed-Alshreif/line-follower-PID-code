//محمد عادل عبد العزيز الشريف
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  
#define sensor_right1 4
#define sensor_right2 8
#define sensor_midel 10
#define sensor_left1 11
#define sensor_left2 7
int pos;
int counter=0;

void setup() {
 lcd.init();                     
 lcd.init();
 lcd.backlight();

  pinMode(sensor_right1,INPUT);
  pinMode(sensor_right2,INPUT);
  pinMode(sensor_midel,INPUT);
  pinMode(sensor_left1,INPUT);
  pinMode(sensor_left2,INPUT);
    
 
  
 lcd.setCursor(3,0);
 lcd.print("# M_20X #         ");

}
int sensTrace() {
  int ret = B00000;
  int a[5]={digitalRead(sensor_right1),
            digitalRead(sensor_right2),
            digitalRead(sensor_midel),
            digitalRead(sensor_left1),
            digitalRead(sensor_left2)};
            
  for (int i = 0; i < 5; i++) {
    if (a[i] == HIGH) ret += (0x1 << i);
  }
  
  return ret;
}
void sensLogic(int X) {
  switch (X) {
    case B00000:
     lcd.setCursor(1,1);
     lcd.print("DO THE LAST ACTION      ");
      break;
    case B11111:
    case B01110:
  //case B01111:
  //case B11110:
     lcd.setCursor(1,1);
     lcd.print("      GO           ");
    counter++;
    delay(62);
      break;
    case B00010:
    case B00110:
      lcd.setCursor(1,1);
      lcd.print("    RIGHT          ");
      break;
    case B00001:
    case B00011:
    //case B00111:
      lcd.setCursor(1,1);
      lcd.print("  MORE RIGHT          ");
      break;
    case B00100:
      lcd.setCursor(1,1);
      lcd.print("      GO            ");
      break;
    case B01000:
    case B01100:
      lcd.setCursor(1,1);
      lcd.print("    LEFT          ");
      break;
    case B10000:
    case B11000:
    //case B11100:
      lcd.setCursor(1,1);
      lcd.print("  MORE LEFT          ");
      break;
    default:
      
      break;
  }
}

void loop() {
   //delay(200);
   
  if(counter==0){
     lcd.setCursor(3,0);
 lcd.print("# M_20X #  S     ");
   }
   else if(counter==1||counter==2||counter==3){
   lcd.setCursor(3,0);
 lcd.print("# M_20X #  A     ");
   }
  else if(counter==4||counter==5||counter==6){
   lcd.setCursor(3,0);
 lcd.print("# M_20X #  B     ");
   }
   else if(counter==8||counter==9||counter==10){
   lcd.setCursor(3,0);
 lcd.print("# M_20X #  C     ");
   }
   else if(counter>=11){
    lcd.setCursor(3,0);
 lcd.print("# M_20X #  D     ");
   }
   /*
   lcd.setCursor(0,0);
 lcd.print(counter);
 
   */
   
  pos = sensTrace();
  sensLogic(pos);
 // lcd.clear();

}
