#include "include/myWifi.h"

#define CONFIG_STA_WIFI_SSID      "ESP32"
#define CONFIG_STA_WIFI_PASSWORD      "asdasd1234"

EventGroupHandle_t wifi_event_group;
const int CONNECTED_BIT = BIT0;

void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("WiFi connecting ... \n");
        break;

    case WIFI_EVENT_STA_CONNECTED:
        printf("WiFi connected ... \n");
        break;

    case WIFI_EVENT_STA_DISCONNECTED:
        printf("WiFi lost connection ... \n");
        break;

	case IP_EVENT_STA_GOT_IP:
		printf("WiFi got IP ... \n\n");
		break;

    default:
        break;
    }
}

void initialise_wifi(void)
{
    esp_netif_init();
	esp_event_loop_create_default();
	esp_netif_create_default_wifi_sta();
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation);
	
	esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = CONFIG_STA_WIFI_SSID,
            .password = CONFIG_STA_WIFI_PASSWORD}};
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);

    esp_wifi_start();

	esp_wifi_connect();
}