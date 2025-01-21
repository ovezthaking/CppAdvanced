#include <iostream>
#include <vector>
#include <array>
#include <string>


template<typename T>
void print_all(const T& arg) {
    std::cout << arg << " ";
}

template<typename T, std::size_t N>
void print_all(const T (&arr)[N]) {
    std::cout << "[";
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << arr[i];
        if (i < N - 1) std::cout << ", ";
    }
    std::cout << "]" << " ";
}


template<typename T>
void print_all(const std::vector<T>& vec) {
    std::cout << "[";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it;
        if (it + 1 != vec.end()) std::cout << ", ";
    }
    std::cout << "]" << " ";
}


void print_all(const char* str) {
    std::cout << str << " ";
}

template<>
void print_all(const std::string& str) {
    std::cout <<  str  << " ";
}

template<typename T, typename... Args>
void print_all(const T& first, const Args&... rest) {
    print_all(first);  
    print_all(rest...);
    if (sizeof...(rest) == 1){
        std::cout << std::endl;
    }  
}

int main() {
    int arr[] = {1, 2, 3};
    std::vector<double> vec = {1.1, 2.2, 3.3};
    
    print_all(1, 2.0);
    print_all(62, 4.2, arr, vec);
    print_all(1, 1.0, 1.0f, "Hello");
    return 0;
}
