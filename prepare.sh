#File per la build e l' avvio automatico del gioco

# Creo la cartella build se non esiste
if [ ! -d "build" ]; then
  mkdir build
fi

# Genero i file per la compilazione
cmake -B build

# Compilo il progetto
cmake --build build --target robbery-rob

# Lancio l' eseguibile
./build/bin/robbery-rob
