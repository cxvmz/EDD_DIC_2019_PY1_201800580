#ifndef LS_H
#define LS_H
template <class T>
class ListaSimple{
    class Nodo{
    public:
        Nodo(T x){
            siguiente = 0;
            dato = x;
        }
        Nodo *getSiguiente(){return siguiente;}
        void setSiguiente(Nodo *n){siguiente=n;}
        T getDato(){return dato;}
    private:
        Nodo *siguiente;
        T dato;
    };
public:
    ListaSimple(){
        primero=0;
        ultimo=0;
        size=0;
    }
    int getSize(){return size;}
    void agregarFinal(T dato);
    void imprimirLD();
private:
    bool estaVacia(){return size==0;}
    int size;
    Nodo *primero;
    Nodo *ultimo;
};

template <class T>
void ListaSimple<T>::agregarFinal(T dato){
    Nodo *n = new Nodo(dato);
    if(this->estaVacia()){
        this->primero=n;
        this->ultimo =n;
        this->size++;
    }
    else
    {
        this->ultimo->setSiguiente(n);
        this->ultimo->n;
        this->size++;
    }
}

#endif // LS_H
