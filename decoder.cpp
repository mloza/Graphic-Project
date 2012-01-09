#include <iostream>
#include "decoder.h"

using namespace std;

namespace decoder {
    unsigned const int DICTIONARY_MAX_SIZE = 4096;      /** < maksymalna ilość słów w słowniku */
    string dictionary[DICTIONARY_MAX_SIZE];             /** < słownik przechowujący słowa zapisane w ciągu bajtów (string) */
    unsigned int nWords;                                /** < ilość słów w słowniku */

    void run()
    {
        cout << "DECODER";
    }

    void lzw(uint16_t dataIn[], unsigned long int dataSize)
    {
        long unsigned int actualIdx = 0; // Index aktualnie pobieranego bajtu danych wejściowych
        string word = "";

        for(int i=0; i< 256; i++)
        {
            dictionary[i] = i; // wypełnianie słownika alfabetem
            nWords++;
        }

        // Dekodowanie danych dopóki mamy dane na wejściu
        for(;actualIdx < dataSize; actualIdx++)
        {

        }
    }
}
