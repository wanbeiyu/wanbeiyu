#ifndef TEST_H
#define TEST_H

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <errno.h>
#ifndef __STDC_LIB_EXT1__
typedef int errno_t;
#endif

#include <wanbeiyu.h>

#define TEST_TEXT_RED "\e[31m"
#define TEST_TEXT_GREEN "\e[32m"
#define TEST_TEXT_RESET "\e[0m"

typedef int (*Test)(void);

#define TEST_RUN(tests)                                                                       \
    int TEST_COUNT = 0;                                                                       \
    for (size_t TEST_INDEX = 0; TEST_INDEX < sizeof((tests)) / sizeof(Test); TEST_INDEX++)    \
    {                                                                                         \
        TEST_COUNT += (tests)[TEST_INDEX]();                                                  \
    }                                                                                         \
    if (TEST_COUNT == 0)                                                                      \
    {                                                                                         \
        printf("%sOK%s\n", TEST_TEXT_GREEN, TEST_TEXT_RESET);                                 \
        return 0;                                                                             \
    }                                                                                         \
    else                                                                                      \
    {                                                                                         \
        fprintf(stderr, "%s%d errors found%s\n", TEST_TEXT_RED, TEST_COUNT, TEST_TEXT_RESET); \
        return 1;                                                                             \
    }

#define TEST_VAR_NAME(var) #var

#define TEST_FOR(cases)         \
    printf("* %s\n", __func__); \
    int TEST_COUNT = 0;         \
    int TEST_STEP = 0;          \
    TestCase *TEST_CASE;        \
    for (size_t TEST_INDEX = 0; TEST_STEP = 0, TEST_CASE = &(cases)[TEST_INDEX], TEST_INDEX < sizeof((cases)) / sizeof(TestCase); TEST_INDEX++)

#define TEST_ASSERT_EQUAL_INT(expected, actual)                                               \
    if ((expected) != (actual))                                                               \
    {                                                                                         \
        fprintf(stderr, "%sindex: %d, step: %d, expected: %d, actual: %d%s\n",                \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, (expected), (actual), TEST_TEXT_RESET); \
        TEST_COUNT++;                                                                         \
        continue;                                                                             \
    }                                                                                         \
    TEST_STEP++;

#define TEST_ERRNO_T(err) ((err) == 0        ? "OK"                  \
                           : (err) == EIO    ? TEST_VAR_NAME(EIO)    \
                           : (err) == EINVAL ? TEST_VAR_NAME(EINVAL) \
                                             : "UNKNOWN")

#define TEST_ASSERT_EQUAL_ERRNO_T(expected, actual)                                                                       \
    if ((expected) != (actual))                                                                                           \
    {                                                                                                                     \
        fprintf(stderr, "%sindex: %d, step: %d, expected: %s, actual: %s%s\n",                                            \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, TEST_ERRNO_T((expected)), TEST_ERRNO_T((actual)), TEST_TEXT_RESET); \
        TEST_COUNT++;                                                                                                     \
        continue;                                                                                                         \
    }                                                                                                                     \
    TEST_STEP++;

typedef enum TestGPIOState
{
    TEST_GPIO_LOW,
    TEST_GPIO_HI_Z,
} TestGPIOState;

#define TEST_GPIO_STATE(s) ((s) == TEST_GPIO_LOW    ? TEST_VAR_NAME(TEST_GPIO_LOW)  \
                            : (s) == TEST_GPIO_HI_Z ? TEST_VAR_NAME(TEST_GPIO_HI_Z) \
                                                    : "UNKNOWN")

#define TEST_ASSERT_EQUAL_TEST_GPIO_STATE(expected, actual)                                                                     \
    if ((expected) != (actual))                                                                                                 \
    {                                                                                                                           \
        fprintf(stderr, "%sindex: %d, step: %d, expected: %s, actual: %s%s\n",                                                  \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, TEST_GPIO_STATE((expected)), TEST_GPIO_STATE((actual)), TEST_TEXT_RESET); \
        TEST_COUNT++;                                                                                                           \
        continue;                                                                                                               \
    }                                                                                                                           \
    TEST_STEP++;

typedef struct TestGPIO
{
    WanbeiyuGPIO parent;
    TestGPIOState state;
} TestGPIO;

errno_t test_gpio_set_low(WanbeiyuGPIO *gpio)
{
    ((TestGPIO *)gpio)->state = TEST_GPIO_LOW;
    return 0;
}

errno_t test_gpio_set_hi_z(WanbeiyuGPIO *gpio)
{
    ((TestGPIO *)gpio)->state = TEST_GPIO_HI_Z;
    return 0;
}

void test_gpio_init(TestGPIO *gpio)
{
    gpio->parent.set_low = test_gpio_set_low;
    gpio->parent.set_hi_z = test_gpio_set_hi_z;
}

