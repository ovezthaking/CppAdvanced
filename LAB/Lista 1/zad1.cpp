#include <iostream>

template <typename T, typename C>
T my_max(T a, T b, C comp){
    return comp(a,b) ? b : a;
}

int main(){
    auto comp = [](auto a, auto b){
        return a < b;
    };
    
    std::cout << "Większy element dla 8 i 90: " << my_max(8, 90, comp) << std::endl;
    std::cout << "Większy element dla 6.25 i 9.1: " << my_max(9.1, 6.25, comp) << std::endl;
    std::cout << "Większy element dla a i z: " << my_max('a', 'z', comp) << std::endl;
    
}
