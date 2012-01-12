#ifndef FILESFORMATS_H
#define FILESFORMATS_H

#include <inttypes.h>
#include "uint2x12_t.h"
#include <string>
#include <list>
#include <vector>
using namespace std;
/* ========================================================================= */
/* ================= CZĘŚĆ DOTYCZĄCA NASZEGO FORMATU ======================= */

/**
 * @brief Struktura nagłówka pliku naszego formatu.
 *
 * /TODO Okomentować to.
 */
struct FILEINFO {
    uint16_t fileType;
    uint8_t colorSpace;
    uint8_t bpp;
    uint32_t width;
    uint32_t height;
    uint32_t numberOf12;
};

/**
 *  @brief Funckja odczytuje plik naszego formatu.
 *
 *  @param path Ścieżka do pliku
 *  @param fileinfo Nagłówek pliku.
 *  @param data Skompresowane dane obrazu.
 *
 */
bool loadFile(const char* path, FILEINFO* fileinfo, std::list<uint2x12_t> *data);

/**
 *  @brief Funckja tworząca plik naszego formatu.
 *
 *  @param path Ścieżka do pliku wynikowego.
 *  @param fileinfo Uzupełniona struktura nagłówka naszego formatu.
 *  @param data Skompresowane dane obrazu.
 *
 */
bool saveFile(const char*, FILEINFO* fileinfo, std::list<uint2x12_t> * data);

/* ========================================================================= */
/* ================= CZĘŚĆ DOTYCZĄCA FORMATU BMP =========================== */

#pragma pack(push)       /* zapamiętaj bieżącą wartość wyrównania struktur */
#pragma pack(1)          /* brak wyrównania */
/**
 *  @brief Nagłówek pliku BMP
 *
 *  (opis pól w dokumentacji formatu BMP)
 */
struct BITMAPFILEHEADER
{
     uint16_t bfType;
     uint32_t bfSize;
     uint16_t bfReserved1;
     uint16_t bfReserved2;
     uint32_t bfOffBits;
};

/**
 *  @brief Nagłówek z informacjami o obrazie BMP.
 *
 *  (opis pól w dokumentacji formatu BMP)
 */
struct BITMAPINFOHEADER
{
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPreMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)


/**
 *  @brief Funckja wczytująca plik w formacie *.BMP.
 *
 *  @param path Ścieżka do pliku, który chcemy odczytać.
 *  @param bitmapInfoHeader Parametr wyjściowy funkcji, w którym zostanie przekazany nagłówek pliku BMP.
 *  @param data Wskaźnik pod którym zostanie zapisany odczytany obraz (przydział pamięci jest realizowany dynamicznie w funkcji, użytkownik sam musi ją zwolnić).
 *
 */

unsigned char* loadBMPFile(const char* path, BITMAPINFOHEADER *bitmapInfoHeader);

/**
 *  @brief Funckja zapisuje plik w formacie *.BMP.
 *
 *  @param path Ścieżka do pliku, który chcemy zapisać.
 *  @param bitmapInfoHeader Parametr wejściowy funkcji, w którym zostanie przekazany nagłówek pliku BMP.
 *  @param data Wskaźnik pod którym powinny znajdowac się dane obarzu do zapisania
 *
 */
bool saveBMPFile(const char* path, int width, int height, std::vector<unsigned char> data);

#endif // FILESFORMATS_H

