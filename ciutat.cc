#include "ciutat.hh"

//Constructor
    void Ciutat::ciutat()
    {
        inv.clear();
        vol_total = 0;
        pes_total = 0;
    }

//Modificadors

    void Ciutat::clear()
    {
        inv.clear();
        pes_total = 0;
        vol_total = 0;
    }

    void Ciutat::add_prod(int pes, int vol, int nec, int hav, int id)
    {
        inv.mod_prod_inventari(nec, hav, id);
        pes_total += pes;
        vol_total += vol;
    }

    void Ciutat::mod_prod(int pes, int vol, int nec, int hav, int id)
    {
        int pes_single, vol_single;
        if(hav == 0){
            pes_single = pes;
            vol_single = vol;
        }
        else{
            pes_single = pes/hav;
            vol_single = vol/hav;
        }
        pes_total -= inv.propietat_inventari(id)*pes_single;
        pes_total += pes;
        vol_total -= inv.propietat_inventari(id)*vol_single;
        vol_total += vol;
        inv.mod_prod_inventari(nec, hav, id);

    }

    void Ciutat::erase_prod(int pes, int vol, int id)
    {
        pes_total -= pes;
        vol_total -= vol;
        inv.erase_prod_inventari(id);
    }

    void Ciutat::new_data(int pes_sub, int pes_new, int vol_sub, int vol_new)
    {
        pes_total -= pes_sub;
        pes_total += pes_new;
        vol_total -= vol_sub;
        vol_total += vol_new;
    }

//Consultors

    map <int, prod>::iterator Ciutat::consultar_inici()
    {
        return inv.consultar_inici_inventari();
    }

    map <int, prod>::iterator Ciutat::consultar_final()
    {
        return inv.consultar_final_inventari();
    }

    int Ciutat::consultar_tamany() const
    {
        return inv.consultar_tamany_inventari();
    }

    bool Ciutat::verificacio_inventari(int id, bool is_there)
    {
        return inv.verificacio_inventari(id, is_there);
    }

    bool Ciutat::empty()
    {
        return inv.empty();
    }

    int Ciutat::necessitats(int id)
    {
        return inv.necessitats_inventari(id);
    }

    int Ciutat::propietat(int id)
    {
        return inv.propietat_inventari(id);
    }

    int Ciutat::manca(int id)
    {
        return inv.manca(id);
    }

    int Ciutat::excedent(int id)
    {
        return inv.excedent(id);
    }

    void Ciutat::escriure_inventari()
    {
        auto it = inv.consultar_inici_inventari();
        while(it != inv.consultar_final_inventari()){
            cout << it->first << ' ' << it->second.have << ' ' << it->second.need << endl;
            ++it;
        }
        cout << pes_total << ' ' << vol_total << endl; 
    }

    void Ciutat::escriure_unitats()
    {
        cout << pes_total << ' ' << vol_total << endl;
    }


