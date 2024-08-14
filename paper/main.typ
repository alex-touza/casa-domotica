#import "template.typ": *
#import "@preview/codelst:2.0.0": sourcecode
#import "@preview/treet:0.1.0": *

#set text(lang: "cat")

#show link: underline

#show: project.with(
  title: "Casa domòtica",
  authors: (
    (name: "Gisele Jaccottet Lopes Pires Ferreira", year: "1r Batxillerat A", email: "06gjaccottet@insernestlluch.cat"),
    (name: "Àlex Xavier Touza Luque", year: "1r Batxillerat B", email: "07atouz@insernestlluch.cat"),
  ),
  date: "17 d'abril de 2024",
  organisation: "Institut Ernest Lluch\nCurs 2023-2024",
  logo: "tot.JPG"
)

#show "Casa domòtica": smallcaps
#show "C++": t => [#set text(weight: "bold", hyphenate: false);#box("C++")]
#show "ArduinoBlocks": t => [#set text(hyphenate: false);#box("ArduinoBlocks")]

#show <screen>: t => [#set text(font: "New Computer Modern Mono");#box(fill: rgb(184, 215, 68), [#t])]













= Objectius
== Problema a resoldre
Per a aquest projecte, el problema que ens va ser proposat va ser desenvolupar un habitatge domòtic fent servir la placa ESP32 SteamMakers. En aquesta habitació, vam haver de dissenyar sistemes de control de les condicions ambientals, de seguretat, i d'il·luminació de la mateixa.

== Reptes
El primer repte consistia a designar els intervals recomanats de condicions de temperatura i d'humitat, a més de, fent servir dos LEDs de la tira de neopixel i el sensor DHT11, fer un sistema de control de la temperatura i de la humitat basat en aquests intervals. Els colors verd i groc del LED indiquen que la temperatura o la humitat estan dins dels valors assignats. Ara, el color vermell dels LEDs indica que la temperatura o la humitat no estan dins dels valors assignats.

El segon repte ens demanava que indiquéssim a la pantalla LCD els valors de la temperatura i de la humitat de dins de l'habitatge llegits pel sensor, a més de la temperatura consigna designada.

El tercer repte proposa que fem servir un tercer LED per a controlar la climatització de l'habitatge. D'aquesta manera, si a temperatura de l'habitatge no és la consigna, hauríem d'encendre o la calefacció o la ventilació. Si el LED està blau, s'encén l'aire condicionat, ja que la temperatura seria més alta que la que es vol. Ara, si el LED està vermell, s'encén la calefacció, perquè la temperatura estaria més baixa que el mínim permès. A més, fent servir el Joystick, es pot canviar la temperatura que es vol que tingui l'habitatge.

El quart repte consistia a desenvolupar un sistema d'alarma, fent servir un polsador, un sensor detector d'obstacles, i dos altres LEDs de la tira. Aleshores, quan el sensor detectés alguna cosa, els dos LEDs brillarien en vermell intermitent.

El cinquè repte ens demanava que incorporéssim un sistema de ventilació per a disminuir la temperatura de l'habitatge quan sigui necessari. Es disposava d'un motor DC i d'una controladora L298N per a fer-ho.

El sisè repte proposava la implementació d'un sistema d'il·luminació fent ús d'un comandament i sensor IR, a més dels últims tres LEDs de la tira neopixel.

A més dels reptes demanats, hem fet diverses ampliacions, explicades a l'apartat Característiques.

== Metodologia
Com dit anteriorment, la placa que vam fer servir per a aquest projecte va ser l'ESP32 SteamMakers. 

Aquesta placa té la disposició dels seus pins com una placa Arduino Uno. Aquests pins són d'una varietat impressionant (mascles i femelles, analògics i digital) per a connectar pantalles, dispositius i2c, entre altres.

A més, la placa compta amb connectivitat WiFi, Bluetooth, un sòcol per a targetes microSD, un microcontrolador molt potent, i molta memòria.

El llenguatge que vam fer servir per a programar aquesta placa va ser el C++ en l'Arduino IDE, però també es podria fer servir un llenguatge de blocs utilitzant l'ArduinoBlocks.
#figure(
  image("esp32steammaker.png", height: 200pt)
)

= Disseny del projecte
== Característiques
_Alarma._ La casa compta amb una alarma que s'activa quan el detector d'obstacles envia un senyal. Dos LEDs vermells parpadegen i la pantalla mostra un missatge fins que es premi el polsador corresponent per a apagar l'alarma.

_Il·luminació._ L'habitatge disposa d'un sistema d'il·luminació, en el qual vam fer servir un polsador per a activar-lo i el joystick per a controlar la seva intensitat, ja que no hem pogut treballar amb el comandament a distància.

