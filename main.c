#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TERMINAL_WIDTH 160

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Bright colors
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

// Background colors
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_LINE 150
#define MAX_NAME 50
#define OWNER_USERNAME "admin"
#define OWNER_PASSWORD "owner123"

char current_username[MAX_USERNAME];

typedef struct {
    int room_number;
    int floor;
    char room_type[20];
    int capacity;
    int occupied;
    float rent;
    char facilities[100];
    int available;
} Room;

typedef struct {
    int booking_id;
    char student_username[MAX_USERNAME];
    int room_number;
    char booking_date[20];
    char status[20];
    char student_name[MAX_NAME];
    char student_phone[20];
} Booking;

void showWelcome();
void showMainMenu();
void handleStudent();
int login(char *filename, char *role);
int signup(char *filename, char *role);
void clearInputBuffer();
void pressEnterToContinue();

void studentDashboard();
void viewAvailableRooms();
void bookRoomMenu();
void bookRoom();
void viewMyBookings();
void checkRoomDetails();
void requestCheckInOut();
void viewMyRoomDetails();
void submitComplaint();

void initializeRooms();
int isRoomAvailable(int room_number);
void saveBooking(Booking booking);
int generateBookingId();
void getCurrentDate(char *date);

void handleManager();
void managerDashboard();
int managerLogin();

void viewAllBookings();
void approveRejectBookings();
void viewAllStudents();
void manageRooms();
void viewComplaints();
void respondToComplaint();
void processCheckinRequests();
void generateReports();

void handleOwner();
void ownerDashboard();
int ownerLogin();
void viewAllManagers();
void approveRejectManagerRequests();
void addNewManager();
void removeManager();
void setHostelRules();
void viewHostelRules();
void generateOwnerReports();
void viewAllHostelData();
void manageSystemSettings();
void viewComplaintsAsOwner();
void clearInputBuffer();
void pressEnterToContinue();
void getCurrentDate(char *date);

int main() {
    int choice;

    initializeRooms();

    showWelcome();

    while (1) {
        showMainMenu();
        printf("Please enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                handleStudent();
                system("cls");
                break;
            case 2:
                handleManager();
                system("cls");
                break;
            case 3:
                handleOwner();
                system("cls");
                break;
            case 4:
                printf("\nThank you for using the University Hostel Management System!\n");
                printf("Have a great day ahead!\n");
                system("cls");
                exit(0);
            default:
                printf("\nSorry, that's not a valid option.\n");
                printf("Please choose a number between 1 and 4.\n\n");
        }
    }

    return 0;
}

void showWelcome() {
    printCentered(BRIGHT_GREEN"WELCOME TO OUR \n \n \n \n \n \n"RESET);
    printf(BRIGHT_RED " __    __    ______        _______.___________. _______  __         .___  ___.      ___   .___________. _______ \n" RESET);
    printf(RED "|  |  |  |  /  __  \\      /       |           ||   ____||  |        |   \\/   |     /   \\  |           ||   ____|\n" RESET);
    printf(BRIGHT_YELLOW "|  |__|  | |  |  |  |    |   (----`---|  |----`|  |__   |  |        |  \\  /  |    /  ^  \\ `---|  |----`|  |__   \n" RESET);
    printf(YELLOW "|   __   | |  |  |  |     \\   \\       |  |     |   __|  |  |        |  |\\/|  |   /  /_\\  \\    |  |     |   __| \n" RESET);
    printf(BRIGHT_RED "|  |  |  | |  `--'  | .----)   |      |  |     |  |____ |  `----.   |  |  |  |  /  _____  \\   |  |     |  |____ \n" RESET);
    printf(RED "|__|  |__|  \\______/  |_______/       |__|     |_______||_______|   |__|  |__| /__/     \\__\\  |__|     |_______|\n\n\n\n\n\n" RESET);
    pressEnterToContinue();
    system("cls");
}

void showMainMenu() {
    printCentered("SELECT YOUR ROLE\n");
    printCentered(BRIGHT_GREEN"1. Student \n"RESET);
    printCentered(BRIGHT_GREEN"2. Manager \n"RESET);
    printCentered(BRIGHT_GREEN"3. Owner \n"RESET);
    printCentered("4. Exit System\n");
    printCentered("=============================================\n");
}

