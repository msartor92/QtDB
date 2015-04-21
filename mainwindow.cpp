#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"messaggio.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){

    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

// INSERISCI
void MainWindow::on_Disco_clicked(){
    ui->consumo->setDisabled(true);
    ui->velocitadirotazione->setEnabled(true);
}
void MainWindow::on_SSD_clicked(){
    ui->consumo->setEnabled(true);
    ui->velocitadirotazione->setDisabled(true);
}

void MainWindow::on_inserisci_clicked(){
    std::string codice=ui->codiceprodotto->text().trimmed().toStdString();
    std::string interfaccia=ui->interfaccia->text().trimmed().toStdString();
    std::string capacita=QString::number(ui->capacita->value()).toStdString();
   if(ui->SSD->isChecked()){
        std::string consumo=QString::number(ui->consumo->value()).toStdString();
        //devo inserire nel container un ssd
        if(!codice.empty() && !interfaccia.empty() && !capacita.empty() && !consumo.empty()){
            Smartaptr hd=new SSD(codice,interfaccia,capacita,consumo);
            k.push(hd);
            messaggio* x=new messaggio("L'ssd "+ui->codiceprodotto->text().trimmed()+" e' stato inserito correttamente!");
            x->exec();
        }
        else{
            messaggio* x=new messaggio("Non hai completato tutti i campi necessari all'inserimento del prodotto oppure il codice prodotto e' gia' presente!");
            x->exec();
        }
    }
    else{
        std::string velocita=QString::number(ui->velocitadirotazione->value()).toStdString();
        //devo inserire nel container un disco tradizionale
        if(!codice.empty() && !interfaccia.empty() && !capacita.empty() && !velocita.empty()){
            Smartaptr hd=new Tradizionale(codice,interfaccia,capacita,velocita);
            k.push(hd);
            messaggio* x=new messaggio("Il disco "+ui->codiceprodotto->text().trimmed()+" e' stato inserito correttamente!");
            x->exec();
        }
        else{
            messaggio* x=new messaggio("Non hai completato tutti i campi necessari all'inserimento del prodotto oppure il codice prodotto e' gia' presente!");
            x->exec();
        }
    }
    //resetto i campi dati nell'interfaccia
    ui->codiceprodotto->setText("");
    ui->interfaccia->setText("");
    ui->capacita->setValue(0);
    ui->consumo->setValue(0);
}
//AGGIORNA
void MainWindow::on_aggiorna_clicked(){
    QString s;
    if(k.size()<=0){
            messaggio* x=new messaggio("Database vuoto!");
            x->exec();
    }
    else{
        s.append("Codice\t\tInterfaccia\tCapacita\tConsumo\tVelocita'\n");
        s.append(QString::fromStdString(k.print()));
        ui->dati->setText(s);
    }
}
//ELIMINA
void MainWindow::on_eliminaelemento_clicked(){
    std::string code=ui->elimina->text().trimmed().toStdString();
    if(code.empty()){
        messaggio* x=new messaggio("Devi inserire un codice prodotto per eliminarlo!");
        x->exec();
    }
    else{
        Smartaptr a;
        bool found=false;
        for(Container<Smartaptr>::Iteratore it=k.begin();it!=k.end() && !found; ++it)
            if((*it)->getinfo().ptr->getcodice()==code){
                a=(*it)->getinfo();
                found=true;
            }
        if(a!=NULL){
            if(k.remove(a)){
                messaggio* x=new messaggio("Elemento eliminato con successo!");
                x->exec();
                ui->elimina->setText("");
                QString s="Codice\t\tInterfaccia\tCapacita\tConsumo\tVelocita'\n";
                s.append(QString::fromStdString(k.print()));
                ui->dati->setText(s);
            }
        }
        else{
            messaggio* x=new messaggio("Non e' stato possibile eliminare il prodotto dalla lista!");
            x->exec();
        }
    }
}
//RICERCA
void MainWindow::on_Discocerca_clicked()
{
    ui->consumocerca->setDisabled(true);
    ui->velocitadirotazionecerca->setEnabled(true);
}
void MainWindow::on_SSDcerca_clicked()
{
    ui->consumocerca->setEnabled(true);
    ui->velocitadirotazionecerca->setDisabled(true);
}
void MainWindow::on_cerca_clicked(){
    QString s;
    s.append("Codice\t\tInterfaccia\tCapacita\tConsumo\tVelocita'\n");
    Smartaptr hd;
    //input dei dati
    std::string code=ui->codiceprodottocerca->text().trimmed().toStdString();
    std::string interfaccia=ui->interfacciacerca->text().trimmed().toStdString();
    std::string capacita=QString::number(ui->capacitacerca->value()).toStdString();
    if(code!="" && interfaccia!="" && capacita!="" && (ui->consumo->value()!=0 || ui->velocitadirotazionecerca->value()!=0)){
        if(ui->SSD->isChecked())
            hd=new SSD(code,interfaccia,capacita,QString::number(ui->consumocerca->value()).toStdString());
        else
            hd=new Tradizionale(code,interfaccia,capacita,QString::number(ui->velocitadirotazionecerca->value()).toStdString());
        //effettuo la ricerca
        for(Container<Smartaptr>::Iteratore it=k.begin();it!=k.end();++it)
            if(*((*it)->getinfo())==*hd)
                s.append(QString::fromStdString(k.print(it)));
        //visualizzo i risultati
        if(s!="Codice\t\tInterfaccia\tCapacita\tConsumo\tVelocita'\n")
            ui->dati->setText(s);
        else{
            messaggio* x=new messaggio("Nessun elemento trovato con queste caratteristiche");
            x->exec();
        }
    }
    else{
        messaggio* x=new messaggio("Devi compilare tutti i campi per effettuare la ricerca");
        x->exec();
    }
}
//RICERCA PARZIALE
void MainWindow::on_cercaparzialebutton_clicked(){
    if(ui->cercaparziale->text().trimmed()==""){
        messaggio* x=new messaggio("Non hai inserito nessuna keyword");
        x->exec();
    }
    else{
        QString s,temp;
        s.append("Codice\t\tInterfaccia\tCapacita\tConsumo\tVelocita'\n");
        QStringList keys=ui->cercaparziale->text().trimmed().split(" ");

        for(Container<Smartaptr>::Iteratore it=k.begin();it!=k.end();++it){
            for(int i=0;i<keys.size();i++){
                if(!s.contains(QString::fromStdString((*it)->getinfo().ptr->getcodice()))){
                    temp=QString::fromStdString(k.print(it));
                    if(temp.contains(keys[i]))
                        s.append(temp);
                }
            }
        }
        ui->dati->setText(s);
        //highlight delle keyword trovate
        QTextDocument* contenuto=ui->dati->document();
        for(int i=0;i<keys.size();i++){
            QTextCursor hlcursor(contenuto);
            QTextCharFormat plainformat(hlcursor.charFormat());
            plainformat.setBackground(Qt::green);
            while(!hlcursor.isNull() && !hlcursor.atEnd()) {
                hlcursor=contenuto->find(keys.at(i), hlcursor);
                if(!hlcursor.isNull())
                    hlcursor.mergeCharFormat(plainformat);
            }
        }
    }
}
//MODIFICA
void MainWindow::on_cercamodificabutton_clicked()
{
    if(ui->cercamodifica->text()==""){
        messaggio* x=new messaggio("Devi inserie un codice prodotto valido!");
        x->exec();
    }
    else{
        bool found=false;
        Smartaptr spt;
        for(Container<Smartaptr>::Iteratore it=k.begin();it!=k.end() && !found; ++it)
            if((*it)->getinfo().ptr->getcodice()==ui->cercamodifica->text().trimmed().toStdString()){
                spt=(*it)->getinfo();
                found=true;
            }
        if(spt.ptr==NULL){
            messaggio* x=new messaggio("Il codice prodotto non e' presente nella lista!");
            x->exec();
        }
        else{
            ui->interfacciamodifica->setEnabled(true);
            ui->interfacciamodifica->setText(QString::fromStdString(spt.ptr->getinterfaccia()));
            ui->capacitamodifica->setEnabled(true);
            ui->capacitamodifica->setValue( (QString::fromStdString(spt.ptr->getcapacita())).toInt());
            ui->interfacciamodificalabel->setEnabled(true);
            ui->capacitamodificalabel->setEnabled(true);
            ui->modificabutton->setEnabled(true);
            if(dynamic_cast<SSD*>(spt.ptr)){
                SSD* ssd=dynamic_cast<SSD*>(spt.ptr);
                ui->Discomodificaradio->setDisabled(true);
                ui->velocitamodifica->setDisabled(true);
                ui->velocitamodificalabel->setDisabled(true);

                ui->consumomodifica->setEnabled(true);
                ui->SSDmodificaradio->setEnabled(true);
                ui->SSDmodificaradio->setChecked(true);
                ui->consumomodifica->setValue((QString::fromStdString(ssd->getconsumo())).toDouble());
                ui->consumomodificalabel->setEnabled(true);
            }
            else{
                Tradizionale* tr=dynamic_cast<Tradizionale*>(spt.ptr);
                ui->SSDmodificaradio->setDisabled(true);
                ui->consumomodifica->setDisabled(true);
                ui->consumomodificalabel->setDisabled(true);

                ui->Discomodificaradio->setEnabled(true);
                ui->Discomodificaradio->setChecked(true);
                ui->velocitamodifica->setEnabled(true);
                ui->velocitamodifica->setValue((QString::fromStdString(tr->getvelocita())).toInt());
                ui->velocitamodificalabel->setEnabled(true);
            }
        }
    }
}

