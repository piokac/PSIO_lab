#include "histogram.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    //Konstruktory
    Histogram hist(5); // tworzy konstruktor określający szerokość przedziału
    Histogram hist_2(
        5,
        std::vector<double>(
            {10,
             15,
             6,
             9,
             10,
             12.5})); // tworzy konstruktor określający szerokość przedziału i inicjuje go listą wyników w punktach

    //Dodawanie elementów
    hist.emplace(20); //dodaje ocenę 20pkt

    hist.emplace(std::vector<double>({10, 15, 6, 9, 10, 12.5}));

    hist << 10 << 12.5 << 20 << 21; // kolejne elementy zawierają punktację poszczególnych studentów

    cin >> hist; // pobiera dane od użytkownika (pobierając najpierw liczbę wyników, które chce wprowadzić)

    hist.from_csv(R"(../wyniki.csv)", ',', 4);

    hist_2.clear(); //usuwa wszystkie dane z histogramu // jeśli dane nie zostaną usunięte kolejne wywołania operatora zapisu do strumienia lub

    //Wyświetlanie i gettery
    std::cout << hist; //zapis histogramu do strumienia tekstowego

    int freq = hist[10.5]; //zwraca częstość dla przedziału do którego należy wartość 10.5

    std::pair<double, double> range = hist.range(); //zwraca początkowy i końcowy przedział.

    std::pair<double, int> max = hist.max(); //zwraca najczęściej występujący przedział oraz częstość

    std::vector<double> bins
        = hist.unique_bins(); //zwraca listę unikalnych, niepustych przedziałów (gdzie dla przedziału o szerokości 5 wartość elementu 0 jest przedziałem [0-5), 5 -> [5,10) itp]

    std::vector<std::pair<double, int>> items
        = hist.unique_items(); //zwraca listę niepustych przedziałów oraz częstość wystąpień

    //konwersja na inne typy
    using BinsVector = std::vector<std::pair<double, int>>;
    BinsVector items_c = static_cast<BinsVector>(hist); //zobacz hist.unique_items

    return 0;
}
