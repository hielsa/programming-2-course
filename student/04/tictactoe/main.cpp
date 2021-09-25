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
}

int main()
{
    size_t koko = 3;
    std::vector<std::vector<char>> ruudukko = {};
    init_grid(ruudukko, koko);
    tulostaLauta(ruudukko, koko);

    return EXIT_SUCCESS;
}
