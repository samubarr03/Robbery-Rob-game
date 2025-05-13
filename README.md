# Robbery-Rob-game
Gioco 2D con visuale dall'alto ispirato a Robbery Bob. Il giocatore deve rubare un oggetto in vari edifici evitando le guardie. Diverse difficoltà influenzano il campo visivo dei nemici. Il gioco finisce solo se il giocatore viene raggiunto.

## Step 1

Generazione della griglia di gioco con settaggi standard. 
Mi sono aiutato abbastanza con la documentazione di sfml-dev.org e ho compreso perchè avevo dei problemi con draw. All' inizio creavo la finestra con Window e non renderWindow e non usavo videomode  
[Discussione su SFML Forum](https://en.sfml-dev.org/forums/index.php?topic=27467.0)

Ho inoltre crato anche un prepare.sh che mi permette di buildare e avviare il gioco in maniera più semplice
