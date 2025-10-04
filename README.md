Introducción

Este proyecto consiste en la creación de una aplicación de red de aeropuertos que simula una red real. Tiene como objetivo proporcionar servicios tanto para viajeros como para el personal de seguridad; por ejemplo, la capacidad de gestionar reservas en vuelos y ofrecer a los clientes opciones para viajar desde un origen a un destino con diversas escalas y aerolíneas.
Para esto, tuvimos que identificar los tipos de datos y algoritmos que necesitamos para su resolución, llevando a cabo investigaciones, y decidimos lo conveniente según ventajas y desventajas, dándole importante a la claridad de los mismos y a la complejidad temporal.

Modelado del problema

Hay una clase aeropuerto, (donde guardamos la información del aeropuerto, nombre, ciudad y país), y una clase red aeropuerto, que dentro tiene una clase vuelos.
En vuelos se guarda la distancia, si es de cabotaje y todas las aerolíneas con sus asientos totales.
En la clase red aeropuertos tenemos un grafo, que conecta todos los aeropuertos identificados por su id (un entero), y sus arcos son de la clase vuelos; un vector, de la clase aeropuerto donde guardamos la información de cada aeropuerto relacionada con su id, y un mapa anidado map<int,map<int,map<string,int>>> donde el primer entero es la id del aeropuerto origen, el segundo entero es el destino, el string la aerolínea, y el tercer entero la cantidad de asientos reservados.
También llevamos la cuenta de la cantidad de aeropuertos con un entero.
El vector y el mapa lo que nos permiten es acceder fácilmente a la información, reduciendo la complejidad temporal.

Implementación de los servicios 1 y 2

Servicio 1:
Dentro de la clase usamos el existevuelo() para ver si hay vuelos disponibles y lo mismo para los asientos. Le envío el origen y el destino y me dice si para ese viaje con esa aerolínea cuantos asientos hay, si no existe la aerolínea devuelve un -1.
Asientos disponibles obtiene la cantidad de asientos libres en el vuelo para esa aerolínea lo que hace es obtener el costo del arco perteneciente a la clase vuelo (con obtenerVuelos), si no existe el arco directamente no existe un vuelo entre los aeropuertos. En la clase vuelos además hay una función que determina si existe la aerolínea, buscando en el mapa de aerolíneas.
Si existe la aerolínea, guarda los asientos totales en una variable. Usamos una función existeReserva, si la reserva existe busca en el mapa los asientos reservados y se la resta a los totales y sino devuelve los asientos totales. La complejidad es O(log n), donde n es el número de elementos en los mapas utilizados en las búsquedas.

Servicio 2:
Usamos el algoritmo DFS modificado para hallar los caminos entre un vértice y otro, en el que llevamos la cuenta de los km y usamos una variable string aerolínea en la que para el primer vértice, si aerolíneas es vacío prueba  con todas las aerolíneas posibles que hay entre el aeropuerto origen y su adyacente, que luego se mantiene para los próximos aeropuertos que visita.
 
1. Inicio en el aeropuerto de origen: Comienza el DFS en el aeropuerto de origen.
2. Visita y marca el aeropuerto actual: Marca el aeropuerto actual como visitado.
3. Verificación del aeropuerto de destino: Verifica si el aeropuerto actual es igual al aeropuerto de destino. Si es así, has encontrado un camino y se detiene el DFS.
4. Exploración de vecinos: Elige un vecino no visitado, el cual tenga asientos disponibles de la aerolínea actual y repite los pasos 2-3 para este nuevo aeropuerto. Este proceso continúa de manera recursiva o mediante una pila hasta que se alcance el aeropuerto de destino o no haya más vecinos no visitados.
5. Retroceso: Cuando no hay más vecinos no visitados desde el aeropuerto actual, retrocede al aeropuerto anterior.
6. Repetición o finalización: Repite los pasos 2-5 hasta que encuentres el aeropuerto de destino o hasta que todos los aeropuertos alcanzables desde el aeropuerto de origen hayan sido visitados.
El algoritmo se detiene cuando alcanza el aeropuerto destino, y el camino se agrega a una lista de listas con la cantidad de kilómetros recorridos y la aerolínea. Su complejidad es O(max(vértices,arcos, aerolíneas)).

Resolución Servicio 3

Alternativas para resolverlo con sus ventajas y desventajas

