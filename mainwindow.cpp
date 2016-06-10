#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "sllist.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFileDialog>

QGraphicsScene *sceneArr[1000];
int sceneNum=0, sceneCur=0;
bool once = true; //signal to know if we are in run once mode
bool nextS = false; //signal to know if user press next button
int numberF; // store the number input from user
int workcur; // store current action for step by step (with next button)
const int trav = 1;
const int f = 2;

SLList List;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized(); //maximize the window size when running
    scene = new QGraphicsScene(this);
    this->ui->graphicsView->setScene(scene);
    this->on_actionRun_Once_triggered(); //use run once mode as default
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsScene *MainWindow::getScene()
{
    return this->scene;
}

void MainWindow::on_actionSave_triggered()
{
    //get the path from user (browse folders and files)
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), "", "Text File (*.txt)");
    if (path != NULL) //NULL when user click cancel
    {
        List.Save(path);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    //get the path from user (browse folders and files)
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Text File (*.txt)");
    if (path != NULL) //NULL when user click cancel
    {
        disableOthers();
        this->on_actionNew_triggered();
        List.Open(path);
    }
}

void MainWindow::on_actionNew_triggered()
{
    //resize the view to completely clear all stuff on the window
    pMain->ui->graphicsView->resize(pMain->width(),pMain->height()-1);
    pMain->ui->graphicsView->resize(pMain->width(),pMain->height()+1);
    List.RemoveAll();
    this->scene->clear();
}

void MainWindow::on_actionAppend_triggered()
{
    disableOthers();
    //show dialog to ask user for an integer
    bool ok = false;
    int number = QInputDialog::getInt(this, "Insert", "Please enter an integer:", rand(), -2147483647, 2147483647, 1, &ok);
    if (ok)
    {
        node = new Node(number);
        scene->addItem(node);
        List.Append(node);
    }
    else enableOthers();
}

void MainWindow::on_actionInsert_Head_triggered()
{
    disableOthers();
    //show dialog to ask user for an integer
    bool ok = false;
    int number = QInputDialog::getInt(this, "Insert", "Please enter an integer:", rand(), -2147483647, 2147483647, 1, &ok);
    if (ok)
    {
        node = new Node(number);
        scene->addItem(node);
        List.InsertHead(node);
    }
    else enableOthers();

}

void MainWindow::on_actionTraverse_triggered()
{
    workcur = trav;
    disableOthers();
    List.Traverse();
    enableOthers();
}

void MainWindow::on_actionInsert_Before_A_Node_triggered()
{
    disableOthers();
    bool ok = false;
    if(!chosenNode)
    {
        //if user has not choose a node, warn him
        QMessageBox::warning(this, "Insert Error", "You must choose a specific node!");
        enableOthers();
        return;
    }
    // show dialog to ask user for an integer
    int number = QInputDialog::getInt(this, "Insert", "Please enter an integer:", rand(), -2147483647, 2147483647, 1, &ok);
    if (ok)
    {
        node = new Node(number);
        scene->addItem(node);
        List.InsertBeforeANode(node);
    }
    else enableOthers();
}

void MainWindow::on_actionFind_triggered()
{
    List.InitColor(); //set default cyan color
    workcur = f;
    disableOthers();
    // show dialog to ask user for an integer
    bool ok = false;
    int number = QInputDialog::getInt(this, "Find", "Please enter an integer:", 0, -2147483647, 2147483647, 1, &ok);
    if (ok)
    {
        numberF = number;
        if (!List.Find(number) && once)
        {
            // if cannot find any matches
            QMessageBox::warning(this, "Result", "No matches!");
        }
    }
    enableOthers();
}

void MainWindow::on_actionRandom_List_triggered()
{
    disableOthers();
    // show dialog to ask user for an integer
    bool ok = false;
    int number = QInputDialog::getInt(this, "", "Please enter number of nodes:", 1, 1, 2147483647, 1, &ok);
    if (ok)
    {
        this->on_actionNew_triggered();
        List.RandomList(number);
    }
    else enableOthers();
}

void MainWindow::disableOthers()
{
    this->ui->actionFind->setDisabled(true);
    this->ui->actionAppend->setDisabled(true);
    this->ui->actionInsert_Before_A_Node->setDisabled(true);
    this->ui->actionInsert_Head->setDisabled(true);
    this->ui->actionRandom_List->setDisabled(true);
    this->ui->actionTraverse->setDisabled(true);

}

void MainWindow::enableOthers()
{
    this->ui->actionFind->setEnabled(true);
    this->ui->actionAppend->setEnabled(true);
    this->ui->actionInsert_Before_A_Node->setEnabled(true);
    this->ui->actionInsert_Head->setEnabled(true);
    this->ui->actionRandom_List->setEnabled(true);
    this->ui->actionTraverse->setEnabled(true);
}


void MainWindow::on_actionRun_Once_triggered()
{
    once=true;
    this->ui->actionRun_Once->setDisabled(true);
    this->ui->actionRun_Step_By_Step->setEnabled(true);
    this->ui->actionNext->setDisabled(true); //run once does not use next button -> disable
}

void MainWindow::on_actionRun_Step_By_Step_triggered()
{
    once=false;
    this->ui->actionRun_Step_By_Step->setDisabled(true);
    this->ui->actionRun_Once->setEnabled(true);
    this->ui->actionNext->setEnabled(true);
}

void MainWindow::on_actionEdit_A_Node_triggered()
{
    if(!chosenNode)
    {
        //warn that user must choose a node first
        QMessageBox::warning(this, "Insert Error", "You must choose a node!");
        enableOthers();
        return;
    }
    // show dialog to ask user for an integer
    bool ok = false;
    int number = QInputDialog::getInt(this, "Edit", "Please enter an integer:", rand(), -2147483647, 2147483647, 1, &ok);
    if (ok)
    {
        chosenNode->data = number; //edit the data of chosen node with number from user
    }
    else enableOthers();
}

void MainWindow::on_actionNext_triggered()
{
    nextS = true; //set true on click
    if (workcur == trav) // if current action is "Traverse the list"
        List.Traverse();
    else if (workcur == f) // if current action is "Find a node"
        List.Find(numberF);

}
