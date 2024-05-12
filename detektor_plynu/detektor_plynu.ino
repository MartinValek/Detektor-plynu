#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

const char* ssid = "WiFiSSID"; //Zadejte název wifi síte
const char* password = "WiFiPassword"; //Zadejte heslo 
const char* serverUrl = "webserver"; 
const int gasPin = "váš pin"; //Zadejte váš pin
const int threshold = 500; 

WebServer server(80);

void setup() 
{
  Serial.begin(9600);
  pinMode(gasPin, INPUT);
  connectToWiFi();

  server.on("/", web);
  server.begin();
}

void loop() 
{
  server.handleClient();

  int gasValue = analogRead(gasPin);
  Serial.print("Hodnota plynu: ");
  Serial.println(gasValue);

  if (gasValue > threshold) 
  {
    Serial.println("Plyn detekován!");
    sendDataToServer(gasValue);
  }

  delay(1000);
}
void web() 
{
  String html = "<!DOCTYPE html><html><head><title>Detektor Plynu</title>";
  html += "<style>body {font-family: Arial, sans-serif; margin: 0; padding: 20px;}";
  html += "h1 {color: #333;} p {font-size: 18px;} .container {max-width: 600px; margin: 0 auto;}";
  html += ".gas-value {font-size: 24px; color: #ff6347;} .alert {color: #ff6347;}</style></head>";
  html += "<body><div class='container'><h1>Detektor Plynu</h1>";
  html += "<p><strong>Úroveň plynu:</strong> <span class='gas-value'>";
  html += gasValue;
  html += "</span></p>";

  if (gasValue > threshold) ´
  {
    html += "<p class='alert'>Plyn detekován!</p>";
  }

  html += "</div></body></html>";
  server.send(200, "text/html", html);
}

void WiFi_pripojeni() 
{
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

void odesilanidat (int gasValue) 
{
  HTTPClient http;

  String postData = "gas_value=" + String(gasValue); // Příprava odesílaní dat

  Serial.println("Posílání dat na server...");
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(postData);
  http.end();

  if (httpResponseCode == 200)
  {
    Serial.println("Data úspěšně odeslána na server.");
  } else 
  {
    Serial.println("Chyba při odesílání dat na server.");
  }
}

