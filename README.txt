// Copyright 314CC Miron Andreea Cristiana

Structuri de Date si Algoritmi

Tema #1
Prelucrarea si analizarea datelor secventiale

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	In realizarea acestei teme am ales sa lucrez cu liste dublu inlantuite 
circulare cu santinela. Astfel, avem o structura List(declarata in List.h) ce 
contine adresele de legatura(prev si next) si o alta structura Item, ce are 
drept campuri timestamp-ul si valoarea unui nod din lista. 
	Cele mai folosite functii sunt declarate in List.h, insa programul lor
se afla in main.c, acestea fiind cu urmatoarele scopuri:
	- add_node: adauga la lista un nod nou
	- nr_list : returneaza numarul de noduri dintr-o lista
	- print_list: afiseaza lista
	- free_list : eliberareaza din memorie o lista

	In cadrul main-ului se declara lista initiala 's', fiind o lista dublu
inlantuita circulara cu santinela si se citesc datele de la tastatura(value 
si timestamp), astfel incat pentru fiecare pereche i se asociaza un nou nod,
care va fi adaugat in lista prin apelarea functiei 'add_node'. 
	
	Utilizatorul a transmis o serie de comenzi primite ca argumente in 
linia de comanda, urmand ca aceastea sa fie executate in ordinea in care apar.
Pentru fiecare argument exista cate o filtrare asociata, acestea fiind:
	
1) e1 : Eliminare de exceptii folosind metode statistice;
2) e2 : Eliminare de zgomot folosind filtru median;
3) e3 : Eliminare de zgomot folosind filtrul bazat pe media aritmetica;
4) u  : Uniformizarea frecventei;
5) c  : Completarea datelor lipsa;
6) st< delta > : Se vor calcula statisticile cu intervale de timp delta	

	/* Pentru a creste dificultatea temei am preferat sa lucrez cu ferestre
de dimensiuni k sau k vecini, unde e cazul, iar la apelari k-ul va lua valoarea
din enunt in functie de filtrare  */	

-------------------------------------------------------------------------------
	Filtrarile s-au realizat astfel:
-Eliminarea de exceptii folosind metode statistice:
	Daca argumentul a fost "--e1", se va apela functia e1, al carei program
se afla in fisierul e1.c. Logica functiei e1 este urmatoarea: declaram 
pointerii de List p si last, care au urmatoarele atributii:
	->  p : va retine adresele nodurilor din lista initiala in jurul caruia
	        se poate construi o fereastra, insa initial va fi initializat 
		cu adresa primului astfel de nod
	->last: va retine adresa ultimului nod din lista in jurul caruia se 
		poate construi o fereastra
	Astfel, prin parcugerea nodurilor in jurul carora se pot construi 
ferestre, se calculeaza inferiorul si superiorul intervalului cu care se 
verifica valoarea unui nod din lista, iar daca acesta nu se afla in interval
se va retine intr-o noua lista nodul cu timestamp-ul de sters. Inferiorul si
superiorul intervalului s-au calculat cu ajutorul functiilor average si 
deviation care au urmatoarele roluri:
	-> average:   returneaza media valorilor numerice dintr-o fereastra de 
		      k elemente
	-> deviation: returneaza deviatia standard a valorilor dintr-o 
		      fereastra cu k elemente 
	Dupa parcurgerea listei intiale, se parcurge noua lista si se elimina
din lista initiala nodurile cu timestamp-ul de sters prin apelarea functiei
delete_node, care sterge un nod cu anume timestamp din lista. Dupa eliminari,
se elibereaza lista cu nodurile de sters.

-------------------------------------------------------------------------------

-Eliminare de zgomot folosind filtre
	Daca argumentul a fost "--e2" sau "--e3", se va apela functia e23, al 
carei program se afla in fisierul e23.c. Cele doua filtrari(mediana si 
aritmetica) se bazeaza pe aceeasi logica, diferenta fiind la valoarea nodurilor
din lista s2.
	Analog ca si la filtrarea anterioara, pointerii p si last au aceleasi
scopuri. La parcurgerea nodurilor in jurul carora se pot construi ferestre, 
se adauga in lista s2 nodurile cu valorile cerute. Diferenta consta doar in 
deciderea a carei valori se va adauga. 
	In cazul filtrarii mediane, valoarea va fi cea returnata de functia 
