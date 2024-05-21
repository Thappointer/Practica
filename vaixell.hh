#include "ciutat.hh"
#include <queue>
#include <string>


/** @brief Classe que representa un vaixell
 * 
*/
class Vaixell{
    private:
    /** @brief Identificador del producte a comprar 
     * 
    */
    int prodbuy;
    /** @brief Nombre de productes a comprar 
     * 
    */
    int buy;
    /** @brief Identificador del producte a vendre 
     * 
    */
    int prodsell;
    /** @brief Nombre de productes a vendre 
     * 
    */
    int sell;
    
    /** @brief cua que emmagatzema la ciutat
     * 
    */
    queue <id_ciutat> viatges;

    public:

    //Constructors

    /** @brief Constructor de vaixell per defecte.
     * 
    */
    void vaixell();

    //Modificadors

    /** @brief Modifica els paràmetres del vaixell.
     * 
    */
    void modificar_vaixell(int prodb, int b, int prods, int s);

    /** @brief Esborra els viatges del vaixell.
     * 
    */
    void clear();

    /** @brief Modifica el vaixell d'acord amb els canvis en l'últim viatge. 
     *  
     * 
    */
    void fer_viatge(id_ciutat ct);

    //Consultors
    /** @brief Retorna l'identificador del producte a comprar.
     * @pre cert
     * @post Es retorna el valor de l'atribut corresponent a l'identificador del producte a comprar del paràmetre implicit.
    */
    int consultar_id_comp();

    /** @brief Retorna l'identificador del producte a vendre.
     * @pre cert
     * @post Es retorna el valor de l'atribut corresponent a l'identificador del producte a vendre del paràmetre implicit.
    */
    int consultar_id_vend();

    /** @brief Retorna la quantitat del producte que es vol comprar. 
     * @pre cert
     * @post Es retorna el valor de l'atribut corresponent a la quantitat d'unitats del producte a comprar del paràmetre implicit.
    */
    int consultar_compres();

    /** @brief Retorna la quantitat del producte que es vol vendre. 
     * @pre cert
     * @post Es retorna el valor de l'atribut corresponent a la quantitat d'unitats del producte a vendre del paràmetre implicit.
    */
    int consultar_vendes();

    /** @brief escriu els valors del vaixell i els viatges, en ordre cronològic.
     * 
    */
    void escriure_vaixell();
};

