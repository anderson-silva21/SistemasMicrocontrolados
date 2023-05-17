#include <LedControl.h>

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

int tempoTetris = 144; 
int tempoGodFather = 80;
int tempoMario = 200;
int tempoStarWars = 120;

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
 
LedControl lc = LedControl(12, 11, 10, 2); // (dataPin, clockPin, csPin, totalDevices)
 
int lc0[] = {0, 0, 0, 0, 0, 0, 0, 0};
int lc1[] = {0, 0, 0, 0, 0, 0, 0, 0};
long active[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
long screen[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int tmpCol = 0;
 
 
int figura = 0;
int figuraNext = 0;
int fromLeft = 0;
int fromRight = 0;
int angle = 0;
int colCheck = 0;
int moveCheck = 0;
int score = 0;
int started = 0;
int lcRows = 16;
int lcCols = 8;
int allLines = 0;
int currLines = 0;
int brickDelay = 0;
int defDelay = 500;
int level = 0;
 
boolean sound = true;
//Pinos
 
int rotate_button = 2;
int left_button   = 3;
int down_button   = 4;
int right_button  = 5;
int start_button  = 6;
int speaker_pin   = 7;
int sound_button  = 8;
 
byte X[8] =
{
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000
};
 
byte O[8] =
{
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000,
  0b00000
};
 
byte L[8] =
{
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11111,
  0b11111,
  0b00000
};
 
byte J[8] =
{
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b11111,
  0b11111,
  0b00000
};
 
byte T[8] =
{
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b01110,
  0b01110,
  0b00000,
  0b00000
};
 
byte I[8] =
{
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b01100,
  0b00000
};
 
byte Z[8] =
{
  0b00000,
  0b00000,
  0b11110,
  0b11110,
  0b01111,
  0b01111,
  0b00000,
  0b00000
};
 
byte S[8] =
{
  0b00000,
  0b00000,
  0b01111,
  0b01111,
  0b11110,
  0b11110,
  0b00000,
  0b00000
};

int melodyStarWars[] = {
  
  // Dart Vader theme (Imperial March) - Star wars 
  // Score available at https://musescore.com/user/202909/scores/1141521
  // The tenor saxophone part was used
  
  NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
  NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
  NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,

  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
  NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,

  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
};


int melodyTetris[] = {

  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,
  

  NOTE_E5,2,  NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,2,   NOTE_A4,2,
  NOTE_GS4,2,  NOTE_B4,4,  REST,8, 
  NOTE_E5,2,   NOTE_C5,2,
  NOTE_D5,2,   NOTE_B4,2,
  NOTE_C5,4,   NOTE_E5,4,  NOTE_A5,2,
  NOTE_GS5,2,

};

int melodyMario[] = {

  // Super Mario Bros theme
  // Score available at https://musescore.com/user/2123/scores/2145
  // Theme by Koji Kondo
  
  
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
  NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
  REST,1, 
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
  
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
  REST,1,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  
  //game over sound
  NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
  NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
  NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  

};

int melodyGodFather[] = {

  // The Godfather theme
  // Score available at https://musescore.com/user/35463/scores/55160

  REST, 4, REST, 8, REST, 8, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8, //1
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8,
  NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,
  
  NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8, //5
  NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
  NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8, 
  NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,

  NOTE_A4, 2, REST,8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8, //9
  NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, 
  NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
  NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8, 
   
  NOTE_E4, 2, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8, //13

  //repeats from 2
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8, //2
  NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,
  
  NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8, //5
  NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
  NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8, 
  NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,

  NOTE_A4, 2, REST,8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8, //9
  NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, 
  NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
  NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8, 
   
  NOTE_E4, 2 //13
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notesGodFather = sizeof(melodyGodFather) / sizeof(melodyGodFather[0]) / 2;
int notesMario = sizeof(melodyMario) / sizeof(melodyMario[0]) / 2;
int notesTetris = sizeof(melodyTetris) / sizeof(melodyTetris[0]) / 2;
int notesStarWars = sizeof(melodyStarWars) / sizeof(melodyStarWars[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenoteGodFather = (60000 * 4) / tempoGodFather;
int wholenoteMario = (60000 * 4) / tempoMario;
int wholenoteTetris = (60000 * 4) / tempoTetris;
int wholenoteStarWars = (60000 * 4) / tempoStarWars;

int divider = 0, noteDuration = 0;
 
//Nuty
int length = 99;
char notes[] = "EbCDCbaaCEDCbbCDECaa DFAGFEECEDCbbCDECaa EbCDCbaaCEDCbbCDECaa DFAGFEECEDCbbCDECaa ECDbCab ECDbCEAJ ";
int beats[] =      // Som
{
  2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 4, 2,
  2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 4, 1,
  2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 4, 2,
  2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 4, 1,
  5, 5, 5, 5, 5, 5, 7, 2, 5, 5, 5, 5, 2, 2, 5, 5, 3
};
int tempo = 128;        // Tempo
 
 
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speaker_pin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speaker_pin, LOW);
    delayMicroseconds(tone);
  }
}

void playStarWars(){
  for (int thisNote = 0; thisNote < notesStarWars * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melodyStarWars[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenoteStarWars) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenoteStarWars) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(speaker_pin, melodyStarWars[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(speaker_pin);
  }
}

void playTetris(){
  for (int thisNote = 0; thisNote < notesTetris * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melodyTetris[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenoteTetris) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenoteTetris) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(speaker_pin, melodyTetris[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(speaker_pin);
  }
} 

void playMario(){
  for (int thisNote = 0; thisNote < notesMario * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melodyMario[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenoteMario) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenoteMario) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(speaker_pin, melodyMario[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(speaker_pin);
  }
} 

void playGodFather(){
  for (int thisNote = 0; thisNote < notesGodFather * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melodyGodFather[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenoteGodFather) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenoteGodFather) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(speaker_pin, melodyMario[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(speaker_pin);
  }
} 


 
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' , 'D', 'E', 'F', 'G', 'J', 'A', 'B'};
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 850, 760, 716, 637, 603, 568, 507 };
 
  for (int i = 0; i < 14; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
 
 
void updateColumn(int colnum)
{
    lc0[colnum] = active[colnum] >> (lcRows / 2);
    lc1[colnum] = active[colnum];
    lc.setColumn(0,colnum,(screen[colnum] >> (lcRows / 2)) | lc0[colnum]);
    lc.setColumn(1,colnum,screen[colnum] | lc1[colnum]);
}
 
 
 
void buttonDelay(int bdelay)
{
    if(brickDelay > bdelay)
    {
        brickDelay -= bdelay;
    }
    delay(bdelay);
}
 
 
void splashScreen()
{
     int up[] =
     {
         B11101110,   //   o o o   o o o
         B01001000,   //     o     o
         B01001100,   //     o     o o
         B01001000,   //     o     o
         B01001110,   //     o     o o o
         B00000000,   //
         B11101110,   //   o o o   o o o
         B01001010    //     o     o   o
     };
 
     int down[] =
     {
         B01001100,   //     o     o o
         B01001010,   //     o     o   o
         B01001001,   //     o     o     o
         B00000000,   //
         B01000111,   //     o       o o o
         B01000100,   //     o       o
         B01000010,   //     o         o
         B01001110    //     o     o o o
     };
 
     for(int rownum = 0; rownum < 8; rownum++)
     {
         lc.setRow(0,rownum,up[rownum]);
         lc.setRow(1,rownum,down[rownum]);
     }
}
 
 
void setup() {
  pinMode(speaker_pin,  OUTPUT);
  pinMode(rotate_button,INPUT_PULLUP);
  pinMode(down_button,  INPUT_PULLUP);
  pinMode(right_button, INPUT_PULLUP);
  pinMode(left_button,  INPUT_PULLUP);
  pinMode(start_button, INPUT_PULLUP);
  pinMode(sound_button, INPUT_PULLUP);
  
 
  lc.shutdown(0,false);
  lc.shutdown(1,false);
 
  lc.setIntensity(0,5);
  lc.setIntensity(1,5);
 
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  Serial.begin(9600);
 
  randomSeed(analogRead(0));
}
 
 
//LOOP
void loop()
{
  
 
 
 if(started == 0)
 {
     splashScreen();
 
     for (int i = 0; i < length; i++)
     {
 
 if(digitalRead(sound_button) == LOW)
 {
  sound =! sound;
  delay(300);
  }
 
         if(digitalRead(start_button) == LOW)
         {
             started = 1;
             break;
         }
         if (notes[i] == ' ')
         {
             delay(beats[i] * tempo);   //Pausa
         }
         else
         {
          if (sound == 1){
             //playNote(notes[i], beats[i] * tempo);
             playGodFather();
          }
          else
          {
             digitalWrite(speaker_pin,LOW);
            }
         }
 
 
        delay(tempo / 2);
     }
 }
 
 
 
 else
 {
 
     lc.clearDisplay(0);
     lc.clearDisplay(1);
     memset(lc0, 0, sizeof(lc0));
     memset(lc1, 0, sizeof(lc1));
     memset(active, 0, sizeof(active));
     memset(screen, 0, sizeof(screen));
     tmpCol = 0;
 
     while(started == 1)
     {

         if(allLines < 100)
         {
             level = 0;              //Level 0
         }
         else if(allLines < 200)
         {
             level = 1;              //Level 1
         }
         else if(allLines < 300)
         {
             level = 2;              //Level 2
         }
         else if(allLines < 400)
         {
             level = 3;              //Level 3
         }
         else if(allLines < 500)
         {
             level = 4;              //Level 4
         }
         else
         {
             level = 5;              //Level 5
         }
 
 
         defDelay = (5 - level) * 100;
         brickDelay = defDelay;
 
 
         if(figura == 0)
         {
              figura = random(1,8);
         }
         else
         {
             figura = figuraNext;
         }
         figuraNext = random(1,8);
         angle = 0;
 
 
 
         switch(figura)
         {
             case 1:
             //"O"
                 active[3] = 131072 + 65536;
                 active[4] = 131072 + 65536;
                 fromLeft = 3;
                 fromRight = 3;
                 break;
 
             case 2:
             //"L"
                 active[3] = 262144 + 131072 + 65536;
                 active[4] = 65536;
                 fromLeft = 3;
                 fromRight = 3;
                 break;
 
             case 3:
             //"J"
                 active[3] = 65536;
                 active[4] = 262144 + 131072 + 65536;
                 fromLeft = 3;
                 fromRight = 3;
                 break;
 
             case 4:
             //"T"
                 active[2] = 131072;
                 active[3] = 131072 + 65536;
                 active[4] = 131072;
                 fromLeft = 2;
                 fromRight = 3;
                 break;
 
             case 5:
             //"I"
                 active[3] = 524288 + 262144 + 131072 + 65536;
                 fromLeft = 3;
                 fromRight = 4;
                 break;
 
             case 6:
             //"Z"
                 active[2] = 131072;
                 active[3] = 131072 + 65536;
                 active[4] = 65536;
                 fromLeft = 2;
                 fromRight = 3;
                 break;
 
             case 7:
             //"S"
                 active[2] = 65536;
                 active[3] = 131072 + 65536;
                 active[4] = 131072;
                 fromLeft = 2;
                 fromRight = 3;
                 break;
         }
 
 
 
         for(int krok = 0; krok < lcRows + 1; krok++)
         {
              
             colCheck = 0;
 
 
             for(int i = 0; i < (lcCols / 2); i++)
             {
              xValue = analogRead(VRX_PIN);
              yValue = analogRead(VRY_PIN);
              Serial.println(xValue);
              Serial.println(yValue);
                 if((yValue < 450) && (fromLeft > 0))
                 {
                     moveCheck = 0;
                     for(int colnum = fromLeft; colnum < (lcCols - fromRight); colnum++)
                     {
                         if((active[colnum] & screen[colnum - 1]) == 0)
                         {
                             moveCheck++;
                         }
                     }
 
                     if(moveCheck == (lcCols - fromLeft - fromRight))
                     {
                         for(int colnum = (fromLeft - 1); colnum < (lcCols - fromRight); colnum++)
                         {
                             if(colnum < (lcCols - 1))
                             {
                                 active[colnum] = active[colnum+1];
                             }
                             else
                             {
                                 active[colnum] = 0;
                             }
                             updateColumn(colnum);
                         }
                         fromLeft--;
                         fromRight++;
                         playNote('E', 10);
                         buttonDelay(200);
                     }
                 }
             }
 
 
 
 
 
             for(int i = 0; i < (lcCols / 2); i++)
             {
                 if((yValue > 600) && (fromRight > 0))
                 {
                     moveCheck = 0;
                     for(int colnum = fromLeft; colnum < (lcCols - fromRight); colnum++)
                     {
                         if((active[colnum] & screen[colnum + 1]) == 0)
                         {
                             moveCheck++;
                         }
                     }
 
                     if(moveCheck == (lcCols - fromLeft - fromRight))
                     {
                         for(int colnum = (lcCols - fromRight); colnum > (fromLeft - 1); colnum--)
                         {
                             if(colnum > 0)
                             {
                                 active[colnum] = active[colnum-1];
                             }
                             else
                             {
                                 active[colnum] = 0;
                             }
                             updateColumn(colnum);
                         }
                         fromLeft++;
                         fromRight--;
                         playNote('E', 10);
                         buttonDelay(200);
                     }
                 }
             }
 
 
 
             if(xValue < 450)
             {
                 brickDelay = 0;
                 playNote('b', 10);
             }
             else
             {
                 brickDelay = defDelay;
             }
 
 
 
             for(int i = 0; i < (lcCols / 2); i++)
             {
                 if(digitalRead(rotate_button) == LOW)
                 {
 
                     switch(figura)
                     {
                         case 1:
                         //"O"
                             break;
 
                         case 2:
                         //"L"
                             switch(angle)
                             {
                                 case 0:
                                 // . o .        . . .
                                 // . o .  --->  o o o
                                 // . o o        o . .
                                     if((fromLeft > 0)
                                     && (((active[fromLeft + 1] | (active[fromLeft + 1] << 1)) & screen[fromLeft - 1]) == 0))
                                     {
                                         active[fromLeft - 1] = (active[fromLeft + 1] | (active[fromLeft + 1] << 1));
                                         updateColumn(fromLeft - 1);
                                         active[fromLeft] = (active[fromLeft + 1] << 1);
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = (active[fromLeft + 1] << 1);
                                         updateColumn(fromLeft + 1);
                                         fromLeft--;
                                         angle = 1;
                                     }
                                     break;
 
                                 case 1:
                                 // . . .        o o .
                                 // o o o  --->  . o .
                                 // o . .        . o .
                                     if((((active[fromLeft + 2] << 1) & screen[fromLeft]) == 0)
                                     && ((((active[fromLeft + 1] << 1) | (active[fromLeft + 1] >> 1)) & screen[fromLeft + 1]) == 0))
                                     {
                                         active[fromLeft] = (active[fromLeft + 2] << 1);
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = active[fromLeft + 1] | (active[fromLeft + 1] << 1) | (active[fromLeft + 1] >> 1);
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = 0;
                                         updateColumn(fromLeft + 2);
                                         fromRight++;
                                         angle = 2;
                                     }
                                     break;
 
                                 case 2:
                                 // o o .        . . o
                                 // . o .  --->  o o o
                                 // . o .        . . .
                                     if((fromRight > 0)
                                     && (((active[fromLeft] >> 1) & screen[fromLeft]) == 0)
                                     && ((((active[fromLeft + 1] << 1) & active[fromLeft + 1]) & screen[fromLeft + 1]) == 0))
                                     {
                                         active[fromLeft] = (active[fromLeft] >> 1);
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = active[fromLeft];
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = ((active[fromLeft + 1] << 1) | active[fromLeft + 1]);
                                         updateColumn(fromLeft + 2);
                                         fromRight--;
                                         krok--;
                                         angle = 3;
                                     }
                                     break;
 
                                 case 3:
                                 // . . o        . o .
                                 // o o o  --->  . o .
                                 // . . .        . o o
                                     if(((((active[fromLeft] << 1) | (active[fromLeft] >> 1)) & screen[fromLeft + 1]) == 0)
                                     && (((active[fromLeft] >> 1) & screen[fromLeft + 2]) == 0)
                                     && (krok < lcRows))
                                     {
                                         active[fromLeft] = 0;
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = (active[fromLeft + 2] | (active[fromLeft + 2] >> 1));
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = ((active[fromLeft + 2] >> 1) & (active[fromLeft + 2] >> 2));
                                         updateColumn(fromLeft + 2);
                                         fromLeft++;
                                         krok++;
                                         angle = 0;
                                     }
                                     break;
                             }
                             break;
 
                         case 3:
                         //"J"
                             switch(angle)
                             {
                                 case 0:
                                 // . o .        o . .
                                 // . o .  --->  o o o
                                 // o o .        . . .
                                     if((fromRight > 0)
                                     && ((((active[fromLeft] << 2) | (active[fromLeft] << 1)) & screen[fromLeft]) == 0)
                                     && (((active[fromLeft] << 1) & screen[fromLeft + 2]) == 0))
                                     {
                                         active[fromLeft] = ((active[fromLeft] << 2) | (active[fromLeft] << 1));
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = ((active[fromLeft + 1] << 1) & (active[fromLeft + 1] >> 1));
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = active[fromLeft + 1];
                                         updateColumn(fromLeft + 2);
                                         fromRight--;
                                         krok--;
                                         angle = 1;
                                     }
                                     break;
 
                                 case 1:
                                 // o . .        . o o
                                 // o o o  --->  . o .
                                 // . . .        . o .
                                     if((krok < lcRows)
                                     && ((((active[fromLeft + 1] << 1) | (active[fromLeft + 1] >> 1)) & screen[fromLeft + 1]) == 0)
                                     && (((active[fromLeft + 2] << 1) & screen[fromLeft + 2]) == 0))
                                     {
                                         active[fromLeft] = 0;
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = (active[fromLeft + 1] | (active[fromLeft + 1] << 1) | (active[fromLeft + 1] >> 1));
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = (active[fromLeft + 2] << 1);
                                         updateColumn(fromLeft + 2);
                                         fromLeft++;
                                         krok++;
                                         angle = 2;
                                     }
                                     break;
 
                                 case 2:
                                 // . o o        . . .
                                 // . o .  --->  o o o
                                 // . o .        . . o
                                     if((fromLeft > 0)
                                     && (((active[fromLeft + 1] >> 1) & screen[fromLeft - 1]) == 0)
                                     && ((((active[fromLeft + 1] >> 1) | (active[fromLeft + 1] >> 2)) & screen[fromLeft + 1]) == 0))
                                     {
                                         active[fromLeft - 1] = (active[fromLeft + 1] >> 1);
                                         updateColumn(fromLeft - 1);
                                         active[fromLeft] = active[fromLeft - 1];
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = (active[fromLeft] | (active[fromLeft + 1] >> 2));
                                         updateColumn(fromLeft + 1);
                                         fromLeft--;
                                         angle = 3;
                                     }
                                     break;
 
                                 case 3:
                                 // . . .        . o .
                                 // o o o  --->  . o .
                                 // . . o        o o .
                                     if((((active[fromLeft] >> 1) & screen[fromLeft]) == 0)
                                     && ((((active[fromLeft] << 1) | (active[fromLeft >> 1])) & screen[fromLeft + 1]) == 0))
                                     {
                                         active[fromLeft] = (active[fromLeft] >> 1);
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = ((active[fromLeft + 1] << 1) | active[fromLeft + 2]);
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = 0;
                                         updateColumn(fromLeft + 2);
                                         fromRight++;
                                         angle = 0;
                                     }
                                     break;
                             }
                             break;
 
                         case 4:
                         //"T"
                             switch(angle)
                             {
                                 case 0:
                                 // . . .        . o .
                                 // o o o  --->  o o .
                                 // . o .        . o .
                                     if(((active[fromLeft + 1] << 1) & screen[fromLeft + 1]) == 0)
                                     {
                                         //active[fromLeft]
                                         active[fromLeft + 1] = active[fromLeft + 1] | (active[fromLeft + 1] << 1);
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = 0;
                                         updateColumn(fromLeft + 2);
                                         fromRight++;
                                         angle = 1;
                                     }
                                     break;
 
                                 case 1:
                                 // . o .        . o .
                                 // o o .  --->  o o o
                                 // . o .        . . .
                                     if((fromRight > 0)
                                     && ((active[fromLeft] & screen[fromLeft + 2])== 0))
                                     {
                                         //active[fromLeft]
                                         active[fromLeft + 1] = active[fromLeft + 1] & (active[fromLeft + 1] << 1);
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = active[fromLeft];
                                         updateColumn(fromLeft + 2);
                                         fromRight--;
                                         krok--;
                                         angle = 2;
                                     }
                                     break;
 
                                 case 2:
                                 // . o .        . o .
                                 // o o o  --->  . o o
                                 // . . .        . o .
                                     if((((active[fromLeft + 1] >> 1) & screen[fromLeft + 1]) == 0)
                                     && (krok < lcRows))
                                     {
                                         active[fromLeft] = 0;
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = active[fromLeft + 1] | (active[fromLeft + 1] >> 1);
                                         updateColumn(fromLeft + 1);
                                         //active[fromLeft + 2]
                                         fromLeft++;
                                         krok++;
                                         angle = 3;
                                     }
                                     break;
 
                                 case 3:
                                     if((fromLeft > 0)
                                     && ((active[fromLeft + 1] & screen[fromLeft - 1]) == 0))
                                     {
                                         active[fromLeft - 1] = active[fromLeft + 1];
                                         updateColumn(fromLeft - 1);
                                         active[fromLeft] = active[fromLeft] & (active[fromLeft] >> 1);
                                         updateColumn(fromLeft);
                                         fromLeft--;
                                         angle = 0;
                                     }
                                     break;
                             }
                             break;
 
                         case 5:
                         //"I"
                             switch(angle)
                             {
                                 case 0:
                                 // . o . .        . . . .
                                 // . o . .  --->  o o o o
                                 // . o . .        . . . .
                                 // . o . .        . . . .
                                     if((fromLeft > 0)
                                     && (fromRight > 1)
 
                                     && ((((((active[fromLeft] >> 1) & (active[fromLeft] << 2)) & screen[fromLeft - 1]) & screen[fromLeft + 1]) & screen[fromLeft + 2]) == 0))
                                     {
                                         active[fromLeft - 1] = ((active[fromLeft] >> 1) & (active[fromLeft] << 2));
                                         updateColumn(fromLeft - 1);
                                         active[fromLeft] = active[fromLeft - 1];
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = active[fromLeft];
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = active[fromLeft];
                                         updateColumn(fromLeft + 2);
                                         fromLeft--;
                                         fromRight -= 2;
                                         krok -= 2;
                                         angle = 1;
                                     }
                                     break;
 
                                 case 1:
                                 // . . . .        . . o .
                                 // o o o o  --->  . . o .
                                 // . . . .        . . o .
                                 // . . . .        . . o .
                                     if((krok < (lcRows - 1))
                                     && (((active[fromLeft] << 1) | (active[fromLeft] >> 1) | (active[fromLeft] >> 2)) & screen[fromLeft + 2]) == 0)
                                     {
                                         active[fromLeft] = 0;
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = 0;
                                         updateColumn(fromLeft + 1);
 
                                         active[fromLeft + 2] = (active[fromLeft + 2] | (active[fromLeft + 2] << 1) | (active[fromLeft + 2] >> 1) | (active[fromLeft + 2] >> 2));
                                         updateColumn(fromLeft + 2);
                                         active[fromLeft + 3] = 0;
                                         updateColumn(fromLeft + 3);
                                         fromLeft += 2;
                                         fromRight++;
                                         krok += 2;
                                         angle = 2;
                                     }
                                     break;
 
                                 case 2:
                                 // . . o .        . . . .
                                 // . . o .  --->  . . . .
                                 // . . o .        o o o o
                                 // . . o .        . . . .
                                     if((fromLeft > 1)
                                     && (fromRight > 0)
 
                                     && ((((((active[fromLeft] << 1) & (active[fromLeft] >> 2)) & screen[fromLeft - 2]) & screen[fromLeft - 1]) & screen[fromLeft + 1]) == 0))
                                     {
                                         active[fromLeft - 2] = ((active[fromLeft] << 1) & (active[fromLeft] >> 2));
                                         updateColumn(fromLeft - 2);
                                         active[fromLeft - 1] = active[fromLeft - 2];
                                         updateColumn(fromLeft - 1);
                                         active[fromLeft] = active[fromLeft - 1];
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = active[fromLeft];
                                         updateColumn(fromLeft + 1);
                                         fromLeft -= 2;
                                         fromRight--;
                                         krok--;
                                         angle = 3;
                                     }
                                     break;
 
                                 case 3:
                                 // . . . .        . o . .
                                 // . . . .  --->  . o . .
                                 // o o o o        . o . .
                                 // . . . .        . o . .
                                     if((krok < (lcRows))
                                     && (((active[fromLeft] >> 1) | (active[fromLeft] << 1) | (active[fromLeft] << 2)) & screen[fromLeft + 1]) == 0)
                                     {
                                         active[fromLeft] = 0;
                                         updateColumn(fromLeft);
 
                                         active[fromLeft + 1] = (active[fromLeft + 1] | (active[fromLeft + 1] >> 1) | (active[fromLeft + 1] << 1) | (active[fromLeft + 1] << 2));
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = 0;
                                         updateColumn(fromLeft + 2);
                                         active[fromLeft + 3] = 0;
                                         updateColumn(fromLeft + 3);
                                         fromLeft++;
                                         fromRight += 2;
                                         krok++;
                                         angle = 0;
                                     }
                                     break;
                             }
                             break;
 
                         case 6:
                         //"Z"
                             switch(angle)
                             {
                                 case 0:
                                 // . . .        . o .
                                 // o o .  --->  o o .
                                 // . o o        o . .
                                     if(((active[fromLeft + 1] & screen[fromLeft]) == 0)
                                     && (((active[fromLeft + 1] << 1) & screen[fromLeft + 1]) == 0))
                                     {
                                         active[fromLeft] = active[fromLeft + 1];
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = (active[fromLeft + 1] << 1);
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = 0;
                                         updateColumn(fromLeft + 2);
                                         fromRight++;
                                         angle = 1;
                                     }
                                     break;
 
                                 case 1:
                                 // . o .        o o .
                                 // o o .  --->  . o o
                                 // o . .        . . .
                                     if((fromRight > 0)
                                     && ((((active[fromLeft] << 2) & (active[fromLeft] << 1)) & screen[fromLeft]) == 0)
                                     && (((active[fromLeft] & active[fromLeft + 1]) & screen[fromLeft + 2]) == 0))
                                     {
                                         active[fromLeft] = ((active[fromLeft] << 2) & (active[fromLeft] << 1));
                                         updateColumn(fromLeft);
                                         //active[fromLeft + 1]
                                         active[fromLeft + 2] = (active[fromLeft] >> 1);
                                         updateColumn(fromLeft + 2);
                                         fromRight--;
                                         krok--;
                                         angle = 2;
                                     }
                                     break;
 
                                 case 2:
                                 // o o .        . . o
                                 // . o o  --->  . o o
                                 // . . .        . o .
                                     if((krok < lcRows)
                                     && (((active[fromLeft + 1] >> 1) & screen[fromLeft + 1]) == 0)
                                     && (((active[fromLeft + 2] << 1) & screen[fromLeft + 2]) == 0))
                                     {
                                         active[fromLeft] = 0;
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = (active[fromLeft + 1] >> 1);
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = (active[fromLeft + 2] | (active[fromLeft + 2] << 1));
                                         updateColumn(fromLeft + 2);
                                         fromLeft++;
                                         krok++;
                                         angle = 3;
                                     }
                                     break;
 
                                 case 3:
                                 // . . o        . . .
                                 // . o o  --->  o o .
                                 // . o .        . o o
                                     if((fromLeft > 0)
                                     && (((active[fromLeft] & active[fromLeft + 1]) & screen[fromLeft - 1]) == 0)
                                     && (((active[fromLeft + 1] >> 1) & screen[fromLeft + 1]) == 0))
                                     {
                                         active[fromLeft - 1] = (active[fromLeft] & active[fromLeft + 1]);
                                         updateColumn(fromLeft - 1);
                                         //active[fromLeft]
                                         active[fromLeft + 1] = (active[fromLeft - 1] >> 1);
                                         updateColumn(fromLeft + 1);
                                         fromLeft--;
                                         angle = 0;
                                     }
                                     break;
                             }
                             break;
 
                         case 7:
                         //"S"
                             switch(angle)
                             {
                                 case 0:
                                 // . . .        o . .
                                 // . o o  --->  o o .
                                 // o o .        . o .
                                     if(((active[fromLeft + 1] << 1) & screen[fromLeft]) == 0)
                                     {
                                         active[fromLeft] = (active[fromLeft + 1] << 1);
                                         updateColumn(fromLeft);
                                         //active[fromLeft + 1]
                                         active[fromLeft + 2] = 0;
                                         updateColumn(fromLeft + 2);
                                         fromRight++;
                                         angle = 1;
                                     }
                                     break;
 
                                 case 1:
                                 // o . .        . o o
                                 // o o .  --->  o o .
                                 // . o .        . . .
                                     if((fromRight > 0)
                                     && (((active[fromLeft + 1] << 1) & screen[fromLeft + 1]) == 0)
                                     && (((active[fromLeft] & (active[fromLeft] << 1)) & screen[fromLeft + 2]) == 0))
                                     {
                                         active[fromLeft] = (active[fromLeft] & active[fromLeft + 1]);
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = (active[fromLeft + 1] << 1);
                                         updateColumn(fromLeft + 1);
                                         active[fromLeft + 2] = (active[fromLeft] << 1);
                                         updateColumn(fromLeft + 2);
                                         fromRight--;
                                         krok--;
                                         angle = 2;
                                     }
                                     break;
 
                                 case 2:
                                 // . o o        . o .
                                 // o o .  --->  . o o
                                 // . . .        . . o
                                     if((krok < lcRows)
                                     && (((active[fromLeft + 1] >> 1) & screen[fromLeft + 2]) == 0))
                                     {
                                         active[fromLeft] = 0;
                                         updateColumn(fromLeft);
                                         //active[fromLeft + 1]
                                         active[fromLeft + 2] = (active[fromLeft + 1] >> 1);
                                         updateColumn(fromLeft + 2);
                                         fromLeft++;
                                         krok++;
                                         angle = 3;
                                     }
                                     break;
 
                                 case 3:
                                 // . o .        . . .
                                 // . o o  --->  . o o
                                 // . . o        o o .
                                     if((fromLeft > 0)
                                     && ((active[fromLeft + 1] & ((active[fromLeft + 1] >> 1)) & screen[fromLeft - 1]) == 0)
                                     && ((active[fromLeft + 1] & screen[fromLeft]) == 0))
                                     {
                                         active[fromLeft - 1] = (active[fromLeft + 1] & (active[fromLeft + 1] >> 1));
                                         updateColumn(fromLeft - 1);
                                         active[fromLeft] = active[fromLeft + 1];
                                         updateColumn(fromLeft);
                                         active[fromLeft + 1] = (active[fromLeft - 1] << 1);
                                         updateColumn(fromLeft + 1);
                                         fromLeft--;
                                         angle = 0;
                                     }
                                     break;
                             }
                             break;
                     }
                     playNote('E', 10);
                     buttonDelay(200);
                 }
             }
 
 
             //Restart
             if(digitalRead(start_button) == LOW)
             {
                 memset(lc0, 0, sizeof(lc0));
                 memset(lc1, 0, sizeof(lc1));
                 memset(active, 0, sizeof(active));
                 memset(screen, 0, sizeof(screen));
                 score = 0;
                 allLines = 0;
                 figura = 0;
                 break;
             }
 
             for(int colnum = 0; colnum < lcCols; colnum++)
             {
 
                 if((screen[colnum] & (active[colnum] >> 1)) == 0)
                 {
                     colCheck++;
                 }
 
                 else
                 {
                     colCheck = 0;
                     if(krok == 0)
                     {
                         started = 0;
                     }
                 }
             }
 
             if((colCheck == lcCols) && (krok < lcRows))
             {
                 for(int colnum = 0; colnum < lcCols; colnum++)
                 {
                     active[colnum] = active[colnum] >> 1;
                     updateColumn(colnum);
                 }
             }
             else
             {
                 break;
             }
             delay(brickDelay);
         }
 
         for(int colnum = 0; colnum < lcCols; colnum++)
         {
             screen[colnum] = screen[colnum] | (lc0[colnum] << (lcRows / 2));
             screen[colnum] = screen[colnum] | lc1[colnum];
             lc0[colnum] = 0;
             lc1[colnum] = 0;
             active[colnum] = 0;
         }
 
 
 
         currLines = 0;
         for(int rownum = 0; rownum < lcRows; rownum++)
         {
             colCheck = 0;
             for(int colnum = 0; colnum < lcCols; colnum++)
             {
                 if(((screen[colnum] >> rownum) & 1) == 1)
                 {
                     colCheck++;
                 }
             }
             if(colCheck == lcCols)
             {
                 //Animacja kasowania
                 for(int colnum = 0; colnum < lcCols; colnum++)
                 {
                     tmpCol = ~((int) round(pow(2, rownum)));
                     screen[colnum] = screen[colnum] & tmpCol;
                     updateColumn(colnum);
 
                     switch(currLines)
                     {
                         case 0:
                             playNote('b', 20);
                             break;
                         case 1:
                             playNote('D', 20);
                             break;
                         case 2:
                             playNote('F', 20);
                             break;
                         case 3:
                             playNote('A', 20);
                             break;
                     }
                     delay(30);
 
                     tmpCol = (int) (round(pow(2, rownum)) - 1);
                     tmpCol = screen[colnum] & tmpCol;
                     screen[colnum] = (screen[colnum] >> (rownum + 1));
                     screen[colnum] = (screen[colnum] << rownum);
                     screen[colnum] = screen[colnum] | tmpCol;
 
                 }
 
 
                 for(int colnum = 0; colnum < lcCols; colnum++)
                 {
                     updateColumn(colnum);
                 }
                 rownum--;
                 currLines++;
                 allLines++;
             }
         }
 
         if(currLines > 0)
         {
             score += (int) round(pow(4, currLines-1));
         }
    }
 
gameOver();
// == Game Over ==
 
 }
}
 
void gameOver()
{
  playNote('F', 80);
  playNote('A', 60);
  playNote('F', 80);
  playNote('A', 60);
 
     int cima[] =
     {
         B11111111,   //     o     o o o
         B11111111,   //   o o o    o
         B11111111,   //   o   o     o o
         B11111111,   //     o     o
         B11111111,   //     o     o o o
         B11111111,   //
         B11111111,   //   o o o   o o o
         B11111111    //     o     o   o
     };
 
     int baixo[] =
     {
         B11111111,   //     o     o o
         B11111111,   //     o     o   o
         B11111111,   //     o     o     o
         B11111111,   //
         B11111111,   //     o       o o o
         B11111111,   //     o       o
         B11111111,   //     o         o
         B11111111    //     o     o o o
     };
 
 for(int rownum = 8; rownum >= 0; rownum--)
     {
         lc.setRow(1,rownum,baixo[rownum]);
         delay(100);
     }
 
     for(int rownum = 8; rownum >= 0; rownum--)
     {
         lc.setRow(0,rownum,cima[rownum]);
         delay(100);
     }
 
     delay(1800);
 
}
