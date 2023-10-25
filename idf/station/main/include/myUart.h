#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"

#define UART_NUM UART_NUM_2
#define RX_PIN 16
#define TX_PIN 17

typedef struct {
    int HUM;
    int TEMP;
    int LIGHT;
    int UV;
    int PRESSURE;
    int ECO2;
    int TVOC;
    int SOUND;
    int EXEC;
} SensorData;
extern SensorData control;


void initUart();
void updateMeasurementValues();
esp_err_t uart_read_until(uint8_t* data, size_t max_len, char delim, TickType_t timeout);