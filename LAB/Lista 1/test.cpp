#include <iostream>
#include <vector>
#include <array>

// Funkcja bazowa dla pojedynczego argumentu
template<typename T>
void print_all(const T& arg) {
    std::cout << arg << " ";
}

// Specjalizacja dla tablicy
template<typename T, std::size_t N>
void print_all(const T (&arr)[N]) {
    std::cout << "[";
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << arr[i];
        if (i < N - 1) std::cout << ", ";
    }
    std::cout << "]" << " ";
}

// Specjalizacja dla wektorów lub innych kontenerów z metodami begin() i end()
template<typename T>
void print_all(const std::vector<T>& vec) {
    std::cout << "[";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it;
        if (it + 1 != vec.end()) std::cout << ", ";
    }
    std::cout << "]" << " ";
}

// Funkcja rekurencyjna dla wielu argumentów
template<typename T, typename... Args>
void print_all(const T& first, const Args&... rest) {
    print_all(first);  // Wypisz pierwszy argument
    print_all(rest...);  // Rekurencyjne wywołanie z resztą argumentów
}

int main() {
    int arr[] = {1, 2, 3};
    std::vector<double> vec = {1.1, 2.2, 3.3};

    print_all(1, 1.0, arr, vec, "Hello");
    return 0;
}
