#include <iostream>
#include <string>
#include <memory>

struct Node
{
    Node(std::string&& name);
    std::string name_;
    size_t xor_value_;
};

Node::Node(std::string&& name): name_(std::move(name)), xor_value_(0) {};


class NodeList;

using ListPtr = std::shared_ptr<NodeList>;

class NodeList: public std::enable_shared_from_this<NodeList>
{
public:
    NodeList();
    ListPtr Create(std::string&& name);
    ListPtr Add(Node* node);
    Node* Get(int index);

private:
    Node* root_;
};


NodeList::NodeList(): root_(nullptr){};

ListPtr NodeList::Create(std::string&& name)
{
    root_ = new Node(std::move(name));
    return shared_from_this();
}

ListPtr NodeList::Add(Node* node)
{
    Node* it_node = root_;
    while(true)
    {
        if(it_node->xor_value_ != 0)
        {
            it_node = (Node*)(it_node->xor_value_ ^ ((size_t)it_node));
        }
        else
        {
            it_node->xor_value_ = (size_t)it_node ^ (size_t)node;
            break;
        }
    }
    return shared_from_this();
}

Node* NodeList::Get(int index)
{
    if(index == 0)
        return root_;

    Node* it_node = root_;

    for(int i = 1; i <= index; ++i)
    {//if(it_node->xor_ == 0) throw out of range exception;
        it_node = (Node*)(it_node->xor_value_ ^ ((size_t)it_node));
    }
    return it_node;
}

Node* count_xor(size_t val, Node* node)
{
    size_t node_rp = reinterpret_cast<size_t>(node);

    return reinterpret_cast<Node*>((node->xor_value_ ^ node_rp));
}


int main()
{
    auto nodes = std::make_shared<NodeList>();

    nodes->Create("root")
            ->Add(new Node("n1"))
                ->Add(new Node("n2"))
                    ->Add(new Node("n3"));

    std::cout <<"get(0).name_ = " << nodes->Get(0)->name_ << std::endl;
    std::cout <<"get(1).name_ = " << nodes->Get(1)->name_ << std::endl;
    std::cout <<"get(2).name_ = " << nodes->Get(2)->name_ << std::endl;

    return 0;
}



