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
            if(not mapa_ciutats[idc].empty()){
                mapa_ciutats[idc].clear();
            }
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
        while(iter1 != end1 and iter2 != end2){
            int id1 = iter1->first;
            int id2 = iter2->first;
            if(id1 == id2){
                int id = id1;
                int exc1, exc2;
                exc1 = iter1->second.have - iter1->second.need;
                exc2 = iter2->second.have - iter2->second.need;
                if(exc1 < 0 and exc2 >= 0){
                    int pass = exc2-(exc2+exc1);
                    if(exc1+exc2 < 0){
                        pass = exc2;
                    }
                    int pes, vol, nec, hav;
                    nec = iter1->second.need;
                    hav = (iter1->second.have)+pass;
                    pes = hav*vector_producte[id].consultar_pes();
                    vol = hav*vector_producte[id].consultar_volum();
                    ct1.mod_prod(pes, vol, nec, hav, id);
                    
                    nec = iter2->second.need;
                    hav = (iter2->second.have)-pass;
                    pes = hav*vector_producte[id].consultar_pes();
                    vol = hav*vector_producte[id].consultar_volum();
                    ct2.mod_prod(pes, vol, nec, hav, id);
                }
                else if(exc1 >= 0 and exc2 < 0){
                    int pass = exc1-(exc1+exc2);
                    if(exc1+exc2 < 0){
                        pass = exc1;
                    }
                    int pes, vol, nec, hav;

                    nec = iter1->second.need;
                    hav = (iter1->second.have)-pass;
                    pes = hav*vector_producte[id].consultar_pes();
                    vol = hav*vector_producte[id].consultar_volum();
                    ct1.mod_prod(pes, vol, nec, hav, id);
                    
                    nec = iter2->second.need;
                    hav = (iter2->second.have)+pass;
                    pes = hav*vector_producte[id].consultar_pes();
                    vol = hav*vector_producte[id].consultar_volum();
                    ct2.mod_prod(pes, vol, nec, hav, id);
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
        if(not t.left().empty()){
            comerciar(t.value(), t.left().value());
            redistribuir_aux(t.left());
        }
        if(not t.right().empty()){
            comerciar(t.value(), t.right().value());
            redistribuir_aux(t.right());
        }
    }

    void Riu::redistribuir()
    {
        if(not arbre_ciutats.left().empty()){
            comerciar(arbre_ciutats.value(), arbre_ciutats.left().value());
            redistribuir_aux(arbre_ciutats.left());
        }
        if(not arbre_ciutats.right().empty()){
            comerciar(arbre_ciutats.value(), arbre_ciutats.right().value());
            redistribuir_aux(arbre_ciutats.right());
        }
    }

    ruta Riu::triar_ruta(BinTree <id_ciutat> t, int buy, int sell)
    {
        int excedent, manca;
        excedent = manca = 0;
        int id_buy = boat.consultar_id_comp();
        int id_sell = boat.consultar_id_vend();
        id_ciutat idc = t.value();
        excedent = mapa_ciutats[idc].excedent(id_buy);
        manca = mapa_ciutats[idc].manca(id_sell); 
        int compres = buy-(buy-excedent);
        int vendes = sell-(sell-manca);

        ruta r;
        buy -= excedent;
        if(buy < 0){
            buy = 0;
        }
        r.buy = buy;
        sell -= manca; 
        if(sell < 0){
            sell = 0;
        }
        r.sell = sell;

        bool finished = ((buy == 0) and (sell == 0));
        ruta left(r.buy, r.sell), right(r.buy, r.sell);
        bool is_left, is_right;
        is_left = is_right = false;
        if(not t.left().empty() and not finished){
            left = triar_ruta(t.left(), r.buy, r.sell);
            is_left = true;
        }
        if(not t.right().empty() and not finished){
            right = triar_ruta(t.right(), r.buy, r.sell);
            is_right = true;
        }
        if(is_left and is_right){
            if(left.trans > right.trans){
                r = left;
            }
            else if(left.trans < right.trans){
                r = right;
            }
            else{
                queue <operacio> check_left = left.operacions;
                bool next = true;
                while(not check_left.empty() and next){
                    if(check_left.front().s_comp == 0 and check_left.front().s_vend == 0)
                        check_left.pop();
                    else next = false;
                }
                queue <operacio> check_right = right.operacions;
                next = true;
                while(not check_right.empty() and next){
                    if(check_right.front().s_comp == 0 and check_right.front().s_vend == 0)
                        check_right.pop();
                    else next = false;
                }
                if(check_left.size() < check_right.size()){
                    r = left;
                }
                else if(check_left.size() > check_right.size()){
                    r = right;
                }
                else{
                    r = left;
                }
            }
        }
        else if(not is_left and is_right){
            r = right;
        }
        else if(is_left and not is_right){
            r = left;
        }
        operacio op(compres, vendes, idc);
        if(compres == 0 and vendes == 0){
            op.null = true;
        }
        int resultat = compres + vendes;
        r.trans += resultat;
        r.operacions.push(op);
        return r;
    }

    operacio Riu::efectuar_viatge(queue <operacio> &op)
    {
        operacio last_op;
        int id_buy = boat.consultar_id_comp();
        int id_sell = boat.consultar_id_vend();
        if(op.empty()){
            last_op.null = true;
        }
        else{
            while(not op.empty()){
                if(not op.front().null)
                    last_op = op.front();
                int comp = op.front().s_comp; 
                if(comp > 0){
                    int nec = mapa_ciutats[last_op.idc].necessitats(id_buy);
                    int hav = mapa_ciutats[last_op.idc].propietat(id_buy)-comp;
                    int pes = vector_producte[id_buy].consultar_pes()*hav;
                    int vol = vector_producte[id_buy].consultar_volum()*hav;
                    mapa_ciutats[last_op.idc].mod_prod(pes, vol, nec, hav, id_buy);
                }
                int vend = op.front().s_vend; 
                if(vend > 0){
                    int nec = mapa_ciutats[last_op.idc].necessitats(id_sell);
                    int hav = mapa_ciutats[last_op.idc].propietat(id_sell)+vend;
                    int pes = vector_producte[id_sell].consultar_pes()*hav;
                    int vol = vector_producte[id_sell].consultar_volum()*hav;
                    mapa_ciutats[last_op.idc].mod_prod(pes, vol, nec, hav, id_sell);
                }
                op.pop();
            }
        }
        if(last_op.s_comp == 0 and last_op.s_vend == 0){
            last_op.null = true;
        }
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
            operacio op = efectuar_viatge(r.operacions);
            if(not op.null){
                boat.fer_viatge(op.idc);
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
        if(id > max_id or id < 0) return false;
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