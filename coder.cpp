#include "coder.h"
#include "filesformats.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

unsigned const int DICTIONARY_MAX_SIZE = 4096;       /**< maksymalna ilość słów w słowniku */
std::string dictionary[DICTIONARY_MAX_SIZE];         /**< słownik przechowujący słowa zapisane w ciągu bajtów (string) */
unsigned int nWords = 0;                             /**< ilość słów w słowniku */

float maxRGB(float R, float G, float B)
{
    if(R >= G && R >= B) return R;
    if(G >= R && G >= B) return G;
    if(B >= R && B >= G) return B;
}
float minRGB(float R, float G, float B)
{
    if(R <= G && R <= B) return R;
    if(G <= R && G <= B) return G;
    if(B <= R && B <= G) return B;
}
/**
 *  Konwertuje obraz zapisany w formacie HSV, gdzie każda składowa jest liczbą całkowitą z zakresu 0-255.
 *  Normalnie zakres H wynosi 0 - 360 stopni, tutaj skalowany tak, aby zmieścić się w 0-255
 */
void RGBtoHSV(unsigned char* RGBData, unsigned long int size)
{
    float H, S, V, R, G, B,
          M, m, C, alpha, beta;
ofstream out("HSV Image.txt");
    for(unsigned long int  i=0; i < size; i+=3)
    {
        // Przeskaluj przed wykoaniem algorytmu RGB do przedziału [0,1]
        R = (float)RGBData[i]/255.0;
        G = (float)RGBData[i + 1]/255.0;
        B = (float)RGBData[i + 2]/255.0;

        M = maxRGB(R, G, B);
        m = minRGB(R, G, B);
        C = M - m;

        out << "RGB(" << (int)(R*255.0) << ", " << (int)(G*255.0) << ", " << (int)(B*255.0) << ") = ";

        alpha = (2.0*R - G - B)/2.0;
        beta = sqrt(3)*(G - B)/2.0;
        C = sqrt(alpha*alpha + beta*beta);

        // Oblicz Hue
        H = 60.0 * atan2(beta, alpha);
        if(H < 0.0)
            H += 360.0;

        // Oblicz Value
        V = M;

        // Oblicz Saturation
        if(C == 0)
        {
            S = 0;
        }
        else
        {
            S = C/V;
        }

        RGBData[i] = H/360.0 * 255.0;
        RGBData[i + 1] = S * 255; // Przeskaluj [0,1] -> [0, 255]
        RGBData[i + 2] = V * 255; // Przeskaluj [0,1] -> [0, 255]

        out << " HSV(" << H << ", " << S << ", " << V << ")" << endl;
    }
    out.close();
}

/**
 *  Konwertuje obraz zapisany w formacie HSL, gdzie każda składowa jest liczbą całkowitą z zakresu 0-255.
 *  Normalnie zakres H wynosi 0 - 360 stopni, tutaj skalowany tak, aby zmieścić się w 0-255
 */
void RGBtoHSL(unsigned char* RGBData, unsigned long int size)
{
    float H, S, L, R, G, B,
          M, m, C, alpha, beta;
ofstream out("HSL Image.txt");
    for(unsigned long int  i=0; i < size; i+=3)
    {
        // Przeskaluj przed wykoaniem algorytmu RGB do przedziału [0,1]
        R = (float)RGBData[i]/255.0;
        G = (float)RGBData[i + 1]/255.0;
        B = (float)RGBData[i + 2]/255.0;

        M = maxRGB(R, G, B);
        m = minRGB(R, G, B);
        C = M - m;

        out << "RGB(" << (int)(R*255.0) << ", " << (int)(G*255.0) << ", " << (int)(B*255.0) << ") = ";

        alpha = (2.0*R - G - B)/2.0;
        beta = sqrt(3)*(G - B)/2.0;
        C = sqrt(alpha*alpha + beta*beta);

        // Oblicz Hue
        H = 60.0 * atan2(beta, alpha);
        if(H < 0.0)
            H += 360.0;

        // Oblicz Lightness
        L = (float)(M + m)/2.0;

        // Oblicz Saturation
        if(C == 0)
        {
            S = 0;
        }
        else
        {
            S = (float)C/(float)(1 - fabs(2*L - 1));
        }

        RGBData[i] = H/360.0 * 255.0;
        RGBData[i + 1] = S * 255; // Przeskaluj [0,1] -> [0, 255]
        RGBData[i + 2] = L * 255; // Przeskaluj [0,1] -> [0, 255]

        out << " HSL(" << H << ", " << S << ", " << L << ")" << endl;
    }
    out.close();
}


/**
 *  Konwertuje obraz zapisany w formacie YUV, gdzie każda składowa jest liczbą całkowitą z zakresu 0-255.
 */
void RGBtoYUV(unsigned char* RGBData, unsigned long int size)
{
    unsigned char Y, U, V,
                  R, G, B;

    ofstream out("YUB Image.txt");
    for(unsigned long int  i=0; i < size; i+=3)
    {
        R = RGBData[i];
        G = RGBData[i + 1];
        B = RGBData[i + 2];

        Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16;
        U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128;
        V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128;

        out << (int)Y << " " << (int)U << " " << (int)V << endl;

        RGBData[i] = Y;
        RGBData[i + 1] = U;
        RGBData[i + 2] = V;
    }
    out.close();
}



