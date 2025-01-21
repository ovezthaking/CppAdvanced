#include <iostream>
#include <stdexcept>
#include <utility> // std::move, std::forward
#include <new>     // placement new

namespace cpplab {

    template <typename T>
    class vector {
    public:
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
        /*
        // Destruktor
        ~vector() {
            delete[] data_;
        }
        */

        // Metoda emplace_back
        template <typename... Args>
        void emplace_back(Args&&... args) {
            if (size_ == capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            new (data_ + size_) T(std::forward<Args>(args)...);
            ++size_;
        }

        // Dodawanie elementu
        void push_back(const T& value) {
            if (size_ == capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            new (data_ + size_) T(value);
            ++size_;
        }

        // Rozmiar wektora
        std::size_t size() const { return size_; }

        // Rezerwacja pamięci
        void reserve(std::size_t new_capacity) {
            if (new_capacity > capacity_) {
                T* new_data = reinterpret_cast<T*>(new std::byte[new_capacity * sizeof(T)]);
                for (std::size_t i = 0; i < size_; ++i) {
                    new (new_data + i) T(std::move(data_[i]));
                    data_[i].~T();
                }
                delete[] reinterpret_cast<std::byte*>(data_);
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

        // Destruktor
        ~vector() {
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i].~T();
            }
            delete[] reinterpret_cast<std::byte*>(data_);
        }

    private:
        std::size_t size_;
        std::size_t capacity_;
        T* data_;
    };

} // namespace cpplab

template <typename T, typename U>
concept Possible = std::is_arithmetic_v<T> && std::is_arithmetic_v<U> &&
    requires(T a, U b) {
        //{ a * b } -> std::convertible_to<T>; //linijka ta miała sprawdzać czy wynik mnozenia 
        //typu T i typu U jest konwertowalny na T
        { a.size() } -> std::convertible_to<std::size_t>;
        { a[0] };
};




template <typename Vector1, typename Vector2>
auto operator*(const Vector1& vec1, const Vector2& vec2) {
    assert(vec1.size() == vec2.size());

    decltype(vec1[0] * vec2[0]) result = 0;

    for (std::size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }

    return result;
}

// Klasa pixel
class pixel {
public:
    int r, g, b;

    pixel(int red, int green, int blue)
        : r(red), g(green), b(blue) {}

    friend std::ostream& operator<<(std::ostream& os, const pixel& p) {
        return os << "(" << p.r << ", " << p.g << ", " << p.b << ")";
    }
};

// Testy
int main() {
    using cpplab::vector;

    vector<pixel> pixels;

    // Dodawanie elementów za pomocą emplace_back
    pixels.emplace_back(3, 4, 6);   
    pixels.emplace_back(0, 255, 0);   
    pixels.emplace_back(0, 0, 255);  

    std::cout << "Pixels:\n";
    for (std::size_t i = 0; i < pixels.size(); ++i) {
        std::cout << pixels[i] << "\n";
    }

    return 0;
}
