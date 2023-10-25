#include "include/myWifi.h"

#define CONFIG_STA_WIFI_SSID      "ESP32"
#define CONFIG_STA_WIFI_PASSWORD      "asdasd1234"
#define EXAMPLE_ESP_WIFI_CHANNEL   CONFIG_ESP_WIFI_CHANNEL
#define EXAMPLE_MAX_STA_CONN       CONFIG_ESP_MAX_STA_CONN

EventGroupHandle_t wifi_event_group;
const int CONNECTED_BIT = BIT0;

static const char *TAG = "WIFI";

void event_handler(void* arg, esp_event_base_t event_base,
								int32_t event_id, void* event_data)
{
	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
		ESP_LOGI(TAG, "WIFI_EVENT_STA_DISCONNECTED");
		esp_wifi_connect();
		xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
	} else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
		ESP_LOGI(TAG, "IP_EVENT_STA_GOT_IP");
		xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
	}
}

void initialise_wifi(void)
{
	esp_log_level_set("wifi", ESP_LOG_WARN);
	static bool initialized = false;
	if (initialized) {
		return;
	}
	ESP_ERROR_CHECK(esp_netif_init());
	wifi_event_group = xEventGroupCreate();
	ESP_ERROR_CHECK(esp_event_loop_create_default());
	esp_netif_t *ap_netif = esp_netif_create_default_wifi_ap();
	assert(ap_netif);
	esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
	assert(sta_netif);
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
	ESP_ERROR_CHECK( esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &event_handler, NULL) );
	ESP_ERROR_CHECK( esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL) );

	ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
	ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_NULL) );
	ESP_ERROR_CHECK( esp_wifi_start() );

	initialized = true;
}

bool wifi_sta(int timeout_ms)
{
	wifi_config_t wifi_config = { 0 };
	strcpy((char *)wifi_config.sta.ssid, CONFIG_STA_WIFI_SSID);
	strcpy((char *)wifi_config.sta.password, CONFIG_STA_WIFI_PASSWORD);

	ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
	ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
	ESP_ERROR_CHECK( esp_wifi_connect() );

	int bits = xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
								   pdFALSE, pdTRUE, timeout_ms / portTICK_PERIOD_MS);
	ESP_LOGI(TAG, "bits=%x", bits);
	if (bits) {
		ESP_LOGI(TAG, "WIFI_MODE_STA connected. SSID:%s password:%s",
			 CONFIG_STA_WIFI_SSID, CONFIG_STA_WIFI_PASSWORD);
	} else {
		ESP_LOGI(TAG, "WIFI_MODE_STA can't connected. SSID:%s password:%s",
			 CONFIG_STA_WIFI_SSID, CONFIG_STA_WIFI_PASSWORD);
	}
	return (bits & CONNECTED_BIT) != 0;
}