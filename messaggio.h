#ifndef MESSAGGIO_H
#define MESSAGGIO_H

#include <QDialog>

namespace Ui {
class messaggio;
}

class messaggio : public QDialog{
    Q_OBJECT
public:
    explicit messaggio(QString txt, QWidget *parent = 0);
    ~messaggio();
    
private slots:
    void on_okbutton_clicked();

private:
    Ui::messaggio *ui;
};

#endif // MESSAGGIO_H
