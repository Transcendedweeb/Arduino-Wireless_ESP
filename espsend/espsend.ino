#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

// WiFi parameters to be configured
const char* ssid = "ikwilinternet"; // Hoofdlettergevoelig
const char* password = "ikwilinloggen"; // Hoofdlettergevoelig

#define echoPin 18
#define trigPin 19

String postData;

long duration;
int distance;
int reference = 22;

int LDR1 = 36;
int LDR2 = 39;
int Afsensor = 38;
int light1;
int light2;
int afstand;

void setup(void) { 
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

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  if(distance > reference)
  {
    postData = "2"; 
  }
  
  light1 = analogRead(LDR1);
  light2 = analogRead(LDR2);
  Serial.println(light1);
  Serial.println(light2);

  if (light2 > 600){
    postData = "0";
  }
  if (light1 > 1600){
    postData = "1";
  }

Serial.println("");

if(WiFi.status()== WL_CONNECTED){ //Check WiFi connection status
   WiFiClient wifiClient;
   HTTPClient http; //Declare object of class HTTPClient

   http.begin(wifiClient, "http://192.168.237.1:8000/api"); //Specify request destination
   http.addHeader("Content-Type", "x-www-form-urlencoded"); //Specify content-type header
   int httpCode = http.POST(postData); //Send the request

   if(httpCode < 0){
       Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
   }

   http.end();  //Close connection
  } else {
    Serial.println("Error in WiFi connection");   
  }

  
  
  delay(1000);  //Send a request every 30 seconds

  


  
}
