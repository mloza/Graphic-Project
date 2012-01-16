// Filtr różnicowy, nowa wartość koloru to różnica obecnej komórki i poprzedniej ( data[j] = data[j] - data[j-1] )
// Pierwszy bajt jest pomijany
void differential_filter(unsigned char *data, int width, int height)
{
        for(int j=1; j< width*height*3; j++)
            data[j] -= data[j-1];

}

// filtr w górę,  nowa wartość koloru to różnica obecnej komórki i komórki powyżej ( data[j] = data[j] - data[j-width])
void up_filter(unsigned char *data, int width, int height)
{
    for(int j=3*width; j< width*height*3; j++)
    {
                data[j] = data[j] - data[j-3*width];
    }
}
