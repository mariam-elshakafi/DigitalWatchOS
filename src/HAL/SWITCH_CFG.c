#include "Std_Types.h"
#include "GPIO.h"
#include "SWITCH.h"
#include "SWITCH_CFG.h"

const SWITCH_map switches[SWITCH_NUM] = {
                                         {.port = GPIO_PORTB, .pin = GPIO_PIN_1, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTB, .pin = GPIO_PIN_11, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTB, .pin = GPIO_PIN_4, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTC, .pin = GPIO_PIN_13, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTC, .pin = GPIO_PIN_14, .pressedState = GPIO_PIN_RESET},
                                         {.port = GPIO_PORTB, .pin = GPIO_PIN_0, .pressedState = GPIO_PIN_RESET}
                                        };

