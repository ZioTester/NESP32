#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <SPIFFS.h>
#include <esp_task_wdt.h>
#include <esp_wifi.h>

#include "controller.h"
#include "display.h"

extern "C" {
#include <nofrendo.h>
}

int16_t bg_color;
extern Arduino_TFT *gfx;
extern void display_begin();
char *argv[1];

void setup() {
#if defined(ILI9341_DRIVER) or defined(ILI9488_DRIVER)
  pinMode(TFT_MISO, OUTPUT);
  digitalWrite(TFT_MISO, LOW);
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, LOW);
#endif
  Serial.begin(115200);

  esp_wifi_deinit();

  TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU(0);
  esp_task_wdt_delete(idle_0);

  display_begin();

  if (!SPIFFS.begin(false, "/fs")) {
    Serial.println("File system Failed");
    for (;;) {
    }
  } else {
    Serial.println("File system Successful");
  }

  argv[0] = (char *)"/fs/t.nes";
  nofrendo_main(1, argv);
}

void loop() {}