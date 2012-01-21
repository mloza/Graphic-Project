#include "defilters.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

namespace defilter {
    bool differential(std::vector<unsigned char> &data, int width, int height)
    {
        int akt;
        for(int j=1; j<width*height*3; j++)
        {
            akt = data[j] + data[j-1];
            if(akt > 255) akt %= 256;
            data[j] = akt;
        }
        return true;
    }

    bool line_differential(std::vector<unsigned char> &data, int width, int height)
    {
        int akt;
        int diff = width*3;
        for(int j=diff; j<width*height*3; j++)
        {
            akt = data[j] + data[j-diff];
            if(akt > 255) akt %= 256;
            data[j] = akt;
        }
        return true;
    }

    bool average(std::vector<unsigned char> &data, int width, int height)
    {
        int akt;
        int diff = width*3;
        for(int j=diff+1; j<width*height*3; j++)
        {
            akt = data[j] + (data[j-1] + data[j-diff])/2;
            if(akt > 255) akt %= 256;
            data[j] = akt;
        }
        return true;
    }

    bool paeth(std::vector<unsigned char> &data, int width, int height)
    {
        int akt, p, w;
        int diff = width*3;
        ofstream a("out/a-d.txt");
        for(int j=diff+1; j<width*height*3; j++)
        {
            w = data[j-1] + data[j-diff] - data[j-diff-1];
            p = data[j-1]<data[j-diff]?(data[j-1]<data[j-diff-1]?data[j-1]:data[j-diff-1]):(data[j-diff]<data[j-diff-1]?data[j-diff]:data[j-diff-1]);
            p-=w;

            akt = data[j] + p;
            if(akt > 255) akt %= 256;
            if(akt < 0) akt += 256;
            a << akt << "\t" << (int)data[j] << "\t" << (int)data[j-1] << "\t" << (int)data[j-diff] << "\t" << (int)data[j-diff-1] << "\t" << (int)w << "\t" << (int)p << endl;
            data[j] = akt;
        }
        return true;
    }
}
