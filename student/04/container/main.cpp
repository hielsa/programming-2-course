#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(const std::vector<int>& ints)
{
    if (ints.size() == 0)
    {
        return true;
    }

    std::vector<int>::size_type i1 = 0;
    std::vector<int>::size_type i2 = 1;

    while (i2 < ints.size())
    {
        int luku1 = ints.at(i1);
        int luku2 = ints.at(i2);

        int diff = luku2 - luku1;

        if (diff != 0)
        {
            return false;
        }

        ++i1;
        ++i2;
    }

    return true;
}

bool is_ordered_non_strict_ascending(const std::vector<int>& ints)
{
    if (ints.size() < 1)
    {
        return true;
    }

    std::vector<int>::size_type i1 = 0;
    std::vector<int>::size_type i2 = 1;

    while (i2 < ints.size())
    {
        int luku1 = ints.at(i1);
        int luku2 = ints.at(i2);

        if (luku1 == 0 && luku2 == 0) {
            return true;
        }

        int diff = luku2 - luku1;

        if (diff < 0)
        {
            return false;
        }


        ++i1;
        ++i2;
    }

    return true;
}

bool is_arithmetic_series(const std::vector<int>& ints)
{
    if (ints.size() == 1)
    {
        return true;
    }

    std::vector<int>::size_type i1 = 0;
    std::vector<int>::size_type i2 = 1;

    int diff = ints.at(1) - ints.at(0);

    while (i2 < ints.size())
    {
        int luku1 = ints.at(i1);
        int luku2 = ints.at(i2);

        if (luku1 == 0 && luku2 == 0) {
            return true;
        }

        int new_diff = luku2 - luku1;

        if (new_diff != diff)
        {
            return false;
        }

        ++i1;
        ++i2;
    }

    return true;
}

bool is_geometric_series(const std::vector<int>& ints)
{
    if (ints.size() == 1)
    {
        return true;
    }

    int lukutesti1 = ints.at(0);
    int lukutesti2 = ints.at(1);
    if (lukutesti1 == 0 && lukutesti2 == 0) {
        return false;
    }

    std::vector<int>::size_type i1 = 0;
    std::vector<int>::size_type i2 = 1;

    int ratio = ints.at(1) / ints.at(0);
    int remainder = ints.at(1) % ints.at(0);

    while (i2 < ints.size())
    {
        int luku1 = ints.at(i1);
        int luku2 = ints.at(i2);

        int new_ratio = luku2 / luku1;
        int new_remainder = luku2 % luku1;

        if (new_ratio != ratio or new_remainder != remainder)
        {
            return false;
        }

        ++i1;
        ++i2;
    }

    return true;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;
/*
    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;
        */

    return EXIT_SUCCESS;
}
