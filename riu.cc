#include "riu.hh"

//Constructor
    void Riu::vaixell(int prodb, int b, int prods, int s)
    {
        boat.modificar_vaixell(prodb, b, prods, s);
    }

    Riu::Riu()
    {
        max_id = 0;
        vector_producte.resize(1);
    }

//Modificadors
    void Riu::llegir_riu_aux(BinTree <id_ciutat> &t)
    {
        id_ciutat s;
        cin >> s;
        if(s != "#"){
            mapa_ciutats[s].ciutat();
            BinTree <id_ciutat> left;
            llegir_riu_aux(left);
            BinTree <id_ciutat> right;
            llegir_riu_aux(right);
            t = BinTree <id_ciutat> (s, left, right);
        }
        else t = BinTree <id_ciutat>();
    }

    void Riu::llegir_riu()
    {
        mapa_ciutats.clear();
        boat.clear();
        llegir_riu_aux(arbre_ciutats);
    }

    void Riu::llegir_inventari(id_ciutat idc, int nump)
    {
        if(verificar_ciutat(idc)){
            id_producte idp;
            mapa_ciutats[idc].clear();
            for(int i = 0; i < nump; ++i){
                cin >> idp;
                if(verificar_producte(idp)){
                    int hav, nec;
                    cin >> hav >> nec;
                    int pes = vector_producte[idp].consultar_pes()*hav;
                    int vol = vector_producte[idp].consultar_volum()*hav;
                    mapa_ciutats[idc].add_prod(pes, vol, nec, hav, idp);
                } 
                else cout << "error: no existe el producto" << endl;
            }
        }
        else{
            cout << "error: no existe la ciudad" << endl;
            string bin;
            for(int i = 0; i < nump; ++i){
                getline(cin, bin);
            }
        }
    }

    void Riu::llegir_inventaris()
    {
        id_ciutat ct;
        cin >> ct;
        int nump;
        while(ct != "#"){
            cin >> nump;
            llegir_inventari(ct, nump);
            cin >> ct;
        }
    }
    
    void Riu::agregar_productes(int nump)
    {
        int pes, vol;
        for(int i = 0; i < nump; ++i){
            ++max_id;
            cin >> pes >> vol;
            Producte p(pes, vol);
            vector_producte.push_back(p);
        }
    }

    void Riu::posar_producte(id_ciutat ct, id_producte idp, int have, int need)
    {
        if(verificar_producte(idp)){
            if(verificar_ciutat(ct)){
                bool is_there = false;
                if(mapa_ciutats[ct].verificacio_inventari(idp, is_there)){
                    int pes = vector_producte[idp].consultar_pes()*have;
                    int vol = vector_producte[idp].consultar_volum()*have;
                    mapa_ciutats[ct].add_prod(pes, vol, need, have, idp);
                    mapa_ciutats[ct].escriure_unitats();
                }
                else cout << "error: la ciudad ya tiene el producto" << endl;
            }
            else cout << "error: no existe la ciudad" << endl;
        }
        else cout << "error: no existe el producto" << endl; 
    }

    void Riu::modificar_producte(id_ciutat ct, id_producte idp, int have, int need)
    {
        if(verificar_producte(idp)){
            if(verificar_ciutat(ct)){
                bool is_there = true;
                if(mapa_ciutats[ct].verificacio_inventari(idp, is_there)){
                    int pes, vol;
                    if(have != 0){
                        pes = vector_producte[idp].consultar_pes() * have;
                        vol =  vector_producte[idp].consultar_volum() * have;
                    }
                    else{
                        pes = vector_producte[idp].consultar_pes();
                        vol =  vector_producte[idp].consultar_volum();
                    }
                    mapa_ciutats[ct].mod_prod(pes, vol, need, have, idp);
                    mapa_ciutats[ct].escriure_unitats();
                }
                else cout << "error: la ciudad no tiene el producto" << endl;
            }
            else cout << "error: no existe la ciudad" << endl;
        }
        else cout << "error: no existe el producto" << endl; 
    } 
    
    void Riu::treure_producte(id_ciutat ct, id_producte idp)
    {
        if(verificar_producte(idp)){
            if(verificar_ciutat(ct)){
                bool is_there = true;
                if(mapa_ciutats[ct].verificacio_inventari(idp, is_there)){
                    int pes = vector_producte[idp].consultar_pes() * mapa_ciutats[ct].propietat(idp);
                    int vol = vector_producte[idp].consultar_volum() * mapa_ciutats[ct].propietat(idp);
                    mapa_ciutats[ct].erase_prod(pes, vol, idp);
                    mapa_ciutats[ct].escriure_unitats();
                }
                else cout << "error: la ciudad no tiene el producto" << endl;
            }
            else cout << "error: no existe la ciudad" << endl;
        }
        else cout << "error: no existe el producto" << endl; 
    }

    void Riu::modificar_vaixell(int pbuy, int buy, int psell, int sell)
    {
        if(verificar_producte(pbuy) and verificar_producte(psell)){
            if(pbuy != psell){
                boat.modificar_vaixell(pbuy, buy, psell, sell);
            }
            else cout << "error: no se puede comprar y vender el mismo producto" << endl;
        }
        else cout << "error: no existe el producto" << endl;
    }

    void Riu::comerciar(id_ciutat s1, id_ciutat s2)
    {
        if(verificar_ciutat(s1) and verificar_ciutat(s2)){
            if(s1 != s2){
                trade(mapa_ciutats[s1], mapa_ciutats[s2]);
            }
            else cout << "error: ciudad repetida" << endl;
        }
        else cout << "error: no existe la ciudad" << endl;
    }

    void Riu::trade(Ciutat &ct1, Ciutat &ct2)
    {
        auto iter1 = ct1.consultar_inici();
        auto end1 = ct1.consultar_final();
        auto iter2 = ct2.consultar_inici();
        auto end2 = ct2.consultar_final();
        int id1, id2;
        while(iter1 != end1 and iter2 != end2){
            id1 = iter1->first;
            id2 = iter2->first;
            if(id1 == id2){
                int id = id1;
                int oferta, demanda;
                int diferencia1 = iter1->second.have - iter1->second.need;
                int diferencia2 = iter2->second.have - iter2->second.need;
                int pes_sub, pes_new, vol_sub, vol_new;
                if(diferencia1 < 0 and diferencia2 > 0){
                    oferta = diferencia2;
                    demanda = (-1)*diferencia1;
                    int pass;
                    if(demanda > oferta){
                        pass = oferta;
                    }
                    else pass = demanda;

                    pes_sub = vector_producte[id].consultar_pes()*iter1->second.have;
                    vol_sub = vector_producte[id].consultar_volum()*iter1->second.have;
                    iter1->second.have += pass;
                    pes_new = vector_producte[id].consultar_pes()*iter1->second.have;
                    vol_new = vector_producte[id].consultar_volum()*iter1->second.have;
                    ct1.new_data(pes_sub, pes_new, vol_sub, vol_new);

                    pes_sub = vector_producte[id].consultar_pes()*iter2->second.have;
                    vol_sub = vector_producte[id].consultar_volum()*iter2->second.have;
                    iter2->second.have -= pass;
                    pes_new = vector_producte[id].consultar_pes()*iter2->second.have;
                    vol_new = vector_producte[id].consultar_volum()*iter2->second.have;
                    ct2.new_data(pes_sub, pes_new, vol_sub, vol_new);
                }
                else if(diferencia1 > 0 and diferencia2 < 0){
                    oferta = diferencia1;
                    demanda = (-1)*diferencia2;
                    int pass;
                    if(demanda > oferta){
                        pass = oferta;
                    }
                    else pass = demanda;
                    
                    pes_sub = vector_producte[id].consultar_pes()*iter1->second.have;
                    vol_sub = vector_producte[id].consultar_volum()*iter1->second.have;
                    iter1->second.have -= pass;
                    pes_new = vector_producte[id].consultar_pes()*iter1->second.have;
                    vol_new = vector_producte[id].consultar_volum()*iter1->second.have;
                    ct1.new_data(pes_sub, pes_new, vol_sub, vol_new);

                    pes_sub = vector_producte[id].consultar_pes()*iter2->second.have;
                    vol_sub = vector_producte[id].consultar_volum()*iter2->second.have;
                    iter2->second.have += pass;
                    pes_new = vector_producte[id].consultar_pes()*iter2->second.have;
                    vol_new = vector_producte[id].consultar_volum()*iter2->second.have;
                    ct2.new_data(pes_sub, pes_new, vol_sub, vol_new);
                }
                ++iter1;
                ++iter2;
            }
            else if(id1 < id2){
                ++iter1;
            }
            else{
                ++iter2;
            }
        }
    }

    void Riu::redistribuir_aux(BinTree <id_ciutat> t)
    {
        if(t.empty()) return;
        if(not t.left().empty()){
            comerciar(t.value(), t.left().value());
        }
        if(not t.right().empty()){
            comerciar(t.value(), t.right().value());
        }
        redistribuir_aux(t.left());
        redistribuir_aux(t.right());
    }

    void Riu::redistribuir()
    {
        redistribuir_aux(arbre_ciutats);
    }

    ruta Riu::triar_ruta(BinTree <id_ciutat> t, int buy, int sell)
    {
        int id_buy = boat.consultar_id_comp();
        int id_sell = boat.consultar_id_vend();
        id_ciutat idc = t.value();
        int excedent, manca;
        excedent = mapa_ciutats[idc].excedent(id_buy);
        manca = mapa_ciutats[idc].manca(id_sell); 
        int compres;
        if(excedent > buy){
            compres = buy;
        } 
        else compres = excedent;
        buy -= compres;
        int vendes;
        if(manca > sell){
            vendes = sell;
        } 
        else vendes = manca; 
        sell -= vendes;
        operacio op(compres, vendes, idc);
        if(compres == 0 and vendes == 0){
            op.null = true;
        }
        int resultat = compres + vendes;
        ruta r;
        if(buy != 0 or sell != 0){
            ruta left, right;
            if(not t.left().empty() or not t.right().empty()){
                left = triar_ruta(t.left(), buy, sell);
                right = triar_ruta(t.right(), buy, sell);
            }
            if(left.trans > right.trans){
                r = left;
            }
            else if(left.trans < right.trans){
                r = right;
            }
            else{
                bool next;
                next = true;
                queue <operacio> check_left = left.operacions;
                while(not check_left.empty() and next){
                    if(check_left.front().null)
                        check_left.pop();
                    else next = false;
                }
                next = true;
                queue <operacio> check_right = right.operacions;
                while(not check_right.empty() and next){
                    if(check_right.front().null)
                        check_right.pop();
                    else next = false;
                }
                if(check_left.size() < check_right.size()){
                    r = left;
                }
                else if(check_left.size() > check_right.size()){
                    r = right;
                }
                else r = left;
            }
        }
        r.trans += resultat;
        r.operacions.push(op);
        return r;
    }

    operacio Riu::efectuar_viatge(queue <operacio> &op)
    {
        operacio last_op;
        int id_buy = boat.consultar_id_comp();
        int id_sell = boat.consultar_id_vend();
        if(not op.empty()){
            bool found = false;
            while(not op.empty()){
                if(not op.front().null){
                    if(not found){
                        last_op = op.front();
                        found = true;
                    }
                    int comp = op.front().comp; 
                    int nec, hav, pes, vol;
                    if(comp > 0){
                        nec = mapa_ciutats[op.front().idc].necessitats(id_buy);
                        hav = mapa_ciutats[op.front().idc].propietat(id_buy)-comp;
                        if(hav == 0){
                            pes = vector_producte[id_buy].consultar_pes();
                            vol = vector_producte[id_buy].consultar_volum();
                        }
                        else{
                            pes = vector_producte[id_buy].consultar_pes()*hav;
                            vol = vector_producte[id_buy].consultar_volum()*hav;
                        }
                        mapa_ciutats[op.front().idc].mod_prod(pes, vol, nec, hav, id_buy);
                    }
                    int vend = op.front().vend; 
                    if(vend > 0){
                        nec = mapa_ciutats[op.front().idc].necessitats(id_sell);
                        hav = mapa_ciutats[op.front().idc].propietat(id_sell)+vend;
                        if(hav == 0){
                            pes = vector_producte[id_sell].consultar_pes();
                            vol = vector_producte[id_sell].consultar_volum();
                        }
                        else{
                            pes = vector_producte[id_sell].consultar_pes()*hav;
                            vol = vector_producte[id_sell].consultar_volum()*hav;
                        }
                        mapa_ciutats[op.front().idc].mod_prod(pes, vol, nec, hav, id_sell);
                    }
                }
                op.pop();
            }
            if(not found){
                last_op.null = true;
            }
        }
        else last_op.null = true;
        return last_op;
    }

    void Riu::fer_viatge()
    {
        ruta r;
        if(not arbre_ciutats.empty()){
            int buy, sell;
            buy = boat.consultar_compres();
            sell = boat.consultar_vendes();
            r = triar_ruta(arbre_ciutats, buy, sell);
            operacio last_op = efectuar_viatge(r.operacions);
            if(not last_op.null){
                boat.fer_viatge(last_op.idc);
            }
        }
        cout << r.trans << endl; 
    }


    //Consultors

    void Riu::consultar_num() const
    {
        cout << max_id << endl;
    }

    void Riu::consultar_producte(id_ciutat ct, id_producte id)
    {
        if(verificar_producte(id)){
            if(verificar_ciutat(ct)){
                bool is_there = true;
                if(mapa_ciutats[ct].verificacio_inventari(id, is_there)){
                    cout << mapa_ciutats[ct].propietat(id) << ' ' << mapa_ciutats[ct].necessitats(id) << endl;
                }
                else cout << "error: la ciudad no tiene el producto" << endl;
            }
            else cout << "error: no existe la ciudad" << endl;
        }
        else cout << "error: no existe el producto" << endl; 
    }

    bool Riu::verificar_producte(id_producte id) const
    {
        if(id > max_id or id < 1) return false;
        else return true;
    }

    bool Riu::verificar_ciutat(id_ciutat s) const
    {
        return mapa_ciutats.find(s) != mapa_ciutats.end();
    }

    void Riu::escriure_producte(id_producte idp)
    {
            if(verificar_producte(idp)){
                int pes = vector_producte[idp].consultar_pes();
                int vol = vector_producte[idp].consultar_volum();
                cout << idp << ' ' << pes << ' ' << vol << endl;
            }
            else cout << "error: no existe el producto" << endl;
    }

    void Riu::escriure_ciutat(id_ciutat ct)
    {
        if(verificar_ciutat(ct)){
            mapa_ciutats[ct].escriure_inventari();
        }
        else cout << "error: no existe la ciudad" << endl;
    }

    void Riu::escriure_vaixell()
    {
        boat.escriure_vaixell();
    }