#include "include/myHttpClient.h"
#include "include/myUart.h"
#include "include/myWifi.h"

static const char *TAG = "HTTP";

esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        rest_post((char *)evt->data);
        break;

    default:
        break;
    }
    return ESP_OK;
}

void rest_get(const char * addr)
{
    char url[128];
    snprintf(url, sizeof(url), "http://%s:80", addr);
    esp_http_client_config_t config_get = {
        .url = url,
        .method = HTTP_METHOD_GET,
        .cert_pem = NULL,
        .event_handler = client_event_get_handler,
        .timeout_ms = 10000};
        
    esp_http_client_handle_t client = esp_http_client_init(&config_get);
    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}

esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        break;

    default:
        break;
    }
    return ESP_OK;
}

void rest_post(const char *data)
{
    esp_http_client_config_t config_post = {
        .url = "http://192.168.100:8080/data",
        .method = HTTP_METHOD_POST,
        .cert_pem = NULL,
        .event_handler = client_event_post_handler
    };
    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    esp_http_client_set_post_field(client, data, strlen(data));
    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);

}

void find_mdns_service(const char * service_name, const char * proto)
{
    ESP_LOGI(TAG, "Query PTR: %s.%s.local", service_name, proto);

    mdns_result_t * results = NULL;
    esp_err_t err = mdns_query_ptr(service_name, proto, 3000, 20,  &results);
    if(err){
        ESP_LOGE(TAG, "Query Failed");
        return;
    }
    if(!results){
        ESP_LOGW(TAG, "No results found!");
        return;
    }

    mdns_ip_addr_t * a = NULL;
    while (results) {
        a = results->addr;
        while (a) {
            printf("  A   : " IPSTR "\n", IP2STR(&(a->addr.u_addr.ip4)));
            char ip_str[16];
            snprintf(ip_str, sizeof(ip_str), IPSTR, IP2STR(&(a->addr.u_addr.ip4)));
            rest_get(ip_str);
            a = a->next;
        }
        results = results->next;
    }

}

char *getMacAddress(uint8_t *mac) {
    static char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], (mac[5] + 1) % 256);
    return macStr;
}

void readFromAP() {
    wifi_mode_t wifi_mode;
    wifi_ap_record_t ap;
    wifi_interface_t inf = WIFI_IF_AP;
    wifi_config_t conf;
    int8_t pow;
    uint8_t mac[6];
    esp_wifi_get_max_tx_power(&pow);
    esp_wifi_get_mode(&wifi_mode);
    esp_wifi_sta_get_ap_info(&ap);
    esp_wifi_get_config(inf, &conf);
    esp_read_mac(mac, ESP_MAC_WIFI_SOFTAP);

    cJSON *root = cJSON_CreateObject();
    cJSON *header = cJSON_CreateObject();
    cJSON *measurements = cJSON_CreateObject();
    cJSON *operational = cJSON_CreateObject();
    cJSON *addressList = cJSON_CreateArray();

    cJSON_AddItemToObject(root, "header", header);
    cJSON_AddItemToObject(root, "measurements", measurements);
    cJSON_AddItemToObject(root, "operational", operational);

    cJSON_AddStringToObject(header, "device", "ESP32");
    char macString[18];
    snprintf(macString, sizeof(macString), "%02X:%02X:%02X:%02X:%02X:%02X",  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    cJSON_AddStringToObject(header, "mac", macString);

    // Update measurement values
    updateMeasurementValues();
    cJSON_AddNumberToObject(measurements, "temp", control.TEMP);
    cJSON_AddNumberToObject(measurements, "hum", control.HUM);
    cJSON_AddNumberToObject(measurements, "press", control.PRESSURE);
    cJSON_AddNumberToObject(measurements, "eco2", control.ECO2);
    cJSON_AddNumberToObject(measurements, "tvoc", control.TVOC);
    cJSON_AddNumberToObject(measurements, "light", control.LIGHT);
    cJSON_AddNumberToObject(measurements, "uv", control.UV);
    cJSON_AddNumberToObject(measurements, "sound", control.SOUND);

    cJSON_AddItemToObject(operational, "addressList", addressList);
    cJSON_AddNumberToObject(operational, "rssi", ap.rssi);
    cJSON_AddNumberToObject(operational, "channel", ap.primary);
    cJSON_AddNumberToObject(operational, "TxPower", pow);
    cJSON_AddStringToObject(operational, "mode", "WIFI_AP_STA");
    cJSON_AddNumberToObject(operational, "sensorRead", 0);
    cJSON_AddNumberToObject(operational, "sensorExec", control.EXEC);

    wifi_sta_list_t stationList;
    memset(&stationList, 0, sizeof(stationList));
    esp_wifi_ap_get_sta_list(&stationList);

    for (int i = 0; i < stationList.num; i++) {
        char *macStr = getMacAddress(stationList.sta[i].mac);
        cJSON_AddItemToArray(addressList, cJSON_CreateString(macStr));
    }

    char *output = cJSON_PrintUnformatted(root);
    rest_post(output);

    cJSON_Delete(root);

    ESP_LOGI(TAG, "JSON Output: %s", output);
    free(output);
}