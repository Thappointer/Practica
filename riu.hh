#include "producte.hh"
#include "vaixell.hh"
#include "BinTree.hh"

/** @brief Struct que conté una operació invidivual en una ruta.
 * 
 * Conté:
 * - Nombre de compres efectuades pel vaixell a la ciutat.
 * - Nombre de vendes efectuades pel vaixell a la ciutat.
 * - L'identificador de la ciutat.
 * - Un booleà que indica si l'operació és nul·la.
 * - Un constructor buit que defineix les compres i vendes a zero.
 * - Un constructor que defineix tots els valors anteriors.
 * 
 * Nota: Tota operació serà no nul·la per defecte.
*/
struct operacio //COMMENTED
{
    int comp, vend;
    id_ciutat idc;
    bool null;

    /** @brief Constructor per defecte d'operació
     * @pre cert
     * @post Les compres i vendes són inicialitzades a zero. La operació no és nul·la.
    */
    operacio(){
        comp = 0;
        vend = 0;
        null = false;
    }
    
    /** @brief Constructor amb compres i vendes d'operació.
     * 
     * @pre La ciutat identificada pel tercer paràmetre explícit forma part del paràmetre implícit.
     * Tant el primer com el segon paràmetre explícit són majors o iguals que zero. 
     * 
     * @post Les compres i vendes són inicialitzades a amb els valors del primer i segon paràmetre 
     * explícit respectivament. L'identificador és inicialitzat amb el tercer paràmetre explícit.
     * Per últim, la operació no és nul·la.
    */
    operacio(int c, int v, id_ciutat ct)
    {
        comp = c;
        vend = v;
        idc = ct;
        null = false;
    }
};


/** @brief Struct que conté característiques d'una ruta.
*   
*   Conté:
* - Nombre total de transaccions.
* - Una cua amb les operacions de cada ciutat present en el camí del vaixell, en les que es pot
*   no haver efectuat cap transacció. 
* - Constructor per defecte que únicament inicialitza les transferències a zero.
*/
struct ruta
{
    int trans;

    queue <operacio> operacions;

    ruta()
    {
        trans = 0;
    }
};

/** @brief Classe que representa un riu
 *  
*/
class Riu{
    private:
    
    /** @brief Arbre que emmagatzema els id's de cada ciutat 
     * 
    */
    BinTree <id_ciutat> arbre_ciutats;
    
    /** @brief Mapa que relaciona un identificador amb la seva ciutat corresponent
     * 
    */
    map <id_ciutat, Ciutat> mapa_ciutats;
    
    /** @brief Vector que relaciona un identificador amb el seu producte corresponent
     * 
    */
    vector <Producte> vector_producte;

    /** @brief Identificador de major valor del mapa de productes.
     * 
    */
    int max_id;

    /** @brief Atribut que representa un vaixell.
     * 
    */
    Vaixell boat;

    /** @brief Llegeix els identificadors de les ciutats, en ordre de l'arbre, pel canal estàndard 
     * d'entrada.
     * 
     * @pre La seqüència de lectura del riu que s'introdueix pel canal estàndard d'entrada fa
     * servir el caràcter '#' per indicar els naixements del riu. 
     * 
     * @post A partir de la seqüència llegida pel canal estàndard d'entrada, es modifica en preordre 
     * l'arbre del paràmetre implícit, de manera que la seva estructura es substitueix per la de la 
     * seqüència. 
    */
    void llegir_riu_aux(BinTree <id_ciutat> &t); //COMMENTED

    /** @brief Intercanvia els productes entre dues ciutats que tenen amb els que necessiten. 
     * @pre Les dues ciutats pertanyen al riu i no són la mateixa.
     * 
    */ 
    void trade(Ciutat &ct1, Ciutat &ct2);

    /** @brief La ciutat del node pare comercia, primer amb la del node fill esquerre, i després amb la del node fill dret,
     * de manera recursiva.
     * 
    */
    void redistribuir_aux(BinTree <id_ciutat> t); 

    /** @brief Retorna la ruta que farà el vaixell en el viatge.
     * 
    */
    ruta triar_ruta(BinTree <id_ciutat> t, int buy, int sell);

    /** @brief Modifica les ciutats per les que el vaixell ha passat i retorna l'identificador 
     * de la última.
     * 
     * @pre El paràmetre explícit no és buit...
    */
    operacio efectuar_viatge(queue <operacio> &op);

