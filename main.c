#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
int query(Account acc[], int count){
long long SearchNumber;
int i,found=0;
printf("Enter account number: ");
scanf("%lld",&SearchNumber);
for(i=0;i<count;i++){
    if(acc[i].accountNumber==SearchNumber){
        char *months[12]={"January","February","March","April","May","June",
        "July","August","September","October","November","December"};
        printf("\nAccount Number: %lld\n",acc[i].accountNumber);
        printf("Name: %s\n",acc[i].name);
        printf("E-mail: %s%\n",acc[i].email);
        printf("Balance: %lf $\n",acc[i].balance);
        printf("Mobile: %s\n",acc[i].mobile);
        printf("Date Opened: %s %d\n",months[acc[i].opened.month-1],acc[i].opened.year);
        printf("Status: %s\n",acc[i].status);
        found=1;
        break;
    }
}
if(!found)
    printf("Account is not found.\n");
return found;
}
int AdvancedSearch(Account acc[], int count){
char keyword[100];
int i,matches=0;
printf("Enter keyword: ");
getchar();
fgets(keyword,sizeof(keyword),stdin);
for(i=0;i<count;i++){
    if(strstr(acc[i].name,keyword)!=NULL){
        char *months[12]={"January","February","March","April","May","June",
        "July","August","September","October","November","December"};
        printf("\nAccount Number: %lld\n",acc[i].accountNumber);
        printf("Name: %s\n",acc[i].name);
        printf("E-mail: %s%\n",acc[i].email);
        printf("Balance: %lf $\n",acc[i].balance);
        printf("Mobile: %s\n",acc[i].mobile);
        printf("Date Opened: %s %d\n",months[acc[i].opened.month-1],acc[i].opened.year);
        printf("Status: %s\n",acc[i].status);
        matches++;
    }
}
if(matches==0)
    printf("Account is not found.\n");
return matches;
}

int main()
{ int max_acc=100,totalAccounts = 0;

Account accounts[max_acc];

login();
loadAccounts(accounts, &totalAccounts);


return 0;
}



