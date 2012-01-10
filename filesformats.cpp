#include "filesformats.h"
#include <iostream>
#include <fstream>
#include <math.h>

bool loadFile()
{
    return true;
}

bool saveFile(const char* path, FILEINFO* fileinfo, uint2x12_t* data)
{
    // Otwórz plik do zapisu binarnego
    std::ofstream out(path, std::ios::binary);
    if(!out.good())
    {
        std::cout << "Utworzenie pliku " << path << " nie powiodlo sie!\n";
        return false;
    }

    // Zapisz nagłówek z informacjami o pliku
    out.write((char*)fileinfo, sizeof(FILEINFO));

    // Zapisz skompresowany obraz (12 bitowe wartości). Aby otrzymać ilość zapisanych struktur uint2x12_t w przypadku nieparzystej ilości 12-stek zaokrąglam.
    // Przykład: numberOf12 wynosi 5, wtedy 5/2 = 2.5, zaokrągamy do 3 i mamy ilość zapisanych struktur uint2x12_t i mnożymy przez rozmiar struktur (3 bajty).
    out.write((char*)data, round(fileinfo->numberOf12/2) * sizeof(uint2x12_t));

    out.close();

    return true;
}

bool loadBMPFile()
{
    return true;
}

bool saveBMPFile()
{
    return true;
}
