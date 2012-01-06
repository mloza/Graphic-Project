#ifndef CODER_H_INCLUDED
#define CODER_H_INCLUDED

#include <string>

using namespace std;

namespace coder {
    /**
    *  Funkcja uruchamiająca koder.
    */
    void run();

    void lzw(char* dataIn, unsigned long int dataSize);

    unsigned const int DICTIONARY_MAX_SIZE = 4096;
    extern string dictionary[DICTIONARY_MAX_SIZE];
    extern unsigned int nWords;                          // ilość słów w słowniku
}

#endif // CODER_H_INCLUDED
