/**
 * @file SWITCH_CFG.h
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is a user interface for the Switch Handler (with and without OS)
 * @version 0.1
 * @date 2020-04-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SWITCH_CFG_H
#define SWITCH_CFG_H

/**
 * @brief This macro configures the switch handler to work with OS
 * This must be commented out if no OS is to be used
 */
#define SWITCH_SCHED_ACTIVE

/**
 * @brief defines number of switches
 */
#define SWITCH_NUM 6

/**
 * @brief This is the counter thresholde used inside SWITCH_runnable
 * Note that the periodicity for the SWITCH_Task * SWITCH_COUNTER_THRESHOLD must be equal to debounce time (20 ms)
 * 
 */
#define SWITCH_COUNTER_THRESHOLD 5

/**
 * @brief This section defines Switch IDs
 * 
 */
#define SWITCH_CFG      0
#define SWITCH_INC      1
#define SWITCH_DEC      2
#define SWITCH_RIGHT    3
#define SWITCH_LEFT     4
#define SWITCH_DATE     5


/**
 * @brief This struct is used in SWITCH_CFG.c to configure switch pins
 * 
 */
typedef struct
{
  void* port;
  u32 pin;
  u8 pressedState;
} SWITCH_map;

#endif
