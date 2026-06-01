#include <stdio.h>


typedef struct {
    int value;
    char name[20];
} Stat;

typedef struct {

    Stat stats[4];
    float price;
    float sell_percent;
} Item1;

typedef struct {
    Item1 items[10];

    Inventory1 previous_inv;
    Inventory1 next_inv;
} Inventory1;

typedef struct {
    Stat stats[4];
    
    int gold;

    char name[20];
    Inventory1 inv;
} Player;

void buy_item(Player* player, Item1 item)
{

}

void sell_item(Player* player, int index)
{

}

void undo(Player* player)
{
    player->inv.previous_inv.next_inv = player->inv;
    player->inv = player->inv.previous_inv;
}

void redo(Player* player)
{
    player->inv = player->inv.next_inv;
}






typedef struct 
{
    char name[20];
    int price;
    float sell_percent;

    int upgrade_price;
    Item upgrade_into;
} Item;

typedef struct 
{
    Item items[10];
    int gold;
} Inventory;

int main()
{
    printf("Hello world!\n");
    printf("Size of Stat: %llu\n", sizeof(Stat));
    printf("Size of Item1: %llu\n", sizeof(Item1));
    printf("Size of Inventory1: %llu\n", sizeof(Inventory1));
    printf("Size of Player: %llu\n", sizeof(Player));
    return 0;
}