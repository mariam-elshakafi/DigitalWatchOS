# DigitalWatchOS
A digital watch implemented on 2 micro-controllers (STM32) using OS and UART communication

### Descripition
2 microcontrollers (STM32), each connected to 6 switches and LCD that displays time. 
The buttons are as follows:

> 1. **Configuration button** - to enter/exit configuration mode.

> 2. **Move right button** - used in configuration mode to move cursor from hours to minutes to seconds.
     
> 3. **Move left button** - used in configuration mode to move cursor from seconds to minutes to hours.
     
> 4. **Increment button** - used in configuration mode to increment the current field.
     
> 5. **Decrement button** - used in configuration mode to decrement the current field.
     
> 6. **Date button** - As long as this button is pressed, the watch shall display Date (but when released, the current time should be displayed correctly).

UART (using DMA) is used for communication between both MCUs.

### Static Architecture
![Static Architecture](../assets/WatchStaticArch.png?raw=true)