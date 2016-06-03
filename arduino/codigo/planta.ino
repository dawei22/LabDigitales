#include <NewPing.h>
#include "DHT.h"  

int pwm = 5;
int trig = 6;
int echo = 7;
int ht = 0;

float prom = 0;
int state = 0;

NewPing sonar(trig,echo,25);
DHT dht;


void setup() {
  Serial.begin(115200);
  pinMode(pwm, OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(ht, INPUT);
  dht.setup(2);
}

void loop() {
  switch (state){
    case 0:  // Medir 
      if (analogRead(ht) > 600 && sonar.ping_cm()< 16){
        state = 1;
      }
      delay(50);
      break;

    case 1: // Regar
      analogWrite(pwm, 55);
      if (analogRead(ht) < 600){
        state = 2;
      }
      delay(50);
      break;

    case 2: // Imprimir
      analogWrite(pwm,0);
      int i = 0;
      while (i < 5){
        unsigned int nivel_cm  = sonar.ping_cm();
        prom = prom + nivel_cm;
        i++;
        delay(50);
      }
    Serial.print("Ping: ");
    Serial.print(prom/5); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
    prom = 0;
    state = 0;
    break;
  }
}


