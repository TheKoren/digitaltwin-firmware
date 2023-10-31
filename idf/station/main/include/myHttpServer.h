#include "esp_http_server.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mdns.h"
#include "esp_netif_ip_addr.h"
#include "cJSON.h"

esp_err_t get_handler(httpd_req_t *req);
void server_initiation();
void add_mdns_service();
void initialise_mdns();