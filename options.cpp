#include "options.h"

COLOR_SPACE getColorSpaceID(std::string name)
{
    if(name == "RGB")
        return RGB;
    else
    if(name == "HSL")
        return HSL;
    else
    if(name == "HSV")
        return HSV;
    else
    if(name == "YUV")
        return YUV;
    else
        return UNDEFINED_COLOR_SPACE;
}


FILTER_TYPE getFilterID(std::string name)
{
    if(name == "NONE")
        return NONE;
    else
    if(name == "DIFFERENTIAL")
        return DIFFERENTIAL;
    else
    if(name == "LINE_DIFFERENCE")
        return LINE_DIFFERENCE;
    else
    if(name == "AVERAGING")
        return AVERAGING;
    else
    if(name == "PAETH")
        return PAETH;
    else
        return UNDEFINED_FILTER;

}
