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

El codi font d'aquestes llibreries es troba a la carpeta [`/lib`](./lib).

## Requisits
Per a enviar el codi a la placa, es pot usar tant PlatformIO com Arduino IDE.

Si useu Arduino IDE, primer heu de fer que el codi sigui compatible. L'execució de l'script de processament necessita Python 3.11 o superior
amb el paquet [`colorama`](https://pypi.org/project/colorama/) instal·lat.

També es recomana tenir l'extensió de [PlatformIO](https://platformio.org/) instal·lada al vostre IDE per poder gaudir d'autocompletat amb
les llibreries d'ESP32 i de `/lib`.

## Execució
### Amb PlatformIO (recomanat)
Si useu PlatformIO, n'hi ha prou amb executar la commanda corresponent. Si no teniu accés a la vostra placa, podeu usar PlatformIO igualment per
comprovar que el codi compila, ja que aquest és molt més ràpid que Arduino IDE.

### Amb Arduino IDE
1. Copieu el contingut de `/lib` a la carpeta corresponent d'Arduino (e.g. `Arduino/libraries`) perquè el projecte
   compili correctament.
2. Instal·leu la placa ESP32 a Arduino IDE.
3. Executeu [`/build_script/main.py`](./build_script/main.py) i seguiu les instruccions. Comproveu que teniu el
   paquet `colorama` instal·lat. Alternativament, també podeu descarregar una distribució del projecte des de Releases.
4. Obriu la carpeta `/dist/casa-domotica` a Arduino IDE i compileu.

## Autors

- Gisele Jaccottet
- Àlex Touza
