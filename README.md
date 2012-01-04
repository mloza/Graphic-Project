# Projekt na grafikę

Projekt ma na celu stworzenie własnego formatu graficznego korzystającego z algorytmu kompresji LZW 
##Specyfikacja pliku .???

Plik tego formatu służy do zapisu obrazów. Używa kompresji bezstratnej (algorytm LZW). Składa się z nagłówka, który posiada podstawowe informacje o obrazie oraz z danych obrazu zapisanych w sposób ciągły zaraz za nagłówkiem. Poniżej znajduje się tabela opisująca ten format.
```
ID pola	Offset [bajty]	Rozmiar [bajty]	Nazwa pola	Opis
1	0	2	Typ pliku	Służy do identyfikacji formatu pliku. Pierwszy bit ma wartość 0x3A, drugi 0x29, co odpowiada znakom :) w kodzie ASCII.
2	2	1	Przestrzeń barw	Identyfikuje użytą przestrzeń barw, odpowiednio dla liczb: 0 - RGB, 1 - HSV, 2 - HSL, 3 - YUV
3	3	1	Ilość bitów na piksel	Format obsługuje tylko 24 bitowy opis piksela. Pole służy jako informacja dla odbiorcy.
4	4	4	Szerokość	Szerokość w pixelach, z uwagi na rozmiar pola maksymalna szerokość obrazka to 4294967295 pixeli
5	8	4	Wysokość	Wysokość w pixelach, z uwagi na rozmiar pola maksymalna szerokość obrazka to 4294967295 pixeli

6	12	4*5*3/8 (ten rozmiar powinien być dużo mniejszy po LZW)	DANE OBRAZU	Ciąg bajtów opisujący obraz uzyskany w wyniku kompresji algorytmem LZW.
```



### Komentarze:
* słownik trzymamy w tablicy 4096 elementów (12 bajtów na indeksy).pod poszczególnym indeksem możemy zapisać ciąg znaków o dowolnej długości string słownik[4096]; 
* Elementy przechowują ciągi znaków, które opisują bajty z których składa się słowo np. “255:24:34:5”
* do pliku zapisujemy liczby 12 bitowe