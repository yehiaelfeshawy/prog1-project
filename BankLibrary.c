#include "BankLibraryH.h"

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
    {   fileUser[strcspn(fileUser,"\r\n")]='\0';
        filePass[strcspn(filePass,"\r\n")]='\0';
        if (strcmp(user, fileUser) == 0 && strcmp(pass, filePass) == 0)
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
sscanf(line,"%lld,%[^,],%[^,],%lf,%[^,],%d-%d,%[^\n]",
&acc[*count].accountNumber,
acc[*count].name,
acc[*count].email,
&acc[*count].balance,
acc[*count].mobile,
&acc[*count].opened.month,
&acc[*count].opened.year,
acc[*count].status);
acc[*count].name[strcspn(acc[*count].name, "\r\n")] = '\0';
acc[*count].email[strcspn(acc[*count].email, "\r\n")] = '\0';
acc[*count].mobile[strcspn(acc[*count].mobile, "\r\n")] = '\0';
acc[*count].status[strcspn(acc[*count].status, "\r\n")] = '\0';
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
getchar();
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
fgets(keyword, sizeof(keyword), stdin);
keyword[strcspn(keyword, "\n")] = '\0';
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
int addAccount(Account acc[], int *count, int max_acc)
{
    int i;
    Account newAcc;

    if (*count >= max_acc)
    {
        printf("Maximum number of accounts reached.\n");
        return 0;
    }

    printf("Enter Account Number: ");
    scanf("%lld", &newAcc.accountNumber);

    for (i = 0; i < *count; i++)
    {
        if (acc[i].accountNumber == newAcc.accountNumber)
        {
            printf("Duplicate account number!\n");
            return 0;
        }
    }

    getchar();
    printf("Enter Name: ");
    fgets(newAcc.name, sizeof(newAcc.name), stdin);
    newAcc.name[strcspn(newAcc.name, "\n")] = '\0';

    printf("Enter Email: ");
    fgets(newAcc.email, sizeof(newAcc.email), stdin);
    newAcc.email[strcspn(newAcc.email, "\n")] = '\0';

    printf("Enter Mobile: ");
    fgets(newAcc.mobile, sizeof(newAcc.mobile), stdin);
    newAcc.mobile[strcspn(newAcc.mobile, "\n")] = '\0';

    printf("Enter Initial Balance: ");
    scanf("%lf", &newAcc.balance);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    newAcc.opened.month = tm.tm_mon + 1;
    newAcc.opened.year  = tm.tm_year + 1900;

    strcpy(newAcc.status, "active");

    acc[*count] = newAcc;
    (*count)++;

    FILE *fp = fopen("accounts.txt","a");
    if(fp == NULL){
        printf("Error opening file to save account.\n");
        return 0;
    }
    fprintf(fp, "%lld,%s,%s,%.2lf,%s,%d-%d, %s\n",
            newAcc.accountNumber,
            newAcc.name,
            newAcc.email,
            newAcc.balance,
            newAcc.mobile,
            newAcc.opened.month,
            newAcc.opened.year,
            newAcc.status);
    fclose(fp);

    printf("Account added successfully.\n");
    printf("Date opened: %d-%d\n",newAcc.opened.month,newAcc.opened.year);
    return 1;
}

int deleteAccount(Account acc[], int *count)
{
    long long accNum;
    int i, j;

    printf("Enter Account Number to delete: ");
    scanf("%lld", &accNum);

    for (i = 0; i < *count; i++)
    {
    if (acc[i].accountNumber == accNum)
    {
    if (acc[i].balance != 0)
    {
    printf("Cannot delete account. Balance is not zero.\n");
    return 0;
    }
    for (j = i; j < *count - 1; j++)
    {
    acc[j] = acc[j + 1];
    }
    (*count)--;
    printf("Account deleted successfully.\n");
    return 1;
    }
    }

    printf("Account not found.\n");
    return 0;
}
int modifyAccount(Account acc[], int count){
long long accnum;
int i, found=0;
printf("enter your account number to modify: ");
scanf("%lld",&accnum);
getchar();
for(i=0;i<count;i++){
    if(acc[i].accountNumber==accnum){
        printf("\ncurrent name: %s\n",acc[i].name);
        printf("enter new name: ");
        fgets(acc[i].name,sizeof(acc[i].name),stdin);
        acc[i].name[strcspn(acc[i].name,"\n")]='\0';
        printf("\ncurrent email: %s\n",acc[i].email);
        printf("enter new email: ");
        fgets(acc[i].email,sizeof(acc[i].email),stdin);
        acc[i].email[strcspn(acc[i].email,"\n")]='\0';
        printf("current phone number: %s\n",acc[i].mobile);
        printf("enter new phone number: ");
        fgets(acc[i].mobile,sizeof(acc[i].mobile),stdin);
        acc[i].mobile[strcspn(acc[i].mobile,"\n")]='\0';
        printf("account modified succesfully.\n");
        found =1;
        break;
     }
}
if(!found){
    printf("account not found.\n");
    return 0;
}
return 1;
}

int changeStatus(Account acc[], int count){
long long accnum;
printf("Enter your account number to change status: ");
scanf("%lld",&accnum);
getchar();
int found=0, i;
for(i=0;i<count;i++){
    if(acc[i].accountNumber==accnum){
        found =1;
        break;
    }
}
if(!found){
    printf("Account not found.\n");
    return 0;
}
printf("Current status: %s\n",acc[i].status);
char newStatus[20];
printf("Enter desired status (active/inactive): ");
fgets(newStatus,sizeof(newStatus),stdin);
newStatus[strcspn(newStatus,"\n")]='\0';
if(strcmp(newStatus,"active")!=0&&strcmp(newStatus,"inactive")!=0){
    printf("Invalid choice. Please type 'active' or 'inactive'.\n");
    return 0;
}
if(strcmp(acc[i].status,newStatus)==0){
    printf("Account is already %s.\n",newStatus);
    return 0;
}
strcpy(acc[i].status,newStatus);
printf("Account status successfully changed to %s.\n",newStatus);
return 1;


}

int withdraw(Account acc[],int count){
long long accnum;
double amount;
int i,found=0;
printf("Enter account number: ");
scanf("%lld",&accnum);
while(getchar()!='\n');
for(i=0;i<count;i++){
    if(acc[i].accountNumber==accnum){
        found=1;
        break;
    }
}
if(!found){
    printf("Account does not exist.\n");
    return 0;
}
if(strcmp(acc[i].status,"inactive")==0){
    printf("Account is inactive. Withdrawals not allowed.\n");
    return 0;
}
printf("\nEnter withdrawal amount: ");
scanf("%lf",&amount);
if(amount<=0){
    printf("invalid amount");
    return 0;
}
if(amount>acc[i].balance){
    printf("Insufficient funds.\n");
    return 0;
}
if(acc[i].dailyWithdrawn+amount>50000){
    printf("Daily limit exceeded.\n");
    printf("You can withdraw up to %lf today.\n", 50000-acc[i].dailyWithdrawn);
    return 0;
}
acc[i].balance=acc[i].balance-amount;
acc[i].dailyWithdrawn=acc[i].dailyWithdrawn+amount;
printf("Withdrawal successful.\n");
printf("Remaining balance: %lf\n",acc[i].balance);
printf("Withdrawn today: %lf\n",acc[i].dailyWithdrawn);
return 1;
}
int deposit(Account acc[],int count){
long long accnum;
double amount;
int i, found=0;
printf("Enter your account number: ");
scanf("%lld",&accnum);
while(getchar()!='\n');
for(i=0;i<count;i++){
    if(acc[i].accountNumber==accnum){
        found=1;
        break;
    }
}
if(!found){
    printf("Account does not exist.\n");
    return 0;
}
if(strcmp(acc[i].status,"inactive")==0){
    printf("Account inactive. Deposit not allowed.\n");
    return 0;
}
printf("Enter deposit amount: ");
scanf("%lf",&amount);
if(amount<=0||amount>10000){
    printf("Invalid amount.\n");
    return 0;
}
acc[i].balance=acc[i].balance+amount;
printf("Deposit successful.\n");
printf("Current balance: %lf",acc[i].balance);
return 1;
}



void runSystem(void)
{
    int max_acc = 100, totalAccounts = 0;
    int choice;
    Account accounts[max_acc];

    if (!login())
        return;

    if (!loadAccounts(accounts, &totalAccounts))
        return;

    do
    {printf("\n Welcome to the menu \n");
        printf("1. Query by Account Number\n");
        printf("2. Advanced Search (by Name)\n");
        printf("3. Add Account\n");
        printf("4. Delete Account\n");
        printf("5. Modify Account\n");
        printf("6. Change Account Status\n");
        printf("7. Withdraw\n");
        printf("8. Deposit\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {case 1:
            query(accounts, totalAccounts);
            break;

        case 2:
            AdvancedSearch(accounts, totalAccounts);
            break;

        case 3:
            addAccount(accounts, &totalAccounts, max_acc);
            break;

        case 4:
            deleteAccount(accounts, &totalAccounts);
            break;

        case 5:
            modifyAccount(accounts, totalAccounts);
            break;

        case 6:
            changeStatus(accounts,totalAccounts);
            break;

        case 7:
            withdraw(accounts,totalAccounts);
            break;
         
        case 8:
            deposit(accounts,totalAccounts);
            break:
         
        case 0:
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid choice\n");}
    } while (choice != 0);
}
