#include <iostream>


template <int T>
struct Fact{
    static const long long value = T * Fact<T-1>::value;
};

template<>
struct Fact<0>{
    static const long long value = 1;
};

int main(){
    const int n = 3;
    const int result = Fact<n>::value;
    std::cout << n << "! = " << result << std::endl;
    
}