#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"
#include "header.h"

/* sterge un nod cu anume timestamp din lista */
void delete_node(List *s, int timestamp)
{
    List *node; 
    node = s->next;
    /* se ajunge la nodul cu timestamp-ul de sters */
    while(node->elem.timestamp != timestamp)
        node = node->next;

    /* stergere nod */
    node->prev->next=node->next;
    node->next->prev=node->prev;
    free(node);
}

/* returneaza media valorilor numerice dintr-o fereastra de k elemente */
double average(List *l, int k)
{
    int i;
    double s = l->elem.value; /// s va retine media aritmetica
    List *right = l->next;    /// vecinii din dreapta
    List *left = l->prev;     /// vecinii din stanga
    for(i=0; i<k/2; i++){
        s = s + right->elem.value + left->elem.value;
        right = right->next;
        left = left->prev;
    }
    s = (double)s/k;

    return s;
}

/* returneaza deviatia standard a valorilor dintr-o fereastra cu k elemente */
double deviation(List *l, int k)
{
    int i;
    double m=average(l,k);    /// media valorilor numerice din fereastra

    /// s va retine deviatia standard
    double s = (l->elem.value-m)*(l->elem.value-m); 
    List *right = l->next;    /// vecinii din dreapta
    List *left = l->prev;     /// vecinii din stanga
    
    for(i=0; i<k/2; i++){
        s = s + (left->elem.value-m)*(left->elem.value-m);
        s = s + (right->elem.value-m)*(right->elem.value-m);
        right = right->next; 
        left = left->prev;
    }
    s = sqrt(s/k);

    return s;
}

/* realizeaza eliminarea de exceptii folosind statistici pentru lista s, unde
fereastra are dimensiune k */
void e1(List *s, int k)
{
    int i;
    List *p = s->next;      /// nodul curent dintr-un proces de aliminare
    List *last = s;         /// ultimul element din procesul de eliminare
    
    /* lista ce va contine pozitiile nodurilor ce trebuiesc eliminate in urma 
    filtrarii, pozitia fiind retinuta in campul timestamp */
    List *l = (List *) malloc(sizeof(List));
    l->next = l->prev = l;

    /* initializarea cu valorile corespunzatoare ale primului nod curent(p) si 
    ultimul nod(last) */  
    for(i=0; i<k/2; i++){
        p = p->next;
        last = last->prev;
    }

    while(p!=last){
        double inf = average(p,k)-deviation(p,k); /// limita inferioara 
        double sup = average(p,k)+deviation(p,k); /// limita superioara
        
        /// verificare daca nodul apartine intervalului
        if(p->elem.value < inf || p->elem.value > sup){
            List *new = (List *) malloc(sizeof(List));
            new->elem.timestamp = p->elem.timestamp; 
            add_node(l,new);        /// adaugare nod cu pozitia de eliminat 
        }
        p=p->next;
    }

    /* parcurgerea listei cu pozitii pentru a elimina din lista initiala si
    eliberarea ei din memorie */
    p = l->next;
    while(p!=l){
        delete_node(s,p->elem.timestamp);
        p=p->next;       
    }

    free_list(l);
}