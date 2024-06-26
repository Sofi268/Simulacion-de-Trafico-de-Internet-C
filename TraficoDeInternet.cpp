#include <cstdlib>
#include <iostream>
#include <sstream>
#include <bitset>
#include <ctime>
#include <random>
#define INFI  9000
#define MIEMBRO   1
#define NO_MIEMBRO 0
const int cantidadRouters = 7;
const int cantidadTerminales = 12;
int matrizAdy[cantidadRouters][cantidadRouters];

using namespace std;


//-------------------------------------------Lista Template-------------------------------------------------------
template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo() { next = NULL; };
    Nodo(T a) { dato = a; next = NULL; };
    void set_dato(T a) { dato = a; };
    void setNext(Nodo* n) { next = n; };
    T getDato() { return dato; };
    Nodo* getNext() { return next; };
    bool es_vacio() { return next == NULL; }
};

template <class T> class Lista {
private: Nodo<T>* czo;
       void borrarD(T d, Nodo<T>* ant);
       void borrarDeLista(T d, Nodo<T>* ant);
public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    ~Lista(void){};
    void add(T d); //sumar nodos a la lista
    bool esVacia(void);
    T cabeza(void); //retorna el dato del primer nodo
    Lista* resto(void); //retorna el puntero al "resto" de la lista
    int size();
    void impre(void);
    bool esta(T d);// detecta si d esta en la lista
    void borrarDato(T d) { borrarD(d, NULL); }//borra el nodo que contiene d
    void borrar(void); //borra la cabeza
    void borrarLast();//borra el ultimo
    void concat(Lista<T>* l1);// le transfiere los datos de l1 a this
    void tomar(int n);//deja "vivos" los n primeros nodos y borra el resto
    Lista<T>* copy(void);// hace una copia de la lista
    T last(); //retorna el dato del ultimo nodo
    void addLast(T d);
    void copiar(Lista<T>*);
    void borrarCabezaLista(void);
    void borrarDeL(T d) { borrarDeLista(d,NULL); };
};

template <class T> void Lista<T>::add(T d) 
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->setNext(czo);
    czo = nuevo;
}

template <class T> bool Lista<T>::esVacia(void)
{
    return czo->es_vacio();
}

template <class T> T Lista<T>::cabeza(void)
{
    if (this->esVacia()) {
        throw std::runtime_error("Error: Esta lista vacía, no se puede obtener la cabeza");
    }
    return czo->getDato();
}

template <class T> Lista<T>* Lista<T>::resto(void)
{
    Lista* l = new Lista(czo->getNext());
    return (l);
}

template <class T> int Lista<T>::size()
{
    if (this->esVacia()) return 0;
    return 1 + this->resto()->size();
}

template <class T> void Lista<T>::impre(void)
{
    Nodo<T>* aux;
    aux = czo;
    while (aux->getNext() != NULL) {
        cout << aux->getDato() << endl;
        aux = aux->getNext();
    }
}

template <class T> void Lista<T>::borrar(void)
{ //borra el nodo cabeza
    if (!this->esVacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->getNext();
        delete tmp;
    }
}

template <class T> void Lista<T>::borrarLast()
{ // borra el ultimo nodo
    if (!this->esVacia()) {
        if ((czo->getNext())->getNext() == NULL) {
            delete czo->getNext();
            czo->setNext(NULL);
        }
        else this->resto()->borrarLast();
    }
}

template <class T> void Lista<T>::concat(Lista<T>* l1)
{// le transfiere los datos de l1 a this
    if (!(l1->esVacia())) {
        this->concat(l1->resto());
        T a = l1->cabeza();
        this->add(a);
    }
}

template <class T> void Lista<T>::tomar(int n)
{ //deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n) {
        this->borrarLast();
        this->tomar(n);
    }
}

template <class T> Lista<T>* Lista<T>::copy(void)
{
    Lista<T>* aux = new Lista();
    aux->concat(this);
    return aux;
}

template <class T> bool Lista<T>::esta(T d)
{// busca d en la lista
    if (this->esVacia()) return false;
    if (this->cabeza() == d) return true;
    
    return this->resto()->esta(d);    
}

template <class T> void Lista<T>::borrarD(T d, Nodo<T>* ant)
{
    if (!this->esVacia()) {
        if (d == this->cabeza()) {
            if (ant == NULL) {//al principio
                this->borrar();
            }
            else {//entre medio
                ant->setNext(czo->getNext());
                delete czo;
            }
        }
        else  this->resto()->borrarD(d, czo);

    }
}


template <class T> void Lista<T>::borrarCabezaLista(void)
{ 
    if (!this->esVacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->getNext();
    }
}
template <class T> void Lista<T>::borrarDeLista(T d, Nodo<T>* ant)
{
    if (!this->esVacia()) {
        if (d == this->cabeza()) {
            if (ant == NULL) {//al principio
                this->borrarCabezaLista();
            }
            else {//entre medio
                ant->setNext(czo->getNext());
            }
        }
        else  this->resto()->borrarD(d, czo);

    }
}

template <class T> T Lista<T>::last()
{
    if (!this->esVacia()) {
        if (this->resto()->esVacia())return this->cabeza();
        return this->resto()->last();
    } 
    else{
        return NULL;
    }
}

template <class T> void Lista<T>::addLast(T d)
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    if (this->esVacia()) {
        czo->setNext(nuevo); 
    } else {
        Nodo<T>* aux = czo; 
        while (aux->getNext() != NULL) {
            aux = aux->getNext();
        }
        aux->setNext(nuevo); 
    }
}

template<class T> void Lista<T>::copiar(Lista<T>* listaACopiar)
{
    T dato = listaACopiar->cabeza();
    this->addLast(dato);
    if(listaACopiar->resto()->esVacia()) {
        T dato = listaACopiar->cabeza();
        this->addLast(dato);
        return;
    }
    copiar(listaACopiar->resto());
}

//------------------------------------------------- Cola Template-------------------------------------------------

template <class T> class Cola :public Lista<T> {
private:
    int numRouter;
    int idAnterior; //Pagina a la que pertenece el ultimo elemento de la cola
    int elemEnCola; //Cantidad de elementos que tiene la cola
    int anchoBanda;
public:
    Cola(void) { Lista<T>(); };
    Cola(int numRout, int idAnt, int elemEnCola, int anchoBanda);
    ~Cola(void){};

    //Getters
    int getNumRout(void){return numRouter;};
    int getIdAnt(void){return idAnterior;};
    int getOrdenPagina(void){return elemEnCola;};
    int getAnchoDeBanda(void){return anchoBanda;};

    //Setters
    void setAnchoBanda(int aB){anchoBanda = aB;};
    void setCantiPaqMas(void){elemEnCola++;};
    void setCantiPaqMenos(void){elemEnCola--;};

    T tope(void) { return this->last(); };
    bool colavacia(void) { return this->esVacia(); };
    void encolar(T a) { this->add(a); };
    void desencolar(void) { this->borrarLast(); };
    T ultimo(void) { return this->cabeza(); };
};

