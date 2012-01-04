#ifndef UINT2x12_T_H
#define UINT2x12_T_H

#pragma pack(push, 1)

/**
 *  @author Paweł Góralik
 *
 *  @brief Struktura do przechowywania dwóch słów kodowych LZW (12 bitowe indeksy słownika).
 *
 *  Przechowywane są dwie wartości 12-bitowe, ponieważ w sumie zajmują równe 3 bajty, dzięki czemu
 *  strukturę można zapisać do pliku przy użyciu strumieni C++, które zapisują sekwencje bajtów.
 */
struct uint2x12_t
{
    unsigned int v1 :12;    /**< Pierwsze słowo kodowe */
    unsigned int v2 :12;    /**< Drugie słowo kodowe */
};

#pragma pack(pop)

#endif // UINT2x12_T_H
