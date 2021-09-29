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
const std::string VIRHEELLISET_KOORDINAATIT = "Coordinate outside the board";
const std::string PAIKKA_VARATTU = "The given place is already occupied";
const std::string PELI_PAATTYNYT = "Game over!";
const std::string PELILAUTA_TAYSI = "No empty places";


// TO DO:
// - pelilaudan tarkistus
// - laajennus


// Alustaa pelilaudan
void alustaLauta(std::vector<std::vector<char>>& lauta,
                 int koko)
{
    for (int sarake = 0; sarake < koko; ++sarake)
    {
        std::vector<char> sarake_vektori = std::vector<char>(koko, '.');
        lauta.push_back(sarake_vektori);
    }
}

// Tulostaa pelilaudan
void tulostaLauta(std::vector<std::vector<char>>& lauta,
                  int koko)
{
    // sarakkeiden numeroiden tulostus
    std::cout << "  ";
    for (int x = 0; x < koko; ++x)
    {
        std::cout << (x + 1) %  10 << " ";
    }
    std::cout << std::endl;

    // rivien numeroiden ja ruudukon tulostus
    for (int y = 0; y < koko; ++y)
    {
        std::cout << (y + 1) % 10 << ' ';
        for (int x = 0; x < koko; ++x)
        {
            std::cout << lauta.at(y).at(x);
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

// Tarkistaa, että x- ja y- koordinaatit osuvat laudalle
// ja että vain toinen annetuista koordinaateista ylittää laudan rajat.
// Palauttaa true jos koordinaatit ovat sopivia, false jos ei.
bool onkoKoordinaatitSopivia(int x,int y,int koko)
{
    // Jos koordinaatit ovat negatiivisia
    if(x < 0 || y < 0)
    {
        return false;
    }
    // Jos koordinaatit menevät ruudukon koon yli enemmän kuin yhdellä.
    if(x > koko + 1 || y > koko + 1)
    {
        return false;
    }
    // Jos molemmat ovat 0.
    if(x == 0 && y == 0)
    {
        return false;
    }
    // Jos toinen on 0 ja toinen ylittää ruudukon
    // rajat.
    else if(x == 0 || y == 0)
    {
        if(x > koko || y > koko)
        {
            return false;
        }
    }
    return true;
}

// Tarkistaa, onko kohta tyhjänä laudalla.
// Palauttaa true jos on, false jos ei.
bool onkoKohtaTyhja(std::vector<std::vector<char>>& lauta,
                    int x,int y)
{
    if(lauta.at(y - 1).at(x - 1) == '.')
    {
        return true;
    }
    return false;
}

// Tarkistaa koordinaatit. Palauttaa true jos koordinaatit on ok, false jos ei.
bool tarkistaKoordinaatit(std::vector<std::vector<char>>& lauta,
                          int x,int y, int koko)
{
    if(!onkoKoordinaatitSopivia(x, y, koko))
    {
        std::cout << VIRHEELLISET_KOORDINAATIT << std::endl;
        return false;
    }
    if(x <= koko && x > 0
            && y <= koko && y > 0)
    {
        if(!onkoKohtaTyhja(lauta, x, y))
        {
            std::cout << PAIKKA_VARATTU << std::endl;
            return false;
        }
    }
    return true;
}

bool onkoLautaTaynna(std::vector<std::vector<char>>& lauta, int koko)
{
    for(int y = 1; y <= koko; ++y )
    {
        for(int x = 1; x <= koko; ++x )
        {
            if(onkoKohtaTyhja(lauta, x, y) )
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    std::cout << "Start game:" << std::endl;

    int koko = 3;
    std::vector<std::vector<char>> lauta = {};
    alustaLauta(lauta, koko);
    tulostaLauta(lauta, koko);

    char pelaaja1 = 'X';
    char pelaaja2 = '0';
    char* vuorossa = 0;

    int vuoro = 1;
    while (true)
    {
        if(vuoro % 2 != 0)
        {
            vuorossa = &pelaaja1;
        }
        else
        {
            vuorossa = &pelaaja2;
        }

        std::string syote1 = "";
        std::string syote2 = "";
        int xkoordinaatti = 0;
        int ykoordinaatti = 0;

        std::cout << "For " << *vuorossa << ", enter coordinates: x y> ";
        std::cin >> syote1;
        if(syote1 == "q")
        {
            std::cout << LOPETA_PELI << std::endl;
            return EXIT_SUCCESS;
        }
        std::cin >> syote2;

        if(onkoNumero(syote1) && (onkoNumero(syote2)))
        {
            muutaLuvuksi(syote1, syote2, xkoordinaatti, ykoordinaatti);
            if (tarkistaKoordinaatit(lauta, xkoordinaatti, ykoordinaatti, koko))
            {

                // jos osuu laudalle -funktio?
                lauta.at(ykoordinaatti - 1).at(xkoordinaatti -1 ) = *vuorossa;
                tulostaLauta(lauta, koko);

                // laajennus
            }
        }
        else
        {
            std::cout << VIRHEELLISET_KOORDINAATIT << std::endl;
        }

        // Täyden laudan tarkistus
        if(onkoLautaTaynna(lauta, koko))
        {
            std::cout << PELILAUTA_TAYSI << std::endl;
            std::cout << PELI_PAATTYNYT << std::endl;
            return EXIT_SUCCESS;
        }
        else vuoro += 1;
    }

    return EXIT_SUCCESS;
}
