#include <stdio.h>
#include <string.h>

#define INV_MAX 45

typedef struct
{
    char name[20];
    int num;

    int maxCap;
} Item;

typedef struct 
{
    Item slots[INV_MAX];
} Inventory;


Item nullitem = {" ", 0, 0};

Item add_item(Inventory* inv, Item* item)
{
    Item res = *item;
    if(res.num == 0) return res;
    printf("res : %c %d %d\n", res.name[0], res.num, res.maxCap);
    int free_index = -1;
    for(int i=0; i<INV_MAX; i++)
    {
        Item* it = inv->slots+i;

        if(free_index == -1 && strcmp(it->name, nullitem.name)==0) free_index = i;

        if(strcmp(it->name, res.name)) 
        {
             printf("%d ", i);
            continue;
        }
        if(it->num >= res.maxCap)
        {
           if(i==0) printf("wtf - %d : %d", it->num, res.maxCap);
            continue;
        }

        it->num += res.num;
        res.num = 0;
        if(it->num > it->maxCap)
        {
            int exess = it->num - it->maxCap;
            it->num -= exess;

            Item ex = {"", exess, it->maxCap};
            strcpy(ex.name, it->name);

            res = add_item(inv, &ex);
        }

        break;
    }

    if(res.num > 0)
    {
        strcpy(inv->slots[free_index].name, res.name);
        res = add_item(inv, &res);
    }

    return res;
}

void drop_item(Inventory* inv, int index)
{
    inv->slots[index] = nullitem;
}


void print_inv(const Inventory* inv)
{
    for(int i=0; i<5; i++)
    {
        for(int j=0;j<9;j++)
        {
            Item it = inv->slots[i*9+j];
            printf("[%c - %d]", it.name[0], it.num);
        }
        printf("\n");
    }
}

void inv_init(Inventory* inv)
{
    for(int i=0;i<INV_MAX;i++)
    {
        inv->slots[i] = nullitem;
    }
}

int main()
{
    Inventory inv;
    Item dirt = {"dirt", 15, 64};
    inv_init(&inv);

    add_item(&inv, &dirt);

    print_inv(&inv);

    //add_item(&inv, &dirt);

    print_inv(&inv);

    return 0;
}