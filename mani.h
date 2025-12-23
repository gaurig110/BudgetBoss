#ifndef MANI_H
#define MANI_H

typedef struct 
{
    int date;
    int mon;
    int year;
    char des[20];
    int cost;
    int cat;
} Expense;

void adde();
void edite();
void viewe();
void dele();

#endif