template <class T> Cola<T>::Cola(int numRout, int idAnt, int numOrdenCola, int anchoBanda)
{
    numRouter = numRout;
    idAnterior = idAnt;
    elemEnCola = numOrdenCola;
}

//----------------------------------------Pagina----------------------------------------------------------------

class Pagina {
private:
    int maqOrigen;
    int maqGnralOrigen;
    int routOrigen;
    int maqFinal;
    int maqGnralFinal;
    int routFinal;
    int tamanioPagina;
    int numeroPagina;
    bitset<16> IPorigen;
    bitset<16> IPdestino;

public:
    Pagina(void){};
    Pagina(int maquinaOrigen, int routerOrigen, int maquinaFinal, int routFinal, int tamanio, int pagina, bitset<16> IpO, bitset<16> IpD,int numMaqGnralO, int numMaqGnralD);
    ~Pagina(void){};

    //Getters
    int getNumMaqOrigen(void){return maqOrigen;};
    int getNumMaqGnralOrigen(void){return maqGnralOrigen;};
    int getRoutOrigen(){return routOrigen;};
    int getNumMaqFinal(void){return maqFinal;};
    int getNumMaqGnralFinal(void){return maqGnralFinal;};
    int getRoutFinal(void){return routFinal;}
    int getTamanoPagina(void){return tamanioPagina;};
    int getNumeroPagina(void){return numeroPagina;};
    bitset<16> getIPorigen(void){return IPorigen;};
    bitset<16> getIPdestino(void){return IPdestino;};

    void imprimirPagina();
};

Pagina::Pagina(int maquinaOrigen, int routerOrigen, int maquinaFinal, int routerFinal,  int tamanio, int pagina, bitset<16> IpO, bitset<16> IpD, int numMaqGnralO, int numMaqGnralD)
{   
    maqOrigen = maquinaOrigen;
    maqGnralOrigen = numMaqGnralO;
    routOrigen = routerOrigen;
    maqFinal = maquinaFinal;
    maqGnralFinal = numMaqGnralD;
    routFinal = routerFinal;
    tamanioPagina = tamanio;
    numeroPagina = pagina;
    IPorigen = IpO;
    IPdestino = IpD;
}

void Pagina::imprimirPagina()
{
    cout<<"Pagina numero "<<numeroPagina<<endl;
    cout<<"Maquina Origen: "<<maqGnralOrigen<<endl;
    cout<<"Router Origen: "<<routOrigen<<endl;
    cout<<"Maquina Destino: "<<maqGnralFinal<<endl;
    cout<<"Router Destino: "<<routFinal<<endl;
    cout<<"Tamanio de la pagina: "<<tamanioPagina<<endl;
    cout<<"Direccion de Origen: "<<IPorigen<<endl;
    cout<<"Direccion de Destino: "<<IPdestino<<endl;
}

//-----------------------------------------------Paquete--------------------------------------------------

class Paquete {
private:
    int maqOrigen, routOrigen, maqFinal, routFinal, routActual, tamanioPag, numeroPagina, numeroOrdenPagina, numeroOrdenCola, numMaqGnralO, numMaqGnralD;
    Lista<int>* camino;
    bitset<16> IPorigen;
    bitset<16> IPdestino;

public:
    Paquete(void){};
    Paquete(int maquinaOrigen, int routerOrigen, int maquinaFinal, int routerFinal, int tamanioPagina, int numPagina, int numOrdenPagina, bitset<16> IPorig, bitset<16> IPdest, int numMaqGnralO, int numMaqGnralD);
    ~Paquete(void){};

    //Getters
    int getMaquinaOrigen(void){ return maqOrigen;};
    int getMaquinaGnralOrigen(void){ return numMaqGnralO;};
    int getRouterOrigen(void){return routOrigen;};
    int getMaquinaFinal(void){return maqFinal;};
    int getMaquinaGnralFinal(void){ return numMaqGnralD;};
    int getRouterFinal(void){return routFinal;};
    int getRoutActual(void){return routActual;};
    int getCantiTotalPaq(void){return tamanioPag;};
    int getNumPag(void){return numeroPagina;};
    int getOrdenPagina(void){return numeroOrdenPagina;};
    int getOrdenCola(void){return numeroOrdenCola;};
    bitset <16> getIPorigen(void){return IPorigen;};
    bitset <16> getIPdestino(void){return IPdestino;};
    Lista<int>* getCamino(void){return camino;};
    int getSigRouter(void){return camino->cabeza();};

    //Setters
    void setMaqTermi(int maqFi){ maqFinal = maqFi;};
    void setNuevoCamino(Lista<int>* nuevoCam){camino = nuevoCam;};
    void setRoutActual(int routerAct){routActual = routerAct;};
    void setOrdenCola(int nuevoNum){numeroOrdenCola = nuevoNum;};

    //Borra el primer elemento del camino
    void borrarElemCamino(void);

};

Paquete::Paquete(int maquinaOrigen, int routerOrigen, int maquinaFinal, int routerFinal, int tamanioPagina, int numPagina, int numOrdenPagina, bitset<16> IPorig, bitset<16> IPdest, int numMaqGnralO, int numMaqGnralD)
{
    maqOrigen = maquinaOrigen;
    routOrigen = routerOrigen;
    maqFinal = maquinaFinal;
    routFinal = routerFinal;
    routActual = routerOrigen;
    tamanioPag = tamanioPagina;
    numeroPagina = numPagina;
    numeroOrdenPagina = numOrdenPagina;
    numeroOrdenCola = 0;
    IPorigen = IPorig;
    IPdestino = IPdest;
    camino = new Lista<int>();
}

void Paquete::borrarElemCamino(void)
{   
    int elementoABorrar = camino->cabeza();
    camino->borrarDeL(elementoABorrar);
}

//---------------------------------------------------------Terminal--------------------------------------------------------------
template <class T> class Terminal  {
private:
    int numTerminal;
    int numRouter;
    T routerAsociado;
    bitset <16> direccionMaquina;
    Pagina* paginaEnviar;
    Lista<Pagina*>* paginasRecibidas;
    int numMaqGnral;


public:
    Terminal(void){};
    Terminal(int numeroMaquina, int numeroRouter, T router, int numMaqGeneral);

    //Getters
    int getNumeroTerminal(void){return numTerminal;};
    int getNumeroRouter(void){return numRouter;};
    T getRouterAsociado(void){return routerAsociado;};
    bitset<16> getDirecMaquina(void){return direccionMaquina;};
    int getNumMaqGeneral(void){return numMaqGnral;}

    bitset<16> setDireccion(int maq,  int rout);

    Pagina* generarPaginaAleatoria(Lista<T>* rout,int cantidadRout, int numPag, int numTerminalFinal, int numRoutFinal,int numMaqGnralFinal, int tamanio);
    void enviarPagina(Lista<T>* rout,int cantidadRout, int numPag, int numMaqFinal, int numRoutFinal, int numMaqGnralFinal, int tamanio);
    void recibirPagina(Pagina* pag);
    void imprimirRecepcion(Pagina* pag);
};

