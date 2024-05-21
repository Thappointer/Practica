#include "inventari.hh"


//Constructors
    void Inventari::inventari()
    {
        map_inventari.clear();
    }

//Modificadors
    void Inventari::mod_prod_inventari(int necessitat, int propietat, int id)
    {
        map_inventari[id].need = necessitat;
        map_inventari[id].have = propietat;
    }

    void Inventari::erase_prod_inventari(int id){
        map_inventari.erase(id);
    }

    void Inventari::property_modification(bool sum, int propietat, int id)
    {
        if(sum) map_inventari[id].have += propietat;
        else map_inventari[id].have -= propietat;
    }

    void Inventari::clear()
    {
        map_inventari.clear();
    }

//Consultors
    int Inventari::consultar_tamany_inventari() const
    {
        return map_inventari.size();
    }

    map <int, prod>::iterator Inventari::consultar_inici_inventari()
    {
        return map_inventari.begin();
    }

    map <int, prod>::iterator Inventari::consultar_final_inventari()
    {
        return map_inventari.end();
    }

    bool Inventari::cerca_inventari(int id) const
    {
        if(map_inventari.find(id) == map_inventari.end())
            return false;
        else return true;
    }

    int Inventari::necessitats_inventari(int id)
    {   
        return map_inventari[id].need;
    }

    int Inventari::propietat_inventari(int id)
    {
        return map_inventari[id].have;
    }

    int Inventari::manca(int id)
    {
        bool is_there = true;
        if(verificacio_inventari(id, is_there)){
            int lack = map_inventari[id].need - map_inventari[id].have;
            if(lack > 0){
                return lack;
            }
            else return 0;
        }
        else return 0;
    }

    int Inventari::excedent(int id)
    {
        bool is_there = true;
        if(verificacio_inventari(id, is_there)){
            int exc = map_inventari[id].have - map_inventari[id].need;
            if(exc > 0){
                return exc;
            }
            else return 0;
        }
        else return 0;
    }

    bool Inventari::verificacio_inventari(int id, bool is_there)
    {
        if(is_there){
            if(map_inventari.find(id) != map_inventari.end()){
                return true;
            }
            else return false;
        }
        else{
            if(map_inventari.find(id) != map_inventari.end()){
                return false;
            }
            else return true;
        }
    }

    bool Inventari::empty()
    {
        if(map_inventari.empty())
            return true;
        else return false;
    }