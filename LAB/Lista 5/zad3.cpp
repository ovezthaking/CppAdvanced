#include <iostream>
#include <vector>
#include <algorithm>



// Funkcja zwracająca maksymalną wartość skarbów, które można zabrać
int maximum(int W, const std::vector<int>& weights, const std::vector<int>& values, int N) {
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[N][W];
}

int main() {
    int N, W;
    std::cout << "Wprowadź liczbę skarbów (N): ";
    std::cin >> N;
    std::cout << "Wprowadź maksymalną wagę skarbu (W): ";
    std::cin >> W;

    std::vector<int> weights(N), values(N);
    std::cout << "Wprowadź wagi skarbów: ";
    for (int i = 0; i < N; ++i) {
        std::cout << i + 1 << ": ";
        std::cin >> weights[i];
    }

    std::cout << "Wprowadź wartości skarbów: ";
    for (int i = 0; i < N; ++i) {
        std::cout << i + 1 << ": " ;
        std::cin >> values[i];
    }

    int max_value = maximum(W, weights, values, N);
    std::cout << "Maksymalna wartość skarbów, które można zabrać to: " << max_value << std::endl;

    return 0;
}