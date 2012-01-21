#ifndef CODER_H_INCLUDED
#define CODER_H_INCLUDED

#include <string>
#include <list>
#include <inttypes.h>
#include "uint2x12_t.h"
#include "options.h"
#include "filters.h"

using namespace std;
namespace coder {
    /**
     *  @brief Funkcja uruchamiająca koder realizujący wczytanie pliku BMP i zapisanie obrazu w naszym formacie.
     *  @param pathIn Ścieżka do pliku wejściowego BMP.
     *  @param pathOut Ścieżka gdzie zapisuje plik ABMP.
     *  @param colorSpace W jakiej przestrzeni zapisujemy obraz.
     *  @param filter Filtr który przetwarza dane przed kompresją.
     *  @return True jeśli wszystko przebiegło pomyślnie.
     */
    bool run(const char* pathIn, const char* pathOut, const char* colorSpace, const char* filter);

    /**
     *  @brief Funkcja kompresująca dane wejściowe algorytmem LZW.
     *  @param data Dane wejściowe, które podlegają kompresji.
     *  @param dataSize Rozmiar danych wejściowych.
     *  @param numberOf12 Ilość 12-bitowych indeksów powstałych na skutek kompresji.
     *  @return Skompresowane dane wyjściowe.
     */
    std::list<uint2x12_t>* lzw(unsigned char* data, unsigned long int dataSize, unsigned int *numberOf12_in);
}

#endif // CODER_H_INCLUDED
