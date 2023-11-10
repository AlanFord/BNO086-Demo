# Sparkfun BMO086 IMU with STM32CubeIDE

## Introduction
The objective of this project is to port a CEVA BMO086 example program
to run using I2C on a combination of a Sparkfun BMO086 IMU breakout, a NUCLEO-F401RE board, and STM32CubeIDE project files.

The CEVA BMO086 IMU has a lot of nice features useful with
various projects.  Arduino libraries exist to interface with Sparkfun's BMO086 breakout board, but the arduino interface for the NUCLEO-F401RE doesn't
provide access to all of the peripherals needed for many projects.

Another alternative is CEVA's SH2 sensor module demo.  It targets a NUCLEO-F411 board, a CEVA BNO080 Shield board, and the IAR Embedded Workbench for ARM (EWARM).  Unfortunately, the STM32CubeIDE isn't quite compatible with CEVA's demo software.

Hence, this project is a port of CEVA's SH2 sensor module demo to run
on a NUCLEO-F401RE board using a project configured by the STM32CubeIDE. 

## Using This Software As-Is
 The files should compile and run as-is.  Wiring up the Sparkfun breakout board to the NUCLEO-F401RE is straightforward.  The following pin mapping is used (Board Pin is the STM32 designator, Arduino Pin is, well, the Arduino designator):
 
| Signal | Board Pin | Arduino Pin |
| ------ | --------- | ------------ |
| SCL | PB8 | D15 |
| SDA | PB9 | D14 |
| INT | PA10 | D2 |
| 3V3 | +3V3 | +3V3 |
| GND | GND | GND |

## Rebuilding The Software From Scratch
If you wish to see how this project was constructed, or if you desire to make modifications, the following steps can be used to construct the project.

1. Wire the hardware as shown in the previous section.
2. Create a standard STM32CubeIDE project for a NUCLEO-F4 series board enabling the default peripherals. (Other boards may work, but the wiring and peripherals may change.)
3. Configure the project using the Device Configuration Tool.  Use the following settings to ensure that the necessary CMSIS and HAL files are included in the project.  Any other peripheral settings will be handled by the software.
	* Enable the I2C1 peripheral
	* Enable external interrupt service for pin PA10
	* Enable the TIM2 timer
4. Add the following folders from the sh2-demo-nucleo project:
	* app
	* main
	* sh2
5. For each of the folders in the previous step, right click on the folder in the Project Explorer and "Add/Remove Include Path" to add the folder to the search path for include files.
6. For each of the folders in the prevous step, right click on the folder in the Project Explorer and select "Properties".  In the resulting dialog panel deselect the box labeled "Exclude resource from build".
7. Copy all of the files from the ceva-dsp/sp2 github repository into the sh2 folder.
8. Delete from the Core/Src/ folder the files main.c and syscalls.c.  The functions provided by these files will be provided by files in the app directory.  Note that if the Device Configuration Tool is updated and saved, these files will be regenerated and must be removed again.
9. Delete from the app/ folder the following files.  These files are used for the optional SPI and/or UART IMU interfaces and are not needed for the I2C interface.
	* bno08x_uart_hal.c
	* cal_app.c
	* demo_rvc.c
	* fsp20x_uart_hal.c
	* fsp201_i2c_hal.c
	* spi_hal.c
	* uart_hal.c
	* uart_hal.h
10. Delete from the main/ folder the following files:
	* startup_stm32f411xe.s
	* system_stm32f4xx.c
11. Delete from the dfu/ folder the following files:
	* dfu_fsp200.c
	* firmware-fsp.c
12. Alter the apps/bno08x_i2c_hal.c file to change the line
	```
	return shtp_i2c_hal_init(&sh2_hal, false, ADDR_SH2_0);
	```
	
	to
	
	```
	return shtp_i2c_hal_init(&sh2_hal, false, ADDR_SH2_1);
	```
13. Alter the apps/console.c file to include the line
	```
	#include <stdio.h>
	```
	
	Also change `__read` to `_read` (only one underscore) and `__write` to `_write`.
14. Alter the apps/i2c_hal.c file to comment out the function `EXTI15_10_IRQHandler`.  It is already provided in the file Core/Src/stm32f4xx_it.c.
15. In the project properties, find the MCU Settings and check the box labeled "**Use float with printf from newlib-nano**".

The project should be ready for use!