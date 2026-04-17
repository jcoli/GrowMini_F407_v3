/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>

#include "io_defines.h"
#include "defines.h"
#include "pitches.h"


void play_sleep_sound();
void play_start_sound();
void play_door_sound();
void play_finish_sound();
void play_star_wars_sound();

void play_sleep_sound(){
  Serial.println("sound1"); 
  int melody[] = { NOTE_D6, NOTE_D6};
  int noteDurations[] = { 8, 8}; 
  for (int thisNote = 0; thisNote < 2; thisNote++) {   // ergodic all notes
      int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
      tone(BUZZER_PIN , melody[thisNote], noteDuration);   // let speaker sonds
      int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
      delay(pauseBetweenNotes);                          // delay for the while
      noTone(BUZZER_PIN );                                 // stop the tone playing:
  }
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("sound2"); 

}

void play_finish_sound(){
    int melody[] = { NOTE_C7, NOTE_C6, NOTE_C7,NOTE_C6,NOTE_C7};
        int noteDurations[] = { 8, 8, 4, 8, 4}; 
        for (int thisNote = 0; thisNote < 5; thisNote++) {   // ergodic all notes
            int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
            tone(BUZZER_PIN , melody[thisNote], noteDuration);   // let speaker sonds
            int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
            delay(pauseBetweenNotes);                          // delay for the while
            noTone(BUZZER_PIN );                                 // stop the tone playing:
        }
        digitalWrite(BUZZER_PIN, LOW);
}

void play_door_sound(){ 
  Serial.println("sound2"); 
  int melody[] = { NOTE_D6, NOTE_D6};
  int noteDurations[] = { 8, 8}; 
  for (int thisNote = 0; thisNote < 2; thisNote++) {   // ergodic all notes
      int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
      tone(BUZZER_PIN , melody[thisNote], noteDuration);   // let speaker sonds
      int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
      delay(pauseBetweenNotes);                          // delay for the while
      noTone(BUZZER_PIN );                                 // stop the tone playing:
  }
  digitalWrite(BUZZER_PIN, LOW);

}

void play_start_sound(){
  Serial.println("sound3"); 
  int melody[] = { NOTE_D6, NOTE_D6};
  int noteDurations[] = { 8, 8}; 
  for (int thisNote = 0; thisNote < 2; thisNote++) {   // ergodic all notes
      int noteDuration = 1000 / noteDurations[thisNote]; // calculate the note duration
      tone(BUZZER_PIN , melody[thisNote], noteDuration);   // let speaker sonds
      int pauseBetweenNotes = noteDuration * 1.30;       // set a minimum time between notes
      delay(pauseBetweenNotes);                          // delay for the while
      noTone(BUZZER_PIN );                                 // stop the tone playing:
  }
  digitalWrite(BUZZER_PIN, LOW);
}

void play_star_wars_sound(){
  Serial.println("sound3"); 
  int melody[] = { 
        NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,//1
        NOTE_F5,2, NOTE_C6,2,
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
        NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,8, NOTE_C5,8, NOTE_C5,8,
        NOTE_F5,2, NOTE_C6,2,
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
        
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, //8  
        NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,-8, NOTE_C5,16, 
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C5,-8, NOTE_C5,16,
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        
        NOTE_C6,-8, NOTE_G5,16, NOTE_G5,2, 0,8, NOTE_C5,8,//13
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C6,-8, NOTE_C6,16,
        NOTE_F6,4, NOTE_DS6,8, NOTE_CS6,4, NOTE_C6,8, NOTE_AS5,4, NOTE_GS5,8, NOTE_G5,4, NOTE_F5,8,
        NOTE_C6,1
  };

        int tempo = 108;
      
  
        int notes = sizeof(melody) / sizeof(melody[0]) / 2;

        // this calculates the duration of a whole note in ms
        int wholenote = (60000 * 4) / tempo;

        int divider = 0;
        int noteDuration = 0;



    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      
    // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER_PIN, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(BUZZER_PIN);
  }
  
}