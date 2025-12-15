#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{int month;
int year;
} Date;


typedef struct
{
long long accountNumber;
char name[100];
char email[100];
double balance;
char mobile[20];
Date opened;
char status[20];
} Account;
int login(void)
{
    FILE *fp;
    char fileUser[100], filePass[30];
    char user[100], pass[30];
    int found = 0;
    fp = fopen("users.txt", "r");
    if (fp == NULL)
    {printf("The file doesn't exist\n");
        return 0;}
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);
    getchar();
    while (fscanf(fp, "%s %s", fileUser, filePass) != EOF)
    {   if (strcmp(user, fileUser) == 0 && strcmp(pass, filePass) == 0)
        { found = 1; break;}
    }
    fclose(fp);

    if (found)
    { printf("Login successful\n");
        return 1; }
    else
    {printf("Try again invalid username or password\n");
        return 0; }
}
int loadAccounts(Account acc[], int *count)
{
FILE *fp;
char line[200];
int max_acc=100;
fp = fopen("accounts.txt", "r");
 if (fp == NULL)
    {printf("The file doesn't exist\n");
        return 0;}
*count = 0;


while (fgets(line, sizeof(line), fp) != NULL)
{
if (*count >= max_acc)
break;
sscanf(line,"%lld,%[^,],%[^,],%f,%[^,],%d-%d,%[^\n]",
&acc[*count].accountNumber,
acc[*count].name,
acc[*count].email,
&acc[*count].balance,
acc[*count].mobile,
&acc[*count].opened.month,
&acc[*count].opened.year,
acc[*count].status);
(*count)++;
}
fclose(fp);
return 1;
}


int main()
{ int max_acc=100,totalAccounts = 0;

Account accounts[max_acc];

login();
loadAccounts(accounts, &totalAccounts);


return 0;
}
