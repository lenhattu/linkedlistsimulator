#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QInputDialog>
#include "node.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsScene *scene;

    QGraphicsScene *getScene(); //get the graphic scene
    void disableOthers(); //disable other actions when an action is in progress
    void enableOthers(); //enable other actions when an action is done

public slots:
    void on_actionSave_triggered(); //Save File action

    void on_actionOpen_triggered(); //Open File action

    void on_actionNew_triggered(); //Init an empty list

    void on_actionAppend_triggered(); //Insert to end of list

    void on_actionInsert_Head_triggered(); //Insert to head of list

    void on_actionTraverse_triggered(); //Traverse the list

    void on_actionInsert_Before_A_Node_triggered(); //Insert before a specific node

    void on_actionFind_triggered(); //Find a node in the list

    void on_actionRandom_List_triggered(); //Random a list (with n elements)

    void on_actionRun_Once_triggered(); //Toggle to run once mode

    void on_actionRun_Step_By_Step_triggered(); //Toggle to run step by step mode

    void on_actionEdit_A_Node_triggered(); //Edit data of a node

    void on_actionNext_triggered(); //Next button to do step by step

private:
    Ui::MainWindow *ui; //control mainwindow.ui
    Node *node;

};

extern MainWindow *pMain;

#endif // MAINWINDOW_H
