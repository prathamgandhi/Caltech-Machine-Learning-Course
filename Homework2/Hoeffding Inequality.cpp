#include <iostream>
#include <random>
#include <vector>

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
std::uniform_int_distribution<int> flipper(0, 1);

class Coin {
    int head_count = 0;

   public:
    void flip() {
        int toss = flipper(generator);
        head_count += toss == 1 ? 1 : 0;
    }
    int get_head_count() {
        return head_count;
    }
};

int main() {
    srand(time(0));
    double v1_sum = 0, vrand_sum = 0, vmin_sum = 0;
    for (int iter = 0; iter < 100000; iter++) {
        std::vector<Coin> coinList(1000);
        int coin_with_min_frequency = 0;
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 10; j++) {
                coinList[i].flip();
            }
            if (coinList[i].get_head_count() < coinList[coin_with_min_frequency].get_head_count()) {
                coin_with_min_frequency = i;
            }
        }
        std::uniform_int_distribution<int> coin_picker(0, 1000);
        Coin c1 = coinList[0];
        Coin crand = coinList[coin_picker(generator)];
        Coin cmin = coinList[coin_with_min_frequency];
        double v1 = c1.get_head_count() / (double)10;
        double vrand = crand.get_head_count() / (double)10;
        double vmin = cmin.get_head_count() / (double)10;
        v1_sum += v1;
        vrand_sum += vrand;
        vmin_sum += vmin;
    }
    double v1_avg = (v1_sum) / 100000;
    double vrand_avg = (vrand_sum) / 100000;
    double vmin_avg = (vmin_sum) / 100000;
    std::cout << "v1_avg : " << v1_avg << std::endl;
    std::cout << "vrand_avg : " << vrand_avg << std::endl;
    std::cout << "vmin_avg : " << vmin_avg << std::endl;
    return 0;
}

/*
    The mean calculated for vmin comes out to be around 0.037, so it should be option (b). Learnt that use of C++11 random library is slower than regular rand and srand methods 🤔

    We know that out sample error has to be close to in sample error as per Hoeffding's inequality. v1_avg and vrand_avg closely follow the out sample probability as they both come out to be close to 0.5.
    However the coin cmin, does not follow the out sample probability as closely.
*/