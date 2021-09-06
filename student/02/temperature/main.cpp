#include <iostream>

using namespace std;

int main()
{
    int temp = 0;
    double C = 0;
    double F = 0;
    cout << "Enter a temperature: ";
    cin >> temp;
    F = (temp*1.8)+32;
    C = (temp-32) / 1.8;

    cout << temp << " degrees Celsius is " << F << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << C << " degrees Celsius" << endl;

    return 0;
}
