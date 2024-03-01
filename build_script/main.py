from shutil import copytree
from glob import glob
from os import rename
from os.path import abspath, join
from colorama import init
from text import Colors, Estils, titol
from postprocessing import Rename, FindReplace

init()

ORIGIN_PATH = "../src"
PROJECT_NAME = "casa-domotica"
DESTINATION_PATH = f"../dist/{PROJECT_NAME}"

sourceFiles = {"headers": "h", "source": "cpp"}

postprocessing = [
    FindReplace("/main.cpp", [("#include <Arduino.h>\n", "")]),
    #FindReplace("/Pantalla.h", [("#include <LiquidCrystal_I2C.h>", "#include \"src/lib/LiquidCrystal_I2C/LiquidCrystal_I2C.h\"")]),
    #FindReplace("/NeoPixel.h", [("#include <FastLED.h>", "#include \"src/lib/FastLED-3.6.0/src/FastLED.h\"")]),
    Rename("/main.cpp", f"/{PROJECT_NAME}.ino")
]

titol("CONFIG")
for k, v in {"Project name": PROJECT_NAME, "Origin path": ORIGIN_PATH, "Destination path": DESTINATION_PATH}.items():
    value = f"{v:>20}"
    print(f'{k:<30} {Estils.brillant(value)}')

print()

for k, ext in sourceFiles.items():
    titol(k.upper())
    for f in [abspath(p) for p in glob(f"./src/*.{ext}")]:
        print(Colors.blau(f))
    print()

print()
titol("POSTPROCESSING RULES")

for s in postprocessing:
    print(s)

print()
input(Colors.blau("Press enter to initiate the copy...") + Colors.groc)
Colors.reset()
copytree(ORIGIN_PATH, DESTINATION_PATH, dirs_exist_ok=True)
copytree('../lib', DESTINATION_PATH + '/lib')

for s in postprocessing:
    s(DESTINATION_PATH)
