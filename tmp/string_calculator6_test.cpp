#include "gmock/gmock.h"
#include "string_calculator.h"

TEST(StringCalculatorTest, DISABLED_when_more_than_2_numbers_are_used_then_exception_is_thrown) {
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

TEST(StringCalculatorTest, when_one_number_is_used_then_return_value_is_that_same_number) {
    ASSERT_EQ(3, StringCalculator::Add("3"));
}

TEST(StringCalculatorTest, when_two_numbers_are_used_then_return_valueIs_their_sum) {
    ASSERT_EQ(3+6, StringCalculator::Add("3,6"));
}

TEST(StringCalculatorTest, when_any_number_of_numbers_is_used_then_return_values_are_their_sums) {
    ASSERT_EQ(3+6+15+18+21+36, StringCalculator::Add("3,6,15,18,21,36"));
}

TEST(StringCalculatorTest, when_new_line_is_used_between_numbers_then_return_values_are_their_sums) {
    ASSERT_EQ(3+6+15, StringCalculator::Add("3,6\n15"));
}

TEST(StringCalculatorTest, when_delimiter_is_specified_then_it_is_used_to_separate_numbers) {
    ASSERT_EQ(3+6+15, StringCalculator::Add("//;\n3;6;15"));
}

