#include "esp_log.h"
#include "fonts.h"
#include "ssd1306.hpp"
#include "driver/gpio.h"
//#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

OLED oled = OLED(GPIO_NUM_4, GPIO_NUM_5, SSD1306_128x64);

void myTask(void *pvParameters) {


	ostringstream os;


	while (1) {

		// clear oled screen

		oled.clear();

		// initialize string  stream
		os.str("");

		// append string to stream
		os << "Hello World" ;

   // select font type
		oled.select_font(1);

   // draw string
		oled.draw_string(0, 0, os.str(), WHITE, BLACK);

		// refresh
		oled.refresh(true);


    // delay one second
		vTaskDelay(1000 / portTICK_PERIOD_MS);

		// clear screen
		oled.clear();

    // refresh screen
		oled.refresh(true);

   // delay one second
		vTaskDelay(1000 / portTICK_PERIOD_MS);


	}

}

#ifdef __cplusplus
extern "C" {
#endif
void app_main() {

	oled = OLED(GPIO_NUM_4, GPIO_NUM_5, SSD1306_128x64);
	if (oled.init()) {

		ESP_LOGI("OLED", "oled inited");


		xTaskCreatePinnedToCore(&myTask, "Name", 2048, NULL, 5, NULL, 1);
	} else {
		ESP_LOGE("OLED", "oled init failed");
	}
}
#ifdef __cplusplus
}
#endif
