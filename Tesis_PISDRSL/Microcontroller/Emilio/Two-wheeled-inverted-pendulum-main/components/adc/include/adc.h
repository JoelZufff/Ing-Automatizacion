#include <stdio.h>
#include <stdint.h>
#include "esp_err.h"
#include "esp_log.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

static const char adc_tag[] = "ADC";

#define PIN_NUM_MISO      41
#define PIN_NUM_MOSI      40
#define PIN_NUM_CLK       42
#define PIN_NUM_CS        39

static spi_device_handle_t spi_handle;

void init_adc();
void read_adc(uint16_t data[8]);

