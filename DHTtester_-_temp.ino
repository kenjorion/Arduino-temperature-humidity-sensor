#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  
  dht.begin();
}

int i = 0;
int j = 0;
float tab[10];
float medtab[11];
int med_length = sizeof(medtab) / sizeof(medtab[0]);
qsort(medtab, lt_length, sizeof(medtab[0]), sort_desc);

void loop() {
  // Wait a few seconds between measurements.
   if ( sizeof(tab)/4 < 10){
    delay(500);
   } else {
      delay(500);
   }

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  tab[i] = t;
  i++;
  if (i == 10) 
    i =0;
  moyenne();

  medtab[j] = t; 
  j++; 
  mediane();
  
  
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}


void moyenne() {

float acc = 0;

for (int x =0; x < sizeof(tab)/4 ; x++) 
  {
    acc += tab[x]; 
  }
  Serial.print("Moyenne :");  
  Serial.println(acc/(sizeof(tab)/4));  
} 

void mediane() {

float acc = 0;

for (int x =0; x < 11 ; x++) 
  {
    acc += tab[x]; 
  }
  Serial.print("Mediane :");  
  Serial.println(acc/(sizeof(tab)/4));  
}

int sort_desc(const void *cmp1, const void *cmp2)
{
     // Need to cast the void * to int *
     int a = *((int *)cmp1);
     int b = *((int *)cmp2);
     // The comparison
     return a > b ? -1 : (a < b ? 1 : 0);
     // A simpler, probably faster way:
     //return b - a;
}