_Estacions de l'any._ La casa posseeix una eina de canvi d'estacions entre estiu i hivern. Cada època té un rang diferent de temperatura, per tant, quan es fa el canvi, els LEDs poden brillar d'un color diferent per la mateixa temperatura d'acord amb l'estació designada.

== Diagrama de flux
#figure(
  image("flux.jpg")
)
Podeu veure el diagrama de flux complet #link("https://github.com/alex-touza/casa-domotica/blob/master/diagrams/flux.png", "aquí").

= Muntatge
En el nostre procés de muntatge, vam seguir l'ordre dels reptes proposats i el muntatge de cadascun va trigar entorn de dues o tres classes, depenent dels contratemps que encontréssim.

Per exemple, el repte el qual vam trigar més temps a desenvolupar va ser el repte sis, ja que vam trobar problemes amb el funcionament del motor DC.

A més, va haver-hi entorn de dues classes que vam perdre perquè la nostra placa ha deixat de funcionar misteriosament.

No obstant això, no vam trobar cap problema relatiu a la connexió dels components.

= Electrònica
== Components
Per a executar les tasques que ens van ser proposades i les nostres ampliacions, vam fer servir diversos components que ens estaven disponibles.

#table(
  columns: (auto, auto, 1fr),
  align: horizon,
  stroke: 0pt,
  [*Component*], [*Descripció*], [*Imatge*],
  "Cable USB", "Connexió entre la placa i l'ordinador", image("cableUSB.jpg", height: 150pt),
  "Cable dupont", "Connexió entre components", image("cable2.jpg", height: 150pt),
  "Sensor DHT11", "Sensor d'humitat i temperatura", image("sensorDHT11.jpg", height: 150pt),
  "Tira LED NeoPixel", "Tira amb vuit LEDs, els quals es 
poden controlar el color i la intensitat", image("tiraLEDneopixel2.jpg", height: 150pt),
  "Pantalla LCD I2C", "Pantalla de cristall líquid", image("pantalla.jpg", height: 150pt),
  "Joystick analògic", "Controlador amb dos eixos 
ortogonals acoblats a dos 
potenciòmetres", image("jostick.jpg", height: 150pt),
  "Polsador","Aparell de commanament que 
permet el pas del corrent quan
accionat", image("polsador.jpg", height: 150pt),
  "Detector d'obstacles", "Sensor detector d'obstacles", image("detectordobstacles.jpg", height: 150pt),
  "Motor DC", "Motor que transforma l'energia
elèctrica en energia mecànica", image("motor.jpg", height: 150pt),
  "Controladora L298N", "Controladora del motor DC", image("controladoral298n.jpg", height: 150pt),
  "Bateria externa", "Font d'energia externa", image("bateria.jpg", height: 150pt),
  
)

== Connexions
// auto --> fixat al contingut
// 1fr --> omplir espai buit
#table(
  columns: (auto, auto),
  stroke: 0pt,
  [Pin], [Component],
  "IO05", "ENA - Controlador de motors L298N",
  "IO14", "Botó Joystick",
  "IO18", "Polsador LED",
  "IO16", "NeoPixel",
  "IO17", "Sensor detector d'obstacles",
  "IO19", "IN2 - Controlador de motors L298N",
  "IO23", "IN1 - Controlador de motors L298N",
  "IO25", "DHT11 - Sensor de temperatura i humitat",
  "IO26", "Polsador alarma",
  "IO34", "X - Joystick",
  "IO35", "Y - Joystick",
  "Bus I2C", "Pantalla LED I2C"
)
== Esquema electrònic
#figure(
  image("fritzing.jpg"),
)

= Programació
Aquest apartat explica amb summe detall les característiques de part informàtica del projecte.

== Llenguatge
El llenguatge de programació utilitzat per a aquest projecte ha estat C++, utilitzat àmpliament als sistemes incrustats (_embedded systems_). C++ és un llenguatge tipat estàticament, és a dir, el tipus de dada de cada variable no canvia, de manera que s'aconsegueix un codi més fàcil de mantenir.

Un gran avantatge de C++ respecte al seu predecessor, C, és la seva àmplia llibreria estàndard. Per desgràcia, aquesta no està disponible quan es programa en ESP32 o Arduino, i en conseqüència moltes de les tècniques de programació d'aquest projecte són pròpies del llenguatge C.

=== Característiques de C++

Aquí ennumerem algunes de les característiques de C++ que hem aprofitat i que ens han estat molt útils per al codi del projecte.