template <class T> Terminal<T>::Terminal(int numeroMaquina, int numeroRouter, T router, int numMaqGeneral)
{
    numTerminal = numeroMaquina;
    numRouter = numeroRouter;
    routerAsociado = router;
    direccionMaquina = setDireccion(numeroMaquina, numeroRouter);
    paginasRecibidas = new Lista<Pagina*>;
    numMaqGnral = numMaqGeneral;
}

template<class T> bitset<16> Terminal<T>::setDireccion(int maq, int rout)
{
    bitset<16> a (maq);
    bitset<16> b (rout);
    (a<<=8);
    bitset<16> direcMaquina = (a|b);
    return direcMaquina;
}

//Generar Pagina a enviar

template <class T> Pagina* Terminal<T>::generarPaginaAleatoria(Lista<T>* rout,int cantidadRout, int numPag, int numeroTerminalFinal, int numeroRoutFinal,int numMaqGnralFinal, int tamanio)
{   
    int tamanioPag = tamanio;
    int numTerminalFinal = numeroTerminalFinal;
    int numRoutFinal = numeroRoutFinal;
    int routOrigen = numRouter;
    bitset<16> IPdest = setDireccion(numTerminalFinal, numRoutFinal);
    Pagina* nueva = new Pagina(numTerminal, routOrigen, numTerminalFinal,numRoutFinal, tamanioPag, numPag, direccionMaquina, IPdest, numMaqGnral, numMaqGnralFinal);
    return nueva;
}

//Crear la pagina y luego enviarla al router asociado
template<class T> void Terminal<T>::enviarPagina(Lista<T>* rout,int cantidadRout, int numPag, int numMaqFinal, int numRoutFinal,int numMaqGnralD, int tamanio)
{
    paginaEnviar = generarPaginaAleatoria(rout, cantidadRout, numPag, numMaqFinal, numRoutFinal,numMaqGnralD, tamanio);
    routerAsociado->recibirPagina(paginaEnviar);
}

//Recibir pagina enviada
template<class T> void Terminal<T>::recibirPagina(Pagina* pag)
{
    paginasRecibidas->add(pag);
    imprimirRecepcion(pag);
}

template<class T> void Terminal<T>::imprimirRecepcion(Pagina* pag)
{
    cout<<endl<<endl;
    cout<<"La maquina "<<numTerminal<<" recibio exitosamente la pagina numero: "<<pag->getNumeroPagina()<<endl;
    cout<<"Direccion de envio: "<<pag->getIPorigen()<<endl;
    cout<<"Direccion de destino: "<<pag->getIPdestino()<<endl;
    cout<<endl<<endl;
}

//----------------------------------------------------------Router-------------------------------------------------------
class Router{
private:
    int ID;
    int anchoBanda;
    int cantidadVecinos;
    int cantidadTerminales;
    Lista<Router*>* vecinos;
    Lista<Terminal<Router*>*>* terminales;
    Lista<Cola<Paquete*>*>* colasTrafico;
    Lista<Cola<Paquete*>*>* colasEspera;
    Lista<Lista<Lista<Paquete*>*>*>* listasTerminales;
    Lista<int>* veciConEspera;
    Lista<int>* veciConColaTrafico;
    Lista<int>* numVecinos;
    Lista<int>* terminalesConLista;
    Lista<Paquete*>* listaAEnviar;
    Lista<Paquete*>* listaConCaminos;
    Lista<Paquete*>* paquetes;

public:
    Router(void){};
    Router(int id, Lista<Paquete*>* paqs);
    ~Router(void){};

    //Gettters
    int getID(void){return ID;};
    int getAnchoBanda(void){return anchoBanda;};
    int getCantidadVecinos(void){return cantidadVecinos;};
    int getCantidadTerminales(void){return cantidadTerminales;};
    Lista<Router*>* getVecinos(void){return vecinos;};
    Lista<Terminal<Router*>*>* getTerminales(void){return terminales;};
    Lista<Cola<Paquete*>*>* getColasEspera(void){return colasEspera;};
    Lista<Cola<Paquete*>*>* getColasTrafico(void){return colasTrafico;};
    Lista<Lista<Lista<Paquete*>*>*>* getListasTerminales(void){return listasTerminales;};
    Lista<int>* getNumVecinos(void){return numVecinos;};
    Lista<Paquete*>* getListaAEnviar(void){return listaAEnviar;};

    //Setters
    void setAnchoBanda(int anchBandavoid);
    void setNuevoVecino(Router* vecino);
    void setNuevaTerminal(Terminal<Router*>* terminal);
    void setListaConCaminos(Lista<Paquete*>* listaCaminos){ listaConCaminos = listaCaminos;};

    //Busqueda
    static Router* buscarRouter(int ID,Lista<Router*>* vecinos);
    static Terminal<Router*>* buscarTerminal(int ID, Lista<Terminal<Router*>*>* terminales);
    Lista<Paquete*>* buscarLista(int ID, Lista<Lista<Lista<Paquete*>*>*>* listasTerminales, int numeroPag);
    Lista<Lista<Paquete*>*>* buscarTerm(int IDTerminal, Lista<Lista<Lista<Paquete*>*>*>* terminales);
    Cola<Paquete*>* buscarCola(int ID, Lista<Cola<Paquete*>*>* colas);
    Lista<Paquete*>* buscarListaPagina(Lista<Lista<Paquete*>*>* listaTerm, int numPag);
    

    //Recibir Pagina y crear Paquetes
    void recibirPagina(Pagina* pagina);
    void armadoDePaquetes(Pagina* pagina);
    void enviarDirecto(Paquete* paquete);

    //Reconstruccion y envio de pagina
    void recibirPaqueteFinal(Paquete* paquete);
    void reconstruirPagina(Lista<Paquete*>* lista);
    void recibirListaConCaminos(Lista<Paquete*>* lista);
    void enviarPagina(Pagina* pagina);
    Paquete* buscarElemMenor(Lista<Paquete*>* listaTerminal);
    void listaOrdenada(Lista<Paquete*>* listaTerminal, Lista<Paquete*>* listaOrdenada);

    //Recepcion de Paquetes y reenvio
    void recibirPaquete(Paquete* paquete); 
    void recibirPaqueteVecino(Paquete* paquete);
    void ciclo();
    bool pertenece(int numPag, int router);
    void enviarPaqueteVecino(Paquete* paquete);
    bool veciTieneEspera(int ID);
    bool veciTieneTrafico(int ID);

    //Extra
    void vaciarLista(Lista<Paquete*>* listaABorrar);
    void vaciarListaAEnviar(void);
    void imprimirRecepcion(Paquete* paquete, bool final);
    int turno(int ID);
    void borrarPaquete(Paquete* paq);
    void agregarPaquete(Paquete* paq);
    void imprimirVecinos(Lista<Router*>* vecis);
};

