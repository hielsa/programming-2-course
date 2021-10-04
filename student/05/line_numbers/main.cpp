#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input = "";
    cout << "Input file: " ;
    getline(cin, input);

    cout << "Output file: " ;
    string output = "";
    getline(cin, output);

    ifstream tiedosto_olio(input);
        if ( not tiedosto_olio ) {
            cout << "Error! The file " << input <<
                 " cannot be opened." << endl;
            return EXIT_FAILURE;
        } else {
            int nro = 1;
            string rivi;
            ofstream tiedosto(output);
            while ( getline(tiedosto_olio, rivi) ) {
                string koko_rivi = "";
                string rivinro = "";
                rivinro = to_string(nro);
                koko_rivi = rivinro + " " + rivi + "\n";

                tiedosto << koko_rivi;

                nro +=1;
            }
            tiedosto.close();
            tiedosto_olio.close();

        }
    return EXIT_SUCCESS;
}
