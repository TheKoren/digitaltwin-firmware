
#include "esp_http_client.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mdns.h"
#include "esp_netif_ip_addr.h"
#include "cJSON.h"

char *getMacAddress(uint8_t *mac);
esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt);
void rest_get(const char * addr);
void rest_post(const char *data);
void find_mdns_service(const char * service_name, const char * proto);
void readFromAP();