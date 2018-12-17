#include <dht.h>

dht DHT;
#define trigPin 10
#define echoPin 9
#define DHT11_PIN 7



void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int val;                
  double temp;
  int chk = DHT.read11(DHT11_PIN);
  temp = DHT.temperature;  
  float duration, durationAvg;
  float spdSnd;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  
  
  Serial.print(duration);
  Serial.print(" ");
  Serial.println(temp);
  delay(2000);
  }
