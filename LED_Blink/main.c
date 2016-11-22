
/*
	22/11/2016
	This is a first project with the beaglebone black device.
	There are 4 LEDs on the device (nead the ethernet connector) and we make them blink
	at a certain frequency (just a loop actually)
*/


/* Hardware definitions, these can be found at the Arm Cortex A8, Technical Reference Manual, section memory map */

//The four led's we are looking for are connected on the port GPIO1 (from BBB-datasheet) (pins 21, 22,23 and 24)
#define GPIO1_BASE		0x4804C000 	//this is the base address of GPIO1 (tmr doc, memory map section)

/**** used to enable output capabilities, at reset, all pins are configured as inputs ( clear to zero the pins if you want them as ouput) ***/
#define GPIO_OE			0x134	

/*** GPIO_SETDATAOUT and GPIO_CLRDATAOUT registers are uset to set/clear the bit selected, 
	a zero takes no effect, a one sets/clears the corrisponding bit ***/	
#define GPIO_CLRDATAOUT	0x190
#define GPIO_SETDATAOUT	0x194



#define CM_PER_BASE				0x44e00000	//L4 WKUP peripheral map, CM_PER (Clock Module Peripheral Registers)
#define CM_PER_GPIO1_CLKCTRL	0xAC		//offset (CM_PER_GPIO1_CLKCTRL), this register manages the GPIO1 clocks

#define Delay 100000000

void main (void)
{
	unsigned int port_dir;
	unsigned int i;
	// Bit 18: OPTFCLKEN_GPIO_1_GDBCLK, 0x1 = FCLK_EN : Optional functional clock is enabled
	// Bits 1-0: 0x2 = ENABLE : Module is explicitly enabled, control TMR for more infos, page 581
	*((unsigned int *)(CM_PER_BASE+CM_PER_GPIO1_CLKCTRL)) = ((1<<18) | 2);

	//now we have set the GPIO1 Clocks, now we need to set the port direction, we read the actual register, and clear the bits 21-24
	port_dir = *((unsigned int *)(GPIO1_BASE+GPIO_OE));		//get the OE_REG and set the ports as outputs
	port_dir &= ~(15<<21);					//GPIO1(21,22,23,24) are used on this board as led driver, set these as zero (output)
	*((unsigned int *)(GPIO1_BASE+GPIO_OE)) = port_dir;		//this clears the pins 21-24 to set them as outputs

	while(1)
	{
		*((unsigned int *)(GPIO1_BASE+GPIO_SETDATAOUT)) = (15<<21);
		for(i = 0; i < Delay; i ++);
		*((unsigned int *)(GPIO1_BASE+GPIO_CLRDATAOUT)) = (15<<21);
		for(i = 0; i < Delay; i ++);
	}
	return;
}




