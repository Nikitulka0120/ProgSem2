#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "sorting.h"

#define SIZE 10

static void test_FillInc(void **state) {
    (void) state;
    int A[SIZE];
    FillInc(SIZE, A);
    for (int i = 0; i < SIZE; i++) {
        assert_int_equal(A[i], i);
    }
}

static void test_FillDec(void **state) {
    (void) state;
    int A[SIZE];
    FillDec(SIZE, A);
    for (int i = 0; i < SIZE; i++) {
        assert_int_equal(A[i], SIZE - i - 1);
    }
}

static void test_FillRand(void **state) {
    (void) state;
    int A[SIZE];
    FillRand(SIZE, A);
    for (int i = 0; i < SIZE; i++) {
        assert_in_range(A[i], 0, SIZE - 1);
    }
}

static void test_CheckSum(void **state) {
    (void) state;
    int A[SIZE];
    FillInc(SIZE, A);
    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        k += A[i];
    }
    assert_int_equal(CheckSum(SIZE, A), k);
}

static void test_RunNumber(void **state) {
    (void) state;
    int A[SIZE];
    FillInc(SIZE, A);
    assert_int_equal(RunNumber(SIZE, A), 1);
}

static void test_insertSort_sorted_array(void **state) {
    (void) state;
    int A[SIZE];
    FillInc(SIZE, A);
    int sum_before = CheckSum(SIZE, A);
    insertSort(SIZE, A, 0);
    assert_int_equal(RunNumber(SIZE, A), 1);
    assert_int_equal(CheckSum(SIZE, A), sum_before);
}

static void test_insertSort_unsorted_array(void **state) {
    (void) state;
    int A[SIZE];
    FillDec(SIZE, A);
    int sum_before = CheckSum(SIZE, A);
    insertSort(SIZE, A, 0);
    assert_int_equal(RunNumber(SIZE, A), 1);
    assert_int_equal(CheckSum(SIZE, A), sum_before);
}

static void test_shellSort_sorted_array(void **state) {
    (void) state;
    int A[SIZE];
    FillInc(SIZE, A);
    shellSort(SIZE, A, 0);
    assert_int_equal(RunNumber(SIZE, A), 1);
}

static void test_shellSort_unsorted_array(void **state) {
    (void) state;
    int A[SIZE];
    FillRand(SIZE, A);
    int sum_before = CheckSum(SIZE, A);
    int before = RunNumber(SIZE, A);
    shellSort(SIZE, A, 0);
    int after = RunNumber(SIZE, A);
    assert_true(after <= before);
    assert_int_equal(CheckSum(SIZE, A), sum_before);
}

static void test_shellSortBetter(void **state) {
    (void) state;
    int A[SIZE];
    FillRand(SIZE, A);
    int sum_before = CheckSum(SIZE, A);
    int before = RunNumber(SIZE, A);
    shellSortBetter(SIZE, A, 0);
    int after = RunNumber(SIZE, A);
    assert_true(after <= before);
    assert_int_equal(CheckSum(SIZE, A), sum_before);
}

static void test_generateShellSequenceAsString(void **state) {
    (void) state;
    char buffer[100];
    generateShellSequenceAsString(100, buffer);
    assert_non_null(strstr(buffer, "1"));
}

static void test_generateCiuraSequenceAsString(void **state) {
    (void) state;
    char buffer[100];
    generateCiuraSequenceAsString(100, buffer);
    assert_non_null(strstr(buffer, "1"));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_FillInc),
        cmocka_unit_test(test_FillDec),
        cmocka_unit_test(test_FillRand),
        cmocka_unit_test(test_CheckSum),
        cmocka_unit_test(test_RunNumber),
        cmocka_unit_test(test_insertSort_sorted_array),
        cmocka_unit_test(test_insertSort_unsorted_array),
        cmocka_unit_test(test_shellSort_sorted_array),
        cmocka_unit_test(test_shellSort_unsorted_array),
        cmocka_unit_test(test_shellSortBetter),
        cmocka_unit_test(test_generateShellSequenceAsString),
        cmocka_unit_test(test_generateCiuraSequenceAsString),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
