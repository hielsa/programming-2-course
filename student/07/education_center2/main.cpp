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
const int QUIT_COMMAND = 1;
const int CONTINUE_ASKING_FOR_COMMANDS = 2;
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
        const std::string& name = fields.at(1);
        const std::string& location = fields.at(2);
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
    }
    return true;
}

void themes_command(std::map<std::string, std::vector<Course>>&
                    courses_by_theme)
{
    std::map<std::string, std::vector<Course>>::iterator iter;
    iter = courses_by_theme.begin();
    ++iter;
    while (iter != courses_by_theme.end() )
    {
        std::cout << iter->first << std::endl;
        ++iter;
    }
}

void courses_command(std::map<std::string, std::vector<Course>>&
                     courses_by_theme,
                     std::string& command_location,
                     std::string& theme)
{
    auto iter = courses_by_theme.find(theme);
    if (iter != courses_by_theme.end())
    {
        std::vector<Course> found_vector = iter->second;
        std::map<std::string, int> found_courses = {};
        for(auto& s : found_vector)
        {
            if (command_location == s.location)
            {
                found_courses.insert( {s.name, s.enrollments});
            }
        }

        if (found_courses.empty())
        {
            std::cout << "Error: unknown location" << std::endl;
        }

        for (auto& pair : found_courses)
        {
            if (pair.second == COURSE_FULL)
            {
                 std::cout << pair.first << " --- full" << std::endl;
            }
            else
            {
                 std::cout << pair.first << " --- "
                           << pair.second << " enrollments"  << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Error: unknown theme" << std::endl;
    }
}

void available_command(std::map<std::string, std::vector<Course>>&
                       courses_by_theme)
{
    std::map<std::string, std::vector<Course>>::iterator iter;
    iter = courses_by_theme.begin();
    ++iter;

    while (iter != courses_by_theme.end() )
    {
        std::string theme = iter->first;
        auto iter2 = courses_by_theme.find(theme);

        if (iter2 != courses_by_theme.end())
        {
            std::vector<Course> found_vector = iter2->second;
            std::map<std::string, std::set<std::string>>
                    location_and_names;
            for(auto& s : found_vector)
            {
                if (s.enrollments != COURSE_FULL)
                {
                    location_and_names[s.location].insert(s.name);
                }
            }

            for (auto& pair : location_and_names)
            {
                for (auto& name : pair.second)
                {
                    std::cout << theme << " : " << pair.first << " : "
                              << name << std::endl;
                }
            }
        }
        ++iter;
    }
}


void courses_in_theme_command(std::map<std::string,std::vector<Course>>&
                              courses_by_theme,
                              std::string& theme)
{
    auto iter = courses_by_theme.find(theme);
    if (iter != courses_by_theme.end())
    {
        std::vector<Course> found_vector = iter->second;
        std::multimap<std::string, std::string> found_courses;
        for(auto& s : found_vector)
        {
            found_courses.insert( {s.location, s.name});
        }
        for (auto& pair : found_courses)
        {

            std::cout << pair.first << " : "
                      << pair.second << std::endl;
        }
    }
    else
    {
        std::cout << "Error: unknown theme" << std::endl;
    }
}


void courses_in_location_command(std::map<std::string,std::vector<Course>>&
                                 courses_by_theme,
                                 std::string command_location)
{
    std::map<std::string, std::vector<Course>>::iterator iter;
    iter = courses_by_theme.begin();
    std::vector<std::string> found_courses = {};
    ++iter;

    while (iter != courses_by_theme.end() )
    {
        std::vector<Course> found_vector = iter->second;

        for(auto& s : found_vector)
        {
            if (command_location == s.location)
            {
                found_courses.push_back(s.name);
            }
        }
        ++iter;
    }

    sort(found_courses.begin(), found_courses.end());
    if (!found_courses.empty())
    {
        for (std::string& s : found_courses)
        {
            std::cout << s << std::endl;
        }
    }
    else std::cout << "Error: unknown location" << std::endl;
}

/*
void favorite_theme_command(std::map<std::string,std::vector<Course>>&
                            courses_by_theme)
{

}

void cancel_command(std::map<std::string,std::vector<Course>>&
                    courses_by_theme)
{

}
*/

int ask_for_command(std::map<std::string,std::vector<Course>>&
                    courses_by_theme)
{
    std::string command_line = "";
    std::cout << "> " ;
    std::getline(std::cin, command_line);

    std::vector<std::string> split_command =
            split_ignoring_quoted_delim(command_line, ' ');
    std::string command = split_command.at(0);

    // vaihda funktio booliin ja return false?
    if (command == "quit")
    {
        return QUIT_COMMAND;
    }
    else if (command == "themes" && split_command.size() == 1)
    {
        themes_command(courses_by_theme);
    }
    else if (command == "courses")
    {
         if (split_command.size() != 3)
         {
             std::cout << "Error: error in command " << command << std::endl;
         }
         else
         {
             std::string location = split_command.at(1);
             std::string theme = split_command.at(2);
             courses_command(courses_by_theme, location, theme);
         }
    }
    else if (command == "available" && split_command.size() == 1)
    {
        available_command(courses_by_theme);
    }
    else if (command == "courses_in_theme")
    {
        if (split_command.size() != 2)
        {
            std::cout << "Error: error in command " << command << std::endl;
        }
        else
        {
            std::string theme = split_command.at(1);
            courses_in_theme_command(courses_by_theme, theme);
        }
    }    
    else if (command == "courses_in_location")
    {
        if (split_command.size() != 2)
        {
            std::cout << "Error: error in command " << command << std::endl;
        }
        else
        {
            std::string location = split_command.at(1);
            courses_in_location_command(courses_by_theme, location);
        }
    }
    /*
    else if (command == "favorite_theme" && split_command.size() == 1)
    {
        favorite_theme_command(courses_by_theme);
    }
    else if (command == "cancel")
    {
        if (split_command.size() != 2)
        {
            std::cout << "Error: error in command " << command << std::endl;
        }
        else
        {
            cancel_command(courses_by_theme);
        }
    }
*/
    else
    {
        std::cout << "Error: Unknown command: " << command
                  << std::endl;
    }
    return CONTINUE_ASKING_FOR_COMMANDS;
}

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

    while (true)
    {
        int user_command = ask_for_command(courses_by_theme);
        if (user_command == QUIT_COMMAND)
        {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}

