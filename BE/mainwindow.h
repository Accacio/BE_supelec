#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include "handler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void removeElement();
    void newElement();
    void updateTable();

    bool setTypeDB();


private slots:
    void on_AjouterElement_clicked();

    void on_SupprimerElement_clicked();

    void on_Tableau_pressed(const QModelIndex &index);

    void on_actionSauvegarder_triggered();

    void on_actionNouveau_triggered();

    void on_actionOuvrir_triggered();

    void on_actionSauvegarder_sous_triggered();

private:
    Ui::MainWindow *ui;
    Handler * m_handler;
    QString program_name=QString("Gestion Bibliothèque");
    bool savedatleastonce;
    QString fileName = QString("untitled.db") ;
};

#endif // MAINWINDOW_H
