#include "wanbeiyu.h"

#include <stdlib.h>

typedef enum TestDigiPotState
{
    TEST_DIGIPOT_POWER_ON,
    TEST_DIGIPOT_POWER_OFF
} TestDigiPotState;

typedef struct TestDigiPot
{
    wby_rdac_t parent;
    TestDigiPotState state;
    uint16_t position;
} TestDigiPot;

static void test_digipot_set_wiper_position(wby_rdac_t *parent, uint16_t pos)
{
    TestDigiPot *self = (TestDigiPot *)parent;
    self->position = pos;
}

static void test_digipot_power_on(wby_rdac_t *parent)
{
    TestDigiPot *self = (TestDigiPot *)parent;
    self->state = TEST_DIGIPOT_POWER_ON;
}

static void test_digipot_power_off(wby_rdac_t *parent)
{
    TestDigiPot *self = (TestDigiPot *)parent;
    self->state = TEST_DIGIPOT_POWER_OFF;
}

TestDigiPot *test_digipot_new(void)
{
    TestDigiPot *self = (TestDigiPot *)malloc(sizeof(TestDigiPot));
    if (self == NULL)
    {
        return NULL;
    }

    self->parent.set_wiper_position = test_digipot_set_wiper_position;
    self->parent.power_on = test_digipot_power_on;
    self->parent.power_off = test_digipot_power_off;

    self->state = TEST_DIGIPOT_POWER_ON;
    self->position = 0;

    return self;
}

void test_digipot_delete(TestDigiPot *self)
{
    free(self);
}