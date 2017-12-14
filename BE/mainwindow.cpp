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
    std::cout<<"Database name set"<<std::endl;
    setWindowTitle(fileName+" - "+program_name);
    m_handler->readDatabase();
    std::cout<<"Database read"<<std::endl;



    savedatleastonce=true;
    //afficher
    updateTable();



    std::cout<<"End of Open================"<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;

}


void MainWindow::updateTable()
{
    ui->Tableau->clear();
    ui->Tableau->setRowCount(0);
    ui->Tableau->setColumnCount(0);
    std::cout<<"Table cleared"<<std::endl;
//    std::cout<<m_handler->getObjectList()->first()->objectStructure->first().toStdString()<<std::endl;

    std::cout<<"objectStructure cleared"<<std::endl;

//    QStringList * objectStructure=new QStringList;
    QList<Persistentobject *> * objects=new QList<Persistentobject *>();
//    objects=m_handler->objects;
    *objects=*m_handler->getObjectList();

    std::cout<<"Table of object:";
    qDebug()<<objects->at(0)->getAttributes()->at(0)->getName();
    //delete objects;
//    =*(m_handler->getObjectList()->first()->objectStructure);
//    objectStructure<<"Titre"<<"Auteur"<<"ISBN"<<"Année";
//    objectStructure=m_handler->getObjectList()->at(0)->objectStructure;
//    qDebug()<<*(QString *)m_handler->getObjectList()->at(0)->getAttributes()->at(0)->getData();
//    qDebug()<<objectStructure->at(0);

    std::cout<<"objectStructure copied"<<std::endl;

    for(int i=0;i<4;i++)
    {
        ui->Tableau->insertColumn(i);
    }
    std::cout<<"Columns inserted"<<std::endl;

    //ui->Tableau->setHorizontalHeaderLabels(*m_handler->getObjectList()->at(0)->objectStructure);
//    ui->Tableau->setVerticalHeaderLabels(*(m_handler->getObjectList()->first()->objectStructure));
    std::cout<<"Headers Set" <<std::endl;

}
