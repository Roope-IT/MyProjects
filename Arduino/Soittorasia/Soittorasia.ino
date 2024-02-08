//määritellään nimet PIN numeroille
const int moottori = A2;
const int piipperi = 11;
const int nappi = 8;

//muuttujat 
int muuttuja = 0;

//kirjastot

#include <Servo.h>
#include "Pitches.h"

//esitellään servo-olio
Servo spinneri;

//kappaleiden nuotit ja kestot

int melody[] = {
  NOTE_G4, NOTE_C5, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, 
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, 
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_G4, 
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, 
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_C4, 
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_B4, NOTE_C5, NOTE_D5, 
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_G4, NOTE_B4, NOTE_C5, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_C5, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_A4, NOTE_A4,
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_C4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
  };

int noteDurations[] = {
  8, 4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 8, 8, 
  4, 8, 8, 4, 8, 8, 4, 8, 8, 2,
  4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 8, 8, 
  4, 6, 16, 4, 6, 16, 
  4, 6, 16, 8, 8, 8, 8, 
  2, 8, 8, 8, 8, 3, 8, 8, 8, 8, 8,
  2, 8, 8, 8, 8, 3, 8, 8, 8, 8, 8,
  4, 6, 16, 4, 6, 16, 4, 8, 8, 2,
  2, 8, 8, 8, 8, 3, 8, 2,
  2, 8, 8, 8, 8, 3, 8, 2,
  4, 6, 16, 4, 4, 2, 4, 4, 1
};

int melody2[]= {NOTE_D4, NOTE_AS4, NOTE_G4, NOTE_G4,
               NOTE_D4, NOTE_D4, NOTE_A4, NOTE_F4,
               NOTE_F4, NOTE_D4, NOTE_D4, NOTE_A4,
               NOTE_F4, NOTE_F4, NOTE_CS3, NOTE_CS3,
               NOTE_E4, NOTE_E4, NOTE_F4, NOTE_E4,
               NOTE_D4, NOTE_AS4, NOTE_G4, NOTE_G4,
               NOTE_D4, NOTE_D4, NOTE_A4, NOTE_F4,
               NOTE_F4, NOTE_D4, NOTE_D4, NOTE_A4,
               NOTE_F4, NOTE_F4, NOTE_CS3, NOTE_CS3,
               NOTE_E4, NOTE_E4, NOTE_F4, NOTE_E4
};

int noteDurations2[]= {10, 10, 10, 18, 10, 18, 10, 10, 18,
                      10, 18, 10, 10, 18, 10, 10, 10, 18,
                      18, 18,10, 10, 10, 18, 10, 18, 10, 10, 18,
                      10, 18, 10, 10, 18, 10, 10, 10, 18,
                      18, 18
};

int melody3[]={NOTE_FS4, NOTE_CS5, NOTE_AS4, NOTE_AS4,
              NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_B4,
              NOTE_AS4, NOTE_AS4, NOTE_GS4, NOTE_GS4,
              NOTE_FS4, NOTE_FS4, NOTE_CS5, NOTE_AS4,
              NOTE_AS4, NOTE_GS4, NOTE_FS4, NOTE_FS4,
              NOTE_DS4, NOTE_CS3
  
};


int noteDurations3[]={5, 10, 10, 5, 10, 10, 10, 5, 10, 10, 10,
                     10, 5, 10, 10, 10, 5, 10, 10, 10, 5, 4
  
};
void setup() {
  // put your setup code here, to run once:
  //PINien määrittely
  pinMode(moottori, OUTPUT);
  pinMode(piipperi, OUTPUT);
  pinMode(nappi, INPUT);

  //liitetään moottori-pin servoon
  spinneri.attach(moottori);

  //otetaan tulostus käyttöön
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //toistolause alkaa napin painalluksesta
  if (digitalRead(nappi) == HIGH){
    Serial.println("Nappi painettu");
    delay(500);
    muuttuja = random(0, 4);
    Serial.println("arvonta suoritettu");
    delay(50);

    
    if (muuttuja == 1){
      Serial.println("USSR theme");
      spinneri.write(0);
      Serial.println("Asento nollakohdassa");
      delay(500);
      ussr();
      Serial.println("DONE");
      
    } else if (muuttuja == 2){
      Serial.println("Crab rave");
      spinneri.write(84);
      Serial.println("Asento keskikohta");
      delay(500);
      crabRave();
      Serial.println("DONE");
      
    } else if (muuttuja == 3){
      Serial.println("All star theme");
      spinneri.write(172);
      Serial.println("Asento toisessa aaripaassa");
      delay(500);
      allStar();
      Serial.println("DONE");
      
    }
  }

}

//metodi USSR:lle
void ussr(){
  Serial.println("Kappale alkaa");
  for (int thisNote = 0; thisNote < sizeof(melody) / 2; thisNote++) {
    int noteDuration = 2000 / noteDurations[thisNote];
    Serial.println("Tone");
    tone(piipperi, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(piipperi);
    }
}

//metodi Crab Ravelle
void crabRave(){
  Serial.println("Kappale alkaa");
  for (int thisNote2 = 0; thisNote2 < sizeof(melody2) / 2; thisNote2++) {
    int noteDuration2 = 2000 / noteDurations2[thisNote2];
    Serial.println("Tone");
    tone(piipperi, melody2[thisNote2], noteDuration2);
    int pauseBetweenNotes2 = noteDuration2 * 1.30;
    delay(pauseBetweenNotes2);
    noTone(piipperi);
    }
}

//metodi All Starille
void allStar(){
  Serial.println("Kappale alkaa");
  for (int thisNote3 = 0; thisNote3 < sizeof(melody3) / 2; thisNote3++) {
    int noteDuration3 = 2000 / noteDurations3[thisNote3];
    Serial.println("Tone");
    tone(piipperi, melody3[thisNote3], noteDuration3);
    int pauseBetweenNotes3 = noteDuration3 * 1.30;
    delay(pauseBetweenNotes3);
    noTone(piipperi);
    }
}
