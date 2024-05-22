#include <iostream>
using namespace std;


class Graph;

class Node
{
    int val = 0;    
    int degree = 0;
    Node *Inc = NULL;
    Node *Next = NULL;
    friend class Graph;

public:
    Node(int value) {val = value;};
    void setValue(int value) {val = value;};
    int getValue() {return val;};
    int getDegree() {return degree;};
    void printIncNodes();
};


void Node::printIncNodes()
{
    Node *next = Next;
    for (int i = 0; i<degree; i++) {cout << next->getValue(); next = next->Next;};
}


class Graph
{   
    Node *root = new Node(0);
public:
    Graph(Node *first);
    int is_Inc(Node *node1, Node *node2);
    Node *addNode(Node *root, Node *newN);
    void delNode(Node *root);
    void addEdge(Node *node1, Node *node2);
    void delEdge(Node *node1, Node *node2);
    // Node *depthSearch, widthSearch
};

Graph::Graph(Node *first)
{
    root = first;
};

int Graph::is_Inc(Node *node1, Node *node2)
{
    int result = 0;
    Node *check = node1->Inc;
    for (int i=0; i<node1->degree; i++)
    {
        if (check == node2){result = 1;};
        check = check->Next;
    }
    return result;
}

void Graph::addEdge(Node* node1, Node* node2)
{
    node2->degree++;
    node1->degree++;
    Node *next = node1;
    for (int i=0; i<node1->degree; i++)
    {
        next = next->Next;
    };
    next->Next = node2;
    next = node2;
    for (int i=0; i<node2->degree; i++)
    {
        next = next->Next;
    };
    next->Next = node1;
    return;
};


void Graph::delEdge(Node *node1, Node *node2)
{
    if (Graph::is_Inc(node1, node2))
    {
        // удаляем связность 1->2
        Node *next = node1->Inc;
        if (next == node2) {root->Inc = node2->Next;}
        else{
            while (next->Next != node2)
            {
                next = next->Next;
            }
            next->Next = next->Next->Next;
        }

        // удаляем связность 2->1
        next = node2;
        if (next == node1) {root->Inc = node1->Next;}
        else{
            while (next->Next != node1)
            {
                next = next->Next;
            }
            next->Next = next->Next->Next;
        }
    }
};

Node *Graph::addNode(Node *node, Node *newN)
{
    Node *last = node->Inc;
    if (last != NULL)
    {
        for (int i=1; i<node->degree; i++)
        {
            last = last->Next;
        };
        last->Next = newN;
    }
    else {node->Inc = newN;}
    node->degree++;
    newN->Inc = node;
    newN->degree = 1;
    return newN;
}

void Graph::delNode(Node *root) 
{
    Node *next = root->Inc;
    for (int i=1; i<root->degree; i++)
    {
        delEdge(root, next);
        next = next -> Next;
    }
};
