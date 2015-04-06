#ifndef STRING_CALCULATOR_H_
#define STRING_CALCULATOR_H_

#include <exception>
#include <string>


namespace StringCalculator {

class Exception {
public:
    Exception(const char* what) 
        : what_(what) {
        // nothing
    }

    const char* what() const {
        return what_.c_str();
    }

private:
    const std::string what_;
};

int Add(const char *numbers) {
    
    std::string sep(",\n");
    if (strncmp(numbers, "//", 2) == 0) {
        const char *end = strchr(numbers, '\n');
        sep = std::string(numbers+2, end);
        numbers = end+1;
    } 

    std::string tmp(numbers);
    std::vector<std::string> numbers_list;
    char *token = strtok(&tmp[0], sep.c_str());
    while (token != 0) {
        numbers_list.push_back(token);
        token = strtok(0, sep.c_str());
    }

    const int size = numbers_list.size();
    if (size == 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < size; ++i) {
        int number;
        const int ret = sscanf(numbers_list[i].c_str(), "%d", &number);
        if (ret != 1) {
            throw new Exception("Input value is not integer.");
        }
        sum += number;
    }
    return sum;
}

}  // namespace StringCalculator 


#endif  // STRING_CALCULATOR_H_
