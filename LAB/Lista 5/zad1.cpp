
#include <iostream>
#include <memory>

template <typename T>
class BST
{
    struct Node
    {
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node* parent;
        T key;

        Node(T k, Node* p = nullptr) : key(k), parent(p) {}
    };

    std::unique_ptr<Node> root;

    void print_in_order(const Node* node) const
    {
        if (node == nullptr)
            return;
        print_in_order(node->left.get());
        std::cout << node->key << " ";
        print_in_order(node->right.get());
    }

public:
    void insert(T key)
    {
        if (!root)
        {
            root = std::make_unique<Node>(key);
            return;
        }

        Node* current = root.get();
        while (true)
        {
            if (key < current->key)
            {
                if (current->left)
                {
                    current = current->left.get();
                }
                else
                {
                    current->left = std::make_unique<Node>(key, current);
                    break;
                }
            }
            else
            {
                if (current->right)
                {
                    current = current->right.get();
                }
                else
                {
                    current->right = std::make_unique<Node>(key, current);
                    break;
                }
            }
        }
    }

    void print_in_order() const
    {
        print_in_order(root.get());
        std::cout << std::endl;
    }
};

int main()
{
    BST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.print_in_order();
    
    return 0;
}