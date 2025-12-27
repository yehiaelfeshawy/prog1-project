#ifndef BANKLIBRARYH_H_INCLUDED
#define BANKLIBRARYH_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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

int login(void);

int loadAccounts(Account acc[], int *count);

int query(Account acc[], int);
int AdvancedSearch(Account acc[], int);
int addAccount(Account acc[], int *count, int max_acc);

int deleteAccount(Account acc[], int *count);
int modifyAccount(Account acc[], int);
int withdraw(Account acc[],int);
int changeStatus(Account acc[],int);
int deposit(Account acc[],int);
int report(Account acc[], int count);
int transfer(Account acc[], int count);



void runSystem(void);

#endif // BANKLIBRARYH_H_INCLUDED

