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

    void lzw(std::list<uint2x12_t>* dataIn)
    {
        cout << "Dekoduje \n";
        for(int i=0; i< 256; i++)
        {
            dictionary[i] = i; // wypełnianie słownika alfabetem
            nWords++;
        }

        list<uint2x12_t>::iterator it;

        unsigned int act;
        string pc = "";
        unsigned int pk = dataIn->begin()->v1;

        cout << (int)dictionary[pk][0] << " ";

        for(it=dataIn->begin(); it != dataIn->end(); ++it)
        {
            act = it->v1;
            for(int i = 0; i<2; i++)
            {
                //jeśli jest w słowniku
                if(act < nWords)
                {
                    // zapisz do słownika poprzedni i pierwszy symbol aktualnego
                    dictionary[nWords] = pc + dictionary[act][0];
                    nWords++;
                    // na wyjście wypisz cały aktualny
                    for(int j = 0; j<dictionary[act].length(); j++)
                    {
                        cout << (int)dictionary[act][j] << " ";
                    }
                } else {
                    //inaczej dodaj do słownika pc + pierwszy symbol pc;
                    dictionary[nWords] = pc + pc[0];
                    for(int j = 0; j<dictionary[nWords].length(); j++)
                    {
                        cout << (int)dictionary[nWords][j] << " ";
                    }
                    nWords++;
                }
                pk = act;
                act = it->v2;
            }
            pk = act;
        }

        cout << "\nSlownik: \n";
        for(int i=0; i<nWords; i++)
        {
            cout << i << ":" << dictionary[i].length() << ":";
            for(int j=0; j<dictionary[i].length(); j++)
            {
                cout << (int)dictionary[nWords][j] << " ";
            }
            cout << endl;
        }

        cout << "\n Koniec dekodowania \n";
    }
}
