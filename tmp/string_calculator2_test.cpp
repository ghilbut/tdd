#include "gmock/gmock.h"
#include "string_calculator2.h"

TEST(StringCalculatorTest, when_more_than_2_numbers_are_used_then_exception_is_thrown) {
    EXPECT_THROW(StringCalculator::Add("1,2,3"), StringCalculator::Exception*);
}

TEST(StringCalculatorTest, when_2_numbers_are_used_then_no_exception_is_thrown) {
	StringCalculator::Add("1,2");
}

TEST(StringCalculatorTest, when_non_number_is_used_then_exception_is_thrown) {
	EXPECT_THROW(StringCalculator::Add("1,X"), StringCalculator::Exception*);
}

TEST(StringCalculatorTest, when_empty_string_is_used_then_return_value_is_zero) {
    ASSERT_EQ(0, StringCalculator::Add(""));
}
