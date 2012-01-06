#ifndef FILESFORMATS_H
#define FILESFORMATS_H

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


#endif // FILESFORMATS_H

