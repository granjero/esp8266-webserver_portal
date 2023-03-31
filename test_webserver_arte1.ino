/*
El pescador hace de la pacienciencia un arma.
También aprovecha la idiotez ajena.
*/

// Includes
#include <ESP8266WiFi.h>                        // https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

String HTML_0 = "<!DOCTYPE html><html lang='es'><head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>-jm-</title><style>html,body {margin: 0;padding: 0;display: flex;justify-content: center;align-items: center;overflow: hidden;}</style></head><body><h1>";
String HTML_1 = "</h1></body></html>";


DNSServer dnsServer;                            // Inicia Servidor DNS (no?)
ESP8266WebServer server(80);                    // Inicia Servidor web en el puerto 80

void setup() {
  Serial.begin(115200);                                   // Inicia Puerto Serie 115200 baudios
  Serial.println(F(""));
  Serial.println(F("TEST"));
  Serial.println(F(""));
  
  IPAddress local_IP(192,168,4,1);
  IPAddress gateway(192,168,4,1);
  IPAddress subnet(255,255,255,0);
  
  WiFi.mode(WIFI_AP);                                     // Configura el modudulo como AP
  WiFi.persistent(true);
  WiFi.disconnect();
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP("Arte");
  Serial.println(F("Wifi Iniciado."));

  dnsServer.start(53, "*", local_IP);

  // replay to all requests with same HTML
  server.onNotFound([]() { handleRoot(); } );

  server.on("/", handleRoot);                               // Configura el servidor y las paginas disponibles
  
  server.begin();                                           // Inicia el Servidor
  Serial.println(F("Servidor Iniciado."));

}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();                                    //Handle client requests
}


/*
PAGINAS
*/

// Root
void handleRoot()
{
  char characters[] = { '/', '\\', '|', '-' };
  String randomString = "";

  for (int i = 0; i < 1000; i++) {
    // generate a random index within the range of the character array
    int randomIndex = random(4);
    // select the character at the random index and add it to the random string
    randomString += characters[randomIndex];
    randomString += " ";
  }


  
    String pagina = "";
    pagina += HTML_0;
    pagina += randomString;
    pagina += HTML_1;
  server.send(200, "text/html", pagina); //Send web page
  Serial.println(F("root"));
}
