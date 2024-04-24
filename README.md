# Nadpis
## Podnadpis
**tučně**

*kurziva*


https://coggle.it/diagram/ZhYydTc90NTCtGFO/t/varovn%C3%BD-syst%C3%A9m-p%C5%99i-%C3%BAniku-plynu-v-dole-question


> Poznamka

------------------

# Dektektor plynu

Používal by se převážně v dolech, kde by pomáhal horníkům při těžení.

Měli by ho u sebe a jakmile by detektor zachytil, že koncentrace plynu je moc vysoká, spustil by alarm.

#Kód

```C++
#include <WiFi.h>
#include <HTTPClient.h>


//Zadání parametrů sítě
const char* ssid = "WiFiSSID";
const char* password = "WiFiPassword";
 
const int gasPin = A0;
//Můžete zadat popřípadě jinou hodnotu 
const int threshold = 500; 

void setup() 
{
  Serial.begin(9600);
  pinMode(gasPin, INPUT);
  connectToWiFi();
}

void loop() 
{
  //Vypisuje hodnotu plynu podle zaznamenaných hodnot
  int hodnotaP = analogRead(gasPin);
  Serial.print("hodnota plynu: ");
  Serial.println(hodnotaP);

  //Při přesažení nastavenou práhovou hodnotu odešle se tato hodnota na server
  if (hodnotaP > threshold) 
  {
    Serial.println("Plyn detekován!");
    DataToServer(hodnotaP);
  }

  delay(1000);
}

void connectToWiFi() {
  //Připojení k WiFi
  Serial.println("Připojování k WiFi....");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Připojování k WiFi...");
  }

  Serial.println("Připojeno k WiFi");
  Serial.print("IP Adresa: ");
  Serial.println(WiFi.localIP());
}

void DataToServer(int hodnotaP) 
{
  HTTPClient http;

  //Odesílaní aktuální hodnoty plynu na server
  String jsonData = "{\"hodnotaP\": " + String(hodnotaP) + "}";

  Serial.println("Posílání dat na server...");

  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");


  http.end();
}
