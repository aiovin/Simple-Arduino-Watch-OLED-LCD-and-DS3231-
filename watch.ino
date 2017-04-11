//Тут настроен вывод в сериал монитор, так что можно проверить модуль часов без дисплея
//OLED и DS3231 подключаются вместе к: SCL - A5 // SDA - A4;
//Ну и VCC Часов - 3.3v, Дисплея - 5v. Оба с общей землей к любому GND

//Код написан по частям из разных примеров на скорую руку просто для проверки модуля реального времени с данным LCD чисто для себя
//но кому интересно, выкладываю этот код и ссылки на библиотеки

//P.S. часы настраиваются коммандой rtc.adjust. В коде уже есть, нужно настроить и за закомметить

//Демонстрация работы: https://youtu.be/vH26oa7qcDY

#include <SPI.h>
#include <Wire.h>
#include "RTClib.h" //Скачать: https://goo.gl/H1Ocu2
#include <Adafruit_GFX.h> //Скачать: https://goo.gl/mwnmOX
#include <Adafruit_SSD1306.h> //Скачать: https://goo.gl/4SNYfG
//Зачем тут две библиотеки для часов точно не помню, но раз есть то надо
#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup(){
#ifndef ESP8266
while (!Serial); // for Leonardo/Micro/Zero
#endif
 

  Serial.begin(57600); //Не забудьте переключить скорость на 57600
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  rtc.adjust(DateTime(2000, 12, 31, 24, 0, 0)); // НАСТРОЙКА года, месяца, дня, часа, минуты, секунды. После настройки и первого запуска ЗАКОММЕНТИРОВАТЬ ЭТУ СТРОКУ

display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // SCL - A5; SDA - A4;
display.clearDisplay();

/*display.startscrollright(0x00, 0x00);
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(1);
display.setCursor(0,0);
display.println("Hello world!");
display.display();
*/

/* display.setTextColor(WHITE);
display.setTextSize(1);
display.setCursor(0,0);
display.println("123");

display.setTextSize(2);
display.setCursor(0,12);
display.println("Hello");

display.setTextSize(3);
display.setCursor(0,30);
display.println("User");


//display.stopscroll();
display.display(); */

}

void loop() {
DateTime now = rtc.now();

    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.println();
    //delay(1000);

display.setTextColor(WHITE);
display.setTextSize(2);
display.setCursor(7,0);
display.println(daysOfTheWeek[now.dayOfTheWeek()]);

display.setTextSize(2);
display.setCursor(10,25);
display.println(now.day());

display.setTextSize(2);
display.setCursor(50,25);
display.println(now.month());

display.setTextSize(2);
display.setCursor(80,25);
display.println(now.year());

//-------------------------------

display.setTextSize(2);
if(now.hour()<10){
display.setCursor(10,50);
display.println("0");
display.setCursor(23,50);
display.println(now.hour());
display.setCursor(36,50);
display.println(":");
} else {
display.setCursor(10,50);
display.println(now.hour());
display.setCursor(36,50);
display.println(":");
}


display.setTextSize(2);
if(now.minute()<10){
display.setCursor(50,50);
display.println("0");
display.setCursor(63,50);
display.println(now.minute());
display.setCursor(75,50);
display.println(":");
} else{
display.setCursor(50,50);
display.println(now.minute());
display.setCursor(75,50);
display.println(":");
}

display.setTextSize(2);
if(now.second()<10){
display.setCursor(90,50);
display.println("0");
display.setCursor(103,50);
display.println(now.second());
} else{
display.setCursor(90,50);
display.println(now.second());
}


//display.stopscroll();
display.display();
display.clearDisplay();
}