==== Manipulació de memòria
C++ és dels pocs llenguatges que ofereix un tipus de dada anomenat punter, que és una adreça de memòria on es situa una altra variable. Això permet crear codi molt eficient. Les _C-style arrays_, per exemple, que són l'única forma de fer una llista sense la llibreria estàndard de C++, utilitzen aritmètica de punters per ràpidament obtenir-ne un ítem.

==== Programació orientada a objectes
Aquest paradigma de programació és el més comú avui dia, i C++ ofereix tot el necessari per fer una bona estructura de classes. Com altres llenguatges com Java, té inherència, polimorfisme i encapsulació, així com classes abstractes (encara que d'una forma poc convencional)

=== Comparació de C++ amb ArduinoBlocks

Quant a l'experiència de programació, els beneficis d'utilitzar un llenguatge de programació textual respecte a un visual són molts. Aquí en destaquem dos:

#grid(columns: (60%, 1fr), gutter: 10pt, [
- *Escabilitat.* Si bé ArduinoBlocks pot ser útil per fer proves, un projecte major es pot veure restringit per les seves limitacions.
- *Llegibilitat.* L'única dificultat que podria sorgir en C++ seria entendre la sintaxis. En canvi, per molt que hom entengui la funcionalitat d'ArduinoBlocks, expressions que en C++ serien simples, es converteixen en grans conjunts de blocs de colors que es fan impossibles de llegir.
- *Usabilitat.* Els blocs són terribles.
- *Rendiment.* El rendiment de la interfície dels llenguatges de programació visual es redueix considerablement en projectes amb molts blocs. En canvi, amb C++, sent només text, grans quantitats de codi no solen alentir l'entorn en el qual es treballa.
], [
  #figure(caption: [Un comentari a ArduinoBlocks.], [#image("imatges/programació/comentari_arduinoblocks.png")])
  #figure(caption: [Un comentari a C++.], [#image("imatges/programació/comentari_cpp.png")])
])

Per altra banda, quant als aspectes tècnics, C++ presenta també moltes característiques molt útils:

- *Variables locals.* Les variables globals són mala pràctica, i per a ArduinoBlocks tot és global, ja que les variables es creen fora del propi codi. En canvi, a C++ totes les variables declarades a dins d'una funció són locals.
- *Diferents fitxers.* El codi de C++ es pot organitzar fàcilment en fitxers (encara que és més complicat que a altres llenguatges, vegeu la secció següent), però ArduinoBlocks no.
- *Programació orientada a objectes.* ArduinoBlocks no permet la creació de classes i objectes, però C++ té una robusta estructura de dades (vegeu la secció anterior)

De fet, ArduinoBlocks és només un envoltori a C++, és a dir, els blocs amaguen el codi real escrit en aquest llenguatge. Per tant, aquesta tecnologia ens pren la llibertat d'usar el llenguatge com considerem adequat.

== Entorn
Per programar al taller i enviar el codi a la placa, hem utilitzat Arduino IDE, ja que és l'opció més fiable.

Arduino IDE, però, no inclou les plaques d'ESP32 per defecte, així que s'han d'instal·lar manualment. Com que aquest procés és molt llarg, s'ha optat per utilitzar una versió portable d'Arduino IDE des d'un pen drive, de forma que només s'han hagut d'instal·lar les plaques una vegada. Per desgràcia, només les versions d'Arduino IDE 1.x (@arduinoide) tenen un mode portable, motiu pel qual hem trobat a faltar algunes característiques importants com el mode fosc o l'autocompletat, incloses només a versions posteriors.

#figure(caption: "Captura de pantalla de la versió d'Arduino IDE utilitzada al projecte.")[
#image("imatges/programació/arduino_ide.png", height: 300pt)
] <arduinoide>

Per millorar l'experiència de programació, s'ha fet servir l'IDE de C++ #link("https://www.jetbrains.com/clion/", "CLion"), de JetBrains. És de pagament, però inclou moltes més característiques que altres IDEs. A més, gràcies a la llicència gratuïta per estudiants (recordem que tothom qui tingui una adreça de correu de l'institut té accés gratuït a absolutament tots els programes de JetBrains), el cost ha estat zero per a nosaltres.

Per poder utilitzar l'autocompletat amb les llibreries, hem utilitzat #link("https://platformio.org/", "PlatformIO"), un _framework_ de programació de sistemes incrustats, perquè faci l'enllaçament del codi automàticament i es pugui compilar el codi sense una placa.

El problema d'utilitzar PlatformIO és que no reconeix el fitxers \*.ino. Per solucionar-ho, el projecte està estructurat perquè el _framework_ ho entengui (amb el fitxer `main.cpp`), i per provar el codi al taller, es converteix el codi i s'hi fan els canvis necessaris de forma automàtica amb un script de Python, que es pot trobar al directori `build_script`.

