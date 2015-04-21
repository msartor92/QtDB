# QtDB

Progetto del corso di programmazione ad oggetti  realizzato nell'anno accademico 2013/2014 per il corso di laurea in informatica dell'[Università Degli Studi di Padova](http://www.unipd.it) da Sartor Michele e-mail:michele.sartor.2@studenti.unipd.it

##Descrizione del progetto

QtDB è un applicazione scritta in C++ basata sulla Libreria [Qt](http://www.qt.io/) versione 4.8 che costituisce un sistema minimale per la gestione di un (piccolo) database tramite una interfaccia utente grafica.

##Componenti

**Template di classe Container<K>**
Ho definito un template di classe Container<K> i cui oggetti rappresentano un contenitore di oggetti di tipo K. La classe Container<K> è una lista doppiamente lincata che fornisce le funzionalit`a di: 
(1) inserimento, 
(2) rimozione, 
(3) ricerca,
(4) modifica,
(5) gestione degli iteratori
(6) stampa.

**Gerarchia di classi**
Ho definito una gerarchia di classi G composta da tre classi A, B e C che modellano una realtà di oggetti da gestire tramite il database. La realtà di oggetti che ho scelto di modellare sono le memorie di massa. 
La classe base, MemoriaMassa,  e ` quindi superclasse di ogni altra classe della gerarchia G. Vi sono inoltre due sottoclassi, SSD e Tradiazionale, che rappresentano hard disk dei corrispondenti tipi. 
Le classi della gerarchia sono dotate di opportune interfacce pubbliche contenti i metodi per la gestione dei dati.

Al fine di popolare un contenitore Container<K> con oggetti della gerarchia di classi G, ho definito una classe SmartAptr di puntatori smart alla classe base A di G che avr`a quindi come campo dati un
puntatore polimorfo ad A — e conseguentemente di popolare il contenitore con oggetti di SmartAptr.

**Interfaccia Grafica**
Ho sviluppato una GUI usando la libreria Qt che permetta all’utente di gestire agevolmente il database di oggetti delle classi della gerarchia. Ho quindi sviluppato una GUI per la gestione di un contenitore di puntatori (smart) polimorfi alla superclasse A della gerarchia, che come requisito permette:

(1) inserimenti
(2) rimozioni
(3) ricerche
(4) modifiche
(5) caricamento di dati da file di testo preformattati
(6) memorizzazione del databese su file di testo

di oggetti della gerarchia nel database rappresentato dal contenitore C.

L'intero progetto è stato sviluppato su piattafroma Linux Kubuntu 64bit, tramite [QtDesigner](https://www.qt.io/download/) e compilatore  GNU g++ versione 4.x
