#ifndef SLLIST_H
#define SLLIST_H
#include "node.h"
#include <QPropertyAnimation>
class SLList
{
public:
    Node *pHead; //head
    SLList();
    ~SLList();
    void InitColor(); //init the color to CYAN (default = 1)
    void Save(QString path); //Save txt file
    void Open(QString path); //Open txt file
    void RemoveAll(); //Remove all nodes
    void InsertHead(Node* node); //insert to head of list
    void Append(Node* node); //insert to end of list
    void InsertBeforeANode(Node* node); //insert before a node
    bool Find(int number); //find a node
    void Traverse(); //traverse the list
    void RandomList(int number); //make a random-value list
};
extern SLList List;
#endif // SLLIST_H
