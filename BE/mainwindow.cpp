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

//    QString * titre= new QString("Titre");
//    QString * titre_data= new QString("The neverending story");
//    QString * auteur= new QString("Auteur");
//    QString * auteur_data= new QString("Mafichael Ende");
//    QString * isbn= new QString("ISBN");
//    qint64 * isbn_data=new qint64;
//    *isbn_data= (qint64) 3522128001;
//    QString * annee= new QString("Annee");
//    int * annee_data=new int;
//    * annee_data=(int) 1979;


//    PersistentAttribute * title = new PersistentAttribute(titre,QVariant::Type::String,titre_data);
//    PersistentAttribute * author = new PersistentAttribute(auteur,QVariant::Type::String,auteur_data);
//    PersistentAttribute * Isbn = new PersistentAttribute(isbn,QVariant::Type::LongLong,isbn_data);
//    PersistentAttribute * year = new PersistentAttribute(annee,QVariant::Type::Int,annee_data);
//    Persistentobject * object= new Livre();
//    object->updateAttribute(0,title);
//    object->updateAttribute(1,author);
//    object->updateAttribute(2,Isbn);
//    object->updateAttribute(3,year);


//    m_handler->readDatabase();



//    m_handler->addObject(object);
//    m_handler->addObject(object);


//    std::cout<<" !!!!!!!!!! Objects in List !!!!!!!!!! "<<std::endl;
//    for(int i=0;i<m_handler->getObjectList()->size();i++)
//    {
//        qDebug()<<m_handler->getObjectList()->at(i)->print();
//    }

//    std::cout<<" !!!!!!!!!! Objectsstructure !!!!!!!!!! "<<std::endl;
//    qDebug()<<m_handler->getObjectList()->at(0)->objectStructure->at(0);
//    qDebug()<<m_handler->getObjectList()->at(0)->objectStructure->at(1);
//    qDebug()<<m_handler->getObjectList()->at(0)->objectStructure->at(2);
//    qDebug()<<m_handler->getObjectList()->at(0)->objectStructure->at(3);

    //qDebug()<<m_handler->getObjectList()->at(0)->getAttributes()->size();


//    updateTable();


//    m_handler->setDatabaseName("olala.db");



//    m_handler->saveTable();





    //delete



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newElement()
{

    Persistentobject * tempObj= m_handler->newObject();

    if(ui->Tableau->currentRow()>=0)
    {
        ui->Tableau->insertRow(ui->Tableau->currentRow());

        m_handler->addObject(ui->Tableau->currentRow(),tempObj);
    }
    else
    {
        ui->Tableau->insertRow(ui->Tableau->rowCount());

        m_handler->addObject(ui->Tableau->rowCount(),tempObj);
    }

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
        std::cout<<"Columns inserted"<<std::endl;

        ui->Tableau->setHorizontalHeaderLabels(*m_handler->getObjectList()->at(0)->objectStructure);

        ui->Tableau->insertRow(ui->Tableau->rowCount());

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
    qDebug()<<ui->Tableau->currentRow();
    m_handler->printObjects();
    ui->Tableau->setCurrentCell(ui->Tableau->rowCount()+2,0);
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



    on_AjouterElement_clicked();

    m_handler->setDatabaseName(fileName);
    setWindowTitle(fileName+" - "+program_name);
    savedatleastonce=true;
}

void MainWindow::on_actionOuvrir_triggered()
{
//    //Ask File name

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
    std::cout<<"Database name set"<<std::endl;
    setWindowTitle(fileName+" - "+program_name);
    m_handler->clearObjects();
    m_handler->readDatabase();
    std::cout<<"Database read"<<std::endl;

    savedatleastonce=true;

    //afficher
    updateTable();

}


void MainWindow::updateTable()
{
    ui->Tableau->clear();
    ui->Tableau->setRowCount(0);
    ui->Tableau->setColumnCount(0);
    std::cout<<"Table cleared"<<std::endl;

    if(m_handler->getObjectList()->isEmpty())
    {
       std::cout<<"No objects in list"<<std::endl;
       return;
    }



    for(int i=0;i<m_handler->getObjectList()->at(0)->objectStructure->size();i++)
    {
        ui->Tableau->insertColumn(i);
    }
    std::cout<<"Columns inserted"<<std::endl;

    ui->Tableau->setHorizontalHeaderLabels(*m_handler->getObjectList()->at(0)->objectStructure);

    std::cout<<"Headers Set" <<std::endl;

    for(int i=0;i<m_handler->getObjectList()->size();i++)
    {
        ui->Tableau->insertRow(i);

        for(int j=0;j<m_handler->getObjectList()->at(0)->getAttributes()->size();j++)
        {


            QTableWidgetItem *newItem = new QTableWidgetItem(m_handler->getObjectList()->at(i)->getDataFromAttribute(m_handler->getObjectList()->at(i)->getAttributes()->at(j)));
            ui->Tableau->setItem(i,j,newItem);

        }

    }
    std::cout<<"Rows inserted"<<std::endl;



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


