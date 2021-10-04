#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>


using namespace std;

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
    std::string filename;
    std::cout << "Input file: ";
    std::cin >> filename;

    std::ifstream file_in;
    file_in.open(filename);
    if (!file_in.is_open())
    {
        std::cout << "Error! The file " << filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file_in, line))
    {
        lines.push_back(line);
    }
    file_in.close();


    std::map<std::string, std::set<int>> lines_by_word;
    for (size_t i = 0; i < lines.size(); ++i)
    {
        line = lines.at(i);
        std::vector<std::string> words = split(line, ' ', true);
        for (size_t j = 0; j < words.size(); ++j)
        {
            std::string word = words.at(j);
            if(lines_by_word.count(word) == 0)
            {
                lines_by_word[word] = std::set<int>();
            }
            lines_by_word[word].insert(static_cast<int>(i) + 1);
        }

    }

    for (std::pair<std::string, std::set<int>> key_value_pair : lines_by_word)
    {
        std::string word = key_value_pair.first;
        std::set<int> lines = key_value_pair.second;
        std::cout << word << " " << lines.size() << ": ";

        for (std::set<int>::iterator current_line = lines.begin(); current_line != lines.end(); ++current_line)
            {
            std::cout << *current_line;
            if (current_line != --lines.end())
            {
                std::cout << ", ";
            }
        }
    std::cout << std::endl;
    }


    return EXIT_SUCCESS;
}
