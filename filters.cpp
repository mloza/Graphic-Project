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
void up_filter(std::vector<unsigned char> &data, int width, int height)
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
        data[j] = dataj;
        upTmp[i] = aktual;
        i++;
        if(i == 3*width) // jeśli przejdzie całą linię to licznik jest zerowany
            i = 0;

    }
}

// pierwszy wiersz oraz pierwszy element drugiego wiersza są pomijane
void paeth_filter(std::vector<unsigned char> &data, int width, int height)
{
    int w; // predyktor, w = tab[1][0] + tab[0][1] - tab[0][0]
    int p; // wartość minimalna z tab[1][0], [0][1], tab[0][0]

    int dataj, prev, aktual, up, diag;
    int diff  = 3*width;
    int upTmp[diff];
    for(int i=0; i<diff; i++)
    {
        upTmp[i] = data[i];
    }

    prev = data[diff];
    diag = data[0];
    ofstream a("out/a.txt");
    for(int j=diff+1; j<width*height*3; j++)
    {
        aktual = dataj = data[j];
        up = upTmp[j%diff];

        w = prev + up - diag;
        p = prev < up? (prev<diag?prev:diag):(up<diag?up:diag);
        p -= w;

        dataj -= p;
        if(dataj<0)
            dataj += 256;

        a << aktual << "\t" << prev << "\t" << up << "\t" << diag << "\t" << dataj << "\t" << w << "\t" << p << endl;
        data[j] = dataj;
        prev = aktual;
        diag = up;
        upTmp[j%diff] = prev = aktual;
    }
}

void averaging_filter(std::vector<unsigned char> &data, int width, int height) // filtr uśredniający, nowa wartość koloru to suma koloru przed i ponad aktualnym podzielona przez 2
{
    int dataj, prev, aktual, up;
    int diff  = 3*width;
    int upTmp[diff];
    for(int i=0; i<diff; i++)
    {
        upTmp[i] = data[i];
    }
    prev = data[diff];
    for(int j=diff+1; j<width*height*3; j++)
    {
        aktual = dataj = data[j];
        up = upTmp[j%diff];
        dataj = aktual - (prev+up)/2;
        if(dataj < 0)
            dataj += 256;
        data[j] = dataj;
        upTmp[j%diff] = prev = aktual;
    }
}
}

