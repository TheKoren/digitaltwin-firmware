#include "include/myHttpServer.h"
#include "include/myUart.h"
#include "include/myWifi.h"



esp_err_t get_handler(httpd_req_t *req)
{
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

    cJSON_AddNumberToObject(operational, "rssi", ap.rssi);
    cJSON_AddNumberToObject(operational, "channel", ap.primary);
    cJSON_AddNumberToObject(operational, "TxPower", pow);
    cJSON_AddStringToObject(operational, "mode", "WIFI_STA");
    cJSON_AddNumberToObject(operational, "sensorRead", 0);
    cJSON_AddNumberToObject(operational, "sensorExec", control.EXEC);

    char *output = cJSON_PrintUnformatted(root);
    httpd_resp_send(req, output, HTTPD_RESP_USE_STRLEN);
    cJSON_Delete(root);
    free(output);
    return ESP_OK;
}

void server_initiation()
{
    httpd_config_t server_config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server_handle = NULL;
    httpd_start(&server_handle, &server_config);

    httpd_uri_t uri_get = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = get_handler,
        .user_ctx = NULL};
    httpd_register_uri_handler(server_handle, &uri_get);
}

void initialise_mdns() {
    mdns_init();
    mdns_hostname_set("esp32");
    ESP_LOGI("mdns", "mdns host name set to esp32");
    
    // Set the mDNS service name to match the service you want to advertise.
    mdns_instance_name_set("esp32_http");
    
    // Add the mDNS service with the specified type and port.
    mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0);

    // Set the instance name for the mDNS service.
    mdns_service_instance_name_set("_http", "_tcp", "esp32_http");
}
