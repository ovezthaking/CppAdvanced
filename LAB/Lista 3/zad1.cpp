#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <cassert>

namespace cpplab {
    template <typename T>
    class vector {
    public:
        using value_type = T;

        // Konstruktor
        vector() : size_(0), capacity_(0), data_(nullptr) {}

        // Destruktor
        ~vector() { delete[] data_; }

        void push_back(const T& value) {
            if (size_ == capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            data_[size_++] = value;
        }

        std::size_t size() const { return size_; }

        T& operator[](std::size_t index) {
            if (index >= size_) {
                throw std::out_of_range("Index out of range");
            }
            return data_[index];
        }

        const T& operator[](std::size_t index) const {
            if (index >= size_) {
                throw std::out_of_range("Index out of range");
            }
            return data_[index];
        }

        void reserve(std::size_t new_capacity) {
            if (new_capacity > capacity_) {
                T* new_data = new T[new_capacity];
                for (std::size_t i = 0; i < size_; ++i) {
                    new_data[i] = data_[i];
                }
                delete[] data_;
                data_ = new_data;
                capacity_ = new_capacity;
            }
        }

    private:
        std::size_t size_;
        std::size_t capacity_;
        T* data_;
    };
}


template <typename T, typename U>
concept Possible = std::is_arithmetic_v<T> && std::is_arithmetic_v<U> &&
    requires(T a, U b) {
        { a * b } -> std::convertible_to<T>;
        { a.size() } -> std::convertible_to<std::size_t>;
        { a[0] };
};

//jest liczbą, ma rozmiar, ma operator[]


template <typename Vector1, typename Vector2>
auto operator*(const Vector1& vec1, const Vector2& vec2) {
    assert(vec1.size() == vec2.size());  

    decltype(vec1[0] * vec2[0]) result = 0; 

    for (std::size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }

    return result;
}

int main() {
// Test z int
    cpplab::vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    std::vector<int> vec2 = {4, 5, 6};

    std::cout << "Iloczyn skalarny vec1 i vec2 (int): " << (vec1 * vec2) << std::endl;

    // Test z double
    cpplab::vector<double> vec3;
    vec3.push_back(1.12);
    vec3.push_back(2.24);
    vec3.push_back(3.31);

    std::vector<double> vec4 = {4.44, 5.54, 6.67};

    std::cout << "Iloczyn skalarny vec3 i vec4 (double): " << (vec3 * vec4) << std::endl;


    // Test z float
    cpplab::vector<float> vecx;
    vecx.push_back(1.1);
    vecx.push_back(2.2);
    vecx.push_back(3.3);

    std::vector<float> vecy = {4.4, 5.5, 6.6};

    std::cout << "Iloczyn skalarny vecx i vecy (float): " << (vecx * vecy) << std::endl;


    // Test z std::string – kompilacja powinna się nie udać
    cpplab::vector<std::string> vec5;
    vec5.push_back("Hello");
    vec5.push_back("World");

    std::vector<std::string> vec6 = {"Test", "String"};

    //std::cout << "Iloczyn skalarny vec5 i vec6 (std::string): " << (vec5 * vec6) << std::endl;

    // Test z std::vector<int> – kompilacja powinna się nie udać
    cpplab::vector<std::vector<int>> vec7;
    vec7.push_back({1, 2, 3});
    vec7.push_back({4, 5, 6});

    std::vector<std::vector<int>> vec8 = {{7, 8, 9}, {10, 11, 12}};

    //std::cout << "Iloczyn skalarny vec7 i vec8 (std::vector<int>): " << (vec7 * vec8) << std::endl;
  
    return 0;
}
