#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newElement()
{
    if(ui->Tableau->currentRow()>=0)
    {

        ui->Tableau->insertRow(ui->Tableau->currentRow());
    }
    else
    {
        ui->Tableau->insertRow(ui->Tableau->rowCount());
    }

}

void MainWindow::removeElement()
{

    if(ui->Tableau->currentRow()>=0)
    {
        ui->Tableau->removeRow(ui->Tableau->currentRow());
    }

    else
    {
        ui->Tableau->removeRow(ui->Tableau->rowCount());
    }


}

void MainWindow::on_AjouterElement_clicked()
{
    newElement();
}

void MainWindow::on_SupprimerElement_clicked()
{
    removeElement();
}
