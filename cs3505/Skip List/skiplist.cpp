#include <iostream>
#include <vector>

class node
{
public:
    int data;
    
    std::vector<node*> next;

    node(int, int);
};

node::node(int data, int level) : next(level, NULL)
{
    this->data = data;

    std::cout << "A node is constructed. Data: " << data << ", Level: " << level << "\n";
}

class skiplist
{
    int max_level;

    int level;

    node* head;

public:
    skiplist(int);
    int randomLevel();
    void insertElement();
    void displayList();
};

skiplist::skiplist(int maxlvl)
{
    this->max_level = maxlvl;
    this->level = 0;
    head = new node(-1, max_level);
}