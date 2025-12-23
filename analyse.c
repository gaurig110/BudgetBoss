#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mani.h"
#include"analyse.h"

void report()
{
    FILE *p;
    Expense e;
    int total = 0;
    int categoryTotals[9] = {0};
    int categoryCount[9] = {0};
    const char *categories[9] = {"Medical", "Food", "Bills", "Clothes", "Grocery", "Maintenance", "House helpers", "Fees/Rent", "Miscellaneous"};

    p = fopen("records.txt", "rb");
    if(!p)
    {
        printf("File Error.\n");
        return;
    }

    while(fread(&e, sizeof(Expense), 1, p) == 1)
    {
        total += e.cost;
        if(e.cat >=1 && e.cat <=9)
        {
            categoryTotals[e.cat-1] += e.cost;
            categoryCount[e.cat-1]++;
        }
    }

    fclose(p);

    if(total == 0)
    {
        printf("No expense records found.\n");
        return;
    }

    printf("\n--- Expense Report ---\n");
    printf("Total Expenses: %d\n", total);
    printf("Category-wise Breakdown:\n");

    for(int i=0; i<9; i++)
    {
        if(categoryCount[i] > 0)
        {
            printf("%s: %d (Average: %.2f)\n", categories[i], categoryTotals[i], (float)categoryTotals[i]/categoryCount[i]);
        }
    }
}


void monthly()
{
    FILE *p;
    Expense e;
    int total = 0, month;

    p = fopen("records.txt", "rb");
    if(!p)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter month number (1-12): ");
    scanf("%d", &month);

    if(month < 1 || month > 12)
    {
        printf("Invalid month.\n");
        fclose(p);
        return;
    }

    while(fread(&e, sizeof(Expense), 1, p) == 1)
    {
        if(e.mon == month)
            total += e.cost;
    }

    fclose(p);

    printf("\n--- Monthly Expense Report ---\n");
    printf("Total Expenses for Month %d: %d\n", month, total);
}
