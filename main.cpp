#include <iostream>
#include <fstream>
#include <list>

// Pliki wspólne
#include "uint2x12_t.h"
#include "filesformats.h"

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
 *  argv[2] = ścieżka do pliku BMP/ABMP który wczytujemy - zależy od trybu działania.
 *  argv[3] = ścieżka do pliku ABMP/BMP który zapisujemy - zależy od trybu działania.
 *  argv[4] = tryb koloru w jakim przechowywany będzie obraz w naszym formacie
 *            RGB
 *            HSV
 *            HSL
 *  argv[5] = wybrany filtr
 *
 */
int main(int argc, char** argv)
{
    //Zapis
/*  fstream file("file.bpam", ios::binary|ios::out);


    FILEINFO* f = new FILEINFO;
    f->bpc = 24;
    f->colors = 4;
    f->width = 100;
    f->height = 100;

    file << ':' << ')';
    file.write((char*)&f, sizeof(fileinfo));
    file.close();

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
    }*/

    /* ==== TEST KODOWANIA LZW  ==== */
    unsigned char tablica[36]={0,0,0,1,1,1,1,2,0,0,3,1,3,2,2,0,0,0,3,3,3,3,1,2,1,2,3,1,2,0,0,1,1,1,3,3};
    cout << "\n\nTEST KODOWANIA LZW:\n";
    std::list<uint2x12_t> *wynik = coder::lzw(tablica, 36);
    list<uint2x12_t>::iterator it;

    cout << "mylist contains:";
    for( it=wynik->begin() ; it != wynik->end(); it++ )
    {
        cout << " " << it->v1;
        cout << " " << it->v2;
    }

    coder::run("test.bmp", "skompresowany.abmp");

    /* ==== TEST DEKODOWANIA LZW ==== */
    // jako dane wejściowe używam wyjścia z poprzedniej funkcji
    uint16_t tablica2[21] = {0,256,1,258,1,2,256,3,1,3,2,261,262,3,269,260,260,263,267,259,269};
    cout << "\n\nTEST DEKODOWANIA LZW:\n";
    decoder::lzw(tablica2, 20);

    /* ==== ZAPIS Bitmapy ==== */
    unsigned char data[12] = { 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 0 };
    saveBMPFile("test.bmp", 2, 2, data);

    return 0;
}
