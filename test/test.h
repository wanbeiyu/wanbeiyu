#ifndef TEST_H_
#define TEST_H_

#include <wanbeiyu.h>

#define TEXT_RED "\e[31m"
#define TEXT_GREEN "\e[32m"
#define TEXT_RESET "\e[0m"

#define TEST_FOR(cases) \
    test_case_t case_;  \
    for (size_t i = 0; case_ = (cases)[i], i < sizeof((cases)) / sizeof(test_case_t); i++)

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

#define TEST_ASSERT_EQUAL_WANBEIYU_ERROR_PRE_RET(expected_ret, actual_ret)                                        \
    if ((expected_ret) != (actual_ret))                                                                           \
    {                                                                                                             \
        fprintf(stderr, "%sindex: %d-pre, expected_ret: %s, actual_ret: %s%s\n",                                  \
                TEXT_RED, i, TEST_WANBEIYU_ERROR((expected_ret)), TEST_WANBEIYU_ERROR((actual_ret)), TEXT_RESET); \
        cnt++;                                                                                                    \
        continue;                                                                                                 \
    }

#define TEST_UINT16_MID 0x8000U
#define TEST_RDAC_TOLERANCE 500

typedef enum test_gpio_state_t
{
    TEST_GPIO_LOW,
    TEST_GPIO_HI_Z,
} test_gpio_state_t;

#define TEST_GPIO_STATE(s) ((s) == TEST_GPIO_LOW    ? TEST_VAR_NAME(TEST_GPIO_LOW)  \
                            : (s) == TEST_GPIO_HI_Z ? TEST_VAR_NAME(TEST_GPIO_HI_Z) \
                                                    : "")

typedef struct test_gpio_t
{
    wanbeiyu_gpio_t parent;
    test_gpio_state_t state;
} test_gpio_t;

wanbeiyu_error_t test_gpio_set_low(wanbeiyu_gpio_t *gpio)
{
    ((test_gpio_t *)gpio)->state = TEST_GPIO_LOW;
    return WANBEIYU_OK;
}

wanbeiyu_error_t test_gpio_set_hi_z(wanbeiyu_gpio_t *gpio)
{
    ((test_gpio_t *)gpio)->state = TEST_GPIO_HI_Z;
    return WANBEIYU_OK;
}

void test_gpio_init(test_gpio_t *gpio)
{
    gpio->parent.set_low = test_gpio_set_low;
    gpio->parent.set_hi_z = test_gpio_set_hi_z;
    gpio->state = TEST_GPIO_LOW;
}

typedef enum test_idac_state_t
{
    TEST_IDAC_SINK,
    TEST_IDAC_SOURCE
} test_idac_state_t;

typedef struct test_idac_t
{
    wanbeiyu_idac_t parent;
    test_idac_state_t state;
    uint8_t value;
} test_idac_t;

void test_idac_set_sink(wanbeiyu_idac_t *idac, uint8_t val)
{
    ((test_idac_t *)idac)->state = TEST_IDAC_SINK;
    ((test_idac_t *)idac)->value = val;
}

void test_idac_set_source(wanbeiyu_idac_t *idac, uint8_t val)
{
    ((test_idac_t *)idac)->state = TEST_IDAC_SOURCE;
    ((test_idac_t *)idac)->value = val;
}

void test_idac_init(test_idac_t *idac)
{
    idac->parent.set_sink = test_idac_set_sink;
    idac->parent.set_source = test_idac_set_source;
    idac->state = TEST_IDAC_SOURCE;
    idac->value = 0;
}

typedef enum test_rdac_state_t
{
    TEST_RDAC_POWER_ON,
    TEST_RDAC_POWER_OFF
} test_rdac_state_t;

typedef struct test_rdac_t
{
    wanbeiyu_rdac_t parent;
    test_rdac_state_t state;
    uint16_t position;
} test_rdac_t;

void test_digipot_set_wiper_position(wanbeiyu_rdac_t *rdac, uint16_t pos)
{
    ((test_rdac_t *)rdac)->position = pos;
}

void test_digipot_power_on(wanbeiyu_rdac_t *rdac)
{
    ((test_rdac_t *)rdac)->state = TEST_RDAC_POWER_ON;
}

void test_digipot_power_off(wanbeiyu_rdac_t *rdac)
{
    ((test_rdac_t *)rdac)->state = TEST_RDAC_POWER_OFF;
}

test_rdac_t *test_rdac_init(test_rdac_t *rdac)
{
    rdac->parent.set_wiper_position = test_digipot_set_wiper_position;
    rdac->parent.power_on = test_digipot_power_on;
    rdac->parent.power_off = test_digipot_power_off;
    rdac->state = TEST_RDAC_POWER_ON;
    rdac->position = 0;
}

typedef enum test_switch_state_t
{
    TEST_SWITCH_ON,
    TEST_SWITCH_OFF
} test_switch_state_t;

typedef struct test_switch_t
{
    wanbeiyu_spst_switch_t parent;
    test_switch_state_t state;
} test_switch_t;

void test_switch_on(wanbeiyu_spst_switch_t *sw)
{
    ((test_switch_t *)sw)->state = TEST_SWITCH_ON;
}

void test_switch_off(wanbeiyu_spst_switch_t *sw)
{
    ((test_switch_t *)sw)->state = TEST_SWITCH_OFF;
}

void test_switch_init(test_switch_t *sw)
{
    sw->parent.on = test_switch_on;
    sw->parent.off = test_switch_off;
    sw->state = TEST_SWITCH_OFF;
}

#endif // TEST_H_