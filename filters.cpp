#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
namespace filters
{
// Filtr różnicowy, nowa wartość koloru to różnica obecnej komórki i poprzedniej ( data[j] = data[j] - data[j-1] )
// Pierwszy bajt jest pomijany
bool differential_filter(unsigned char *data, int width, int height)
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
    int diff=3*width;
    int upTmp[diff]; // tablica elementów linię ponad aktualnymi
    for(int i=0; i <3*width; i++)
    {
        upTmp[i] = data[i];
    }
    int i=0; // licznik szerokości tablicy upTmp
    for(int j=diff; j< width*height*3; j++)
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
// filtr Paeth'a, najpierw obliczamy predyktor w, odejmujemy od każdego z 3 kolorów otaczających predyktor,
// wybieramy z nich minimum (p) , nowa wartość koloru to różnica koloru aktualnego i p
// pierwszy wiersz oraz pierwszy element drugiego wiersza są pomijane
void paeth_filter(unsigned char *data, int width, int height)
{
    int w; // predyktor, w = t[1][0] + t[0][1] - t[0][0]
    int p; // wartość minimalna z t[1][0], t[0][1], t[0][0]

    int dataj, aktual, prev, up, diag; // element aktualny, tmp aktualnego, poprzedni, powyżej i nad poprzednim
    int diff  = 3*width;
    int upTmp[diff]; // tablica elementów linię ponad aktualnymi
    for(int i=0; i<diff; i++)
    {
        upTmp[i] = data[i];
    }

    prev = data[diff];
    diag = data[0];
    upTmp[0] = data[diff];
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

        data[j] = dataj;
        prev = aktual;
        diag = up;
        upTmp[j%diff] = prev = aktual;
    }
}

// filtr uśredniający, nowa wartość koloru to suma koloru przed i ponad aktualnym podzielona przez 2
void averaging_filter(unsigned char *data, int width, int height)
{
    int dataj, prev, aktual, up;
    int diff  = 3*width;
    int upTmp[diff]; // tablica elementów linię ponad aktualnymi
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

