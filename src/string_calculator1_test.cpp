#include "gmock/gmock.h"
#include "string_calculator1.h"

TEST(StringCalculatorTest, when_more_than_2_numbers_are_used_then_exception_is_thrown) {
	//EXPECT_THROW(StringCalculator::add("1,2,3"), StringCalculator::Exception*);
	ASSERT_TRUE(false);
}

TEST(StringCalculatorTest, when_2_numbers_are_used_then_no_exception_is_thrown) {
	//StringCalculator::add("1,2");
	ASSERT_TRUE(false);
}

TEST(StringCalculatorTest, when_non_number_is_used_then_exception_is_thrown) {
	//EXPECT_THROW(StringCalculator::add("1,2"), StringCalculator::Exception*);
	//ASSERT_TRUE(false);
	throw nullptr;
}
