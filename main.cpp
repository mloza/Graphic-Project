#include <iostream>

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
    cout << "Hello world!" << endl;
    return 0;
}
