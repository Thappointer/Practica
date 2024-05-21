#include "producte.hh"

    //Constructor

    Producte::Producte()
    {
        pes = 0;
        volum = 0; 
    }

    Producte::Producte(int p, int v)
    {
        pes = p;
        volum = v; 
    }

    //Consultors
    int Producte::consultar_pes() const
    {
        return pes;
    }
    
    int Producte::consultar_volum() const
    {
        return volum;
    }

    