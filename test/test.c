#include <wanbeiyu.h>
#include "test.h"

#include <stdio.h>

#include "button.h"
#include "hat.h"
#include "slidepad.h"
#include "touchscreen.h"

int main(void)
{
    Test tests[] = {test_button,
                    test_hat,
                    test_slidepad,
                    test_touchscreen};

    TEST_RUN(tests);
}