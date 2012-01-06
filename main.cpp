#include <iostream>
#include <fstream>

// Pliki wspólne
#include "uint2x12_t.h"
#include "fileformat.h"

// Pliki do kodera
#include "coder.h"

// Pliki do dekodera
#include "decoder.h"

using namespace std;

struct colors {
    void RGBToYUV() {}
    void RGBToHSV() {}
    void RGBToHSL() {}

    void YUVToRGB() {}
    void HSVToRGB() {}
    void HSLToRGB() {}
};

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
 *  argv[2] = ścieżka do pliku BMP który wczytujemy, albo do którego zapisujemy
 *            (w zależności od trybu działania)
 *  argv[3] = tryb koloru w jakim przechowywany będzie obraz w naszym formacie
 *            RGB
 *            HSV
 *            HSL
 *  argv[4] = wybrany filtr
 *
 */
int main(int argc, char** argv)
{
    //Zapis
    fstream file("file.bpam", ios::binary|ios::out);

    fileinfo* f = new fileinfo;
    f->bpc = 24;
    f->colors = 4;
    f->width = 100;
    f->height = 100;

    file << ':' << ')';
    file.write((char*)&f, sizeof(fileinfo));
    file.close();
//    delete file; // TODO: Co to jest? Nie powinno być delete f?

    //Odczyt informacji
    file.open("file.bpam", ios::binary|ios::in);

    char signs[2];
    file >> signs[0] >> signs[1];

    if(signs[0] == ':' && signs[1] == ')')
    {
        cout << "Plik typu bpam, odczytano nastepujace liczby:\n" ;
        f = new fileinfo;
        file.read((char*)&f, sizeof(fileinfo));
        cout << f->colors << endl << f->bpc << endl << f->width << endl << f->height;
    } else {
        cout << "Nieprawidłowy typ pliku";
    }

    /* ==== TEST KODOWANIA LZW  ==== */
    char tablica[36]={0,0,0,1,1,1,1,2,0,0,3,1,3,2,2,0,0,0,3,3,3,3,1,2,1,2,3,1,2,0,0,1,1,1,3,3};
    cout << "\n\nTEST KODOWANIA LZW:\n";
    coder::lzw(tablica, 36);

    return 0;
}
