#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
namespace filters
{
// Filtr różnicowy, nowa wartość koloru to różnica obecnej komórki i poprzedniej ( data[j] = data[j] - data[j-1] )
// Pierwszy bajt jest pomijany
bool differential_filter(std::vector<unsigned char> &data, int width, int height)
{
    int dataj, prev, aktual;
    prev = data[0];
    for(int j=1; j< width*height*3; j++)
    {
        aktual = dataj = data[j];
        dataj -= prev;
        if(dataj < 0)
            dataj += 256; // jeśli wartości są mniejsze od 0 to dodajemy 256
        data[j] = dataj;
        prev = aktual;
    }
}

// filtr w górę,  nowa wartość koloru to różnica obecnej komórki i komórki powyżej ( data[j] = data[j] - data[j-width])
// pierwszy wiersz jest pomijany
void up_filter(unsigned char *data, int width, int height)
{
    int dataj, prev, aktual;
    int upTmp[3*width];
    for(int i=0; i <3*width; i++)
    {
        upTmp[i] = data[i];
    }
    int i=0; // licznik szerokości tablicy upTmp
    for(int j=3*width; j< width*height*3; j++)
    {
        aktual = dataj = data[j];
        dataj -= upTmp[i];
        if(dataj < 0)
            dataj += 256; // jeśli wartości są mniejsze od 0 to dodajemy 256

        upTmp[i] = aktual;
        i++;
        if(i == 3*width) // jeśli przejdzie całą linię to licznik jest zerowany
            i = 0;

    }
}

// pierwszy wiersz oraz pierwszy element drugiego wiersza są pomijane
void paeth_filter(unsigned char *data, int width, int height)
{
    int w; // predyktor, w = tab[1][0] + tab[0][1] - tab[0][0]
    int p; // wartość minimalna z tab[1][0], [0][1], tab[0][0]
    int prev, up, diag; // element poprzedni, powyżej i powyżej nad poprzednim
    for(int j=3*width+1; j< width*height*3; j++)
    {
        prev = data[j-1];
        up = data[j- 3*width];
        diag = data[j- 3*width-1];
        w = prev + up - diag +256;
        if(w > 255)
            w = w % 256;

        prev -= w +256;
        if(prev > 255)
            prev = prev % 256;

        up -= w +256;
        if(up > 255)
            up = up % 256;

        diag -= w +256;
        if(diag > 255)
            diag = diag % 256;

        //wyznaczenie elementu minimalnego
        if(prev <= up)
            p = prev;
        else
            p = up;
        if(diag <= p)
            p = diag;

        // nowa wartość koloru
        data[j] -= p;

    }
}

void averaging_filter(unsigned char *data, int width, int height) // filtr uśredniający, nowa wartość koloru to suma koloru przed i ponad aktualnym podzielona przez 2
{
    int prev, up;// element poprzedni i powyżej
    for(int j=3*width+1; j< width*height*3; j++)
    {
        prev = data[j-1];
        up = data[j- 3*width];
        data[j] = (prev+up)/2 + 256;
        if(data[j] > 255)
            data[j] = data[j] % 256;
    }
}
}

