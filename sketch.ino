#include <DHT.h>

#define DHTPIN 15         // DHT22 data pin connected to GPIO15
#define DHTTYPE DHT22
DHT dht(DHTPIN,DHTTYPE) ;    // Sensor type is DHT22

#define GREEN_LED 5      // Heater (LED) control pin
#define RED_LED 18 
#define BUZZER_PIN 19        // Warning LED pin

#define MIN_TEMP 25.0     // Minimum temperature to turn ON heater
#define MAX_TEMP 30.0 
String laststate="" ;   // Maximum temperature to turn OFF heater



void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
   pinMode(BUZZER_PIN, OUTPUT);

 digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}


void loop() {
  float temp = dht.readTemperature(); // Read temperature in Celsius

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(1000);
    return;
  }
  String currentState="";
  String lastState="";

 
  // Heater ON if temp is below MIN_TEMP
  if (temp < MIN_TEMP) {
    currentState="Heating";
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED,LOW);
    digitalWrite(BUZZER_PIN,LOW);
    
  }
  // Heater OFF if temp exceeds MAX_TEMP
  else if (temp <=MAX_TEMP) {
    currentState="Target Reached";
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER_PIN,LOW);
    
  }
  // Overheat warning
  else {
    currentState="Overheat";
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER_PIN,HIGH);
   
  }
  if(currentState !=lastState){
  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.print(" C | State:");
  Serial.println(currentState);
  lastState=currentState;
  }

  delay(1000); // Read every 2 seconds
}