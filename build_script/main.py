from shutil import copytree
from glob import glob
from os import rename, chdir
from pathlib import Path
from os.path import abspath, join, isdir
from shutil import rmtree
from colorama import init
from text import Colors, Estils, titol
from postprocessing import Rename, FindReplace

init()

chdir(Path(__file__).parent.resolve())

ORIGIN_PATH = "../src"
PROJECT_NAME = "casa-domotica"

DESTINATION_PATH = f"../dist/{PROJECT_NAME}"
ORIGIN_ROOT_NAME = ORIGIN_PATH.split('/')[-1]

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

if isdir(DESTINATION_PATH):
    Colors.groc()
    print("WARNING: Destination path already exists.\nCurrent content will be removed.")
    input("Press enter to confirm...")
    Colors.reset()
    try:
        rmtree(DESTINATION_PATH)
    except Exception as e:
        Colors.error()
        print(f"Error occured while clearing destination path.")
        print(e)
        Colors.reset()
        exit(1)

    print()
    print(Colors.verd("Destination path cleared successfully."))
    print()


for k, ext in sourceFiles.items():
    titol(k.upper())
    for f in [abspath(p) for p in glob(f"{ORIGIN_PATH}/*.{ext}")]:
        spl = f.rfind(ORIGIN_ROOT_NAME)
        print(Colors.blau(f[spl + len(ORIGIN_ROOT_NAME) + 1:]))
    print()

titol("POSTPROCESSING RULES")

for i, s in enumerate(postprocessing):
    print(f"#{i} {s}")

print()
input(Colors.blau("Press enter to initiate the copy...") + Colors.groc)
Colors.reset()

try:
    copytree(ORIGIN_PATH, DESTINATION_PATH, dirs_exist_ok=True)
except Exception as e:
    print(Colors.error(f"Error occured while copying."))
    print(e)
    exit(1)

n_errors = 0

for i, s in enumerate(postprocessing):
    try:
        s(DESTINATION_PATH)
    except Exception as e:
        n_errors += 1
        Colors.error()
        print(f"Error occured in postprocessing rule #{i}.")
        print(e)
        Colors.reset()

print()

if n_errors:
    print(Colors.groc(f"Code copied with {n_errors} error(s)."))
else:
    print(Colors.verd("Code copied successfully."))