    /** @brief A partir d'un identificador de producte, es verifica si aquest hi és o no 
     * al mapa de productes. 
     * 
     * @pre Un identificador d'un producte que pertanyi al paràmetre implícit sempre serà 
     * major estricte que zero i menor o igual que el seu max_id.
     * 
     * @post Retorna cert si l'identificador de producte del paràmetre explícit correspon 
     * a un dels productes del paràmetre implícit, i fals en cas contrari. 
     * Degut a que els identificadors de producte són consecutius, només cal comprovar 
     * si el paràmetre explícit pertany a l'intèrval [1, max_id].
    */  
    bool verificar_producte(id_producte id) const; //COMMENTED

    /** @brief A partir d'un identificador de ciutat, es verifica si aquesta hi és o 
     * no al mapa de productes. 
     * 
     * @pre cert
     * 
     * @post Retorna cert si la ciutat identificada pel paràmetre explícit pertany al
     * paràmetre implícit, i fals en cas contrari.
    */  
    inline bool verificar_ciutat(id_ciutat s) const; //COMMENTED

    public:

    //Constructor
    /** @brief Constructor per defecte de la classe riu.
     * 
     * @pre cert
     * 
     * @post cert
    */
    Riu();

    /** @brief Constructor de vaixell.
     * 
    */
    void vaixell(int prodb, int b, int prods, int s);
    
    //Modificadors

    /** @brief Llegeix els identificadors de les ciutats, en ordre de l'arbre, pel canal
     * estàndard d'entrada. També esborra les ciutats i els viatges del vaixell.
     * 
     * @pre La seqüència de lectura del riu que s'introdueix pel canal estàndard d'entrada 
     * fa servir el caràcter '#' per indicar els naixements del riu. 
     * 
     * @post A partir de la seqüència llegida pel canal estàndard d'entrada, es modifica 
     * l'arbre del paràmetre implícit, de manera que la seva estructura es substitueix 
     * per la de la seqüència. També s'esborren els elements del mapa de ciutats del paràmetre 
     * implícit així com la cua de viatges del seu vaixell.
    */  
    void llegir_riu();

    /** @brief Llegeix l'identificador d'una ciutat i, si aquesta existeix, un inventari amb 
     * els seus atributs corresponents.
     * 
     * @pre S'introdueix pel canal estàndard d'entrada un identificador de ciutat i el tamany
     * d'un inventari, indicant el nombre de productes diferents. Cada un d'aquests productes
     * pertanyen al comerç del riu. 
     * Per cada producte diferent, s'indiquen el seu identificador, les unitats en propietat
     * que té la ciutat i les que es necessiten. L'identificador és major o igual que 1 i menor
     * o igual que el major identificador de producte. El nombre d'elements en possessió de cada
     * producte és major o igual que zero i el nombre d'elements que es necessiten de cada 
     * producte és major estricte que zero.
     * 
     * @post En cas de que la ciutat, identificada pel primer paràmetre explícit, no existeixi
     * dins del paràmetre implícit, s'escriurà un error pel canal estàndard d'escriptura i es
     * llegiran el nombre de productes així com, per cadascun, el seu identificador, les unitats
     * en propietat i les que es necessiten. Aquestes dades no modificaran en cap cas el
     * paràmetre implícit. 
     * En cas contrari, es llegirà tantes vegades com indica el segon paràmetre explícit 
     * l'identificador del producte, les seves unitats que la ciutat té en propietat i
     * les que aquesta necessita, del producte en qüestió.   
     * Aquests tres valors quedaran assignats a la ciutat corresponent del paràmetre implícit.
     * En cas de que la ciutat existeixi, però ja formi part del paràmetre implícit, 
     * s'esborrarà l'inventari antic abans d'assignar el nou. 
     * 
    */
    void llegir_inventari(string id, int nump);

    /** @brief Llegeix múltiples inventaris de diverses ciutats.
     * @pre cert
     * @post Mentres que l'identificador sigui diferent de "#", es llegiran els inventaris de cada ciutat, a partir
     * del seu nombre de producte corresponents.
     * 
    */
    void llegir_inventaris();
    
    /** @brief Llegeix productes nous, a partir dels seus respectius identificadors, pesos i volums i els 
     * afegeix al mapa de productes. 
     * @pre Totes les ciutats existeixen...
    */
    void agregar_productes(int nump);

    /** @brief Es llegeixen identificadors de producte i ciutat i, en cas de que ambdós existeixin i el
     * producte no formi part de l'inventari de la ciutat, aquest s'afegeix a l'inventari de la ciutat,
     * així com les seves dades. Es modificarà si cal el pès i volum totals, que en tot cas s'escriuran.  
     * 
    */
    void posar_producte(id_ciutat ct, id_producte idp, int have, int need);

