#include <iostream>
#include <vector>

template <typename T>
void insertion_sort(std::vector<T>& w){
    for (auto i = 1; i < w.size(); i++){
        T key = w[i];
        while(i > 0 && w[i-1] > key){
            w[i] = w[i-1];
            i--;
        }
        w[i] = key;
    }   
}

int main(){
    std::vector<int> wek = {5, 2, 9, 1, 5, 6};

    std::cout << "Przed sortowaniem: ";
    for (int v : wek) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    
    insertion_sort(wek);

    std::cout << "Po sortowaniu: ";
    for (int v : wek) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*
złożoność: 
najgorszy przypadek - O(n^2) - gdy dane są posortowane odwrotnie, to wszystkie elementy muszą zostać 
przesunięte ; 
najlepszy przypadek - O(n) - gdy dane są posortowane rosnąco, to nie trzeba przesuwać żadnego elementu;
Przypadek występujący średnio najczęściej - O(n^2) - najczęsciej wiele danych nie jest posortowane i wtedy
trzeba przesuwać elementy;
*/

/*
PYTANIE: Czy wykorzystując sortowanie z porównaniami można uzyskać lepszą średnią złożoność niż n^2?

Tak, można uzyskać średnią złożoność O(nlogn) wykorzystując np. sortowanie kubełkowe.


*/