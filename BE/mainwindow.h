#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
private slots:
    void on_AjouterElement_clicked();

    void on_SupprimerElement_clicked();

    void on_Tableau_pressed(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Handler * myhandler;
    QString program_name=QString("Gestion Bibliothèque");
};

#endif // MAINWINDOW_H
