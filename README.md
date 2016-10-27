# corewar

**./asm path_to_a_file.s**

**./corewar** [-**cnGva**][-__dump *num*__][path_to_files.cor ...]

*Projet de groupe effectué avec lgosse et akaragoz*

__*Warning:*__ *Une grande partie de ce README vient directement du sujet de 42, dont la description des instructions.*

	./corewar -c -n 42 donald_trump.cor -n 4242 resources/cor_championship/_.cor

![](https://github.com/dihydrro/corewar/blob/master/README/ncurse.gif)

* L'option -c active le mode ncurse, qui est un mode visuel de l'arène, on peut augmenter/diminuer la vitesse d'exécution avec les touches directionnelles. Mettre sur pause avec la bar espace.
* L'option -n suivis d'un numéro sert à assigner ce dernier au champion.

	./corewar -Gv -dump 10000 -n 42 donald_trump.cor -n 4242 resources/cor_championship/_.cor

![](https://github.com/dihydrro/corewar/blob/master/README/dump_10000.gif)

* L'option -dump suivis d'un numéro sert à dump la mémoire au cycle du numéro donné.
* L'option -v permet d'activer le mode verbose.
* L'option -G rajoute un peu de couleur lors du dump de la mémoire.

Le corewar est une arène où des champions se battent jusqu'à la mort à l'aide de processus. Chaque processus dispose des éléments suivants:

*	REG_NUMBER registres qui font chacun une taille de REG_SIZE octets.
*	Un PC ("Program Counter"). Qui contient l'adresse de la prochaine instruction à décoder et exécuter.
*	Un flag nommé carry, qui vaut 1 si la dernière opération a réussi. Seules certaines opérations vont modifier le carry.

Le numéro du joueur est généré par la machine ou spécifié au lancement, et est fourni aux champions via le registre r1 de leur premier processus au démarrage. Tous les autres registres sont mis à 0. Sauf le PC.

Tous les CYCLE_TO_DIE cycles, la machine doit s’assurer que chaque processus a exécuté au moins un live depuis la dernière vérification. Un processus qui ne se soumet pas à cette règle sera mis à mort à l’aide d’une batte en mousse virtuelle.

Le gagnant est le dernier joueur qui a été rapporté comme étant en vie.

La mémoire est circulaire et fait MEM_SIZE octets.

Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications, on le décrémente.

Les champions ne peuvent pas dépasser CHAMP_MAX_SIZE.

Le champion est décrit dans un fichier **.s** qui contient des labels et des instructions. Il existe seize instructions possibles:

* lfork: Ca signifie long-fork, pour pouvoir fourcher de la paille à une distance de 15 mètres, exactement comme son opcode. Pareil qu’un fork sans modulo à l’adresse.
* sti: Opcode 11. Prend un registre, et deux index (potentiellement des registres). Additionne les deux derniers, utilise cette somme comme une adresse ou sera copiée la valeur du premier paramètre.
* fork: Pas d’octet de codage des paramètres, prend un index, opcode 0x0c. Crée un nouveau processus, qui hérite des différents états de son père, à part son PC, qui est mis à (PC + (1er paramètre % IDX_MOD)).
* lld: Signifie long-load, donc son opcode est évidemment 13. C’est la même chose que ld, mais sans % IDX_MOD. Modifie le carry.
* ld: Prend un paramètre quelconque et un registre. Charge la valeur du premier paramètre dans le registre. Son opcode est 10 en binaire, et il changera le carry.
* add: Opcode 4. Prend trois registres, additionne les 2 premiers, et met le résultat dans le troisième, juste avant de modifier le carry.
* zjmp: Il n’y a jamais eu, n’y a pas, et n’y aura jamais d’octet de codage des paramètres derrière cette opération dont l’opcode est de 9. Elle prendra un index, et fait un saut à cette adresse si le carry est à 1.
* sub: Pareil que add, mais l’opcode est 0b101, et utilise une soustraction.
* ldi: ldi, comme son nom l’indique, n’implique nullement de se baigner dans de la crème de marrons, même si son opcode est 0x0a. Au lieu de ça, ca prend 2 index et 1 registre, additionne les 2 premiers, traite ca comme une adresse, y lit une valeur de la taille d’un registre et la met dans le 3eme.
* or: Cette opération est un OU bit-à-bit, suivant le même principe que and, son opcode est donc évidemment 7.
* st: Prend un registre et un registre ou un indirect, et stocke la valeur du registre vers le second paramètre. Son opcode est 0x03. Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse (PC + (42 % IDX_MOD))
* aff: L’opcode est 10 en hexadécimal. Il y a un octet de codage des paramètres, même si c’est un peu bête car il n’y a qu’un paramètre, qui est un registre, dont le contenu est interprété comme la valeur ASCII d’un caractère à afficher sur la sortie standard. Ce code est modulo 256.
* live: L’instruction qui permet à un processus de rester vivant. A également pour effet de rapporter que le joueur dont le numéro est en paramètre est en vie. Pas d’octet de codage des paramètres, opcode 0x01. Oh, et son seul paramètre est sur 4 octets.
* xor: Fait comme and avec un OU exclusif. Comme vous l’aurez deviné, son opcode en octal est 10.
* lldi: Opcode 0x0e. Pareil que ldi , mais n’applique aucun modulo aux adresses. Modifiera, par contre, le carry.
* and: Applique un & (ET bit-à-bit) sur les deux premiers paramètres, et stocke le résultat dans le registre qui est le 3ème paramètre. Opcode 0x06. Modifie le carry.

Les champions passe dans une phase de préparation à travers l'**asm** qui traduit ces instructions en bytecode dans un fichier **.cor**.

	./asm donald_trump.s
	Writing output program to donald_trump.cor

Le **.cor** peut être envoyé au corewar avec d'autres champions sous la forme de bytecode pour voir qui est le meilleur.
