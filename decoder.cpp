#include <iostream>
#include <fstream>
#include "decoder.h"
#include <vector>
#include "filesformats.h"
#include "filters.h"
#include "defilters.h"

#include <math.h>
using namespace std;

namespace decoder
{
unsigned const int DICTIONARY_MAX_SIZE = 4096;      /** < maksymalna ilość słów w słowniku */
string dictionary[DICTIONARY_MAX_SIZE];             /** < słownik przechowujący słowa zapisane w ciągu bajtów (string) */
unsigned int nWords;                                /** < ilość słów w słowniku */

int clip(int lower, int upper, int val)
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

    for(int i=0; i<fileinfo->height*fileinfo->width*3; i+=3)
    {
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

std::vector<unsigned char> HSLtoRGB(std::vector<unsigned char> data, FILEINFO* fileinfo)
{
    double h,s,l, hp, c, x, m, hp2;
    double r,g,b;
    int tmp;

    for(int i=0; i<fileinfo->height*fileinfo->width*3; i+=3)
    {
            // dla prostrzego rachunku przypisujemy sobie do nowych zmiennych Y, U, i V
            h = data[i];
            s = data[i+1];
            l = data[i+2];
            // skalowanie h: 0-360, s i l 0-1
            h = h*360./255.;
            s = s/255.;
            l = l/255.;

            // chroma
            c = (1-fabs(2.*l-1.))*s;
            // liczymy h'
            hp2 = hp = h/60;

            //mod dla double
            tmp = hp;
            hp2 -= tmp;
            tmp = tmp%2;
            hp2 += tmp;

            x = c*(1-fabs(hp2-1));

            if(hp>=5)
                { r = c; g = 0; b = x; }
            else if(hp>=4)
                { r = x; g = 0; b =c; }
            else if(hp>=3)
                { r = 0; g = x; b = c; }
            else if(hp>=2)
                { r = 0; g = c; b = x; }
            else if(hp>=1)
                { r = x; g = c; b = 0; }
            else if(hp>=0)
                { r = c; g = x; b = 0; }

            m = l-c/2;
            r+=m;
            g+=m;
            b+=m;

            data[i] = r*255;
            data[i+1] = g*255;
            data[i+2] = b*255;
    }

    return data;
}

std::vector<unsigned char> HSVtoRGB(std::vector<unsigned char> data, FILEINFO* fileinfo)
{
    double h,s,v, hp, c, x, m, hp2;
    double r,g,b;
    int tmp;

    for(int i=0; i<fileinfo->height*fileinfo->width*3; i+=3)
    {
            // dla prostrzego rachunku przypisujemy sobie do nowych zmiennych Y, U, i V
            h = data[i];
            s = data[i+1];
            v = data[i+2];

            h = h*360./255.;
            s = s/255.;
            v = v/255.;

            // chroma
            c = v*s;
            // liczymy h'
            hp2 = hp = h/60;

            tmp = hp;
            hp2 -= tmp;
            tmp = tmp%2;
            hp2 += tmp;

            x = c*(1-fabs(hp2-1));

            if(hp>=5)
                { r = c; g = 0; b = x; }
            else if(hp>=4)
                { r = x; g = 0; b =c; }
            else if(hp>=3)
                { r = 0; g = x; b = c; }
            else if(hp>=2)
                { r = 0; g = c; b = x; }
            else if(hp>=1)
                { r = x; g = c; b = 0; }
            else if(hp>=0)
                { r = c; g = x; b = 0; }

            m = v-c;
            r+=m;
            g+=m;
            b+=m;

            data[i] = r*255;
            data[i+1] = g*255;
            data[i+2] = b*255;
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

    if(fileinfo->fileType != ':)')
    {
        cout << "Nieprawidłowy plik \n";
        return false;
    }

    cout << "+++ Plik zaladowany, dekodowanie +++\n";
    cout << "Ilosc 12: " << fileinfo->numberOf12 << endl;
    std::vector<unsigned char> rawData = lzw(filedata);

    filters::paeth_filter(rawData, fileinfo->width, fileinfo->height);
    defilter::paeth(rawData, fileinfo->width, fileinfo->height);

    switch(fileinfo->filterType)
    {
        case 1:
            //defilter::differential(rawData, fileinfo->width, fileinfo->height);
            break;
        case 2:

            break;
        case 3:

            break;
    }

    switch(fileinfo->colorSpace)
    {
        case 1:
            rawData = HSVtoRGB(rawData, fileinfo);
            break;
        case 2:
            rawData = HSLtoRGB(rawData, fileinfo);
            break;
        case 3:
            rawData = YUVtoRGB(rawData, fileinfo);
            break;
    }

    saveBMPFile(pathOut, fileinfo->width, fileinfo->height, rawData);
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

    result.push_back(dict[pk][0]);
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

    int size = dataIn->size();
    int progress;
    int i = 1;
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
        pk = act;
        if((int)((double)i++/(double)size*100.) != progress)
        {
            progress = (int)((double)i++/(double)size*100.);
            cout << "Trwa dekompresowanie obrazu... [" << progress << "%]\n";
        }
    }
    cout << "\nKoniec dekodowania \n";
    return result;
}
}
