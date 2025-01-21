#include <iostream>
#include <vector>
#include <cassert>

namespace cpplab {

    template <typename T>
    class vector {
    public:
        using value_type = T;

        // Konstruktor 
        vector() : size_(0), capacity_(0), data_(nullptr) {}

        // Destruktor
        ~vector() {
            delete[] data_;
        }

        //Usuwanie elementów
        void erase(std::size_t index) {
            if (index >= size_) {
                throw std::out_of_range("Wektor nie posiada takiego elementu");
            }
            for (std::size_t i = index; i < size_ - 1; ++i) {
                data_[i] = data_[i + 1];  
            }
            --size_;  
        }

        //Rozmiar wektora
        std::size_t size() const {
            return size_;
        }
        std::size_t capacity() const {
            return capacity_;
        }

        //Dodawanie elementów
        void push_back(const T& value) {
            if (size_ == capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2); 
            }
            data_[size_++] = value;
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

        //Zmiana rozmiaru
        void resize(std::size_t new_size, const T& default_value = T()) {
        if (new_size > capacity_) {
            reserve(new_size * 2);  
        }

        for (std::size_t i = size_; i < new_size; ++i) {
            data_[i] = default_value;
        }

        size_ = new_size;
    }

        //Operator [] do dostępu do elementów
        T& operator[](std::size_t index) {
            if (index >= size_) {
                throw std::out_of_range("Wektor nie posiada takiego elementu");
            }
            return data_[index];
        }

        const T& operator[](std::size_t index) const {
            if (index >= size_) {
                throw std::out_of_range("Wektor nie posiada takiego elementu");
            }
            return data_[index];
        }
        /*
        //Iloczyn skalarny z innym wektorem cpplab::vector
        template <typename U>
        T dot(const vector<U>& other) const {
            if (size_ != other.size()) {
                throw std::invalid_argument("Wektory muszą mieć taki sam rozmiar");
            }
            T result = T();
            for (std::size_t i = 0; i < size_; ++i) {
                result += data_[i] * other[i];
            }
            return result;
        }

        //Iloczyn skalarny z std::vector
        template <typename U>
        T dot(const std::vector<U>& other) const {
            if (size_ != other.size()) {
                throw std::invalid_argument("Wektory muszą mieć taki sam rozmiar");
            }
            T result = T();
            for (std::size_t i = 0; i < size_; ++i) {
                result += data_[i] * other[i];
            }
            return result;
        }
    */
    private:
        std::size_t size_;
        std::size_t capacity_;
        T* data_;
    };
    /*
    // Globalny operator mnożenia dla cpplab::vector i std::vector
    template <typename T, typename U>
    auto operator*(const vector<T>& v1, const std::vector<U>& v2) -> decltype(v1.dot(v2)) {
        return v1.dot(v2);
    }

    template <typename T, typename U>
    auto operator*(const std::vector<T>& v1, const vector<U>& v2) -> decltype(v2.dot(v1)) {
        return v2.dot(v1);
    }
    */
}

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
    cpplab::vector<int> vec1;
    
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(7);

     std::cout << "Wektor po dodaniu elementów: ";
    for (std::size_t i = 0; i < vec1.size(); ++i) {
        std::cout << vec1[i] << " "; 
    }
    std::cout << std::endl;
    
    std::cout << "Rozmiar wektora: " << vec1.size() << std::endl;  
    



    std::vector<int> vec2 = {4, 8, 6, 9};

    
    std::cout << "Iloczyn skalarny vec1 i vec2: " << (vec1 * vec2 ) << std::endl;


    
    //std::cout << "Iloczyn skalarny vec1 i vec2: " << dot_product(vec1, vec2) << std::endl; 
     
    vec1[0] = 100;
    std::cout << "Po modyfikacji, element 0: " << vec1[0] << std::endl;

    
    vec1.erase(3);

    std::cout << "Elementy po erase: ";
    for (std::size_t i = 0; i < vec1.size(); ++i) {
        std::cout << vec1[i] << " ";  
    }
    std::cout << std::endl;

    vec1.resize(10);
    std::cout << "Po resize: " << vec1.size() << std::endl; 


    cpplab::vector<std::string> vec3;
    vec3.push_back("Hello");
    vec3.push_back("World");
    
    std::vector<std::string> vec4 = {"Test", "String"};
    
    
    
    std::cout << "Iloczyn skalarny vec3 i vec4: " << (vec3 * vec4) << std::endl;
    return 0;
}