median, care returneaza mediana dintr-o fereastra de dimensiune k. In cadrul 
acesteia, pentru a nu distruge lista initiala, se creeaza o noua lista cu 
valorile dintr-o ferestra, se ordoneaza crescator la apelul functiei sort_list 
si returneaza nodul din mijlocul listei.
	In cazul filtrarii aritmetice, valoarea va fi cea returnata de functia
average, care se regaseste in fisierul e1.c.
	Timestamp-ul fiecarui nod adaugat este acelas cu timestamp-ul nodului
in care s-au construit ferestrele.

-------------------------------------------------------------------------------

-Uniformizarea frecventei in timp a datelor
	Daca argumentul a fost "--u", se va apela functia u, al carei program
se afla in fisierul u.c. 
	Se parcurge lista de la al doilea element pana la ultimul si pentru
fiecare nod parcurs se calculeaza diferenta de timestamp intre nodul actual si
cel precedent. Daca diferenta este intre 0.1 si 1, noile valori ale nodului
actual vor fi atat pentru value si timestamp media aritmetica a valorilor, 
respectiv timestamp-urilor a nodului actual si cel precedent.

-------------------------------------------------------------------------------

-Completarea datelor
	Daca argumentul a fost "--c", se va apela functia c, al carei program
se afla in fisierul c.c. Logica functiei c este urmatoarea: declaram pointerii 
de List p si last, care au urmatoarele atributii:
	->  p : va retine adresele nodurilor din lista initiala, care are k-1
		vecini in stanga si k vecini in dreapta. Astfel, valoarea
		nodului retinuta de p, reprezinta marginea inferioara a unui
		interval. Initial va fi initializat cu adresa primului 
		astfel de nod
		
	->last: va retine adresa ultimului nod din lista care are k vecini in
		dreapta
	Pana cand p este diferita de last, se parcurge lista, unde au loc 
urmatoarele instructiuni:
	- se retine adresa urmatorului nod in pointerul next, deoarece in cazul
unei completari, p->next va diferi de cel dinainte de completare
	- daca diferenta dintre valoarea nodului actual si cel urmator este mai
mare de o secunda, se vor efectua si urmatoarele instructiuni:
            1) se creeaza listele left si right ce vor contine cei k vecini din
	      stanga, respectiv din dreapta;
	    2) se creeaza nodurile cu noile timestamp-uri, iar pentru 
	      asigurarea ca intr-o secunda se completeaza cu cel putin 5 
	      valori, noile timestamp-uri vor fi de forma inf+200*k, unde inf
	      este marginea inferioara a intervalului de completat, iar k un 
	      numar intreg, totul pana cand se depaseste limita superioara
            3) pentru fiecare nod cu timestamp creat, valoarea va fi data de
	      functia f, ce reprezinta o medie ponderata a vecinilor, unde
	      sunt apelate functiile w si C, ce reprezinta factori scalari, si
	      este adaugat in lista prin apelarea functiei add_node_k, care 
	      adauga in fata nodului de pe pozitia k dintr-o lista nodul creat 
	    4) dupa creare, se elibereaza listele left si right
	- p preia valoarea lui next si se continua parcurgerea listei
	

-------------------------------------------------------------------------------	

-Statistici	
	Daca argumentul a fost "--st<delta>", se va apela functia st, al carei 
program se afla in fisierul st.c.
	Implementarea functiei st consta in:
	-> ordonarea listei crescator dupa valoare prin apelarea functiei 
	sort_list, al carei program se afla in fisierul e23.c
	-> gasirea limitei superioare a primului interval prin incadrarea 
	primului element
	-> parcurgerea listei, in care se verifica pentru fiecare valoare a 
	unui nod urmatoarele:
		a) daca valoarea se incadreaza in intervalul deschis actual, 
		se incrementeaza nr(numarul de valori din intervalul actual)
		b) daca valoarea este multiplu de k, adica se gaseste in doua
		intervale, se incrementeaza nr si nr2(numarul de valori care
		se afla in intervalul actual si urmator)
		c) daca valoarea depaseste intervalul, se afiseaza intervalul 
		cu numarul de elemente(nr), nr are acum valoarea lui nr2+1, 
		caci intervalul actual si cel urmator aveau elemente comune, si
		se schimba intervalul actual cu urmatorul in care mai exista 
		valori
	-> afisarea ultimului interval

	Deoarece nu se cere si afisarea listei, a fost nevoie de o variabila 
ok_st in main, care sa retine daca utilizatorul a vrut statistici. 
