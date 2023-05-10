#include "stats.h"
#include <cmath>
using namespace std;

double compute_mean(const std::vector<int> &v) {
    double sum = 0;
    for (auto &n: v)
        sum += n;
    return sum/v.size();
}

double compute_stddev(const std::vector<int> &v) {
    double sum_squares = 0;
    double mean = compute_mean(v);
    double len = v.size();
    for (auto n: v) {
        double diff = n-mean;
        sum_squares += diff * diff;
    }
    return sqrt(sum_squares/len);
}

Stats::Stats(string name, const vector<int> & chain_lengths) {
    name = name;
    mean = compute_mean(chain_lengths);
    stddev = compute_stddev(chain_lengths);
}
