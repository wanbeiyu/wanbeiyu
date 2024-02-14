#include "wanbeiyu.h"

#include <stdlib.h>

void wby_button_hold(wby_button_t *btn)
{
    if (btn == NULL)
    {
        return;
    }

    btn->gpio->set_low(btn->gpio);
}

void wby_button_release(wby_button_t *btn)
{
    if (btn == NULL)
    {
        return;
    }

    btn->gpio->set_hi_z(btn->gpio);
}

wby_button_t *wby_button_new(wby_gpio_t *gpio)
{
    if (gpio == NULL)
    {
        return NULL;
    }

    wby_button_t *btn = (wby_button_t *)malloc(sizeof(wby_button_t));
    if (btn == NULL)
    {
        return NULL;
    }

    btn->gpio = gpio;

    wby_button_release(btn);

    return btn;
}

void wby_button_delete(wby_button_t *btn)
{
    if (btn == NULL)
    {
        return;
    }

    free(btn);
}