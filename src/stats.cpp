#include "stats.h"
#include <cmath>
#include <vector>
#include <numeric>
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
    chain_lengths = chain_lengths;
    min = *min_element(chain_lengths.begin(), chain_lengths.end());
    max = *max_element(chain_lengths.begin(), chain_lengths.end());
    for (int i=0; i<chain_lengths.size(); i++) {
        entries += chain_lengths[i];
    }
    chains = chain_lengths.size();
    load_factor = double(entries)/chains;
    mean = compute_mean(chain_lengths);
    stddev = compute_stddev(chain_lengths);
}
