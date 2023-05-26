//音樂部分(巨集)
#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262

//圖形部分(巨集)
#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

//#define BUTTON 2

//音樂部分(陣列)
int melody[] = {
  NOTE_C3, NOTE_C3, NOTE_C3, NOTE_G3, NOTE_G3, NOTE_F3, NOTE_E3, 0, NOTE_D3, NOTE_E3, NOTE_F3, 0, NOTE_E3,
  NOTE_D3, NOTE_C3, NOTE_C3, NOTE_E3, NOTE_D3, NOTE_G3, NOTE_C3, NOTE_C3, NOTE_C3, NOTE_D3
};

int noteDurations[] = {
  8, 8, 8, 4, 4, 8, 8, 8, 4, 8, 8, 8, 4,
  8, 8, 4, 4, 8, 4, 4, 8, 4, 4
};

//圖形部分(矩陣)
const int row[] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8 };
const int col[] = { COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8 };

byte scan[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 1}
};

byte circle[8][8] = {
  {1, 1, 0, 0, 0, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 0, 1},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 0, 1, 1, 0, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 0, 1, 1, 1, 1, 0, 1},
  {1, 1, 0, 0, 0, 0, 1, 1}
};


//byte previousState=0, presentState=0, patternNumber=0;

void setup()
{
  for (byte i = 0; i <= sizeof(row); i++) {
    pinMode(row[i], OUTPUT);
  }
  for (byte i = 0; i <= sizeof(col); i++) {
    pinMode(col[i], OUTPUT);
  }

  //pinMode(BUTTON, INPUT_PULLUP);
  //Serial.begin(9600);
}
int thisNote = -1, noteDuration = 0;
long presentTime = 0, previousTime = 0, pauseBetweenNotes = 0;


void checkToPlay() {
  presentTime = millis();
  if (presentTime - previousTime >= pauseBetweenNotes) {
   
    thisNote += 1;
    if (thisNote >= 8) {
      thisNote = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }
    else {
         

      noteDuration = 1000 / noteDurations[thisNote];
      tone(2, melody[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime = presentTime;
    }
  }
}
void showPattern(byte matrix[8][8])
{
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < 8; j++) {
      digitalWrite(row[j],1-scan[i][j]);
      digitalWrite(col[j],1-matrix[i][j]);
    }
    for (byte j = 0; j < 8; j++) {
      digitalWrite(row[j], HIGH);
      digitalWrite(col[j], LOW);
    }
  }
}
void loop()
{
  showPattern(circle);
  delay(2);
  checkToPlay();
}




/*presentState = digitalRead(BUTTON);
  if(presentState == 1 && previousState == 0){
  patternNumber++;
  if(patternNumber > 2) patternNumber = 0;
  }
  Serial.println(patternNumber);

  if(patternNumber == 0) showPattern(circle);
  else if(patternNumber == 1) showPattern(H);
  else if(patternNumber == 2)showPattern(A);
  delay(2);
  previousState = presentState;*/
