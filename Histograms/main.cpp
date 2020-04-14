#include "histogram.h"
#include <iostream>
#include <vector>
using namespace std;
float sum(float a, float b)
{
    return a + b;
}

float mul(float a, float b)
{
    return a * b;
}

int main()
{
    float (*operacja)(float a, float b);
    operacja = sum;              //przypisuje funkcję sum
    std::cout << operacja(3, 3); //wyswietli 6 - dodawanie

    operacja = mul;              //przypisuje funkcję mul
    std::cout << operacja(3, 3); //wyswietli 9 - mnożenie

    operacja = [](float a, float b) { return a - b; }; // przypisuje wyrażenie lambda
    std::cout << operacja(3, 3); //wyswietli 0 - odejmowanie za pomocą wyrażenia lambda
    //Konstruktory
    Histogram hist; // wywołuje konstruktor domyślny
    Histogram hist_3 = Histogram::generate(100, []() { return 0 + rand() % 10; });
    Histogram hist_2(std::vector<int>(
        {10,
         15,
         6,
         9,
         10,
         12})); // tworzy konstruktor określający szerokość przedziału i inicjuje go listą wyników w punktach

    //Dodawanie elementów
    hist.emplace(20); //dodaje ocenę 20pkt

    hist.emplace(std::vector<int>({10, 15, 6, 9, 10, 12}));

    hist << 10 << 12.5 << 20 << 21; // kolejne elementy zawierają punktację poszczególnych studentów

    cin >> hist; // pobiera dane od użytkownika (pobierając najpierw liczbę wyników, które chce wprowadzić)

    if (!hist.from_csv(R"(../wyniki.csv)", ',', 4))
        std::cout << "ERROR: file was not found";

    hist_2.clear(); //usuwa wszystkie dane z histogramu // jeśli dane nie zostaną usunięte kolejne wywołania operatora zapisu do strumienia lub

    //Wyświetlanie i gettery
    std::cout << hist; //zapis histogramu do strumienia tekstowego

    int freq = hist[10]; //zwraca częstość dla przedziału do którego należy wartość 10.5

    std::pair<int, int> max = hist.max(); //zwraca najczęściej występujący przedział oraz częstość

    std::vector<int> bins
        = hist.unique_bins(); //zwraca listę unikalnych, niepustych przedziałów (gdzie dla przedziału o szerokości 5 wartość elementu 0 jest przedziałem [0-5), 5 -> [5,10) itp]

    std::vector<std::pair<int, int>> items
        = hist.unique_items(); //zwraca listę niepustych przedziałów oraz częstość wystąpień

    //konwersja na inne typy
    using BinsVector = std::vector<std::pair<int, int>>;
    BinsVector items_c = static_cast<BinsVector>(hist); //zobacz hist.unique_items

    return 0;
}
