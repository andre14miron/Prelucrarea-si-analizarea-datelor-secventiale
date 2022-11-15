#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "header.h"

void st(List *s, int k)
{
    sort_list(s);    /// ordonarea listei

    int sup;         /// limita superioara a unui interval
    if(s->next->elem.value>=0)
        sup=(int)(s->next->elem.value+k)/k*k;
    else 
        sup=(int)(s->next->elem.value)/k*k;
    
    int nr=0;        /// numarul de elemente care se afla intr-un interval
    int nr2=0;       /// numarul de elemente care se afla in doua intervale
    List *p;
    for(p=s->next; p!=s; p=p->next){
        if(p->elem.value < sup)
            nr++;
        else if(p->elem.value == sup){
            nr++;
            nr2++;
        }        
        else {
            printf("[%d, %d] %d\n",sup-k,sup,nr);
            nr=nr2+1;
            nr2=0;
            while(p->elem.value >= sup){
                sup=sup+k;
            }
        }
    }
    printf("[%d, %d] %d\n",sup-k,sup,nr);
}