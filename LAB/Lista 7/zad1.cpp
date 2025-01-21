#include<iostream>
#include<vector>
#include<thread>
#include<future>
#include <numeric>

void dot(std::vector<double> vec1, std::vector<double> vec2, std::promise<double> result){
    if(vec1.empty() || vec2.empty()){
        result.set_exception(std::make_exception_ptr(std::invalid_argument("Wektory nie mogą byc puste!!!")));
        return;
    }
    if(vec1.size() != vec2.size()){
        result.set_exception(std::make_exception_ptr(std::invalid_argument("Wektory muszą mieć takie same rozmiary!!!")));
        return;
    }

    result.set_value(std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0.0));
}


int main(){
    std::vector<double> vec1(10, 1.32);
    std::vector<double> vec2(10, 2.0);

    std::vector<std::thread> threads;
    std::vector<std::future<double>> futures;

    for(int i = 0; i < 10; i++){
        std::promise<double> result;
        futures.push_back(result.get_future());
        threads.emplace_back(dot, std::ref(vec1), std::ref(vec2), std::move(result));
    }

    for(auto &thread : threads){
        thread.join();
    }

    double total_sum = 0.0;
    for(auto &future : futures){
        try{
            total_sum += future.get();
        }catch(const std::exception &e){
            std::cerr << "Wykryto wyjątek: " << e.what() << std::endl;
        }
    }

    std::cout << "Suma iloczynów skalarnych: " << total_sum << std::endl;
}