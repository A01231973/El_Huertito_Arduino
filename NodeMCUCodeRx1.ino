#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <FirebaseObject.h>
#include <SoftwareSerial.h>

#define WIFI_SSID "IMF2020"
#define WIFI_PASSWORD "Damajeti2013@"
//#define FIREBASE_HOST "pruebamcu-91983.firebaseio.com"
//define FIREBASE_AUTH "Rqkxle1NXMeH583a9wh4a5nUJPI3ek6KducWzbIm"
#define FIREBASE_HOST "el-huertito.firebaseio.com"
#define FIREBASE_AUTH "zbUqF85rvSMtJysxPLceCTW1EWp6zojIz9ZIMa6i"



SoftwareSerial s(D6,D5);
int sensorHumedad;
int sensorTemp;
int data;


void setup() {
s.begin(9600);
Serial.begin(9600);

//-------------------------Conecciones a internet y Firebase
wifiConnect();

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    if (Firebase.failed()) {
        Serial.print("setting number failed:");
        Serial.println(Firebase.error());
    } else {
        Serial.print("Firebase connected ");
    }
    delay(10);
    
}// end setup
 
void loop() {
  //--------------------- Coneccion de arduino y MCU
  s.write("s");
  if (s.available()>0)
  {
    data=s.read();
    Serial.print("dato_ ");
    Serial.println(data);
    if (data<70){
      sensorTemp=data;
    } else {
      sensorHumedad=data;
    }
    Serial.println(sensorHumedad);
    Serial.println(sensorTemp);
  }
 //----------------------

 
 Serial.print("["+Firebase.getString("LED1")+"]\n"); //verificar que entre a firebase
 Firebase.setInt("Hum",sensorHumedad);
 Firebase.setInt("Temp",sensorTemp);

 if(WiFi.status() != WL_CONNECTED) {
        wifiConnect();
    }
    delay(10);
} //end Loop--------------------------------------------------------------


//funcion wifi---------------------------------------------------------------
void wifiConnect() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     //Conectar con la red WiFi
    Serial.print("Conectando WiFi --> ");
    Serial.print(WIFI_SSID); Serial.println(" ...");

    int teller = 0;
    while (WiFi.status() != WL_CONNECTED) {   //Esperar por la conexiÛn WiFi
        delay(1000);
        Serial.print(++teller); Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("WiFi conectado!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
} //End wifiConnect()
