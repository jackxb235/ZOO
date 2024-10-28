#include <iostream>
#include <array>

// Na prednáške hovoril, že toto používať radšej nemáme. V opačnom prípade by z celého kódu zmizli "std::"
//using namespace std;

//--- Datové typy ---//
/*
    int         -   celé čísla
    char        -   znaky
    string      -   textové reťazce
    bool        -   pravdivostná hodnota (true/false)
    double      -   desatinné čísla
    float       -   desatinné čísla
*/


class Class1{       //Vedľajšia trieda
private:

    int m_classId;              //atributy triedy
    std::string m_className;

    static int s_pocitadlo;     //statický atribut, ktorý je viazaný na triedu, nie na objekt

public:

    Class1(){                   //bezparametrický konstruktor
        m_classId = 0;          //vynulovanie hodnôt
        m_className = "";

        Class1::s_pocitadlo++;  //zvýšenie počítadla
    }

    Class1(int id, std::string name){   //parametrický konštruktor
        m_classId = id;                 //nastavenie hodnôt
        m_className = name;

        Class1::s_pocitadlo++;          //zvýšenie počítadla
    }

    ~Class1(){                      //destruktor   - označuje to symbol '~' na začiatku
        Class1::s_pocitadlo--;      //zníženie počítadla
    }

    int getId(){                //vráti m_classId;
        return m_classId;
    }

    std::string getName(){      //vráti m_className
        return m_className;
    }

    static int getPoc(){        //vráti počet objektov Class1
        return s_pocitadlo;
    }

    void setId(int id){         //nastaví m_classId
        m_classId = id;
    }

    void setName(std::string name){ //nastaví m_className
        m_className = name;
    }

    void printAll(){            //výpis
        std::cout << m_classId << " - " << m_className << std::endl;
    }

};

class Class2{   //hlavná trieda
private:

    int m_id;               //atributy
    std::string m_name;

    std::array<Class1*, 10> Classes;    //pole objektov Class1, kapacita nastavená na 10

public:

    Class2(){                           //bezparametrický konstruktor
        m_id = 0;
        m_name = "";

        for ( Class1* &c:Classes ){     //vynulovanie poľa
            c = nullptr;
        }

    }

    Class2(int id, std::string name){   //parametrický konstruktor
        m_id = id;
        m_name = name;

        for ( Class1* &c:Classes ){     //vynulovanie poľa
            c = nullptr;
        }

    }

    int getId(){            //vráti m_id
        return m_id;
    }

    std::string getName(){  //vráti m_name
        return m_name;
    }

    void addCont(Class1* C1){       //pridá objekt Class1 do poľa
        for ( Class1* &c:Classes ){     //prechádza celé pole
            if ( c == nullptr ){        //kontrola prázdneho prvku
                c = C1;                 //nastavenie nového objektu
                std::cout << "Vlozeni uspesne" << std::endl;
                return;     //ukončenie funkcie
            }
        }
        std::cout << "Pole je plne" << std::endl;   //ak prejde celé pole a nenájde voľné miesto
    }

    void delCont(Class1* C1){       //vymaže objekt z poľa
        for ( Class1* &c:Classes ){     //prechádza celé pole
            if ( c == C1 ){             //hľadá určený objekt
                delete C1;              //vymaže prvok
                c = nullptr;            //odstráni prvok zo zoznamu
                std::cout << "Vymazani uspesne" << std::endl;
                return;     //ukončenie funkcie
            }
        }
        std::cout << "Objekt nenalezen" << std::endl;   //ak prejde ceclé pole a nenájde zadaný objekt
    }

    void printAttr(){       //výpis atribútov objektu
        std::cout << m_id << " - " << m_name << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    void printCont(){       //výpis obsahu poľa
        for ( Class1* &c:Classes ){ //prechádza celé pole
            if ( c != nullptr ){    //ak sa nejedná o prázdnu položu, vykoná výpis objektu
                c->printAll();
            }
        }
    }

    void printAll(){        //celkový výpis, volá predchádzajúce funkcie pre jednoduchosť
        printAttr();
        printCont();
    }

};

int Class1::s_pocitadlo = 0;    //nastavenie počítadla objektov Class1
                                //funguje iba ak sme s_pocitadlo nastavili ako static

int main() {

    int id;
    std::string name;

    std::cout << "Zadejte ID objektu" << std::endl;
    std::cin >> id;             //načítanie z klávesnice do id
    std::cout << "Zadejte nazev objektu" << std::endl;
    getline(std::cin, name);    //spracuje iba znak konca riadku za zadaným ID
    getline(std::cin, name);    //načíta z klávesnice názov do name

    Class2* C2 = new Class2(id, name);        //vytvorenie hlavného objektu

    std::cout << "Pocet Class1: " <<Class1::getPoc() << std::endl;  //výpis počtu objektov Class1

    Class1* C1 = new Class1(1, "Vedlejsi objekt 1");    //vytvorenie nových vedľajších objektov
    Class1* C3 = new Class1(1, "Vedlejsi objekt 2");

    C2->addCont(C1);            //vloženie objektov C1, C3 do poľa objektov C2
    C2->addCont(C3);

    std::cout << "Pocet Class1: " <<Class1::getPoc() << std::endl;      //počítadlo

    C2->printAll();             //celkový výpis objektu C2 vrátane poľa

    C2->delCont(C1);            //odstránenie objektu C1
                                //tu je objekt C1 už nepoužiteľný, pretože ho vymažeme aj z pamäti
    std::cout << "Pocet Class1: " <<Class1::getPoc() << std::endl;      //počítadlo
    C2->printAll();             //celkový výpis objektu C2 vrátane poľa

    return 0;
}

//--- Syntax príkazov ---//
/*          CYKLUS WHILE
    while ( i < 10 ){        //v zátvorkách nejaká podmienka, ak platí, vykonajú sa príkazy vo vnútri
        ........             //napr. 'i < 10'  i musíme nastaviť pred cyklom a v cykle ho musíme meniť
        i++; //zvýši hodnotu o 1
    }
*/
/*          CYKLUS FOR
    for ( int i = 0; i < 10; i++ ){     //fungujú rovnako, ak je podmieka splnená, vykonávajú sa príkazy
        ........
    }
*/
/*          PODMIENKA IF
    if ( podmienka ) {       //ak podmienka platí, vykonajú sa príkazy v  { }
        .......              //v podmienke môžu byť logické operátory '&&' (logický and) a '||' (logický or)
    }
    else {                   //ak podmienka splnená nie je, vykonajú sa tieto príkazy
        .......              //vetva else nie je vždy potrebná, niekedy ale áno
    }
*/

