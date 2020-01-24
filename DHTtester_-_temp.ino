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
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
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

  float resultMediane = mediane(tenLastValues, 10);
    Serial.println(resultMoyenne);
    Serial.print("MEDIANE: ");
  
  
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

//moyenne
void moyenne() {

float acc = 0;

for (int x =0; x < sizeof(tab)/4 ; x++) 
  {
    acc += tab[x]; 
  }
  Serial.print("Moyenne :");  
  Serial.println(acc/(sizeof(tab)/4));  
} 

//mediane
float mediane(float t[], int const size) {
  float f[size];
  for (int i = 0; i < size; ++i) {
    f[i] = t[i];
  }
  tri_a_bulle(f, size);
  return f[5];
}


void tri_a_bulle(float t[], int const size) {
  bool en_desordre = true;
  for (int i = 0; i < size && en_desordre; ++i) {
    en_desordre = false;
    for (int j = 1; j < size - i; ++j) {
      if (t[j-1] > t[j]) {
        float temp = t[j-1];
        t[j-1] = t[j];
        t[j] = temp;
        en_desordre = true;
      }
    }
  }


