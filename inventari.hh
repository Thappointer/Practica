#ifndef NO_DIAGRAM
#include <map>
#endif


using namespace std;

/** @brief Struct que emmagatzema les unitats d'un producte que es tenen i necessiten.
 * 
*/
struct prod
{
    int have;
    int need; 
};

/** @brief Classe que representa l'inventari d'una ciutat.
 * 
*/
class Inventari
{
    private:
        /** @brief Mapa que relaciona un identificador de producte amb les seves unitats 
         * que es tenen i necessiten.
         * 
        */
        map <int, prod> map_inventari;
        
        
    public:
    //Constructor
    /** @brief Constructor buit d'inventari
     * 
    */
   void inventari();

    //Modificadors

    /** @brief Afegeix o modifica, a partir de la seva id corresponent, el nombre de productes que es
     *  tenen i es necessiten d'un producte en concret al mapa de l'inventari. 
     * @pre L'identificador proporcionat pel tercer paràmetre explícit forma part del comerç del riu, 
     * el primer paràmetre explícit és un enter major estricte que zero i el segon és un enter major o igual que zero.
     * @post Les unitats en propietat i que es necessiten del producte, s'han substituït per les indicades pels 
     * paràmetres explícits. 
     *  
    */
    void mod_prod_inventari(int necessitat, int propietat, int id);

    /** @brief Esborra un producte de l'inventari de la ciutat.
     * @pre L'identificador id forma part del mapa general de productes.
     * @post La posició del mapa de l'inventari corresponent al paràmetre explícit queda esborrada. 
    */
    void erase_prod_inventari(int id);

    /** @brief Esborra tots els elements del mapa de l'inventari.
     * @pre cert
     * @post El mapa de l'inventari queda amb totes les posicions sense inicialitzar.
    */
    void clear();

    //Consultors
    /** @brief Retorna la quantitat de productes de l'inventari.
     * @pre cert
     * @post cert
    */
    int consultar_tamany_inventari() const;

    /** @brief Retorna un iterador amb la posició inicial del mapa de l'inventari.
     * @pre cert
     * @post cert
    */
    map <int, prod>::iterator consultar_inici_inventari();

    /** @brief Retorna un iterador amb la posició final del mapa de l'inventari.
     * @pre cert
     * @post cert
    */
    map <int, prod>::iterator consultar_final_inventari();

    /** @brief Busca si el paràmetre explícit és una clau del mapa de l'inventari.
     * @pre El paràmetre explícit és un enter
     * @post Retorna cert si l'identificador de producte forma part de l'inventari, per
     * tant si el producte en qüestió pertany a l'inventari de la ciutat.
     * En cas contrari, retorna fals. 
    */
    bool cerca_inventari(int id) const;

    /** @brief Consulta la quantitat de necessitats d'un producte en l'inventari.
     * 
    */
    int necessitats_inventari(int id);

    /** @brief Consulta la quantitat que es té en propietat d'un producte en l'inventari.
     * 
    */
    int propietat_inventari(int id);

    /** @brief Retorna la quantitat de productes que una ciutat necessita, tenint en compte els que ja té.
     * @pre El paràmetre explícit id és un enter vàlid, major estricte que zero i menor o igual a l'identificador de producte màxim.
     * @post Es retorna el nombre de necessitats menys la propietat d'un producte, excepte en els casos en que aquest sigui negatiu o 
     * el producte no formi part de l'inventari de la ciutat, en els que es retornarà zero. 
     * 
    */
    int manca(int id);

    /** @brief Retorna la quantitat de productes que a una ciutat li sobren, tenint en compte els que necessita.
     *  @pre El paràmetre explícit id és un enter vàlid, major estricte que zero i menor o igual a l'identificador de producte màxim.
     * @post Es retorna el nombre de propietat menys la necessitat d'un producte, excepte en els casos en que aquest sigui negatiu o 
     * el producte no formi part de l'inventari de la ciutat, en els que es retornarà zero.  
    */
    int excedent(int id);

    /** @brief Verifica si un producte està o no està en l'inventari, segons el segon paràmetre explícit.
     * 
     * @pre Cert.
     * 
     * @post En cas de que el paràmetre explícit is_there sigui cert, es retornarà cert si el producte 
     * indicat pel primer paràmetre explícit pertany a l'inventari. En cas contrari es retornarà fals.
     * En el cas contrari en que is_there és fals, es retornarà cert  si el producte 
     * indicat pel primer paràmetre explícit no pertany a l'inventari. En cas contrari es retornarà fals.  
     * 
    */
    bool verificacio_inventari(int id, bool is_there);

    /** @brief Retorna si l'inventari està buit o no.
     * @pre cert 
     * @post Es retorna cert cas de que l'inventari no tingui cap producte i en cas contrari
     * es retorna fals.  
    */
    bool empty();
};