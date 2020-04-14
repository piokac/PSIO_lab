#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <iostream>
#include <map>
#include <vector>
class Histogram
{
    std::map<int, int> bins_;

    using BinsVector = std::vector<std::pair<int, int>>;

public:
    Histogram(const std::vector<int> &data = std::vector<int>());
    static Histogram generate(int min, int max, int counter);
    static Histogram generate(int count, int (*func_ptr)());
    void emplace(int v);
    void emplace(const std::vector<int> &data);

    void clear();
    bool from_csv(const std::string &filename, char delim = ',', int column_idx = 4);
    std::pair<int, int> max() const;
    std::pair<int, int> range() const;
    std::vector<int> unique_bins() const;
    BinsVector unique_items() const;

    Histogram &operator<<(int v);
    int operator[](int v) const; //zwraca częstość dla binu w indeksie
    operator BinsVector();

    friend std::istream &operator>>(std::istream &str, Histogram &hist);
    friend std::ostream &operator<<(std::ostream &str, const Histogram &hist);
};

#endif // HISTOGRAM_H
