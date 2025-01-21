#include <stdexcept>
#include <iostream>

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


int main() {
    int x = 42;
    non0_ptr<int> p(&x);
    std::cout << *p << std::endl;

    // Odkomentowanie poniższej lini sprawdzi, że pointer nie może być nullptr
     non0_ptr<int> p_null(nullptr);

    return 0;
}


