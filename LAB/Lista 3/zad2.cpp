#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

template <typename T>
void as_sorted_view(const std::vector<T>& vec) {
    
    std::vector<T> sorted = vec;
    std::sort(sorted.begin(), sorted.end());
    std::cout << "posortowany wektor: "<< std::endl;
    for (const auto& elem : sorted) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void show_vector(const std::vector<int>& vec) {
    std::cout << "wektor: " << std::endl;
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {5, 2, 8, 1, 3};
    
    
    auto startTime = std::chrono::high_resolution_clock::now();

    //std::thread t1(as_sorted_view<int>, vec);
    
    as_sorted_view(vec);
    
    //std::thread t2(show_vector, vec);
    
    show_vector(vec);


    //t1.join();
    
    //t2.join();

    auto StopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(StopTime - startTime);

    std::cout << "Czas wykonania: " << duration.count()/1000000.0 << "s" << std::endl;

    return 0;
}