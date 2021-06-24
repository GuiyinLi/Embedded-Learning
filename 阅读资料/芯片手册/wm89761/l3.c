/*
 * L3 code
 *
 *  Copyright (C) 2008, Christian Pellegrin <chripell@evolware.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 * based on:
 *
 * L3 bus algorithm module.
 *
 *  Copyright (C) 2001 Russell King, All Rights Reserved.
 *
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>

#include <sound/l3.h>

/*
 * Send one byte of data to the chip.  Data is latched into the chip on
 * the rising edge of the clock.
 */
static void sendbyte(struct l3_pins *adap, unsigned int byte)
{
	int i;

	for (i = 0; i < 8; i++) {
		adap->setclk(0);
		udelay(adap->data_hold);
		adap->setdat(byte & 1);
		udelay(adap->data_setup);
		adap->setclk(1);
		udelay(adap->clock_high);
		byte >>= 1;
	}
}

/*
 * Send a set of bytes to the chip.  We need to pulse the MODE line
 * between each byte, but never at the start nor at the end of the
 * transfer.
 */
static void sendbytes(struct l3_pins *adap, const u8 *buf,
		      int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (i) {
			udelay(adap->mode_hold);
			adap->setmode(0);
			udelay(adap->mode);
		}
		adap->setmode(1);
		udelay(adap->mode_setup);
		sendbyte(adap, buf[i]);
	}
}

int l3_write(struct l3_pins *adap, u8 addr, u8 *data, int len)
{
	adap->setclk(1);
	adap->setdat(1);
	adap->setmode(1);
	udelay(adap->mode);

	adap->setmode(0);
	udelay(adap->mode_setup);
	sendbyte(adap, addr);
	udelay(adap->mode_hold);

	sendbytes(adap, data, len);

	adap->setclk(1);
	adap->setdat(1);
	adap->setmode(0);

	return len;
}

/* hcj: mimick for the l3 */
int l3_write1(struct l3_pins *adap, u8 addr, u8 data, int len)
{
	int i,j;
	adap->setmode(1);
	adap->setclk(1);
	adap->setmode(1);
	adap->setclk(1);

	for(j=0; j<100; j++);

	for(i=0; i<8; i++)
	{
		if(addr&0x80)
		{
			adap->setclk(0);
			adap->setdat(1);
			for(j=0; j<10; j++);
			adap->setclk(1);
			for(j=0; j<10; j++);
		}
		else
		{
			adap->setclk(0);
			adap->setdat(0);
			for(j=0; j<10; j++);
			adap->setclk(1);
			for(j=0; j<10; j++);
		}
		addr<<=1;
	}

	for(i=0; i<8; i++)
	{
		if(data&0x80)
		{
			adap->setclk(0);
			adap->setdat(1);
			for(j=0; j<10; j++);
			adap->setclk(1);
			for(j=0; j<10; j++);
		}
		else
		{
			adap->setclk(0);
			adap->setdat(0);
			for(j=0; j<10; j++);
			adap->setclk(1);
			for(j=0; j<10; j++);
		}
		data<<=1;
	}

	adap->setmode(0);
	for(j=0; j<1000; j++);
	adap->setmode(1);
	adap->setclk(1);
	return 0;
}

int l3_startup(struct l3_pins *adap)\
{
	adap->setmode(1);
	adap->setclk(1);
	adap->setdat(0);
	return 0;
}
	

EXPORT_SYMBOL_GPL(l3_write);

MODULE_DESCRIPTION("L3 bit-banging driver");
MODULE_AUTHOR("Christian Pellegrin <chripell@evolware.org>");
MODULE_LICENSE("GPL");
