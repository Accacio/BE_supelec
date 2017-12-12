#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_handler= new Handler(fileName);
    setWindowTitle(fileName+" - "+program_name);
    savedatleastonce=false;



    //delete



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
        ui->Tableau->setCurrentCell(ui->Tableau->rowCount()-1,0);
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

void MainWindow::on_Tableau_pressed(const QModelIndex &index)
{
    ui->Tableau->setCurrentCell(ui->Tableau->rowCount()+2,0);
}

void MainWindow::on_actionSauvegarder_triggered()
{
    if(!savedatleastonce)
    {
        //Ask File name
        //    fileName = // TODO
    }



    m_handler->setDatabaseName(fileName);
    m_handler->saveTable();
    setWindowTitle(fileName+" - "+program_name);
    savedatleastonce=true;
}

void MainWindow::on_actionNouveau_triggered()
{

    //Ask File name
    //    fileName = // TODO


    m_handler->setDatabaseName(fileName);
    setWindowTitle(fileName+" - "+program_name);
    savedatleastonce=false;
}

void MainWindow::on_actionOuvrir_triggered()
{
    //Ask File name
    //    fileName = // TODO
    m_handler->setDatabaseName(fileName);
    setWindowTitle(fileName+" - "+program_name);
    m_handler->readDatabase();

    //afficher
    showTable();
    savedatleastonce=true;
}


void MainWindow::showTable()
{

}
