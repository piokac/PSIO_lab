#include "histogram.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>

int Histogram::value2bin(double value) const
{
    return static_cast<int>(value / bin_size_);
}

double Histogram::bin2value(double bin) const
{
    return static_cast<double>(bin * bin_size_);
}

Histogram::Histogram(int bin_size, const std::vector<double> &data) : bin_size_(bin_size)
{
    for (auto &el : data) {
        bins_[value2bin(el)]++;
    }
}

void Histogram::emplace(double v)
{
    bins_[value2bin(v)]++;
}

void Histogram::emplace(const std::vector<double> &data)
{
    for (auto &el : data) {
        bins_[value2bin(el)]++;
    }
}

void Histogram::clear()
{
    bins_.clear();
}

bool Histogram::from_csv(const std::string &filename, char delim, int column_idx)
{
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        getline(file, line); //header
        while (getline(file, line)) {
            std::stringstream str(line);
            std::string el;
            for (int i = 0; getline(str, el, delim); i++) {
                if (i == column_idx) {
                    try {
                        emplace(stoi(el));
                    } catch (std::invalid_argument) {
                        std::cout << "Invalid value found in column " << column_idx << std::endl;
                    }
                }
            }
        }

    } else {
        return false;
    }
}

std::pair<double, int> Histogram::max() const
{
    auto v = std::max_element(bins_.begin(),
                              bins_.end(),
                              [](const std::pair<int, int> &el1, const std::pair<int, int> &el2) {
                                  return el1.second < el2.second;
                              });
    return {bin2value(v->first), v->second};
}

std::pair<double, double> Histogram::range() const
{
    if (bins_.size() == 0) {
        return {0, 0};
    }
    return {bin2value(bins_.begin()->first), bin2value(bins_.rbegin()->first)};
}

std::vector<double> Histogram::unique_bins() const
{
    std::vector<double> bins;
    for (auto &el : bins_) {
        bins.emplace_back(bin2value(el.first));
    }
    return bins;
}

Histogram::BinsVector Histogram::unique_items() const
{
    Histogram::BinsVector vect;
    std::copy(bins_.begin(), bins_.end(), std::back_inserter(vect));
    int bin_size = bin_size_;
    std::transform(vect.begin(),
                   vect.end(),
                   vect.begin(),
                   [bin_size](const std::pair<double, int> &v) {
                       return std::make_pair(v.first * bin_size, v.second);
                   });
    return vect;
}

Histogram &Histogram::operator<<(double v)
{
    emplace(v);
    return *this;
}

int Histogram::operator[](double v) const
{
    try {
        return bins_.at(value2bin(v));
    } catch (std::out_of_range) {
        return 0;
    }
}

std::istream &operator>>(std::istream &str, Histogram &hist)
{
    double v;
    str >> v;
    hist.emplace(v);
    return str;
}

std::ostream &operator<<(std::ostream &str, const Histogram &hist)
{
    for (const auto &[bin, freq] : hist.bins_) {
        str << hist.bin2value(bin) << " - " << freq << std::endl;
    }
    return str;
}

Histogram::operator BinsVector()
{
    return unique_items();
}
