#include <iostream>
#include "decoder.h"

using namespace std;

namespace decoder {
    unsigned const int DICTIONARY_MAX_SIZE = 4096;      /** < maksymalna ilość słów w słowniku */
    string dictionary[DICTIONARY_MAX_SIZE];             /** < słownik przechowujący słowa zapisane w ciągu bajtów (string) */
    unsigned int nWords;                                /** < ilość słów w słowniku */

    void run()
    {
        cout << "DECODER";
    }

    bool in_dict(string word)
    {
        for(int i =0; i<nWords; i++)
        {
            if(disctionary[i] == word) return true;
        }

        return false;
    }

    void lzw(std::list<uint2x12_t>* dataIn, unsigned long int dataSize)
    {
        string word = "";

        for(int i=0; i< 256; i++)
        {
            dictionary[i] = i; // wypełnianie słownika alfabetem
            nWords++;
        }

        list<uint2x12_t>::iterator it;
        for( it=wynik->begin() ; it != wynik->end(); it++ )
        {
            cout << " " << it->v1;
            cout << " " << it->v2;
        }



    }
}
