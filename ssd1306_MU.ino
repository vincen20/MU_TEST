#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
// If using software SPI (the default case):
#define OLED_MOSI  11
#define OLED_CLK   12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
 
void setup()   {       
  Serial.begin(115200);         
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
}
bool _valid;
int comdata[50];
int data_p,dataDetected;
void loop() {
if(Serial.available() >0 )  
  {
    int  dataByte=Serial.read();     
    if (dataByte == 0xFE)
    { 
     comdata[data_p] = dataByte;
    int temp_p = data_p;
    data_p = 0;
    
 if (comdata[temp_p-1] == 0xFF)
 {
  dataDetected = comdata[0];
  if(dataDetected){
        display.display();
      display.clearDisplay();    
  display.setCursor(0,0);
  display.setTextSize(0);
  display.setTextColor(BLACK, WHITE);
//  display.setTextColor(WHITE);
  display.print("SCR:");
  display.print(comdata[1]); 
  display.println(comdata[2]); 
  int x=comdata[3];
  if(x>128){x=128;}
  int y=comdata[4]-32;
  if(y>64){y=64;}
  int w=comdata[5];
    if(w>128){w=128;}
  int h=comdata[6];
    if(h>64){x=64;}  
  display.drawRect(x,y,w,h, WHITE);
  
  display.display();
  delay(1000);
  display.clearDisplay();  
  _valid = true;
  }
  else
  {
      
      display.display();
      display.clearDisplay();  
        display.setCursor(0,0);
       display.setTextSize(2);
      display.setTextColor(BLACK, WHITE);
        display.println("NO OBJ ."); 
    }
      }
      else
      {
        _valid = false;
      }
    }
    else
    {
      comdata[data_p] = dataByte ;
      data_p++ ;
    }
  }




}
 