Router::Router(int id, Lista<Paquete*>* paqs)
{
    ID = id;
    cantidadVecinos = 0;
    cantidadTerminales = 0;
    vecinos = new Lista<Router*>();
    terminales = new Lista<Terminal<Router*>*>();
    colasTrafico = new Lista<Cola<Paquete*>*>();
    colasEspera = new Lista<Cola<Paquete*>*>();
    veciConColaTrafico = new Lista<int>();
    veciConEspera = new Lista<int>();
    listasTerminales = new Lista<Lista<Lista<Paquete*>*>*>();
    numVecinos = new Lista<int>();
    terminalesConLista = new Lista<int>();
    listaAEnviar = new Lista<Paquete*>();
    listaConCaminos = new Lista<Paquete*>();
    paquetes = paqs;
}

void Router::imprimirVecinos(Lista<Router*>* vecis)
{
    if(vecis->esVacia()) return;
    else{
        cout<<"Router vecino: "<<vecis->cabeza()->getID()<<endl;
        imprimirVecinos(vecis->resto());
    }
    
}
void Router::setAnchoBanda(int anchBanda)
{
    anchoBanda = anchBanda;
}

void Router::setNuevoVecino(Router* vecino)
{
    vecinos->add(vecino);
    numVecinos->add(vecino->getID());
    cantidadVecinos++;
}

void Router::setNuevaTerminal(Terminal<Router*>* terminal)
{
    terminales->add(terminal);
    cantidadTerminales++;
}

Router* Router::buscarRouter(int IDRout, Lista<Router*>* vecinos)
{   
    if(vecinos->esVacia()) return nullptr;
    if(vecinos->cabeza()->getID() == IDRout){
        return vecinos->cabeza();
    }
    if(vecinos->esVacia()) return nullptr;
    else return buscarRouter(IDRout, vecinos->resto());
}

Terminal<Router*>* Router::buscarTerminal(int IDTerminal, Lista<Terminal<Router*>*>* terminales)
{
    if(terminales->esVacia()) return nullptr;
    if(terminales->cabeza()->getNumeroTerminal() == IDTerminal){
        return terminales->cabeza();
    }
    else return buscarTerminal(IDTerminal, terminales->resto());
}

//Busca las listas de una Terminal
Lista<Lista<Paquete*>*>* Router::buscarTerm(int IDTerminal, Lista<Lista<Lista<Paquete*>*>*>* terminales)
{
    Lista<Lista<Paquete*>*>* listaTermi = terminales->cabeza();
    int numeroDeLaTerm = listaTermi->cabeza()->cabeza()->getMaquinaFinal();
    if(numeroDeLaTerm== IDTerminal)return listaTermi;
    else return buscarTerm(IDTerminal, terminales->resto());
}

Lista<Paquete*>* Router::buscarListaPagina(Lista<Lista<Paquete*>*>* listaTerm, int numPag)
{
    if(listaTerm->esVacia()) return nullptr;
    Lista<Paquete*>* listaPag = listaTerm->cabeza();
    int numeroDeLaPag = listaPag->cabeza()->getNumPag();
    if(numeroDeLaPag == numPag) return listaPag;
    else return buscarListaPagina(listaTerm->resto(), numPag);
}

//Busca la lista de paquetes de una pagina
Lista<Paquete*>* Router::buscarLista(int IDTerminal, Lista<Lista<Lista<Paquete*>*>*>* listasTerminales, int numeroPagina)
{
    //Caso en que la terminal tiene listas de paginas incompletas
    if(terminalesConLista->esta(IDTerminal)){
        Lista<Lista<Paquete*>*>* listaTerm = buscarTerm(IDTerminal, listasTerminales);
        Lista<Paquete*>* listaDePag = buscarListaPagina(listaTerm, numeroPagina);
        if(listaDePag!=nullptr){
            return listaDePag;
        }
        else{
            Lista<Paquete*>* listaPagina = new Lista<Paquete*>();
            listaTerm->add(listaPagina);
            return listaPagina;
        }
    }

    //Caso en que todavia la terminal no tiene lista de paginas incompletas
    else{
        Lista<Lista<Paquete*>*>* listaTermi = new Lista<Lista<Paquete*>*>();
        Lista<Paquete*>* listaPagina = new Lista<Paquete*>();
        listaTermi->add(listaPagina);
        listasTerminales->add(listaTermi);
        terminalesConLista->add(IDTerminal);
        return listaPagina;
    }
}

Cola<Paquete*>* Router::buscarCola(int IDRout, Lista<Cola<Paquete*>*>* colas)
{
    if(colas->esVacia()) return nullptr;
    Cola<Paquete*>* colaBuscada = colas->cabeza();
    if(colaBuscada->getNumRout() == IDRout) return colaBuscada;
    else return buscarCola(IDRout, colas->resto());
}

void Router::recibirPagina(Pagina* pagina)
{
    cout<<"Router numero: "<<getID()<<endl;
    cout<<"Recepcion de la Pagina: "<<endl;
    pagina->imprimirPagina();
    armadoDePaquetes(pagina);
}

void Router::armadoDePaquetes(Pagina* pagina)
{
    int cantidadPaquetes = pagina->getTamanoPagina();
    cout<<"Cantidad de paquetes a armar: "<<cantidadPaquetes<<endl;
    for(int i= 0; i<cantidadPaquetes; i++){
        Paquete* paquete = new Paquete(pagina->getNumMaqOrigen(), ID, pagina->getNumMaqFinal(), pagina->getRoutFinal(), pagina->getTamanoPagina(), pagina->getNumeroPagina(), i+1, pagina->getIPorigen(),pagina->getIPdestino(), pagina->getNumMaqGnralOrigen(), pagina->getNumMaqGnralFinal());
        listaAEnviar->add(paquete);
    }
}

void Router::recibirListaConCaminos(Lista<Paquete*>* listaCaminos)
{
    setListaConCaminos(listaCaminos);
    Lista<Paquete*>* listaAux = listaConCaminos;
    int tamLista = listaConCaminos->size();
    for(int i = 0; i<tamLista; i++){
        Paquete* paquete = listaAux->cabeza();
        paquetes->add(paquete);
        enviarDirecto(paquete);
        if(listaAux->resto()->esVacia())break;
        listaAux = listaAux->resto();
        
    }
    vaciarLista(listaConCaminos);
}

void Router::enviarDirecto(Paquete* paquete)
{
    int sigRouter = paquete->getSigRouter();
    Router* routVeci = buscarRouter(sigRouter, vecinos);
    routVeci->recibirPaquete(paquete);
}

void Router::reconstruirPagina(Lista<Paquete*>* listaOrdenada)
{
    Paquete* paqAux = listaOrdenada->cabeza();
    Pagina* pagina = new Pagina(paqAux->getMaquinaOrigen(), paqAux->getRouterOrigen(), paqAux->getMaquinaFinal(),paqAux->getRouterFinal(),paqAux->getCantiTotalPaq(),paqAux->getNumPag(),paqAux->getIPorigen(), paqAux->getIPdestino(), paqAux->getMaquinaGnralOrigen(), paqAux->getMaquinaGnralFinal());
    enviarPagina(pagina);
}

