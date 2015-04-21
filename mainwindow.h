#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"gerarchia.h"
#include"container.h"
#include<QMainWindow>
#include<string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    Container<Smartaptr> k;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_Disco_clicked();

    void on_SSD_clicked();

    void on_inserisci_clicked();

    void on_aggiorna_clicked();

    void on_eliminaelemento_clicked();

    void on_cerca_clicked();

    void on_cercaparzialebutton_clicked();

    void on_cercamodificabutton_clicked();

    void on_Discocerca_clicked();

    void on_SSDcerca_clicked();

    void on_modificabutton_clicked();

    void on_salvabutton_clicked();

    void on_caricabutton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
