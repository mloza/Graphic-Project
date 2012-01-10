#ifndef FILESFORMATS_H
#define FILESFORMATS_H

#include <inttypes.h>
#include "uint2x12_t.h"
/* ========================================================================= */
/* ================= CZĘŚĆ DOTYCZĄCA NASZEGO FORMATU ======================= */

/**
 * @brief Struktura nagłówka pliku naszego formatu.
 *
 * /TODO Okomentować to.
 */
struct FILEINFO {
    uint8_t colors;
    uint8_t bpc; //bits per color TODO: A moze bpp, czyli na piksel ? Np. 24 w naszym wypadku
    uint32_t width;
    uint32_t heigh;
    uint64_t numberOf12;
};


bool loadFile();

/**
 *  @brief Funckja tworząca plik naszego formatu.
 *
 *  @param path Ścieżka do pliku wynikowego.
 *  @param fileinfo Uzupełniona struktura nagłówka naszego formatu.
 *  @param data Skompresowane dane obrazu.
 *
 */
bool saveFile(const char*, FILEINFO* fileinfo, uint2x12_t* data);

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

bool loadBMPFile();
bool saveBMPFile();

#endif // FILESFORMATS_H
