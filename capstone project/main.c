#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_LINE 150

// Functions for all menu
void showWelcome();
void showMainMenu();
void handleStudent();
void handleManager();
void handleOwner();
int login(char *filename, char *role);
int signup(char *filename, char *role);
void clearInputBuffer();
void pressEnterToContinue();

int main() {
    int choice;

    showWelcome();

    while (1) {
        showMainMenu();
        printf("Please enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                handleStudent();
                break;
            case 2:
                handleManager();
                break;
            case 3:
                handleOwner();
                break;
            case 4:
                printf("\nThank you for using the University Hostel Management System!\n");
                printf("Have a great day ahead!\n");
                exit(0);
            default:
                printf("\nSorry, that's not a valid option.\n");
                printf("Please choose a number between 1 and 4.\n\n");
        }
    }

    return 0;
}

void showWelcome() {
    printf("\n===============================================\n");
    printf("    SMART HOSTEL MANAGEMENT SYSTEM\n");
    printf("         Welcome to your digital home!\n");
    printf("===============================================\n\n");
    printf("Hello there! We're glad you're here.\n");
    printf("This system will help you access all hostel services easily.\n");
    printf("Let's get you connected to the right portal.\n\n");
    pressEnterToContinue();
}

void showMainMenu() {
    printf("=============================================\n");
    printf("              SELECT YOUR ROLE\n");
    printf("=============================================\n");
    printf("1. Student Portal\n");
    printf("2. Manager Portal\n");
    printf("3. Owner Portal\n");
    printf("4. Exit System\n");
    printf("=============================================\n");
}

void handleStudent() {
    int action;

    printf("\n==========================================\n");
    printf("           STUDENT PORTAL\n");
    printf("==========================================\n");
    printf("Welcome to the student section!\n");
    printf("Here you can access your hostel account and services.\n\n");
    printf("1. Login to existing account\n");
    printf("2. Create new student account\n");
    printf("3. Return to main menu\n");
    printf("\nWhat would you like to do? ");
    scanf("%d", &action);
    clearInputBuffer();

    switch (action) {
        case 1:
            if (login("students.txt", "Student")) {
                printf("\n==========================================\n");
                printf("         STUDENT DASHBOARD\n");
                printf("==========================================\n");
                printf("Welcome back! Login successful.\n");
                printf("You now have access to:\n");
                printf("- Room booking and management\n");
                printf("- Hostel facilities information\n");
                printf("- Fee payment portal\n");
                printf("- Support and complaints\n");
                printf("\nEnjoy your hostel experience!\n");
                pressEnterToContinue();
            }
            break;
        case 2:
            if (signup("students.txt", "Student")) {
                printf("\nGreat! Your student account has been created successfully.\n");
                printf("You can now login with your new credentials.\n");
                printf("Welcome to our hostel community!\n");
                pressEnterToContinue();
            }
            break;
        case 3:
            printf("\nReturning to main menu...\n\n");
            break;
        default:
            printf("\nPlease select a valid option (1, 2, or 3).\n\n");
    }
}

void handleManager() {
    int action;

    printf("\n==========================================\n");
    printf("           MANAGER PORTAL\n");
    printf("==========================================\n");
    printf("Welcome to the management section!\n");
    printf("Your administrative access awaits.\n\n");
    printf("1. Login to manager account\n");
    printf("2. Register as new manager\n");
    printf("3. Return to main menu\n");
    printf("\nPlease choose an option: ");
    scanf("%d", &action);
    clearInputBuffer();

    switch (action) {
        case 1:
            if (login("managers.txt", "Manager")) {
                printf("\n==========================================\n");
                printf("         MANAGER DASHBOARD\n");
                printf("==========================================\n");
                printf("Welcome to your management console!\n");
                printf("You have access to:\n");
                printf("- Student account management\n");
                printf("- Room allocation system\n");
                printf("- Maintenance requests\n");
                printf("- Financial reports\n");
                printf("- Staff coordination\n");
                printf("\nReady to manage efficiently!\n");
                pressEnterToContinue();
            }
            break;
        case 2:
            if (signup("managers.txt", "Manager")) {
                printf("\nExcellent! Your manager account is now active.\n");
                printf("You can login and start managing hostel operations.\n");
                printf("Welcome to the management team!\n");
                pressEnterToContinue();
            }
            break;
        case 3:
            printf("\nReturning to main menu...\n\n");
            break;
        default:
            printf("\nInvalid selection. Please choose 1, 2, or 3.\n\n");
    }
}

