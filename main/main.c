#include "esp_log.h"
#include "esp_bt.h"
#include "esp_hidh.h"
#include "tinyusb.h"
#include "class/hid/hid_host.h"
#include "esp_hidd_prf_api.h"
#include "esp_bt_main.h"

static const char *TAG = "USB_BT_MOUSE";

static uint32_t last_click_time = 0;
static int click_count = 0;

#define CPS_LIMIT 15   // Maksimum click per second

// Mouse event işleme
void usb_mouse_event(uint8_t buttons, int8_t x, int8_t y, int8_t wheel) {
    uint32_t now = esp_timer_get_time() / 1000000; // saniye

    if (buttons & 0x01) { // Sol tık
        if (now == last_click_time) {
            click_count++;
            if (click_count > CPS_LIMIT) {
                ESP_LOGW(TAG, "CPS limit exceeded, ignoring click");
                return;
            }
        } else {
            last_click_time = now;
            click_count = 1;
        }
    }

    ESP_LOGI(TAG, "Mouse Event: btn=%02x, dx=%d, dy=%d, wheel=%d", buttons, x, y, wheel);

    // Burada BT HID mouse event gönderilir
    esp_hidd_send_mouse_value(x, y, buttons);
}

// USB HID callback
void tusb_hid_mouse_cb(uint8_t dev_addr, uint8_t instance, hid_mouse_report_t const * report) {
    usb_mouse_event(report->buttons, report->x, report->y, report->wheel);
}

void app_main(void) {
    ESP_LOGI(TAG, "Starting USB → BT Mouse Bridge with CPS filter...");

    // USB Host init
    tusb_init();

    // BT init
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT);
    esp_bluedroid_init();
    esp_bluedroid_enable();

    esp_hidd_profile_init();
}
