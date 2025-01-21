#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>


template <typename T>
std::vector<int> generate_vector(T v){
    std::srand(std::time(0));
    for(int i = 0; i< 1000; i++){
        v.push_back(rand());
    }
    std::cout << "Randomly generated vector: ";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n\n";
    return v;
}
/*
template <typename T>
void sort_vector(T &v){
    std::sort(v.begin(), v.end());

    std::cout << "std::sort single thread: ";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n\n";
}
*/
template <typename T>
void sort_vector_multi(T &v){
    std::thread t1([&v]() {
        std::sort(v.begin(), v.begin() + v.size()/2);
    });

    std::thread t2([&v](){
        std::sort(v.begin() + v.size()/2, v.end());
    });

    t1.join();
    t2.join();

    std::inplace_merge(v.begin(), v.begin() + v.size()/2, v.end());


    std::cout << "std::sort multi thread: ";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n\n";   
}


int main(){

    std::vector<int> v;
    std::vector<int> v2;
    v = generate_vector(v);
    v2 = v;

    //\sort_vector(v);

    sort_vector_multi(v2);

    return 0;
}

/*
Wektor sortowany przez 2 wątki jest posortowany w dwóch częściach, a następnie łączony w jedną posortowaną całość.
Jest więc to równoważne z posortowaniem całego wektora przez pojedynczy wątek, co oznacza posortowanie go w całości.
*/