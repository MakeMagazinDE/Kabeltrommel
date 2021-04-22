#include <ESP8266WiFi.h>
#include <PZEM004Tv30.h>
const char* ssid = "hbvdr";
const char* password = "babybaer";
WiFiServer server(80);
PZEM004Tv30 pzem(D1,D2);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));
  // Start the server
  server.begin();
  Serial.println(F("Server started"));
  // Print the IP address
  Serial.println(WiFi.localIP());
}
void loop() {
  WiFiClient client = server.available();
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();
  client.print("<head><title>Make-Kabeltrommel</title><meta http-equiv='refresh' content='5' /></head>");
  client.print("<img src='http://www.heise.de/make/icons/make_logo.png' alt='Make:' height=10%><h1>Kabeltrommel </h1><br>");
  client.print("<table>");
  client.print("<tr><td><b>Spannung:</b> </td><td>"); client.print(voltage); client.print("V<br></td></tr>");
  client.print("<tr><td><b>Strom:</b> </td><td>"); client.print(current); client.print("A<br></td></tr>");
  client.print("<tr><td><b>Leistung:</b> </td><td>"); client.print(power); client.print("W<br></td></tr>");
  client.print("<tr><td><b>Arbeit:</b> </td><td>"); client.print(energy); client.print("kWh<br></td></tr>");
  client.print("<tr><td><b>Frequenz:</b> </td><td>"); client.print(frequency); client.print("Hz<br></td></tr>");
  client.print("<tr><td><b>Leistungsfaktor:</b> </td><td>"); client.print(pf); client.print("<br></td></tr>");
  client.print("</table>");
}
