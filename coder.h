#ifndef CODER_H_INCLUDED
#define CODER_H_INCLUDED

#include <string>

using namespace std;

namespace coder {
    /**
     *  Funkcja uruchamiająca koder realizujący wczytanie pliku BMP i zapisanie obrazu w naszym formacie.
     */
    void run();

    /**
     *  @brief Funkcja kompresująca dane wejściowe algorytmem LZW.
     *  @param data Dane wejściowe, które podlegają kompresji
     *  @param dataSize Rozmiar danych wejściowych
     */
    void lzw(char* dataIn, unsigned long int dataSize);

    unsigned const int DICTIONARY_MAX_SIZE = 4096;       /**< maksymalna ilość słów w słowniku */
    extern string dictionary[DICTIONARY_MAX_SIZE];       /**< słownik przechowujący słowa zapisane w ciągu bajtów (string) */
    extern unsigned int nWords;                          /**< ilość słów w słowniku */
}

#endif // CODER_H_INCLUDED
