#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<person.h>
#include<QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainDataBase db("SDMP","QODBC");
    db.conectDataBase("ODAVINH\\SQLEXPRESS");
    //db.addTable("KIEV");
    //db.deleteTable(1);

}
MainWindow::~MainWindow()
{
    delete ui;
}
