/* Ristinolla
 *
 * Kuvaus:
 *   Ohjelma toteuttaa ristinollapelin, jossa pelialuetta pystyy
 * laajentamaan. Alussa peliruudukko on kooltaan 3 x 3. Peliruudukossa
 * on kolmenlaisia merkkejä: risti (X), nolla (0) ja tyhjä (.).
 *   Pelivuorossa ovat vuorotellen risti ja nolla, risti aloittaa.
 * Joka kierroksella vuorossa olevalle merkille kysytään koordinaatteja
 * eli kahta lukua. Vuorossa oleva merkki sijoitetaan peliruudukolla
 * annettuihin koordinaatteihin, ja vuoro siirtyy toiselle merkille.
 *   Pelin voittaa merkki, jolla saadaan ensimmäiseksi täytettyä peliruudukon
 * kokonainen rivi, kokonainen sarake tai kokonainen diagonaali.
 * Peli voi päättyä myös sellaiseen tilanteeseen, että peliruudukko on
 * täynnä merkkejä, mutta kumpikaan merkki ei voittanut.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, tai koordinaatit saavat ylittyä tai alittua
 * korkeintaan yhdellä. Jos annettu x- tai y-koordinaatti (rivi tai sarake)
 * ylittyy yhdellä, peliruudukko laajenee oikealle ja alaspäin. Jos taas
 * x- tai y-koordinaatti alittuu yhdelle, peliruudukko laajenee vasemmalle
 * ja alaspäin. Peliruudukko siis pysyy aina neliön muotoisena.
 *   Pelin päättyessä kerrotaan, kumpi voitti, vai voittiko kumpikaan.
 *
 * Ohjelman kirjoittaja
 * Nimi: Elsa Huovila
 * Opiskelijanumero: 50264838
 * Käyttäjätunnus: mtelhu
 * E-Mail: elsa.huovila@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */


#include <iostream>
#include <vector>
#include <string>
#include <sstream>


const std::string LOPETA_PELI = "Why on earth you are giving up the game?";
const std::string PELILAUDAN_ULKOPUOLELLA = "Coordinate outside the board";
const std::string PELI_PAATTYNYT = "Game over!";
const std::string PELILAUTA_TAYSI = "No empty places";


// TO DO:
// - koordinaattien tarkistus
// - laajennus
// - pelilaudan tarkistus


// Alustaa pelilaudan
void init_grid(std::vector<std::vector<char>>& ruudukko,
               size_t koko)
{
    for (size_t sarake = 0; sarake < koko; ++sarake)
    {
        std::vector<char> sarake_vektori = std::vector<char>(koko, '.');
        ruudukko.push_back(sarake_vektori);
    }
}

// Tulostaa pelilaudan
void tulostaLauta(std::vector<std::vector<char>>& ruudukko,
              size_t koko)
{
    // sarakkeiden numeroiden tulostus
    std::cout << "  ";
    for (size_t x = 0; x < koko; ++x)
    {
        std::cout << (x + 1) %  10 << " ";
    }
    std::cout << std::endl;

    // rivien numeroiden ja ruudukon tulostus
    for (size_t y = 0; y < koko; ++y)
    {
        std::cout << (y + 1) % 10 << ' ';
        for (size_t x = 0; x < koko; ++x)
        {
            std::cout << ruudukko.at(y).at(x);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Tarkistaa, onko syötteessä kirjaimia.
// Palauttaa true jos ei, false jos on.
bool onkoNumero(const std::string syote)
{
    for (char const c : syote)
    {
        if (std::isdigit(c) == 0)
        {
            return false;
        }
    }
    return true;
}

// Muuttaa syötteen luvuiksi
void muutaLuvuksi(std::string syote1,
                 std::string syote2,
                 int& xkoordinaatti,
                 int& ykoordinaatti)
{
    std::stringstream syote1_xkoordinaatiksi;
    std::stringstream syote2_ykoordinaatiksi;

    syote1_xkoordinaatiksi << syote1;
    syote2_ykoordinaatiksi << syote2;

    syote1_xkoordinaatiksi >> xkoordinaatti;
    syote2_ykoordinaatiksi >> ykoordinaatti;
}

int main()
{
    std::cout << "Start game:" << std::endl;

    size_t koko = 3;
    std::vector<std::vector<char>> ruudukko = {};
    init_grid(ruudukko, koko);
    tulostaLauta(ruudukko, koko);

    char pelaaja1 = 'X';
    char pelaaja2 = '0';
    char* vuorossa = 0;

    int vuoro = 1;
    while (true)
    {
        if (vuoro % 2 != 0)
        {
            vuorossa = &pelaaja1;
        }
        else
        {
            vuorossa = &pelaaja2;
        }

        std::string syote1 = "";
        std::string syote2 = "";

        std::cout << "For " << *vuorossa << ", enter coordinates: x y> ";
        std::cin >> syote1;
        if (syote1 == "q")
        {
            std::cout << LOPETA_PELI << std::endl;
            return EXIT_SUCCESS;
        }
        std::cin >> syote2;

        if (!onkoNumero(syote1) || !(onkoNumero(syote2)))
        {
             std::cout << "Coordinate outside the board" << std::endl;
        }

        int xkoordinaatti = 0;
        int ykoordinaatti = 0;

        muutaLuvuksi(syote1, syote2, xkoordinaatti, ykoordinaatti);

        std::cout << std::endl;

        // tän siirto myöhemmin niihin missä ei ongelmaa
        vuoro += 1;
    }

    return EXIT_SUCCESS;
}
