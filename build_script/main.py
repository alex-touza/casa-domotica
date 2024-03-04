from shutil import copytree
from glob import glob
from os import chdir, system
from pathlib import Path
from os.path import abspath, join, isdir
from shutil import rmtree
from colorama import init
from text import Colors, Estils, titol
from postprocessing import Rename, FindReplace

init()

chdir(Path(__file__).parent.resolve())

ROOT = "../"
ORIGIN_PATH = "./src"
PROJECT_NAME = "casa-domotica"

DESTINATION_PATH = f"./dist/{PROJECT_NAME}"
ORIGIN_DIR_NAME = ORIGIN_PATH.split('/')[-1]

ROOT_ABS = abspath("../")
ORIGIN_PATH_ABS = abspath(join(ROOT_ABS, ORIGIN_PATH))
DESTINATION_PATH_ABS = abspath(join(ROOT_ABS, DESTINATION_PATH))

sourceFiles = {"header": "h", "source": "cpp"}

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


if isdir(DESTINATION_PATH_ABS):
    Colors.groc()
    print()
    print("WARNING: Destination path already exists.\nCurrent content will be removed.")
    input("Press enter to confirm...")
    Colors.reset()
    try:
        rmtree(DESTINATION_PATH_ABS)
    except Exception as e:
        Colors.error()
        print(f"Error occured while clearing destination path.")
        print(e)
        Colors.reset()
        exit(1)

    print()
    print(Colors.verd("Destination path cleared successfully."))
    input("Press enter to continue...")


titol("FILES")
files_dict = {t: glob(f"{ORIGIN_PATH_ABS}/*.{ext}") for t, ext in sourceFiles.items()}

for t, files in files_dict.items():
    for path in files:
        print(Colors.blau(f"{t} ./" + path[path.rfind(ROOT_ABS) + len(ROOT_ABS) + 1:].replace('\\', '/')))
# for f in [abspath(p) for p in [glob(f"{ORIGIN_PATH_ABS}/*.{f}") for f in sourceFiles.values()]]:
#     print(Colors.blau("./" + f[f.rfind(ROOT_ABS) + len(ROOT_ABS) + 1:].replace('\\', '/')))
# print()

input("Press enter to continue...")

titol("POSTPROCESSING RULES")

for i, s in enumerate(postprocessing, 1):
    print(f"#{i} {s}")

print()
input(Colors.blau("Press enter to initiate the copy...") + Colors.groc)
Colors.reset()

system('cls||clear')
print("--------------")

print(Colors.blau(f"Copying directory {ORIGIN_PATH} to {DESTINATION_PATH}..."))

try:
    copytree(ORIGIN_PATH_ABS, DESTINATION_PATH_ABS, dirs_exist_ok=True)
except Exception as e:
    print(Colors.error(f"Error occured while copying."))
    print(e)
    exit(1)

print(Colors.verd(f"Files copied successfully."))
print()

print(Colors.blau("Executing postprocessing rules..."))

n = len(postprocessing)

n_errors = 0

for i, s in enumerate(postprocessing, 1):
    try:
        s(DESTINATION_PATH_ABS)
    except Exception as e:
        n_errors += 1
        Colors.error()
        print(f"Error occured in postprocessing rule #{i}: {s.repr()}")
        print(e)
        Colors.reset()
    else:
        print(Colors.verd(f"Postprocessing rule #{i} of {n} executed successfully."))

if n_errors:
    print(Colors.groc(f"Code processed with {n_errors} error(s)."))
else:
    print(Colors.verd("Code processed successfully."))

print()
print(Colors.blau("Don't forget to copy the libraries to the correct location!"))
