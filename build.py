from shutil import copytree
from glob import glob
from os import rename
from os.path import abspath, join
from colorama import init
from text import Colors, Estils, titol

init()

ORIGIN_PATH = "./src"
PROJECT_NAME = "casa-domotica"
DESTINATION_PATH = f"./dist/{PROJECT_NAME}"


class FindReplace:
    # Ruta relativa a la carpeta "dist".
    # None indica que és l'sketch.
    def __init__(self, path: str | None, pairs: list[tuple[str, str]] | tuple[str, str]):
        self.path = path
        self.pairs = pairs if isinstance(pairs, list) else [pairs]

    def __call__(self) -> str:
        with open('./' + self.path, 'r') as file:
            s = file.read()
            for old, new in self.pairs:
                s.replace(old, new)
            return s

    def __str__(self):
        return Colors.gris('Find and replace -- ') + Colors.blau(self.path) + Colors.gris(':') + ''.join(
            [('\n\t' + Colors.groc(
                old) + Colors.gris(
                ' => ') + (Colors.gris('(empty)') if new == "" else Colors.verd(new))) for old, new in self.pairs])


class Rename:
    def __init__(self, oldPath: str, newPath: str):
        self.oldPath = oldPath
        self.newPath = newPath

    def __call__(self):
        rename(self.oldPath, self.newPath)

    def __str__(self):
        return Colors.gris('Rename -- ') + Colors.blau(self.oldPath) + Colors.gris(' => ') + Colors.verd(self.newPath)


sourceFiles = {"headers": "h", "source": "cpp"}

postprocessing = [
    FindReplace("./main.cpp", [("#include \"../lib/DHT_sensor_library-1.4.6/DHT.h\"",
                                "#include \"lib/DHT_sensor_library-1.4.6/DHT.h\""), ("#include <Arduino.h>", "")]),
    Rename("./main.cpp", f"./{PROJECT_NAME}.ino")
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
# copytree(ORIGIN_PATH, DESTINATION_PATH, dirs_exist_ok=True)
