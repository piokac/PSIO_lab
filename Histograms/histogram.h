#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <iostream>
#include <map>
#include <vector>
class Histogram
{
    int bin_size_;
    std::map<int, int> bins_;

    int value2bin(double value) const;
    double bin2value(double bin) const;
    using BinsVector = std::vector<std::pair<double, int>>;

public:
    Histogram(int bin_size = 1, const std::vector<double> &data = std::vector<double>());
    void emplace(double v);
    void emplace(const std::vector<double> &data);

    void clear();
    bool from_csv(const std::string &filename, char delim = ',', int column_idx = 4);
    std::pair<double, int> max() const;
    std::pair<double, double> range() const;
    std::vector<double> unique_bins() const;
    BinsVector unique_items() const;

    Histogram &operator<<(double v);
    int operator[](double v) const; //zwraca częstość dla binu w indeksie
    operator BinsVector();

    friend std::istream &operator>>(std::istream &str, Histogram &hist);
    friend std::ostream &operator<<(std::ostream &str, const Histogram &hist);
};

#endif // HISTOGRAM_H
