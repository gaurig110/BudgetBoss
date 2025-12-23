#include<stdio.h>
#include"options.h"

//list of choices
int menu()
{
    int f;
    printf("\n\n------BudgetBoss Main Menu------\n\nWhat would you like to do now??");
    printf("\n1)Add Expenses.\n2)View expenses.\n3)Edit expenses.\n4)Delete records.\n5)View Report.\n6)Calculate Monthly Total.\n7)Log Out?\n\n");
    scanf("%d",&f);
    return f;
}

//main menu
int first()
{
    int f;    
    printf("\n------Welcome To BudgetBoss------\n");
    printf("\n1)Register.\n2)Login.\n3)Exit.\n\n");
    scanf(" %3d",&f);
    return f;
}
