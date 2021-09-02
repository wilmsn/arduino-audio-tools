// Simple wrapper for Arduino sketch to compilable with cpp in cmake
#include "Arduino.h"
#include "AudioTools.h"
#include "sample-12s.h"

using namespace audio_tools;  

MemoryStream mp3(sample_12s_mp3, sample_12s_mp3_len);
MetaDataID3 out;
StreamCopy copier(out, mp3); // copy in to out
bool title_printed = false;


void printMetaData(MetaInfo type, const char* str, int len){
  Serial.print("==> ");
  Serial.print(MetaInfoStr[type]);
  Serial.print(": ");
  Serial.println(str);
  title_printed = true;
}

void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);  

  out.setCallback(printMetaData);
  out.begin();
  mp3.begin();
}

void loop(){
  if (mp3) {
    copier.copy();
  } else {
    assert(title_printed);
    exit(0);
  }
}

int main(){
  setup();
  while(true) loop();
}