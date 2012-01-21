#include <iostream>
#include <cstring>
#include <fstream>
#include <list>

// Pliki wspólne
#include "uint2x12_t.h"
#include "filesformats.h"
#include "options.h"

// Pliki do kodera
#include "coder.h"

// Pliki do dekodera
#include "decoder.h"

using namespace std;

/**
 *  @brief Główna funkcja programu.
 *
 *  Program działa jako koder lub dekoder, w zależności od przekazanego argumentu, za ich pomocą
 *  dokonujemy także niezbędnej konfiguracji.
 *
 *  argv[0] = zawsze ścieżka do pliku wykonywalnego tego programu
 *  argv[1] = tryb działania, możliwe wartości:
 *            CODER - program konwertuje plik BMP do naszego formatu
 *            DECODER - program dekoduje plik z naszego formatu do BMP
 *  argv[2] = ścieżka do pliku BMP/ABMP który wczytujemy - zależy od trybu działania.
 *  argv[3] = ścieżka do pliku ABMP/BMP który zapisujemy - zależy od trybu działania.
 *  argv[4] = tryb koloru w jakim przechowywany będzie obraz w naszym formacie
 *            RGB
 *            HSV
 *            HSL
 *            YUV
 *  argv[5] = wybrany filtr
 *
 */
int main(int argc, char** argv)
{
 /*   if(argc < 4)
    {
        // TODO: Zrobic tutaj opis..
        cout << "Sposob uzycia:\n";

        return -1;
    }

    if(strcmp(argv[1], "CODER") == 0)
    {
        coder::run(argv[2], argv[3], argv[4], argv[5]);
    }
    else
    if(strcmp(argv[1], "DECODER") == 0)
    {
        decoder::run(argv[2], argv[3]);
    }
*/
    coder::run("test-files/01-300x200x24bit.bmp", "skompresowany.abmp", "RGB", "NONE"); // DO TESTOW RECZNE USTAWIANIE PARAMETROW

    decoder::run("skompresowany.abmp", "result.bmp"); // DO TESTOW RECZNE USTAWIANIE PARAMETROW

    return 0;
}