void Router::enviarPagina(Pagina* pagina)
{
    int maqDestino = pagina->getNumMaqFinal();
    Terminal<Router*>* terminalDestino = buscarTerminal(maqDestino, terminales);
    terminalDestino->recibirPagina(pagina);
}

void Router::recibirPaquete(Paquete* paquete)
{
    if(paquete->getRouterFinal()==ID){
        recibirPaqueteFinal(paquete);
    }
    else recibirPaqueteVecino(paquete);
}

void Router::recibirPaqueteFinal(Paquete* paquete)
{
    borrarPaquete(paquete);
    int maqTerminal = paquete->getMaquinaFinal();
    int cantiTotalPaquetes = paquete->getCantiTotalPaq();
    int numPagina = paquete->getNumPag();
    Lista<Paquete*>* listaMaquina = buscarLista(maqTerminal, listasTerminales, numPagina);
    listaMaquina->add(paquete);

    if(listaMaquina->size()==cantiTotalPaquetes){
        Lista<Paquete*>* listaOrd = new Lista<Paquete*>();
        listaOrdenada(listaMaquina,listaOrd);
        Lista<Lista<Paquete*>*>* listaDeLaTerminal = buscarTerm(maqTerminal, listasTerminales);
        listaDeLaTerminal->borrarDato(listaMaquina);
        if(listaDeLaTerminal->esVacia()){
            listasTerminales->borrarDato(listaDeLaTerminal);
            terminalesConLista->borrarDato(maqTerminal);
        }
        reconstruirPagina(listaOrd);
    }
}

Paquete* Router::buscarElemMenor(Lista<Paquete*>* listaTerminal)
{
    Lista<Paquete*>* listaAux = listaTerminal;
    
    if (listaTerminal->esVacia()) {
        cout<<"La lista ya no tiene elementos"<<endl;
        return nullptr;
    }

    Paquete* paqueteMenor = listaAux->cabeza();
    while (listaAux->size()>1) {
        Paquete* paqueteActual = listaAux->resto()->cabeza();
        if (paqueteActual->getOrdenPagina() < paqueteMenor->getOrdenPagina()) {
            paqueteMenor = paqueteActual;
        }
        listaAux = listaAux->resto();
    }
    return paqueteMenor;
}

void Router::listaOrdenada(Lista<Paquete*>* listaTerminal, Lista<Paquete*>* listaOrdenada)
{
    while (!listaTerminal->esVacia()) {
        Paquete* paquete = new Paquete();
        paquete = buscarElemMenor(listaTerminal);
        listaOrdenada->add(paquete);
        listaTerminal->borrarDeL(paquete);
    }
    Paquete* paquete = new Paquete();
    int numMaq = listaOrdenada->cabeza()->getMaquinaFinal();
    paquete->setMaqTermi(numMaq);
    listaTerminal->add(paquete);
    return;
}

void Router::recibirPaqueteVecino(Paquete* paquete)
{
    paquete->borrarElemCamino();
    int siguienteRout = paquete->getSigRouter();
    if(veciTieneEspera(siguienteRout)){//Si existe una cola de espera para el trafico del router
        if(pertenece(paquete->getNumPag(), siguienteRout)){//Si pertenece a esa cola de espera
            Cola<Paquete*>* colaEsp= buscarCola(siguienteRout, colasEspera);//Se añade
            colaEsp->encolar(paquete);
            colaEsp->setCantiPaqMas();
            cout<<"Paquete: "<<paquete->getOrdenPagina()<<"de la pagina: "<<paquete->getNumPag()<<" en cola de Router: "<<ID<<endl;
        }

        else{
            Cola<Paquete*>* colaTraf = buscarCola(siguienteRout, colasTrafico);
            colaTraf->encolar(paquete);
            colaTraf->setCantiPaqMas();
            Paquete* paq = buscarCola(siguienteRout, colasEspera)->tope(); 
            colaTraf->encolar(paq); //Se encola tambien un paquete de la cola de espera
            cout<<"Paquete: "<<paquete->getOrdenPagina()<<"de la pagina: "<<paquete->getNumPag()<<" en cola de Router: "<<ID<<endl;
            colaTraf->setCantiPaqMas();
            Cola<Paquete*>* colaEspe = buscarCola(siguienteRout, colasEspera); //Se desencola de la lista de espera
            colaEspe->desencolar();
            colaEspe->setCantiPaqMenos();
            if(colaEspe->esVacia()){
                int numRouter = colaEspe->getNumRout();
                colasEspera->borrarDato(colaEspe);
                veciConEspera->borrarDato(numRouter);
            }
        }
    }

    else{
        if(veciTieneTrafico(siguienteRout)){
            int ant = buscarCola(siguienteRout, colasTrafico)->getIdAnt();

            if(paquete->getNumPag()==ant){
                int anchoBanda = buscarRouter(siguienteRout, vecinos)->getAnchoBanda();
                Cola<Paquete*>* colaEspera = new Cola<Paquete*>(siguienteRout,paquete->getNumPag(),1,anchoBanda);
                colaEspera->encolar(paquete);
                cout<<"Paquete: "<<paquete->getOrdenPagina()<<"de la pagina: "<<paquete->getNumPag()<<" en cola de Router: "<<ID<<endl;
                colaEspera->setCantiPaqMas();
                colasEspera->add(colaEspera);
                veciConEspera->add(siguienteRout);
            }
            else{
                Cola<Paquete*>* colaTraf = buscarCola(siguienteRout, colasTrafico);
                colaTraf->encolar(paquete);
                cout<<"Paquete: "<<paquete->getOrdenPagina()<<"de la pagina: "<<paquete->getNumPag()<<" en cola de Router: "<<ID<<endl;
                colaTraf->setCantiPaqMas();
            }
        }
        else{
            int anchoDeBanda = buscarRouter(siguienteRout,vecinos)->getAnchoBanda();
            Cola<Paquete*>* colaTrafico = new Cola<Paquete*>(siguienteRout,paquete->getNumPag(),1, anchoDeBanda);
            colaTrafico->encolar(paquete);
            cout<<"Paquete: "<<paquete->getOrdenPagina()<<"de la pagina: "<<paquete->getNumPag()<<" en cola de Router: "<<ID<<endl;
            colaTrafico->setCantiPaqMas();
            colasTrafico->add(colaTrafico);
            veciConColaTrafico->add(siguienteRout);
        }
    }
}