typedef enum TestIDACState
{
    TEST_IDAC_SINK,
    TEST_IDAC_SOURCE
} TestIDACState;

#define TEST_IDAC_STATE(s) ((s) == TEST_IDAC_SINK     ? TEST_VAR_NAME(TEST_IDAC_SINK)   \
                            : (s) == TEST_IDAC_SOURCE ? TEST_VAR_NAME(TEST_IDAC_SOURCE) \
                                                      : "UNKNOWN")

#define TEST_ASSERT_EQUAL_TEST_IDAC_STATE(expected, actual)                                                                     \
    if ((expected) != (actual))                                                                                                 \
    {                                                                                                                           \
        fprintf(stderr, "%sindex: %d, step: %d, expected: %s, actual: %s%s\n",                                                  \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, TEST_IDAC_STATE((expected)), TEST_IDAC_STATE((actual)), TEST_TEXT_RESET); \
        TEST_COUNT++;                                                                                                           \
        continue;                                                                                                               \
    }                                                                                                                           \
    TEST_STEP++;

typedef struct TestIDAC
{
    WanbeiyuIDAC parent;
    TestIDACState state;
    uint8_t value;
} TestIDAC;

errno_t test_idac_set_sink(WanbeiyuIDAC *idac, uint8_t val)
{
    ((TestIDAC *)idac)->state = TEST_IDAC_SINK;
    ((TestIDAC *)idac)->value = val;
    return 0;
}

errno_t test_idac_set_source(WanbeiyuIDAC *idac, uint8_t val)
{
    ((TestIDAC *)idac)->state = TEST_IDAC_SOURCE;
    ((TestIDAC *)idac)->value = val;
    return 0;
}

void test_idac_init(TestIDAC *idac)
{
    idac->parent.set_sink = test_idac_set_sink;
    idac->parent.set_source = test_idac_set_source;
}

#define TEST_UINT16_MID ((uint16_t)0x8000)

typedef struct TestRDAC
{
    WanbeiyuRDAC parent;
    uint16_t position;
} TestRDAC;

errno_t test_digipot_set_wiper_position(WanbeiyuRDAC *rdac, uint16_t pos)
{
    ((TestRDAC *)rdac)->position = pos;
    return 0;
}

#define TEST_RDAC_TOLERANCE ((double)250.0)

#define TEST_ASSERT_EQUAL_WIPER_POSITION(expected, actual)                                        \
    if ((actual) < (expected)-TEST_RDAC_TOLERANCE || (expected) + TEST_RDAC_TOLERANCE < (actual)) \
    {                                                                                             \
        fprintf(stderr, "%sindex: %d, step: %d, expected: %d, actual: %d%s\n",                    \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, (expected), (actual), TEST_TEXT_RESET);     \
        TEST_COUNT++;                                                                             \
        continue;                                                                                 \
    }                                                                                             \
    TEST_STEP++;

TestRDAC *test_rdac_init(TestRDAC *rdac)
{
    rdac->parent.set_wiper_position = test_digipot_set_wiper_position;
    rdac->position = 0;
}

typedef enum TestSwitchState
{
    TEST_SWITCH_ON,
    TEST_SWITCH_OFF
} TestSwitchState;

#define TEST_SWITCH_STATE(s) ((s) == TEST_SWITCH_ON    ? TEST_VAR_NAME(TEST_SWITCH_ON)  \
                              : (s) == TEST_SWITCH_OFF ? TEST_VAR_NAME(TEST_SWITCH_OFF) \
                                                       : "UNKNOWN")

#define TEST_ASSERT_EQUAL_TEST_SWITCH_STATE(expected, actual)                                                                       \
    if ((expected) != (actual))                                                                                                     \
    {                                                                                                                               \
        fprintf(stderr, "%sindex: %d, step: %d, expected: %s, actual: %s%s\n",                                                      \
                TEST_TEXT_RED, TEST_INDEX, TEST_STEP, TEST_SWITCH_STATE((expected)), TEST_SWITCH_STATE((actual)), TEST_TEXT_RESET); \
        TEST_COUNT++;                                                                                                               \
        continue;                                                                                                                   \
    }                                                                                                                               \
    TEST_STEP++;

typedef struct TestSwitch
{
    WanbeiyuSPSTSwitch parent;
    TestSwitchState state;
} TestSwitch;

errno_t test_switch_on(WanbeiyuSPSTSwitch *sw)
{
    ((TestSwitch *)sw)->state = TEST_SWITCH_ON;
    return 0;
}

errno_t test_switch_off(WanbeiyuSPSTSwitch *sw)
{
    ((TestSwitch *)sw)->state = TEST_SWITCH_OFF;
    return 0;
}

void test_switch_init(TestSwitch *sw)
{
    sw->parent.on = test_switch_on;
    sw->parent.off = test_switch_off;
}

#endif // TEST_H