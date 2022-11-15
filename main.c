#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "header.h"      

/* adauga la sfarsitul unei liste cu santinela un nod nou */
void add_node(List *s, List *new)
{   
    s->prev->next = new;
    new->prev = s->prev;
    new->next = s;
    s->prev=new;
}

/* returneaza numarul de elemente dintr-o lista */
int nr_list(List *s)
{
    int nr=0;
    List *p;
    for(p=s->next; p!=s; p=p->next)
        nr++;

    return nr;
}

/* afiseaza lista */
void print_list(List *s)
{
    printf("%d\n",nr_list(s));
    
    List *p;
    for(p=s->next; p!=s; p=p->next)
        printf("%d %.2lf\n",p->elem.timestamp,p->elem.value);
}

/* eliberarea din memorie a unei liste */
void free_list(List *s)
{
    List *p;
    for(p=s->next->next; p!=s; p=p->next) 
        free(p->prev);
    free(p->prev);
    free(p);
}

int main(int argc, char *argv[]) 
{
    /* lista dubla circulara cu santinela */
    List *s = (List *) malloc(sizeof(List));
    s->next = s->prev = s;

    /* citirea datelor pentru lista initiala*/
    int n, i;
    scanf("%d",&n);
    for(i=0; i<n; i++){
        List *new = (List *) malloc(sizeof(List));
        scanf("%d%lf",&new->elem.timestamp,&new->elem.value);
        add_node(s,new);
    }

    /* realizarea filtrarilor primite in linia de comanda */
    int ok_st=0;
    for(i=1; i<argc; i++){
        /// Eliminare de exceptii folosind metode statistice
        if(strcmp(argv[i],"--e1")==0)
            e1(s,5);

        /// Eliminare de zgomot folosind filtrare mediana sau aritmetica
        if(strcmp(argv[i],"--e2")==0 || strcmp(argv[i],"--e3")==0){
            List *s2;
            s2=e23(s,s2,5,argv[i]);
            free_list(s);    
            s=s2;
        }

        /// Uniformizarea frecventei in timp a datelor
        if(strcmp(argv[i],"--u")==0)
            u(s);

        /// Completarea datelor
        if(strcmp(argv[i],"--c")==0)
            c(s,3);

        /// Statistici
        if(strstr(argv[i],"--st")!=0){  
                int k = 0;  /// intervalul de timp dorit
                int j;
                for(j=4; j<strlen(argv[i]); j++)
                    k = k*10 + argv[i][j] - '0';
                
                st(s,k);
                ok_st=1;
            }       
    }

    /* afisarea listei in urma filtrarilor, daca nu s-au cerut statistici */
    if(ok_st==0)
        print_list(s);

    /* eliberarea din memorie a listei */
    free_list(s);
}