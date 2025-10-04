#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <map>
#include <cassert>

using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolver_adyacente() const;
		const C & devolver_costo() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const;

	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const;

	bool existe_vertice(int vertice) const;

	bool existe_arco(int origen, int destino) const;

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const;

	void devolver_vertices(list<int> & vertices) const;

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;

	void agregar_vertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino);

	void vaciar();

private:
	map <int, map <int, C > > grafo;

}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco()
{

}

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    this->vertice=adyacente;
    this->costo=costo;
}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const
{
    return this->vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const
{
    return this->costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    grafo = otroGrafo.grafo;
}

template <typename C> Grafo<C>::~Grafo()
{
    vaciar();
}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    if (this != &otroGrafo)
    {
        grafo = otroGrafo.grafo;
    }
    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const
{
    return grafo.empty();
}

template <typename C> int Grafo<C>::devolver_longitud() const
{
    return grafo.size();
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{
    return grafo.find(vertice) != grafo.end();
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{
    auto it= grafo.find(origen);
    if (it!=grafo.end()){
        if (it->second.find(destino) != it->second.end()) {
            return true;
        }
    }else
    return false;
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{
    assert(existe_arco(origen, destino));
    auto it = grafo.find(origen);
    auto it2 = it->second.find(destino);
    return it2->second;
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
    auto it= grafo.begin();
    while(it != grafo.end()) {
        vertices.push_back(it->first);
        it++;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    auto it= grafo.find(origen);
    if (it !=grafo.end()){
        auto it2= it->second.begin();
        while (it2 != it->second.end()){
            adyacentes.push_back(Arco(it2->first,it2->second));
            it2++;
        }
    }
}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
    if (!existe_vertice(vertice)){
        grafo[vertice] = map<int, C>();
    }
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    grafo.erase(vertice);
    auto it= grafo.begin();
    while (it != grafo.end()){
        it->second.erase(vertice);
        it++;
    }
}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
    assert(existe_arco(origen, destino));
    agregar_arco(origen,destino,costo);
}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
    assert(existe_vertice(origen) && existe_vertice(destino));
    grafo[origen][destino] = costo;
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    if (existe_arco(origen,destino)){
        grafo[origen].erase(destino);
    }
}

template <typename C> void Grafo<C>::vaciar()
{
    grafo.clear();
}

#endif /* GRAFO_H_ */
