#include <iostream>
#include <utility>

class Node
{
public:
    int data;
    Node* left;
    Node* right; 

    Node(int d)
    {
        this->data = d;
        this->left = nullptr;
        this->right = nullptr;
    }
};

static int maxCompleteSubtreeDepth = INT_MIN;
std::pair<Node*, int> result(nullptr, 0);

int completeDepth(Node* node)
{
    if(node == nullptr) return -1;
    else
    {
        int leftDepth = completeDepth(node->left);
        int rightDepth = completeDepth(node->right);

        int answer = std::min(leftDepth, rightDepth) + 1;

        if(answer > maxCompleteSubtreeDepth)
        {
            maxCompleteSubtreeDepth = answer;
            result.first = node;
            result.second = answer;
        }

        return answer;
    }
    
}

std::pair<Node*, int> LargestCompleteSubtree(Node* root)
{   
    completeDepth(root);
    return result;
}

int main()
{
    Node* root = new Node(0);
    root->left = new Node(1);
    root->right = new Node(2);

    root->left->left = new Node(3);
    root->left->right = new Node(4);

    root->right->left = new Node(5);
    root->right->left->left = new Node(6);
    root->right->left->right = new Node(7);

    std::pair<Node*, int> ans = LargestCompleteSubtree(root);

    std::cout << ans.second;
    return 0;
}

