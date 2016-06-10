#ifndef NODE_H
#define NODE_H
#include <QPainter>
#include <QGraphicsItem>
#include <fstream>
#include <QString>
#include <QFile>
#include <QGraphicsSceneMouseEvent>

using namespace std;


class Node : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF position READ boundingRect WRITE setPosition)
    Q_PROPERTY(int done READ rdone WRITE setDone)
    Q_PROPERTY(int color MEMBER color WRITE setColor)

public:
    int color; //color of the node
    int pos, done=0; //position, done property
    qreal width, height; //size of the node
    int data; //data in a node
    Node *pNext;

    Node();
    Node(int x);
    ~Node();
    int rdone();
    QRectF boundingRect() const; // bounding rect to paint a node
    void setPosition(QRectF &newRect);
    void paint(QPainter * painter,
                   const QStyleOptionGraphicsItem * option,
                   QWidget * widget); //paint function
    void setInit(Node *node); //init values
    void gotoxy(int t); //animations
    void setDone(int t);
    void setColor(int t); //RED = 0, CYAN = 1, YELLOW = 2
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //do something on mouse click
};

extern Node *chosenNode;
extern bool once, nextS;
extern int numberF;

#endif // NODE_H
