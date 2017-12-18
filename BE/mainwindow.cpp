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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newElement()
{

    //qDebug()<<ui->Tableau->currentRow();
    Persistentobject * tempObj= m_handler->newObject();

    if(ui->Tableau->currentRow()>=0)
    {
        m_handler->addObject(ui->Tableau->currentRow(),tempObj);
        int newRow=ui->Tableau->currentRow();
        ui->Tableau->insertRow(ui->Tableau->currentRow());



        for(int j=0;j<m_handler->getObjectList()->at(newRow)->getAttributes()->size();j++)
        {

            QTableWidgetItem *newItem = new QTableWidgetItem(m_handler->getObjectList()->at(newRow)->getDataFromAttribute(m_handler->getObjectList()->at(newRow)->getAttributes()->at(j)));
            ui->Tableau->setItem(newRow,j,newItem);

        }


    }
    else
    {
        m_handler->addObject(ui->Tableau->rowCount(),tempObj);
        int newRow=ui->Tableau->rowCount();
        ui->Tableau->insertRow(ui->Tableau->rowCount());



        for(int j=0;j<m_handler->getObjectList()->at(newRow)->getAttributes()->size();j++)
        {

            QTableWidgetItem *newItem = new QTableWidgetItem(m_handler->getObjectList()->at(newRow)->getDataFromAttribute(m_handler->getObjectList()->at(newRow)->getAttributes()->at(j)));
            ui->Tableau->setItem(newRow,j,newItem);

        }


    }

}

void MainWindow::updateElement(int row,int column)
{
    //std::cout<<" >>>>>>>>>> MainWindow::updateElement >>>>>>>>>> "<<std::endl;
    QTableWidgetItem * cell = ui->Tableau->item(row,column);
    //std::cout<<" cell copied "<<std::endl;
    Persistentobject * tempObj= m_handler->getObjectList()->at(row);
    tempObj->updateAttributeData(column,cell->text());
    tempObj->print();
    m_handler->updateObject(row,tempObj);

    //std::cout<<" <<<<<<<<<< MainWindow::updateElement <<<<<<<<<< "<<std::endl;
}

void MainWindow::removeElement()
{
//    qDebug()<<ui->Tableau->currentRow();
    if(ui->Tableau->currentRow()>0)
    {
        m_handler->removeObject(ui->Tableau->currentRow());
        ui->Tableau->removeRow(ui->Tableau->currentRow());

        ui->Tableau->setCurrentCell(ui->Tableau->rowCount()-1,0);

    }
    else
    {
        m_handler->removeObject(ui->Tableau->currentRow());
        ui->Tableau->removeRow(ui->Tableau->currentRow());

    }


//    else
//    {
//        ui->Tableau->removeRow(ui->Tableau->rowCount());
//        m_handler->removeObject(ui->Tableau->rowCount());
//    }

}

void MainWindow::on_AjouterElement_clicked()
{
    if(m_handler->getTypeDB()==Persistentobject::Types::noType||m_handler->getObjectList()->isEmpty())
    {
        if(!setTypeDB())
        {
            std::cout<<"No Type chosen"<<std::endl;
            return;
        }

        Persistentobject * tempObj= m_handler->newObject();
        m_handler->addObject(tempObj);

        for(int i=0;i<m_handler->getObjectList()->at(0)->objectStructure->size();i++)
        {
            ui->Tableau->insertColumn(i);
        }
        //std::cout<<"Columns inserted"<<std::endl;

        ui->Tableau->setHorizontalHeaderLabels(*m_handler->getObjectList()->at(0)->objectStructure);

        ui->Tableau->insertRow(ui->Tableau->rowCount());
        int newRow=ui->Tableau->rowCount()-1;

        for(int j=0;j<m_handler->getObjectList()->at(newRow)->getAttributes()->size();j++)
        {

            QTableWidgetItem *newItem = new QTableWidgetItem(m_handler->getObjectList()->at(newRow)->getDataFromAttribute(m_handler->getObjectList()->at(newRow)->getAttributes()->at(j)));
            ui->Tableau->setItem(newRow,j,newItem);

        }



    }
    else
    {
        newElement();
    }





}

void MainWindow::on_SupprimerElement_clicked()
{
    removeElement();
}

void MainWindow::on_Tableau_pressed(const QModelIndex &index)
{
    qDebug()<<QString(" Column: ")<<ui->Tableau->currentRow()<<QString(" Column: ")<<ui->Tableau->currentRow();

    updateElement(ui->Tableau->currentRow(),ui->Tableau->currentColumn());
    ui->Tableau->setCurrentCell(ui->Tableau->rowCount()+2,0);
    m_handler->printObjects();
}





