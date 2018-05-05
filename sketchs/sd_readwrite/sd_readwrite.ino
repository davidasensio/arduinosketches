#include <SD.h>

File testFile;

//SD pins

int cs = 4;

void setup() {
  Serial.begin(9600);
  Serial.print("Initializing SD...");
  if (!SD.begin(cs)) {
    Serial.println("Cant initialize");
    return;
  }
  Serial.println("Initialization successfully");
  //readFile();
  writeFile();
  
}

void loop() {
}

void readFile() {
  testFile = SD.open("testfile.txt");
  if (testFile) {
    Serial.println("textfile.txt");
    while (testFile.available()) {
      Serial.write(testFile.read());
    }
    testFile.close();
  } else {
    Serial.println("Error opening file");
  }
}

void writeFile() {
  testFile = SD.open("testfile.txt", FILE_WRITE);//abrimos  el archivo

  if (testFile) { 
    Serial.print("Writing SD: ");
    testFile.print("Tiempo(ms)=");
    testFile.print(millis());
    testFile.println();
    testFile.println("End of test <--");
    testFile.close();

    Serial.print("_Tiempo(ms)=");
    Serial.print(millis());
  }
  else {
    Serial.println("Error opening file for writing");
  }
}

