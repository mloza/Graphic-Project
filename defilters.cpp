#include "defilters.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

namespace defilter {
    bool differential(std::vector<unsigned char> &data, int width, int height)
    {
        int akt;
        ofstream f("out/aft.txt");
        f << (int)data[0] << endl;
        for(int j=1; j<width*height*3; j++)
        {
            akt = data[j] + data[j-1];
            if(akt > 255) akt %= 256;
            data[j] = akt;
            f << (int)data[j] << endl;
        }
        return true;
    }
}
