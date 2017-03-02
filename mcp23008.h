/****************************************************************************/
  //   File name           : (C) by 2017 Imed Elhadef
 //   Copyright            : (C) by 2017 Imed Elhadef
 //   Contact:              imed.elhadef@arcangel.fr  
  
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _MCP23008_H_
#define _MCP23008_H_
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdint.h>


#define MCP23008_ADR               0x20// The three pins A0,A1 et A2 are connected to GND 

//Internal Registers
#define MCP23008_IODIR             0x00
#define MCP23008_IPOL              0x01
#define MCP23008_GPINTEN           0x02
#define MCP23008_DEFVAL            0x03
#define MCP23008_INTCON 	   0x04
#define MCP23008_IOCON 	           0x05
#define MCP23008_GPPU  	           0x06
#define MCP23008_INTF	           0x07
#define MCP23008_INTCAP 	   0x08
#define MCP23008_GPIO   	   0x09
#define MCP23008_OLAT    	   0x0A

//Mask Bytes

#define IODIR_MASK                  0xC0 //0b11000000 
#define GPINTEN_MASK                0xC0 //0b11000000


typedef struct _i2c_device
{
	char *dev; 	// device file i.e. /dev/i2c-N
	int addr;	// i2c address
	int fd;		// file descriptor
} mcp23008;

/*
 * opens the mcp23008 device at [dev_fqn] (i.e. /dev/i2c-N) whose address is
 * [addr] and set the mcp23008
 */
int mcp23008_open(char *dev_fqn, int addr, mcp23008 *e);
/*
 * closes the mcp23008 device [e] 
 */
int mcp23008_close(mcp23008 *e);

/*
 * read and returns the mcp23008 byte at reg address [reg_addr] 
 * Note: mcp23008 must have been selected by ioctl(fd,I2C_SLAVE,address) 
 */
int mcp23008_read_byte(mcp23008* e, __u8 reg_addr);
/*
 * read the current byte
 * Note: mcp23008 must have been selected by ioctl(fd,I2C_SLAVE,address) 
 */
int mcp23008_read_current_byte(mcp23008 *e);
/*
 * writes [data] at reg address [reg_addr] 
 * Note: mcp23008 must have been selected by ioctl(fd,I2C_SLAVE,address) 
 */
int mcp23008_write_byte(mcp23008 *e, __u8 reg_addr, __u8 data);



#endif