void Router::ciclo()
{   
    Cola<Paquete*>* colaAux= new Cola<Paquete*>();
    Lista<Cola<Paquete*>*>* listaColasAux = colasTrafico;
    if(veciConColaTrafico->size()==0)return; //No tiene colas de Trafico

    //Recorre la Lista
    for(int i = 0; i< colasTrafico->size(); i++){
        cout<<endl;
        if(colaAux->esVacia())break;
        colaAux = listaColasAux->cabeza();
        //Recorre la cola
        int anchoB = colaAux->getAnchoDeBanda();
        for(int j = 0; j<anchoB; j++){
            Paquete* paquete = colaAux->tope();
            enviarPaqueteVecino(paquete);
            colaAux->desencolar();
            colaAux->setCantiPaqMenos();

            //Caso en que quede vacia la cola de Espera
            if(colaAux->esVacia()){
                int numRout = colaAux->getNumRout();
                colasTrafico->borrarDato(colaAux);
                veciConColaTrafico->borrarDato(numRout);
                break;
            }
        }
        listaColasAux = listaColasAux->resto();
    }
}

bool Router::pertenece(int numPag, int router)
{
    int ant = buscarCola(router, colasEspera)->getIdAnt();
    if(ant == numPag) return true;
    else return false;
}

bool Router::veciTieneEspera(int ID)
{
    if(veciConEspera->esta(ID)){
        return true;
    }
    else return false;
}

bool Router::veciTieneTrafico(int ID)
{
    if(veciConColaTrafico->esta(ID)){
        return true;
    }
    else return false;
}

void Router::enviarPaqueteVecino(Paquete* paquete)
{
    int routDestino = paquete->getSigRouter();
    Router* routDest = buscarRouter(routDestino, vecinos);
    routDest->recibirPaquete(paquete);
}

void Router::imprimirRecepcion(Paquete* paquete, bool final){
    cout<<endl<<endl;
    cout<<"Se recibio paquete de pagina numero: "<<paquete->getOrdenPagina()<<endl;
    cout<<"De la pagina numero: "<<paquete->getNumPag()<<endl;
    if(final)cout<<"Final: si"<<endl;
    else cout<<"Final: no"<<endl;
    cout<<"Router receptor: "<<ID<<endl;
    cout<<"Emitido por maquina con direccion: "<<paquete->getIPorigen()<<endl;
    cout<<"Con destino maquina con direccion: "<<paquete->getIPdestino()<<endl;
}

int Router::turno(int ID)
{
    if(!veciConColaTrafico->esta(ID)) return 2;
    else{
        Cola<Paquete*>* colaVecino = buscarCola(ID, colasTrafico);
        Router* routVecino = buscarRouter(ID, vecinos);
        int anchoDeBandaCola = routVecino->getAnchoBanda();

        colaVecino->setAnchoBanda(anchoDeBandaCola);
        int anchoBanda = colaVecino->getAnchoDeBanda();
        int elemEnCola = colaVecino->getOrdenPagina();
        int ciclosEspera = 0;
        elemEnCola = elemEnCola - anchoBanda;
        int a = 5;
        while(elemEnCola>anchoBanda){
            cout<<"El ancho de Banda es: "<<anchoBanda<<endl;
            cout<<"La cantidad de elementos de la cola es: "<<elemEnCola<<endl;
            ciclosEspera++;
            elemEnCola = elemEnCola - anchoBanda;
        }
        return ciclosEspera + 2;
    }
}

void Router::borrarPaquete(Paquete* paq)
{
    paquetes->borrarDeL(paq);
}

void Router::agregarPaquete(Paquete* paq)
{
    paquetes->add(paq);
}

void Router::vaciarListaAEnviar(void)
{
    vaciarLista(listaAEnviar);
}

void Router::vaciarLista(Lista<Paquete*>* listaABorrar)
{
    while(!listaABorrar->esVacia()){
        listaABorrar->borrarCabezaLista();
    }
}

//----------------------------------------------------------Extra------------------------------------------------------------
Router* buscarRouter(int numRout, Lista<Router*>* routers) 
{
    if(routers->esVacia()) return nullptr; 
    if(routers->cabeza()->getID() == numRout){
        return routers->cabeza();
    }
    else return buscarRouter(numRout, routers->resto());
}

Terminal<Router*>* buscarTerminal(int numTerminal, Lista<Terminal<Router*>*>* terminales)
{
    if (terminales->esVacia()) return nullptr;
    if (terminales->cabeza()->getNumMaqGeneral() == numTerminal) {
        return terminales->cabeza();
    } 
    else return buscarTerminal(numTerminal, terminales->resto());
}

void imprimirMatriz(void)
{
    for(int i = 0; i<cantidadRouters; i++){
            for(int j = 0; j<cantidadRouters; j++){
                cout<<matrizAdy[i][j]<<" ";
            }
            cout<<"\n";
        }
}

//----------------------------------------------------------Camino---------------------------------------
class Camino {
private:
    int matriz[cantidadRouters][cantidadRouters];
    Lista<Router*>* routers;
    Paquete* paquete;
    int routOrigen;
    int routFinal;
    Lista<int>* cam = new Lista<int>();
    

public:
    Camino(){};
    Camino(int matrizAdy[cantidadRouters][cantidadRouters], Lista<Router*>* routs);
    ~Camino(void){};

    Lista<int>* getCamino(void){return cam;};

    void setNuevoPaquete(Paquete* paq);
    void copiarMatriz(int matrizAdy[cantidadRouters][cantidadRouters]);
    void actualizarMatriz(void);
    int *dijkstra(int C[][cantidadRouters],int s, int t, int P[]);
    void camino(int P[], int s, int t);
    void guardarCamino(int t);
    void setCamino(void);
    void resetCamino(void);
    void imprimirMatrizAdy(void);
    bool hayCamino(int routO, int routD);
};

Camino::Camino(int matrizAdy[cantidadRouters][cantidadRouters], Lista<Router*>* routs)
{
    copiarMatriz(matrizAdy);
    routers = routs;
}

void Camino::copiarMatriz(int matrizAdy[cantidadRouters][cantidadRouters])
{
    for(int i =0; i<cantidadRouters; i++){
        for(int j = 0; j<cantidadRouters; j++){
            matriz[i][j] = matrizAdy[i][j];
        }
    }
}

void Camino::setNuevoPaquete(Paquete* paq)
{
    paquete = paq;
    routFinal = paquete->getRouterFinal();

    //Primera vez que se setea el camino
    if(paquete->getCamino()->esVacia()){
        routOrigen = paquete->getRouterOrigen();
        setCamino();
    }

    //Ya hay un camino y hay que modificarlo
    else{
        routOrigen = paquete->getSigRouter();

        if(routOrigen!=routFinal){
            setCamino();
        }
        else return; //Si el siguiente Router del camino es su destino, no se modifica el camino
    }
}

void Camino::actualizarMatriz(void)
{
    for(int i = 0; i<cantidadRouters; i++){ //i es el Router de Origen
        Router* routAux = buscarRouter(i, routers);
        //routAux->imprimirVecinos(routAux->getVecinos());
        for(int j = 0; j<cantidadRouters; j++){ //j es el Router Destino
            if(matriz[i][j]!=INFI){ //Comprobar si son vecinos
                int numTurno = routAux->turno(j);
                matriz[i][j] = numTurno;
            }
        }
        cout<<"Actualizacion de la fila del router numero: "<<i<<" exitosa"<<endl<<endl;
    }
}

