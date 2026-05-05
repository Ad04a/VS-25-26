#include <stdio.h>
#include <string.h>

#define INV_LIMIT 36


int item_cap(char type)
{
    switch(type)
    {
        case 'm' : return 16;
        case 's' : return 1;
        default: return 64;
    }
}

typedef struct
{
    char name[20];
    int num;

    int maxNum;
} Item;

Item nullItem = {" ", 0, 0}; 

typedef struct 
{
    Item slots[INV_LIMIT];

} Inventory;


void init_inv(Inventory* inv)
{
    for(int i=0; i<INV_LIMIT; i++) inv->slots[i] = nullItem;
}

Item add_item(Inventory* inv, Item item)
{
    Item res = item;
    int free_index = -1;
    for(int i = 0; i<INV_LIMIT; i++)
    {

        Item* tmp = inv->slots + i;

        if(free_index == -1 && strcmp(tmp->name, " ")==0) free_index = i;

        if(strcmp(res.name, tmp->name)) continue;

        if(tmp->num >= tmp->maxNum) continue;

        tmp->num += res.num;

        if(tmp->num > tmp->maxNum)
        {
            int ex_num = tmp->num - tmp->maxNum;
            tmp->num = tmp->maxNum;

            Item ex = {"", ex_num, tmp->maxNum};
            strcpy(ex.name, tmp->name);
            res = add_item(inv, ex);
        }

    }

    if(res.num != 0 && free_index != -1)
    {
        inv->slots[free_index] = res;
        res = nullItem;
    }
    
    return res;
}

void drop_item(Inventory* inv, int index)
{
    inv->slots[index] = nullItem;
}

void print_item(const Item* item)
{
    printf("[%c - %d]", item->name[0], item->num);
}

void print_inv(const Inventory* inv)
{
    for(int i =0 ;i <4; i++)
    {
        for(int j=0; j<9; j++)
        {
            print_item(inv->slots + (i*4+j));
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    Inventory inv;
    init_inv(&inv);

    Item dirt = {"dirt", 63, item_cap('b')};

    add_item(&inv, dirt);
    add_item(&inv, dirt);
    add_item(&inv, dirt);

    drop_item(&inv, 1);

    print_inv(&inv);
    add_item(&inv, dirt);

    printf("\n");
    print_inv(&inv);
    return 0;
}