void MainWindow::on_modificabutton_clicked()
{
    Smartaptr n,old;
    for(Container<Smartaptr>::Iteratore it=k.begin();it!=k.end();++it)
        if((*it)->getinfo().ptr->getcodice()==ui->cercamodifica->text().trimmed().toStdString())
            old=(*it)->getinfo();
    if(ui->SSDmodificaradio->isChecked())
         n=new SSD(old.ptr->getcodice(),ui->interfacciamodifica->text().trimmed().toStdString(),ui->capacitamodifica->text().trimmed().toStdString(),ui->consumomodifica->text().trimmed().toStdString());
    else
        n=new Tradizionale(old.ptr->getcodice(),ui->interfacciamodifica->text().trimmed().toStdString(),ui->capacitamodifica->text().trimmed().toStdString(),ui->velocitamodifica->text().trimmed().toStdString());
    if(k.modifica(old,n)){
        messaggio* x=new messaggio("Dati modificati con successo!");
        x->exec();
    }
    else{
        messaggio* x=new messaggio("Nessuna modifica effettuata!");
        x->exec();
    }
    //resetto i campi dati nell'interfaccia
    ui->cercamodifica->setText("");
    ui->interfacciamodifica->setText("");
    ui->capacitamodifica->setValue(0);
    ui->consumomodifica->setValue(0);
    ui->velocitamodifica->setValue(7200);
}
//GESTIONE DATI
void MainWindow::on_salvabutton_clicked()
{
    if(k.empty()){
        messaggio* x=new messaggio("Non puoi salvare un database vuoto!");
        x->exec();
    }
    else{
        QString dato,element;
        for(Container<Smartaptr>::Iteratore it=k.begin();it!=k.end();++it){
            if(dynamic_cast<SSD*>(&*(*it)->getinfo()))
                dato.append("[S] ");
            else
                dato.append("[T] ");
            element=QString::fromStdString(k.print(it));
            //correzzione della formattazione dei dati per il salvataggio sul file
            element.replace("\t\t","\t");
            element.replace("\t"," ");
            dato.append(element);
        }
        //lettura del nome file da qfiledialog
        QString fileName = QFileDialog::getOpenFileName(this, QObject::tr("Salva File"), "", QObject::tr("Files (*.dbd)"));
        //inserimento dati nel file
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            messaggio* x=new messaggio("Problemi con il caricamento del file!");
            x->exec();
         }
        QTextStream out(&file);
        out<<dato;
        file.close();
        messaggio* x=new messaggio("salvataggio completato!");
        x->exec();
    }
}

