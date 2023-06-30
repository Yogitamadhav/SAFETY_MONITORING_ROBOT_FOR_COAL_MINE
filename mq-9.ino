
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define values      A0                        
#define led         D6                       

// You should get Auth Token in the Blynk App.

char auth[] = "JBTa1Q4en-dOocFd6zi83qSwejcP9uDN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "********";
char pass[] = "********";

#define DHTPIN D3          // What digital pin we're connected to

#define DHTTYPE DHT11     // DHT 11


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  if(h<40){                             
    digitalWrite(led,HIGH); //turn on led
     Serial.println("high");
      Blynk.notify("humidity is high");
  }
  else{                                       //if not
    digitalWrite(led,LOW);
     Serial.println("low");//turn off led
      }
      if(t>40){                             
    digitalWrite(led,HIGH); //turn on led
     Serial.println("high");
     Blynk.notify("temperature is low");
  }
  else{                                       //if not
    digitalWrite(led,LOW);
     Serial.println("low");//turn off led
      }
}


void setup() {
  pinMode(values,INPUT);           
   pinMode(led,OUTPUT);            
   Serial.begin(9600);
  // put your setup code here, to run once:
  Blynk.begin(auth, ssid, pass);


  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);


}

void loop() {
  int values;
  values =analogRead(A0);
  Serial.println(values);
   Blynk.virtualWrite(V7, values);
  
   if(values>400){                             
    digitalWrite(led,HIGH); //turn on led
     Serial.println("high");
     Blynk.notify("flammable gas is there");
  }
  else{                                       //if not
    digitalWrite(led,LOW);
     Serial.println("low");//turn off led
      }
       
 delay(500);

  Blynk.run();
  timer.run();
}
