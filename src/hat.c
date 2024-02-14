#include "wanbeiyu.h"

#include "stdlib.h"

void wby_hat_hold(wby_hat_t *hat, wby_hat_direction_t direction)
{
    if (hat == NULL)
    {
        return;
    }

    switch (direction)
    {
    case WBY_HAT_UP:
        wby_button_hold(hat->up);
        wby_button_release(hat->right);
        wby_button_release(hat->down);
        wby_button_release(hat->left);
        break;
    case WBY_HAT_UPRIGHT:
        wby_button_hold(hat->up);
        wby_button_hold(hat->right);
        wby_button_release(hat->down);
        wby_button_release(hat->left);
        break;
    case WBY_HAT_RIGHT:
        wby_button_release(hat->up);
        wby_button_hold(hat->right);
        wby_button_release(hat->down);
        wby_button_release(hat->left);
        break;
    case WBY_HAT_DOWNRIGHT:
        wby_button_release(hat->up);
        wby_button_hold(hat->right);
        wby_button_hold(hat->down);
        wby_button_release(hat->left);
        break;
    case WBY_HAT_DOWN:
        wby_button_release(hat->up);
        wby_button_release(hat->right);
        wby_button_hold(hat->down);
        wby_button_release(hat->left);
        break;
    case WBY_HAT_DOWNLEFT:
        wby_button_release(hat->up);
        wby_button_release(hat->right);
        wby_button_hold(hat->down);
        wby_button_hold(hat->left);
        break;
    case WBY_HAT_LEFT:
        wby_button_release(hat->up);
        wby_button_release(hat->right);
        wby_button_release(hat->down);
        wby_button_hold(hat->left);
        break;
    case WBY_HAT_UPLEFT:
        wby_button_hold(hat->up);
        wby_button_release(hat->right);
        wby_button_release(hat->down);
        wby_button_hold(hat->left);
        break;
    case WBY_HAT_NEUTRAL:
        wby_button_release(hat->up);
        wby_button_release(hat->right);
        wby_button_release(hat->down);
        wby_button_release(hat->left);
        break;
    default:
        return;
    }
}

void wby_hat_release(wby_hat_t *hat)
{
    if (hat == NULL)
    {
        return;
    }

    wby_hat_hold(hat, WBY_HAT_NEUTRAL);
}

wby_hat_t *wby_hat_new(wby_button_t *up, wby_button_t *right, wby_button_t *down, wby_button_t *left)
{
    if (up == NULL || right == NULL || down == NULL || left == NULL)
    {
        return NULL;
    }

    wby_hat_t *hat = (wby_hat_t *)malloc(sizeof(wby_hat_t));
    if (hat == NULL)
    {
        return NULL;
    }

    hat->up = up;
    hat->right = right;
    hat->down = down;
    hat->left = left;

    wby_hat_release(hat);

    return hat;
}

void wby_hat_delete(wby_hat_t *hat)
{
    if (hat == NULL)
    {
        return;
    }

    free(hat);
}