#include <Arduino.h>
#include <unity.h>
#include <fifo.h>

void test_Fifo_reset() {
	
	Fifo fifo;

	TEST_ASSERT_TRUE(fifo.is_empty());

	for(int i = 0; i < FIFO_SIZE; i++) {
		fifo.put(i);
		TEST_ASSERT_FALSE(fifo.is_empty());
	}

	fifo.reset();
	TEST_ASSERT_TRUE(fifo.is_empty());

}

void test_Fifo_normal_flow() {
	
	Fifo fifo;

	TEST_ASSERT_TRUE(fifo.is_empty());

	for(int i = 0; i < FIFO_SIZE; i++) {
		fifo.put(i);
	}

	TEST_ASSERT_TRUE(fifo.is_full());
	TEST_ASSERT_FALSE(fifo.is_empty());

	int item;
	for(int i = 0; i < FIFO_SIZE - 2; i++) {
		item = fifo.get();
		TEST_ASSERT_EQUAL_INT(i, item);
		TEST_ASSERT_FALSE(fifo.is_full());
		TEST_ASSERT_FALSE(fifo.is_empty());
	}

	fifo.put(123);

	for(int i = FIFO_SIZE - 2; i < FIFO_SIZE; i++) {
		TEST_ASSERT_FALSE(fifo.is_empty());
		item = fifo.get();
		TEST_ASSERT_EQUAL_INT(i, item);
		TEST_ASSERT_FALSE(fifo.is_full());
	}

	item = fifo.get();
	TEST_ASSERT_EQUAL_INT(123, item);
	TEST_ASSERT_TRUE(fifo.is_empty());
	TEST_ASSERT_FALSE(fifo.is_full());

}

void test_Fifo_underflow() {

	Fifo fifo;
	TEST_ASSERT_TRUE(fifo.is_empty());

	for(int i = 2; i < FIFO_SIZE; i++) {
		fifo.put(i);
	}

	int item;
	for(int i = 2; i < FIFO_SIZE; i++) {
		TEST_ASSERT_FALSE(fifo.is_empty());
		item = fifo.get();
		TEST_ASSERT_EQUAL_INT(i, item);
		TEST_ASSERT_FALSE(fifo.is_full());
	}

	TEST_ASSERT_TRUE(fifo.is_empty());
	TEST_ASSERT_FALSE(fifo.is_full());

	fifo.put(123);
	TEST_ASSERT_FALSE(fifo.is_empty());
	TEST_ASSERT_FALSE(fifo.is_full());
	item = fifo.get();

	TEST_ASSERT_EQUAL_INT(123, item);
	TEST_ASSERT_TRUE(fifo.is_empty());
	TEST_ASSERT_FALSE(fifo.is_full());

	for(int i = 0; i < FIFO_SIZE; i++) {
		fifo.put(i);
	}

	for(int i = 0; i < FIFO_SIZE; i++) {
		TEST_ASSERT_FALSE(fifo.is_empty());
		item = fifo.get();
		TEST_ASSERT_EQUAL_INT(i, item);
		TEST_ASSERT_FALSE(fifo.is_full());
	}

	TEST_ASSERT_TRUE(fifo.is_empty());
}

void test_Fifo_overflow() {

	Fifo fifo;
	TEST_ASSERT_TRUE(fifo.is_empty());
	TEST_ASSERT_FALSE(fifo.is_full());

	for(int i = 0; i < FIFO_SIZE; i++) {
		fifo.put(i);
	}

	TEST_ASSERT_TRUE(fifo.is_full());

	int item;


	for(int i = 0; i < FIFO_SIZE - 3; i++) {
		TEST_ASSERT_FALSE(fifo.is_empty());
		item = fifo.get();
		TEST_ASSERT_EQUAL_INT(i, item);
		TEST_ASSERT_FALSE(fifo.is_full());
	}

	TEST_ASSERT_FALSE(fifo.is_empty());
	TEST_ASSERT_FALSE(fifo.is_full());

	for(int i = 3; i < FIFO_SIZE; i++) {
		fifo.put(i);
	}

	TEST_ASSERT_TRUE(fifo.is_full());
	TEST_ASSERT_FALSE(fifo.is_empty());

}

void test_Fifo_overflow_overwrite() {

	Fifo fifo;
	TEST_ASSERT_TRUE(fifo.is_empty());
	TEST_ASSERT_FALSE(fifo.is_full());

	for(int i = 0; i < FIFO_SIZE; i++) {
		fifo.put(i);
	}

	TEST_ASSERT_TRUE(fifo.is_full());

	int item;
	item = fifo.get();

	TEST_ASSERT_EQUAL_INT(0, item);

	TEST_ASSERT_FALSE(fifo.is_empty());
	TEST_ASSERT_FALSE(fifo.is_full());
	
	fifo.reset();

	for(int i = 0; i < FIFO_SIZE + 7; i++) {
		fifo.put(i);
	}

	TEST_ASSERT_TRUE(fifo.is_full());

	for(int i = 7; i < FIFO_SIZE + 7; i++) {
		TEST_ASSERT_FALSE(fifo.is_empty());
		item = fifo.get();
		TEST_ASSERT_EQUAL_INT(i, item);
		TEST_ASSERT_FALSE(fifo.is_full());
	}

	TEST_ASSERT_TRUE(fifo.is_empty());

}

void setup() {

	UNITY_BEGIN();
	RUN_TEST(test_Fifo_reset);
	RUN_TEST(test_Fifo_normal_flow);
	RUN_TEST(test_Fifo_underflow);
	RUN_TEST(test_Fifo_overflow);
	RUN_TEST(test_Fifo_overflow_overwrite);
	UNITY_END();

}

void loop() {

}
