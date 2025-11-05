#include "./include/twelve.h"
#include <utility>

int main() {

    std::string num1, num2, sign;
    std::cout << "Input first number (12 notation): ";
    std::cin >> num1;
    Twelve a(num1);
    std::cout << "Input second number (12 notation): ";
    std::cin >> num2;
    Twelve b(num2);
    std::cout << "+/- : ";
    std::cin >> sign;
    Twelve c;
    if(sign == "+")
        c.move_from(std::move(a.add(b)));
    else if(sign == "-")
        c.move_from(std::move(a.sub(b)));
    else throw std::exception();
    c.print();
    return 0;
    
}
