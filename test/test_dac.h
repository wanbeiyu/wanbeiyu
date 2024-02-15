#include "wanbeiyu.h"

#include <stdlib.h>

typedef enum TestDACState
{
    TEST_DAC_SINK,
    TEST_DAC_SOURCE
} TestDACState;

typedef struct TestDAC
{
    wby_idac_t parent;
    TestDACState state;
    uint8_t value;
} TestDAC;

static void test_dac_set_sink(wby_idac_t *parent, uint8_t val)
{
    TestDAC *self = (TestDAC *)parent;
    self->state = TEST_DAC_SINK;
    self->value = val;
}

static void test_dac_set_source(wby_idac_t *parent, uint8_t val)
{
    TestDAC *self = (TestDAC *)parent;
    self->state = TEST_DAC_SOURCE;
    self->value = val;
}

TestDAC *test_dac_new(void)
{
    TestDAC *self = (TestDAC *)malloc(sizeof(TestDAC));
    if (self == NULL)
    {
        return NULL;
    }

    self->parent.set_sink = test_dac_set_sink;
    self->parent.set_source = test_dac_set_source;

    self->state = TEST_DAC_SOURCE;
    self->value = 0;

    return self;
}

void test_dac_delete(TestDAC *self)
{
    free(self);
}