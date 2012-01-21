// Filtr różnicowy, nowa wartość koloru to różnica obecnej komórki i poprzedniej ( data[j] = data[j] - data[j-1] )
// Pierwszy bajt jest pomijany
void differential_filter(unsigned char *data, int width, int height)
{
    for(int j=1; j< width*height*3; j++)
    {
        data[j] -= data[j-1]+255;
        if(data[j] > 255)
                data[j] = data[j]%255; // jeśli wartości są większe od 255 to ich nowa wartość jest resztą z dzielenia przez 255
    }
}

// filtr w górę,  nowa wartość koloru to różnica obecnej komórki i komórki powyżej ( data[j] = data[j] - data[j-width])
// pierwszy wiersz jest pomijany
void up_filter(unsigned char *data, int width, int height)
{
    for(int j=3*width; j< width*height*3; j++)
    {
        data[j] = data[j] - data[j-3*width] +255;
        if(data[j] > 255)
            data[j] = data[j]%255; // jeśli wartości są większe od 255 to ich nowa wartość jest resztą z dzielenia przez 255
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
        w = prev + up - diag +255;
        if(w > 255)
            w = w % 255;

        prev -= w +255;
        if(prev > 255)
            prev = prev % 255;

        up -= w +255;
        if(up > 255)
            up = up % 255;

        diag -= w +255;
        if(diag > 255)
            diag = diag % 255;

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
        data[j] = (prev+up)/2 + 255;
        if(data[j] > 255)
            data[j] = data[j] % 255;
    }
}
