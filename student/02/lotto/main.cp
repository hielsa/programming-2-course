#include <iostream>

using namespace std;

unsigned long int kertoma(int luku)
{
    unsigned long int tulo;
    if (luku == 0)
    {
        tulo = 0;
    }
    else {
        tulo = 1;
        for (int i = 1; i < luku + 1; i++)
        {
            tulo = tulo * i;
        }
    }
    return tulo;
}

unsigned long int todnak(int l, int d)
{
    unsigned long int probability;
    unsigned long int l_kertoma = kertoma(l);
    int erotus = l - d;
    unsigned long int erotuksen_kertoma = kertoma(erotus);
    unsigned long int d_kertoma = kertoma(d);

    probability = l_kertoma / (erotuksen_kertoma * d_kertoma);

    return probability;
}

int main()
{
    int lottery_balls;
    int drawn_balls;
    cout << "Enter the total number of lottery balls: ";
    cin >> lottery_balls;
    cout << "Enter the total number of drawn balls: ";
    cin >> drawn_balls;

    if(lottery_balls <= 0 || drawn_balls <= 0)
    {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    }

    if (lottery_balls < drawn_balls)
    {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    }

    cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" << todnak(lottery_balls, drawn_balls) << endl;
    return 0;
}
