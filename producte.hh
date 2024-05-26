using namespace std;

/** @brief Classe que representa un producte del comerç del riu.
 * 
*/
class Producte{

    private:
    /** @brief Atribut que correspon al pès del producte.
     * 
    */
    int pes;

    /** @brief Atribut que correspon al volum del producte.
     * 
    */
    int volum;

    public:
    //constructor
    /** @brief Constructor per defecte de la classe producte. 
     * 
    */
    Producte();

    /** @brief construeix un producte amb un cert pès i volum
     * @pre Ambdós paràmentres explícits són enters positius
     * @post Es declara i inicialitza el paràmetre implícit amb
     * els atributs explícits.
    */
    Producte(int p, int v);

    //Consultors
    /** @brief Retorna el pes del producte.
     * @pre Cert.
     * @post Es retorna el valor corresponent al pes del paràmetre implícit.
    */
    int consultar_pes() const;

    /** @brief Retorna el volum del producte
     * 
    */
    int consultar_volum() const;

};