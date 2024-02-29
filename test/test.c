#include <wanbeiyu.h>
#include "test.h"

#include <stdio.h>

#include "button.h"
#include "hat.h"
#include "slidepad.h"
#include "touchscreen.h"

int main(void)
{
    int cnt = 0;

    cnt += test_button();
    cnt += test_hat();
    cnt += test_slidepad();
    cnt += test_touchscreen();

    if (cnt == 0)
    {
        printf("%sOK%s\n", TEXT_GREEN, TEXT_RESET);
        return 0;
    }
    else
    {
        fprintf(stderr, "%s%d errors found%s\n", TEXT_RED, cnt, TEXT_RESET);
        return 1;
    }
}