void MainWindow::on_actionSauvegarder_triggered()
{
    if(!savedatleastonce)
    {
        QString oldFileName=fileName;
        fileName = QFileDialog::getSaveFileName(this,QString("Nouvelle Base de Donées"),QDir::currentPath(),QString("Base de Donées (*.db)"));

        if(fileName.isNull())
        {
            std::cout<<"No file selected"<<std::endl;
            fileName=oldFileName;
            return;
        }

        if(!setTypeDB())
        {
            std::cout<<"No Type chosen"<<std::endl;
            return;
        }
    }

    m_handler->setDatabaseName(fileName);
    m_handler->saveTable();
    setWindowTitle(fileName+" - "+program_name);
    savedatleastonce=true;
}

void MainWindow::on_actionSauvegarder_sous_triggered()
{
    QString oldFileName=fileName;
    fileName = QFileDialog::getSaveFileName(this,QString("Nouvelle Base de Donées"),QDir::currentPath(),QString("Base de Donées (*.db)"));

    if(fileName.isNull())
    {
        std::cout<<"No file selected"<<std::endl;
        fileName=oldFileName;
        return;
    }

    if(!setTypeDB())
    {
        std::cout<<"No Type chosen"<<std::endl;
        return;
    }

    m_handler->setDatabaseName(fileName);
    m_handler->saveTable();
    setWindowTitle(fileName+" - "+program_name);
    savedatleastonce=true;
}

void MainWindow::on_actionNouveau_triggered()
{

    QString oldFileName=fileName;
    fileName = QFileDialog::getSaveFileName(this,QString("Nouvelle Base de Donées"),QDir::currentPath(),QString("Base de Donées (*.db)"));


    if(fileName.isNull())
    {
        std::cout<<"No file selected"<<std::endl;
        fileName=oldFileName;
        return;
    }

     m_handler->clearObjects();
    ui->Tableau->setColumnCount(0);
    ui->Tableau->setRowCount(0);

    on_AjouterElement_clicked();

    m_handler->setDatabaseName(fileName);
    setWindowTitle(fileName+" - "+program_name);
    savedatleastonce=true;
}

void MainWindow::on_actionOuvrir_triggered()
{
    //Ask File name

    QString oldFileName=fileName;
    fileName = QFileDialog::getOpenFileName(this,QString("Ouvrir Base de Donées"),QDir::currentPath(),QString("Base de Donées (*.db)"));
    if(fileName.isNull())
    {
        std::cout<<"No file selected"<<std::endl;
        fileName=oldFileName;
        return;
    }



    if(!setTypeDB())
    {
        std::cout<<"No Type chosen"<<std::endl;
        return;
    }


    m_handler->setDatabaseName(fileName);
    //std::cout<<"Database name set"<<std::endl;
    setWindowTitle(fileName+" - "+program_name);
    m_handler->clearObjects();
    m_handler->readDatabase();
    //std::cout<<"Database read"<<std::endl;

    savedatleastonce=true;

    //afficher
    updateTable();

}


void MainWindow::updateTable()
{
    ui->Tableau->clear();
    ui->Tableau->setRowCount(0);
    ui->Tableau->setColumnCount(0);
    //std::cout<<"Table cleared"<<std::endl;

    if(m_handler->getObjectList()->isEmpty())
    {
       std::cout<<"No objects in list"<<std::endl;
       return;
    }



    for(int i=0;i<m_handler->getObjectList()->at(0)->objectStructure->size();i++)
    {
        ui->Tableau->insertColumn(i);
    }
    //std::cout<<"Columns inserted"<<std::endl;

    ui->Tableau->setHorizontalHeaderLabels(*m_handler->getObjectList()->at(0)->objectStructure);

    //std::cout<<"Headers Set" <<std::endl;

    for(int i=0;i<m_handler->getObjectList()->size();i++)
    {
        ui->Tableau->insertRow(i);

        for(int j=0;j<m_handler->getObjectList()->at(0)->getAttributes()->size();j++)
        {


            QTableWidgetItem *newItem = new QTableWidgetItem(m_handler->getObjectList()->at(i)->getDataFromAttribute(m_handler->getObjectList()->at(i)->getAttributes()->at(j)));
            ui->Tableau->setItem(i,j,newItem);

        }

    }
    //std::cout<<"Rows inserted"<<std::endl;



}

bool MainWindow::setTypeDB()
{
    QStringList items;
    items << QString("Livre") ;

    bool ok;
    QString item=QInputDialog::getItem(this, QString("Select Type of BD"),QString("Type:"), items, 0, false, &ok);

    if(!ok)
    {
        std::cout<<"No Type chosen"<<std::endl;
        return false;
    }

    m_handler->setTypeDB((Persistentobject::Types )(items.indexOf(item)+1));
    return true;
}





void MainWindow::on_Tableau_cellChanged(int row, int column)
{
    updateElement(row,column);
}
