#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0)); // use current time as seed for random generator
    std::vector<int> vec(1000);

    for (int &num : vec) {
        num = std::rand(); // assign random number to each element
    }

    // Optional: Print the vector to verify
    for (const int &num : vec) {
        std::cout << num << " ";
    }

    return 0;
}