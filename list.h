typedef struct Item{
    int timestamp;
    double value;
} Item;
typedef struct List{
    Item elem;
    struct List *next;
    struct List *prev;
} List;

void add_node(List *s, List *new);

int nr_list(List *s);

void print_list(List *s);

void free_list(List *s);