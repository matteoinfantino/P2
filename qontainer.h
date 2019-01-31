#ifndef QONTAINER_H
#define QONTAINER_H
#include <iostream>
#include <initializer_list>

template <class T>
class Qontainer;

template <class T>
std::ostream& operator<<(std::ostream&, const Qontainer<T>&);

template <class T>
class Qontainer
{
    friend std::ostream& operator<< <T> (std::ostream&, const Qontainer&);
private:
    class nodo{
    public:
        T info;
        nodo *prev,*next;
        nodo(const T& t, nodo* p = 0, nodo* n = 0): info(t), prev(p), next(n) {}
        ~nodo(){
            if(next) delete next;
        }
    };
    nodo *first, *last;

//metodo ausiliario di copia
    static nodo* copy(nodo* f, nodo*& l){
        if(f==nullptr){
            l=nullptr;
            return nullptr;
        };
        nodo* x = new nodo(f->info,nullptr,nullptr), *p=x;
        while(f->next != nullptr){
            p->next = new nodo(f->next->info,p,nullptr);
            f=f->next;
            p=p->next;
        }
        l=p;
        return x;
    }
//metodo ausiliario di stampa
    static std::ostream& print(nodo* l,std::ostream& os) {
        if(!l) return os;
        os << l->info << ' ';
        print(l->next,os);
        return os;
    }
//metodo ausiliario di inserimento
//PRECONDIZIONE: inserisce in posizione 0<k<size(). L'inserimento in posizione <=0 e >=size() è assicurato dal metodo insert
// tramite push_front e push_back.
    static void insertAux(nodo* l, int k, const T& t){
        if(!l) return;
        if(k == 0){
            nodo *x = new nodo(t,l->prev,l);
            l->prev->next = x;
            l->prev = x;
            return;
        }
        insertAux(l->next,k-1,t);
    }
//metodo ausialiaro di rimozione
//PRECONDIZIONE: rimuove in posizione 0<k<size(). L'inserimento in posizione 0 e size() è assicurato dal metodo insert
// tramite pop_front e pop_back.
    static void removeAux(nodo* l,int k){
        if(!l)  return;
        if(k == 0){
            nodo* tmp = l;
            l->prev->next = l->next;
            l->next->prev = l->prev;
            tmp->prev = tmp->next = nullptr;
            delete tmp;
            return;
        }
        removeAux(l->next,k-1);
    }

    static void removeOneItemAux(nodo* &l, const T t){
        if(!l)  return;

        if(l->info == t){
            if(!l->next && !l->prev){
                delete l;
                l = nullptr;
                return;
            }
            nodo* tmp = l;
            if(!l->next && l->prev){
                l->prev->next = nullptr;
                tmp->prev = nullptr;
                delete tmp;
                return;
            }
            if(l->next && !l->prev){
                l->next->prev = nullptr;
                l = l->next;
                tmp->next = nullptr;
                delete tmp;
                return;
            }
            //l->next && l->prev
            l->next->prev = l->prev;
            l->prev->next = l->next;
            tmp->next = tmp->prev = nullptr;
            delete tmp;
            return;
        }
        else removeOneItemAux(l->next,t);
    }

    static int removeItemAux(nodo* &l, const T& t){
        if(!l) return 0; //caso base: lista vuota, nessun pattern trovato, ritorno 0
        int z = removeItemAux(l->next,t);  //ricorsione alla fine della lista
        if(l->info == t){
            if(!l->next && !l->prev){
                delete l;
                l = nullptr;
                return z+1;
            }
            nodo* tmp = l;
            if(!l->next && l->prev){
                l->prev->next = nullptr;
                tmp->prev = nullptr;
                delete tmp;
                return z+1;
            }
            if(l->next && !l->prev){
                l->next->prev = nullptr;
                l = l->next;
                tmp->next = nullptr;
                delete tmp;
                return z+1;
            }
            //l->next && l->prev
            l->next->prev = l->prev;
            l->prev->next = l->next;
            tmp->next = tmp->prev = nullptr;
            delete tmp;
            return z+1;
        }
        return z;
    }
//metodo ausialiario di confronto booleano
    static bool compare(nodo* a, nodo* b){
        if(!a && !b) return true;
        if(!a) return false;
        if(!b) return false;
        return a->info == b->info && compare(a->next,b->next);
    }
public:
    Qontainer() : first(nullptr), last(nullptr) {} // default, construisce qontainer vuoto
    Qontainer(int k, const T& t): first(nullptr), last(nullptr){  //construisce un qontainter di k nodi uguali a t
        for(int i=0; i<k; i++) push_back(t);
    }
//Costruttore con lista di inizializzazione
//Esempio d'uso:   Qontainer<int> x = {1,8,3,29,17,36};
    Qontainer(std::initializer_list<T> l) : Qontainer() {
        for (auto i = l.begin(); i < l.end(); i++){
            push_back(*i);
        }
    }
    //GESTIONE MEMORIA PROFONODA
    ~Qontainer(){if(first) delete first;}  // deep destructor
    Qontainer(const Qontainer& l){      // deep copy
        first=copy(l.first,last);
    }
    Qontainer& operator=(const Qontainer& l){
        if(this!=&l){
            if(first) delete first;
            first=copy(l.first,last);
        }
        return *this;
    }

