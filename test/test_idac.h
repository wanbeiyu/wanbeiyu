#include "wanbeiyu.h"

#include <stdlib.h>

typedef enum test_idac_state_t
{
    TEST_IDAC_SINK,
    TEST_IDAC_SOURCE
} test_idac_state_t;

typedef struct test_idac_t
{
    wby_idac_t parent;
    test_idac_state_t state;
    uint8_t value;
} test_idac_t;

static void test_idac_set_sink(wby_idac_t *idac, uint8_t val)
{
    ((test_idac_t *)idac)->state = TEST_IDAC_SINK;
    ((test_idac_t *)idac)->value = val;
}

static void test_idac_set_source(wby_idac_t *idac, uint8_t val)
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