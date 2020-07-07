#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>
#include <FS.h>

typedef struct {
    char init[5];
    char data[3500];
} eepromSave;

eepromSave data;
const char initString[] PROGMEM = "NAMF";
const char initPayload[] PROGMEM = "Szła dzieweczka do laseczka, do zielooooneeegoo!";
void setup() {
    // put your setup code here, to run once:
    EEPROM.begin(4096);
    Serial.begin(115200);
    for (byte i=0; i<20;i++) {
        delay(200);
        Serial.print(".");
    }

    Serial.println("Starting");
    if (SPIFFS.begin()) {
        Serial.println("SPIFFS initialized!");
    }else {
        Serial.println("SPIFFS NOT initialized!");
    }

    FSInfo fs_info;
    SPIFFS.info(fs_info);
    Serial.print(F("SPIFFS size (kB): "));
    Serial.println(fs_info.totalBytes/(1024));

    Serial.print(F("Free sketch space (kB): "));
    Serial.println(ESP.getFreeSketchSpace()/1024);
    Serial.print(F("CPU freq (MHz): "));
    Serial.println(ESP.getCpuFreqMHz());


    EEPROM.get(0, data);
    if (!strcmp_P(data.init, initString)) {
        Serial.println("EEPROM initialized and saved before.\nSaved data:");
        Serial.println(data.data);
    } else {
        Serial.println("Clear EEPROM, write data.");
        strncpy_P(data.init, initString, 5);
        strncpy_P(data.data, initPayload, 3500);
        EEPROM.put(0,data);
        Serial.println(data.data);
        EEPROM.commit();
    }
    EEPROM.end();
}

void loop() {
    // put your main code here, to run repeatedly:
}