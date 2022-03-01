#include <iostream>
#include <random>
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

int main() {
    int n = 100;
    int iter_sum = 0;
    int probability_count = 0;
    for (int i = 0; i < 1000; i++) {
        std::vector<double> line = generate_line(-1, 1);
        std::vector<double> weights(3, 0);
        std::vector<std::pair<std::pair<double, double>, int>> training_data = generate_test_points(-1, 1, line, n);
        int iterations = 1;
        weights = {0, 0, 0};
        weights[0] = training_data[0].first.first * training_data[0].second;
        weights[1] = training_data[0].first.second * training_data[0].second;
        weights[2] = 1 * training_data[0].second;
        while (true) {
            bool flag = true;
            for (int j = 0; j < n; j++) {
                int calc_ans;
                if ((weights[0] * training_data[j].first.first) + (weights[1] * training_data[j].first.second) + (weights[2] * 1) > 0) {
                    calc_ans = 1;
                } else {
                    calc_ans = -1;
                }
                if (calc_ans != training_data[j].second) {
                    weights[0] = weights[0] + (training_data[j].first.first * training_data[j].second);
                    weights[1] = weights[1] + (training_data[j].first.second * training_data[j].second);
                    weights[2] = weights[2] + 1 * training_data[j].second;
                    flag = false;
                    break;
                }
            }
            if (flag) {
                break;
            }
            iterations++;
        }
        iter_sum += iterations;
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_real_distribution<double> distr(-1, 1);
        double x = distr(generator), y = distr(generator);
        double ans = ((line[0] * x) + (line[1] * y) + line[2]) > 0 ? 1 : -1;
        double test = ((weights[0] * x) + (weights[1] * y) + weights[2]) > 0 ? 1 : -1;
        if (ans != test) {
            probability_count++;
        }
    }
    std::cout << (iter_sum / 1000) << std::endl;
    std::cout << ((double)probability_count / 1000.0) << std::endl;
    return 0;
}