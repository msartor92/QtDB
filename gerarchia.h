#ifndef GERARCHIA_H
#define GERARCHIA_H
#include<string>
#include<ostream>
using std::ostream;
using std::string;

class MemoriaMassa{
protected:
    string Codice;
    string Interfaccia;
    string Capacita;
    MemoriaMassa(string code="", string i="", string c=0):Codice(code),Interfaccia(i),Capacita(c){}
    MemoriaMassa(const MemoriaMassa &m):Codice(m.getcodice()),Interfaccia(m.getinterfaccia()),Capacita(m.getcapacita()){}
public:
    string getcodice() const{ return Codice;}
    string getinterfaccia() const{ return Interfaccia; }
    string getcapacita() const{ return Capacita; }
    virtual ~MemoriaMassa(){}
    virtual bool operator==(const MemoriaMassa& m)const {
        return Codice==m.getcodice() && Interfaccia==m.getinterfaccia() && Capacita==m.getcapacita();
    }
    virtual bool operator!=(const MemoriaMassa& m)const {
        return !MemoriaMassa::operator ==(m);
    }
    friend ostream& operator<<(ostream & os, const MemoriaMassa& m){
        return os<<m.getcodice()<<"\t\t"<<m.getinterfaccia()<<"\t"<<m.getcapacita();
    }
};

class SSD:public MemoriaMassa{
private:
    string Consumo;
public:
    SSD(string code, string i,string c, string cons):MemoriaMassa(code,i,c),Consumo(cons){}
    SSD(const SSD& s):MemoriaMassa(s),Consumo(s.getconsumo()){}
    string getconsumo() const{ return Consumo; }
    bool operator==(const SSD& s)const {
        return Consumo==s.getconsumo() && Codice==s.getcodice() && Interfaccia==s.getinterfaccia() && Capacita==s.getcapacita();
    }
    bool operator !=(const SSD& s)const {
        return !SSD::operator==(s);
    }
    friend ostream& operator<<(ostream & os, const SSD& m){
        return os<<m.getcodice()<<"\t\t"<<m.getinterfaccia()<<"\t"<<m.getcapacita()<<"\t"<<m.getconsumo();
    }
};

class Tradizionale: public MemoriaMassa{
private:
    string Velocita;//di rotazione
public:
    Tradizionale(string code, string i, string c, string v):MemoriaMassa(code,i,c),Velocita(v){}
    Tradizionale(const Tradizionale &t):MemoriaMassa(t),Velocita(t.getvelocita()){}
    string getvelocita() const{ return Velocita; }
    bool operator==(const Tradizionale& t)const {
        return Velocita==t.getvelocita() && Codice==t.getcodice() && Interfaccia==t.getinterfaccia() && Capacita==t.getcapacita();
    }
    bool operator !=(const Tradizionale& t)const {
        return !Tradizionale::operator ==(t);
    }
    friend ostream& operator<<(ostream & os, const Tradizionale& m){
        return os<<m.getcodice()<<"\t\t"<<m.getinterfaccia()<<"\t"<<m.getcapacita()<<"\t\t"<<m.getvelocita();
    }
};

class Smartaptr{
public:
    MemoriaMassa* ptr;
    Smartaptr(const Smartaptr& m){
        if(dynamic_cast<SSD*>(m.ptr))
            ptr=new SSD(*dynamic_cast<SSD*>(m.ptr));
        else if(dynamic_cast<Tradizionale*>(m.ptr))
            ptr=new Tradizionale(*dynamic_cast<Tradizionale*>(m.ptr));
    }
    Smartaptr(MemoriaMassa* m=0):ptr(m){}
    ~Smartaptr(){if(ptr) delete ptr;}
    MemoriaMassa& operator*()const{ return *ptr; }

    bool operator!=(const MemoriaMassa& m) const{ return *ptr!=m; }
    bool operator==(const MemoriaMassa& m) const{ return *ptr==m; }
    bool operator!=(const Smartaptr& m) const{ return ptr!=m.ptr; }
    bool operator==(const Smartaptr& m) const{ return *ptr==*m.ptr; }
    Smartaptr* operator=(const Smartaptr& s){
        if(dynamic_cast<SSD*>(s.ptr))
            ptr=new SSD(*dynamic_cast<SSD*>(s.ptr));
        else if(dynamic_cast<Tradizionale*>(s.ptr))
            ptr=new Tradizionale(*dynamic_cast<Tradizionale*>(s.ptr));
        return this;
    }

    friend ostream& operator<<(ostream & os, const Smartaptr& m){
        if(dynamic_cast<SSD*>(m.ptr))
            os<<*(dynamic_cast<SSD*>(m.ptr));
        else if(dynamic_cast<Tradizionale*>(m.ptr))
            os<<*(dynamic_cast<Tradizionale*>(m.ptr));
        return os;
    }
};

#endif // GERARCHIA_H
