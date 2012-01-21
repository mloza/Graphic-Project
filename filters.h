#ifndef FILTERS_H
#define FILTERS_H

#include <vector>

namespace filters {
    bool differential_filter(std::vector<unsigned char> &data, int width, int height);
    void up_filter(std::vector<unsigned char> &data, int width, int height);
}

#endif
