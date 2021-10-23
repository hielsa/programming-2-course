//--------------------------------------------------

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const int COURSE_FULL = 50;
const char CSV_FIELD_DELIMITER = ';';

struct Course
{
    std::string name;
    std::string location;
    int enrollments;
};

// Splits the given string str into parts separated by the given delimiter
// and returns the parts in a vector.
// If the delimiter appears inside quatation, ignores delimiter,
// i.e. does not split quoted text.
std::vector<std::string> split_ignoring_quoted_delim(const std::string& str,
                                                     char delimiter)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if(result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;
}

bool read_input_file(const std::string& filepath,
                     std::vector<std::string>& lines)
{
    std::ifstream input_file_in(filepath);
    if (!input_file_in.is_open())
    {
        return false;
    }

    std::string line;
    while (std::getline(input_file_in, line))
    {
        lines.push_back(line);
    }
    return true;
}

bool validate_field_count(const std::vector<std::string>& fields)
{
    if (fields.size() != 4) // tallennus vakioihin?
    {
        return false;
    }
    return true;
}

bool validate_no_empty_fields(const std::vector<std::string>& fields)
{
    for (const auto& field : fields)
    {
        if (field.empty())
        {
            return false;
        }
    }
    return true;
}

bool parse_input_lines(
        const std::vector<std::string>& lines,
        std::map<std::string, std::vector<Course>>& courses_by_theme)
{
    for (const std::string& line : lines)
    {
        std::vector<std::string> fields
                = split_ignoring_quoted_delim(line, CSV_FIELD_DELIMITER);

        if (!validate_field_count(fields)
            || !validate_no_empty_fields(fields))
        {
                return false;
        }

        const std::string& theme = fields.at(0);
        const std::string& location = fields.at(1);
        const std::string& name = fields.at(2);
        int enrollments = 0;

        if (fields.at(3) == "full")
        {
            enrollments = COURSE_FULL;
        }
        else
        {
            std::istringstream enrollments_in(fields.at(3));
            if (!(enrollments_in >> enrollments))
            {
                return false;
            }
        }

        Course new_course{name, location, enrollments};

        courses_by_theme.try_emplace({});

        std::vector<Course>& courses_under_theme = courses_by_theme[theme];

        auto it = courses_under_theme.begin();

        for( ; it != courses_under_theme.end(); ++it)
        {
            if (it->name == new_course.name
                && it->location == new_course.location)
            {
                break;
            }
        }

        if (it != courses_under_theme.end())
        {
            courses_under_theme.erase(it);
        }

        courses_under_theme.push_back(new_course);
        std::cout << "Theme: " << theme << "\n"
                  << "Name: " << name  << "\n"
                  << "Location: " << location << "\n"
                  << "Enrollments: " << enrollments << "\n\n";
    }
    return true;
}

/*
void themes_command()
{

}

void courses_command()
{

}

void available_command()
{

}

void courses_in_theme_command()
{

}

void courses_in_location_command()
{

}

void favorite_theme_command()
{

}

void cancel_command()
{

}
*/

int main()
{    
    std::string input_filepath = "";
    std::cout << "Input file: " ;
    std::getline(std::cin, input_filepath);

    std::vector<std::string> input_file_lines;
    if (!read_input_file(input_filepath, input_file_lines))
    {
        std::cerr << "Error: the input file cannot be opened\n";
        return EXIT_FAILURE;
    }

    std::map<std::string, std::vector<Course>> courses_by_theme;

    if (!parse_input_lines(input_file_lines, courses_by_theme))
    {
        std::cerr << "Error: empty field\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

