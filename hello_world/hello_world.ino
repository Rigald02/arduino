#include <FirmataDefines.h>
#include <FirmataConstants.h>
#include <Boards.h>
#include <Firmata.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>

// tableau 4 cases= 0 = , 1= , 2="", 3="". avec en prise possible ".", "_", "null"
// 
/*int inPin = 11;
int ledPin = 13;*/
int analogPin= A0;
/*int val = 0;
int freq;
int sensorValue;*/
int led = 3;
String message= "!...";
//char * tab;
static String tabAlphabet[] = {"a","b", "c", "d", "e", "f", "g", "h",
                                "i", "j", "k", "l", "m", "n", "o", "p", "q",
                                 "r", "s", "t", "u", "v", "w", "x", "y", "z", " "
                             };
static String tabMorse[] = {".-!!","-...", "-.-.", "-..!", ".!!!", "..-.", "--.!", "....",
                             "..!!", ".---", "-.-!", ".-..!", "--!!", "-.!!", "---!", ".--.", "--.-",
                             ".-.!", "...!", "-!!!!", "..-!", "...-", ".--!", "-..-", "-.--", "--..", "!!!!"
                             };
// dans ce tableau, ! = Null

void morseOutput(String myMessage){
  int j = 0;
  
  while (tabAlphabet[j] != " ")
  {
    if (tabAlphabet[j] == myMessage)
    {
      Serial.print(tabMorse[j]);
      break;
    }
    j++;
    if (tabAlphabet[j] == " ")
    {
      Serial.print("!!!!");
    }
  }
  
}

void morseincoming(String myMessage){
  int i = 0;

    
  while (tabMorse[i] != "!!!!") //ce n'est pas la fin de la lettre
  { 
    if (tabMorse[i] == myMessage)
    {
      Serial.print(char('a' + i)); //si i = position O, alors A est affiché, si i = 1, B est affiché, etc. Le char etant selon la position ASCII
      Serial.print(" "); //espace entre deux lettre
      break; // on sort de la boucle
    }
    i++; //incrémenter afin de check si cela corresponde a la lettre suivante, on rerentre ainsi dans la boucle.
    if (tabMorse[i] == "!!!!") //ca commence par un null
    {
      Serial.println(" "); //trou
    }
    
  }
  

 //   message = ""; //fin de la fonction, on retourne un message?
  }
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);
  pinMode(analogPin, INPUT);

  //Serial.begin(9600);

  /*for(int k = 0; k< 5; k++)
  {
    message += tab[k];
  }
  // converti tableau en un string
  */
  
  morseincoming(message);
  //morseOutput(message);
    
  //freq = 12.5;
  //initialize the digital pin as an output.
}

void loop() {
  // put your main code here, to run repeatedly:
 

  int valeur = analogRead(A0);

  if (valeur > 800)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
  
  //Serial.println(valeur);
  delay(1000);
}
