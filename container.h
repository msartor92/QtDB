#ifndef CONTAINER_H
#define CONTAINER_H
#include<iostream>
#include<string.h>
#include<sstream>

template<class T>
class Container{
private:
  friend class Iteratore;
  class Item{
  private:
    T info;
    Item* next;
    Item* prev;
  public:
    Item();
    Item(const T& i, Item* n=0, Item* p=0);
    bool operator==(const Item&) const;
    bool operator!=(const Item&) const;
    T operator*() const;
    const T& getinfo()const { return info;}
    Item* getnext()const { return next; }
    Item* getprev()const { return prev; }
    void setnext(Item* n){ next=n; }
    void setprev(Item* n){ prev=n; }
    void setinfo(const T& i){ info=i;}
  };
  Item* first;

public:
  class Iteratore{
  private:
      Item* punt;
  public:
      Iteratore(typename Container<T>::Item* p=0);
      bool operator==(const Iteratore&) const;
      bool operator!=(const Iteratore&) const;
      Iteratore& operator++();
      Iteratore operator++(int);
      Iteratore& operator--();
      Iteratore operator--(int);
      Item* operator*();
  };
  Container();
  Container(Container&);
  ~Container();
  Iteratore begin() const;
  Iteratore end() const;
  bool empty()const;
  int size()const;
  Item* copia(Item* );
  void push(const T&);
  T pop();
  bool remove(const T&);
  bool modifica(const T&, const T&);// come replace in vector restituisce true se andata a buon fine
  Item* search(const T&) const;
  std::string print()const;
  std::string print(Iteratore& it)const;
  Container& operator=(const Container<T>& c);
};

// METODI DI ITEM
template<class T>
Container<T>::Item::Item():next(0),prev(0){}
template<class T>
Container<T>::Item::Item(const T& i, Item* n, Item* p):info(i),next(n),prev(p){}
template<class T>
bool Container<T>::Item::operator==(const Item& p) const{
    if(*this==&p) return true;
    else return false;
}
template<class T>
bool Container<T>::Item::operator!=(const Item& p) const{
    if(*this!=&p) return true;
    else return false;
}
template<class T>
T Container<T>::Item::operator*()const{
    return info;
}
// METODI DI ITERATORE
template<class T>
Container<T>::Iteratore::Iteratore(Item* p):punt(p){}
template<class T>
bool Container<T>::Iteratore::operator==(const Iteratore& i) const{
    return punt==i.punt;
}
template<class T>
bool Container<T>::Iteratore::operator!=(const Iteratore& i) const{
    return punt!=i.punt;
}
template<class T>
typename Container<T>::Iteratore& Container<T>::Iteratore::operator++(){
    if(punt!=0) punt=punt->getnext();
    return *this;
}
template<class T>
typename Container<T>::Iteratore Container<T>::Iteratore::operator++(int){
    Iteratore i=*this;
    if(punt!=0) punt=punt->getnext();
    return i;
}
template<class T>
typename Container<T>::Iteratore& Container<T>::Iteratore::operator--(){
    if(punt!=0) punt=punt->getprev();
    return *this;
}
template<class T>
typename Container<T>::Iteratore Container<T>::Iteratore::operator--(int){
    Iteratore i=*this;
    if(punt!=0) punt=punt->getprev();
    return i;
}
template<class T>
typename Container<T>::Item* Container<T>::Iteratore::operator *(){
    return punt;
}
//METODI DI CONTAINER
template<class T>
Container<T>::Container():first(0){}
template<class T>
Container<T>::Container(Container& c):first(copia(c.first)){}
template<class T>
Container<T>::~Container(){
    while(first!=0){
        Item *t=first->getnext();
        delete first;
        first=t;
    }
}
template<class T>
typename Container<T>::Iteratore Container<T>::begin() const{
    return Iteratore(first);
}
template<class T>
typename Container<T>::Iteratore Container<T>::end() const{
    return Iteratore();
}
template<class T>
typename Container<T>::Item* Container<T>::search(const T& i) const{
    for(Iteratore it=begin();it!=end();++it){
        if((*it)->getinfo()==i)
            return *it;
    }
    return NULL;
}
template<class T>
void Container<T>::push(const T& i){
    first=new Item(i,first,0);
    if(first->getnext())
        (first->getnext())->setprev(first);
}
template<class T>
bool Container<T>::empty()const{
    return first==0;
}
template<class T>
T Container<T>::pop(){
    T p;
    if(first!=0){
        p=first->getinfo();
        Item* q=first;
        first=first->getnext();
        first->setprev(0);
        delete q;
    }
    return p;
}
template<class T>
bool Container<T>::remove(const T& i){
    Item* temp=first;
    bool e=true;
    while(temp!=0 && e){
        if(temp->getinfo()==i){
            if(temp->getprev()==0){
                first=first->getnext();
                if(first){
                    first->setprev(0);
                    delete temp;
                }
            }
            else{
                (temp->getprev())->setnext(temp->getnext());
                if(temp->getnext())
                        (temp->getnext())->setprev(temp->getprev());
                delete temp;

            }
            e=false;
        }
        else temp=temp->getnext();
    }
    return !e;
}

template<class T>
bool Container<T>::modifica(const T& o, const T& n){// come replace in iter vector
    Item* p=search(o);
    if(p){
        p->setinfo(n);
        return true;
    }
    return false;
}
template<class T>
int Container<T>::size() const{
    int c=0;
    for(Iteratore it=begin();it!=end();++it){
        c++;
    }
    return c;
}
template<class T>
typename Container<T>::Item* Container<T>::copia(Item* o){
  Item* p=o;
  if(!p)
    return 0;
  Item* primo=new Item;  //primo punta alla lista nuova
  primo->info=p->info;
  Item* q=primo;  //q scorre la lista nuova
  while(p->next){
      q->next=new Item(p->info,0,q);
      p=p->next;
      q=q->next;
  }
  return primo;
}
template<class T>
typename Container<T>::Container& Container<T>::operator=(const Container<T>& c){
  if(this!=&c){
    this->~Container();
    first=copia(c.first);
  }
  return *this;
}
template<class T>
std::string Container<T>::print() const{
    std::ostringstream stream;
    std::string dati;
    for(Iteratore it=begin();it!=end();++it){
        stream<<(**it).getinfo();
        stream<<"\n";
    }
    dati+= stream.str();
    return dati;
}
template<class T>
std::string Container<T>::print(Iteratore& it) const{
    std::ostringstream stream;
    std::string dati;
    stream<<(**it).getinfo();
    stream<<"\n";
    dati+= stream.str();
    return dati;
}
#endif // CONTAINER_H
