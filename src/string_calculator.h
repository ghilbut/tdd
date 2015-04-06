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
   // empty 
}


}  // namespace StringCalculator 


#endif  // STRING_CALCULATOR_H_