    /** @brief Es llegeixen identificadors de producte i ciutat i, en cas de que ambdós existeixin i el
     * producte formi part de l'inventari de la ciutat, es modificaran les seves dades de l'inventari així 
     * com de ser necessari el pès i volum totals, que en tot cas s'escriuran.
     * 
    */
    void modificar_producte(id_ciutat ct, id_producte idp, int have, int need);
    
    /** @brief Es llegeixen identificadors de producte i ciutat i, en cas de que ambdós existeixin i el
     * producte no formi part de l'inventari de la ciutat, s'esborren les seves dades de l'inventari. 
     * De ser necessari, es modificaran el pès i volum totals, que en tot cas s'escriuran.
     * 
    */
    void treure_producte(id_ciutat ct, id_producte idp);

    /** @brief Substitueix els elements del vaixell, excepte els viatges, sempre i quan tots els identificadors existeixin
     * i siguin diferents.
     * 
    */
    void modificar_vaixell(int pbuy, int buy, int psell, int sell);

    /** @brief Es llegeixen dos identificadors de ciutat. En cas de que ambdues existeixin, s'intercanvien 
     * els productes que necessiti una i tingui l'altra.
     * 
    */
    void comerciar(string s1, string s2);

    /** @brief La ciutat de la desembocadura comercia, primer amb la ciutat a mà dreta i després amb la de mà esquerra,
     * així successivament.
     * 
    */
    void redistribuir();

    /** @brief El vaixell realitza el recorregut que més productes permèt comprar i vendre, si és igual escull el
     * més curt i en cas de que aquest paràmentre també sigui igual, escollirà el recorregut que passa per riu amunt
     * a mà dreta. Els inventaris de les ciutats es modifiquen i al final s'escriuen pel canal estàndard de sortida els
     * productes comprats i venuts pel vaixell.  
     * 
    */
    void fer_viatge();


    //Consultors
    /** @brief Escriu el nombre total de productes diferents
     * @pre cert
     * @post S'escriurà pel canal estàndard de sortida l'identificador de producte màxim present al riu, ja que sempre 
     * representa el nombre total de productes diferents.  
    */
    void consultar_num() const;

    /** @brief Escriu les unitats que es necessiten i es tenen d'un producte en un inventari.
     * @pre cert 
     * @post En cas de que la ciutat, identificada pel paràmetre explícit, no existeixi dins del paràmetre implícit, s'escriurà un error pel 
     * canal estàndard d'escriptura.
     * En un segon cas en que la ciutat existeixi, però el producte no formi part del comerç del paràmetre implícit, s'escriura
     * un error diferent pel canal estàndard d'escriptura.
     * 
     * En un últim cas en que tant la ciutat com el producte existeixin al paràmetre implícit, però aquest no formi part de l'inventari
     * de la ciutat, s'escriura un últim error diferent pel canal estàndard d'escriptura.
     * 
     * En el cas en que tots els requeriments es compleixin, s'escriurà l'identificador del producte, seguit per les unitats en propietat del producte de l'identificador
     * del segon paràmetre explícit, seguides per les seves unitats en necessitat pel canal estàndard de sortida. 
     * Aquestes unitats corresponen únicament a l'inventari de la ciutat de l'identificador del primer paràmetre explícit.  
    */
    void consultar_producte(id_ciutat ct, id_producte id); //COMMENTED

    /** @brief Es llegeix un identificador de producte i, en cas d'existir, s'escriu el seu pès i volum.
     * 
    */
    void escriure_producte(id_producte idp);

    /** @brief Es llegeix un identificador de ciutat i, en cas d'existir, s'escriu el seu inventari.
     * @pre cert
     * @post En cas de que la ciutat, identificada pel paràmetre explícit, no existeixi dins del paràmetre implícit, s'escriurà un error pel 
     * canal estàndard d'escriptura.
     * En cas contrari, per cada producte que pertanyi a l'inventari de la ciutat, s'escriuran els següents atributs:
     * - El seu identificador.
     * - La quantitat del producte 
    */
    void escriure_ciutat(id_ciutat ct);

    /** @brief Escriu els elements del vaixell, així com la última ciutat visitada en cada un dels viatges realitzats,
     * en ordre cronològic.
     * @pre cert
     * @post S'escriuen pel canal estàndard de sortida els atributs del vaixell en aquest ordre:
     * - L'identificador del producte que es vol comprar
     * - El nombre de productes que es volen comprar
     * - L'identificador del producte que es vol vendre
     * - El nombre de productes que es volen vendre
     * - La última ciutat visitada corresponent a cada un dels viatges realitzats pel vaixell.
    */
    void escriure_vaixell();
};