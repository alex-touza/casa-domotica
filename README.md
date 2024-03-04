# Casa domòtica

## Estructura

### [build_script](./build_script)

Script de còpia i processament del projecte per al seu ús a Arduino IDE. Vegeu [Execució](#execució).

### [diagrams](./diagrams)

Diagrames [PlantUML](https://plantuml.com/) del projecte:

- Diagrama de classes
- Diagrama de seqüència

### [lib](./lib)

Carpeta arrel de les llibreries. Vegeu [Dependències](#depèndencies).

### [src](./src)

Codi font.

## Depèndencies

- AdaFruit Unified Sensor
- DHT sensor library
- FastLED
- LiquidCrystal_I2C

El codi font d'aquestes llibreries es troba a la carpeta [`~/lib`](./lib).

## Requeriments
- Python 3.11 o superior
  - [`colorama`](https://pypi.org/project/colorama/)
- Arduino IDE

## Execució

1. Copieu el contingut de `~/lib` a la carpeta corresponent d'Arduino (e.g. `Arduino/libraries`) perquè el projecte
   compili correctament.
2. Executeu [`~/build_script/main.py`](./build_script/main.py). Comproveu que teniu el paquet `colorama` instal·lat.
3. 

## Autors

- Gisele Jaccottet
- Àlex Touza