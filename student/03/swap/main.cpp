#include <cstdlib>
#include <iostream>

// Write your swap function here.



#ifndef UNIT_TESTING

int swap(int& i, int& j)
{
    int luku1 = i;
    int luku2 = j;
    i = luku2;
    j = luku1;
}

int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}
#endif
