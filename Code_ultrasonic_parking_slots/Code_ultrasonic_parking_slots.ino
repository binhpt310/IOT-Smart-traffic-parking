#include <ESP8266WiFi.h>
#include <ThingsBoard.h>
#include <ArduinoJson.h>
#include <FirebaseESP8266.h>

#define trig1  D1
#define echo1  D2
#define trig2  D3
#define echo2  D4
#define trig3  D5
#define echo3  D6
#define trig4  D7
#define echo4  D8

#define TOKEN              "gn827oSkCKM7kRb6n8Nu" 
#define THINGSBOARD_SERVER "demo.thingsboard.io" 
#define MY_WIFI_AP         "UiTiOt-E3.1"
#define WIFI_PASSWORD      "UiTiOtAP"


#define FIREBASE_HOST "first-firebase-project-6a5a4-default-rtdb.asia-southeast1.firebasedatabase.app"      
#define FIREBASE_AUTH "SXne7wL4uP6pWBQ3e8XffU7tkf9t95poydWsfqqy"
FirebaseData fbdo;
String path = "/";

WiFiClient espClient;
ThingsBoard tb(espClient);
 

void setup() 
{
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(trig4, OUTPUT);
  pinMode(echo4, INPUT);

  Serial.begin(9600); 
  Serial.print("Connecting to WiFi...");
  
  //WiFi.begin("Wokwi-GUEST", "");
  WiFi.begin(MY_WIFI_AP, WIFI_PASSWORD);
  //WiFi.setAutoConnect(autoConnect);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to the WiFi !");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

float DistanceInCm(int Trig, int Echo)
{
    digitalWrite(Trig, LOW);
    delay(200);
    digitalWrite(Trig, HIGH);
    delay(200);
    digitalWrite(Trig, LOW);

    float Distance = pulseIn(Echo, HIGH) *0.0344/2;
    return Distance;
    
}

void loop() 
{
  int Count = 0;
  int Freeslot = 0;

  tb.connect(THINGSBOARD_SERVER, TOKEN);
  
//==========================================================
  float Distance1 = DistanceInCm(trig1, echo1);
  if (Distance1 < 15 && Distance1 > 0) {
    Firebase.setString(fbdo, "/UIT_Parking/Slot1", "Full");
    tb.sendTelemetryString("Slot1", "Full");
    Count +=1;
  }

  else {
    Firebase.setString(fbdo, "/UIT_Parking/Slot1", "Empty");
    tb.sendTelemetryString("Slot1", "Empty");
  }
  Serial.print("Distance of ultrasonic1: ");
  Serial.println(Distance1);
  tb.sendTelemetryFloat("Distance 1:", Distance1);
  Firebase.setInt(fbdo, "/UIT_Parking/Slot1_status", Distance1);

 
//==========================================================
  float Distance2 = DistanceInCm(trig2, echo2);
  if (Distance2 < 15 && Distance2 > 0){
    Firebase.setString(fbdo, "/UIT_Parking/Slot2", "Full");
    Count +=1;
  }
  
  else {
    Firebase.setString(fbdo, "/UIT_Parking/Slot2", "Empty");
    tb.sendTelemetryString("Slot2", "Empty");
  }
  Serial.print("Distance of ultrasonic2: ");
  Serial.println(Distance2);
  tb.sendTelemetryFloat("Distance 2:", Distance2);
  Firebase.setInt(fbdo, "/UIT_Parking/Slot2_status", Distance2);
  
//==========================================================
  float Distance3 = DistanceInCm(trig3, echo3);
  if (Distance3 < 15 && Distance3 > 0){
    Firebase.setString(fbdo, "/UIT_Parking/Slot3", "Full");
    Count +=1;
  }
  else {
    Firebase.setString(fbdo, "/UIT_Parking/Slot3", "Empty");
    tb.sendTelemetryString("Slot3", "Empty");
  }
  Serial.print("Distance of ultrasonic3: ");
  Serial.println(Distance3);
  tb.sendTelemetryFloat("Distance 3:", Distance3);
  Firebase.setInt(fbdo, "/UIT_Parking/Slot3_status", Distance3);

//==========================================================
  float Distance4 = DistanceInCm(trig4, echo4);
  if (Distance4 < 15 && Distance4 > 0){
    Firebase.setString(fbdo, "/UIT_Parking/Slot4", "Full");
    Count +=1;
  }
  
  else {
    Firebase.setString(fbdo, "/UIT_Parking/Slot4", "Empty");
    tb.sendTelemetryString("Slot1", "Full");
  }
  Serial.print("Distance of ultrasonic4: ");
  Serial.println(Distance4);
  tb.sendTelemetryString("Distance 4:", Distance4);
  Firebase.setInt(fbdo, "/UIT_Parking/Slot4_status", Distance4);



  Freeslot = 4 - Count;
  tb.sendTelemetryInt("Freeslot: ", Freeslot);
  Serial.print("Free slot: ");
  Serial.println(Freeslot);
  Firebase.setInt(fbdo, "/UIT_Parking/AllFreeSlots", Freeslot); 
  //Firebase.setInt(fbdo, "/USSH Parking/", Freeslot);
  
  delay(500);
  Freeslot = 0;
  Count = 0;
}
