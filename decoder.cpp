#include <iostream>
#include <fstream>
#include "decoder.h"
#include <vector>
#include "filesformats.h"

using namespace std;

namespace decoder
{
unsigned const int DICTIONARY_MAX_SIZE = 8192;      /** < maksymalna ilość słów w słowniku */
string dictionary[DICTIONARY_MAX_SIZE];             /** < słownik przechowujący słowa zapisane w ciągu bajtów (string) */
unsigned int nWords;                                /** < ilość słów w słowniku */

int clip(int upper, int lower, int val)
{
    if(val>upper)
        return upper;
    else if(val<lower)
        return lower;
    else return val;

}

std::vector<unsigned char> YUVtoRGB(std::vector<unsigned char> data, FILEINFO* fileinfo)
{
    int y,u,v;
    int r,g,b;

    ofstream f("plik.txt");
    f << "W: " << fileinfo->width << "x" << fileinfo->height << "\n";
    f << fileinfo->height*fileinfo->width << "\n";
    for(int i=0; i<fileinfo->height*fileinfo->width*3; i+=3)
    {
            f << i << "\n";
            // dla prostrzego rachunku przypisujemy sobie do nowych zmiennych Y, U, i V
            y = data[i];
            u = data[i+1];
            v = data[i+2];
            // przeliczamy na RGB
            y-=16;
            u-=128;
            v-=128;
            r = clip(0, 255, ((298*y+409*v+128) >> 8));
            g = clip(0, 255, ((298*y-100*u-208*v+128) >> 8));
            b = clip(0, 255, ((298*y+516*u+128) >> 8));

            data[i] = r;
            data[i+1] = g;
            data[i+2] = b;
    }

    return data;
}

bool run(const char* pathIn, const char* pathOut)
{
    cout << "\n====== URUCHAMIAM DEKODER =====\n";
    cout << "Laduje plik\n";
    FILEINFO* fileinfo = new FILEINFO;
    std::list<uint2x12_t>* filedata = new std::list<uint2x12_t>;
    loadFile(pathIn, fileinfo, filedata);
    cout << "Wymiary: " << fileinfo->width << " x " << fileinfo->height << "\n";

    cout << "+++ Plik zaladowany, dekodowanie +++\n";
    cout << "Ilosc 12: " << fileinfo->numberOf12;
    std::vector<unsigned char> rawData = lzw(filedata);

    //if(fileinfo->colorSpace == 3)
    //{
        rawData = YUVtoRGB(rawData, fileinfo);
    //}

    saveBMPFile("decompressed.bmp", fileinfo->width, fileinfo->height, rawData);

    /*std::ofstream f2("t.txt");
    list<uint2x12_t>::iterator it;
    for(it=rawData->begin(); it != rawData->end(); it++)
    {
        f2 << *it << " ";
    }*/
}

std::vector<unsigned char> lzw(std::list<uint2x12_t>* dataIn)
{
    std::vector<unsigned char> dict[DICTIONARY_MAX_SIZE];
    std::vector<unsigned char> result;

    cout << "Dekoduje \n";
    for(int i=0; i< 256; i++)
    {
        dict[nWords].push_back(i); // wypełnianie słownika alfabetem
        nWords++;
    }

    list<uint2x12_t>::iterator it;

    unsigned int act;
    std::vector<unsigned char> pc;
    unsigned int pk = dataIn->begin()->v1;

    std::ofstream f("t.txt", ios::out);
    f << "a";
    result.push_back(dict[pk][0]);
    //obliczenia dla pierwszego v2
    //jeśli jest w słowniku
    act = dataIn->begin()->v2;
    pc = dict[pk];
    if(act < nWords)
    {
        // zapisz do słownika poprzedni i pierwszy symbol aktualnego
        for(int i = 0; i<pc.size(); i++)
            dict[nWords].push_back(pc[i]);
        dict[nWords].push_back(dict[act][0]);
        nWords++;
        // na wyjście wypisz cały aktualny
        for(int j = 0; j<dict[act].size(); j++)
        {
            result.push_back(dict[act][j]);

        }
    }
    else
    {
        //inaczej dodaj do słownika pc + pierwszy symbol pc;
        for(int i = 0; i<pc.size(); i++)
            dict[nWords].push_back(pc[i]);
        dict[nWords].push_back(pc[0]);
        for(int j = 0; j<dict[nWords].size(); j++)
        {
            result.push_back(dict[nWords][j]);

        }
        nWords++;
    }
    pk = act;

    for(it=++dataIn->begin(); it != dataIn->end(); it++)
    {
        act = it->v1;
        for(int i = 0; i<2; i++)
        {
            //jeśli jest w słowniku
            pc = dict[pk];
            if(act < nWords)
            {
                // zapisz do słownika poprzedni i pierwszy symbol aktualnego jeśli jest miejsce
                if(nWords < DICTIONARY_MAX_SIZE)
                {
                    for(int i = 0; i<pc.size(); i++)
                        dict[nWords].push_back(pc[i]);
                    dict[nWords].push_back(dict[act][0]);
                    nWords++;
                }
                // na wyjście wypisz cały aktualny
                for(int j = 0; j<dict[act].size(); j++)
                {
                    result.push_back(dict[act][j]);

                }
            }
            else
            {
                //inaczej dodaj do słownika pc + pierwszy symbol pc;
                for(int i = 0; i<pc.size(); i++)
                    dict[nWords].push_back(pc[i]);
                dict[nWords].push_back(pc[0]);
                for(int j = 0; j<dict[nWords].size(); j++)
                {
                    result.push_back(dict[nWords][j]);
                }
                nWords++;
            }
            pk = act;
            act = it->v2;
        }
        f << nWords << "\n";
        pk = act;
    }
    cout << "\nKoniec dekodowania \n";
    f.close();
    return result;
}
}
