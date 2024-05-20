
#include <WiFi.h>

const char* ssid     = "wifi007";
const char* password = "12345678";

const char* host = "iotproject2024.000webhostapp.com";
const char* streamId   = "....................";
const char* privateKey = "....................";
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define WIDTH 128 // OLED width (pixels)
#define HEIGHT 64 // OLED height (pixels)

#define ADDRESS 0x3C
float lat=0;
float lon=0;

int volt = A0;
float dc=0;
float dc1=0;
int loc=0;
//Creation of SSD1306 display object
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

void setup() {
   Serial.begin(9600);

   if(!display.begin(SSD1306_SWITCHCAPVCC, ADDRESS)) {
      Serial.println("SSD1306 initialization failed");
      while(1){}
   }
    Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
   
//analogReadResolution(9);
//analogSetWidth(9);
   delay(1000);
 
pinMode(34,INPUT);
pinMode(25,INPUT);
pinMode(26,INPUT);
pinMode(27,INPUT);
}

void loop() {
read_voltage1();

lat=10.82;
lon=77.06;
   

if((digitalRead(25))) 
  {
    loc=1;
 }
    
if((digitalRead(26))) 
  {
    loc=2;
    }
if((digitalRead(27))) 
  {
    loc=3;
   
    }
if((digitalRead(14))) 
  {
    loc=0;
   
    }

if(loc==1)
{
    display.setCursor(0, 35);
   display.print("loc : Ebulk-1 Reached");
   display.display();
   
lat=10.78;
lon=77.21;   
 
  }

else if(loc==2)
{
   display.setCursor(0, 35);
   display.print("loc : Ebulk-2 Reached");
   display.display();
   lat=10.52;
   lon=77.79;
  
  }
else if(loc==3)
{
  display.setCursor(0, 35);
   display.print("loc : Ebulk-3 Reached");
   display.display();
   lat=10.33;
   lon=77.52;
  }
  
else
{
  display.setCursor(0, 35);
   display.print("loc : Near E-Bulk 1 ");
   display.display();
  
  }
    
display.setCursor(0, 20);
display.print("lat: ");display.print(lat);
display.print(" lon: ");display.print(lon);
display.display();
  
    Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "GET https://iotproject2024.000webhostapp.com/ebulk_iot/update.php?v="; // Getting info from my online database through my online website
  url+=dc;
  url+="&lat=";
  url+=lat;
  url+="&lon=";
  url+=lon;
  url+="&loc=";
  url+=loc;
  url+=" HTTP/1.1\r\nHost: iotproject2024.000webhostapp.com\r\n\r\n";
  url += "\r\n\r\n";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(url);
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    char a=client.read();
    Serial.print(a);
    if(a=='*')
    {
      a=client.read();
    Serial.print(a);
    if(a=='a')
    {
      a=client.read();
      Serial.print(a);
    if(a=='1')
    {
      }
      if(a=='0')
    {
      }  
      
    }  
      }
    //String line = client.readStringUntil('\r');
    //Serial.print(line);
   
    Serial.print(a);
 
     
    }
delay(2000);

  
  }

void read_voltage1()
{
  dc = analogRead(34);
  dc = (dc/2048)*12*0.70;
  display.clearDisplay();

   display.setTextColor(WHITE);
   display.setTextSize(1);
   display.setCursor(0, 5);
   display.print("Bat Voltage : ");
   display.print(dc);
   display.print(" V");
   display.display();

  if(dc>=11)
  {
    display.setCursor(0, 50);
   display.print("BT Status : Good");
   display.display();
    }
  else if((dc>=9)&&(dc<11))
  {
    display.setCursor(0, 50);
   display.print("BT: need to charge");
   display.display();
    }
    else if((dc<9))
  {
    display.setCursor(0, 50);
   display.print("BT: charge too low");
   display.display();
    }
  }
  
