#include <iostream>
#include <vector>
#include <bits/stdc++.h>

template <typename T>
void insertion_sort(std::vector<T>& w) {
    for (auto i = 1; i < w.size(); i++) {
        T key = w[i];
        i = i - 1;
        while (i >= 0 && w[i] > key) {
            w[i + 1] = w[i];
            i--;
        }
        w[i + 1] = key;
    }
}


bool compare(const std::string& a, const std::string& b) {
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (std::isdigit(a[i]) && std::isdigit(b[j])) {
            size_t i_start = i, j_start = j;
            while (i < a.size() && std::isdigit(a[i])) i++;
            while (j < b.size() && std::isdigit(b[j])) j++;
            int num_a = std::stoi(a.substr(i_start, i - i_start));
            int num_b = std::stoi(b.substr(j_start, j - j_start));
            if (num_a != num_b) return num_a < num_b;
        } else {
            if (a[i] != b[j]) return a[i] < b[j];
            i++;
            j++;
        }
    }
    return a.size() < b.size();
}

template<>
void insertion_sort(std::vector<std::string>& w) {
    for (auto i = 1; i < w.size(); i++) {
        std::string key = w[i];
        int j = i - 1;
        while (j >= 0 && compare(key, w[j])) {
            w[j + 1] = w[j];
            j--;
        }
        w[j + 1] = key;
    }
}


int main() {
    std::vector<std::string> wek = {"plik10", "plik2", "plik1", "plik20", "plik11"};

    
    std::cout << "Przed sortowaniem: ";
    for (const auto& v : wek) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    insertion_sort(wek);

    std::cout << "Po sortowaniu insertion_sort: ";
    for (const auto& v : wek) {
        std::cout << v << " ";
    }
    std::cout << std::endl;


    wek = {"plik10", "plik2", "plik1", "plik20", "plik11"};
    std::sort(wek.begin(), wek.end());

    std::cout << "Po sortowaniu std::sort:   ";
    for (auto v : wek)
        std::cout << v << " ";
    return 0;
}