    // MODIFIERS
    void push_back(const T& t){ //aggiunge elemento t in coda
        last = new nodo(t, last, nullptr);
        if(first == nullptr)
            first = last;
        else
            last->prev->next = last;
    }
    void push_front(const T& t){  //aggiunge elemento t in testa
        first = new nodo(t, nullptr, first);
        if(last == nullptr)
            last = first;
        else
            first->next->prev=first;
    }

    void pop_back(){  //rimuove l'elemento in coda (se c'è)
        if(last){
            if(last->prev){
                nodo* tmp = last;
                last = last->prev;
                last->next = nullptr;
                tmp->prev = nullptr;
                delete tmp;
            }
            else{
                delete first;
                first = nullptr;
                last = nullptr;
            }
        }
    }

    void pop_front(){
        if(first){
            if(first->next){
                nodo* tmp = first;
                first = first->next;
                first->prev = nullptr;
                tmp->next = nullptr;
                delete tmp;
            }
            else{
                delete first;
                first = nullptr;
                last = nullptr;
            }
        }
    }

    void insert(int k, const T& t){
//se k è un indice sbagliato, ossia <0 o >size(), è stato scelto di inserire comunque il nuovo nodo rispettivamente
// in testa e in coda al qontainer
        if(k <= 0) {
            push_front(t);
            return;
        }
        if(k >= size()){
            push_back(t);
            return;
        }
        insertAux(first,k,t);
    }
    void remove(int k){
//se k è un indice sbagliato, ossia <0 o >size(), è stato scelto di non rimuovere nessun nodo del qontainer
        if(k<0 || k>=size()) return;

        if(k == 0){
            pop_front();
            return;
        }
        if(k == size()-1){
            pop_back();
            return;
        }
        removeAux(first,k);
    }
    void removeOneItem(const T& t){// rimuove il primo elemento = t
        removeOneItemAux(first,t);
    }
    int removeItem(const T& t){// rimuove tutti elementi = t e restituisce il numero degli elementi rimossi
        return removeItemAux(first,t);
    }

    int search(const T& t){ //ritorna l'indice del primo elemento con info = t, se c'è, altrimenti ritorna -1
        int indice = 0;
        for (Constiterator cit = cbegin(); cit != cend(); cit++){
            if(*cit == t)
                return indice;

            indice++;
        }
        return -1;
    }
// Ritorna l'elemento di indice i.
    T getItem(int i){
        int indice = 0;

        Qontainer<T>::Constiterator cit = cbegin();
        while(indice<i){
            indice++;
            cit++;
        }
        return *cit;
    }

    void append(const Qontainer& q){ //concatenazione
        if(first == nullptr || q.first == nullptr) return;
        last->next = q.first;
        q.first->prev = last;
    }

    void swap(T& t1,T& t2){
        T temp = t1;
        t1 = t2;
        t2 = temp;
    }

    //utilità
    bool empty() const{
        return first == nullptr;
    }
    int size() const{
        int count = 0;
        for(auto cit = cbegin(); cit != cend(); cit++)
            count++;
        return count;
    }

    //OPERATORI

    bool operator==(const Qontainer& q){
        return compare(first,q.first);
    }

    bool operator!=(const Qontainer& q){
        return !compare(first,q.first);
    }

