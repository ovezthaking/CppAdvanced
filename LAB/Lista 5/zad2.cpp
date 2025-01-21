#include <iostream>
#include <stdexcept>
#include <iostream>

namespace cpplab {

template <typename T>
class unique_ptr {
private:
    T* ptr;

public:
    // Konstruktor
    explicit unique_ptr(T* p = nullptr) : ptr(p) {}

    // Destruktor
    ~unique_ptr() {
        delete ptr;
    }

    // Konstruktor przenoszący
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Operator przenoszący
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Usunięcie konstruktora kopiującego i operatora przypisania
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // Operator dereferencji
    T& operator*() const {
        return *ptr;
    }

    // Operator dostępu do składowych
    T* operator->() const {
        return ptr;
    }

    // Wskaźnik do przechowywanego obiektu
    T* get() const {
        return ptr;
    }

    // Zwolnienie obiektu z zarządzania
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // Resetowanie wskaźnika
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

} 

template<typename T>
class non0_ptr {
public:
    explicit non0_ptr(T* ptr) : ptr_(ptr) {
        if (ptr == nullptr) {
            throw std::invalid_argument("Pointer cannot be nullptr");
        }
    }

    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    T* get() const {
        return ptr_;
    }

private:
    T* ptr_;
};




//Problem non0ptr można rozwiązać za pomocą konceptów, a na dole przykład:

/*
#include <iostream>
#include <concepts>

template <typename T>
concept NonNullPointer = requires(T ptr) {
    { ptr != nullptr } -> std::convertible_to<bool>;
};

template <NonNullPointer T>
class non0_ptr {
public:
    explicit non0_ptr(T ptr) : ptr_(ptr) {
        if (ptr_ == nullptr) {
            throw std::invalid_argument("Pointer cannot be nullptr");
        }
    }

    T get() const {
        return ptr_;
    }

private:
    T ptr_;
};

int main() {
    int x = 42;
    non0_ptr<int*> p(&x);
    std::cout << *p.get() << std::endl;

    // Odkomentowanie poniższej lini sprawdzi, że pointer nie może być nullptr
    // non0_ptr<int*> p_null(nullptr);

    return 0;
}
*/

int main() {
    cpplab::unique_ptr<int> p1(new int(5));
    std::cout << *p1 << std::endl;

    cpplab::unique_ptr<int> p2 = std::move(p1);
    std::cout << *p2 << std::endl;

    p2.reset(new int(10));
    std::cout << *p2 << std::endl;

    int* rawPtr = p2.release();
    std::cout << *rawPtr << std::endl;
    delete rawPtr;

    int x = 42;
    non0_ptr<int> p(&x);
    std::cout << *p << std::endl;

    // Odkomentowanie poniższej lini sprawdzi, że pointer nie może być nullptr
     non0_ptr<int> p_null(nullptr);

    std::cout << "test" << std::endl;

    return 0;
}