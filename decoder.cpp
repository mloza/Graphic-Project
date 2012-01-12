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
