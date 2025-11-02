Regles:

Pour le master : connnecter les pins A0, A1 et A2
Pour le slave : deconnnecter les pins A0, A1 et A2

- En attente d'un debut de partie, la LED D5 est en blanc


- Lorsqu'un joueur a appuye sur le bouton de demarrage SW1, la LED D5 est en bleu


- Une fois les deux boutons de debut de partie presses, le compte a rebours demarre.
Il est signale par la sequence de LED suivante:
	- La LED D5 RGB est eteinte
	- la LED D1 s'allume en rouge et reste allumee
	- la LED D2 s'allume en rouge et reste allumee 
	- la LED D3 s'allume en rouge et reste allumee
	- la LED D4 s'allume en rouge et reste allumee
	- les LED D1 a D4 s'eteignent. Le jeu commence.
Tant que les LED sont rouges, un joueur appuyant sur le bouton SW1 perd


- La victoire est signalee sur le microcontrolleur du gagnant par :
	- la led D5 en vert


- La defaite est signalee sur le microcontrolleur du perdant par :
	- la led D5 en rouge
