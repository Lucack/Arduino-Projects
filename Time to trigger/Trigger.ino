/*******************************************************************************
* Utilizando RTC Ds3231 para acionar dispositivo com hora marcada
*******************************************************************************/
// Arduino DS3232RTC Library
// https://github.com/JChristensen/DS3232RTC
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch to display the date and time from a DS3231
// or DS3232 RTC every second. Display the temperature once per
// minute. (The DS3231 does a temperature conversion once every
// 64 seconds. This is also the default for the DS3232.)
//
// Set the date and time by entering the following on the Arduino
// serial monitor:
//  year,month,day,hour,minute,second,
//
// Where
//  year can be two or four digits,
//  month is 1-12,
//  day is 1-31,
//  hour is 0-23, and
//  minute and second are 0-59.
//
// Entering the final comma delimiter (after "second") will avoid a
// one-second timeout and will allow the RTC to be set more accurately.
//
// No validity checking is done, invalid values or incomplete syntax
// in the input will result in an incorrect RTC setting.
//
// Jack Christensen 08Aug2013


// PARA ACERTAR A DATA E HORA DO RELOGIO 
// VÁ NO MONITOR (menu Ferramentas -> Monitor Serial
// E no espaço à esquerda do botao ENVIAR digite a data e hora no seguinte formato, utilizando as virgulas:
// AAAA,MM,DD,HH,MM,SS
// onde AAAA = Ano,
//      MM   = Mes
//      DD   = Dia
//      HH   = Hora
//      MM   = Minuto
//      SS   = Segundos
// E depois clique no botão enviar

#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>      // http://arduiniana.org/libraries/streaming/
#include <Wire.h> // i2c
//Essa é a bliblioteca do LCD 
#include <LiquidCrystal_I2C.h>

// criacao do lcd 16x2
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Array que desenha o simbolo de grau
byte a[8]= {B00110,B01001,B00110,B00000,B00000,B00000,B00000,B00000,}; 
byte campanhia[8]={B00000,B00100,B01110,B01110,B11111,B00100,B00000,B00000};
byte branco[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000};

const int LED_PIN = 9;    //pino definido para conexao com o led
const int HORA = 20;        //variavel de hora que o LED ira acionar
const int MINUTO = 15;      //variavel de minuto que o LED ira acionar

void setup()
{
    digitalWrite(LED_PIN, HIGH);                             //aciona LED
    delay(2000);                                              
    digitalWrite(LED_PIN, LOW);   // DESLIGA O LED
    Serial.begin(9600);

    // setSyncProvider() causes the Time library to synchronize with the
    // external RTC by calling RTC.get() every five minutes by default.
    setSyncProvider(RTC.get);
    Serial << F("RTC Sync");
    if (timeStatus() != timeSet) Serial << F(" FAIL!");
    Serial << endl;

    lcd.begin(16,2);
    lcd.print("RTC DS3231 +");
    lcd.setCursor(0,1);
    lcd.print("Temperatura");
    delay(3000);
    lcd.clear();

    //Atribui a "1" o valor do array "A", que desenha o simbolo de grau
    lcd.createChar(1, a); 
    lcd.createChar(2, campanhia); 
    lcd.createChar(3, branco); 
}

void loop()
{
    static time_t tLast;
    time_t t;
    tmElements_t tm;

    // check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s
    if (Serial.available() >= 12) {
        // note that the tmElements_t Year member is an offset from 1970,
        // but the RTC wants the last two digits of the calendar year.
        // use the convenience macros from the Time Library to do the conversions.
        int y = Serial.parseInt();
        if (y >= 100 && y < 1000)
            Serial << F("Error: Year must be two digits or four digits!") << endl;
        else {
            if (y >= 1000)
                tm.Year = CalendarYrToTm(y);
            else    // (y < 1000)
                tm.Year = y2kYearToTm(y);
            tm.Month = Serial.parseInt();
            tm.Day = Serial.parseInt();
            tm.Hour = Serial.parseInt();
            tm.Minute = Serial.parseInt();
            tm.Second = Serial.parseInt();
            t = makeTime(tm);
            RTC.set(t);        // use the time_t value to ensure correct weekday is set
            setTime(t);
            Serial << F("RTC set to: ");
            printDateTime(t);
            Serial << endl;
            // dump any extraneous input
            while (Serial.available() > 0) Serial.read();
        }
    }

    t = now();
    if (t != tLast) {
        tLast = t;
        printDateTime(t);
        if (second(t) == 0) {
            float c = RTC.temperature() / 4.;
            float f = c * 9. / 5. + 32.;
            Serial << F("  ") << c << F(" C  ") << f << F(" F");
            lcd.setCursor(9,1);
            lcd.print(c); // Aqui mostra a temperatura em Graus Centigrados
            // lcd.print(f); // Aqui a temperatura em FARENHEITS
            lcd.write(1); //Escreve o simbolo de grau
            lcd.print('C');
        }
        Serial << endl;
    }
}

// print date and time to Serial
void printDateTime(time_t t)
{
    lcd.setCursor(0,0);
    if(day(t) < 10) lcd.print('0');
    lcd.print(day(t));
    lcd.print("/");
    if(month(t) < 10) lcd.print('0');
    lcd.print(month(t));
    lcd.print("/");
    lcd.print(year(t)); 
    
    lcd.setCursor(0,1);
    if(hour(t) < 10) lcd.print('0');
    lcd.print(hour(t));
    lcd.print(':');
    if(minute(t) < 10) lcd.print('0');
    lcd.print(minute(t));
    lcd.print(':');
    if(second(t) < 10) lcd.print('0');
    lcd.print(second(t));
    lcd.print(' ');
    
    
    printDate(t);
    Serial << ' ';
    printTime(t);

    if ((hour(t) == HORA) && (minute(t) == MINUTO)) {  //se no instante que hora atual for igual a hora da variavel
        lcd.setCursor(11,0);
        digitalWrite(LED_PIN, HIGH); 
        lcd.write(2); //Escreve o simbolo de campanhia
    } else {  
        lcd.setCursor(11,0); //senao
        digitalWrite(LED_PIN, LOW); 
        lcd.write(3); //Escreve o quadro branco
    }
}

// print time to Serial
void printTime(time_t t)
{
    printI00(hour(t), ':');
    printI00(minute(t), ':');
    printI00(second(t), ' ');
}

// print date to Serial
void printDate(time_t t)
{
    printI00(day(t), 0);
    Serial << monthShortStr(month(t)) << _DEC(year(t));
}

// Print an integer in "00" format (with leading zero),
// followed by a delimiter character to Serial.
// Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
    if (val < 10) Serial << '0';
    Serial << _DEC(val);
    if (delim > 0) Serial << delim;
    return;
}
