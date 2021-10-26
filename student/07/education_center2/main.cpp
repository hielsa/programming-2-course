/* Education center
 *
 * Desc:
 *  This program implements a program that reads the course collection
 *data of different education centers from a file at startup, stores
 *them in a suitable data sructure and gives the user the opportunity to
 *search the data structure in question.
 * At first, asks the user for the name of the file. If the file is not found
 *or it does not correspond to the definition, an error message is given
 *and the program terminates. Otherwise, the program reads the file and
 *stores the data into a data structure, after which the the user can give
 *seven different commands to the program:
 *
 *  themes - prints all known themes
 *  courses <location> <theme> - prints all the courses in a given theme and
 *location, and the number of participants.
 *  available - prints the themes, locations, and course names of all non-full
 *courses.
 *  courses_in_theme <theme> - prints all courses under the given theme in all
 *locations.
 *  courses_in_location <location> prints all courses in a given location
 *  favorite_theme - prints the number of participants and the name of the most
 *popular theme(s), based on the total number of participants.
 *  cancel <course> cancels the given course in all locations.
 *  quit - the program terminates without printing anything.
 *
 * If the user command is none of the above, or the command is incomplete or has
 *an incorrect theme, course, or location, the program prints an error message.
 *
 * Program author
 * Name: Elsa Huovila
 * Student number: 50264838
 * UserID: mtelhu
 * Email: elsa.huovila@tuni.fi
 *
 * */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const int COURSE_FULL = 50;
const int VALID_FIELD_COUNT = 4;
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

// Reads the input file line by line. If the file can't be opened
// returns false, otherwise true.
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

// Validates the field count of a line. Returns false if the field size
// is other than 4, otherwise returns true.
bool validate_field_count(const std::vector<std::string>& fields)
{
    if (fields.size() != VALID_FIELD_COUNT)
    {
        return false;
    }
    return true;
}

// Validates there are no fields filled with spaces. Returns false if there is,
// otherwise returns true.
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

// Stores the data to the structure
bool parse_input_lines(
        std::vector<std::string>& lines,
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

        // change the enrollments to "full" if there are 50 enrollments.
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

        // remove duplicates
        if (it != courses_under_theme.end())
        {
            courses_under_theme.erase(it);
        }

        courses_under_theme.push_back(new_course);
    }
    return true;
}

// Prints all themes in alphabetical order. If there are no themes,
// returns without printing.
void themes_command(std::map<std::string, std::vector<Course>>&
                    courses_by_theme)
{
    if (courses_by_theme.empty()) return;

    std::map<std::string, std::vector<Course>>::iterator iter;
    iter = courses_by_theme.begin();
    ++iter;
    while (iter != courses_by_theme.end() )
    {
        std::cout << iter->first << std::endl;
        ++iter;
    }
}

// Prints all the courses in a theme and location, and the number of
// participants. If the course has 50 enrollments, prints that the course
// is full. Error message is printed if the theme or location is unknown.
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

// Prints the themes, locations, and course names of all non-full courses.
// The output is a single alphabetically ordered list, where the list elements
// are firstly ordered by themes, secondly by locations, and thirdly by
// course names. If the input file is empty, returns without printing.
void available_command(std::map<std::string, std::vector<Course>>&
                       courses_by_theme)
{
    if (courses_by_theme.empty()) return;

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

// Prints all courses under the given theme in all locations.The locations are
// listed an alphabetical order and courses in the order they have been listed
// in the input file. Error message is printed if the theme is unknown.
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

// Prints all courses in a location in alphabetical order.
// Error message is printed if the location is unknown.
void courses_in_location_command(std::map<std::string,std::vector<Course>>&
                                 courses_by_theme,
                                 std::string command_location)
{
    std::map<std::string, std::vector<Course>>::iterator iter;
    iter = courses_by_theme.begin();
    ++iter;

    std::vector<std::string> found_courses = {};

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
        for (std::string& course : found_courses)
        {
            std::cout << course << std::endl;
        }
    }
    else std::cout << "Error: unknown location" << std::endl;
}