    T& getFirst(){ //Ritorna un riferimento a first
        return first->info;
    }
    T& getLast(){ //Ritorna un riferimento a last
        return last->info;
    }

    class Iterator{
        friend class Qontainer<T>;
    private:
        nodo* ptr;
        bool pastEnd;  // vero se sono dopo end
    public:
        Iterator(): ptr(nullptr), pastEnd(false){}
        Iterator(nodo* p, bool past = false) : ptr(p), pastEnd(past){}
        Iterator& operator++(){ //INCREMENTO PREFISSO
            if(!pastEnd && ptr){
                if(ptr->next)
                    ptr = ptr->next;
                else{
                    ptr = ptr+1;
                    pastEnd = true;
                }
            }
            return *this;
        }
        Iterator& operator--(){ //DECREMENTO PREFISSO
            if(pastEnd){
                ptr = ptr-1;
                pastEnd = false;
            }
            else
                if(ptr)
                    ptr = ptr->prev;
            return *this;
        }
        Iterator operator++(int){ //INCREMENTO POST FISSO
            if(!pastEnd && ptr){
                if(ptr->next)
                    ptr = ptr->next;
                else{
                    ptr = ptr+1;
                    pastEnd = true;
                }
            }
            return *this;
        }
        Iterator operator--(int){ // DECREMENTO POSTFISSO
            if(pastEnd){
                ptr = ptr-1;
                pastEnd = false;
            }
            else
                if(ptr)
                    ptr = ptr->prev;
            return *this;
        }
        T& operator*() const {
            return ptr->info;
        }
        T* operator->() const {
            return &(ptr->info);
        }
        bool operator==(const Iterator& cit) const{
            return cit.ptr == ptr;
        }
        bool operator!=(const Iterator& cit) const {
            return ptr != cit.ptr;
        }
    };

    Iterator begin() const {
        return Iterator(first);
    }

    Iterator end() const {
        if(first == nullptr)
            return Iterator(nullptr);
        return Iterator(last+1,true);
    }

    Iterator min_element(Iterator begin, Iterator end) const{
        Iterator min = begin;
        for(Iterator it = begin; it != end; it++){
            if(**it < **min)
                min = it;
        }
        return min;
    }

    class Constiterator{
        friend class Qontainer<T>;
    private:
        const nodo* ptr;
        bool pastEnd;  // vero se sono dopo end
    public:
        Constiterator(): ptr(nullptr), pastEnd(false){}
        Constiterator(nodo* p, bool past = false) : ptr(p), pastEnd(past){}
        Constiterator& operator++(){ // INCREMENTO PREFISSO
            if(!pastEnd && ptr){
                if(ptr->next)
                    ptr = ptr->next;
                else{
                    ptr = ptr+1;
                    pastEnd = true;
                }
            }
            return *this;
        }
        Constiterator& operator--(){ // DECREMENTO PREFISSO
            if(pastEnd){
                ptr = ptr-1;
                pastEnd = false;
            }
            else
                if(ptr)
                    ptr = ptr->prev;
            return *this;
        }

        Constiterator operator++(int){ // INCREMENTO POSTFISSO
            if(!pastEnd && ptr){
                if(ptr->next)
                    ptr = ptr->next;
                else{
                    ptr = ptr+1;
                    pastEnd = true;
                }
            }
            return *this;
        }
        Constiterator operator--(int){ // DECREMENTO POSTFISSO
            if(pastEnd){
                ptr = ptr-1;
                pastEnd = false;
            }
            else
                if(ptr)
                    ptr = ptr->prev;
            return *this;
        }
        const T& operator*() const {
            return ptr->info;
        }
        const T* operator->() const {
            return &(ptr->info);
        }
        bool operator==(const Constiterator& cit) const{
            return cit.ptr == ptr;
        }
        bool operator!=(const Constiterator& cit) const {
            return ptr != cit.ptr;
        }
    };
    Constiterator cbegin() const {
        return Constiterator(first);
    }

    Constiterator cend() const {
        if(first == nullptr)
            return Constiterator(nullptr);
        return Constiterator(last+1,true);
    }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Qontainer<T>& q) {
    return Qontainer<T>::print(q.first,os);
}

#endif // QONTAINER_H
