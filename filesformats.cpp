#include "filesformats.h"
#include <iostream>
#include <fstream>
#include <math.h>

bool loadFile()
{
    return true;
}

bool saveFile(const char* path, FILEINFO* fileinfo, std::list<uint2x12_t> *data)
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

    // Zapisz obraz wyciągając elementy z listy
    list<uint2x12_t>::iterator it;
    for( it=data->begin() ; it != data->end(); it++ )
    {
        out.write((char*)&(*it), sizeof(uint2x12_t));
    }

    //out.write((char*)data, round(fileinfo->numberOf12/2) * sizeof(uint2x12_t));

    out.close();

    return true;
}

unsigned char* loadBMPFile(const char* path, BITMAPINFOHEADER *bitmapInfoHeader)
{
    BITMAPFILEHEADER bitmapFileHeader; // nagłówek pliku
    int imageIdx = 0; // licznik bajtów obrazu
    unsigned char *data;

    // otwarcie pliku w trybie binarnym
    ifstream infile;
    infile.open(path, ios::binary);
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

    ofstream test("OBRAZ_BMP.txt");
        // zamiana na format RGB z formatu BGR (BGR jest domyślnie w BMP)
        for(imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3 )
        {
            swap(data[imageIdx], data[imageIdx+2]);
            test << (int)data[imageIdx]<< " " << (int)data[imageIdx + 1] << " " << (int)data[imageIdx + 2] << endl;
        }
test.close();

        infile.close();
        return data;
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku!" << endl;
        return 0;
    }
}

bool saveBMPFile(const char* path, int width, int height, unsigned char *imageData)
{
    // Tworzenie nagłóków pliku
    BITMAPFILEHEADER *bfh = new BITMAPFILEHEADER;
    bfh->bfSize = sizeof(BITMAPINFOHEADER);
    bfh->bfType = 0x4D42;
    bfh->bfReserved1 = 0;
    bfh->bfReserved2 = 0;
    bfh->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    BITMAPINFOHEADER *bih = new BITMAPINFOHEADER;
    bih->biSize = sizeof(BITMAPINFOHEADER);
    bih->biPlanes = 1;
    bih->biBitCount = 24;
    bih->biCompression = 0;//BI_RGB;
    bih->biSizeImage = width * height * 3;
    bih->biXPelsPreMeter = 0;
    bih->biYPelsPerMeter = 0;
    bih->biClrUsed = 0;
    bih->biClrImportant = 0;
    bih->biWidth = width;
    bih->biHeight = height;

    // odwracanie kolorów RGB -> GBR
    unsigned char tempRGB;
    for(unsigned int imageIdx = 0; imageIdx < bih->biSizeImage; imageIdx += 3)
    {
        tempRGB = imageData[imageIdx];
        imageData[imageIdx] = imageData[imageIdx+2];
        imageData[imageIdx + 2] = tempRGB;
    }

    //otwieranie pliku
    ofstream file(path, ios::binary);

     //zapisujemy nagłówki
    file.write((char*)bfh, sizeof(BITMAPFILEHEADER));
    file.write((char*)bih, sizeof(BITMAPINFOHEADER));

    //zapisujemy dane kierunek: lewy dolny róg  -> prawy górny róg
    for(int i=bih->biHeight-1; i>=0; i--)
    {
        int j;
        for(j=0; j < bih->biWidth*3; j++)
        {
            file << (char)imageData[i*bih->biWidth*3+j];
            cout << i*bih->biWidth*3+j << " ";
        }
        // dopełnienie
        while(j%4 != 0)
        {
            file << (char)0;
            j++;
        }
    }

    //zamykamy plik
    file.close();
    return true;
}
