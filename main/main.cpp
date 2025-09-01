#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "tusb.h"
#include "esp32s3/rom/ets_sys.h"
#include "esp_system.h"

extern "C" void app_main(void);

void app_main(void) {
    ESP_LOGI("HID-BRIDGE", "Starting USB HID to BLE bridge...");

    // TinyUSB initialization
    tusb_init();

    while (true) {
        // USB host task placeholder
        tud_task(); // TinyUSB device task

        // TODO: Read OTG mouse/keyboard input
        // TODO: Send as BLE HID

        vTaskDelay(pdMS_TO_TICKS(10)); // small delay
    }
}
