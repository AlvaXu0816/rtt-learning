/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-22     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#define LED_PIN GET_PIN(C,13)
#include <rtdbg.h>

int main(void)
{
    int count = 1;

    rt_kprintf("Hello from rt_kprintf!\n");

    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED_PIN, PIN_LOW);
        LOG_D("LED ON");
        rt_thread_mdelay(1000);

        rt_pin_write(LED_PIN, PIN_HIGH);
        LOG_D("LED OFF");
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
