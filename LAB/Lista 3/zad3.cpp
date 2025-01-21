#include <iostream>
#include <memory>

//ForwardList
template <typename T>
class ForwardList {
private:
    
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        Node(T value) : data(value), next(nullptr) {}
    };
    
    std::unique_ptr<Node> head;  

public:
    // Konstruktor
    ForwardList() : head(nullptr) {}
    
    
    void push_front(T value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head);
        head = std::move(newNode);
    }
    
    
    void display() const {
        Node* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }

    
    void reverse() {
        std::unique_ptr<Node> prev = nullptr;
        while (head) {
            std::unique_ptr<Node> nextNode = std::move(head->next);
            head->next = std::move(prev);
            prev = std::move(head);
            head = std::move(nextNode);
        }
        head = std::move(prev);
    }
};

int main() {
    
    ForwardList<std::string> list;
    list.push_front("zupa");
    list.push_front("kura");
    list.push_front("jajo");
    list.push_front("arbuz");
    list.push_front("babilon");

    std::cout << "Oryginalna lista: ";
    list.display();

    
    list.reverse();
    std::cout << "Odwrócona lista: ";
    list.display();

    return 0;
}
