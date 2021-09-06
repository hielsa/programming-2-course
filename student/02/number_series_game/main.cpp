#include <iostream>


int main()
{
    int numbers_amnt = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numbers_amnt;

    for (int i = 1; i < numbers_amnt + 1; ++i) {
        if (i % 3 == 0 && i % 7 == 0) {
            std::cout << "zip boing" << std::endl;
        } else if (i % 3 == 0) {
            std::cout << "zip" << std::endl;
        } else if (i % 7 == 0) {
            std::cout << "boing" << std::endl;
        } else {
            std::cout << i << std::endl;
        }
    }
}
