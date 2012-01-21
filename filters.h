#ifndef FILTERS_H
#define FILTERS_H

#include <vector>

namespace filters {
    bool differential_filter(unsigned char data*, int width, int height);
    void up_filter(unsigned char data*, int width, int height);
    void averaging_filter(unsigned char data*, int width, int height);
    void paeth_filter(unsigned char data*, int width, int height);
}

#endif
