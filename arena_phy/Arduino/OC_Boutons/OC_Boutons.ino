/* Variables pour contrôler les feux*/
#include <Bounce2.h>
#include <Servo.h>

 //Passage a Niveau
Servo servomoteur;
const int broche =7;
const byte fermeture=13;
const byte ouverture=12;
Bounce bfermeture;
Bounce bouverture;

  // feu F1
const byte F1V = 3 ;
const byte F1O = 4 ;
const byte F1R = 5 ;
const byte PF1 = 9 ;
Bounce BPF1;
const unsigned long TempsAttenteFO = 1000;
unsigned long previousTime=0;

bool etat=false;
bool etatf=false;
bool etato=false;
bool orange=false;

void setup() {
 // bouton poussoir
pinMode (PF1, INPUT_PULLUP) ;
pinMode (fermeture, INPUT_PULLUP) ;
pinMode (ouverture, INPUT_PULLUP) ;

  BPF1.attach(PF1);   // la broche du bouton poussoir
  BPF1.interval(1); // l'intervalle de temps en ms
    bfermeture.attach(fermeture);   // la broche du bouton poussoir
  bfermeture.interval(1); // l'intervalle de temps en ms
      bouverture.attach(ouverture);   // la broche du bouton poussoir
  bouverture.interval(1); // l'intervalle de temps en ms
  // feu F1
  pinMode (F1V, OUTPUT) ;
  pinMode (F1O, OUTPUT) ;
  pinMode (F1R, OUTPUT) ;
  servomoteur.attach(broche);
  servomoteur.write(160);
  Serial.begin(9800);
}

void loop() {
  BPF1.update();
  bfermeture.update();
  bouverture.update();
  unsigned long currentTime=millis();
Serial.println(currentTime-previousTime);
  digitalWrite(F1V, LOW) ;
    digitalWrite(F1O, LOW) ;
    digitalWrite(F1R, HIGH) ;
  // put your main code here, to run repeatedly:
  if (etat)
  { 
    digitalWrite(F1V, HIGH) ;
    digitalWrite(F1O, LOW) ;
    digitalWrite(F1R, LOW) ;
  }
  else 
  {
    if(currentTime-previousTime<=TempsAttenteFO)
    {
       digitalWrite(F1V, LOW) ;
        digitalWrite(F1O, HIGH) ;
      digitalWrite(F1R, LOW) ;
    }
    else
    {
      digitalWrite(F1O, LOW) ;
      digitalWrite(F1V, LOW) ;
      digitalWrite(F1R, HIGH) ;
    } 

  }
  //lecture de l'état du bouton et stockage dans etatBouton
  bool etatPinBouton = BPF1.read();
  bool etatvert=(digitalRead(F1V)==LOW);
  if(etatvert)
  {
    orange=true;
  }
  else
  {
    orange=false;
  }
  //test des conditions
  if (!etatPinBouton)//si bouton appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
  {
    if (etat) //si rouge on passe à vert
    {
      etat=false; //on le passe à vert
    }
    else //sinon on passe à rouge en passant par orange
    {
      if(orange)
      {
           previousTime=millis();
      }
      else
      {
        Serial.print("pas de orange");
      }

      etat=true; //on le passe à 1
    }
  }
 // verfication du bon servomoteur
  if(etatf)
  {
    
      if(servomoteur.read()==160)//si ouvert
      {
         //  Fermeture passage à niveau : faire bouger le bras de 90°
        for (int position = 160; position >= 70 ; position--) 
        {
          servomoteur.write(position);
          delay(15);
        }
      }
  }
  
    bool etatBoutonS=bfermeture.read();
 if (!etatBoutonS)//si bouton appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
  {
    if (etatf) //si etatAllumage à 1
    {
      etatf=false; //on le passe à 0
    }
    else //sinon
    {
      etatf=true; //on le passe à 1
    }
  }
 if(etato)
  {
    
      if(servomoteur.read()==70)//si ouvert
      {
         //  Fermeture passage à niveau : faire bouger le bras de 90°
        for (int position = 70; position <= 160 ; position++) 
        {
          servomoteur.write(position);
          delay(15);
        }
      }
  }
    bool etatBoutonO=bouverture.read();
 if (!etatBoutonO)//si bouton appuyé (donc le pin indique 0 car il est en mode INPUT_PULLUP)
  {
    if (etato) //si etatAllumage à 1
    {
      etato=false; //on le passe à 0
      etatf=false;
    }
    else //sinon
    {
      etato=true; //on le passe à 1
    }
  }
}
