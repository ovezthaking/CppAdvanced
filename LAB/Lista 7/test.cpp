#include <iostream>
#include <vector>
#include <typeinfo>
#include <new>

namespace cpplab {
    template <typename T>
    class allocator {
    public:
        using value_type = T;

        T* allocate(std::size_t n) {
            if (n == 0) return nullptr;
            T* ptr = static_cast<T*>(::operator new(n * sizeof(T)));
            for (std::size_t i = 0; i < n; ++i) {
                new (ptr + i) T();
            }
            return ptr;
        }

        void deallocate(T* p, std::size_t n) {
            if (p == nullptr) return;
            for (std::size_t i = 0; i < n; ++i) {
                p[i].~T();
            }
            ::operator delete(p);
        }
    };
}

int main() {
    cpplab::allocator<int> alloc;
    std::cout << typeid(cpplab::allocator<int>::value_type).name() << std::endl;

    cpplab::allocator<int>::value_type *p_test = alloc.allocate(1);
    std::cout << *p_test << std::endl;
    *p_test = 3;
    std::cout << *p_test << std::endl;
    alloc.deallocate(p_test, 1);

    std::vector<int, cpplab::allocator<int>> v;
    v.push_back(13);
    v.push_back(23);

    std::cout << *(v.end() - 1) << std::endl;

    return 0;
}