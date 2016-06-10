#include "sllist.h"
#include "mainwindow.h"
#include <QGraphicsScene>
#include <QPropertyAnimation>

SLList::SLList()
{
    this->pHead = NULL;
}

SLList::~SLList()
{

}

void SLList::InitColor()
{
    chosenNode = NULL;
    Node *cur = this->pHead;
    while (cur)
    {
        cur->setColor(1); // default cyan
        cur=cur->pNext;
    }
}

void SLList::Save(QString path)
{
    //open
    QFile mFile(path);
    if (!mFile.open(QIODevice::WriteOnly))
    {
        exit(1);
    }
    QTextStream writer(&mFile);

    //write
    if (this->pHead)
    {
        Node *cur = this->pHead;
        while (cur)
        {
            writer << cur->data;
            if (cur->pNext)
            {
                writer << " ";
            }
            cur = cur->pNext;
        }
    }
    mFile.flush();
    //close
    mFile.close();
}

void SLList::Open(QString path)
{
    //open
    QFile mFile(path);
    if (!mFile.open(QIODevice::ReadOnly))
    {
        exit(1);
    }
    QTextStream reader(&mFile);
    //read
    int x;
    while (!reader.atEnd())
    {
        reader >> x;
        Node *node = new Node(x);
        pMain->getScene()->addItem(node);
        this->Append(node);
    }
    mFile.flush();
    //close
    mFile.close();
}

void SLList::RemoveAll()
{
    Node *cur = this->pHead;
    while (this->pHead)
    {
        this->pHead = this->pHead->pNext;
        delete cur;
        cur = this->pHead;
    }
}

void SLList::InsertHead(Node *node)
{
    int t=1;
    for(Node *i=this->pHead; i !=NULL; i = i->pNext){
        i->gotoxy(t);
        t++;
    }
    node->gotoxy(0);
    if (!this->pHead)
    {
        this->pHead = node;
    }
    else
    {
        Node *cur = this->pHead;
        this->pHead = node;
        this->pHead->pNext = cur;
    }
    node->update();
}

void SLList::Append(Node *node)
{
    int t=0;
    if (!this->pHead)
    {
        this->pHead = node;
    }
    else
    {
        t++;
        Node *cur = this->pHead;
        while (cur->pNext)
        {
            cur = cur->pNext;
            t++;
        }
        cur->pNext = node;
    }
    node->gotoxy(t);
}

void SLList::InsertBeforeANode(Node *node)
{

    int t=0, r=0;
    Node* cur = pHead;
    if (cur == chosenNode)
    {
        this->InsertHead(node);
        r=0;
    }
    else
    {
        r=1;
        Node* cur1 = cur->pNext;
        while (cur1)
        {
            if (cur1 == chosenNode)
            {
                cur->pNext = node;
                node->pNext = cur1;
                break;
            }
            cur = cur->pNext;
            cur1 = cur1->pNext;
            r++;
        }

        t=r;
        Node *node2=node->pNext;
        t++;
        while(node2)
        {
            node2->gotoxy(t);
            t++;
            node2=node2->pNext;
        }
        node->gotoxy(r);
    }
}

Node *curF; //store current node for step by step in Find action
bool SLList::Find(int number)
{
    bool found = false;
    if (once) //in run once mode
    {
        Node *cur = this->pHead;
        while(cur)
        {
            if (cur->data == number)
            {
                found = true;
                cur->setColor(2);
            }
            cur=cur->pNext;
        }
        return found;
    }
    else //in step by step mode
    {
        if (!curF) curF = this->pHead;
        // make some delays
        QEventLoop loop;
        QTimer::singleShot(500, &loop, SLOT(quit()));
        loop.exec();

        curF->setColor(0);

        if (nextS == true) //when user clicks next
        {
            if (curF->data == number)
            {
                found = true;
                curF->setColor(2);
            }
            else curF->setColor(1);
            curF=curF->pNext;
            if(!curF) return found;
            curF->setColor(0);
            nextS == false;
        }

        return found;
    }
}

Node *curT; //store current node for step by step in Traverse action
void SLList::Traverse()
{
    this->InitColor();

    if (once) //in run once mode
    {
        Node *cur = this->pHead;
        while(cur)
        {
            cur->setColor(0);
            //make some delays
            QEventLoop loop;
            QTimer::singleShot(1000, &loop, SLOT(quit()));
            loop.exec();

            cur->setColor(1);

            cur = cur->pNext;
        }
    }
    else //in step by step mode
    {
        if (!curT) curT = this->pHead;
        //make some delays
        QEventLoop loop;
        QTimer::singleShot(500, &loop, SLOT(quit()));
        loop.exec();
        curT->setColor(0);
        if (nextS == true) //when user clicks next
        {
            if (!curT) return;
            curT->setColor(1);
            curT=curT->pNext;
            if(curT==NULL) return;
            curT->setColor(0);
            nextS == false;
        }
    }
}

void SLList::RandomList(int number)
{
    for (int i=0; i<number; i++)
    {
        Node* newNode = new Node(rand()%100); //random value for the node
        pMain->getScene()->addItem(newNode);
        this->Append(newNode);
    }
}

