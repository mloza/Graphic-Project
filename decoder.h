#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include <inttypes.h>
#include <string>
#include <list>
#include <vector>
#include "uint2x12_t.h"

using namespace std;
namespace decoder {
    /**
     *  Funkcja uruchamiająca koder realizujący wczytanie pliku BMP i zapisanie obrazu w naszym formacie.
     */
    bool run(const char* pathIn, const char* pathOut);

    /**
     *  @brief Funkcja dekompresująca dane wejściowe algorytmem LZW.
     *  @param data Dane wejsciowe, które podlegają dekompresji
     *  @param dataSize Rozmiar danych wejściowych
     */
    std::vector<unsigned char> lzw(std::list<uint2x12_t>* dataIn);
}

#endif // DECODER_H_INCLUDED
