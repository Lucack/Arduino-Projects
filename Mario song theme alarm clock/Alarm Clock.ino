#include <virtuabotixRTC.h>                      

#define   clk   6
#define   dat   7
#define   rst   8

#define   segL       00
#define   minL       00
#define   horL       22
#define   d_semL      3
#define   d_mesL     16
#define   mesL       03
#define   anoL     2021



virtuabotixRTC   myRTC(clk, dat, rst);

void DS1302();
void week(int dayW);

//const int LED_PIN = 10;

//LED RGB:
const int blue = 3;
const int red = 5;
const int green = 11;
//const leds[] = 


//Dia do Lembrete 1 :
const int DIA1 = 16;        

//Dia do Lembrete 2 :
const int DIA2 = 2;

//Dia do Lembrete 3 :
const int DIA3 = 3;        

//Dia do Lembrete 4 :
const int DIA4 = 4;



void setup()  
{    
  delay(2000);                                               
  Serial.begin(9600);
  //myRTC.setDS1302Time(segL, minL, horL, d_semL, d_mesL, mesL, anoL);
}

void loop()  
{
  
   DS1302();
  
}
void DS1302()
{
  myRTC.updateTime();

  Serial.print(" -> ");
  week(myRTC.dayofweek);
  Serial.print(" | ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" | ");
  if(myRTC.hours < 10) Serial.print("0");
  Serial.print(myRTC.hours);
  Serial.print(":");
  if(myRTC.minutes < 10) Serial.print("0");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  if(myRTC.seconds < 10) Serial.print("0");
  Serial.println(myRTC.seconds);
  delay(1000);
  } 
void week(int dayW)
{
    switch(dayW)
  {
    case 1: Serial.print("Dom"); break;
    case 2: Serial.print("Seg"); break;
    case 3: Serial.print("Ter"); break;
    case 4: Serial.print("Qua"); break;
    case 5: Serial.print("Qui"); break;
    case 6: Serial.print("Sex"); break;
    case 7: Serial.print("Sab"); break;
   }
  
   if (((myRTC.dayofmonth) == DIA1)) {
        digitalWrite(red, HIGH);
        digitalWrite(blue, HIGH);
        digitalWrite(green, HIGH);           
                      }
                                     
    
  if (((myRTC.dayofmonth) == DIA2)) {
        digitalWrite(red, HIGH);
        digitalWrite(blue, HIGH);
        digitalWrite(green, HIGH);

 
  delay(650);
}
      
   else { 
        //digitalWrite(LED_PIN, LOW)
        digitalWrite(red, LOW);
        digitalWrite(blue, LOW);
        digitalWrite(green, LOW);
          
  }

} //end week
