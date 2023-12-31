/*
 * measurement.c
 *
 *  Created on: 9 Oct 2023
 *      Author: 36302
 */


#include "sl_sleeptimer.h"
#include "measurement.h"


#define TOOGLE_DELAY_MS         5000


sl_sleeptimer_timer_handle_t timer;
bool toggle_timeout = false;

static void on_timeout(sl_sleeptimer_timer_handle_t *handle,
                       void *data);

void measurement_init(void)
{
  sensorInit();
  // Create timer for waking up the system periodically.
  sl_sleeptimer_start_periodic_timer_ms(
      &timer,
      TOOGLE_DELAY_MS,
      on_timeout, NULL,
      0,
      SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);

}
uint32_t start_time, end_time, execution_time;


void measurement_process_action(void)
{
  if (toggle_timeout == true) {
	  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
	    TIMER_Init(TIMER0, &timerInit);
	    TIMER_Enable(TIMER0, true);
	    start_time = TIMER_CounterGet(TIMER0);

      uint32_t humidity;
      int32_t temperature;
      float lux;
      float uvi;
      float pressure;
      uint16_t eco2;
      uint16_t tvoc;
      float sound_level;
      char values[9][50];
      sl_service_rht_get(&humidity, &temperature);
      sl_service_light_get(&lux, &uvi);
      sl_service_pressure_get(&pressure);
      sl_service_gas_get(&eco2, &tvoc);
      sl_service_sound_get(&sound_level);

      sprintf(values[0], "[%lu,", humidity);
      sprintf(values[1], "%ld,", temperature);
      sprintf(values[2], "%lu,", (uint32_t)(lux * 100));
      sprintf(values[3], "%d,", (uint8_t)uvi);
      sprintf(values[4], "%lu,", (uint32_t)(pressure * 1000.0f));
      sprintf(values[5], "%d,", eco2);
      sprintf(values[6], "%d,", tvoc);
      sprintf(values[7], "%d,", (int16_t)(sound_level * 100.0f));
      end_time = TIMER_CounterGet(TIMER0);
      execution_time = end_time - start_time;
      sprintf(values[8], "%lu,", execution_time);

      for(int i = 1; i <= 9; i++)
        {
           strcat(values[0], values[i]);
        }

      const char * payload = values[0];
      printf(payload, APP_LOG_NL);
    toggle_timeout = false;
  }
}

static void on_timeout(sl_sleeptimer_timer_handle_t *handle,
                       void *data)
{
  (void)&handle;
  (void)&data;
  toggle_timeout = true;
}

void sensorInit()
{
  sl_status_t sc;
  #ifdef SL_CATALOG_SENSOR_LIGHT_PRESENT
    sc = sl_sensor_light_init();
    if (sc != SL_STATUS_OK) {
        app_log_info("Ambient light and UV index sensor initialization failed.\r\n");
    }
  #endif // SL_CATALOG_SENSOR_LIGHT_PRESENT
  #ifdef SL_CATALOG_SENSOR_RHT_PRESENT
    sc = sl_sensor_rht_init();
    if (sc != SL_STATUS_OK) {
        app_log_info("Relative Humidity and Temperature sensor initialization failed.\r\n");
    }
  #endif // SL_CATALOG_SENSOR_RHT_PRESENT
  #ifdef SL_CATALOG_SENSOR_PRESSURE_PRESENT
    sc = sl_sensor_pressure_init();
    if (sc != SL_STATUS_OK) {
        app_log_info("Air Pressure sensor initialization failed.\r\n");
    }
  #endif // SL_CATALOG_SENSOR_PRESSURE_PRESENT
  #ifdef SL_CATALOG_SENSOR_GAS_PRESENT
    sc = sl_sensor_gas_init();
    if (sc != SL_STATUS_OK) {
        app_log_info("Air quality sensor initialization failed.\r\n");
    }
  #endif // SL_CATALOG_SENSOR_GAS_PRESENT
  #ifdef SL_CATALOG_SENSOR_SOUND_PRESENT
    sc = sl_sensor_sound_init();
    if (sc != SL_STATUS_OK) {
        app_log_info("Sound level sensor initialization failed.\r\n");
    }
  #endif // SL_CATALOG_SENSOR_SOUND_PRESENT
}

void sensorDeInit()
{
  #ifdef SL_CATALOG_SENSOR_LIGHT_PRESENT
    sl_sensor_light_deinit();
  #endif // SL_CATALOG_SENSOR_LIGHT_PRESENT
  #ifdef SL_CATALOG_SENSOR_RHT_PRESENT
    sl_sensor_rht_deinit();
  #endif // SL_CATALOG_SENSOR_RHT_PRESENT
  #ifdef SL_CATALOG_SENSOR_PRESSURE_PRESENT
    sl_sensor_pressure_deinit();
  #endif // SL_CATALOG_SENSOR_PRESSURE_PRESENT
  #ifdef SL_CATALOG_SENSOR_GAS_PRESENT
    sl_sensor_gas_deinit();
  #endif // SL_CATALOG_SENSOR_GAS_PRESENT
  #ifdef SL_CATALOG_SENSOR_SOUND_PRESENT
    sl_sensor_sound_deinit();
  #endif // SL_CATALOG_SENSOR_SOUND_PRESENT
}


sl_status_t sl_service_light_get(float *lux, float *uvi)
{
  sl_status_t sc;
  sc = sl_sensor_light_get(lux, uvi);
  if (SL_STATUS_OK == sc) {
  } else if (SL_STATUS_NOT_INITIALIZED == sc) {
      app_log_info("Ambient light and UV index sensor is not initialized.\r\n");
  } else {
      app_log_info("Light sensor measurement failed.\r\n");
  }
  return sc;
}

sl_status_t sl_service_pressure_get(float *pressure)
{
  sl_status_t sc;
  sc = sl_sensor_pressure_get(pressure);
  if (SL_STATUS_OK == sc) {
  } else if (SL_STATUS_NOT_INITIALIZED == sc) {
      app_log_info("Air Pressure sensor is not initialized.\r\n");
  } else {
      app_log_info("Air Pressure measurement failed.\r\n");
  }
  return sc;
}

sl_status_t sl_service_rht_get(uint32_t *rh, int32_t *t)
{
  sl_status_t sc;
  sc = sl_sensor_rht_get(rh, t);
  if (SL_STATUS_OK == sc) {
  } else if (SL_STATUS_NOT_INITIALIZED == sc) {
      app_log_info("Relative Humidity and Temperature sensor is not initialized.\r\n");
  } else {
      app_log_info("RHT sensor measurement failed.\r\n");
  }
  return sc;
}

sl_status_t sl_service_gas_get(uint16_t *eco2, uint16_t *tvoc)
{
  sl_status_t sc;
  sc = sl_sensor_gas_get(eco2, tvoc);
  if (SL_STATUS_OK == sc) {
  } else if (SL_STATUS_NOT_INITIALIZED == sc) {
      app_log_info("Air quality sensor is not initialized.\r\n");
  } else if (SL_STATUS_NOT_READY == sc) {
      //app_log_info("Air quality sensor measurement failed.\r\n");
  }
  return sc;
}

sl_status_t sl_service_sound_get(float *sound_level)
{
  sl_status_t sc;
  sc = sl_sensor_sound_get(sound_level);
  if (SL_STATUS_OK == sc) {
  } else if (SL_STATUS_NOT_INITIALIZED == sc) {
      app_log_info("Sound level sensor is not initialized.\r\n");
  } else {
      app_log_info("Sound level measurement failed.\r\n");
  }
  return sc;
}
