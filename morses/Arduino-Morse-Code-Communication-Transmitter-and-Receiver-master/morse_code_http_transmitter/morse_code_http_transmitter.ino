
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

int laser = 2;
char texte[58]; //message a envoyer
char texteAenvoyer[4];
static String tabAlphabet[] = {"a","b", "c", "d", "e", "f", "g", "h",
                                "i", "j", "k", "l", "m", "n", "o", "p", "q",
                                 "r", "s", "t", "u", "v", "w", "x", "y", "z", " "
                             };
static String tabMorse[] = {"._!!","_...", "_._.", "_..!", ".!!!", ".._.", "__.!", "....",
                             "..!!", ".___", "_._!", "._..", "__!!", "_.!!", "___!", ".__.", "__._",
                             "._.!", "...!", "_!!!", ".._!", "..._", ".__!", "_.._", "_.__", "__..", "!!!!"
                             };
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("AndroidAP", "ynlu4844");

  
 pinMode(laser,OUTPUT);
 digitalWrite(laser,LOW);
 delay(6000);
}
void loop() {
  // put your main code here, to run repeatedly:


    String payload;
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://jigsaw.w3.org/HTTP/connection.html")) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
   
   String phrase;

   for(int i = 225; i < 283; i++)
   {
     phrase += payload.charAt(i);
   }
   phrase.toCharArray(texte, 59);
   Serial.println(phrase);
   
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }


  
int i; 
int y;
String texteMorse;
int taille=((sizeof(texte))/(sizeof(char)));
 
for (i=0;i<taille;i++)
{
  texteMorse=morseOutput(texte[i]);
 
  for(y=0;y<4;y++)
  {
  texteAenvoyer[y]=texteMorse.charAt(y);
  envoi(texteAenvoyer[y]);
  }
}
delay(1000000); //fin de transmission
}
void envoi(char carac)
{
  int i;
  Serial.println("fonction envoi");
    if(carac=='.')
    {
       digitalWrite(laser,HIGH);
       Serial.println('.');
       delay(300);
       digitalWrite(laser,LOW);
       delay(200);
    }
    if(carac=='_')
    {
       digitalWrite(laser,HIGH);
       Serial.println('_');
       delay(700);
       digitalWrite(laser,LOW);
       delay(200);
    }
    if(carac=='!')
    {
       digitalWrite(laser,LOW);
       Serial.println('!');
       delay(1000);
    }
 }
String morseOutput(char myMessage){
  int j = 0;
  
  while (tabAlphabet[j] != " ")
  {
    if (tabAlphabet[j].charAt(0) == myMessage)
    {
      return tabMorse[j];
    }
    j++;
    if (tabAlphabet[j] == " ")
    {
      //Serial.print("!!!!");
      return("!!!!");
    }
  }
}
