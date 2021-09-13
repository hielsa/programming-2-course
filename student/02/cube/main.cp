#include <iostream>

using namespace std;

int main()
{
    int nro = 0;
    cout << "Enter a number: ";
    cin >> nro;

    if(nro == 0)
    {
        cout << "The cube of " << 0 << " is " << 0 << "." << endl;
    }
    else
   {
        int kuutio = nro * nro * nro;
        int tarkistus = (kuutio / nro) / nro;

        if(tarkistus == nro)
        {
            cout << "The cube of " << nro << " is " << kuutio << endl;
        }
        else
        {
            cout << "The cube of " << nro << " is not " << kuutio << endl;
        }
    }
    return 0;
}
