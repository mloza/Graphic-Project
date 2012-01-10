#include "coder.h"
#include <iostream>

unsigned int coder::nWords = 0;
string coder::dictionary[DICTIONARY_MAX_SIZE];

void coder::run()
{
    std::cout << "Uruchomiono koder.\nRozpoczynam konwersje pliku BMP do formatu BPAM(RGB, bez filtra)" << endl;
}

/*
 *  @brief Funkcja sprawdza na jakiej pozycji w słowniku znajduje się dane słowo.
 *  @param word Słowo do sprawdzenia.
 *  @return Indeks słowa jeśli jest w słowniku, w przeciwnym wypadku -1;
 */
int getDictionaryIdx(string word)
{
    for(int i=0; i < coder::nWords; i++)
    {
        if(word == coder::dictionary[i])
        {
            return i;
        }
    }

    return -1;
}

void coder::lzw(char* data, unsigned long int dataSize)
{
    unsigned long int actualIdx = 0; // Index aktualnie pobieranego bajtu danych wejściowych
    string word = "";

    for(int i=0; i< 256; i++)
    {
        dictionary[i] = i; // wypełnianie słownika alfabetem
        nWords++;
    }

    // Kodowanie danych dopóki mamy dane na wejściu
    while(actualIdx < dataSize)
    {
        if(getDictionaryIdx(word + data[actualIdx]) < 0)
        {
            // Jeżeli nie ma słowa z aktualnym znakiem w słowniku to
            cout << getDictionaryIdx(word) << " "; // wypisz indeks słowa na wyjście

            if(nWords < DICTIONARY_MAX_SIZE)
            {
                dictionary[nWords] = word + data[actualIdx]; // dodaj słowo z aktualnym znakiem do słownika
                nWords++;
            }

            word=""; // Wyzeruj słowo, poniżej dodawany jest do niego aktualny znak
        }

        // Dodaj aktualny znak i przesuń się na następny
        word += data[actualIdx];
        actualIdx++;
    }

    // Wypisz indeks tego co zostało
    cout << getDictionaryIdx(word);
};
