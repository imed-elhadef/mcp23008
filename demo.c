#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "mcp23008.h"

mcp23008 mcp23008_dev;
const char *I2CDEV = "/dev/i2c-1"; 

int main()
{
  int i;

	printf("Start Program \n");
	
        mcp23008_open(I2CDEV,MCP23008_ADR,&mcp23008_dev);  //Open the mcp23008 I2C GPIO Expander
        //Set GPIO direction
        mcp23008_write_byte(&mcp23008_dev,MCP23008_IODIR,IODIR_MASK);  //2 Inputs and others are outputs

        //Init Interruption
        mcp23008_write_byte(&mcp23008_dev,MCP23008_GPINTEN,GPINTEN_MASK);
        
	while(1)
	{
         //Nothing
		
	}

	return 0;
}

