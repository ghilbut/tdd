#include "gmock/gmock.h"

class StringCalculator {
public:

	class Exception {
		
	};

	static void add(char* exp) {
		throw new Exception();
	}
};

class StringCalculatorTest : public ::testing::Test {

// NOTE(ghilbut): member functions
protected:
	virtual void SetUp() {
		// nothing
	}

	virtual void TearDown() {
		// nothing
	}

// NOTE(ghilbut): member variables
protected:
};

TEST_F(StringCalculatorTest, when_more_than_2_numbers_are_used_then_exception_is_thrown) {
	EXPECT_THROW(StringCalculator::add("1,2,3"), StringCalculator::Exception*);
}

TEST_F(StringCalculatorTest, when_2_numbers_are_used_then_no_exception_is_thrown) {
	StringCalculator::add("1,2");
}

TEST_F(StringCalculatorTest, when_non_number_is_used_then_exception_is_thrown) {
	EXPECT_THROW(StringCalculator::add("1,2"), StringCalculator::Exception*);
}
