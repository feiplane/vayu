/*
 * LED Core
 *
 * Copyright 2005 Openedhand Ltd.
 *
 * Author: Richard Purdie <rpurdie@openedhand.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#ifndef __LEDS_H_INCLUDED
#define __LEDS_H_INCLUDED

#include <linux/rwsem.h>
#include <linux/leds.h>

static inline int led_get_brightness(struct led_classdev *led_cdev)
{
	return led_cdev->brightness;
}

static inline struct led_classdev *trigger_to_lcdev(struct led_trigger *trig)
{
	struct led_classdev *led_cdev;

	read_lock(&trig->leddev_list_lock);
	list_for_each_entry(led_cdev, &trig->led_cdevs, trig_list) {
		if (!strcmp(led_cdev->default_trigger, trig->name)) {
			read_unlock(&trig->leddev_list_lock);
			return led_cdev;
		}
	}

	read_unlock(&trig->leddev_list_lock);
	return NULL;
}

void led_init_core(struct led_classdev *led_cdev);
void led_stop_software_blink(struct led_classdev *led_cdev);
void led_set_brightness_nopm(struct led_classdev *led_cdev,
				enum led_brightness value);
void led_set_brightness_nosleep(struct led_classdev *led_cdev,
				enum led_brightness value);

extern struct rw_semaphore leds_list_lock;
extern struct list_head leds_list;
extern struct list_head trigger_list;
extern const char * const led_colors[LED_COLOR_ID_MAX];

#endif	/* __LEDS_H_INCLUDED */