A més, utilitzar PlatformIO ens ha permès organitzar el codi en directoris, ja que per algun arcaic motiu, Arduino IDE no ho permet.

/*
#sourcecode[```cpp
#include <vector>
#include <queue>

using namespace std;

int n;
int s;

int main() {

    vector<vector<int>> g(n);
    vector<int> dist(n, -1);

    queue<int> q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u: g[v]) 
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        
    }
}
```]*/

== Estructura de dades <estructura_dades>
L'estructura de dades d'aquest projecte és la forma com estan organitzades i relacionades les classes.

Un projecte sense estructura de dades, l'estat del qual està controlat només per variables, pot semblar una opció atractiva en un inici per la seva facilitat de desenvolupament, però no és escalable. El motiu pel qual hem posat tanta èmfasi en aquest aspecte del projecte és assegurar que el seu codi sigui fàcil de mantenir, modificar i expandir.

=== Disseny
L'objectiu principal d'una estructura de dades és abstreure els processos d'ordre inferior en funcions i classes.

Hi ha principalment tres nivells d'abstracció a l'estructura de dades:


- *Codi principal.* El codi situat al fitxer `main.cpp`. (l'equivalent al fitxer \*.ino), on es creen i controlen les instàncies de les classes. Es divideix en tres parts: la creació dels objectes, la funció `setup()` i la funció `loop()`.
- *Components.* Components directament utilitzats al codi principal. La majoria són purs (i.e. funcionen de forma aïllada), però altres utilitzen punters a altres variables per sincronitzar l'estat entre si.
  - Dins el directori `pins`, es pot trobar una classe per a cada tipus de pin (totes derivades de la classe abstracta `Pin`), de les quals es deriven o composen totes les classes que utilitzin els pins sense una llibreria de tercers.
- *Utilitats.* S'utilitzen per abstreure processos més complicats. Són les classes `Range` i `LEDArray`.

=== Diagrama de classes

== Explicació del codi
A continuació s'explica el codi. Només s'explicarà allò rellevant per al funcionament del projecte. No es tractaran, per exemple, les funcions de preparació com `begin()`, que es troben a la majoria de les classes.

=== Utilitats
==== `Range`
Donat un real `n`, `Range` retorna un enter que representa els valors entre els quals es troba el real en la llista proporcionada a través del constructor. Per exemple:

$ "range" = {5, 7, 10, 15} -> "range"(7.5) = 2, "" "range"(4)=0, "" "range"(20)=4 $

El paràmetre `cycle` fa que l'enter retornat comenci i acabi en 0, de forma que a mesura que creix $n$, l'enter augmenti i un cop passada la meitat de la llista, disminueixi. Per tant, amb $n>=max("range") $ o $ n < min("range")$, es retorna 0.

#sourcecode[
  ```cpp
// helpers/Range.cpp

Range::Range(int _range[], int _size, bool _cycle) : range(_range), size(_size), cycle(_cycle) {}

// Obtenir posició de n dins el rang.
// cycle fa que comenci i acabi en 0:
// 0 1 2 3 4 vs 0 1 2 1 0
int Range::getLevel(double n) const {

    // Iterar sobre cada punt del rang
    for (int i = 0; i <= this->size; ++i) {
        
        // És el valor menor que el punt actual o
        // ja hem arribat al final?
        if (i == this->size || n < this->range[i]) {

            // S'ha activat el cicle i estem a la
            // segona meitat?
            if (this->cycle && i > this->size / 2) {
                return this->size - i;
            } else return i;
        }
    }

    Serial.println("Range getLevel() -1");

    return -1;
}

  ```
]

==== `LEDArray`
Un simple embolcall a una llista d'objectes `CRGB`, que són el color d'un pixel del NeoPixel. Té una funció que assigna un color a tots els LEDs de la llista.

#sourcecode[
  ```cpp
// helpers/LEDArray.cpp

LEDArray::LEDArray(CRGB** _leds, int _ledsSize) : leds(_leds), ledsSize(_ledsSize) {

}

void LEDArray::setColorAll(CRGB color) {
    for (int i = 0; i < this->ledsSize; ++i) {
        *this->leds[i] = color;
    }
}
  ```
]

=== Pantalla
El codi que fa funcionar la pantalla es troba als fitxers `Pantalla.h` i `Pantalla.cpp`.

Al _header_, primer, definim una estructura que contingui dos strings i declarem el seu comparador.

