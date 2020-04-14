#include "histogram.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>

Histogram::Histogram(const std::vector<int> &data)
{
    for (auto &el : data) {
        bins_[el]++;
    }
}

Histogram Histogram::generate(int min, int max, int count)
{
    Histogram h;
    for (int i = 0; i < count; i++)
        h.emplace(min + rand() % (max - min));
    return h;
}
Histogram Histogram::generate(int count, int (*func_ptr)())
{
    Histogram h;
    for (int i = 0; i < count; i++)
        h.emplace(func_ptr());
    return h;
}

void Histogram::emplace(int v)
{
    bins_[v]++;
}

void Histogram::emplace(const std::vector<int> &data)
{
    for (auto &el : data) {
        bins_[el]++;
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
        return true;

    } else {
        return false;
    }
}

std::pair<int, int> Histogram::max() const
{
    auto v = std::max_element(bins_.begin(),
                              bins_.end(),
                              [](const std::pair<int, int> &el1, const std::pair<int, int> &el2) {
                                  return el1.second < el2.second;
                              });
    return {v->first, v->second};
}

std::pair<int, int> Histogram::range() const
{
    if (bins_.size() == 0) {
        return {0, 0};
    }
    return {bins_.begin()->first, bins_.rbegin()->first};
}

std::vector<int> Histogram::unique_bins() const
{
    std::vector<int> bins;
    for (auto &el : bins_) {
        bins.emplace_back(el.first);
    }
    return bins;
}

Histogram::BinsVector Histogram::unique_items() const
{
    Histogram::BinsVector vect;
    std::copy(bins_.begin(), bins_.end(), std::back_inserter(vect));
    //    int bin_size = bin_size_;
    //    std::transform(vect.begin(),
    //                   vect.end(),
    //                   vect.begin(),
    //                   [bin_size](const std::pair<double, int> &v) {
    //                       return std::make_pair(v.first * bin_size, v.second);
    //                   });
    return vect;
}

Histogram &Histogram::operator<<(int v)
{
    emplace(v);
    return *this;
}

int Histogram::operator[](int v) const
{
    try {
        return bins_.at(v);
    } catch (std::out_of_range) {
        return 0;
    }
}

std::istream &operator>>(std::istream &str, Histogram &hist)
{
    int v;
    str >> v;
    hist.emplace(v);
    return str;
}

std::ostream &operator<<(std::ostream &str, const Histogram &hist)
{
    for (const auto &[bin, freq] : hist.bins_) {
        str << bin << " - " << freq << std::endl;
    }
    return str;
}

Histogram::operator BinsVector()
{
    return unique_items();
}
