# ✈️ Red de Aeropuertos – Simulación y Servicios

## 📌 Introducción
Este proyecto consiste en la creación de una aplicación que simula una **red de aeropuertos reales**.  
Su objetivo es proporcionar servicios tanto para **viajeros** como para el **personal de seguridad**, tales como:
- Gestión de reservas de vuelos.  
- Búsqueda de rutas desde un origen a un destino con **escalas** y diferentes **aerolíneas**.  

Para resolverlo, se identificaron los tipos de datos y algoritmos necesarios, investigando y seleccionando las alternativas más convenientes en términos de **claridad** y **complejidad temporal**.

---

## 🏗️ Modelado del problema
El proyecto se organiza en varias clases:

- **Clase Aeropuerto**  
  Contiene la información de cada aeropuerto: nombre, ciudad y país.  

- **Clase Vuelos**  
  Incluye:  
  - Distancia del vuelo.  
  - Si es de cabotaje o no.  
  - Aerolíneas con sus asientos totales.  

- **Clase RedAeropuertos**  
  - Grafo que conecta los aeropuertos (identificados por ID entero).  
  - Vector de aeropuertos con su información.  
  - Mapa anidado `map<int,map<int,map<string,int>>>` para reservas:  
    - Clave 1: id aeropuerto origen.  
    - Clave 2: id aeropuerto destino.  
    - Clave 3: aerolínea.  
    - Valor: cantidad de asientos reservados.  
  - Entero que lleva la cuenta de aeropuertos totales.  

👉 Esta estructura permite acceso rápido a la información y optimiza la complejidad temporal en consultas y actualizaciones.

---

## 🛠️ Implementación de Servicios

### 🔹 Servicio 1: Gestión de reservas
- Se usa `existeVuelo()` para verificar si existe un vuelo entre dos aeropuertos y cuántos asientos tiene disponibles por aerolínea.  
- Se utiliza `existeReserva` para consultar si ya hay reservas previas y calcular los asientos libres.  
- Complejidad: **O(log n)** (búsquedas en mapas).  

### 🔹 Servicio 2: Búsqueda de rutas
- Se emplea un **DFS modificado** para encontrar caminos entre un origen y un destino.  
- El algoritmo mantiene la aerolínea seleccionada desde el primer tramo y verifica asientos disponibles en cada paso.  
- Se exploran caminos válidos hasta alcanzar el destino.  
- Complejidad: **O(max(vértices, arcos, aerolíneas))**.  

### 🔹 Servicio 3: Optimización de rutas
Se evaluaron distintos enfoques:  

- **Fuerza bruta**  
  - ✅ Encuentra siempre la solución óptima.  
  - ❌ Complejidad factorial (no escalable).  

- **Heurísticos**  
  - ✅ Rápidos para problemas grandes.  
  - ❌ Pueden dar soluciones subóptimas.  

- **Algoritmos aproximados**  
  - ✅ Eficientes y fáciles de implementar.  
  - ❌ La calidad de la solución depende del método.  

📌 Finalmente se eligió **backtracking (fuerza bruta con poda)**, priorizando exactitud sobre eficiencia.  
- Se exploran todas las combinaciones posibles de aeropuertos.  
- Se descartan rutas que superan el mejor recorrido encontrado.  
- Se registra la solución óptima al finalizar.  
- Se usó un **dataset modificado** para este servicio.  

---

## 📋 Funcionamiento de la aplicación
La aplicación cuenta con un **menú de 5 opciones** más la de salir.  
- Según el servicio seleccionado, el usuario ingresa los datos requeridos y se generan archivos `.txt` con los resultados:  
  - `servicio_1.txt`  
  - `servicio_2.txt`  
  - `servicio_3.txt`  

De esta manera se almacena la información procesada de manera clara y reutilizable.  

---

## ✅ Conclusiones
Este proyecto permitió:  
- Implementar soluciones usando **objetos** y **algoritmos** aplicados a un problema del mundo real.  
- Poner en práctica conceptos como **recorridos en grafos, DFS, backtracking, iteradores, bibliotecas y estructuras de datos (mapas, vectores, grafos)**.  
- Desarrollar una aplicación orientada a la eficiencia temporal y a la claridad en el modelado.  

La experiencia fue valiosa para consolidar conocimientos de **estructuras de datos y algoritmos**, y a la vez simular un sistema práctico que atiende a las necesidades de **viajeros y seguridad aeroportuaria**.

---
