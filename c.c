#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "header.h"

/* adauga in fata nodului de pe pozitia k un nou nod */
void add_node_k(List *s, List *new, int k)
{   
    List *p=s->next;
    int i;
    for(i=0; i<k; i++)
        p=p->next;
    
    p->prev->next = new;
    new->prev = p->prev;
    new->next = p;
    p->prev=new;
}

/* coeficient care va scadea influenta valorilor pe masura ce ne departam de 
interval */
double w(int i, int k)
{
    double j = i;  /// conversia lui i la double
    
    double num = (j/(k-1))*(j/(k-1))*0.9+0.1;  /// numitor
    double den = 0;                            /// numarator
    
    for(j=0; j<k; j++){
        den=den+(j/(k-1))*(j/(k-1))*0.9+0.1;
    }

    return num/den;
}

/* factor de scalare C */
double C(List *left, List *right, int timestamp)
{
    double num = timestamp - left->prev->elem.timestamp;
    double den = right->prev->elem.timestamp -left->prev->elem.timestamp;
    return num/den;
}

double f(List *left, List *right, int timestamp, int k)
{
    double s=0;
    int i;
    double C1 = C(left,right,timestamp);   /// factor de scalare
    for(i=0; i<k; i++){
        left=left->next;
        right=right->next;
        s=s+(1-C1)*left->elem.value*w(i,k);
        s=s+C1*right->elem.value*w(i,k);
    }
    return s;
}

/* realizeaza completarea datelor in lista s, unde k reprezeinta numarul de 
vecini pentru un interval */
void c(List *s, int k)
{
    List *p = s;
    List *last = s;
    
    int i;
    for(i=0; i<k; i++){
        p=p->next;
        last=last->prev;
    }

    int poz=k-1;
    while(p!=last){
        List *next=p->next;
        if(next->elem.timestamp - p->elem.timestamp > 1000){            
            
            List *left = (List *) malloc(sizeof(List));
            left->next = left->prev = left;

            List *right = (List *) malloc(sizeof(List));
            right->next = right->prev = right;
    
            List *p_left = p;
            List *p_right = p->next;

            for(i=0; i<k; i++){
                List *new = (List *) malloc(sizeof(List));
                new->elem = p_left->elem;
                add_node_k(left,new,0);
                p_left = p_left->prev;

                new = (List *) malloc(sizeof(List));
                new->elem = p_right->elem;
                add_node_k(right,new,0);
                p_right = p_right->next;   
            }

            int inf = p->elem.timestamp+200;
            int sup = next->elem.timestamp;

            for(i=inf; i < sup; i=i+200){
                List *new = (List *) malloc(sizeof(List));
                new->elem.timestamp = i;
                new->elem.value = f(left,right,i,k);
                add_node_k(s,new,poz+1);
                poz++;
            }
                    
            free_list(left);
            free_list(right);
        }
        poz++;
        p=next;
    }
}