#sourcecode[
  ```cpp
// Pantalla.h

struct Lines {
    String upperLine;
    String lowerLine;

    bool operator==(const Lines& a) const;
};


  ```
]

Després, declarem la classe principal.

#sourcecode[
  ```cpp
// Pantalla.h

class Pantalla : private LiquidCrystal_I2C {
private:
    Temperatura* temp;
    Humitat* hum;
    Iluminacio* ilum;

    Timer timer;

public:
    Pantalla(Temperatura* _temp, Humitat* _hum, Iluminacio* _ilum);

    void begin();

    /*
     * forceRefresh: Força que la pantalla es refresqui encara que el contingut no canviï.
     *
     * Retorna true si la pantalla s'ha refrescat.
     */
    void update(const String& upperLine, const String& lowerLine, int id = -1, bool forceRefresh = false);

    void update(const Lines& _lines, int id = -1, bool forceRefresh = false);
    
    void updateTimed(const Lines& _lines, unsigned long t, int id = -1, bool forceRefresh = false);

    void idle();

    int screenId;

    Lines lines;
};
  ```
]

Com es pot veure al codi anterior, la pantalla té punters a objectes de tipus `Temperatura`, `Humitat` i `Iluminació`.

La pantalla funciona amb un sistema de IDs de pantalla, de forma que és ben senzill i eficient saber què està mostrant la pantalla en un moment donat. Cada vegada que s'utilitza una funció d'actualització, s'ha de proveïr un enter que representarà l'ID de la pantalla actual. Aquest ID es pot obtenir amb l'atribut públic `screenId`.

Això es fa encara més intuïtiu utilitzant un _enum_, que es defineix fora de la classe i es pot fer servir per comparar fàcilment pantalles.

#sourcecode[
  ```cpp
// main.cpp

enum Pantalles {
    ALT = -1,
    IDLE = 0,

    // Pantalles d'interacció
    TEMPSET = 1,
    LIGHTSET = 2,
    LIGHTOFF = 3,

    // Pantalles d'informació
    LIGHTTOGGLE = 4,
    ALARMACTIVE = 5,
    ALARMOFF = 6,
    SEASONSET = 7,
    TEMPRESET = 8
};


/* ... */

pantalla.update("Llums apagats", "", Pantalles::LIGHTOFF);

/* ... */

pantalla.update("Establint temp", /* ... */, Pantalles::TEMPSET);
  ```
]

Totes les funcions d'actualització acaben a cridant a una sola, definida de la següent forma:

#sourcecode[
  ```cpp
// Pantalla.cpp

void Pantalla::update(const String& upperLine, const String& lowerLine, int id, bool forceRefresh) {
    if (this->lines == Lines{upperLine, lowerLine} && !forceRefresh) return;
    this->timer.active = false;

    this->screenId = id;

    this->lines.lowerLine = lowerLine;
    this->lines.upperLine = upperLine;

    this->clear();
    this->setCursor(0, 0);
    this->print(upperLine);
    this->setCursor(0, 1);
    this->print(lowerLine);
}
  ```
]

`updateTimed()` només espera el temps demanat després de mostrar la pantalla per retornar-la a la pantalla per defecte:

#sourcecode[
  ```cpp
// Pantalla.cpp

void Pantalla::updateTimed(const Lines& _lines, unsigned long t, int id, bool forceRefresh) {
    this->update(_lines, id, forceRefresh);
    delay(t);
    this->idle();
}
  ```
]

=== Sensor DHT
El sensor DHT, com que mesura dues variables, la temperatura i l'humitat, està estructurada de forma que allò que s'hagi de fer amb les dues (com llegir-les) es fa des d'una classe parent, i a partir d'aquesta es fan l'especialitzacions necessàries (com actualitzar el LED de la consigna de temperatura).

Hi ha una classe abstracta `Sensor` declarada de la següent forma:

#sourcecode[
  ```cpp
// Pantalla.h

class Sensor {
private:
    CRGB* led;
protected:
    // No és un punter perquè pugui ser passat directament
    // com a paràmetre en lloc de ser creat amb una variable
    // temporal.
    Range range;
    // Processar un valor llegit des de la funció de la
    // classe filla.
    bool process(double _value, CRGB::HTMLColorCode colors[]);

public:
    Sensor(CRGB* _led, Range _range);
    virtual void begin() = 0;
    virtual bool read() = 0;

    double value;

    // Constructor simplificat de DHT
    static DHT initDHT(unsigned char _pin);

};
  ```
]

Noti's que per a crear una classe abstracta a C++, és suficient amb declarar alguna de les seves funcions com virtuals. En el cas de les funcions `begin()` i `read()`, són virtuals pures, perquè han de ser invalidades per una altra implementació en les classes (`virtual`) filles i no tenen cap definició per defecte (`= 0`).

