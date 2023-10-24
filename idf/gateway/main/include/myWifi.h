#include "esp_system.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "freertos/event_groups.h"

void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void initialise_wifi(void);
bool wifi_apsta(int timeout_ms);