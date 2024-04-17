# Nadpis
## Podnadpis
**tučně**

*kurziva*

> Poznamka


```C++
void loop() 
{
  int hodnotaP = analogRead(gasPin);
  Serial.print("hodnota plynu: ");
  Serial.println(hodnotaP);

  if (hodnotaP > threshold) 
  {
    Serial.println("Plyn detekován!");
    DataToServer(hodnotaP);
  }

  delay(1000);
}

void connectToWiFi() {
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


  String jsonData = "{\"hodnotaP\": " + String(hodnotaP) + "}";

  Serial.println("Posílání dat na server...");

  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");


  http.end();
}
