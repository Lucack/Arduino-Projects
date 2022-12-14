/* ========================================================================================================



======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <virtuabotixRTC.h>                    //biblioteca para o RTC DS1302      


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   clk   6
#define   dat   7
#define   rst   8


// ========================================================================================================
// --- Constantes Auxiliares ---
#define   segL       50
#define   minL       29
#define   horL       15
#define   d_semL      5
#define   d_mesL     29
#define   mesL       10
#define   anoL     2020


// ========================================================================================================
// --- Declaração de Objetos ---
virtuabotixRTC   myRTC(clk, dat, rst);         //declara objeto para o RTC


// ========================================================================================================
// --- Protótipo das Funções ---
void DS1302();
void week(int dayW);

int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};
const int LED_PIN = 10;
const int buzzer = 10;
const int HORA = 15;        
const int MINUTO = 30; 
const int SEC = 00;

// ========================================================================================================
// --- Configurações Iniciais ---
void setup()  
{   
  pinMode(buzzer,OUTPUT);
  //digitalWrite(LED_PIN, HIGH);
  delay(2000);                                              
  //digitalWrite(LED_PIN, LOW);   
  Serial.begin(9600);

  //Faça upload do código para o Arduino uma vez para carregar os
  //dados iniciai no RTC.
  //Após, comente a linha abaixo e faça upload novamente. 
  myRTC.setDS1302Time(segL, minL, horL, d_semL, d_mesL, mesL, anoL);
  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()  
{
  
   DS1302();
  
} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---
void DS1302()
{
  myRTC.updateTime();         //faz leitura do DS1302

  // Imprime informações
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
  
} //end DS1302

 
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
   
  } //end switch
  
   if (((myRTC.hours) == HORA) && ((myRTC.minutes) == MINUTO) &&  ((myRTC.seconds) == SEC)) {  
        
        //digitalWrite(LED_PIN, HIGH)
        
        //tone(buzzer,1500);             
        //delay(500); 


        for (int nota = 0; nota < 156; nota++) {
 
              int duracaodanota = duracaodasnotas[nota];
              tone(buzzer, melodia[nota],duracaodanota);
              int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
              delay(pausadepoisdasnotas[nota]);}
               
  } else {  
        //digitalWrite(LED_PIN, LOW)
        
        noTone(buzzer);
        //delay(500); 

        
  }

} //end week
