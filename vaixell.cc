#include "vaixell.hh"

//Constructors

void Vaixell::vaixell()
{
}

//Modificadors
void Vaixell::modificar_vaixell(int prodb, int b, int prods, int s)
{
    prodbuy = prodb;
    buy = b;
    prodsell = prods;
    sell = s;
}

void Vaixell::clear()
{
    while(not viatges.empty()){
        viatges.pop();
    }
}

void Vaixell::fer_viatge(id_ciutat ct)
{
    viatges.push(ct);
}

//Consultors

int Vaixell::consultar_id_comp()
{
    return prodbuy;
}

int Vaixell::consultar_id_vend()
{
    return prodsell;
}

int Vaixell::consultar_compres()
{
    return buy;
}

int Vaixell::consultar_vendes()
{
    return sell;
}

void Vaixell::escriure_vaixell()
{
    cout << prodbuy << ' ' << buy << ' ' << prodsell 
    << ' ' << sell << endl;
    queue <id_ciutat> viatges_write = viatges;
    while(not viatges_write.empty()){
        cout << viatges_write.front() << endl;
        viatges_write.pop();
    } 
}