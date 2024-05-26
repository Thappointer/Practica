#include "inventari.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#endif

/** @brief Identificador que assigna un valor enter a un producte
 * 
*/
typedef int id_producte;

/** @brief Identificador que assigna una string a una ciutat
 * 
*/
typedef string id_ciutat;

/** @brief Classe que representa una ciutat del riu.
 * 
*/
class Ciutat{

    private:
    /** @brief Atribut que composa l'inventari de la ciutat.
     * 
    */
    Inventari inv;

    /** @brief Atribut que representa el pes total d'una ciutat. 
     * 
    */
    int pes_total;

    /** @brief Atribut que representa el volum total d'una ciutat.
     * 
    */
    int vol_total;

    public:

    //Constructor

    /** @brief Constructor per defecte de la classe ciutat 
     * @pre cert
     * @post El paràmetre implícit conté un inventari i un pes i volum totals.
     * El pès i volum totals són nuls. 
    */
    void ciutat();

    //Modificadors

    /** @brief Esborra tots els productes de l'inventari de la ciutat, modificant si cal el pès i volum totals.
     * @pre cert
     * @post El mapa de l'inventari de la ciutat queda amb totes les posicions sense inicialitzar i el pès i volum
     * totals passen a ser zero.
    */
    void clear();

    /** @brief Afegeix un nou producte a l'inventari, amb la seva quantitat d'unitats necessitades
     * i en propietat. També modifica, si cal, el pès i volum totals.
     * 
     * 
    */
    void add_prod(int pes, int vol, int nec, int hav, int id);

    /** @brief Modifica un producte de l'inventari, substituïnt les unitats necessitades
     * i en propietat. També modifica, si cal, el pès i volum totals.
     * 
    */
    void mod_prod(int pes, int vol, int nec, int hav, int id);

    /** @brief Treu un nou producte de l'inventari. També modifica, si cal, el pès i volum totals.
     * 
    */
    void erase_prod(int pes, int vol, int id);

    /** @brief Modifica el pes i volum totals en base a noves dades d'un producte.
     * @pre Els quatre paràmetres explícits són enters no negatius.
     * Concretament, pes_sub és el pès en conjunt antic del producte, pes_new és el seu pès en conjunt actualitzat,
     * vol_sub és el volum en conjunt antic del producte i vol_new és el seu volum en conjunt actualitzat.
     * @post S'extreu del pès total el pès en conjunt antic del producte i s'hi afegeix el pès en conjunt actualitzat.
     * També s'extreu del volum total el volum en conjunt antic del producte i s'hi afegeix el volum en conjunt actualitzat.
    */
    void new_data(int pes_sub, int pes_new, int vol_sub, int vol_new);

    //Consultors

    /** @brief Retorna la posició inicial del mapa de l'inventari.
     * 
    */
    map <int, prod>::iterator consultar_inici();

    /** @brief Retorna la posició final del mapa de l'inventari.
     * 
    */
    map <int, prod>::iterator consultar_final();

    /** @Retorna el nombre de productes a l'inventari de la ciutat.
     * 
    */
    int consultar_tamany() const;

    /** @brief Verifica si un producte està o no està en l'inventari, segons el paràmetre explícit.
     * 
     * @post En cas de que el paràmetre explícit is_there sigui cert, es retornarà cert si la posició del
     * paràmetre explícit id existeix en el mapa.
     * En el cas contrari en que is_there és fals, es retornarà cert si la posició del
     * paràmetre explícit id no existeix en el mapa.  
     * 
    */
    bool verificacio_inventari(int id, bool is_there);

    /** @brief Retorna la quantitat que es necessita d'un producte en l'inventari.
     * 
    */
    int necessitats(int id);

    /** @brief Retorna la quantitat que es té en propietat d'un producte en l'inventari.
     * 
    */
    int propietat(int id);

    /** @brief Retorna la quantitat de productes que una ciutat necessita, tenint en compte els que ja té.
     * @pre El paràmetre explícit id és un enter vàlid, d'entre zero i l'identificador de producte màxim.
     * @post Es retorna el nombre de necessitats menys la propietat d'un producte, excepte en els casos en que aquest sigui negatiu o 
     * el producte no formi part de l'inventari de la ciutat, en els que es retornarà zero. 
     * 
    */
    int manca(int id);

    /** @brief Retorna la quantitat de productes que a una ciutat li sobren, tenint en compte els que necessita.
     *  @pre El paràmetre explícit id és un enter vàlid, d'entre zero i l'identificador de producte màxim.
     * @post Es retorna el nombre de propietat menys la necessitat d'un producte, excepte en els casos en que aquest sigui negatiu o 
     * el producte no formi part de l'inventari de la ciutat, en els que es retornarà zero.  
    */
    int excedent(int id);

    /** @brief Escriu l'inventari de la ciutat.
     * @pre cert
     * @post 
     * 
    */
    void escriure_inventari();

    /** @brief Escriu el pès i volum totals de la ciutat.
     * @pre cert
     * @post Escriu pel canal estàndard de sortida el pès total, seguit del volum total, separats amb un caràcter d'espaiat.
    */
    void escriure_unitats();
    
    /** @brief Retorna si l'inventari de la ciutat està buit o no.
     * @pre cert 
     * @post Es retorna cert cas de que l'inventari no tingui cap producte i en cas contrari
     * es retorna fals.  
    */
    bool empty();
};