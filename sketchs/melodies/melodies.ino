int speakerPin = 7;
char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };
int tempo = 140;

int length = 19;
char notes[] = "gage gage ddb ccg aacba";
int beats[] = { 6,3,6,6, 2,6,3,6,6, 2, 12,6,8,2 ,12,6,12, 4,12,6,6,6,6};

void playTone(int tone, int duration) {
  int p = tone*2;
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(p);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(p);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      int t = tones[i]*0.05;
      playTone(t, duration);
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 playMelody();

}

void playMelody() {
   for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2); 
  }
}


