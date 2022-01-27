#include <SerialID.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_SPI.h>

//paramters define
#define MODEL SSD1283A
#define CS   10
#define CD   12
#define SDA  11
#define MOSI SDA
#define MISO 8
#define SCK  13
#define RST  9
#define LED  -1

LCDWIKI_SPI mylcd(MODEL,CS,CD, MISO, MOSI, RST, SCK, LED); 

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#include <SerialID.h>
SerialIDset("\n#\tv2.01 " __FILE__ "\t" __DATE__ " " __TIME__);

uint32_t color;
uint32_t colorTemp;
uint32_t colorHum;
uint32_t colorLight;
uint32_t colorCo2;
uint32_t colorTvoc;

String nom = "Arduino";
String msg;
String incomingTemp;
String incomingHum;
String incomingLight;
String incomingCo2;
String incomingTvoc;

int temp;
int hum;
int light;
int co2;
int tvoc;

void setup() {
  Serial.begin(9600);
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);
}

void loop() {
  readSerialPort();
  if (msg != "") {
    sendData();
  }
  if(msg[0] == 't'){
    incomingTemp = msg.substring(1);
    temp = incomingTemp.toInt();
    if(temp > 23 && temp < 25.5){
      colorTemp = GREEN;
    } else if(temp > 20 && temp < 28) {
      colorTemp = YELLOW;
    } else {
      colorTemp = RED;
    }
  } else if(msg[0] == 'h'){
    incomingHum = msg.substring(1);
    hum = incomingHum.toInt();
    if(hum > 40 && hum < 70){
      colorHum = WHITE;
    } else {
      colorHum = RED;
    }
  } else if(msg[0] == 'l'){
    incomingLight = msg.substring(1);
    light = incomingLight.toInt();
    if(light > 500 && light < 750){
      colorLight = WHITE;
    } else if(light > 300 && light < 1000) {
      colorLight = YELLOW;
    } else {
      colorLight = RED;
    }
  } else if(msg[0] == 'c'){
    incomingCo2 = msg.substring(1);
    co2 = incomingCo2.toInt();
    if(co2 < 600){
      colorCo2 = WHITE;
    } else if(co2 < 1000) {
      colorCo2 = YELLOW;
    } else {
      colorCo2 = RED;
    }
  } else if(msg[0] == 'v'){
    incomingTvoc = msg.substring(1);
    tvoc = incomingTvoc.toInt();
    if(tvoc < 250){
      colorTvoc = WHITE;
    } else if(tvoc < 300) {
      colorCo2 = YELLOW;
    } else {
      colorTvoc = RED;
    }
  }
  readSerialPort();
  
  color = WHITE;
  mylcd.Set_Text_Mode(0);
  
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_Back_colour(BLACK);
  
  mylcd.Set_Text_colour(color);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Temp: ", 5, 13);
  //mylcd.Print_String(msg, 5, 13);
  mylcd.Set_Text_colour(colorTemp);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String(incomingTemp, 68, 5);

  mylcd.Set_Text_colour(color);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Humidity: ", 5, 39);
  mylcd.Set_Text_colour(colorHum);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String(incomingHum, 68, 31);
  
  mylcd.Set_Text_colour(color);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Light: ", 5, 65);
  mylcd.Set_Text_colour(colorLight);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String(incomingLight, 68, 57);
  
  mylcd.Set_Text_colour(color);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("CO2: ", 5, 91);
  mylcd.Set_Text_colour(colorCo2);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String(incomingCo2, 68, 83);
  
  mylcd.Set_Text_colour(color);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("TVOC: ", 5, 117);
  mylcd.Set_Text_colour(colorTvoc);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String(incomingTvoc, 68, 109);

  delay(500);
}

void readSerialPort() {
  msg = "";
  if (Serial.available()) {
    delay(10);
    while (Serial.available() > 0) {
      msg += (char)Serial.read();
    }
    Serial.flush();
  }
}

void sendData() {
  //write data
  Serial.print(nom);
  Serial.print(" received : ");
  Serial.print(msg);
}
