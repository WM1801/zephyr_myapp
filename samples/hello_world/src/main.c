/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	while ( 1 )
	{
		k_msleep(1000);
		printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	}
	
	return 0;
}
