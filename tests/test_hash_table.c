#include "hash_table.h"
#include "unity.h"

static a_hash_table_t *t;

void setUp() {
    t = a_hash_table_create();
    TEST_ASSERT_NOT_NULL(t);
}

void tearDown() { a_hash_table_free(t); }

void test_hash_table_empty() {
    TEST_ASSERT_EQUAL_UINT64(0, a_hash_table_len(t));
    TEST_ASSERT_NULL(a_hash_table_get(t, "foo"));
}

void test_hash_table_set_get() {
    a_hash_table_set(t, "foo", "bar");
    TEST_ASSERT_EQUAL_STRING("bar", a_hash_table_get(t, "foo"));
    TEST_ASSERT_EQUAL_UINT64(1, a_hash_table_len(t));
}

void test_hash_table_set_override() {
    a_hash_table_set(t, "foo", "bar");
    a_hash_table_set(t, "foo", "baz");
    TEST_ASSERT_EQUAL_STRING("baz", a_hash_table_get(t, "foo"));
    TEST_ASSERT_EQUAL_UINT64(1, a_hash_table_len(t));
}

void test_hash_table_len() {
    a_hash_table_set(t, "foo", "bar");
    a_hash_table_set(t, "bar", "baz");
    a_hash_table_set(t, "foo", "footbar");
    TEST_ASSERT_EQUAL_INT64(2, a_hash_table_len(t));
}

void test_hash_table_collision() {
    const char *k1 = "Aa";
    const char *k2 = "Bb";
    a_hash_table_set(t, k1, "foo");
    a_hash_table_set(t, k2, "bar");
    TEST_ASSERT_EQUAL_STRING("foo", a_hash_table_get(t, k1));
    TEST_ASSERT_EQUAL_STRING("bar", a_hash_table_get(t, k2));
    TEST_ASSERT_EQUAL_INT64(2, a_hash_table_len(t));
}

void test_hash_table() {
    RUN_TEST(test_hash_table_empty);
    RUN_TEST(test_hash_table_set_get);
    RUN_TEST(test_hash_table_set_override);
    RUN_TEST(test_hash_table_len);
    RUN_TEST(test_hash_table_collision);
}
