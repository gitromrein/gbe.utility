#include <unity.h>
#include "cbuffer.h"
#include "u_test.h"
#include "conv32toBI.h"

cbuffer_t buff;

void setUp(void) {
    //cbuffer_t buff;
    cbuffer_init(&buff);
}

void tearDown(void) {
    //cbuffer_t buff;
    cbuffer_clear(&buff);
}

void test_circular_buffer_empty_after_init() {
    //cbuffer_t buff;

    //cbuffer_init(&buff);

    TEST_ASSERT_TRUE(cbuffer_empty(&buff));
}

void test_circular_buffer_not_empty_after_new_element_added() {
    //cbuffer_t buff;
    //cbuffer_init(&buff);

    cbuffer_add(&buff, 100);

    TEST_ASSERT_FALSE(cbuffer_empty(&buff));
}

void test_circular_buffer_reports_full_correctly() {
    //cbuffer_t buff;
    //cbuffer_init(&buff);
    for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
        cbuffer_add(&buff, i);
    }

    TEST_ASSERT_TRUE(cbuffer_full(&buff));
}

void test_circular_buffer_read_element_succesful() {
    //cbuffer_t buff;
    //cbuffer_init(&buff);

    uint8_t value = 55;
    cbuffer_add(&buff, value);

    TEST_ASSERT_EQUAL(value, cbuffer_get(&buff));
}

void test_circular_buffer_cleaned_succesfully() {
    //cbuffer_t buff;
    //cbuffer_init(&buff);

    for (uint8_t i = 0; i < BUFFER_SIZE/2; i++) {
        cbuffer_add(&buff, i);
    }
    cbuffer_clear(&buff);

    TEST_ASSERT_TRUE(cbuffer_empty(&buff));
}

void test_pdsv_ConvertToBigEndian() {
    //cbuffer_t buff;

    //cbuffer_init(&buff);

    uint16_t ui16ParamVerif;
    uint16_t ui16ParamTest;
    ui16ParamVerif = 32;
    ui16ParamTest = 32;


    TEST_ASSERT_EQUAL(ui16ParamVerif, ui32ConvertToBigEndianTest(ui16ParamTest));
}

void test_pdsv_ConvertToBigEndian32() {
    //cbuffer_t buff;

    //cbuffer_init(&buff);

    uint32_t ui32ParamVerif;
    uint32_t ui32ParamTest;
    ui32ParamVerif = 536870912;
    ui32ParamTest = 32;


    TEST_ASSERT_EQUAL(ui32ParamVerif, ui32ConvertToBigEndian(ui32ParamTest));
}

//int return?
int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_circular_buffer_empty_after_init);
    RUN_TEST(test_circular_buffer_not_empty_after_new_element_added);
    RUN_TEST(test_circular_buffer_reports_full_correctly);
    RUN_TEST(test_circular_buffer_read_element_succesful);
    RUN_TEST(test_circular_buffer_cleaned_succesfully);
    RUN_TEST(test_pdsv_ConvertToBigEndian);
    RUN_TEST(test_pdsv_ConvertToBigEndian32);

    UNITY_END();
}
