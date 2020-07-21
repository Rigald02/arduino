#include <FirmataDefines.h>
#include <FirmataConstants.h>
#include <Boards.h>
#include <Firmata.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>
#include <ESP8266WiFi.h>


const char* ssid = "insérernom";
const char* password = "insérerpassword";
  
void setup() {

  Serial.begin(9600);
  delay(10);
 
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Name");
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
