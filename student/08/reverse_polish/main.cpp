#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cstdlib>


double rpn(const std::string &expr){
  std::istringstream iss(expr);
  std::vector<double> stack;

  std::string token;

  while (iss >> token) {

    double tokenNum;
    if (std::istringstream(token) >> tokenNum) {
      stack.push_back(tokenNum);

    } else {

      double secondOperand = stack.back();
      stack.pop_back();
      double firstOperand = stack.back();
      stack.pop_back();
      if (token == "*")
    stack.push_back(firstOperand * secondOperand);
      else if (token == "/")
      {
          if (secondOperand == 0)
          {
              std::cout << "Error: Division by zero" << std::endl;
              return false;
          }
          else
          {
              stack.push_back(firstOperand / secondOperand);
          }
      }
      else if (token == "-")
    stack.push_back(firstOperand - secondOperand);
      else if (token == "+")
    stack.push_back(firstOperand + secondOperand);


      else { //just in case
    std::cerr << "Error" << std::endl;
    std::exit(1);
      }
    }
  }

  double nmbrs = stack.back();
  std::ostringstream strs;
  strs << nmbrs;
  std::string str = strs.str();

  std::cout << "Correct: " << str << " is the result" << std::endl;

  return true;
}

bool first_character(const std::string &expression)
{
    auto first_char = expression.at(0);
    if (first_char == '*' || first_char == '/' || first_char == '+' || first_char == '-')
    {
        std::cout << "Error: Expression must start with a number" << std::endl;
        return false;
    }
    return true;
}


bool operators_operands_count(const std::string &expression)
{
    std::string disp_expression = expression;
    disp_expression.erase( remove( disp_expression.begin(), disp_expression.end(), ' ' ), disp_expression.end() );
    int length = disp_expression.length();

    int operator_count = 0;
    int operand_count = 0;

    for (int i = 0; i < length; ++i)

    {
        auto character = disp_expression.at(i);

         if (character == '*' ||
             character == '/' ||
             character == '+' ||
             character == '-')
         {
             operand_count += 1;

         }
         else if (character == '1' ||
                  character == '2' ||
                  character == '3' ||
                  character == '4' ||
                  character == '5' ||
                  character == '6' ||
                  character == '7' ||
                  character == '8' ||
                  character == '9' ||
                  character == '0')
         {
             operator_count += 1;

         }
         else {

             std::cout << "Error: Unknown character" << std::endl;
             return false;
         }
    }
    int sep = operator_count - operand_count;
    if (sep > 1)
    {
        std::cout << "Error: Too few operators" << std::endl;
        return false;

    } else if (sep <= 0)
    {
        std::cout << "Error: Too few operands" << std::endl;
        return false;

    } else {
        return true;

    }
}



int main() {

  std::cout << "Input an expression in reverse Polish notation (end with #): " << std::endl;

  std::string expression;
  std::cout << "EXPR> ";
  getline(std::cin, expression);

  if (!first_character(expression))
  {
      return EXIT_FAILURE;
  }

  expression.pop_back();
  if (!operators_operands_count(expression))
  {
      return EXIT_FAILURE;
  }
  if (operators_operands_count(expression))
  {
        if (!rpn(expression))
        {
            return EXIT_FAILURE;
        }
        else
        {
        return EXIT_SUCCESS;
        }
  }
}