void handleStudent() {
    int action;
    system("cls");

    printCentered(BRIGHT_RED"STUDENT DormDesk\n"RESET);
    printCentered("Welcome to the student section!\n");
    printCentered("Here you can access your hostel account and services.\n\n");
    printCentered(BRIGHT_GREEN"1. Login to existing account\n"RESET);
    printCentered(BRIGHT_GREEN"2. Create new student account\n"RESET);
    printCentered(BRIGHT_GREEN"3. Return to main menu\n\n\n\n\n"RESET);
    printf(YELLOW"\nWhat would you like to do? coice your number :  "RESET);

    if (scanf("%d", &action) != 1) {
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (action) {
        case 1:
            if (login("students.txt", "Student")) {
                printCentered(RED"STUDENT DASHBOARD\n"RESET);
                printCentered("Welcome back!\n");
                studentDashboard();
            }
            break;
        case 2:
            if (signup("students.txt", "Student")) {
                printf("\nGreat! Your student account has been created successfully.\n");
                printf("You can now login with your new username and password.\n");
                printf("Welcome to our hostel!\n");
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

void studentDashboard() {
    int choice;

    while (1) {
        system("cls");
        printCentered(BLUE"              STUDENT DASHBOARD\n"RESET);
        printCentered(RED"========================================================\n"RESET);
        printf("Welcome back, %s!\n\n", current_username);
        printCentered(GREEN"1. View Available Rooms\n"RESET);
        printCentered(GREEN"2. Book a Room\n"RESET);
        printCentered(GREEN"3. Request Check-in / Check-out\n"RESET);
        printCentered(GREEN"4. View My Room Details\n"RESET);
        printCentered(GREEN"5. Submit a Complaint\n"RESET);
        printCentered(GREEN"6. Logout\n"RESET);
        printf(YELLOW"\nEnter your choice: "RESET);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                viewAvailableRooms();
                system("cls");
                break;
            case 2:
                bookRoomMenu();
                system("cls");
                break;
            case 3:
                requestCheckInOut();
                system("cls");
                break;
            case 4:
                viewMyRoomDetails();
                system("cls");
                break;
            case 5:
                submitComplaint();
                system("cls");
                break;
            case 6:
                printf("\nLogging out...\n");
                system("cls");
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
        pressEnterToContinue();
    }
}

void bookRoomMenu() {
    int choice;

    while (1) {
        system("cls");
        printCentered(BLUE"ROOM BOOKING MENU\n"RESET);
        printCentered(RED"========================================================\n"RESET);
        printCentered(GREEN"1. Book a Room\n"RESET);
        printCentered(GREEN"2. View My Bookings\n"RESET);
        printCentered(GREEN"3. Check Room Details\n"RESET);
        printCentered("4. Return to Dashboard\n");
        printf(YELLOW"\nEnter your choice: "RESET);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                bookRoom();
                system("cls");
                break;
            case 2:
                viewMyBookings();
                system("cls");
                break;
            case 3:
                checkRoomDetails();
                system("cls");
                break;
            case 4:
                printf("\nReturning to dashboard...\n");
                system("cls");
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
        pressEnterToContinue();
    }
}

void initializeRooms() {
    FILE *file = fopen("rooms.txt", "r");
    if (file != NULL) {
        fclose(file);
        return; // Rooms already initialized
    }

    file = fopen("rooms.txt", "w");
    if (file == NULL) {
        printf("Error creating rooms file.\n");
        return;
    }

    fprintf(file, "101 1 Single 1 0 8000.00 AC,WiFi,Study_Table 1\n");
    fprintf(file, "102 1 Double 2 0 6000.00 AC,WiFi,Study_Table 1\n");
    fprintf(file, "103 1 Triple 3 0 4500.00 WiFi,Study_Table 1\n");
    fprintf(file, "201 2 Single 1 0 8500.00 AC,WiFi,Study_Table,Balcony 1\n");
    fprintf(file, "202 2 Double 2 0 6500.00 AC,WiFi,Study_Table,Balcony 1\n");
    fprintf(file, "203 2 Triple 3 0 5000.00 WiFi,Study_Table,Balcony 1\n");
    fprintf(file, "301 3 Single 1 0 9000.00 AC,WiFi,Study_Table,Balcony,Nature_view 1\n");
    fprintf(file, "302 3 Double 2 0 7000.00 AC,WiFi,Study_Table,Balcony,Nature_View 1\n");

    fclose(file);
}

void viewAvailableRooms() {
    FILE *file = fopen("rooms.txt", "r");
    if (file == NULL) {
        printf("Error accessing room information.\n");
        return;
    }

    Room room;
    int found = 0;
    system("cls");

    printCentered(BLUE"AVAILABLE ROOMS\n"RESET);
    printCentered(RED"========================================================\n"RESET);
    printf("Room No. | Floor | Type   | Capacity | Rent     | Facilities\n");
    printf("--------------------------------------------------------\n");

    while (fscanf(file, "%d %d %s %d %d %f %s %d",
                  &room.room_number, &room.floor, room.room_type,
                  &room.capacity, &room.occupied, &room.rent,
                  room.facilities, &room.available) == 8) {

        if (room.available == 1 && room.occupied < room.capacity) {
            printf(YELLOW"%-8d | %-5d | %-6s | %-8d | %-8.2f | %s\n"RESET,
                   room.room_number, room.floor, room.room_type,
                   room.capacity, room.rent, room.facilities);
            found = 1;
        }
    }

    if (!found) {
        printf("No rooms available at the moment.\n");
    }

    printf("========================================================\n");
    fclose(file);
}

void bookRoom() {
    int room_number;
    Booking booking;
    system("cls");

    printCentered(BRIGHT_RED"                    ROOM BOOKING\n"RESET);
    printCentered(BRIGHT_BLUE"========================================================\n"RESET);

    viewAvailableRooms();

    printf(YELLOW"\nEnter the room number you want to book: "RESET);
    if (scanf("%d", &room_number) != 1) {
        printf("Invalid room number!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (!isRoomAvailable(room_number)) {
        printf("Sorry, this room is not available for booking.\n");
        return;
    }

    printf("Enter your full name: ");
    fgets(booking.student_name, sizeof(booking.student_name), stdin);
    booking.student_name[strcspn(booking.student_name, "\n")] = '\0';

    printf("Enter your phone number: ");
    fgets(booking.student_phone, sizeof(booking.student_phone), stdin);
    booking.student_phone[strcspn(booking.student_phone, "\n")] = '\0';

    booking.booking_id = generateBookingId();
    booking.room_number = room_number;
    strcpy(booking.student_username, current_username);
    getCurrentDate(booking.booking_date);
    strcpy(booking.status, "Pending");

    saveBooking(booking);
    system("cls");

    printCentered(BRIGHT_RED"BOOKING SUBMITTED SUCCESSFULLY!\n"RESET);
    printCentered(BRIGHT_BLUE"========================================================\n"RESET);
    printf("Booking ID: %d\n", booking.booking_id);
    printf("Room Number: %d\n", booking.room_number);
    printf("Student: %s\n", booking.student_name);
    printf("Phone: %s\n", booking.student_phone);
    printf("Booking Date: %s\n", booking.booking_date);
    printf("Status: %s\n\n\n", booking.status);
    printf(YELLOW"\nYour booking request has been sent to the manager for approval.\n"RESET);
    printf("You will be notified once it's processed.\n");
}

void viewMyBookings() {
    FILE *file = fopen("bookings.txt", "r");
    if (file == NULL) {
        printf("No booking records found.\n");
        return;
    }

    Booking booking;
    int found = 0;
    system("cls");

    printCentered(BRIGHT_RED"                     MY BOOKINGS\n"RESET);
    printCentered(BRIGHT_BLUE"========================================================\n"RESET);
    printf("Booking ID | Room No. | Date       | Status   | Student Name\n");
    printf("--------------------------------------------------------\n");

    while (fscanf(file, "%d %s %d %s %s %s %s",
                  &booking.booking_id, booking.student_username,
                  &booking.room_number, booking.booking_date,
                  booking.status, booking.student_name,
                  booking.student_phone) == 7) {

        if (strcmp(booking.student_username, current_username) == 0) {
            printf(YELLOW"%-10d | %-8d | %-10s | %-8s | %s\n"RESET,
                   booking.booking_id, booking.room_number,
                   booking.booking_date, booking.status, booking.student_name);
            found = 1;
        }
    }

    if (!found) {
        printf(BRIGHT_YELLOW"No bookings found for your account.\n"RESET);
    }

    printf("========================================================\n");
    fclose(file);
}

void checkRoomDetails() {
    int room_number;
    FILE *file = fopen("rooms.txt", "r");
    if (file == NULL) {
        printf("Error accessing room information.\n");
        return;
    }

    printf(YELLOW"Enter room number to check details: "RESET);
    if (scanf("%d", &room_number) != 1) {
        printf("Invalid room number!\n");
        clearInputBuffer();
        fclose(file);
        return;
    }
    clearInputBuffer();

    Room room;
    int found = 0;

    while (fscanf(file, "%d %d %s %d %d %f %s %d",
                  &room.room_number, &room.floor, room.room_type,
                  &room.capacity, &room.occupied, &room.rent,
                  room.facilities, &room.available) == 8) {

        if (room.room_number == room_number) {
            system("cls");
            printCentered(BRIGHT_RED"                   ROOM DETAILS\n"RESET);
            printCentered(BRIGHT_BLUE"========================================================\n"RESET);
            printf("Room Number: %d\n", room.room_number);
            printf("Floor: %d\n", room.floor);
            printf("Room Type: %s\n", room.room_type);
            printf("Capacity: %d students\n", room.capacity);
            printf("Currently Occupied: %d students\n", room.occupied);
            printf("Monthly Rent: %.2f BDT\n", room.rent);
            printf("Facilities: %s\n", room.facilities);
            printf("Status: %s\n", room.available ? "Available" : "Not Available");
            printf("========================================================\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Room number %d not found.\n", room_number);
    }

    fclose(file);
}

void requestCheckInOut() {
    int choice;
    system("cls");
    printCentered(BRIGHT_RED"              CHECK-IN / CHECK-OUT REQUEST\n"RESET);
    printCentered(BRIGHT_BLUE"========================================================\n"RESET);
    printCentered(BRIGHT_GREEN"1. Request Check-in\n"RESET);
    printCentered(BRIGHT_GREEN"2. Request Check-out\n"RESET);
    printCentered(BRIGHT_GREEN"3. View Check-in/Check-out Status\n"RESET);
    printCentered("4. Return to Dashboard\n");
    printf(BRIGHT_YELLOW"\nEnter your choice: "RESET);

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *file;
    char date[20];

    switch (choice) {
        case 1:
            getCurrentDate(date);
            printf("\nSubmitting check-in request...\n");

            file = fopen("checkin_requests.txt", "a");
            if (file != NULL) {
                fprintf(file, "%s CHECK_IN %s Pending\n", current_username, date);
                fclose(file);
                printf("Check-in request submitted successfully!\n");
                printf("You will be notified once it's processed by the manager.\n");
            } else {
                printf("Error submitting request. Please try again.\n");
            }
            break;

        case 2:
            getCurrentDate(date);
            printf("\nSubmitting check-out request...\n");

            file = fopen("checkout_requests.txt", "a");
            if (file != NULL) {
                fprintf(file, "%s CHECK_OUT %s Pending\n", current_username, date);
                fclose(file);
                printf("Check-out request submitted successfully!\n");
                printf("You will be notified once it's processed by the manager.\n");
            } else {
                printf("Error submitting request. Please try again.\n");
            }
            break;

        case 3:
            printCentered(BRIGHT_BLUE"\n========================================================\n"RESET);
            printCentered(BRIGHT_RED"              YOUR REQUEST STATUS\n"RESET);
            printCentered(BRIGHT_BLUE"========================================================\n"RESET);

            file = fopen("checkin_requests.txt", "r");
            int found = 0;
            if (file != NULL) {
                char username[MAX_USERNAME], type[20], date_str[20], status[20];

                while (fscanf(file, "%s %s %s %s", username, type, date_str, status) == 4) {
                    if (strcmp(username, current_username) == 0) {
                        printf("Check-in Request - Date: %s, Status: %s\n", date_str, status);
                        found = 1;
                    }
                }
                fclose(file);
            }

            file = fopen("checkout_requests.txt", "r");
            if (file != NULL) {
                char username[MAX_USERNAME], type[20], date_str[20], status[20];

                while (fscanf(file, "%s %s %s %s", username, type, date_str, status) == 4) {
                    if (strcmp(username, current_username) == 0) {
                        printf("Check-out Request - Date: %s, Status: %s\n", date_str, status);
                        found = 1;
                    }
                }
                fclose(file);
            }

            if (!found) {
                printf("No requests found.\n");
            }
            break;

        case 4:
            return;

        default:
            printf("\nInvalid choice. Please try again.\n");
    }
}

void viewMyRoomDetails() {
    FILE *file = fopen("bookings.txt", "r");
    if (file == NULL) {
        printf("No booking records found.\n");
        return;
    }

    Booking booking;
    int found = 0;
    int assigned_room = 0;

    while (fscanf(file, "%d %s %d %s %s %s %s",
                  &booking.booking_id, booking.student_username,
                  &booking.room_number, booking.booking_date,
                  booking.status, booking.student_name,
                  booking.student_phone) == 7) {

        if (strcmp(booking.student_username, current_username) == 0 &&
            strcmp(booking.status, "Approved") == 0) {
            assigned_room = booking.room_number;
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printCentered(BRIGHT_RED"NO ROOM ASSIGNED\n"RESET);
        printCentered(BRIGHT_BLUE"========================================================\n"RESET);
        printf("You don't have any approved room booking yet.\n");
        printf("Please book a room and wait for manager approval.\n");
        return;
    }

    file = fopen("rooms.txt", "r");
    if (file == NULL) {
        printf("Error accessing room information.\n");
        return;
    }

    Room room;
    int room_found = 0;

    while (fscanf(file, "%d %d %s %d %d %f %s %d",
                  &room.room_number, &room.floor, room.room_type,
                  &room.capacity, &room.occupied, &room.rent,
                  room.facilities, &room.available) == 8) {

        if (room.room_number == assigned_room) {
            printCentered(BRIGHT_RED"MY ROOM DETAILS\n"RESET);
            printCentered(BRIGHT_BLUE"========================================================\n"RESET);
            printf("Student Name: %s\n", booking.student_name);
            printf("Username: %s\n", current_username);
            printf("Phone: %s\n", booking.student_phone);
            printf("Room Number: %d\n", room.room_number);
            printf("Floor: %d\n", room.floor);
            printf("Room Type: %s\n", room.room_type);
            printf("Capacity: %d students\n", room.capacity);
            printf("Currently Occupied: %d students\n", room.occupied);
            printf("Monthly Rent: %.2f BDT\n", room.rent);
            printf("Facilities: %s\n", room.facilities);
            printf("Booking Date: %s\n", booking.booking_date);
            printf("Booking Status: %s\n", booking.status);
            printf("========================================================\n");
            room_found = 1;
            break;
        }
    }

    if (!room_found) {
        printf("Error: Room details not found.\n");
    }

    fclose(file);
}

void submitComplaint() {
    char complaint[500];
    char subject[100];

    printCentered(BRIGHT_RED"SUBMIT A COMPLAINT\n"RESET);
    printCentered(BRIGHT_BLUE"========================================================\n"RESET);

    printf(BRIGHT_YELLOW"Enter complaint subject: "RESET);
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\n")] = '\0';

    if (strlen(subject) == 0) {
        printf("Subject cannot be empty.\n");
        return;
    }

    printf("Enter your complaint details: ");
    fgets(complaint, sizeof(complaint), stdin);
    complaint[strcspn(complaint, "\n")] = '\0';

    if (strlen(complaint) == 0) {
        printf("Complaint details cannot be empty.\n");
        return;
    }

    FILE *file = fopen("complaints.txt", "a");
    if (file == NULL) {
        printf("Error submitting complaint. Please try again.\n");
        return;
    }

    char date[20];
    getCurrentDate(date);

    fprintf(file, "%s | %s | %s | %s | Pending\n",
            current_username, date, subject, complaint);
    fclose(file);

    printCentered(BRIGHT_RED"COMPLAINT SUBMITTED SUCCESSFULLY!\n"RESET);
    printCentered(BRIGHT_BLUE"========================================================\n"RESET);
    printf("Subject: %s\n", subject);
    printf("Date: %s\n", date);
    printf("Status: Pending\n");
    printf(BRIGHT_YELLOW"\nYour complaint has been forwarded to the management.\n"RESET);
    printf(BRIGHT_YELLOW"You will receive a response within 24-48 hours.\n"RESET);
}

int isRoomAvailable(int room_number) {
    FILE *file = fopen("rooms.txt", "r");
    if (file == NULL) {
        return 0;
    }

    Room room;
    while (fscanf(file, "%d %d %s %d %d %f %s %d",
                  &room.room_number, &room.floor, room.room_type,
                  &room.capacity, &room.occupied, &room.rent,
                  room.facilities, &room.available) == 8) {

        if (room.room_number == room_number) {
            fclose(file);
            return (room.available == 1 && room.occupied < room.capacity);
        }
    }

    fclose(file);
    return 0;
}

void saveBooking(Booking booking) {
    FILE *file = fopen("bookings.txt", "a");
    if (file == NULL) {
        printf("Error saving booking information.\n");
        return;
    }

    fprintf(file, "%d %s %d %s %s %s %s\n",
            booking.booking_id, booking.student_username,
            booking.room_number, booking.booking_date,
            booking.status, booking.student_name,
            booking.student_phone);

    fclose(file);
}

int generateBookingId() {
    FILE *file = fopen("bookings.txt", "r");
    int max_id = 1000;
    Booking booking;

    if (file != NULL) {
        while (fscanf(file, "%d %s %d %s %s %s %s",
                      &booking.booking_id, booking.student_username,
                      &booking.room_number, booking.booking_date,
                      booking.status, booking.student_name,
                      booking.student_phone) == 7) {
            if (booking.booking_id > max_id) {
                max_id = booking.booking_id;
            }
        }
        fclose(file);
    }

    return max_id + 1;
}

void getCurrentDate(char *date) {
    strcpy(date, "02/08/2025");
}

void handleManager() {
    int action;
    system("cls");

    printCentered(BRIGHT_RED"MANAGER HostelCommand\n"RESET);
    printCentered(BRIGHT_BLUE"Welcome to the management section!\n"RESET);
    printCentered(BRIGHT_GREEN"1. Login to manager account\n"RESET);
    printCentered(BRIGHT_GREEN"2. Return to main menu\n"RESET);
    printf(BRIGHT_YELLOW"\nPlease choose an option: "RESET);

    if (scanf("%d", &action) != 1) {
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (action) {
        case 1:
            if (managerLogin()) {
                managerDashboard();
            }
            system("cls");
            break;

        case 2:
            printf("\nReturning to main menu...\n\n");
            system("cls");
            break;
        default:
            printf("\nInvalid selection. Please choose 1, 2,.\n\n");
    }
}

int managerLogin() {
    FILE *file;
    char password[MAX_PASSWORD];
    char fileUsername[MAX_USERNAME], filePassword[MAX_PASSWORD], status[20];
    char line[MAX_LINE];
    int found = 0;
    system("cls");

    printCentered(BRIGHT_RED"MANAGER LOGIN\n"RESET);
    printCentered(BRIGHT_BLUE"Please enter your login information.\n\n"RESET);

    printf(BRIGHT_YELLOW"Username: "RESET);
    fgets(current_username, MAX_USERNAME, stdin);
    current_username[strcspn(current_username, "\n")] = '\0';

    printf(BRIGHT_YELLOW"Password: "RESET);
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf(BRIGHT_GREEN"\nVerifying your information...\n"RESET);

    file = fopen("managers.txt", "r");
    if (file == NULL) {
        printf("\nNo manager accounts found in the system.\n");
        printf("Please request registration first.\n\n");
        return 0;
    }

    while (fgets(line, MAX_LINE, file)) {
        if (sscanf(line, "%s %s %s", fileUsername, filePassword, status) == 3) {
            if (strcmp(current_username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
                if (strcmp(status, "Active") == 0) {
                    found = 1;
                    break;
                } else if (strcmp(status, "Pending") == 0) {
                    printf("\nYour account is pending owner approval.\n");
                    printf("Please wait for activation.\n\n");
                    fclose(file);
                    return 0;
                } else {
                    printf("\nYour account has been rejected or suspended.\n");
                    printf("Please contact the owner for more information.\n\n");
                    fclose(file);
                    return 0;
                }
            }
        }
    }

    fclose(file);

    if (!found) {
        printf("\nLogin failed. Username or password is incorrect.\n");
        printf("Please double-check your information and try again.\n\n");
        return 0;
    }

    printf("Login successful!\n");
    pressEnterToContinue();
    return 1;
}


void managerDashboard() {
    int choice;

    while (1) {
        system("cls");
        printCentered(BRIGHT_RED"              MANAGER DASHBOARD\n"RESET);
        printCentered(BRIGHT_BLUE"========================================================\n"RESET);
        printf("Welcome back, %s!\n\n", current_username);
        printCentered(BRIGHT_GREEN"1. View All Booking Requests\n"RESET);
        printCentered(BRIGHT_GREEN"2. Approve/Reject Bookings\n"RESET);
        printCentered(BRIGHT_GREEN"3. View All Students\n"RESET);
        printCentered(BRIGHT_GREEN"4. Manage Room Availability\n"RESET);
        printCentered(BRIGHT_GREEN"5. View Complaints\n"RESET);
        printCentered(BRIGHT_GREEN"6. Respond to Complaints\n"RESET);
        printCentered(BRIGHT_GREEN"7. Process Check-in/Check-out Requests\n"RESET);
        printCentered(BRIGHT_GREEN"8. Generate Reports\n"RESET);
        printCentered("9. Logout\n");
        printf(BRIGHT_YELLOW"\nEnter your choice: "RESET);

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                viewAllBookings();

                break;
            case 2:
                approveRejectBookings();

                break;
            case 3:
                viewAllStudents();

                break;
            case 4:
                manageRooms();

                break;
            case 5:
                viewComplaints();

                break;
            case 6:
                respondToComplaint();

                break;
            case 7:
                processCheckinRequests();

                break;
            case 8:
                generateReports();

                break;
            case 9:
                printf("\nLogging out...\n");
                system("cls");
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
        pressEnterToContinue();
    }
}

void viewAllBookings() {
    FILE *file = fopen("bookings.txt", "r");
    if (file == NULL) {
        printf("No booking records found.\n");
        return;
    }

    int booking_id, room_number;
    char student_username[MAX_USERNAME], booking_date[20], status[20];
    char student_name[MAX_NAME], student_phone[20];
    system("cls");


    printCentered(BRIGHT_RED"ALL BOOKING REQUESTS\n");
    printCentered(BRIGHT_BLUE"========================================================\n\n\n");
    printf("ID   | Username   | Room | Date       | Status   | Student Name\n");
    printf("----------------------------------------------------------\n");

    while (fscanf(file, "%d %s %d %s %s %s %s",
                  &booking_id, student_username, &room_number,
                  booking_date, status, student_name, student_phone) == 7) {
        printf(BRIGHT_YELLOW"%-4d | %-10s | %-4d | %-10s | %-8s | %s\n"RESET,
               booking_id, student_username, room_number,
               booking_date, status, student_name);
    }

    printf("========================================================\n");
    fclose(file);
}

void approveRejectBookings() {
    FILE *file, *temp;
    int booking_id, target_id, choice;
    int found = 0;
    char line[MAX_LINE];

    viewAllBookings();

    printf("\nEnter booking ID to process: ");
    if (scanf("%d", &target_id) != 1) {
        printf("Invalid booking ID!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    printCentered(BRIGHT_GREEN"1. Approve Booking\n"RESET);
    printCentered(BRIGHT_GREEN"2. Reject Booking\n\n\n"RESET);
    printf(BRIGHT_YELLOW"Enter your choice: "RESET);
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid choice!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    file = fopen("bookings.txt", "r");
    temp = fopen("temp_bookings.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error processing booking.\n");
        return;
    }

    int room_number;
    char student_username[MAX_USERNAME], booking_date[20], status[20];
    char student_name[MAX_NAME], student_phone[20];

    while (fscanf(file, "%d %s %d %s %s %s %s",
                  &booking_id, student_username, &room_number,
                  booking_date, status, student_name, student_phone) == 7) {

        if (booking_id == target_id) {
            if (choice == 1) {
                fprintf(temp, "%d %s %d %s Approved %s %s\n",
                        booking_id, student_username, room_number,
                        booking_date, student_name, student_phone);

                // Update room occupancy
                FILE *room_file = fopen("rooms.txt", "r");
                FILE *temp_room = fopen("temp_rooms.txt", "w");

                if (room_file != NULL && temp_room != NULL) {
                    int r_num, floor, capacity, occupied, available;
                    float rent;
                    char room_type[20], facilities[100];

                    while (fscanf(room_file, "%d %d %s %d %d %f %s %d",
                                  &r_num, &floor, room_type, &capacity,
                                  &occupied, &rent, facilities, &available) == 8) {
                        if (r_num == room_number) {
                            fprintf(temp_room, "%d %d %s %d %d %.2f %s %d\n",
                                    r_num, floor, room_type, capacity,
                                    occupied + 1, rent, facilities,
                                    (occupied + 1 >= capacity) ? 0 : 1);
                        } else {
                            fprintf(temp_room, "%d %d %s %d %d %.2f %s %d\n",
                                    r_num, floor, room_type, capacity,
                                    occupied, rent, facilities, available);
                        }
                    }

                    fclose(room_file);
                    fclose(temp_room);
                    remove("rooms.txt");
                    rename("temp_rooms.txt", "rooms.txt");
                }

                printf("Booking approved successfully!\n");
            } else {
                fprintf(temp, "%d %s %d %s Rejected %s %s\n",
                        booking_id, student_username, room_number,
                        booking_date, student_name, student_phone);
                printf("Booking rejected successfully!\n");
            }
            found = 1;
        } else {
            fprintf(temp, "%d %s %d %s %s %s %s\n",
                    booking_id, student_username, room_number,
                    booking_date, status, student_name, student_phone);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("bookings.txt");
        rename("temp_bookings.txt", "bookings.txt");
    } else {
        remove("temp_bookings.txt");
        printf("Booking ID not found.\n");
    }
}

void viewAllStudents() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No student records found.\n");
        return;
    }

    char username[MAX_USERNAME], password[MAX_PASSWORD];
    system("cls");

    printCentered(BRIGHT_RED"ALL REGISTERED STUDENTS\n"RESET);
    printCentered(BRIGHT_BLUE"========================================================\n"RESET);
    printf("Username\n");
    printf("----------------------------------------------------------\n");

    while (fscanf(file, "%s %s", username, password) == 2) {
        printf("%s\n", username);
    }

    printf("========================================================\n");
    fclose(file);

    // Show students with bookings
    file = fopen("bookings.txt", "r");
    if (file != NULL) {
        system("cls");
        printCentered(BRIGHT_RED"STUDENTS WITH ROOM BOOKINGS\n"RESET);
        printCentered(BRIGHT_BLUE"========================================================\n"RESET);
        printf("Username   | Room | Status   | Student Name\n");
        printf("----------------------------------------------------------\n");

        int booking_id, room_number;
        char student_username[MAX_USERNAME], booking_date[20], status[20];
        char student_name[MAX_NAME], student_phone[20];

        while (fscanf(file, "%d %s %d %s %s %s %s",
                      &booking_id, student_username, &room_number,
                      booking_date, status, student_name, student_phone) == 7) {
            printf(BRIGHT_YELLOW"%-10s | %-4d | %-8s | %s\n"RESET,
                   student_username, room_number, status, student_name);
        }
        printf("========================================================\n");
        fclose(file);
    }
}

void manageRooms() {
    int choice;
    system("cls");


    printCentered(BRIGHT_RED"ROOM MANAGEMENT\n"RESET);
    printCentered(BRIGHT_BLUE"===========================================\n\n\n"RESET);
    printCentered(BRIGHT_GREEN"1. View All Rooms Status\n"RESET);
    printCentered(BRIGHT_GREEN"2. Make Room Available/Unavailable\n"RESET);
    printCentered(BRIGHT_GREEN"3. Update Room Details\n"RESET);
    printCentered("4. Return to Dashboard\n");
    printf(BRIGHT_YELLOW"\nEnter your choice: "RESET);

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *file;
    int room_number, floor, capacity, occupied, available;
    float rent;
    char room_type[20], facilities[100];

    switch (choice) {
        case 1:
            system("cls");
            file = fopen("rooms.txt", "r");
            if (file == NULL) {
                printf("Error accessing room data.\n");
                return;
            }

            printCentered(BRIGHT_RED"ALL ROOMS STATUS\n"RESET);
            printCentered(BRIGHT_BLUE"========================================================\n\n\n"RESET);
            printf("Room | Floor | Type   | Capacity | Occupied | Rent    | Available\n");
            printf("----------------------------------------------------------------\n");

            while (fscanf(file, "%d %d %s %d %d %f %s %d",
                          &room_number, &floor, room_type, &capacity,
                          &occupied, &rent, facilities, &available) == 8) {
                printf(BRIGHT_YELLOW"%-4d | %-5d | %-6s | %-8d | %-8d | %-7.2f | %s\n"RESET,
                       room_number, floor, room_type, capacity,
                       occupied, rent, available ? "Yes" : "No");
            }
            printf("========================================================\n");
            fclose(file);
            break;

        case 2: {
            system("cls");
            int target_room, new_status;
            printf("Enter room number to change availability: ");
            if (scanf("%d", &target_room) != 1) {
                printf("Invalid room number!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            printf("Set room status (1 for Available, 0 for Unavailable): ");
            if (scanf("%d", &new_status) != 1 || (new_status != 0 && new_status != 1)) {
                printf("Invalid status! Enter 1 or 0.\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            file = fopen("rooms.txt", "r");
            FILE *temp = fopen("temp_rooms.txt", "w");

            if (file == NULL || temp == NULL) {
                printf("Error updating room status.\n");
                return;
            }

            int found = 0;
            while (fscanf(file, "%d %d %s %d %d %f %s %d",
                          &room_number, &floor, room_type, &capacity,
                          &occupied, &rent, facilities, &available) == 8) {
                if (room_number == target_room) {
                    fprintf(temp, "%d %d %s %d %d %.2f %s %d\n",
                            room_number, floor, room_type, capacity,
                            occupied, rent, facilities, new_status);
                    found = 1;
                    printf("Room %d status updated to %s\n",
                           target_room, new_status ? "Available" : "Unavailable");
                } else {
                    fprintf(temp, "%d %d %s %d %d %.2f %s %d\n",
                            room_number, floor, room_type, capacity,
                            occupied, rent, facilities, available);
                }
            }

            fclose(file);
            fclose(temp);

            if (found) {
                remove("rooms.txt");
                rename("temp_rooms.txt", "rooms.txt");
            } else {
                remove("temp_rooms.txt");
                printf("Room number not found.\n");
            }
            break;
        }

        case 3:
            system("cls");
            printf("Room details update feature will be implemented.\n");
            break;

        case 4:
            return;

        default:
            printf("Invalid choice.\n");
    }
}

void viewComplaints() {
    FILE *file = fopen("complaints.txt", "r");
    if (file == NULL) {
        printf("No complaints found.\n");
        return;
    }

    char line[500];
    system("cls");

    printf("\n========================================================\n");
    printf("                   STUDENT COMPLAINTS\n");
    printf("========================================================\n");
    printf("Username | Date | Subject | Details | Status\n");
    printf("--------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    printf("========================================================\n");
    fclose(file);
}

void respondToComplaint() {
    system("cls");
    char username[MAX_USERNAME], response[300];
    printf("Enter student username to respond to: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your response: ");
    fgets(response, sizeof(response), stdin);
    response[strcspn(response, "\n")] = '\0';

    FILE *file = fopen("complaint_responses.txt", "a");
    if (file != NULL) {
        char date[20];
        getCurrentDate(date);
        fprintf(file, "%s | %s | %s | %s\n", username, date, current_username, response);
        fclose(file);
        printf("Response sent successfully!\n");
    } else {
        printf("Error sending response.\n");
    }
}

void processCheckinRequests() {
    int choice;
    system("cls");

    printf("\n========================================================\n");
    printf("              CHECK-IN/CHECK-OUT REQUESTS\n");
    printf("========================================================\n");
    printf("Choose an option:\n");
    printf("1. View All Check-in Requests\n");
    printf("2. View All Check-out Requests\n");
    printf("3. Process Check-in Request\n");
    printf("4. Process Check-out Request\n");
    printf("5. Return to Dashboard\n");
    printf("\nEnter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *file;
    char username[MAX_USERNAME], type[20], date[20], status[20];

    switch (choice) {
        case 1:
            file = fopen("checkin_requests.txt", "r");
            if (file == NULL) {
                printf("No check-in requests found.\n");
                return;
            }
            printf("\nCheck-in Requests:\n");
            printf("Username | Type | Date | Status\n");
            printf("--------------------------------\n");
            while (fscanf(file, "%s %s %s %s", username, type, date, status) == 4) {
                printf("%s | %s | %s | %s\n", username, type, date, status);
            }
            fclose(file);
            break;

        case 2:
            file = fopen("checkout_requests.txt", "r");
            if (file == NULL) {
                printf("No check-out requests found.\n");
                return;
            }
            printf("\nCheck-out Requests:\n");
            printf("Username | Type | Date | Status\n");
            printf("--------------------------------\n");
            while (fscanf(file, "%s %s %s %s", username, type, date, status) == 4) {
                printf("%s | %s | %s | %s\n", username, type, date, status);
            }
            fclose(file);
            break;

        case 3:
        case 4: {
            char target_username[MAX_USERNAME];
            int approve;
            char *filename = (choice == 3) ? "checkin_requests.txt" : "checkout_requests.txt";
            char *temp_filename = (choice == 3) ? "temp_checkin.txt" : "temp_checkout.txt";

            printf("Enter username to process: ");
            fgets(target_username, sizeof(target_username), stdin);
            target_username[strcspn(target_username, "\n")] = '\0';

            printf("1. Approve\n2. Reject\nEnter choice: ");
            if (scanf("%d", &approve) != 1 || (approve != 1 && approve != 2)) {
                printf("Invalid choice!\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            file = fopen(filename, "r");
            FILE *temp = fopen(temp_filename, "w");

            if (file == NULL || temp == NULL) {
                printf("Error processing request.\n");
                return;
            }

            int found = 0;
            while (fscanf(file, "%s %s %s %s", username, type, date, status) == 4) {
                if (strcmp(username, target_username) == 0 && strcmp(status, "Pending") == 0) {
                    fprintf(temp, "%s %s %s %s\n", username, type, date,
                            approve == 1 ? "Approved" : "Rejected");
                    found = 1;
                } else {
                    fprintf(temp, "%s %s %s %s\n", username, type, date, status);
                }
            }

            fclose(file);
            fclose(temp);

            if (found) {
                remove(filename);
                rename(temp_filename, filename);
                printf("Request %s successfully!\n", approve == 1 ? "approved" : "rejected");
            } else {
                remove(temp_filename);
                printf("Request not found or already processed.\n");
            }
            break;
        }

        case 5:
            return;

        default:
            printf("Invalid choice.\n");
    }
}

void generateReports() {
    system("cls");
    printf("\n========================================================\n");
    printf("                   HOSTEL REPORTS\n");
    printf("========================================================\n");

    // Room Occupancy Report
    FILE *file = fopen("rooms.txt", "r");
    if (file != NULL) {
        int total_rooms = 0, occupied_rooms = 0, available_rooms = 0;
        int room_number, floor, capacity, occupied, available;
        float rent, total_revenue = 0;
        char room_type[20], facilities[100];

        printf("ROOM OCCUPANCY REPORT:\n");
        printf("----------------------\n");

        while (fscanf(file, "%d %d %s %d %d %f %s %d",
                      &room_number, &floor, room_type, &capacity,
                      &occupied, &rent, facilities, &available) == 8) {
            total_rooms++;
            if (occupied > 0) {
                occupied_rooms++;
                total_revenue += rent * occupied;
            }
            if (available == 1 && occupied < capacity) {
                available_rooms++;
            }
        }

        printf("Total Rooms: %d\n", total_rooms);
        printf("Occupied Rooms: %d\n", occupied_rooms);
        printf("Available Rooms: %d\n", available_rooms);
        printf("Monthly Revenue: %.2f BDT\n", total_revenue);
        printf("Occupancy Rate: %.1f%%\n\n",
               total_rooms > 0 ? (float)occupied_rooms/total_rooms*100 : 0);

        fclose(file);
    }

    // Booking Statistics
    file = fopen("bookings.txt", "r");
    if (file != NULL) {
        int total_bookings = 0, approved = 0, pending = 0, rejected = 0;
        int booking_id, room_number;
        char student_username[MAX_USERNAME], booking_date[20], status[20];
        char student_name[MAX_NAME], student_phone[20];

        printf("BOOKING STATISTICS:\n");
        printf("-------------------\n");

        while (fscanf(file, "%d %s %d %s %s %s %s",
                      &booking_id, student_username, &room_number,
                      booking_date, status, student_name, student_phone) == 7) {
            total_bookings++;
            if (strcmp(status, "Approved") == 0) approved++;
            else if (strcmp(status, "Pending") == 0) pending++;
            else if (strcmp(status, "Rejected") == 0) rejected++;
        }

        printf("Total Bookings: %d\n", total_bookings);
        printf("Approved: %d\n", approved);
        printf("Pending: %d\n", pending);
        printf("Rejected: %d\n", rejected);

        fclose(file);
    }

    printf("\n========================================================\n");
}


void handleOwner() {
    int action;
    system("cls");

    printf("                                OWNER PORTAL\n");
    printf("Welcome to the owner control center!\n");
    printf("1. Login to owner account\n");
    printf("2. Return to main menu\n");
    printf("\nSelect your option: ");

    if (scanf("%d", &action) != 1) {
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (action) {
        case 1:
            if (ownerLogin()) {
                system("cls");
                printf("                             OWNER CONTROL PANEL\n");
                printf("Full system access granted! Welcome to your home \n");
                pressEnterToContinue();
                ownerDashboard();
            }
            break;
        case 2:
            system("cls");
            printf("\nReturning to main menu...\n\n");
            break;
        default:
            printf("\nPlease enter a valid choice (1 or 2).\n\n");
    }
}

int ownerLogin() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    system("cls");

    printf("                                OWNER LOGIN\n");
    printf("Please enter your login information.\n\n");

    printf("Username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("\nVerifying your information...\n");

    if (strcmp(username, OWNER_USERNAME) == 0 && strcmp(password, OWNER_PASSWORD) == 0) {
        strcpy(current_username, username);
        printf("Login successful!\n");
        pressEnterToContinue();
        return 1;
    } else {
        printf("\nLogin failed. Username or password is incorrect.\n");
        printf("Please double-check your information and try again.\n\n");
        pressEnterToContinue();
        return 0;
    }
}

void ownerDashboard() {
    int choice;

    while (1) {
        system("cls");
        printf("\n========================================================\n");
        printf("              OWNER DASHBOARD\n");
        printf("========================================================\n");
        printf("Welcome back, %s!\n\n", current_username);
        printf("Choose an option:\n");
        printf("1. View All Managers\n");
        printf("2. Add New Manager\n");
        printf("3. Remove Manager\n");
        printf("4. Set Hostel Rules & Policies\n");
        printf("5. View Hostel Rules\n");
        printf("6. View All Hostel Data\n");
        printf("7. View All Complaints\n");
        printf("8. Generate Comprehensive Reports\n");
        printf("9. System Settings\n");
        printf("10. Logout\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                viewAllManagers();
                break;
            case 2:
                addNewManager();
                break;
            case 3:
                removeManager();
                break;
            case 4:
                setHostelRules();
                break;
            case 5:
                viewHostelRules();
                break;
            case 6:
                viewAllHostelData();
                break;
            case 7:
                viewComplaintsAsOwner();
                break;
            case 8:
                generateOwnerReports();
                break;
            case 9:
                manageSystemSettings();
                break;
            case 10:
                printf("\nLogging out...\n");
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
        pressEnterToContinue();
    }
}

void viewAllManagers() {
    FILE *file = fopen("managers.txt", "r");
    system("cls");

    printf("\n========================================================\n");
    printf("                   ALL MANAGERS\n");
    printf("========================================================\n");

    if (file == NULL) {
        printf("No manager records found.\n");
        return;
    }

    char username[MAX_USERNAME], password[MAX_PASSWORD], status[20];
    printf("Username     | Status\n");
    printf("------------------------\n");

    while (fscanf(file, "%s %s %s", username, password, status) == 3) {
        printf("%-12s | %s\n", username, status);
    }

    printf("========================================================\n");
    fclose(file);
}


void addNewManager() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    system("cls");

    printf("\n========================================================\n");
    printf("              ADD NEW MANAGER\n");
    printf("========================================================\n");

    printf("Enter new manager username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    if (strlen(username) == 0) {
        printf("Username cannot be empty.\n");
        return;
    }

    printf("Enter password for manager: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strlen(password) == 0) {
        printf("Password cannot be empty.\n");
        return;
    }

    // Check if username already exists
    FILE *file = fopen("managers.txt", "r");
    if (file != NULL) {
        char existing_username[MAX_USERNAME], existing_password[MAX_PASSWORD], status[20];
        while (fscanf(file, "%s %s %s", existing_username, existing_password, status) == 3) {
            if (strcmp(username, existing_username) == 0) {
                printf("Username already exists!\n");
                fclose(file);
                return;
            }
        }
        fclose(file);
    }

    // Add new manager
    file = fopen("managers.txt", "a");
    if (file == NULL) {
        printf("Error adding manager.\n");
        return;
    }

    fprintf(file, "%s %s Active\n", username, password);
    fclose(file);

    printf("Manager added successfully!\n");
    printf("Username: %s\n", username);
    printf("Status: Active\n");
}

void removeManager() {
    system("cls");
    printf("\n========================================================\n");
    printf("              REMOVE MANAGER\n");
    printf("========================================================\n");

    viewAllManagers();

    printf("\nEnter username of manager to remove: ");
    char target_username[MAX_USERNAME];
    fgets(target_username, sizeof(target_username), stdin);
    target_username[strcspn(target_username, "\n")] = '\0';

    FILE *file = fopen("managers.txt", "r");
    FILE *temp = fopen("temp_managers.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error removing manager.\n");
        return;
    }

    char username[MAX_USERNAME], password[MAX_PASSWORD], status[20];
    int found = 0;

    while (fscanf(file, "%s %s %s", username, password, status) == 3) {
        if (strcmp(username, target_username) == 0) {
            found = 1;
            printf("Manager '%s' removed successfully!\n", target_username);
        } else {
            fprintf(temp, "%s %s %s\n", username, password, status);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("managers.txt");
        rename("temp_managers.txt", "managers.txt");
    } else {
        remove("temp_managers.txt");
        printf("Manager not found.\n");
    }
}

void setHostelRules() {
    char rule[500];
    system("cls");

    printf("\n========================================================\n");
    printf("              SET HOSTEL RULES & POLICIES\n");
    printf("========================================================\n");

    printf("Enter new hostel rule/policy: ");
    fgets(rule, sizeof(rule), stdin);
    rule[strcspn(rule, "\n")] = '\0';

    if (strlen(rule) == 0) {
        printf("Rule cannot be empty.\n");
        return;
    }

    FILE *file = fopen("hostel_rules.txt", "a");
    if (file == NULL) {
        printf("Error saving rule.\n");
        return;
    }

    char date[20];
    getCurrentDate(date);

    fprintf(file, "%s | %s | %s\n", date, current_username, rule);
    fclose(file);

    printf("Rule added successfully!\n");
    printf("Date: %s\n", date);
    printf("Added by: %s\n", current_username);
    printf("Rule: %s\n", rule);
}

void viewHostelRules() {
    FILE *file = fopen("hostel_rules.txt", "r");
    system("cls");

    printf("\n========================================================\n");
    printf("              HOSTEL RULES & POLICIES\n");
    printf("========================================================\n");

    if (file == NULL) {
        printf("No rules found.\n");
        return;
    }

    char line[600];
    int rule_number = 1;

    while (fgets(line, sizeof(line), file)) {
        printf("%d. %s", rule_number++, line);
    }

    printf("========================================================\n");
    fclose(file);
}

void viewAllHostelData() {
    system("cls");
    printf("\n========================================================\n");
    printf("              COMPLETE HOSTEL DATA OVERVIEW\n");
    printf("========================================================\n");

    // Students Data
    FILE *file = fopen("students.txt", "r");
    int student_count = 0;
    if (file != NULL) {
        char username[MAX_USERNAME], password[MAX_PASSWORD];
        while (fscanf(file, "%s %s", username, password) == 2) {
            student_count++;
        }
        fclose(file);
    }
    printf("Total Students: %d\n", student_count);

    // Managers Data
    file = fopen("managers.txt", "r");
    int manager_count = 0, active_managers = 0;
    if (file != NULL) {
        char username[MAX_USERNAME], password[MAX_PASSWORD], status[20];
        while (fscanf(file, "%s %s %s", username, password, status) == 3) {
            manager_count++;
            if (strcmp(status, "Active") == 0) active_managers++;
        }
        fclose(file);
    }
    printf("Total Managers: %d (Active: %d)\n", manager_count, active_managers);

    // Rooms Data
    file = fopen("rooms.txt", "r");
    int total_rooms = 0, occupied_rooms = 0, available_rooms = 0;
    float total_revenue = 0;
    if (file != NULL) {
        int room_number, floor, capacity, occupied, available;
        float rent;
        char room_type[20], facilities[100];

        while (fscanf(file, "%d %d %s %d %d %f %s %d",
                      &room_number, &floor, room_type, &capacity,
                      &occupied, &rent, facilities, &available) == 8) {
            total_rooms++;
            if (occupied > 0) {
                occupied_rooms++;
                total_revenue += rent * occupied;
            }
            if (available == 1 && occupied < capacity) {
                available_rooms++;
            }
        }
        fclose(file);
    }
    printf("Total Rooms: %d\n", total_rooms);
    printf("Occupied Rooms: %d\n", occupied_rooms);
    printf("Available Rooms: %d\n", available_rooms);
    printf("Monthly Revenue: %.2f BDT\n", total_revenue);

    // Bookings Data
    file = fopen("bookings.txt", "r");
    int total_bookings = 0, approved = 0, pending = 0, rejected = 0;
    if (file != NULL) {
        int booking_id, room_number;
        char student_username[MAX_USERNAME], booking_date[20], status[20];
        char student_name[MAX_NAME], student_phone[20];

        while (fscanf(file, "%d %s %d %s %s %s %s",
                      &booking_id, student_username, &room_number,
                      booking_date, status, student_name, student_phone) == 7) {
            total_bookings++;
            if (strcmp(status, "Approved") == 0) approved++;
            else if (strcmp(status, "Pending") == 0) pending++;
            else if (strcmp(status, "Rejected") == 0) rejected++;
        }
        fclose(file);
    }
    printf("Total Bookings: %d (Approved: %d, Pending: %d, Rejected: %d)\n",
           total_bookings, approved, pending, rejected);

    // Complaints Data
    file = fopen("complaints.txt", "r");
    int complaint_count = 0;
    if (file != NULL) {
        char line[500];
        while (fgets(line, sizeof(line), file)) {
            complaint_count++;
        }
        fclose(file);
    }
    printf("Total Complaints: %d\n", complaint_count);

    printf("========================================================\n");
}

void viewComplaintsAsOwner() {
    FILE *file = fopen("complaints.txt", "r");
    system("cls");

    printf("\n========================================================\n");
    printf("              ALL STUDENT COMPLAINTS\n");
    printf("========================================================\n");

    if (file == NULL) {
        printf("No complaints found.\n");
        return;
    }

    char line[500];
    int complaint_number = 1;

    printf("Complaint Details:\n");
    printf("------------------\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%d. %s", complaint_number++, line);
    }

    printf("========================================================\n");
    fclose(file);

    // Show responses if any
    file = fopen("complaint_responses.txt", "r");
    if (file != NULL) {
        printf("\n========================================================\n");
        printf("              COMPLAINT RESPONSES\n");
        printf("========================================================\n");

        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        printf("========================================================\n");
        fclose(file);
    }
}

void generateOwnerReports() {
    system("cls");
    printf("\n========================================================\n");
    printf("          COMPREHENSIVE HOSTEL MANAGEMENT REPORT\n");
    printf("========================================================\n");

    char date[20];
    getCurrentDate(date);
    printf("Report Generated on: %s\n", date);
    printf("Generated by: %s (Owner)\n\n", current_username);

    // Financial Report
    printf("FINANCIAL SUMMARY:\n");
    printf("------------------\n");
    FILE *file = fopen("rooms.txt", "r");
    float total_revenue = 0, potential_revenue = 0;
    int occupied_students = 0, total_capacity = 0;

    if (file != NULL) {
        int room_number, floor, capacity, occupied, available;
        float rent;
        char room_type[20], facilities[100];

        while (fscanf(file, "%d %d %s %d %d %f %s %d",
                      &room_number, &floor, room_type, &capacity,
                      &occupied, &rent, facilities, &available) == 8) {
            total_revenue += rent * occupied;
            potential_revenue += rent * capacity;
            occupied_students += occupied;
            total_capacity += capacity;
        }
        fclose(file);
    }

    printf("Current Monthly Revenue: %.2f BDT\n", total_revenue);
    printf("Potential Monthly Revenue: %.2f BDT\n", potential_revenue);
    printf("Revenue Efficiency: %.1f%%\n",
           potential_revenue > 0 ? (total_revenue/potential_revenue)*100 : 0);
    printf("Student Occupancy: %d/%d (%.1f%%)\n\n",
           occupied_students, total_capacity,
           total_capacity > 0 ? (float)occupied_students/total_capacity*100 : 0);

    // Operational Statistics
    printf("OPERATIONAL STATISTICS:\n");
    printf("-----------------------\n");

    // Manager Performance
    file = fopen("managers.txt", "r");
    int active_managers = 0, total_managers = 0;
    if (file != NULL) {
        char username[MAX_USERNAME], password[MAX_PASSWORD], status[20];
        while (fscanf(file, "%s %s %s", username, password, status) == 3) {
            total_managers++;
            if (strcmp(status, "Active") == 0) active_managers++;
        }
        fclose(file);
    }
    printf("Manager Status: %d/%d Active\n", active_managers, total_managers);

    // Booking Performance
    file = fopen("bookings.txt", "r");
    int total_bookings = 0, approved_bookings = 0, pending_bookings = 0;
    if (file != NULL) {
        int booking_id, room_number;
        char student_username[MAX_USERNAME], booking_date[20], status[20];
        char student_name[MAX_NAME], student_phone[20];

        while (fscanf(file, "%d %s %d %s %s %s %s",
                      &booking_id, student_username, &room_number,
                      booking_date, status, student_name, student_phone) == 7) {
            total_bookings++;
            if (strcmp(status, "Approved") == 0) approved_bookings++;
            else if (strcmp(status, "Pending") == 0) pending_bookings++;
        }
        fclose(file);
    }
    printf("Booking Approval Rate: %.1f%% (%d/%d)\n",
           total_bookings > 0 ? (float)approved_bookings/total_bookings*100 : 0,
           approved_bookings, total_bookings);
    printf("Pending Bookings: %d\n", pending_bookings);

    // Service Quality
    file = fopen("complaints.txt", "r");
    int total_complaints = 0;
    if (file != NULL) {
        char line[500];
        while (fgets(line, sizeof(line), file)) {
            total_complaints++;
        }
        fclose(file);
    }
    printf("Total Complaints: %d\n", total_complaints);

    printf("\n========================================================\n");
    printf("              RECOMMENDATIONS\n");
    printf("========================================================\n");

    if (pending_bookings > 5) {
        printf("- High pending bookings detected. Consider adding more managers.\n");
    }
    if ((float)occupied_students/total_capacity < 0.7) {
        printf("- Low occupancy rate. Consider marketing campaigns.\n");
    }
    if (total_complaints > 10) {
        printf("- High complaint volume. Review service quality.\n");
    }
    if (active_managers < 2) {
        printf("- Consider hiring additional active managers.\n");
    }

    printf("\nReport End\n");
    printf("========================================================\n");
}

void manageSystemSettings() {
    int choice;
    system("cls");

    printf("\n========================================================\n");
    printf("              SYSTEM SETTINGS\n");
    printf("========================================================\n");
    printf("Choose an option:\n");
    printf("1. Reset All Bookings\n");
    printf("2. Reset All Complaints\n");
    printf("3. Initialize Default Rooms\n");
    printf("4. Backup System Data\n");
    printf("5. System Status\n");
    printf("6. Return to Dashboard\n");
    printf("\nEnter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (choice) {
        case 1:
            printf("Are you sure you want to reset all bookings? (y/n): ");
            char confirm;
            scanf("%c", &confirm);
            clearInputBuffer();
            if (confirm == 'y' || confirm == 'Y') {
                remove("bookings.txt");
                printf("All bookings have been reset.\n");
            }
            break;

        case 2:
            printf("Are you sure you want to reset all complaints? (y/n): ");
            scanf("%c", &confirm);
            clearInputBuffer();
            if (confirm == 'y' || confirm == 'Y') {
                remove("complaints.txt");
                remove("complaint_responses.txt");
                printf("All complaints have been reset.\n");
            }
            break;

        case 3:
            remove("rooms.txt");
            // Re-initialize default rooms
            FILE *file = fopen("rooms.txt", "w");
            if (file != NULL) {
                fprintf(file, "101 1 Single 1 0 8000.00 AC,WiFi,Study_Table 1\n");
                fprintf(file, "102 1 Double 2 0 6000.00 AC,WiFi,Study_Table 1\n");
                fprintf(file, "103 1 Triple 3 0 4500.00 WiFi,Study_Table 1\n");
                fprintf(file, "201 2 Single 1 0 8500.00 AC,WiFi,Study_Table,Balcony 1\n");
                fprintf(file, "202 2 Double 2 0 6500.00 AC,WiFi,Study_Table,Balcony 1\n");
                fprintf(file, "203 2 Triple 3 0 5000.00 WiFi,Study_Table,Balcony 1\n");
                fprintf(file, "301 3 Single 1 0 9000.00 AC,WiFi,Study_Table,Balcony,Nature_view 1\n");
                fprintf(file, "302 3 Double 2 0 7000.00 AC,WiFi,Study_Table,Balcony,Nature_View 1\n");
                fclose(file);
                printf("Default rooms have been initialized.\n");
            }
            break;

        case 4:
            printf("System backup initiated...\n");
            printf("Note: In a real system, this would create backups of all data files.\n");
            printf("Backup completed successfully!\n");
            break;

        case 5:
            printf("SYSTEM STATUS:\n");
            printf("--------------\n");
            printf("Owner Access: Active\n");
            printf("System Files: Operational\n");
            printf("Database Status: Connected\n");
            printf("Last Backup: Not Available\n");
            printf("System Uptime: Active\n");
            break;

        case 6:
            return;

        default:
            printf("Invalid choice.\n");
    }
}




int login(char *filename, char *role) {
    FILE *file;
    char password[MAX_PASSWORD];
    char fileUsername[MAX_USERNAME], filePassword[MAX_PASSWORD];
    char line[MAX_LINE];
    int found = 0;
    system("cls");

    printf(RED"                                                                    %s LOGIN\n\n\n"RESET, role);
    printCentered("Please enter your login information.\n\n\n\n\n\n\n");

    printf("Username: ");
    fgets(current_username, MAX_USERNAME, stdin);
    current_username[strcspn(current_username, "\n")] = '\0'; // Remove newline

    printf("Password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline

    printf("\nVerifying your information...\n");

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nNo %s accounts found in the system.\n", role);
        printf("Please create an account first by selecting the signup option.\n\n");
        return 0;
    }

    while (fgets(line, MAX_LINE, file)) {
        if (sscanf(line, "%s %s", fileUsername, filePassword) == 2) {
            if (strcmp(current_username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
                found = 1;
                break;
            }
        }
    }

    fclose(file);

    if (!found) {
        printf("\nLogin failed. Username or password is incorrect.\n");
        printf("Please double-check your information and try again.\n");
        printf("Make sure there are no extra spaces in your input.\n\n");
        return 0;
    }

    printf("Login successful!\n");
    return 1;
}

int signup(char *filename, char *role) {
    FILE *file;
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    char fileUsername[MAX_USERNAME], filePassword[MAX_PASSWORD];
    char line[MAX_LINE];
    int userExists = 0;

    printf("                              %s REGISTRATION\n", role);
    printf("Let's create your new account.\n");
    printf("Please provide the following information:\n\n");

    printf("Choose a username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = '\0';

    if (strlen(username) == 0) {
        printf("\nUsername cannot be empty.\n");
        printf("Please enter a valid username for your account.\n\n");
        return 0;
    }

    printf("Create a password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strlen(password) == 0) {
        printf("\nPassword cannot be empty.\n");
        printf("Please create a secure password for your account.\n\n");
        return 0;
    }

    printf("\nChecking username availability...\n");

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

    file = fopen(filename, "a");
    if (file == NULL) {
        printf("\nSystem error: Unable to create account at this time.\n");
        printf("Please try again later or contact system administrator.\n\n");
        return 0;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("Account created successfully!\n");
    return 1;
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
void printCentered(const char *text) {
    int len = strlen(text);
    int spaces = (TERMINAL_WIDTH - len) / 2;

    if (spaces < 0) spaces = 0; // Avoid negative spaces

    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}
