#ifndef AEROPUERTO_H_INCLUDED
#define AEROPUERTO_H_INCLUDED
#include <string>
using namespace std;


class Aeropuerto
{
public:
    Aeropuerto();
    Aeropuerto(string nombre, string ciudad, string pais);
    string  Nombre() const;
    string Ciudad() const;
    string Pais() const;


private:
    string nombre;
    string ciudad;
    string pais;
};

Aeropuerto::Aeropuerto()
{
}

Aeropuerto::Aeropuerto(string nombre, string ciudad, string pais)
{
    this->nombre=nombre;
    this->ciudad=ciudad;
    this->pais=pais;
}

string Aeropuerto::Nombre() const{
    return this->nombre;
}

string Aeropuerto::Ciudad() const{
    return this->ciudad;
}

string Aeropuerto::Pais() const{
    return this->pais;
}

#endif // AEROPUERTO_H_INCLUDED
