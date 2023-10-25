#include "include/myUart.h"

SensorData control;

static const char *TAG = "UART";

void initUart() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    ESP_ERROR_CHECK(uart_param_config(UART_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM, 256, 0, 0, NULL, 0));
}

esp_err_t uart_read_until(uint8_t* data, size_t max_len, char delim, TickType_t timeout)
{
    size_t idx = 0;
    while (idx < max_len - 1) {
        // Read one byte with a timeout
        int len = uart_read_bytes(UART_NUM, data + idx, 1, timeout);
        if (len < 0) {
            ESP_LOGE(TAG, "UART read error");
            return ESP_FAIL;
        }
        if (len == 1 && (data[idx] == delim)) {
            data[idx] = '\0';
            return ESP_OK;
        }
        idx++;
    }
    data[max_len - 1] = '\0';
    return ESP_FAIL;
}

void updateMeasurementValues() {
    ESP_LOGI(TAG, "Reading sensor values");
    char buffer[10];
    char firstChar;

    // Wait for the opening '[' character
    do {
        uart_read_bytes(UART_NUM, (uint8_t*)&firstChar, 1, portMAX_DELAY);
    } while (firstChar != '[');

    
    for (int i = 0; i < 9; i++) {
        if (uart_read_until((uint8_t*)buffer, sizeof(buffer), ',', portMAX_DELAY) == ESP_OK) {

        switch (i) {
            case 0:
                control.HUM = atoi(buffer);
                break;
            case 1:
                control.TEMP = atoi(buffer);
                break;
            case 2:
                control.LIGHT = atoi(buffer);
                break;
            case 3:
                control.UV = atoi(buffer);
                break;
            case 4:
                control.PRESSURE = atoi(buffer);
                break;
            case 5:
                control.ECO2 = atoi(buffer);
                break;
            case 6:
                control.TVOC = atoi(buffer);
                break;
            case 7:
                control.SOUND = atoi(buffer);
                break;
            case 8:
                control.EXEC = atoi(buffer);
                break;
            default:
                break;
        }
        }
    }

    ESP_LOGI(TAG, "Sensor read complete");
}