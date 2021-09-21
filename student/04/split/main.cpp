#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(const std::string& text, char separator, bool ignore_empty = false)
{
    std::vector<std::string> parts;

    std::string::size_type left = 0;
    std::string::size_type right = text.find(separator, left);

    while (right != std::string::npos)
    {
        std::string part = text.substr(left, right - left);

        if (part != "" or !ignore_empty)
        {
            parts.push_back(part);
        }

        left = right + 1;
        right = text.find(separator, left);
    }

    std::string final_part = text.substr(left, std::string::npos);
    parts.push_back(final_part);

    return parts;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