void MainWindow::on_caricabutton_clicked()
{
    //apertura widget file
    QString fileName = QFileDialog::getOpenFileName(this, QObject::tr("Apri File"),"",QObject::tr("Files (*.dbd)"));
    //lettura file
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
         //svuoto il container per evitare inconsistenzene dati
         k.~Container();
         while (!file.atEnd()) {
             bool found=false;
             QByteArray line = file.readLine();
             QString temp(line);
             temp.remove(QRegExp("\n"));
             QStringList data=temp.split(" ");
             //controllo che non sia gia presente nel container un elemento con il nuovo codice prodotto
             for(Container<Smartaptr>::Iteratore it=k.begin();it!=k.end() && !found ;++it)
                 if((*it)->getinfo().ptr->getcodice()==data.at(1).toStdString())
                     found=true;
             //inserisco il nuovo prodotto
             if(data.size()==5 && !found){
                 if(data.at(0)=="[S]"){
                     Smartaptr hd=new SSD(data.at(1).toStdString(),data.at(2).toStdString(),data.at(3).toStdString(),data.at(4).toStdString());
                     k.push(hd);
                 }
                 else if(data.at(0)=="[T]"){
                     Smartaptr hd=new Tradizionale(data.at(1).toStdString(),data.at(2).toStdString(),data.at(3).toStdString(),data.at(4).toStdString());
                     k.push(hd);
                 }
             }
         }
         file.close();
         //visualizzo i dati
         QString s;
         s.append("Codice\t\tInterfaccia\tCapacita\tConsumo\tVelocita'\n");
         s.append(QString::fromStdString(k.print()));
         ui->dati->setText(s);
     }
     else{
        messaggio* x=new messaggio("Problemi con il caricamento del file!");
        x->exec();
     }
}
