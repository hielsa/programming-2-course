#include <iostream>

using namespace std;

bool length(string encryption_key)
{
    if (encryption_key.length() != 26)
    {
        return false;
    }
    return true;
}


int main()
{
    string key;
    string message;
    cout << "Enter the encryption key: ";
    cin >> key;

    if (! length(key))
    {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    for (string::size_type i = 0; i < key.length(); ++i)
    {
        if (key.at(i) < 'a' || key.at(i) > 'z')
        {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    for (char c = 'a'; c <= 'z'; ++c)
    {
        if (key.find(c) == string::npos)
        {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return EXIT_FAILURE;
        }
    }

    cout << "Enter the text to be encrypted: ";
    cin >> message;

    for (string::size_type j = 0; j < message.length(); ++j) {
        if (message.at(j) < 'a' || message.at(j) > 'z')
        {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }

    cout << "Encrypted text: ";
    for (string::size_type i = 0; i < message.length(); ++i)
    {
        char plain = message[i];
        char encrypted = key[plain - 'a'];
        cout << encrypted << endl;
    }


    return 0;
}
