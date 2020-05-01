#include "Std_Types.h"
#include "GPIO.h"
#include "SWITCH.h"
#include "SWITCH_CFG.h"

const SWITCH_map switches[SWITCH_NUM] = {
                                         {.port = GPIO_PORTA, .pin = GPIO_PIN_0, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTA, .pin = GPIO_PIN_1, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTA, .pin = GPIO_PIN_2, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTA, .pin = GPIO_PIN_3, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTA, .pin = GPIO_PIN_4, .pressedState = GPIO_PIN_RESET},
										 {.port = GPIO_PORTA, .pin = GPIO_PIN_5, .pressedState = GPIO_PIN_RESET}
                                        };

