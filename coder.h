#ifndef CODER_H_INCLUDED
#define CODER_H_INCLUDED

#include <string>
#include <list>
#include <inttypes.h>
#include "uint2x12_t.h"

using namespace std;
namespace coder {
    /**
     *  @brief Funkcja uruchamiająca koder realizujący wczytanie pliku BMP i zapisanie obrazu w naszym formacie.
     *  @param pathIn Ścieżka do pliku wejściowego BMP.
     *  @param pathOut Ścieżka gdzie zapisuje plik ABMP.
     *  @return True jeśli wszystko przebiegło pomyślnie.
     */
    bool run(const char* pathIn, const char* pathOut);

    /**
     *  @brief Funkcja kompresująca dane wejściowe algorytmem LZW.
     *  @param data Dane wejściowe, które podlegają kompresji.
     *  @param dataSize Rozmiar danych wejściowych.
     *  @return Skompresowane dane wyjściowe.
     */
    std::list<uint2x12_t>* lzw(unsigned char* data, unsigned long int dataSize);
}

#endif // CODER_H_INCLUDED
