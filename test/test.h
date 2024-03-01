#ifndef TEST_H_
#define TEST_H_

#include <wanbeiyu.h>

#define TEXT_RED "\e[31m"
#define TEXT_GREEN "\e[32m"
#define TEXT_RESET "\e[0m"

#define TEST_FOR(cases) \
    TestCase case_;     \
    for (size_t i = 0; case_ = (cases)[i], i < sizeof((cases)) / sizeof(TestCase); i++)

#define TEST_VAR_NAME(var) #var

#define TEST_WANBEIYU_ERROR(e) ((e) == WANBEIYU_OK       ? TEST_VAR_NAME(WANBEIYU_OK)     \
                                : (e) == WANBEIYU_EINVAL ? TEST_VAR_NAME(WANBEIYU_EINVAL) \
                                                         : "")

#define TEST_ASSERT_EQUAL_WANBEIYU_ERROR_RET(expected_ret, actual_ret)                                            \
    if ((expected_ret) != (actual_ret))                                                                           \
    {                                                                                                             \
        fprintf(stderr, "%sindex: %d, expected_ret: %s, actual_ret: %s%s\n",                                      \
                TEXT_RED, i, TEST_WANBEIYU_ERROR((expected_ret)), TEST_WANBEIYU_ERROR((actual_ret)), TEXT_RESET); \
        cnt++;                                                                                                    \
        continue;                                                                                                 \
    }

#define TEST_UINT16_MID ((uint16_t)0x8000)
#define TEST_RDAC_TOLERANCE ((double)500.0)

typedef enum TestGPIOState
{
    TEST_GPIO_LOW,
    TEST_GPIO_HI_Z,
} TestGPIOState;

#define TEST_GPIO_STATE(s) ((s) == TEST_GPIO_LOW    ? TEST_VAR_NAME(TEST_GPIO_LOW)  \
                            : (s) == TEST_GPIO_HI_Z ? TEST_VAR_NAME(TEST_GPIO_HI_Z) \
                                                    : "")

typedef struct TestGPIO
{
    WanbeiyuGPIO parent;
    TestGPIOState state;
} TestGPIO;

WanbeiyuErrNo test_gpio_set_low(WanbeiyuGPIO *gpio)
{
    ((TestGPIO *)gpio)->state = TEST_GPIO_LOW;
    return WANBEIYU_OK;
}

WanbeiyuErrNo test_gpio_set_hi_z(WanbeiyuGPIO *gpio)
{
    ((TestGPIO *)gpio)->state = TEST_GPIO_HI_Z;
    return WANBEIYU_OK;
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
                                                      : "")

typedef struct TestIDAC
{
    WanbeiyuIDAC parent;
    TestIDACState state;
    uint8_t value;
} TestIDAC;

WanbeiyuErrNo test_idac_set_sink(WanbeiyuIDAC *idac, uint8_t val)
{
    ((TestIDAC *)idac)->state = TEST_IDAC_SINK;
    ((TestIDAC *)idac)->value = val;
    return WANBEIYU_OK;
}

WanbeiyuErrNo test_idac_set_source(WanbeiyuIDAC *idac, uint8_t val)
{
    ((TestIDAC *)idac)->state = TEST_IDAC_SOURCE;
    ((TestIDAC *)idac)->value = val;
    return WANBEIYU_OK;
}

void test_idac_init(TestIDAC *idac)
{
    idac->parent.set_sink = test_idac_set_sink;
    idac->parent.set_source = test_idac_set_source;
}
typedef struct TestRDAC
{
    WanbeiyuRDAC parent;
    uint16_t position;
} TestRDAC;

WanbeiyuErrNo test_digipot_set_wiper_position(WanbeiyuRDAC *rdac, uint16_t pos)
{
    ((TestRDAC *)rdac)->position = pos;
    return WANBEIYU_OK;
}

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
                                                       : "")

typedef struct TestSwitch
{
    WanbeiyuSPSTSwitch parent;
    TestSwitchState state;
} TestSwitch;

WanbeiyuErrNo test_switch_on(WanbeiyuSPSTSwitch *sw)
{
    ((TestSwitch *)sw)->state = TEST_SWITCH_ON;
    return WANBEIYU_OK;
}

WanbeiyuErrNo test_switch_off(WanbeiyuSPSTSwitch *sw)
{
    ((TestSwitch *)sw)->state = TEST_SWITCH_OFF;
    return WANBEIYU_OK;
}

void test_switch_init(TestSwitch *sw)
{
    sw->parent.on = test_switch_on;
    sw->parent.off = test_switch_off;
}

#endif // TEST_H_