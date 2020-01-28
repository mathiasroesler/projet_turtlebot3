#include <Servo.h>
// Initialisation des variables

// feu F1
const byte F1V = 3 ;
const byte F1O = 4 ;
const byte F1R = 5 ;
// tableau des couleurs du feu
int F1C[] = {F1V, F1O, F1R};

Servo servomoteur;
const int broche =7;

// Ordre de la Raspberry
int messageFeu = 0;
int messagePan = 0;
int message = 0;
// Initialisation des lignes 4 à 9 en sortie
void setup () 
{              
  // feu F1
  pinMode (F1V, OUTPUT) ;
  pinMode (F1O, OUTPUT) ;
  pinMode (F1R, OUTPUT) ;

  // servomoteur
  servomoteur.attach(broche);
  servomoteur.write(160);
  Serial.begin (9600);
}
     
// Fonction loop
void loop () 
{ 
 if ( Serial.available()>0 ) 
 {
    // on lit le message envoyé par la raspberry
      message = Serial.read()-'0';
    // destinataire
    if (message == 1 || message == 2)
    {
       messageFeu=message;
    }
    if (message == 3 || message == 4)
    {
      messagePan=message;
    }
    //gestion du feu
    if (messageFeu == 2) 
    {
      //feu rouge en passant par orange pendant 5 secondes
      digitalWrite(F1C[0], LOW);
      digitalWrite(F1C[1], HIGH);
      digitalWrite(F1C[2], LOW);
      delay(1000);
      digitalWrite(F1C[0], LOW);
      digitalWrite(F1C[1], LOW);
      digitalWrite(F1C[2], HIGH);
    }
    else
    {
      if (messageFeu == 1) 
      {
        //On allume le feu Vert
        digitalWrite(F1C[0], HIGH);
        digitalWrite(F1C[1], LOW);
        digitalWrite(F1C[2], LOW);
      }
    }
    //gestion du panneau
    if(messagePan==3)
    {
         //  Fermeture passage à niveau : faire bouger le bras de 90°
        if(servomoteur.read()==160)
        {
        for (int position = 160; position >= 70 ; position--) 
          {
            servomoteur.write(position);
            delay(15);
          }
        }
    }
    else
    {
      if(messagePan==4)
      {
         //  Fermeture passage à niveau : faire bouger le bras de 90°
        if(servomoteur.read()==70)
        {
          for (int position = 70; position <=160 ; position++) 
          {
            servomoteur.write(position);
            delay(15);
          }
        }
      }
    }
     
 }
}
