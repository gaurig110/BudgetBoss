#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"login.h"

void clear_input_buffer() 
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

//registration function
void regis()
{
    FILE *r;
    char u[20], p[20], existingUser[20], existingPass[20];
    int exists = 0;

    printf("----REGISTER PAGE----\nEnter username :- ");
    clear_input_buffer();
    fgets(u, sizeof(u), stdin);
    u[strcspn(u, "\n")] = '\0';

    printf("Enter password :- ");
    fgets(p, sizeof(p), stdin);
    p[strcspn(p, "\n")] = '\0';

    r = fopen("register.txt", "r");
    if (r) {
        while(fscanf(r, "%s %s", existingUser, existingPass) != EOF) {
            if(strcmp(u, existingUser) == 0) {
                exists = 1;
                break;
            }
        }
        fclose(r);
    }

    if(exists) {
        printf("\nUsername already registered. Try a different username.\n");
        return;
    }

    r = fopen("register.txt", "a");
    if(!r) {
        printf("\nREGISTRATION FILE NOT CREATED.\n");
        exit(0);
    }

    fprintf(r, "%s %s\n", u, p);
    printf("Registration Successful!!\n");
    fclose(r);
}



//if already registered
int auth()
{
    FILE *r;
    char u[20], p[20], user[20], pass[20], line[50];
    int foundUser = 0;

    printf("\n----LOGIN PAGE----\n");

    r = fopen("register.txt", "r");
    if(!r)
    {
        printf("File error.\n");
        return 0;
    }

    printf("Enter username :- ");
    clear_input_buffer();
    fgets(u, sizeof(u), stdin);
    u[strcspn(u, "\n")] = '\0';

    printf("Enter password :- ");
    fgets(p, sizeof(p), stdin);
    p[strcspn(p, "\n")] = '\0';

    while(fgets(line, sizeof(line), r) != NULL)
    {
        sscanf(line, "%s %s", user, pass);
        if(strcmp(u, user) == 0)
        {
            foundUser = 1;
            if(strcmp(p, pass) == 0)
            {
                printf("\nLogin Successful!\n");
                fclose(r);
                return 1;
            }
            else
            {
                printf("\nIncorrect password.\n");
                fclose(r);
                return 0;
            }
        }
    }

    fclose(r);
    if(!foundUser)
        printf("\nUsername not found.\n");

    return 0;
}

