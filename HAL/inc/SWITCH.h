/**
 * @file SWITCH.h
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is a user interface for the Switch Handler (with and without OS)
 * @version 0.1
 * @date 2020-04-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SWITCH_H
#define SWITCH_H


/**
 * @brief These are the values returned by u8 SWITCH_readSwitchState API
 * 
 */
#define SWITCH_PRESSED      1
#define SWITCH_RELEASED     0


/**
 * @brief Initializes switch pin as either pull-up or pull-down according to SWITCH_CFG.c, and enables its clock
 * *This API must be called before attempting any other SWITCH APIs
 * 
 */
void SWITCH_init(void);

/**
 * @brief Get switch state (Pressed or released)
 * 
 * @param swID  This is the switch number obtained from SWITCH_CFG.h
 *                 @arg SWITCH_CFG
 *                 @arg SWITCH_INC
 *                 @arg SWITCH_DEC
 *                 @arg SWITCH_RIGHT
 *                 @arg SWITCH_LEFT
 *                 @arg SWITCH_DATE
 *
 * @return u8 switchState
 *                 SWITCH_PRESSED 
 *                 SWITCH_RELEASED
 */
u8 SWITCH_readSwitchState(u8 swID);

/**
 * @brief This is the switch runnable to be used with OS
 * This must be called periodically to update switch states.
 * Note that the periodicity for this task * SWITCH_COUNTER_THRESHOLD must be equal to debounce time (20 ms)
 * 
 */
void SWITCH_runnable(void);

#endif