// Sorts the vector with themes and enrollments by the amount of enrollments.
bool compare_pairs(std::pair<std::string, int>&a,
                   std::pair<std::string, int>&b)
{
    return a.second > b.second;
}

// Prints the number of participants and the name of the most popular theme(s),
// based on the total number of participants. If the file is empty, prints
// a message.
void favorite_theme_command(std::map<std::string,std::vector<Course>>&
                            courses_by_theme)
{
    if (!courses_by_theme.empty())
    {
        std::map<std::string, std::vector<Course>>::iterator iter;
        iter = courses_by_theme.begin();
        ++iter;
        std::vector<std::pair<std::string, int>> themes_with_enrollements;

        while (iter != courses_by_theme.end() )
        {
            std::string theme = iter->first;

            auto iter2 = courses_by_theme.find(theme);
            int total_enrollments = 0;

            if (iter2 != courses_by_theme.end())
            {
                std::vector<Course> found_vector = iter2->second;
                for(auto& s : found_vector)
                {
                    total_enrollments += s.enrollments;
                }
            }
            themes_with_enrollements.push_back({theme, total_enrollments});

            ++iter;
        }

        sort(themes_with_enrollements.begin(), themes_with_enrollements.end(),
             compare_pairs);

        if (!themes_with_enrollements.empty())
        {
            std::cout << themes_with_enrollements[0].second
                      << " enrollments in themes" <<  std::endl;

            auto iter2 = themes_with_enrollements.begin();

            // prints all the themes with the same amount of enrollments
            // as the one with the most enrollments.
            while (iter2 != themes_with_enrollements.end())
            {
                if (themes_with_enrollements[0].second == iter2[0].second)
                {
                    std::cout << "--- " << iter2[0].first <<  std::endl;
                }
                ++iter2;
            }
        }
    }
    else std::cout << "No enrollments" << std::endl;
}

// Cancels the course in all locations. Prints an error message if
// the course is unknown or if the file is empty.
void cancel_command(std::map<std::string,std::vector<Course>>&
                    courses_by_theme,
                    std::string course)
{
    if (courses_by_theme.empty())
    {
        std::cout << "Error: unknown course" << std::endl;
        return;
    }
    std::map<std::string, std::vector<Course>>::iterator map_it;
    map_it = courses_by_theme.begin();
    ++map_it;

    // counter to count how many courses are to be cancelled
    int counter = 0;

    while (map_it != courses_by_theme.end() )
    {
        std::vector<Course>::iterator vec_it;
        vec_it = map_it->second.begin();
        for (; vec_it != (*map_it).second.end();)
        {
            if (course == vec_it->name)
            {
                vec_it = map_it->second.erase(vec_it);
                ++counter;
            }
            else
            ++vec_it;
        }
        ++map_it;
    }

    if (counter == 0)
    {
        std::cout << "Error: unknown course" << std::endl;
    }
    else  std::cout << course
                    << " cancelled in all locations" << std::endl;
}

// Asks the user for command. Prints an error message if the command is invalid,
// i.e. the command is too short, long, or unknown. If the command is empty,
// continues asking.
bool ask_for_command(std::map<std::string,std::vector<Course>>&
                    courses_by_theme)
{
    std::string command_line = "";
    std::cout << "> " ;
    std::getline(std::cin, command_line);

    if (command_line == "")
    {
        return true;
    }

    std::vector<std::string> split_command =
            split_ignoring_quoted_delim(command_line, ' ');
    std::string command = split_command.at(0);

    if (command == "quit")
    {
        return false;
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
            std::string course = split_command.at(1);
            cancel_command(courses_by_theme, course);
        }
    }
    else
    {
        std::cout << "Error: Unknown command: " << command
                  << std::endl;
    }
    return true;
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

    // store the data. If the fields are empty or the field count is invalid,
    // terminate the program.
    if (!parse_input_lines(input_file_lines, courses_by_theme))
    {
        std::cerr << "Error: empty field\n";
        return EXIT_FAILURE;
    }

    // continue printing the prompt until the user gives the command 'quit'
    while (true)
    {
        if (!ask_for_command(courses_by_theme))
        {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}

