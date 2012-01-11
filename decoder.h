#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include <inttypes.h>
#include <string>
#include <list>
#include "uint2x12_t.h"

using namespace std;
namespace decoder {
    /**
     *  Funkcja uruchamiająca koder realizujący wczytanie pliku BMP i zapisanie obrazu w naszym formacie.
     */
    void run();

    /**
     *  @brief Funkcja dekompresująca dane wejściowe algorytmem LZW.
     *  @param data Dane wejsciowe, które podlegają dekompresji
     *  @param dataSize Rozmiar danych wejściowych
     */
    void lzw(std::list<uint2x12_t>* dataIn, unsigned long int dataSize);
}

#endif // DECODER_H_INCLUDED
