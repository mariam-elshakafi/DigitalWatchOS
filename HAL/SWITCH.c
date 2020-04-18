/**
 * @file SWITCH.c
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is an implementation for a Switch Handler (with and without OS)
 * @version 0.1
 * @date 2020-04-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "Std_Types.h"

#include "GPIO.h"
#include "SWITCH_CFG.h"
#include "SWITCH.h"

#include "SCHED.h"

/**
 * @brief This is the switch task to be called by the scheduler
 * 
 */
Task_t SWITCH_Task = {SWITCH_runnable, 0, 4};


extern const SWITCH_map switches[SWITCH_NUM];
static GPIO_initStruct switchGPIO_Obj[SWITCH_NUM];
static SWITCH_state[SWITCH_NUM];


/**
 * @brief Initializes switch pin as either pull-up or pull-down according to SWITCH_CFG.c, and enables its clock
 * *This API must be called before attempting any other SWITCH APIs
 * 
 */
void SWITCH_init(void)
{
  u8 swCount = 0;
  GPIO_initStruct sw;
  for(swCount = 0; swCount < SWITCH_NUM; swCount++)
  {
    sw.port = switches[swCount].port;
    sw.pin = switches[swCount].pin;
    sw.speed = GPIO_INPUT;
    
    if((switches[swCount].pressedState) == GPIO_PIN_RESET)
    {
      sw.mode = GPIO_INPUT_PULL_UP;
    }
    else if((switches[swCount].pressedState) == GPIO_PIN_SET)
    {
      sw.mode = GPIO_INPUT_PULL_DOWN;
    }
    switchGPIO_Obj[swCount] = sw;
    /*TODO: Call HRCC API to enable GPIO clock*/
    GPIO_init(&sw);
  }
}

/**
 * @brief Get switch state (Pressed or released)
 * 
 * @param swID  This is the switch number obtained from SWITCH_CFG.h
 *                 @arg SWITCH_INC
 *                 @arg SWITCH_DEC
 *                 @arg SWITCH_RIGHT
 *                 @arg SWITCH_LEFT
 *                 @arg SWITCH_OK
 *
 * @return u8 switchState
 *                 SWITCH_PRESSED 
 *                 SWITCH_RELEASED
 */
u8 SWITCH_readSwitchState(u8 swID)
{
  u8 switchState;
  #ifdef SWITCH_SCHED_ACTIVE
  switchState = (SWITCH_state[swID] == switches[swID].pressedState);
  #else
  switchState = (GPIO_readPin(&switchGPIO_Obj[swID], switches[swID].pin) == switches[swID].pressedState);
  #endif
  return switchState;
}


/**
 * @brief This is the switch runnable to be used with OS
 * This must be called periodically to update switch states.
 * Note that the periodicity for this task * SWITCH_COUNTER_THRESHOLD must be equal to debounce time (20 ms)
 * 
 */
void SWITCH_runnable(void)
{
  static u8 prevState[SWITCH_NUM];
  static u8 counter[SWITCH_NUM];
  u8 swID, currentState;
  for (swID = 0; swID < SWITCH_NUM; swID++)
  {
    currentState = GPIO_readPin(&switchGPIO_Obj[swID], switches[swID].pin);
    if (currentState == prevState[swID])
    {
      counter[swID]++;
    }
    else
    {
      counter[swID] = 0;
    }

    if (counter[swID] == SWITCH_COUNTER_THRESHOLD)
    {
       SWITCH_state[swID] = currentState;
       counter[swID] = 0;
    }
    prevState[swID] = currentState;
  }



}
