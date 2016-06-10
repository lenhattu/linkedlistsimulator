#include "node.h"
#include "sllist.h"
#include "mainwindow.h"
#include <QPropertyAnimation>

Node *chosenNode;

void Node::setInit(Node *node){
    width=50;
    height=50;
    node->setPos(0,0);
    node->pNext=NULL;
    node->color = 1; //set default color as cyan
}

Node::Node()
{
    setInit(this);
}
Node::Node(int x)
{
    setInit(this);
    this->data = x;
}

void Node::gotoxy(int t)
{
    setDone(1);
    QPropertyAnimation *positionAnimation;
    positionAnimation = new QPropertyAnimation(this, "position");
    positionAnimation->setDuration(700);

    QRectF tt = this->boundingRect();
    positionAnimation->setKeyValueAt(0, tt);
    tt.setLeft(t*70);
    tt.setTop(100);
    positionAnimation->setKeyValueAt(1, tt);
    positionAnimation->start();
    this->setPosition(tt);
    QPropertyAnimation *lineAnimation;
    lineAnimation = new QPropertyAnimation(this, "done");
    lineAnimation->setDuration(700);
    lineAnimation->setStartValue(0);
    lineAnimation->setKeyValueAt(1,-1);
    lineAnimation->start();
}

void Node::setDone(int t){
    this->done+=t;
    if (done==0)
    {
        update();
        pMain->resize(pMain->width(), pMain->height()+1);
        pMain->resize(pMain->width(), pMain->height()-1);
        pMain->enableOthers();
    }
}

void Node::setColor(int t)
{
    this->color=t;
    update();
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //make all nodes' color to default (cyan)
    Node *cur = List.pHead;
    while (cur)
    {
        cur->setColor(1);
        cur->update();
        cur=cur->pNext;
    }
    //change the color on click
    this->color = 1 - this->color;
    if (color == 0) //color red means that the node is chosen by user
    {
        chosenNode = this;
    }
    else //not choose
    {
        chosenNode = NULL;
    }
    update();
}

Node::~Node()
{
}

int Node::rdone()
{
    return this->done;
}

QRectF Node::boundingRect() const
{
    return QRectF(this->x(),this->y(), width, height);
}

void Node::setPosition(QRectF &newRect)
{
    //setPos(newRect.topLeft());
    this->setX(newRect.x());
    this->setY(newRect.y());
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QPen pen(Qt::black, 3); //pen for the nodes
    QPen pen2(Qt::black, 2); //pen 2 for the arrows between the nodes
    QBrush brush(Qt::cyan); //brush to color the nodes

    // set up painter and colors
    painter->setPen(pen);
    if (this->color == 1)
    {
        brush.setColor(Qt::cyan);
    }
    else if (this->color == 0)
    {
        brush.setColor(Qt::red);
    }
    else if (this->color == 2)
    {
        brush.setColor(Qt::yellow);
    }
    painter->setBrush(brush);
    //draw the circles (nodes)
    painter->drawEllipse(rect);
    //change type of the data (from int to text)
    char text[100];
    _itoa(this->data,text,10);
    //put the data (after type-changed) to the nodes
    QTextOption textOption(Qt::AlignCenter);
    painter->drawText(rect,text,textOption);
    //draw arrows between the nodes
    if (done==0&&this!=List.pHead) // except the first and the last nodes don't have arrows
    {
        painter->setPen(pen2);
        painter->drawLine(this->x()-90,this->y()+height/2,this->x(),this->y()+height/2);
        painter->drawLine(this->x()-5,this->y()+height/2-5,this->x(),this->y()+height/2);
        painter->drawLine(this->x()-5,this->y()+height/2+5,this->x(),this->y()+height/2);
    }
}




