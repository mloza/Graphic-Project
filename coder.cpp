#include "coder.h"
#include <iostream>

unsigned int coder::nWords = 0;
string coder::dictionary[DICTIONARY_MAX_SIZE];

void coder::run()
{
    std::cout << "CODER RUN.";
}

/**
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

/**
 *  @param data Dane wejściowe, które podlegają kompresji
 *  @param dataSize Rozmiar danych wejściowych
 */
void coder::lzw(char* data, unsigned long int dataSize)
{
    unsigned long int actualIdx = 0; // Index aktualnie pobieranego bajtu danych wejściowych
    string word = "";

    for(int i=0; i< 4; i++)
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
            dictionary[nWords] = word + data[actualIdx]; // dodaj słowo z aktualnym znakiem do słownika

            nWords++;
            word=data[actualIdx]; // przypisz słowu znak z wejścia
        }

        // Dodaj aktualny znak i przesuń się na następny
        word += data[actualIdx];
        actualIdx++;
    }

    // Wypisz indeks tego co zostało
    cout << getDictionaryIdx(word);
};
