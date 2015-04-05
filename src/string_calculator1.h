#ifndef STRING_CALCULATOR_H_
#define STRING_CALCULATOR_H_

#include <exception>
#include <string>


class StringCalculator {
public:

	class Exception : public std::exception {
		public:
			Exception(const std::string& what)
				: std::exception()
				, what_(what) {
				// nothing
			}

			virtual ~Exception() _NOEXCEPT {
				// nothing
			}

			virtual const char* what() const _NOEXCEPT {
				return what_.c_str();
			}

		private:
			const std::string what_;
	};

	static void add(const char *numbers) {

		std::vector<std::string> numbers_list;

		char *token = strtok((char*)numbers, ",");
		while (token != nullptr) {
			numbers_list.push_back(token);
			token = strtok(nullptr, ",");
		}

		const int size = numbers_list.size();
		if (size > 2) {
			throw Exception("Up to 2 numbers separated by comma (,) are allowed");
		}
		else {
			for (int i = 0; i < size; ++i) {
				int number;
				const int ret = sscanf(numbers_list[i].c_str(), "%d", &number);
				if (ret != 1) {
					throw Exception("Input value is not integer.");
				}
			}
		}
	}
};


#endif  // STRING_CALCULATOR_H_