Com que l'objecte que llegeix les dades és d'una llibreria de tercers, declarem una funció estàtica `initDHT()` que retorna un objecte `DHT`, en el qual s'ha de cridar la seva pròpia funció `begin()`.

La funció `process()` utilitza el rang i el LED que s'han passat al constructor i, donat un valor, mostra el color apropiat:

#sourcecode[
  ```cpp
// Sensor.cpp

bool Sensor::process(double _value, CRGB::HTMLColorCode colors[]) {
    this->value = _value;
  
    int level = this->range.getLevel(this->value);
  
    *this->led = colors[level];
  
    return true;
}
```
]

Considerem ara les classes `Temperatura` i `Humitat`, derivades de `Sensor`.

#sourcecode[
  ```cpp
// Temperatura.h
  
#define SEASONS 2
  
class Temperatura : public Sensor {
private:
    static int seasons[SEASONS][4];
    static CRGB::HTMLColorCode tempColors[];
    static CRGB::HTMLColorCode settingColors[];
  
    DHT* dht;
    CRGB* ledSetting;
    Motor* fan;
public:
    enum Seasons {
        SUMMER = 0,
        WINTER = 1
    };
  
    static String seasonsName[SEASONS];
  
    Temperatura(int initSetting, DHT* _dht, CRGB* _ledTemp, CRGB* _ledSetting, Motor* _fan);
  
    void begin() override;
  
    bool read() override;
  
    void setSeason(Seasons _season);
  
    Seasons season;
  
    int setting;


};
  ```
]

Aquí observem el comportament especialitzat de `Temperatura`, com les funcionalitats de la consigna (`setting`) i les èpoques de l'any (`season`, `setSeason`, etc).

A la implementació de `read()`, podem veure els processos anteriors a cridar la funció de la classe pare per actualitzar els LEDs:

#sourcecode[
  ```cpp
// Temperatura.cpp
  
bool Temperatura::read() {
    this->value = this->dht->readTemperature();
  
    int settingRangesList[] = {this->setting - 1, this->setting + 1};
    
    const Range& range = Range(settingRangesList, 2, false);
    
    int level = range.getLevel(this->value);
  
    *ledSetting = Temperatura::settingColors[level];
    
    int dif = (int)(round(this->value) - this->setting);

    if (dif > 0) {
        this->fan->setSpeed(map(constrain(dif, 0, 10), 0, 10, 100, 255));
    } else this->fan->off();
  
    return this->process(this->value, Temperatura::tempColors);
}
```
]
A `Humitat`, no hi ha cap especialització. Només es crida la funció `process()`.

#sourcecode[
  ```cpp
// Humitat.cpp

bool Humitat::read() {
    return this->process(this->value = this->dht->readHumidity(), Humitat::colors);
}
  ```
]

=== Il·luminació
La classe `Iluminacio` és derivada de `LEDArray`, ja que ha de fer brillar una sèrie de LEDs.
#sourcecode[
  ```cpp
// Iluminacio.h

class Iluminacio : private LEDArray {
protected:
    EntradaDigital button;
public:
  
    Iluminacio(int pinButton, CRGB** _leds, int _ledsSize);
  
    void begin();
    bool read();
    void changeBrightness(int delta);
    void update();
  
  
    bool isOn;
    int brightness;
  
    String brightnessStr() const;
};
  ```
]

La funció `changeBrightness()` modifica l'atribut `brightness` d'una forma controlada i crida `update()`.

#sourcecode[
  ```cpp
// Iluminacio.cpp

void Iluminacio::changeBrightness(int delta) {
    this->brightness += delta;
    this->brightness = constrain(this->brightness, 0, 255);
    this->update();
}
  ```
]


La funció `read()` comprova si el botó de la il·luminació s'ha premut cridant el mètode `read()` d'`EntradaDigital` amb els paràmetres `debounce` i `invert`. `debounce` fa que només retorni 1 (i.e. `true` quan s'interpreta com un booleà) quan el botó es deixa de prèmer, i `invert` fa exactament el que diu.

#sourcecode[
  ```cpp
// Iluminacio.cpp

bool Iluminacio::read() {
    if (this->button.read(true, true)) {
        this->isOn = !this->isOn;
        update();
        return true;
    }
    return false;
}

  ```
]

La funció `update()` només crida `setColorAll()` a través del constructor `CHSV` de la llibreria `FastLED`, que retorna un objecte `CRGB`. Al constructor li passa el valor de brillantor com a `uint8_t`, és a dir, un valor entre 0 i 255. Cal fer un `static_cast` perquè `brightness` és un `int`. Sabem que la brillantor sempre està entre dit rang, així que no ens hem de preocupar per desbordaments.

