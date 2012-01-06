#ifndef FILEFORMAT_H
#define FILEFORMAT_H

/**
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


#endif // FILEFORMAT_H