void Camino::setCamino(void)
{
    int *pdist, P[cantidadRouters];
    pdist=dijkstra(matriz,routOrigen,routFinal,P);

    if (pdist[routFinal]!=INFI){
        cout<<endl;
        cout<<"Dijkstra: "<<endl;
        cout<<"La distancia minima router " <<routOrigen<<" al router "<<routFinal<<" es = "<<pdist[routFinal]<<endl;
        camino(P,routOrigen ,routFinal); 
    }            
    else return; 

    cam->borrar();
    cam->borrar();
    cam->addLast(routFinal);
    paquete->setNuevoCamino(cam);
    resetCamino();
}

void Camino::resetCamino(void)
{
    Lista<int>* caminoVacio = new Lista<int>();
    cam = caminoVacio;
}

int* Camino::dijkstra(int C[][cantidadRouters],int s, int t, int Pre[])
{
    static int D[cantidadRouters]; 
    int S[cantidadRouters];
    int actual, i, k, b;
    int menordist, nuevadist;
    for(i=0;i<cantidadRouters;i++){
                            S[i]=NO_MIEMBRO;
                            D[i]=INFI;
                            Pre[i]= -1;
    }
    S[s]=MIEMBRO; D[s]=0; actual=s; b=1; k=0;
    while((actual!=t)&&(b==1)){
                    b=0;
                    menordist=INFI;
                    for(i=0;i<cantidadRouters;i++){          
                            if(S[i]==NO_MIEMBRO){
                                    nuevadist=D[actual]+C[actual][i];
                                    if(nuevadist<D[i]){
                                            D[i]=nuevadist;
                                            Pre[i]=actual; b=1;
                                    }
                                    if(D[i]<menordist){
                                            menordist=D[i];
                                            k=i;  b=1;
                                    }
                            }
                    }
                    actual=k; 
                    S[actual]=MIEMBRO;
    }
    return D;
}

void Camino::camino(int P[], int s, int t)
{  
    if (t==s){
        int a = s;
        cam->addLast(a);
    }
   else{
        camino(P,s,P[t]);
        int b = t;
        cam->addLast(b);
   }
}