#sourcecode[
  ```cpp
// Iluminacio.cpp

void Iluminacio::update() {
    this->setColorAll(CHSV{0, 0, static_cast<uint8_t>(this->isOn ? this->brightness : 0)});
}
  ```
]

La funció `brightnessStr()` retorna un `String` amb la brillantor formatada com a percentatge, o "OFF" si els llums estan apagats.

#sourcecode[
  ```cpp
// Iluminacio.cpp

String Iluminacio::brightnessStr() const {
    String str = "";
  
    if (this->isOn) {
        str = String(((float) this->brightness) / 2.55, 0) + "%";
    } else {
        str = "OFF";
    }
  
    return str;
}
```
]

=== Joystick
A `Joystick.h`, definim un _enum_ amb cada eix del Joystick.

#sourcecode[
  ```cpp
// Joystick.h

enum Axis {
    X,
    Y
};


  ```
]

Seguidament, definim la classe `Joystick`:

#sourcecode[
  ```cpp

class Joystick {
private:
    int deadzone;
  
    Pair<int> pos;
  
    // Obtenir accés d'escriptura-lectura a la posició d'un eix
    int* getPosPtr(Axis axis);
  
protected:
    Pair<EntradaAnalogica> axisPins;
    EntradaDigital buttonPin;
public:
    Joystick(int _pinX, int _pinY, int _buttonPin, int deadzone);
  
    void begin();
  
    struct State {
        Axis axis;
        int pos;
        bool idle;
  
        bool operator==(const Joystick::State& other) const;
        bool operator!=(const Joystick::State& other) const;
    };
  
    // Retornen true si la posició ha canviat des de l'última lectura.
    bool read(Axis axis); // Llegir un eix
    bool read();          // Llegir els dos eixos
    bool readState();     // Llegir i actualitzar state
  
    State state;
  
    bool isPressed(bool debounce = false);
  
    // Obtenir accés de només lectura a la posició d'un eix
    const int* getPos(Axis axis);
};
  ```
]

Hi ha dues formes de llegir les dades rebudes del Joystick. Es pot fer obtenint la posició (entre -100 i 100) d'un dels eixos amb la funció `getPos`, o es pot llegir de forma més intel·ligent amb `readState`, que actualitza l'atribut `state`.

Aquesta funció està definida de la següent forma:

#sourcecode[
  ```cpp
// Joystick.cpp

bool Joystick::readState() {
    bool active = this->read();
  
    if (this->state.idle && active) {
        if (abs(this->pos.x) > (abs(this->pos.y) + this->deadzone + 5)) {
            this->state.axis = X;
            this->state.pos = this->pos.x;
            this->state.idle = false;
        } else if (abs(this->pos.y) > (abs(this->pos.x) + this->deadzone + 5)) {
            this->state.axis = Y;
            this->state.pos = this->pos.y;
            this->state.idle = false;
        }
    } else if (active) {
        this->state.pos = *this->getPos(this->state.axis);
    } else {
        this->state.idle = true;
        this->state.lastActive = millis();
    }
  
    return active;
}
  ```
]

El funcionament del codi anterior és el següent. Considerem que el Joystick està en repòs. Quan el comencem a moure, la placa detecta quin és l'eix cap al qual la palanca està més inclinada (si la diferència no és suficientment gran, en concret, 5 unitats més que el _deadzone_ establert, es considera que el Joystick està en repòs) i recorda l'eix actual. Aleshores, fins que la placa no torni a estar en repòs, només considerarà aquest eix, ignorant la posició de l'altre, de forma que és impossible passar d'un eix a l'altre directament. Totes aquestes dades processades es poden accedir des de l'atribut _state_.

La funció `readState()` també fa ús de la funció `read()`, que apliquen el _deadzone_ (part de les posicions que són massa petites per dir que el Joystick no està en repòs) de la forma següent:


#sourcecode[
  ```cpp
// Joystick.cpp

bool Joystick::read(Axis axis) {
    int* posAxis = getPosPtr(axis);
    EntradaAnalogica* pin = axis == X ? &this->axisPins.x : &this->axisPins.y;
  
    auto round = [=](int _pos) -> int { return abs(_pos) > this->deadzone ? _pos : 0; };
  
    *posAxis = round(::map((int) pin->read(), 0, 4095, -100, 100));

    return *posAxis != 0;
}
  ```
]

`round` és una funció `lambda` que retorna el valor tenint en compte el _deadzone_.

=== Alarma

