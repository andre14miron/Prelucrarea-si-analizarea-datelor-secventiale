#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "header.h"

/* realizeaza uniformizarea frecventei in timp a datelor pentru lista s */
void u(List *s)
{
    List *p;
    for(p=s->next->next; p!=s; p=p->next){
        /// diferenta temporala intre nodul actual si cel precedent
        double dif = (double)(p->elem.timestamp - p->prev->elem.timestamp)/1000;
        
        /// verificare daca diferenta se afla in interval [0.1,1]
        if((dif >= 0.1 && dif <= 1) || (dif >= -1 && dif <= -0.1)){
            /// inlocuirea cu noile valori
            p->elem.timestamp = (p->elem.timestamp+p->prev->elem.timestamp)/2;
            p->elem.value = (p->elem.value+p->prev->elem.value)/2;
        }
    }
}