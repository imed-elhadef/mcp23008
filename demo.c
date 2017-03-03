#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "mcp23008.h"
#include <wiringPi.h>

#define MYFLAG  0x30
#define BADFLAG 0xFF

mcp23008 mcp23008_dev;
const char *I2CDEV = "/dev/i2c-1"; 
static volatile int handlerFlag=0;

void InterruptHandler (void)
 {
 handlerFlag++;
 if (handlerFlag==1)
 handlerFlag=MYFLAG;
 else 
 handlerFlag=BADFLAG;
 //printf("global counter=%d\n",globalCounter);
 }

int main()
{
        char buffer[12];
        char  interrupt_status;//read the GPIO number where the interrupt was triggered
        char  intterrupt_capture;//read the gpio status when the interrut was occured 

	printf("Start Program \n");
        //Configure mcp23008 INT pin for Raspberry 
        wiringPiSetup ();
        pinMode(16, INPUT);// Set call button as INPUT
        pullUpDnControl(16, PUD_DOWN);// Enable pull-down resistor on button
        wiringPiISR (27, INT_EDGE_RISING, &InterruptHandler) ;//ISR handler config

	//Open the mcp23008 I2C GPIO Expander
        mcp23008_open(I2CDEV,MCP23008_ADR,&mcp23008_dev);  
        //Set GPIO direction
        mcp23008_write_byte(&mcp23008_dev,MCP23008_IODIR,IODIR_MASK);  //2 Inputs and others are outputs

        //----------Init Interruption-------------------//
        mcp23008_write_byte(&mcp23008_dev,MCP23008_GPINTEN,GPINTEN_MASK);// The interruption was activated for GP7 and GP6 pins 
        mcp23008_write_byte(&mcp23008_dev,MCP23008_DEFVAL,DEFVAL_MASK);// The default value for GP7 and GP6 pins is 1  
        mcp23008_write_byte(&mcp23008_dev,MCP23008_INTCON,INTCON_MASK);// The interruption will occur when the default value will change
        //-------------------------------------------------//

        puts("--->If you want to active the relay write: Relay\n--->If you want to active the led write: LED\n--->If you want to work with the interruption mode write: Interrupt");

        scanf("%s",buffer);

        if (!strcmp("Relay",buffer))
         {
           printf("Relay is activated for 1 second!!!\n");
           mcp23008_write_byte(&mcp23008_dev,MCP23008_GPIO,RELAY_MASK);//Active relay
           sleep(1);
           mcp23008_write_byte(&mcp23008_dev,MCP23008_GPIO,DEACTIVATE_MASK);//Deactive relay
           exit(0);
         }

        else if (!strcmp("LED",buffer))
         {
           printf("LED is activated for 1 second!!!\n");           
           mcp23008_write_byte(&mcp23008_dev,MCP23008_GPIO,LED_MASK );//Active LED
           sleep(1);
           mcp23008_write_byte(&mcp23008_dev,MCP23008_GPIO,DEACTIVATE_MASK );//Deactive LED
           exit(0);
         }
        
        else if (!strcmp("Interrupt",buffer))
         {
           printf("You are in Interrupt mode!!!\n");
         }
        
        else
         {
          printf("You didn't write the right argument!!!\n");
          exit(0);
         }

	while(1)
	{
         //Nothing
          if(handlerFlag==MYFLAG)
           {   
            printf("Interrupt was occured\n");
            //sleep(1);
            interrupt_status=mcp23008_read_byte(&mcp23008_dev,MCP23008_INTF);//read the GPIO number where the interrupt was triggered
            if(interrupt_status & POWER_BUTTON_MASK)
            //power button was bushed
            system("sudo poweroff");
            else if(interrupt_status & PUSH_SENSOR_MASK )
            //push sensor is on
            printf("do an action here!!!\n);  
            intterrupt_capture=mcp23008_read_byte(&mcp23008_dev,MCP23008_INTCAP);//read the gpio status when the interrut was occured
            handlerFlag=0;
           } 
            		
	}

	return 0;
}

