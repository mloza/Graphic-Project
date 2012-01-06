#ifndef FILESFORMATS_H
#define FILESFORMATS_H

/* ========================================================================= */
/* ================= CZĘŚĆ DOTYCZĄCA NASZEGO FORMATU ======================= */

/**
 * @brief Struktura nagłówka pliku naszego formatu.
 *
 * /TODO Okomentować to.
 */
struct fileinfo {
    int colors : 8;
    int bpc : 8; //bits per color
    unsigned int width : 32;
    unsigned int height : 32;
};

bool loadFile();
bool saveFile();

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

