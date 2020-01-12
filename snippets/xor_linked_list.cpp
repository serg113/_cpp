#include <iostream>
#include <string>

// node.h
class Node
{
public:
    friend class NodeList;
    Node(std::string&& name);
    std::string name_;

private:
    size_t xor_value_;
};

Node::Node(std::string&& name): name_(name), xor_value_(0) {};


// nodelist.h
class NodeList
{
public:
    NodeList();
    NodeList& Create(std::string&& name);
    NodeList& Add(Node* node);
    Node& Get(int index);

private:
    Node* root_;
    Node* count_xor(size_t val, Node* node);
};

//nodelist.cpp
NodeList::NodeList(): root_(nullptr){};

NodeList& NodeList::Create(std::string&& name)
{
    root_ = new Node(std::move(name));
    return *this;
}

NodeList& NodeList::Add(Node* node)
{//if(root_ == nullptr) throw exception;
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
    return *this;
}

Node& NodeList::Get(int index)
{//if(root_ == nullptr) throw exception;
    if(index == 0)
        return *root_;

    Node* it_node = root_;

    for(int i = 1; i <= index; ++i)
    {//if(it_node->xor_ == 0) throw out of range exception;
        it_node = (Node*)(it_node->xor_value_ ^ ((size_t)it_node));
    }
    return *it_node;
}

Node* NodeList::count_xor(size_t val, Node* node)
{
    size_t node_rp = reinterpret_cast<size_t>(node);

    return reinterpret_cast<Node*>((node->xor_value_ ^ node_rp));
}


int main()
{
    NodeList nodes = NodeList().Create("root");

    nodes.Add(new Node("n1"))
                .Add(new Node("n2"))
                    .Add(new Node("n3"));

    std::cout <<"get(0).name_ = " << nodes.Get(0).name_ << std::endl;
    std::cout <<"get(1).name_ = " << nodes.Get(1).name_ << std::endl;
    std::cout <<"get(2).name_ = " << nodes.Get(2).name_ << std::endl;

    return 0;
}



