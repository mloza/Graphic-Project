#ifndef DEFILTERS_H_INCLUDED
#define DEFILTERS_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>

namespace defilter {
    bool differential(std::vector<unsigned char> &data, int width, int height);
}

#endif // DEFILTERS_H_INCLUDED
