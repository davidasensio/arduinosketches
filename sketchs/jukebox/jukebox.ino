

//TMRpcm audio;
//audio.play("filename");    plays a file
//audio.play("filename",30); plays a file starting at 30 seconds into the track
//audio.speakerPin = 11;     set to 5,6,11 or 46 for Mega, 9 for Uno, Nano, etc.
//audio.disable();           disables the timer on output pin and stops the music
//audio.stopPlayback();      stops the music, but leaves the timer running
//audio.isPlaying();         returns 1 if music playing, 0 if not
//audio.pause();             pauses/unpauses playback
//audio.quality(1);          Set 1 for 2x oversampling
//audio.volume(0);           1(up) or 0(down) to control volume
//audio.setVolume(0);        0 to 7. Set volume level
//audio.loop(1);             0 or 1. Can be changed during playback for full control of looping.


#include <SD.h>
#include <Bounce2.h>

#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

String ROOT_FOLDER = "/fx/";
String CARTOON_FOLDER = "cartoon";
String ENGINE_FOLDER = "engine";
String VEHICLE_FOLDER = "vehicle";
String SIREN_FOLDER = "siren";
String OTHER_FOLDER = "other";

TMRpcm audio;
Bounce bouncer = Bounce();

//SD pins
int cs = 4;

int spkPin = 9;
int buttonPin = A0;

void setup() {
  audio.speakerPin = spkPin;
  buttonPin = A0;

  bouncer.attach(buttonPin);
  bouncer.interval(10);

  pinMode(spkPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  Serial.print("Initializing SD...");
  if (!SD.begin(cs)) {
    Serial.println("Cant initialize");
    return;
  }
  Serial.println("Initialization successfully");

}

void loop() {
  randomSeed(millis());
  bouncer.update();

  if (bouncer.fell()) {
    if (audio.isPlaying() == 0) {
      play(getRandomTheme());
    } else {
      audio.stopPlayback();
    }
  }
}

void play(String theme) {
  Serial.println("Playing theme " + theme + " ...");
  audio.setVolume(6);
  audio.play(&theme[0]);
}

//Random Themes
String getRandomTheme() {
  int index = random(5) + 1;
  String path = "";
  switch (index) {
    case 1:
      return getRandomCartoonTheme();
      break;
    case 2:
      return getRandomEngineTheme();
      break;
    case 3:
      return getRandomVehicleTheme();
      break;
    case 4:
      return getRandomSirenTheme();
      break;
    case 5:
      return getRandomOtherTheme();
      break;
  }
  return "";
}

String getRandomCartoonTheme() {
  Serial.println("Random cartoon");
  return getRandomFolderTheme(4, getCartoonFolder() + "cartoon");
}

String getRandomEngineTheme() {
  Serial.println("Random engine");
  return getRandomFolderTheme(7, getEngineFolder() + "engine");
}

String getRandomVehicleTheme() {
  Serial.println("Random vehicle");
  return getRandomFolderTheme(3, getVehicleFolder() + "vehicle");
}

String getRandomSirenTheme() {
  Serial.println("Random siren");
  return getRandomFolderTheme(2, getSirenFolder() + "siren");
}

String getRandomOtherTheme() {
  Serial.println("Random other");
  return getRandomFolderTheme(4, getOtherFolder() + "other");
}

String getRandomFolderTheme(int max, String path) {
  int index = random(max) + 1;
  String filename = path + index + ".wav";
  Serial.println("Filename: "  + filename);
  return filename;
}



String getCartoonFolder() {
  return ROOT_FOLDER + CARTOON_FOLDER + "/";
}

String getEngineFolder() {
  return ROOT_FOLDER + ENGINE_FOLDER + "/";
}

String getVehicleFolder() {
  return ROOT_FOLDER + VEHICLE_FOLDER + "/";
}

String getSirenFolder() {
  return ROOT_FOLDER + SIREN_FOLDER + "/";
}

String getOtherFolder() {
  return ROOT_FOLDER + OTHER_FOLDER + "/";
}

