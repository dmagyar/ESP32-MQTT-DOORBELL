#include "Arduino.h"
#include "WiFiMulti.h"
#include "Audio.h"
#include "SPI.h"
#include "SD.h"
#include "FS.h"
#include "LITTLEFS.h"

// Digital I/O used
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;

const char *SayThis = 0;
const char *OldSayThis = 0;

int SoundTheBell = 0;

void Say(const char *s) {
   Serial.print("Saying: ");
   Serial.println(s);
   audio.connecttospeech(s, "nl");
}

void SetVolume(int a) {
      	audio.setVolume(a);
}

void Bell() {
	Serial.println("Bellbell!");
	audio.connecttoFS(LITTLEFS, "/bell.mp3");
	delay(200);
}

void AudioSetup() {
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(21); // 0...21

    if(!LITTLEFS.begin(true)){
        Serial.println("LITTLEFS Mount Failed");
        return;
    }

//    audio.connecttoFS(LITTLEFS, "/bell.mp3");
    //audio.connecttohost("www.wdr.de/wdrlive/media/einslive.m3u");
    //audio.connecttohost("dg-ais-eco-http-fra-eco-cdn.cast.addradio.de/hellwegradio/west/mp3/high");
//   audio.connecttohost("http://21293.live.streamtheworld.com/WEB10_MP3_SC");
//    audio.connecttohost("http://87.98.217.63:24112/stream");
    audio.connecttospeech("Speaker ready.", "en");
    delay(1000);
}

void AudioLoop()
{
    audio.loop();
    if (SayThis != OldSayThis) {
	OldSayThis = SayThis;
	Say((const char *)SayThis);
    } 
    if (SoundTheBell == 1) {
	SoundTheBell = 0;
	Bell();
    }
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     "); Serial.println(info);
}
void audio_id3image(File& file, const size_t pos, const size_t size){
    Serial.print("id3image     "); Serial.printf("at pos: %u, length: %u\n", pos, size);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}