void handleOwner() {
    int action;

    printf("\n==========================================\n");
    printf("            OWNER PORTAL\n");
    printf("==========================================\n");
    printf("Welcome to the executive control center!\n");
    printf("Complete system administration at your fingertips.\n\n");
    printf("1. Login to owner account\n");
    printf("2. Register as new owner\n");
    printf("3. Return to main menu\n");
    printf("\nSelect your preference: ");
    scanf("%d", &action);
    clearInputBuffer();

    switch (action) {
        case 1:
            if (login("owners.txt", "Owner")) {
                printf("\n==========================================\n");
                printf("         OWNER CONTROL PANEL\n");
                printf("==========================================\n");
                printf("Full system access granted!\n");
                printf("Your administrative privileges include:\n");
                printf("- Complete hostel oversight\n");
                printf("- Financial management and reports\n");
                printf("- Staff hiring and management\n");
                printf("- System configuration\n");
                printf("- Strategic planning tools\n");
                printf("\nAll systems under your control!\n");
                pressEnterToContinue();
            }
            break;
        case 2:
            if (signup("owners.txt", "Owner")) {
                printf("\nCongratulations! Owner account successfully established.\n");
                printf("You now have complete administrative control.\n");
                printf("Welcome to the executive level!\n");
                pressEnterToContinue();
            }
            break;
        case 3:
            printf("\nReturning to main menu...\n\n");
            break;
        default:
            printf("\nPlease enter a valid choice (1, 2, or 3).\n\n");
    }
}

int login(char *filename, char *role) {
    FILE *file;
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    char fileUsername[MAX_USERNAME], filePassword[MAX_PASSWORD];
    char line[MAX_LINE];
    int found = 0;

    printf("\n==========================================\n");
    printf("            %s LOGIN\n", role);
    printf("==========================================\n");
    printf("Please enter your login credentials.\n\n");

    // USERNAME AND PASSWORD USER ER THEKE NEYAR JONNO
    printf("Username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0'; // NEW LINE REMOVE KORAR JONNO

    printf("Password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0'; // SAME ASE BEFORE

    printf("\nVerifying your credentials...\n");

    // FILE READ KORAR JONNO
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nNo %s accounts found in the system.\n", role);
        printf("Please create an account first by selecting the signup option.\n\n");
        return 0;
    }


    while (fgets(line, MAX_LINE, file)) {
        // USERNAME AND PASSWORD FILE A STORE KORAR JONNO (format: username password)
        if (sscanf(line, "%s %s", fileUsername, filePassword) == 2) {
            if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
                found = 1;
                break;
            }
        }
    }

    fclose(file);

    if (!found) {
        printf("\nLogin failed. Username or password is incorrect.\n");
        printf("Please double-check your credentials and try again.\n");
        printf("Make sure there are no extra spaces in your input.\n\n");
        return 0;
    }

    printf("Authentication successful!\n");
    return 1; // Login successful
}

int signup(char *filename, char *role) {
    FILE *file;
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    char fileUsername[MAX_USERNAME], filePassword[MAX_PASSWORD];
    char line[MAX_LINE];
    int userExists = 0;

    printf("\n==========================================\n");
    printf("          %s REGISTRATION\n", role);
    printf("==========================================\n");
    printf("Let's create your new account.\n");
    printf("Please provide the following information:\n\n");


    printf("Choose a username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0';

    // Check kora je user ki faka username input dise naki
    if (strlen(username) == 0) {
        printf("\nUsername cannot be empty.\n");
        printf("Please enter a valid username for your account.\n\n");
        return 0;
    }

    printf("Create a password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0';

    // Check kora je password input ki faka naki
    if (strlen(password) == 0) {
        printf("\nPassword cannot be empty.\n");
        printf("Please create a secure password for your account.\n\n");
        return 0;
    }

    printf("\nChecking username availability...\n");

    // Check if username already taken or not
    file = fopen(filename, "r");
    if (file != NULL) {
        while (fgets(line, MAX_LINE, file)) {
            if (sscanf(line, "%s %s", fileUsername, filePassword) == 2) {
                if (strcmp(username, fileUsername) == 0) {
                    userExists = 1;
                    break;
                }
            }
        }
        fclose(file);
    }

    if (userExists) {
        printf("\nSorry, this username is already taken.\n");
        printf("Please choose a different username and try again.\n");
        printf("Consider adding numbers or variations to make it unique.\n\n");
        return 0;
    }

    // new user add kora file a
    file = fopen(filename, "a");
    if (file == NULL) {
        printf("\nSystem error: Unable to create account at this time.\n");
        printf("Please try again later or contact system administrator.\n\n");
        return 0;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("Account created successfully!\n");
    return 1; // Signup successful
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pressEnterToContinue() {
    printf("Press Enter to continue...");
    getchar();
    printf("\n");
}
