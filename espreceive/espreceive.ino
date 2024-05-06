#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WifiClient.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 4
#define NUMPIXELS 64

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "ikwilinternet"; // Hoofdlettergevoelig
const char* password = "ikwilinloggen"; // Hoofdlettergevoelig
String stat = "0";
String old;

int buitenranden[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 23, 24, 39, 40, 55, 56, 57, 58, 59, 60, 61, 62, 63, 48, 47, 32, 31, 16, 15};
int binnenranden[] = {9, 10 , 11, 12, 13, 14, 17, 22, 25, 30, 33, 38, 41, 46, 49, 50, 51, 52, 53, 54};
int binnenranden2[] = {18, 19, 20, 21, 26, 29, 34, 37, 42, 43, 44, 45};
int binnenste[] = {27, 28, 35, 36};
int laag1[] = {9, 10, 11, 12, 13, 14};
int laag2[] = {17, 18, 19, 20, 21, 22};
int laag3[] = {25, 26, 27, 28, 29, 30};
int laag4[] = {33, 34, 35, 36, 37, 38};
int laag5[] = {41, 42, 43, 44, 45, 46};
int laag6[] = {49, 50, 51, 52, 53, 54};

void setup(void) { 
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(115200);
  Serial.print("Bezig met verbinden");
  WiFi.begin(ssid, password); // Connect to WiFi

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  // Verbonden.
  Serial.println("OK!");
  // Access Point (SSID).
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // IP adres.
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  // Signaalsterkte.
  long rssi = WiFi.RSSI();
  Serial.print("Signaal sterkte (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println("");

  pixels.begin();

}

void loop() {
if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
   WiFiClient wifiClient;
   HTTPClient http; //Declare object of class HTTPClient

   http.begin(wifiClient, "http://192.168.237.1:8000/api/"); //Specify request destination
   http.addHeader("Content-Type", "x-www-form-urlencoded"); //Specify content-type header

   http.GET();
   String data = http.getString();
   Serial.println(data);
   Serial.println(stat);

   stat = data;

   if (stat == "0"){
    old = stat;
    setLeeg();
//    pixels.setPixelColor(0, pixels.Color(0, 150, 0));
   }
   else if (stat == "1"){
    old = stat;
    setHalf();
//    pixels.setPixelColor(0, pixels.Color(150, 150, 0));
   }
   else if (stat == "2"){
    old = stat;
    setVol();
   }
   

//   if (data != stat){
//      if(stat == "0"){
//        setLeeg();
//      }
//      else if(stat == "1"){
//        setHalf();
//      }
//      else if(stat == "2"){
//        setVol();
//      }
//   }
   


   http.end();  //Close connection
  } else {
    Serial.println("Error in WiFi connection");   
  }
  pixels.show();
  delay(1000);  //Send a request every 30 seconds
}





//matrix functies
void setLeeg(){
  for (int i=0; i<28; i++){
      pixels.setPixelColor(buitenranden[i], pixels.Color(0, 255, 0));
  }
  for (int i=0; i<20; i++){
    pixels.setPixelColor(binnenranden[i], pixels.Color(0, 160, 0));
  }
  for (int i=0; i<12; i++){
    pixels.setPixelColor(binnenranden2[i], pixels.Color(0, 100, 0));
  }
  for (int i=0; i<4; i++){
    pixels.setPixelColor(binnenste[i], pixels.Color(0, 60, 0));
  }
}

void setHalf(){

//  binnenste aanzetten
  for (int i=0; i<28; i++){
      pixels.setPixelColor(buitenranden[i], pixels.Color(70, 35, 0));
    }
  for (int i=0; i<20; i++){
    pixels.setPixelColor(binnenranden[i], pixels.Color(125, 70, 0));
  }
  for (int i=0; i<12; i++){
    pixels.setPixelColor(binnenranden2[i], pixels.Color(255, 140, 0));
  }
  for (int i=0; i<4; i++){
    pixels.setPixelColor(binnenste[i], pixels.Color(255, 140, 0));
  }
  

  
//  buiten ring
  
//  for (int i=0; i<28; i++){
//    pixels.setPixelColor(buitenranden[i], pixels.Color(255, 100, 0));
//    pixels.setPixelColor(buitenranden[i-3], pixels.Color(0, 0, 0));
//    if(i == 0){
//      pixels.setPixelColor(31, pixels.Color(0, 0, 0));
//      pixels.setPixelColor(16, pixels.Color(255, 100, 0));
//      pixels.setPixelColor(15, pixels.Color(255, 100, 0));
//    }
//    if(i == 1){
//      pixels.setPixelColor(31, pixels.Color(0, 0, 0));
//      pixels.setPixelColor(16, pixels.Color(0, 0, 0));
//      pixels.setPixelColor(15, pixels.Color(255, 100, 0));
//    }
//    if(i == 2){
//      pixels.setPixelColor(31, pixels.Color(0, 0, 0));
//      pixels.setPixelColor(16, pixels.Color(0, 0, 0));
//      pixels.setPixelColor(15, pixels.Color(0, 0, 0));
//    }
//    delay(100);
//    pixels.show();
//    
//  }
  
}


void setVol(){
  for (int i=0; i<28; i++){
    pixels.setPixelColor(buitenranden[i], pixels.Color(255, 0, 0));
  }
  for (int i=0; i<20; i++){
    pixels.setPixelColor(binnenranden[i], pixels.Color(200, 0, 0));
  }
  for (int i=0; i<12; i++){
    pixels.setPixelColor(binnenranden2[i], pixels.Color(150, 0, 0));
  }
  for (int i=0; i<4; i++){
    pixels.setPixelColor(binnenste[i], pixels.Color(100, 0, 0));
  }
  pixels.show();
  delay(1000);

  for (int i=0; i<28; i++){
    pixels.setPixelColor(buitenranden[i], pixels.Color(0, 0, 0));
  }
  for (int i=0; i<20; i++){
    pixels.setPixelColor(binnenranden[i], pixels.Color(0, 0, 0));
  }
  for (int i=0; i<12; i++){
    pixels.setPixelColor(binnenranden2[i], pixels.Color(0, 0, 0));
  }
  for (int i=0; i<4; i++){
    pixels.setPixelColor(binnenste[i], pixels.Color(0, 0, 0));
  }
}
