#include "messaggio.h"
#include "ui_messaggio.h"

messaggio::messaggio(QString txt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messaggio)
{
    ui->setupUi(this);
    ui->label->setText(txt);
}

messaggio::~messaggio()
{
    delete ui;
}

void messaggio::on_okbutton_clicked()
{
    this->close();
}
