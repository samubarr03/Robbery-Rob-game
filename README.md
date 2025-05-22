# Robbery-Rob-game
Gioco 2D con visuale dall'alto ispirato a Robbery Bob. Il giocatore deve rubare un oggetto in vari edifici evitando le guardie. Diverse difficoltà influenzano il campo visivo dei nemici. Il gioco finisce solo se il giocatore viene raggiunto.

## Step 1

**Generazione della griglia di gioco con settaggi standard**  
Mi sono aiutato abbastanza con la documentazione di sfml-dev.org e ho compreso perchè avevo dei problemi con draw. All' inizio creavo la finestra con Window e non renderWindow e non usavo videomode 
[Discussione su SFML Forum](https://en.sfml-dev.org/forums/index.php?topic=27467.0)

Ho inoltre crato anche un prepare.sh che mi permette di buildare e avviare il gioco in maniera più semplice

## Step 2
Inizio a pensare a quanto dovrebbe essere grande la matrice che compone la mappa per fare in modo che tutti gli oggetti di scena, il personaggio e le guardie siano proporzionate. 
Per ora utilizzerò una **griglia 64 x 64** e il **player 2 x 2** sarà colorato di verde.

**Ho iniziato separando i file e dividendoli nelle cartelle:**
- Game gestisce il gioco
- matrix crea il campo di gioco
- Player crea il giocatore, lo disegna e contiene i listener di movimento
 
[Listener class reference](https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Listener.php)  
[Simulating charachter move](https://en.sfml-dev.org/forums/index.php?topic=5378.0)  
[Keyboard inputs SFML](https://stackoverflow.com/questions/45257041/taking-2-keyboard-inputs-with-sfml)

**Problemi:**

- **Ho notato qualche problema con la creazione di `CMakeLists.txt`** per l'aggiunta di tutte le directory, e in fase di compilazione volevo tenere solo `utils.hpp`, però ho dovuto creare anche `utils.cpp` e organizzare i file.

- **Ho dovuto ridimensionare la grandezza delle celle** in base alla grandezza della finestra / numero di celle, perché altrimenti uscivano dalla finestra visibile.

## Step 3

Durante questo step mi sono reso conto che il mio approccio non era seguibile e ho trasformato la matrice disegnata in una matrice di numeri creando i tipi che potrebbero servirmi in futuro:

```c
    TYPE_FLOOR = 0,
    TYPE_PLAYER = 1,
    TYPE_GUARD = 2,
    TYPE_FURNITURE = 3,
    TYPE_LOOT = 4,
    TYPE_VISUAL_GUARD = 5,
    TYPE_WALL = 6
  ```  
Ho riorganizzato le classi tenendo solo un punto in cui la matrice viene disegnata e nella classe player la gestione della posizione di esso. Ho tolto anche tutte le costanti perchè le informazioni che contenevano me le calcolo dalla grandezza dello schermo del player e dalla matrice.

La matrice ora è più piccola di 64x64 ma solo per fare i test. Il prossimo passaggio sarà implementarla da un file.txt.

## Step 4

In questa fase ho riportato la griglia a 64x64 ma anche solo per fare i test sarebbe stato troppo difficile disegnare a mano le mappe. Così  
ho creato una schermata iniziale con 2 bottoni:   

**Gioca**  : carica una mappa già preimpostata e si può muovere il player.  
**Disegna mappa** : viene mostrata una finestra in cui si possono osservare i bottoni del componenti dei principali elementi di gioco e se si clicca su uno di essi e poi si clicca su un punto della mappa noteremo che la cella cliccata si colorerà e l'oggetto selezionato è come se fosse stato posizionato in quel punto. 

Alla fine delle modifiche cliccando su **salva** la mappa viene automoaticamente salvata.  
In questo modo la creazione delle mappe sarà molto più veloce e c'è la possibilità che anche il player si crei delle mappe e con la possibilità in seguito di impostarne la difficoltà.

## Step 1.0.0
In questa versione ho adattato il mio progetto a un **pattern generale**, riorganizzando i file:

- Le **immagini**, le **mappe** e i **file di risorse** si trovano ora all'interno della cartella `resources/`.
- I **file sorgente relativi alla tappa 1** sono stati spostati nella cartella `Tappa01/`.

Ho inoltre aggiornato la versione di **SFML** dalla `2.5` alla più recente `3.0`.

Fortunatamente, non ho riscontrato troppe difficoltà nel processo, se non la necessità di **dichiarare tutti i componenti nel costruttore**.

Per aiutarmi nella migrazione, ho fatto riferimento alla documentazione ufficiale disponibile qui:  
🔗 [SFML Migration Guide](https://github.com/SFML/SFML/blob/master/migration.md)

 A livello di migliorie effettive nel gioco, in questa fase **non ne sono state svolte**.


# Step 02.0.0

In questo step ho: 
- Aggiunto **Seleziona mappa** e **Salva mappa** tramite una finestra di dialogo, mi è stato utile il [forum SFML dialog](https://en.sfml-dev.org/forums/index.php?topic=29473.0)
che mi ha portato a conoscienza della libreria [portable-file-dialogs](https://github.com/samhocevar/portable-file-dialogs)  
- Corretto degli errori di movimento del player ( relativi a una confusione fra x e y)
- Aggiunto le texture del pavimento 

Ora la schermata di gioco si presenta così:

![Step 2](./resources/Step2-game.png)


# Step 3.0.0
In questo step ho aggiunto:
- **Le guardie** facendo una brutta versione dalla classe player. Fino ad ora ho solo sviluppato l' algoritmo che a inizio gioco visualizza tutte le guardie e crea ogni guardia inserendola in un vector apposta di Guardie.
- Le texture per i muri

Ho anche fixato:
- La visualizzazione della texture del player
- Un altro problema di segmentation faul perchè il player andava fuori dalla mappa  

Problemi riscontrati:  
Ho avuto qualche problema solo nella creazione del vector di guardie perchè non ricordavo si potesse passare un solo parametro facendo il push_back di una class. Ho fixato subito leggendo questa discussione  [Stack overflow push_back ](https://stackoverflow.com/questions/12083070/c-vectors-and-errors-no-instance-of-overloaded-function).

Ora quando si inizia una nuova partita si può osservare questa grafica:

![Step 3](./resources/step3.png)
