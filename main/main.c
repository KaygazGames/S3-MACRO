#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"

// Burada USB HID → Bluetooth mouse emülasyonu eklenecek
// Şimdilik alive test

static const char *TAG = "usb_mouse_bt";

void app_main(void) {
    ESP_LOGI(TAG, "USB Mouse to Bluetooth HID Projesi basladi!");

    while (1) {
        ESP_LOGI(TAG, "Sistem calisiyor...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