Algoritmos de Fuerza Bruta:
Implementación: Relativamente simple de llevar a cabo, pero carece de eficiencia en términos de velocidad de ejecución.
Limitaciones: No es práctico para resolver problemas con un gran número de elementos debido a su complejidad factorial.
Ventajas: Siempre encuentra la solución óptima, aunque a un costo alto en términos de tiempo.
Contexto de aplicación: Adecuado para instancias pequeñas del problema en las que la eficiencia no es una preocupación crítica.

Algoritmos Heurísticos:
Implementación: Más eficientes que la Fuerza Bruta, pero no garantizan la solución óptima.
Limitaciones: La solución encontrada puede ser subóptima en algunos casos.
Ventajas: Son adecuados para abordar problemas con un gran número de elementos, ya que proporcionan soluciones aceptables en un tiempo razonable.
Contexto de aplicación: Ampliamente utilizados en aplicaciones prácticas, como la resolución de Problemas del Vendedor Viajero (TSP) en logística y planificación de rutas.

Algoritmos Aproximados:
Implementación: Generalmente eficientes y fáciles de implementar.
Limitaciones: La calidad de la solución puede variar según el algoritmo específico utilizado.
Ventajas: Ofrecen soluciones razonables en tiempos razonables, lo que los hace adecuados para problemas de tamaño mediano a grande.
Contexto de aplicación: Son ampliamente empleados en aplicaciones prácticas donde la optimización exacta no es una necesidad absoluta.

Luego de repasar todas las alternativas, optamos por emplear el algoritmo de fuerza bruta, específicamente el método de backtracking, ya que priorizamos encontrar la solución óptima por sobre su costo.
Este algoritmo funciona de la siguiente manera:
1. Elección del aeropuerto inicial: se elige un aeropuerto inicial desde el cual comenzar el recorrido.
2. Exploración de posibles soluciones: el algoritmo explora todas las posibles combinaciones de aeropuertos en busca de la solución óptima. Comienza con el aeropuerto inicial y considera todos los aeropuertos adyacentes como el siguiente aeropuerto a visitar.
3. Criterio de validez: antes de avanzar al siguiente aeropuerto, se verifica si la elección actual es factible, esto significa asegurarse de que el aeropuerto no haya sido visitado previamente en la ruta actual y que la longitud total del recorrido parcial es menor que la longitud del mejor recorrido encontrado hasta el momento.
4. Volver atrás: si en algún punto se determina que la solución parcial actual no puede llevar a una solución óptima, el algoritmo retrocede a la elección anterior y realiza una nueva elección. Esto implica deshacer la última decisión y explorar otras posibilidades.
5. Condición de terminación: el algoritmo continúa explorando y retrocediendo hasta que se han explorado todas las posibles combinaciones de ciudades o se alcanza una condición de terminación específica. La condición de terminación es haber visitado todos los aeropuertos y regresar al aeropuerto inicial.
Registro del mejor resultado: Durante la exploración, se mantiene un registro del mejor resultado encontrado hasta el momento. Esto permite mantener un seguimiento de la solución óptima a medida que el algoritmo avanza.
También se incorporó un dataset modificado para que este servicio pueda brindar una solución.

Seguimiento:

Seguimiento de servicio 3, con un grafo de ejemplo y su árbol de recursión.

Explicación funcionamiento de aplicación
La aplicación presenta un menú con 5 opciones más la de salir del programa. Según lo que el usuario quiera hacer, selecciona una opción y sigue los pasos que se van mostrando por pantalla de manera clara para que cualquiera pueda entenderlo. Una vez que el usuario termina, guarda un archivo .txt con los datos recién modificados por el mismo. Para el servicio 1, por ejemplo se genera un archivo llamado “servicio_1.txt”, de la misma manera para los servicios 2 y 3.

Conclusiones

En este proyecto, hemos tenido la oportunidad de ampliar nuestros conocimientos y habilidades en el desarrollo de servicios eficaces para resolver problemas del mundo real. Hemos implementado soluciones utilizando objetos y algoritmos para atender tanto a los viajeros como a los organismos de seguridad, teniendo en cuenta factores como rutas, aeropuertos y disponibilidad, así como otras restricciones relevantes.
Este proyecto ha sido una valiosa oportunidad para aplicar la teoría que hemos aprendido en las clases, pero acá de manera práctica y en un contexto interesante. Esto nos ha permitido profundizar nuestra comprensión de los algoritmos que estudiamos, como el recorrido de grafos, DFS, backtracking, entre otros. Además, hemos adquirido experiencia en la utilización de iteradores, bibliotecas, clases y estructuras de datos como lo son los mapas, lo que ha facilitado la modelización y organización de nuestro trabajo. Además de algunas permitir mejorar la complejidad temporal.

