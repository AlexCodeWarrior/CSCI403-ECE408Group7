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
//	char *data = (char*) malloc(32);

//	for(uint8_t i=0;i<64;i++){
//		oled.clear();
//		oled.draw_hline(0, i, 100, WHITE);
//		sprintf(data,"%d",i);
//		oled.draw_string(105, 10, string(data), BLACK, WHITE);
//		oled.refresh(false);
//		vTaskDelay(1000 / portTICK_PERIOD_MS);
//	}
	while (1) {
		oled.clear();

		// put name
		os.str("");

		os << "**Name**" ;


		oled.select_font(1);

		oled.draw_string(0, 0, os.str(), WHITE, BLACK);

		oled.refresh(true);

		vTaskDelay(1000 / portTICK_PERIOD_MS);

		// Added
		oled.clear();

		oled.refresh(true);

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
//		oled.draw_rectangle(10, 30, 20, 20, WHITE);
//		oled.select_font(0);
//		//deprecated conversion from string constant to 'char*'
//		oled.draw_string(0, 0, "glcd_5x7_font_info", WHITE, BLACK);
//		ESP_LOGI("OLED", "String length:%d",
//				oled.measure_string("glcd_5x7_font_info"));
//		oled.select_font(1);
//		oled.draw_string(0, 18, "tahoma_8pt_font_info", WHITE, BLACK);
//		ESP_LOGI("OLED", "String length:%d",
//				oled.measure_string("tahoma_8pt_font_info"));
//		oled.draw_string(55, 30, "Hello ESP32!", WHITE, BLACK);
//		oled.refresh(true);
//		vTaskDelay(3000 / portTICK_PERIOD_MS);
		xTaskCreatePinnedToCore(&myTask, "Name", 2048, NULL, 5, NULL, 1);
	} else {
		ESP_LOGE("OLED", "oled init failed");
	}
}
#ifdef __cplusplus
}
#endif
