#ifndef __UTILS_H
#define __UTILS_H

#include "common_includes.h"

#define MAX_TRACE_OUTPUT 256

#define PIN_UP(pin_name) HAL_GPIO_WritePin(pin_name ## _GPIO_Port, pin_name ## _Pin, GPIO_PIN_SET)
#define PIN_DOWN(pin_name) HAL_GPIO_WritePin(pin_name ## _GPIO_Port, pin_name ## _Pin, GPIO_PIN_RESET)
#define PIN_TOGGLE(pin_name) HAL_GPIO_TogglePin(pin_name ## _GPIO_Port, pin_name ## _Pin)

#define NOW HAL_GetTick()

uint16_t calculate_crc(uint8_t* buffer, uint32_t buffer_size);





#ifdef __cplusplus
static uint32_t __attribute__((unused)) trace_message_id = 0;
#define trace(fmt, ...) \
{ \
	char fmt_msg[MAX_TRACE_OUTPUT]; \
	sprintf(fmt_msg, fmt, ##__VA_ARGS__); \
	trace_printf("[%ld]%-100s\r\n", trace_message_id++, fmt_msg); \
}
#else
void trace(const char* template, ...);
#endif

char* buffer_to_string(char* output, int max_output_length, uint8_t* data, int length);
uint16_t q97angle2motor_position(uint16_t q97angle);
uint16_t motor_position2q97angle(uint16_t motor_position);
uint16_t angle2q97angle(float angle);
float q97angle2angle(uint16_t angle);
char* float_to_string(float number);
uint16_t uint8angle2q97angle(uint8_t angle);
float motor_position2angle(uint16_t motor_position);

// uncomment for creating another crc table
//make_crc_table(crc_poly);

#endif
