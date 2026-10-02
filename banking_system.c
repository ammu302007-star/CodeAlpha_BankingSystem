#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "accounts.dat"

/* Account structure */
struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

/* Clear leftover characters from input buffer */
void clearInputBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

/* Check whether an account already exists */
int accountExists(int accountNumber)
{
    FILE *file;
    struct Account account;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

/* Create a new account */
void createAccount(void)
{
    struct Account account;
    FILE *file;

    printf("\n=== Create Account ===\n");

    printf("Enter account number: ");

    if (scanf("%d", &account.accountNumber) != 1 ||
        account.accountNumber <= 0)
    {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }

    if (accountExists(account.accountNumber))
    {
        printf("Account number already exists.\n");
        return;
    }

    printf("Enter account holder name: ");
    scanf(" %49[^\n]", account.name);

    printf("Enter initial balance: ");

    if (scanf("%f", &account.balance) != 1 ||
        account.balance < 0)
    {
        printf("Invalid initial balance.\n");
        clearInputBuffer();
        return;
    }

    file = fopen(FILE_NAME, "ab");

    if (file == NULL)
    {
        printf("Unable to open account file.\n");
        return;
    }

    fwrite(&account, sizeof(struct Account), 1, file);
    fclose(file);

    printf("\nAccount created successfully.\n");
    printf("Account Number: %d\n", account.accountNumber);
}

/* Deposit money */
void deposit(void)
{
    FILE *file;
    struct Account account;
    int accountNumber;
    float amount;
    int found = 0;

    printf("\n=== Deposit ===\n");

    printf("Enter account number: ");

    if (scanf("%d", &accountNumber) != 1 ||
        accountNumber <= 0)
    {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter deposit amount: ");

    if (scanf("%f", &amount) != 1 ||
        amount <= 0)
    {
        printf("Deposit amount must be greater than zero.\n");
        clearInputBuffer();
        return;
    }

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            account.balance += amount;

            long offset =
                ftell(file) - (long)sizeof(struct Account);

            fseek(file, offset, SEEK_SET);

            fwrite(&account, sizeof(struct Account), 1, file);
            fflush(file);

            printf("\nDeposit successful!\n");
            printf("Deposited Amount: %.2f\n", amount);
            printf("New Balance: %.2f\n", account.balance);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Account not found.\n");
    }
}

/* Withdraw money */
void withdraw(void)
{
    FILE *file;
    struct Account account;
    int accountNumber;
    float amount;
    int found = 0;

    printf("\n=== Withdraw ===\n");

    printf("Enter account number: ");

    if (scanf("%d", &accountNumber) != 1 ||
        accountNumber <= 0)
    {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter withdrawal amount: ");

    if (scanf("%f", &amount) != 1 ||
        amount <= 0)
    {
        printf("Withdrawal amount must be greater than zero.\n");
        clearInputBuffer();
        return;
    }

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            found = 1;

            if (amount > account.balance)
            {
                printf("\nInsufficient balance.\n");
                fclose(file);
                return;
            }

            account.balance -= amount;

            long offset =
                ftell(file) - (long)sizeof(struct Account);

            fseek(file, offset, SEEK_SET);

            fwrite(&account, sizeof(struct Account), 1, file);
            fflush(file);

            printf("\nWithdrawal successful!\n");
            printf("Withdrawn Amount: %.2f\n", amount);
            printf("New Balance: %.2f\n", account.balance);

            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Account not found.\n");
    }
}

/* Balance enquiry */
void balanceEnquiry(void)
{
    FILE *file;
    struct Account account;
    int accountNumber;
    int found = 0;

    printf("\n=== Balance Enquiry ===\n");

    printf("Enter account number: ");

    if (scanf("%d", &accountNumber) != 1 ||
        accountNumber <= 0)
    {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            printf("\n-----------------------------\n");
            printf("Account Number: %d\n", account.accountNumber);
            printf("Account Holder: %s\n", account.name);
            printf("Current Balance: %.2f\n", account.balance);
            printf("-----------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Account not found.\n");
    }
}

/* Display complete account details */
void accountDetails(void)
{
    FILE *file;
    struct Account account;
    int accountNumber;
    int found = 0;

    printf("\n=== Account Details ===\n");

    printf("Enter account number: ");

    if (scanf("%d", &accountNumber) != 1 ||
        accountNumber <= 0)
    {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            printf("\n-----------------------------\n");
            printf("Account Number: %d\n", account.accountNumber);
            printf("Account Holder: %s\n", account.name);
            printf("Balance: %.2f\n", account.balance);
            printf("-----------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Account not found.\n");
    }
}

/* Search for an account */
void searchAccount(void)
{
    FILE *file;
    struct Account account;
    int accountNumber;
    int found = 0;

    printf("\n=== Search Account ===\n");

    printf("Enter account number: ");

    if (scanf("%d", &accountNumber) != 1 ||
        accountNumber <= 0)
    {
        printf("Invalid account number.\n");
        clearInputBuffer();
        return;
    }

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file))
    {
        if (account.accountNumber == accountNumber)
        {
            printf("\nAccount found!\n");
            printf("Account Number: %d\n", account.accountNumber);
            printf("Account Holder: %s\n", account.name);
            printf("Balance: %.2f\n", account.balance);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Account not found.\n");
    }
}

/* Main function */
int main(void)
{
    int choice;

    do
    {
        printf("\n========== BANK ACCOUNT MANAGEMENT SYSTEM ==========\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Account Details\n");
        printf("6. Search Account\n");
        printf("7. Exit\n");
        printf("===================================================\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a valid option.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                accountDetails();
                break;

            case 6:
                searchAccount();
                break;

            case 7:
                printf("\nThank you for using the Banking System!\n");
                break;

            default:
                printf("\nInvalid choice. Please select from 1 to 7.\n");
        }

    } while (choice != 7);

    return 0;
}
