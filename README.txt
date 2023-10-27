Creation steps.
1) Create a standard STM32CubeIDE project for a NUCLEO-F401RE board.
2) Configure the project using the Device Configuration Tool with the following settings.  These settings
	will ensure that the appropriate CMSIS and HAL files are included in the project.  The settings
	are consistent with the configuration specified in the sh2-demo app.
	Enable the following GPIO Pins:
		CLKSEL0_PIN:    PA8
		RSTN_PIN:	    PB4
		BOOTN_PIN:	    PB5
		PS0_WAKEN_PIN:  PB10
		PS1_PIN:	    PB0
		INTN_PIN:	    PA10
	Enable interrupt service for the following pin:
		INTN_PIN:	    PA10
	Enable the following peripherals:
		I2C Peripheral: I2C1
			I2C1_SCL ==> PB8
			I2C1_SDA ==> PB9
		IMU Timer:		TIM2
			
3) Add the following folders from the sh2-demo-nucleo project:
	 app
	 main
	 sh2
4) For each of the folders in the previous step, right click on the folder in
   the Project Explorer and "Add/Remove Include Path" to add the folder to the
   search path for include files.
5) For each of the folders in the previous step, right click on the folder in
   the Project Explorer and select "Properties".  In the resulting dialog panel
   deselect the box labled "Exclude resource from build".
6) Copy all of the files from the ceva-dsp/sp2 github repository into the sh2 directory.

			
7) STM32CUBEIDE template files to delete:
	  Core/Src folder:
	    main.c (Note: this file will be regenerated every time the STM32Cube configurator is run
	    	and saved.  Remember to delete this file each time it is created.)
	    syscalls.c (_read and _write will be supplied by apps/console.c)
8) sh2-demo-nucleo files to detete:
	  app folder:
	  	bno08x_uart_hal.c
	  	cal_app.c
	  	demo_rvc.c
	  	fsp20x_uart_hal.c
	  	fsp201_i2c_hal.c
	  	spi_hal.c
	  	uart_hal.c
	  	uart_hal.h
	  main folder:
	    startup_stm32f411xe.s
	    system_stm32f4xx.c
	  dfu folder:
	    dfu_fsp200.c
	    firmware-fsp.c
9) Code Mods:
	In apps/bno08x_i2c_hal.c, change
		return shtp_i2c_hal_init(&sh2_hal, false, ADDR_SH2_0);
	to
		return shtp_i2c_hal_init(&sh2_hal, false, ADDR_SH2_1);
		
	In apps/console.c,
	add
		#include <stdio.h>
	change
		__read to _read (note the number of underscores)
	change 
		__write to _write
	
	In apps/i2c_hal.c, comment out the function EXTI15_10_IRQHandler.  It is
		already provided in the file Core/Src/stm32f4xx_it.c
	 
10) In the project properties, find the MCU Settings and check the box labeled
	"Use float with printf from newlib-nano"
