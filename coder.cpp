#include "coder.h"
#include "filesformats.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string toStr(int a)
{
    stringstream ss;
    ss << a;
    return ss.str();
}

unsigned const int DICTIONARY_MAX_SIZE = 4096;       /**< maksymalna ilość słów w słowniku */
std::string dictionary[DICTIONARY_MAX_SIZE];         /**< słownik przechowujący słowa zapisane w ciągu bajtów (string) */
unsigned int nWords = 0;                             /**< ilość słów w słowniku */

bool coder::run(const char* pathIn, const char* pathOut)
{
    BITMAPINFOHEADER bmpih;
    unsigned char* bitmapImageData = 0;
    FILEINFO fileinfo;
    std::list<uint2x12_t> *compressedImage;

    std::cout << "URUCHOMIONO KODER\nRozpoczynam konwersje pliku BMP do formatu ABMP (RGB, bez filtra)" << endl;
    bitmapImageData = loadBMPFile(pathIn, &bmpih);
    if(!bitmapImageData)
    {
        cout << "Nie udalo wczytac sie pliku BMP " << pathIn << endl;
        return false;
    }

    // TODO filtry i wybór koloru

    compressedImage = lzw(bitmapImageData, bmpih.biSizeImage);

    /*cout << "compressedImage contains:";
    list<uint2x12_t>::iterator it;
    for( it=compressedImage->begin() ; it != compressedImage->end(); it++ )
    {
        cout << " " << it->v1;
        cout << " " << it->v2;
    }*/

    fileinfo.fileType = ':)';
    fileinfo.colorSpace = 0; // TODO :ZMIENIĆ
    fileinfo.bpp = 24;
    fileinfo.width = bmpih.biWidth;
    fileinfo.height = bmpih.biHeight;
    fileinfo.numberOf12;

    saveFile(pathOut, &fileinfo, compressedImage);


}

/*
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
 *  @return Skompresowane dane wyjściowe.
 */
std::list<uint2x12_t>* coder::lzw(unsigned char* data, unsigned long int dataSize)
{
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

    return compressedData;
};
