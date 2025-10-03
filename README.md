# LAN Party

Acest proiect implementeaza o aplicatie care foloseste structuri de date pentru a organiza un LAN Party. Programul simuleaza meciuri intre echipele inscrise si aranjeaza castigatorii sub forma unor arbori.

Structura Programului:

- [main.c](main.c) : Fisierul principal; in functie de cerintele din fisierele [c.in](c.in), sunt apelate functiile pentru fiecare task
- [lists.c](lists.c) : Functii pentru lucrul cu liste
- [stacks.c](stacks.c) : Functii pentru lucrul cu stive
- [queues.c](queues.c) : Functii pentru lucrul cu cozi
- [bst.c](bst.c) : Functii pentru lucrul cu BST si AVL
- [header.h](header.c) : Header care contine structurile si antetele functiilor folosite in program
- [Makefile](Makefile) : Fisier pentru compilarea fisierelor .c folosite in rezolvarea cerintelor

TASK 1:
Se citesc din fisierele [d.in](d.in) informatiile despre fiecare echipa cu ajutorul functiei `readTeams`, iar datele sunt introduse intr-o lista.

TASK 2:
Folosesc functia `averagescoresV` pentru a crea un vector cu mediile echipelor si caut punctajul minim.

`EliminatedTeams` calculeaza numarul de echipe ce trebuie eliminat pentru a ramane cu un numar maxim de echipe ce poate fi scris ca putere a lui 2.

Elimin numarul respectiv de echipe cu punctajul cel mai mic, iar in cazul in care 2 echipe au acelasi punctaj este eliminata prima gasita (in functie de valoarea mediei din vector). Modific numarul total de echipe si elimin minimul din vector.

TASK 3:
Se realizeaza meciurile dintre echipe. Acestea sunt puse intr-o coada. Fiecare meci are loc intre 2 echipe, in ordinea lor din coada.

De aici folosesc campul `totalPoints` al structurii team drept media aritmetica a punctajului echipei.

Echipele sunt scoase 2 cate 2 din coada, cu functia `deQueue`, sunt comparate scorurile lor; cele castigatoare ajung cu `push` in stiva `winnersStack`, adaugand la punctaj + 1, iar cele ce pierd sunt puse in `losersStack`.

Se afiseaza castigatorii, care sunt mutati inapoi in coada pentru a realiza urmatoarea runda, eliminam pe cei invinsi din stiva. Cand numarul de echipe din lista de castigatori este egal cu 8, salvam aceste echipe intr-o alta lista, folosita pentru realizarea urmatoarelor task-uri.

TASK 4:
Creez un BST ce contine cele 8 echipele salvate la punctul anterior, ordonat dupa punctaj, iar in caz de egalitate, sunt comparate in functie de nume. Continutul este afisat descrescator.

TASK 5:
Pornind BST-ul de la task-ul 4, am inserat echipele intr-un AVL prin echilibrare si au fost afisate echipele de pe nivelul 2.
