#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mani.h"

//function to add an expense
void adde()
{
    FILE *p;
    int n=1,c=0;
    Expense e;
    p=fopen("records.txt","ab");
    if(!p)
    {
        printf("File Error.");
        return;
    }
    while(n==1 && c<20)
    {
        printf("\nEnter date (e.g. 01 10 2025) :- ");
        scanf("%d %d %d",&e.date,&e.mon,&e.year);

        printf("Enter description :- ");
        getchar();
        fgets(e.des, sizeof(e.des), stdin);
        e.des[strcspn(e.des, "\n")] = '\0';

        printf("Enter expense :- ");
        scanf("%d",&e.cost);

        printf("Enter category option :-\n1)Medical  2)Food  3)Bills  4)Clothes  ");
        printf("5)Grocery  6)Maintenance  7)House helpers  8)Fees/Rent  9)Miscellaneous\n");
        scanf("%d",&e.cat);

        if (e.cat < 1 || e.cat > 9)
        {
            printf("Invalid category.\n");
            return;
        }

        printf("\nTo add more, press 1 ; else press any number : ");
        scanf("%d",&n);
        c++;

        fwrite(&e, sizeof(Expense), 1, p);
    }
    fclose(p);
}


//function to edit an expense
void edite() 
{
    int n;
    FILE *p;
    Expense e;

    p= fopen("records.txt", "r+b");
    if (!p) 
    {
        printf("Error opening file");
        exit(1);
    }

    printf("Enter record number to edit: ");
    scanf("%d",&n);
    fseek(p, (n- 1) * sizeof(Expense),SEEK_SET);
    
    if(fread(&e, sizeof(Expense), 1, p) != 1) 
    {
        printf("Record not found.\n");
        fclose(p);
        return;
    }

    printf("Editing record %d:\n", n);
    printf("Enter new date (DD MM YYYY): ");
    scanf("%d %d %d",&e.date,&e.mon,&e.year);

    getchar();
    printf("Enter new description: ");
    fgets(e.des, sizeof(e.des), stdin);
    e.des[strcspn(e.des, "\n")] = '\0';

    printf("Enter new cost: ");
    scanf("%d",&e.cost);

    printf("Enter new category (1-9):\n1)Medical  2)Food  3)Bills  4)Clothes  ");
    printf("5)Grocery  6)Maintenance  7)House helpers  8)Fees/Rent  9)Miscellaneous\n");
    scanf("%d",&e.cat);

    if(e.cat < 1 || e.cat > 9)
    {
        printf("Invalid category. Edit cancelled.\n");
        fclose(p);
        return;
    }

    fseek(p, (n- 1) * sizeof(Expense),SEEK_SET);
    if (fwrite(&e, sizeof(Expense), 1, p) != 1) 
    {
        perror("Error writing to file");
    }
    else
    {
        printf("Record updated successfully.\n");
    }
    fclose(p);
}


//function to view an expense
void viewe()
{
    FILE *p;
    char option;
    Expense e;
    int d,m,y,i=1,f=0,c=0;

    p = fopen("records.txt", "rb");
    if (!p) 
    {
        printf("Error opening file");
        return;
    }

    printf("Options for viewing records:-\nPress 'A' or 'a' -  all records.\nPress any character to view specific records - ");
    getchar();
    scanf("%c",&option);

    if(option=='A'||option=='a')
    {
        while(fread(&e,sizeof(Expense),1,p)==1)
        {
            printf("\nRecord number : %d\n",i);
            printf("Date : %d-%d-%d\n",e.date,e.mon,e.year);
            printf("Description: %s\n",e.des);
            printf("Cost: %d\n\n",e.cost);
            i++;
            c++;
        }
        if(c==0)
            printf("No records in the file.");
    }

    else
    {
        printf("Enter date to view record (e.g. 01 10 2025): ");
        scanf("%d %d %d",&d,&m,&y);

        while(fread(&e,sizeof(Expense),1,p)==1)
        {
            if (e.date==d && e.mon==m && e.year==y) 
            {
                printf("Date: %d-%d-%d\n",e.date, e.mon, e.year);
                printf("Description: %s\n", e.des);
                printf("Cost: %d\n\n", e.cost);
                f = 1;
            }
        }
        if(f==0)
            printf("No records found for the given date.");
    }

    fclose(p);
}



//Function to delete an event 
void dele()
{
    FILE *p, *t;
    char option, c;
    Expense e;
    int d, m, y, f = 0, recordCount = 0, choice;

    p = fopen("records.txt", "rb");
    if (!p) 
    {
        printf("Error opening file.\n");
        return;   
    }

    printf("Options for deleting records:-\n");
    printf("Press 'A' or 'a' to delete ALL records.\n");
    printf("Press any other key to delete a specific record.\n");
    getchar();
    scanf("%c", &option);

    if(option=='A'||option=='a')
    {
        printf("\nPress 'C'/'c' if you are sure to delete all records.\nNOTE: They can't be retrieved once deleted.\n");
        getchar();
        scanf("%c",&c);
        if(c=='C'||c=='c')
        {
            fclose(p);
            p = fopen("records.txt", "wb");
            if(p) fclose(p);
            printf("All records deleted.\n");
        }   
        else
        {
            printf("Deletion cancelled.\n");
            fclose(p);
        }
    }
    else
    {
        printf("Enter date of record to delete (DD MM YYYY): ");
        scanf("%d %d %d", &d, &m, &y);

        rewind(p);
        printf("\nRecords on %02d-%02d-%d:\n", d, m, y);
        printf("No.  Date        Description           Cost  Category\n");
        printf("-----------------------------------------------------\n");

        Expense records[50]; 
        int indices[50]; 
        int idx = 0;

        while(fread(&e, sizeof(Expense), 1, p) == 1)
        {
            if(e.date == d && e.mon == m && e.year == y)
            {
                idx++;
                records[idx-1] = e;
                printf("%-4d %02d-%02d-%d  %-20s %-5d  %-d\n", idx, e.date, e.mon, e.year, e.des, e.cost, e.cat);
                f = 1;
            }
        }

        if(!f)
        {
            printf("No records found for the given date.\n");
            fclose(p);
            return;
        }

        printf("\nEnter the number of the record you want to delete: ");
        scanf("%d", &choice);
        if(choice < 1 || choice > idx)
        {
            printf("Invalid choice.\n");
            fclose(p);
            return;
        }

        rewind(p);
        t = fopen("temp.txt", "wb");
        if(!t) { printf("File error.\n"); fclose(p); return; }

        while(fread(&e, sizeof(Expense), 1, p) == 1)
        {
            if(!(e.date == d && e.mon == m && e.year == y && strcmp(e.des, records[choice-1].des)==0 && e.cost == records[choice-1].cost && e.cat == records[choice-1].cat))
            {
                fwrite(&e, sizeof(Expense), 1, t);
            }
        }

        fclose(p);
        fclose(t);
        remove("records.txt");
        rename("temp.txt", "records.txt");
        printf("Record deleted successfully.\n");
    }
}
