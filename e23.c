#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "header.h"

/* interschimba doua valori reale */
void swap(double *a, double *b) 
{
    double aux = *a;
    *a = *b;
    *b = aux;
}

/* sorteaza o lista crescator dupa valoare */
void sort_list(List *s)
{
    int ok;
    List *p;
    do{
        ok=1;
        for(p=s->next; p!=s->prev; p=p->next)
            if(p->elem.value > p->next->elem.value){
                swap(&p->elem.value,&p->next->elem.value);
                ok=0;
            }
    }while(ok==0);
}

/* returneaza mediana dintr-o fereastra de dimensiune k */
double median(List *s, int k)
{
    List *l = (List *) malloc(sizeof(List));
    l->prev = l->next = l;

    List *p=s;
    int i;

    for(i=0;i<k/2;i++)
        p=p->prev;

    for(i=0; i<k; i++){
        List *new = (List *) malloc(sizeof(List));
        new->elem = p->elem;
        add_node(l,new);
        p=p->next;
    }

    sort_list(l);
                
    p=l->next;
    for(i=0; i<k/2; i++)
        p=p->next;

    double m = p->elem.value;

    free_list(l);
    
    return m;
}

/* realizeaza filtrarea mediana pentru o fereastra de dimensiune k, iar noua 
lista se adauga la lista s2 */
List* e23(List *s, List *s2, int k, char* argv)
{
    int i;
    List *p = s->next; /// nodul curent
    List *last = s;    /// ultimul element din procesul de procesul de filtrare

    /* alocare de memorie pentru noua lista */ 
    s2 = (List *) malloc(sizeof(List));
    s2->next = s2->prev = s2; 

    /* initializarea cu valorile corespunzatoare ale primului nod mijlociu al 
    unei ferestre(p) si ultimul nod(last) */   
    for(i=0; i<k/2; i++){
        p=p->next;
        last = last->prev;
    }

    /* realizarea filtrarii */
    while(p!=last){
        List *new = (List *) malloc(sizeof(List));
        new->elem.timestamp = p->elem.timestamp; 
        /* alegerea filtrarii */
        if(strcmp(argv,"--e2")==0)
            new->elem.value = median(p,k);   // realizeaza filtrarea mediana
        else new->elem.value = average(p,k); // realizeaza filtrarea aritmetica
        add_node(s2,new);     /// adauga rezultatul unei ferestre la noua lista
        p = p->next;
    }

    return s2;
}