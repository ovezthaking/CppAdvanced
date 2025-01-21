#include <iostream>
#include <stdexcept>
#include <utility> // std::move

namespace cpplab {

    template <typename T>
    class vector {
    public:
        // Typy
        using value_type = T;

        // Konstruktor domyślny
        vector() : size_(0), capacity_(0), data_(nullptr) {}

        // Konstruktor kopiujący (l-value)
        vector(const vector& other)
            : size_(other.size_), capacity_(other.capacity_), data_(nullptr) {
            if (capacity_ > 0) {
                data_ = new T[capacity_];
                for (std::size_t i = 0; i < size_; ++i) {
                    data_[i] = other.data_[i]; // Kopiowanie elementów
                }
            }
        }

        // Konstruktor przenoszący (r-value)
        vector(vector&& other) noexcept
            : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr; // Przenoszenie własności
        }

        // Operator przypisania kopiujący (l-value)
        vector& operator=(const vector& other) {
            if (this == &other) return *this; // Ochrona przed samokopiowaniem

            // Czyszczenie aktualnych zasobów
            delete[] data_;

            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = nullptr;
            if (capacity_ > 0) {
                data_ = new T[capacity_];
                for (std::size_t i = 0; i < size_; ++i) {
                    data_[i] = other.data_[i];
                }
            }
            return *this;
        }

        // Operator przypisania przenoszący (r-value)
        vector& operator=(vector&& other) noexcept {
            if (this == &other) return *this; // Ochrona przed samoprzeniesieniem

            // Czyszczenie aktualnych zasobów
            delete[] data_;

            // Przenoszenie zasobów
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = other.data_;

            // Czyszczenie przeniesionego obiektu
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;

            return *this;
        }

        // Destruktor
        ~vector() {
            delete[] data_;
        }

        // Dodawanie elementu
        void push_back(const T& value) {
            if (size_ == capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            data_[size_++] = value;
        }

        // Rozmiar wektora
        std::size_t size() const { return size_; }

        // Rezerwacja pamięci
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

        // Dostęp do elementów
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

    private:
        std::size_t size_;
        std::size_t capacity_;
        T* data_;
    };

} // namespace cpplab

int main() {
    using cpplab::vector;

    // Test konstrukcji domyślnej
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    std::cout << "v1: ";
    for (std::size_t i = 0; i < v1.size(); ++i) {
        std::cout << v1[i] << " ";
    }
    std::cout << "\n";

    // Test konstrukcji kopiującej
    vector<int> v2 = v1;
    std::cout << "v2 (kopiowane z v1): ";
    for (std::size_t i = 0; i < v2.size(); ++i) {
        std::cout << v2[i] << " ";
    }
    std::cout << "\n";

    // Test konstrukcji przenoszącej
    vector<int> v3 = std::move(v1);
    std::cout << "v3 (przeniesione z v1): ";
    for (std::size_t i = 0; i < v3.size(); ++i) {
        std::cout << v3[i] << " ";
    }
    std::cout << "\n";

    // Test operatora przypisania kopiującego
    vector<int> v4;
    v4 = v2;
    std::cout << "v4 (kopiowane z v2): ";
    for (std::size_t i = 0; i < v4.size(); ++i) {
        std::cout << v4[i] << " ";
    }
    std::cout << "\n";

    // Test operatora przypisania przenoszącego
    vector<int> v5;
    v5 = std::move(v3);
    std::cout << "v5 (przeniesione z v3): ";
    for (std::size_t i = 0; i < v5.size(); ++i) {
        std::cout << v5[i] << " ";
    }
    std::cout << "\n";

    for (std::size_t i = 0; i < v3.size(); ++i) {
        std::cout << v3[i] << " ";
    }
    std::cout << "\n";
    return 0;
}


/*Dlaczego nie używamy mempcy? memcpy działa na surowych bajtach. 
Jeśli T ma złożony destruktor lub konstruktor kopiujący, 
memcpy nie zadba o poprawną semantykę tych operacji, 
co może prowadzić do wycieków pamięci lub błędów w zarządzaniu zasobami.*/