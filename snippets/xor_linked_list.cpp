
#include <iostream>
#include <string>


class Node
{
    size_t xor_ = 0;

public:
    friend class NodeList;

    Node(std::string name)
    {
        name_ = name;
    }
    std::string name_;
};

struct NodeList
{
    Node* root = nullptr;

    NodeList& Create()
    {
        root = new Node("root");
        return *this;
    }

    NodeList& add(Node* node)
    {
        if(root != nullptr)
        {
            Node* fnode = root;

            while(true)
            {
                if(fnode->xor_ != 0)
                {
                    fnode = (Node*)(fnode->xor_^((size_t)fnode));
                }
                else
                {
                    fnode->xor_ = (size_t)fnode^(size_t)node;
                    break;
                }
            }
        }
        return *this;
    }

    Node* get(int index)
    {
        if(root == nullptr) return nullptr;

        if(index == 0) return root;

        Node* fnode = root;

        for(int i = 1; i <= index; ++i)
        {
            if(fnode->xor_ == 0) return nullptr;

            fnode = (Node*)(fnode->xor_^((size_t)fnode));
        }

        return fnode;
    }

};


int main()
{
    NodeList nodes = NodeList().Create();

    nodes.add(new Node("n1"))
                .add(new Node("n2"))
                    .add(new Node("n3"));

    std::cout <<"get(0).name_ = " << nodes.get(0)->name_ << std::endl;
    std::cout <<"get(1).name_ = " << nodes.get(1)->name_ << std::endl;
    std::cout <<"get(2).name_ = " << nodes.get(2)->name_ << std::endl;

    return 0;
}
