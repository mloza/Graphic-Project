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

bool loadBMPFile(string path, BITMAPINFOHEADER *bitmapInfoHeader, unsigned char *data)
{

    BITMAPFILEHEADER bitmapFileHeader; // nagłówek pliku
    int imageIdx = 0; // licznik bajtów obrazu


    // otwarcie pliku w trybie binarnym
    ifstream infile;
    infile.open("tst.bmp", ios::binary);
    if(infile.good())
    {
        // wczytanie nagłówka pliku
        infile.read((char *)&bitmapFileHeader, sizeof(BITMAPFILEHEADER));

        // sprawdzenie, czy jest to plik BMP
        if(bitmapFileHeader.bfType != 0x4D42)
        {
            cout << "To nie jest plik BMP!" << endl;
            infile.close();
            return 0;
        }

        // wczytanie nagłówka obrazu zapisanego w pliku
        infile.read((char *)bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

        // ustawienie wskaźnika pliku na początek danych opisujących obraz
        infile.seekg(bitmapFileHeader.bfOffBits,ios::beg);

        // przydzielenie pamięci na bufor obrazu
        data = new unsigned char[bitmapInfoHeader->biSizeImage];

        // sprawdzenie, czy pamięć została przydzielona
        if(!data)
        {
            cout << "Nie udalo sie przydzielic pamieci!" << endl;
            delete [] data;
            infile.close();
            return 0;
        }

        // wczytywanie danych obrazu
        infile.read((char *)data, bitmapInfoHeader->biSizeImage);

        // sprawdzenie, czy operacja się powiodła
        if(data == NULL)
        {
            cout << "Operacja wczytywania danych sie nie powiodla!" << endl;
            infile.close();
            return 0;

        }

        // zamiana na format RGB z formatu BGR (BGR jest domyślnie w BMP)
        for(imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3 )
            swap(data[imageIdx], data[imageIdx+2]);

        infile.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        return 0;
    }
}

bool saveBMPFile()
{
    // just comment to test git
    return true;
}
