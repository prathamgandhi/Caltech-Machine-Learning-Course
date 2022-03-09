#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<double> generate_line(int from, int to) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(from, to);

    double a1 = distr(generator), b1 = distr(generator), a2 = distr(generator), b2 = distr(generator);
    std::vector<double> line(3);
    line[0] = (b1 - b2);
    line[1] = (a2 - a1);
    line[2] = ((a1 * b2) - (b1 * a2));
    return line;
}

std::vector<std::pair<std::pair<double, double>, int>> generate_test_points(int from, int to, const std::vector<double>& line, int n) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(from, to);
    std::vector<std::pair<std::pair<double, double>, int>> training_data(n);
    for (int i = 0; i < n; i++) {
        double x = distr(generator);
        double y = distr(generator);
        training_data[i].first = std::make_pair(x, y);
        if ((x * line[0]) + (y * line[1]) + (line[2]) > 0) {
            training_data[i].second = 1;
        } else {
            training_data[i].second = -1;
        }
    }
    return training_data;
}

using namespace boost::numeric;
int main() {
    ublas::matrix<double> m(3, 3);
    for (int i = 0; i < m.size1(); i++) {
        for (int j = 0; j < m.size2(); j++) {
            m(i, j) = i + j;
        }
    }
    m.std::cout << m << std::ehdl;
    return 0;
}
