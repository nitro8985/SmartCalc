#include <iostream>

#include "calc_model.h"
#include "parser.h"

int main() {
    std::string input;
    std::cout << "Enter an expression:"
              << std::endl;  // 12modcos(1) - mustn't process
    std::getline(std::cin, input);
    s21::CalcModel model(0, input);
    std::cout << "Result is:  " << model.GetCalculatedData() << std::endl;
    return 0;
}