bool coder::run(const char* pathIn, const char* pathOut, const char* colorSpace, const char* filter)
{
    BITMAPINFOHEADER bmpih;
    unsigned char* bitmapImageData = 0;
    FILEINFO fileinfo;
    std::list<uint2x12_t> *compressedImage;
    unsigned int numberOf12 = 0;

    cout << "URUCHOMIONO KODER" << endl;
    cout << "Plik wejsciowy: " << pathIn << endl;
    cout << "Plik wyjsciowy: " << pathOut << endl;
    cout << "    Przestrzen barw: " << colorSpace << endl;
    cout << "    Filtr: " << filter << endl;

    bitmapImageData = loadBMPFile(pathIn, &bmpih);
    if(!bitmapImageData)
        return false;

    // TODO filtry

    switch(getColorSpaceID(colorSpace))
    {
        case RGB:
                  break;

        case HSL: RGBtoHSL(bitmapImageData, bmpih.biSizeImage);
                  break;

        case HSV: RGBtoHSV(bitmapImageData, bmpih.biSizeImage);
                  break;

        case YUV: RGBtoYUV(bitmapImageData, bmpih.biSizeImage);
                  break;
        default:
                 cout << "Otrzymano nieobslugiwana przestrzen barw!\n";
                 return false;
    }

    compressedImage = lzw(bitmapImageData, bmpih.biSizeImage, &numberOf12);

    /*cout << "compressedImage contains:";
    list<uint2x12_t>::iterator it;
    for( it=compressedImage->begin() ; it != compressedImage->end(); it++ )
    {
        cout << " " << it->v1;
        cout << " " << it->v2;
    }*/

    fileinfo.fileType = ':)';
    fileinfo.colorSpace = getColorSpaceID(colorSpace);
    fileinfo.bpp = 24;
    fileinfo.width = bmpih.biWidth;
    fileinfo.height = bmpih.biHeight;
    fileinfo.numberOf12 = numberOf12;

    if(!saveFile(pathOut, &fileinfo, compressedImage))
        return false;

    cout << "\nOperacja kodowania do formatu .abmp wykonana pomyślnie.\n";
    return true;
}

/**
 *  @brief Funkcja sprawdza na jakiej pozycji w słowniku znajduje się dane słowo.
 *  @param word Słowo do sprawdzenia.
 *  @return Indeks słowa jeśli jest w słowniku, w przeciwnym wypadku -1;
 */
int getDictionaryIdx(string word)
{
    for(int i=0; i < nWords; i++)
    {
        if(word == dictionary[i])
        {
            return i;
        }
    }

    return -1;
}

/**
 *  @brief Funkcja kompresująca dane wejściowe algorytmem LZW.
 *  @param data Dane wejściowe, które podlegają kompresji.
 *  @param dataSize Rozmiar danych wejściowych.
 *  @param numberOf12 Ilość 12-bitowych indeksów powstałych na skutek kompresji.
 *  @return Skompresowane dane wyjściowe.
 */
std::list<uint2x12_t>* coder::lzw(unsigned char* data, unsigned long int dataSize, unsigned int *numberOf12_in)
{
    nWords = 0; // Zeruj zmienna globalna z iloscia slow przed kazda kompresja
    unsigned int numberOf12 = 0; // Ilość zapisanych dwunastobitowych indeksów
    std::list<uint2x12_t> *compressedData = new std::list<uint2x12_t>;
    unsigned long int actualIdx = 0; // Index aktualnie pobieranego bajtu danych wejściowych
    string word = "";

    for(int i=0; i< 256; i++)
    {
        dictionary[i] = i; // wypełnianie słownika alfabetem
        nWords++;
    }


    uint2x12_t tmp;
    // Kodowanie danych dopóki mamy dane na wejściu
    while(actualIdx < dataSize)
    {
        if(getDictionaryIdx(word + (char)data[actualIdx]) < 0)
        {
            // Jeżeli nie ma słowa z aktualnym znakiem w słowniku to zapisuj pod odpowiednie pola uint2x12_t
            if(numberOf12 % 2 == 0)
                tmp.v1 = getDictionaryIdx(word);
            else
                tmp.v2 = getDictionaryIdx(word);
            numberOf12++;

            // Co dwie 12-stki zapisuj uint2x12_t na listę
            if(numberOf12 % 2 == 0)
            {
                compressedData->push_back(tmp);
            }

            if(nWords < DICTIONARY_MAX_SIZE)
            {
                dictionary[nWords] = word + (char)data[actualIdx]; // dodaj słowo z aktualnym znakiem do słownika
                nWords++;
            }

            word=""; // Wyzeruj słowo, poniżej dodawany jest do niego aktualny znak
        }

        // Dodaj aktualny znak i przesuń się na następny
        word += data[actualIdx];

        actualIdx++;
    }

    // Wypisz indeks tego co zostało
    if(numberOf12 % 2 == 0)
    {
        // Jeżeli zapisało już parzystą liczbę 12-stek (pełną uint2x12_t) to dołóż niepatrzystą 12-stkę - ostatnia wartość ignorowana
        tmp.v1 = getDictionaryIdx(word);
        tmp.v2 = 0;
        compressedData->push_back(tmp);
    }
    else
    {
        // Jeżeli jest nieparzysta licza 12-stek to do aktualnej uint2x12_t dołóż niepatrzystą 12-stkę
        tmp.v2 = getDictionaryIdx(word);
        compressedData->push_back(tmp);
    }

    *numberOf12_in = numberOf12;
    return compressedData;
};
