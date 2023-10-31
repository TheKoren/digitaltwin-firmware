#include <string.h>
#include "include/myWifi.h"
#include "include/myHttpClient.h"
#include "include/myUart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_http_client.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_system.h"

#define CONFIG_STA_CONNECT_TIMEOUT 30 // 30 seconds

void vLowWifiTask(void *pvParameter)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while(1) {
		updateMeasurementValues();
		find_mdns_service("_http", "_tcp");
		readFromAP();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10000))
    }
}



void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
	initUart();

    initialise_wifi();
    wifi_apsta(CONFIG_STA_CONNECT_TIMEOUT*1000);
	ESP_ERROR_CHECK( mdns_init() );

    xTaskCreate(vLowWifiTask, "LowWifiTask", 8192, NULL, 5, NULL);
}