La classe `Alarma` també és derivada de `LEDArray`. Es declara de la següent forma:

#sourcecode[
  ```cpp
// Alarma.h

class Alarma : private LEDArray {
private:
    EntradaDigital sensor;
    EntradaDigital button;

    static CRGB::HTMLColorCode colors[2];

    bool wasPressed;
    int interval;
    int mod;
public:
    enum class State {
        IDLE,
        PRESSED,
        DEACTIVATED,
        TRIGGERED
    };

    Alarma(int buttonPin, int sensorPin, CRGB* _leds[], int _ledsSize);

    bool active;

    State state;

    void begin(int _interval, int _mod);
    void read();

    static String stateToString(State st);
};
  
  ```
]

Respecte a l'atribut `state`, pot tenir els següents valors:

- `IDLE`. El botó no s'ha premut.
- `PRESSED`. El botó s'ha premut, però l'alarma estava desactivada.
- `DEACTIVATED`. El botó s'ha premut i ha desactivat l'alarma.
- `TRIGGERED`. S'ha detectat un obstacle i l'alarma s'ha activat.

Noti's que aquests són estats 'instantanis'. No es refereixen a l'estat de l'alarma pròpiament dita (activada o desactivada), sinó al que ha passat l'última vegada que s'ha cridat `read()`.

La funció `read()` es defineix així:

#sourcecode[
  ```cpp
void Alarma::read() {
    Alarma::State ret = Alarma::State::IDLE;

    this->button.read(false, true);

    if (this->sensor.read(false, true)) {
        this->active = true;
        this->wasPressed = false;
        ret = Alarma::State::TRIGGERED;
  
    } else {
        if (this->active && this->button.value) {
            this->active = false;
            this->wasPressed = true;
            ret = Alarma::State::DEACTIVATED;
    
        } else if (this->wasPressed && !this->button.value) {
          this->wasPressed = false;
          
        } else if (!this->wasPressed && this->button.value) {
            ret = Alarma::State::PRESSED;
            this->wasPressed = true;
        }
    }
    this->setColorAll(Alarma::colors[(millis() / this->interval) % this->mod && this->active]);

    this->state = ret;
}
  ```
]

El comportament del codi anterior es pot representar en un diagrama de flux (@alarmaflux).

#figure(caption: "Diagrama de flux que representa l'assingnació de l'estat de l'alarma.",
image("alarma_flux.png")
) <alarmaflux>

La variable `wasPressed`, el comportament de la qual no apareix al diagrama, serveix per no assignar `PRESSED` quan el botó s'estigui prement per desactivar l'alarma.

== Codi complet
Es pot trobar el repositori de GitHub amb tot el codi del projecte, incloent els diagrames i els scripts de processament de codi, en #link("https://github.com/alex-touza/casa-domotica", "aquest enllaç").

= Conclusions
Com vist anteriorment, l'objectiu d'aquest projecte era desenvolupar un habitatge domòtic fent servir la placa ESP32 SteamMakers i resolent els reptes proposats.

== Contratemps

Aquest projecte no ha sigut tan desafiant com el primer projecte que vam fer aquest curs, tanmateix, això no significa que no hàgim trobat alguns problemes. La dificultat més gran va ser fer que el motor DC funcionés quan volíem, a més, no vam aconseguir fer l'últim repte com s'havia plantejat, per tant, vam haver d'adaptar-lo. Altrament, durant les últimes sessions, vam tenir problemes fent que el Joystick i el polsador funcionessin amb la il·luminació.

També cal fer menció de les dues sessions en què la placa no funcionava i mostrava un missatge d'error pel Serial Monitor perquè havíem assignat un pin malament el codi---ara ja recordarem per sempre més que s'ha de comprovar quatre vegades que s'hagi utilitzat el nombre al costat de "IO" i no "D".

Malgrat tot això, considerem el nostre producte final considerablement satisfactori, especialment gràcies als reptes addicionals que vam fer.

== Valoració del projecte
Com ja hem mencionat, vam aconseguir complir tots els reptes proposats per aquest projecte, a més d'afegir alguns addicionals, com el canvi d'estacions i els missatges a la pantalla d'alarma, de la intensitat de la il·luminació, i de la connexió del sensor DHT11 (si no està connectat).

Per aquests motius, considerem el nostre projecte reeixit. Ens vam divertir molt fent-lo, vam aprendre moltes coses, i certament estem ansiosos per a fer el projecte final.

== Propostes de millora
Malgrat que tot hagi funcionat al final, ens agradaria poder haver fet el repte sis de la manera intencionada, fent servir el comandament a distància, ja que ja vam tenir problemes amb aquest mateix component en el projecte anterior.