void Camino::imprimirMatrizAdy(void)
{
    for(int i=0; i<cantidadRouters; i++){
        for(int j = 0; j<cantidadRouters; j++){
            cout<<matrizAdy[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool Camino::hayCamino(int routO, int routD)
{
    int *pdistancia, P[cantidadRouters];
    pdistancia = dijkstra(matriz,routO,routD,P);

    if (pdistancia[routD]!=INFI)return true;
    else return false;
}

//----------------------------------------------------------Administrador-------------------------------------------------------
class Administrador{
private:
    Lista<Paquete*>* listaPaquetes;
    Lista<Paquete*>* listaAux;
    Lista<Router*>* routers;
    int matriz[cantidadRouters][cantidadRouters];
    Camino* camino;
    
public: 
    Administrador(void){};
    Administrador(Lista<Paquete*>* paquetes, Lista<Router*>* routs,Camino* cam);
    ~Administrador(void){};
    
    void resetearCaminos();
};

Administrador::Administrador(Lista<Paquete*>* paquetes, Lista<Router*>* routs,Camino* cam)
{
    listaPaquetes = paquetes;
    routers = routs;
    camino = cam;
}

void Administrador::resetearCaminos()
{   
    cout<<"Cantidad de paquetes para resetear: "<<listaPaquetes->size()<<endl;
    listaAux = listaPaquetes;
    camino->actualizarMatriz();
    int cantidadDePaquetes = listaPaquetes->size();
    cout<<"Actualizacion de Matriz exitosa"<<endl;
    for(int i=0; i<cantidadDePaquetes; i++){
        Paquete* paquete = listaAux->cabeza();
        camino->setNuevoPaquete(paquete);
        //cout<<"Reseteo del paquete numero: "<<i<<" completado con exito"<<endl;
        listaAux = listaAux->resto();
        //cout<<"Cantidad de paquetes: "<<listaPaquetes->size()<<endl;
    }
    cout<<"Reseteo de los caminos de los paquetes exitoso"<<endl;
}

//----------------------------------------------------------Main-------------------------------------------------------------
int main(){

    Lista<Router*>* rout = new Lista<Router*>(); //Lista de todos los routers creados
    Lista<Terminal<Router*>*>* terminales = new Lista<Terminal<Router*>*>(); //Lista de todas las maquinas creadas, independiente del routerAEnviar asociado
    Lista<Paquete*>* paquetes = new Lista<Paquete*>(); //Lista de todos los paquetes creados, independiente de la maquina creadora
    int maxVecinos = 2;
    fill(*matrizAdy, *matrizAdy + cantidadRouters*cantidadRouters, INFI); //Inicializo la matriz de adyacencia con todos los nodos desconectados
    Lista<Paquete*>* listaAEnviar = new Lista<Paquete*>();
    Lista<Paquete*>* listaRecibida = new Lista<Paquete*>();
    Lista<Paquete*>* listaVacia = new Lista<Paquete*>();
    random_device rd;
    uniform_int_distribution<int> posiblesRouters(0,cantidadRouters-1);
    uniform_int_distribution<int> posiblesTerminales(1, cantidadTerminales);
    uniform_int_distribution<int> posiblesPaginas(1,5);
    uniform_int_distribution<int> posiblesTamanios(1, 20);
    uniform_int_distribution<int> posibleAnchoBanda(3,8);
    uniform_int_distribution<int> posiblesVecinos(1, maxVecinos);


    //Creacion de los routers
    for(int i = 0; i < cantidadRouters; i++){
        Router* nuevoRout = new Router(i, paquetes);
        rout->add(nuevoRout);
        int ancho = posibleAnchoBanda(rd); //Recordar cambiarlo
        nuevoRout->setAnchoBanda(ancho);
    }

    //Creacion de Terminales
    for(int i = 0; i < cantidadTerminales; i++){
        int numMaq, numRout;
        int idCantTermi;
        bool noApto = true;//Comprobacion que numero de maquinas del routerAEnviar elegido sea menor que el limite (256)
        
        //Bucle para seleccionar un routerAEnviar aleatorio apto, con cantidad de maquinas disponibles 
        while(noApto){ 
            numRout = posiblesRouters(rd); //Eleccion de Router Aleatorio
            Router* routTentativo = buscarRouter(numRout, rout); 
            idCantTermi = routTentativo->getCantidadTerminales();//Obtencion de la cantidad de Maquinas asociada al routerAEnviar aleatorio obtenido
            if(idCantTermi <256 ){  //Comprobacion de la cantidad de maquinas es menor a la maxima Tentativo
                numMaq = idCantTermi+1;
                Terminal<Router*>* nuevaTerminal = new Terminal<Router*>(numMaq,numRout,routTentativo,i+1);//Creacion de la nueva maquina
                routTentativo->setNuevaTerminal(nuevaTerminal);//Asociacion de la maquina al routerAEnviar
                terminales->add(nuevaTerminal);//Agregado de la maquina nueva a la lista de maquinas    
            }            
            noApto = false;
        }
    }
    
    // Creacion de conexiones entre los Routers
    // Dos bucles: el primero para elegir los routers vecinos y guardarlos, y el segundo para guardar en los vecinos ese routerAEnviar
    Lista<Router*>* routAux = rout;
    for(int i = 0; i < cantidadRouters; i++){ //i representa el numero del routerAEnviar al que se le esta designando los vecinos
        Router* routActual = routAux->cabeza();
        Router* routVecino;
        int idActual = routActual->getID();
        int idVecino;
        int cantidadVecinosActual;
        if(routActual->getVecinos()->esVacia()) cantidadVecinosActual = 0;
        else cantidadVecinosActual = routActual->getNumVecinos()->size();;
        
        int cantVeciAleat = posiblesVecinos(rd);

        if(cantVeciAleat>cantidadVecinosActual){
            cantVeciAleat = cantVeciAleat - cantidadVecinosActual;

            for(int j = 0; j<cantVeciAleat; j++){

                int numRoutVeci = posiblesRouters(rd);
                if(!routActual->getNumVecinos()->esta(numRoutVeci)){
                    if(numRoutVeci!=routActual->getID()){
                        routVecino = buscarRouter(numRoutVeci, rout); 
                        int numVecino = routActual->getNumVecinos()->size();;
                        
                        if(numVecino<=maxVecinos){
                            idVecino = routVecino->getID();

                            routActual->setNuevoVecino(routVecino);
                            routVecino->setNuevoVecino(routActual);
                            
                            matrizAdy[idActual][idVecino] = 1; //Actualizacion de la matriz de Adyacencia
                            matrizAdy[idVecino][idActual] = 1;
                        }
                        else j--;
                    }
                }
                else j--; //Caso en que el numero del routerAEnviar proutVecino sea su mismo numero de ID
            }
        }
        routAux = routAux->resto(); //Movimiento hacia el siguiente routerAEnviar
    }

    //imprimirMatriz();
    Camino* camino = new Camino(matrizAdy, rout);

    // Creacion de paginas 
    int cantidadPaginas = posiblesPaginas(rd);
    cout<<"La cantidad de paginas es: "<<cantidadPaginas<<endl<<endl<<endl;
    for(int i=0; i<cantidadPaginas; i++){
        
        //Seleccion de maquina generadora aleatoria
        cout<<"Pasada numero: "<<i+1<<endl<<endl<<endl;
        int numTerminalAleat = posiblesTerminales(rd);
        cout<<"Terminal origen aleatoria de la pagina numero: "<<i<<" es: "<<numTerminalAleat<<endl<<endl;
        Terminal<Router*>* terminalOrigenAleat = buscarTerminal(numTerminalAleat, terminales);
        int numTerminalFinal = posiblesTerminales(rd);
        cout<<"Terminal destino aleatoria de la pagina numero: "<<i<<" es: "<<numTerminalFinal<<endl<<endl;
        if(numTerminalAleat == numTerminalFinal){
            while(numTerminalAleat == numTerminalFinal){
                numTerminalFinal = posiblesTerminales(rd);
                cout<<"Terminal destino aleatoria segunda opcion de la pagina numero : "<<i<<" es: "<<numTerminalFinal<<endl<<endl;
            }
        }

        Terminal<Router*>* terminalFinalAleat = buscarTerminal(numTerminalFinal, terminales);
        
        //Generacion de la pagina y envio
        Router* routerO = terminalOrigenAleat->getRouterAsociado();
        int routO = routerO->getID();
        cout<<"Router origen aleatoria de la pagina numero : "<<i<<" es: "<<routO<<endl<<endl;
        Router* routerD = terminalFinalAleat->getRouterAsociado();
        int routD = routerD->getID();
        cout<<"Router destino aleatoria de la pagina numero : "<<i<<" es: "<<routD<<endl<<endl;

        if(routD!=routO){
            if(camino->hayCamino(routO,routD)){
                int tam = posiblesTamanios(rd);
                terminalOrigenAleat->enviarPagina(rout, cantidadRouters, i, terminalFinalAleat->getNumeroTerminal(), terminalFinalAleat->getNumeroRouter(),numTerminalFinal,tam);
                listaRecibida = routerO->getListaAEnviar();
                //cout<<"El tamanio de la lista recibida en el main es de: "<<listaRecibida->size()<<endl;
                int tamanio = listaRecibida->size();
                Paquete* paquete = listaRecibida->cabeza();
                //cout<<"Paquete numero "<<paquete->getOrdenPagina()<<" de "<<paquete->getCantiTotalPaq()<<endl;
                camino->setNuevoPaquete(paquete);
                Lista<int>* caminoPaq = paquete->getCamino();
            
                cout<<endl;
                listaAEnviar->add(paquete);
                listaRecibida = listaRecibida->resto();
                //cout<<"Entrada al bucle de paquetes exitoso"<<endl;
                caminoPaq->impre();
                for(int j = 1; j<tamanio; j++){
                    Lista<int>* camResto = new Lista<int>();
                    camResto= caminoPaq->copy();
                    Paquete* paquete = listaRecibida->cabeza();
                    //cout<<"Paquete numero "<<paquete->getOrdenPagina()<<" de "<<paquete->getCantiTotalPaq()<<endl;
                    paquete->setNuevoCamino(camResto);
                    //paquete->getCamino()->impre();
                    listaAEnviar->add(paquete);
                    listaRecibida = listaRecibida->resto();
                }
                routerO->recibirListaConCaminos(listaAEnviar);
                routerO->vaciarListaAEnviar();
                listaRecibida = listaVacia;
                listaAEnviar = listaVacia;
                cout<<endl;
                cout<<"Se enviaron correctamente los paquetes de la pagina numero: "<<i<<endl;
            }
            else i--;
        }
        else i--;
    }

    cout<<"Inicio de los ciclos: "<<endl;


    //Se inician los ciclos 
    Administrador* administrador= new Administrador(paquetes, rout,camino);
    int ciclos = 10;
    int dosCiclos = 0;
    Lista<Router*>* routsAux = new Lista<Router*>();

    for(int i = 0; i<ciclos; i++){
        routsAux = rout;
        cout<<"Ciclo numero: "<<i<<endl;

        if(dosCiclos==2){
            cout<<"Reseteo de Caminos"<<endl;
            administrador->resetearCaminos();
            dosCiclos = 0;
        }

        for(int j = 0; j<rout->size(); j++){
            Router* auxRout = routsAux->cabeza();
            cout<<"Ciclo del Router numero: "<<auxRout->getID()<<endl;
            cout<<"Cantidad de paquetes: "<<paquetes->size()<<endl;
            auxRout->ciclo();
            routsAux = routsAux->resto();
            if(paquetes->esVacia()) break;
        }
        if(paquetes->esVacia()) break;
        dosCiclos++;
    }

    cout<<"Finalizo la Simulacion Correctamente :) ";
     
    return EXIT_SUCCESS;
}
