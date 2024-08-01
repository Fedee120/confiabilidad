# Confiabilidad de Redes Eléctricas mediante Simulación Monte Carlo

Este repositorio contiene el código para evaluar la confiabilidad de redes eléctricas modeladas como grafos, utilizando simulaciones de Monte Carlo. El objetivo es calcular la probabilidad de que la red esté en estado de falla, es decir, que no sea conexa. Para esto se utilizan simulaciones multihiladas con técnicas de robo de trabajo.

## Estructura del Proyecto

- `data/`: Contiene los archivos CSV con la definición de los grafos.
- `include/`: Archivos de cabecera (.hpp) del proyecto.
- `src/`: Implementaciones de las clases y funciones principales.
- `tests/`: Archivos de prueba para verificar la funcionalidad del código.
- `obj/`: Archivos objeto generados durante la compilación.

## Dependencias

- Compilador compatible con C++11 (GCC, Clang).
- `make` para la compilación.

## Compilación

Para compilar el proyecto, ejecute los siguientes comandos:

```sh
make clean
make
```

## Uso
El ejecutable principal requiere cuatro argumentos: el archivo CSV con el grafo, el número de muestras, el número de hilos y el número de experimentos.

```sh
./obj/main <csv_file> <num_samples> <num_threads> <num_experiments>
```

### Ejemplo

```sh
./obj/main data/54-nodes.csv 100000 8 10
```

## Descripción de los Archivos Principales
- `src/main.cpp`: Implementa la función principal que ejecuta los experimentos de simulación.
- `include/GraphLoader.hpp` y `src/GraphLoader.cpp`: Carga grafos desde archivos CSV.
- `include/MonteCarloSimulator.hpp` y `src/MonteCarloSimulator.cpp`: Implementa la simulación de Monte Carlo para evaluar la confiabilidad de la red.
- `include/ThreadManager.hpp` y `src/ThreadManager.cpp`: Gestiona la ejecución concurrente de las simulaciones.
