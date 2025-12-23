#include<stdio.h>
#include<stdlib.h>
#include "login.h"
#include "options.h"
#include "mani.h"
#include "analyse.h"

int main()
{
    int r,menuchoice,mainchoice,flag=0;
    char c;
    do
    {
    flag=0;
    mainchoice=first();

    if(mainchoice==1)
    {
        regis();
        printf("If you want to continue,press Y or y. Else,press any character:- ");
        scanf(" %c", &c);
        if(c=='Y'||c=='y')
            flag=1;
        else
            flag=0;
    }

    else if(mainchoice==2)
    {
        r=auth();
        if(r!=1)
        {
            printf("\nAuthentication failed.\nTry again.\n");
            flag=1;
        }
        else
        {
            do
            { 
                menuchoice=menu();
                switch(menuchoice)
                {
                    case 1:
                    {
                        printf("\nNOTE: You can add maximum 20 inputs in one go.\n");
                        adde();
                        break;
                    }

                    case 2:
                    {
                        viewe();
                        break;
                    }

                    case 3:
                    {
                        edite();
                        break;
                    }

                    case 4:
                    {
                        dele();
                        break;
                    }

                    case 5:
                    {
                        report();
                        break;
                    }

                    case 6:
                    {
                        monthly();
                        break;
                    }

                    case 7:
                    {
                        printf("Logging Out...\nContinue? (Y/y): ");
                        scanf(" %c", &c);
                        if(c=='Y'||c=='y')
                            flag=1;
                        else
                            flag=0;
                        break;
                    }

                    default:
                    {
                        printf("Invalid input.\nIf you want to continue,press Y or y.Else,press any character:- ");
                        scanf(" %c",&c);
                        if(c=='Y'|| c=='y')
                            flag=1;
                        else 
                            flag=0;
                    }
                }
            }          
            while(menuchoice!=7);
        }
    }
        
    else if(mainchoice==3) 
    {
        printf("Exiting the app.\n");
        exit(0);
    }

    else
    {
        printf("Invalid Input.If you want to continue,press Y or y.Else,press any character:- ");
        scanf(" %c",&c);
        if(c=='Y' || c=='y')
            flag = 1;
        else
            flag = 0;
    }
    }
    while(flag);
    return 0;
}