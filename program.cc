#include "riu.hh"

using namespace std;

int main()
{
    Riu r;
    int n;
    cin >> n;
    r.agregar_productes(n);
    r.llegir_riu();
    int pbuy, buy, psell, sell;
    cin >> pbuy >> buy >> psell >> sell;
    r.vaixell(pbuy, buy, psell, sell);
    string s;
    cin >> s;
    while (s != "fin")
    {
        if(s == "//"){
            getline(cin, s);
        }
        else if(s == "lr" or s == "leer_rio"){
            cout << '#' << s << endl;
            r.llegir_riu();
        }

        else if(s == "li" or s == "leer_inventario"){
            cout << '#' << s;
            id_ciutat idc;
            int productes;
            cin >> idc >> productes;
            cout << ' ' << idc << endl;
            r.llegir_inventari(idc, productes);
        }

        else if(s == "ls" or s == "leer_inventarios"){
            cout << '#' << s << endl;
            r.llegir_inventaris();
        }

        else if(s == "mb" or s == "modificar_barco"){
            cout << '#' << s << endl;
            cin >> pbuy >> buy >> psell >> sell;
            r.modificar_vaixell(pbuy, buy, psell, sell);
        }

        else if(s == "eb" or s == "escribir_barco"){
            cout << '#' << s << endl;
            r.escriure_vaixell();
        }

        else if(s == "cn" or s == "consultar_num"){
            cout << '#' << s << endl;
            r.consultar_num();
        }

        else if(s == "ap" or s == "agregar_productos"){
            cout << '#' << s;
            int productes;
            cin >> productes;
            r.agregar_productes(productes);
            cout << ' ' << productes << endl;
        }

        else if(s == "ep" or s == "escribir_producto"){
            cout << '#' << s;
            int producte;
            cin >> producte;
            cout << ' ' << producte << endl;
            r.escriure_producte(producte);
        }

        else if(s == "ec" or s == "escribir_ciudad"){
            cout << '#' << s;
            id_ciutat idc;
            cin >> idc;
            cout << ' ' << idc << endl;
            r.escriure_ciutat(idc);
        }

        else if(s == "pp" or s == "poner_prod"){
            cout << '#' << s;
            id_ciutat idc;
            cin >> idc;
            id_producte idp;
            cin >> idp;
            cout << ' ' << idc << ' ' << idp << endl;
            int have, need;
            cin >> have >> need;
            r.posar_producte(idc, idp, have, need);
        }

        else if(s == "mp" or s == "modificar_prod"){
            cout << '#' << s;
            id_ciutat idc;
            cin >> idc;
            id_producte idp;
            cin >> idp;
            cout << ' ' << idc << ' ' << idp << endl;
            int have, need;
            cin >> have >> need;
            r.modificar_producte(idc, idp, have, need);
        }

        else if(s == "qp" or s == "quitar_prod"){
            cout << '#' << s;
            id_ciutat idc;
            cin >> idc;
            id_producte idp;
            cin >> idp;
            cout << ' ' << idc << ' ' << idp << endl;
            r.treure_producte(idc, idp);
        }

        else if(s == "cp" or s == "consultar_prod"){
            cout << '#' << s;
            id_ciutat idc;
            id_producte idp;
            cin >> idc >> idp;
            cout << ' ' << idc << ' ' << idp << endl;
            r.consultar_producte(idc, idp);
        }

        else if(s == "co" or s == "comerciar"){
            cout << '#' << s;
            id_ciutat c1, c2;
            cin >> c1 >> c2;
            cout << ' ' << c1 << ' ' << c2 << endl;
            r.comerciar(c1, c2);
        }

        else if(s == "re" or s == "redistribuir"){
            cout << '#' << s << endl;
            r.redistribuir();
        }

        else if(s == "hv" or s == "hacer_viaje"){
            cout << '#' << s << endl;
            r.fer_viatge();
        }
        cin >> s;
    }
}