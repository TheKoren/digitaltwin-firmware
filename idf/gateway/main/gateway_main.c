/*  WiFi softAP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
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

//static const char *TAG = "MAIN";

void print_lowlevel_wifi_data()
{/*
    ESP_LOGI(TAG, "MAC address: %02X:%02X:%02X:%02X:%02X:%02X, Mode: %d, RSSI: %d, Channel: %d, Beacon interval: %d, TX Power: %d. \n",
     mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
      wifi_mode, ap.rssi, ap.primary, conf.ap.beacon_interval, pow);
	  */
}

void vLowWifiTask(void *pvParameter)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while(1) {
        print_lowlevel_wifi_data();
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
