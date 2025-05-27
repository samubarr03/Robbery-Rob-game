#File per la build e l' avvio automatico del gioco
set -e

# Creo la cartella build se non esiste
mkdir -p build
cd build

# Compilo
cmake ..
make -j$(nproc)

# Inserisco le risorse
mkdir -p bin/resources
cp -r ../resources/* bin/resources/

# Lancio l'eseguibile
cd bin
./Tappa07
