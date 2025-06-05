/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

/*
 * Get button configuration from the devicetree sw0 alias. This is mandatory.
 */
#define SW0_NODE	DT_ALIAS(sw0)
#if !DT_NODE_HAS_STATUS_OKAY(SW0_NODE)
#error "Unsupported board: sw0 devicetree alias is not defined"
#endif

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET_OR(SW0_NODE, gpios,
	{0});
static struct gpio_callback button_cb_data;

void button_pressed(const struct device *dev, struct gpio_callback *cb,
	uint32_t pins)
{
printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
}

int main(void)
{
	printf("my_project! %s\n", CONFIG_BOARD_TARGET);

	int ret;
	if (!gpio_is_ready_dt(&button)) {
		printk("Error: button device %s is not ready\n",
		       button.port->name);
		return 0;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, button.port->name, button.pin);
		return 0;
	}

	ret = gpio_pin_interrupt_configure_dt(&button,
		GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
	printk("Error %d: failed to configure interrupt on %s pin %d\n",
	ret, button.port->name, button.pin);
	return 0;
	}

	gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
	gpio_add_callback(button.port, &button_cb_data);
	printk("Set up button at %s pin %d\n", button.port->name, button.pin);

	while ( 1 )
	{
		k_msleep(1000);
		printf("my_project! %s\n", CONFIG_BOARD_TARGET);
		int val = gpio_pin_get_dt(&button);

		/*if (val >= 0) {
			printf("press button\n"); 
		}*/
	}
	
	return 0;
}
