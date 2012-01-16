#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

/**
 *  @brief Stałe przestrzeni barw
 */
enum COLOR_SPACE
{
    UNDEFINED_COLOR_SPACE = 666,
    RGB = 0,
    HSV,
    HSL,
    YUV
};

COLOR_SPACE getColorSpaceID(std::string name);

/**
 *  @brief Stałe określające typ filtru
 */
enum FILTER_TYPE
{
    UNDEFINED_FILTER = 666,
    NONE = 0
};

FILTER_TYPE getFilterID(std::string name);


#endif
