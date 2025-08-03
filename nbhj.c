#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_LINE 150
#define MAX_NAME 50

// Global variable to store current logged-in user
char current_username[MAX_USERNAME];

// Room structure
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

// Booking structure
typedef struct {
    int booking_id;
    char student_username[MAX_USERNAME];
    int room_number;
    char booking_date[20];
    char status[20];
    char student_name[MAX_NAME];
    char student_phone[20];
} Booking;

// Function prototypes
void showWelcome();
void showMainMenu();
void handleStudent();
void handleManager();
void handleOwner();
int login(char *filename, char *role);
int signup(char *filename, char *role);
void clearInputBuffer();
void pressEnterToContinue();

// Student dashboard functions
void studentDashboard();
void viewAvailableRooms();
void bookRoomMenu();
void bookRoom();
void viewMyBookings();
void checkRoomDetails();
void requestCheckInOut();
void viewMyRoomDetails();
void submitComplaint();

// Room management functions
void initializeRooms();
int isRoomAvailable(int room_number);
void saveBooking(Booking booking);
int generateBookingId();
void getCurrentDate(char *date);

int main() {
    int choice;

    // Initialize rooms file if it doesn't exist
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
    printf("                        SMART HOSTEL MANAGEMENT SYSTEM\n");
    printf("                           Welcome to digital home!\n");
    printf("\n\nThis system will make you feel you are in future\n");
    printf("Let's get you connected to us.\n\n");
    pressEnterToContinue();
}

void showMainMenu() {
    printf("                                  SELECT YOUR ROLE\n");
    printf("1. Student Portal\n");
    printf("2. Manager Portal\n");
    printf("3. Owner Portal\n");
    printf("4. Exit System\n");
    printf("                    =============================================\n");
}

void handleStudent() {
    int action;

    printf("                               STUDENT PORTAL\n");
    printf("Welcome to the student section!\n");
    printf("Here you can access your hostel account and services.\n\n");
    printf("1. Login to existing account\n");
    printf("2. Create new student account\n");
    printf("3. Return to main menu\n");
    printf("\nWhat would you like to do? ");

    if (scanf("%d", &action) != 1) {
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (action) {
        case 1:
            if (login("students.txt", "Student")) {
                printf("                             STUDENT DASHBOARD\n");
                printf("Welcome back! Login successful.\n");
                studentDashboard();
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

void studentDashboard() {
    int choice;

    while (1) {
        printf("\n========================================================\n");
        printf("              STUDENT DASHBOARD\n");
        printf("========================================================\n");
        printf("Welcome back, %s!\n\n", current_username);
        printf("Choose an option:\n");
        printf("1. View Available Rooms\n");
        printf("2. Book a Room\n");
        printf("3. Request Check-in / Check-out\n");
        printf("4. View My Room Details\n");
        printf("5. Submit a Complaint\n");
        printf("6. Logout\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                viewAvailableRooms();
                break;
            case 2:
                bookRoomMenu();
                break;
            case 3:
                requestCheckInOut();
                break;
            case 4:
                viewMyRoomDetails();
                break;
            case 5:
                submitComplaint();
                break;
            case 6:
                printf("\nLogging out...\n");
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
        printf("\n========================================================\n");
        printf("              ROOM BOOKING MENU\n");
        printf("========================================================\n");
        printf("Choose an option:\n");
        printf("1. Book a Room\n");
        printf("2. View My Bookings\n");
        printf("3. Check Room Details\n");
        printf("4. Return to Dashboard\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                viewMyBookings();
                break;
            case 3:
                checkRoomDetails();
                break;
            case 4:
                printf("\nReturning to dashboard...\n");
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

    // Initialize sample rooms
    // Format: room_number floor room_type capacity occupied rent facilities available
    fprintf(file, "101 1 Single 1 0 8000.00 AC,WiFi,Study_Table 1\n");
    fprintf(file, "102 1 Double 2 0 6000.00 AC,WiFi,Study_Table 1\n");
    fprintf(file, "103 1 Triple 3 0 4500.00 WiFi,Study_Table 1\n");
    fprintf(file, "201 2 Single 1 0 8500.00 AC,WiFi,Study_Table,Balcony 1\n");
    fprintf(file, "202 2 Double 2 0 6500.00 AC,WiFi,Study_Table,Balcony 1\n");
    fprintf(file, "203 2 Triple 3 0 5000.00 WiFi,Study_Table,Balcony 1\n");
    fprintf(file, "301 3 Single 1 0 9000.00 AC,WiFi,Study_Table,Balcony,City_View 1\n");
    fprintf(file, "302 3 Double 2 0 7000.00 AC,WiFi,Study_Table,Balcony,City_View 1\n");

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

    printf("\n========================================================\n");
    printf("                   AVAILABLE ROOMS\n");
    printf("========================================================\n");
    printf("Room No. | Floor | Type   | Capacity | Rent     | Facilities\n");
    printf("--------------------------------------------------------\n");

    while (fscanf(file, "%d %d %s %d %d %f %s %d",
                  &room.room_number, &room.floor, room.room_type,
                  &room.capacity, &room.occupied, &room.rent,
                  room.facilities, &room.available) == 8) {

        if (room.available == 1 && room.occupied < room.capacity) {
            printf("%-8d | %-5d | %-6s | %-8d | %-8.2f | %s\n",
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

    printf("\n========================================================\n");
    printf("                    ROOM BOOKING\n");
    printf("========================================================\n");

    viewAvailableRooms();

    printf("\nEnter the room number you want to book: ");
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

    // Get student details
    printf("Enter your full name: ");
    fgets(booking.student_name, sizeof(booking.student_name), stdin);
    booking.student_name[strcspn(booking.student_name, "\n")] = '\0';

    printf("Enter your phone number: ");
    fgets(booking.student_phone, sizeof(booking.student_phone), stdin);
    booking.student_phone[strcspn(booking.student_phone, "\n")] = '\0';

    // Fill booking details
    booking.booking_id = generateBookingId();
    booking.room_number = room_number;
    strcpy(booking.student_username, current_username);
    getCurrentDate(booking.booking_date);
    strcpy(booking.status, "Pending");

    saveBooking(booking);

    printf("\n========================================================\n");
    printf("          BOOKING SUBMITTED SUCCESSFULLY!\n");
    printf("========================================================\n");
    printf("Booking ID: %d\n", booking.booking_id);
    printf("Room Number: %d\n", booking.room_number);
    printf("Student: %s\n", booking.student_name);
    printf("Phone: %s\n", booking.student_phone);
    printf("Booking Date: %s\n", booking.booking_date);
    printf("Status: %s\n", booking.status);
    printf("\nYour booking request has been sent to the manager for approval.\n");
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

    printf("\n========================================================\n");
    printf("                     MY BOOKINGS\n");
    printf("========================================================\n");
    printf("Booking ID | Room No. | Date       | Status   | Student Name\n");
    printf("--------------------------------------------------------\n");

    while (fscanf(file, "%d %s %d %s %s %s %s",
                  &booking.booking_id, booking.student_username,
                  &booking.room_number, booking.booking_date,
                  booking.status, booking.student_name,
                  booking.student_phone) == 7) {

        if (strcmp(booking.student_username, current_username) == 0) {
            printf("%-10d | %-8d | %-10s | %-8s | %s\n",
                   booking.booking_id, booking.room_number,
                   booking.booking_date, booking.status, booking.student_name);
            found = 1;
        }
    }

    if (!found) {
        printf("No bookings found for your account.\n");
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

    printf("Enter room number to check details: ");
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
            printf("\n========================================================\n");
            printf("                   ROOM DETAILS\n");
            printf("========================================================\n");
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

    printf("\n========================================================\n");
    printf("              CHECK-IN / CHECK-OUT REQUEST\n");
    printf("========================================================\n");
    printf("Choose an option:\n");
    printf("1. Request Check-in\n");
    printf("2. Request Check-out\n");
    printf("3. View Check-in/Check-out Status\n");
    printf("4. Return to Dashboard\n");
    printf("\nEnter your choice: ");

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
            printf("\n========================================================\n");
            printf("              YOUR REQUEST STATUS\n");
            printf("========================================================\n");

            // Check check-in requests
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

            // Check check-out requests
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

    // Find approved booking for current user
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
        printf("\n========================================================\n");
        printf("                   NO ROOM ASSIGNED\n");
        printf("========================================================\n");
        printf("You don't have any approved room booking yet.\n");
        printf("Please book a room and wait for manager approval.\n");
        return;
    }

    // Get room details
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
            printf("\n========================================================\n");
            printf("                   MY ROOM DETAILS\n");
            printf("========================================================\n");
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

    printf("\n========================================================\n");
    printf("              SUBMIT A COMPLAINT\n");
    printf("========================================================\n");

    printf("Enter complaint subject: ");
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

    printf("\n========================================================\n");
    printf("          COMPLAINT SUBMITTED SUCCESSFULLY!\n");
    printf("========================================================\n");
    printf("Subject: %s\n", subject);
    printf("Date: %s\n", date);
    printf("Status: Pending\n");
    printf("\nYour complaint has been forwarded to the management.\n");
    printf("You will receive a response within 24-48 hours.\n");
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
    // Simple date format - you can enhance this
    strcpy(date, "02/08/2025");
}

void handleManager() {
    int action;

    printf("                               MANAGER PORTAL\n");
    printf("Welcome to the management section!\n");
    printf("Your administrative access awaits.\n\n");
    printf("1. Login to manager account\n");
    printf("2. Register as new manager\n");
    printf("3. Return to main menu\n");
    printf("\nPlease choose an option: ");

    if (scanf("%d", &action) != 1) {
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (action) {
        case 1:
            if (login("managers.txt", "Manager")) {
                printf("                             MANAGER DASHBOARD\n");
                printf("Welcome to your management console!\n");
                printf("You have access to:\n");
                printf("- Approve/Reject Booking Requests\n");
                printf("- Assign Rooms to Students\n");
                printf("- View All Students\n");
                printf("- Manage Room Availability\n");
                printf("- Respond to Complaints\n");
                pressEnterToContinue();
            }
            break;
        case 2:
            if (signup("managers.txt", "Manager")) {
                printf("\nYour manager account is now active.\n");
                printf("You can login and start managing hostel operations.\n");
                printf("Welcome to the management team of new gen smart hostel!\n");
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

    printf("                                OWNER PORTAL\n");
    printf("Welcome to the owner control center!\n");
    printf("1. Login to owner account\n");
    printf("2. Register as new owner\n");
    printf("3. Return to main menu\n");
    printf("\nSelect your option: ");

    if (scanf("%d", &action) != 1) {
        printf("Invalid input! Please enter a number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    switch (action) {
        case 1:
            if (login("owners.txt", "Owner")) {
                printf("                             OWNER CONTROL PANEL\n");
                printf("Full system access granted!\n");
                printf("Your owner portal include:\n");
                printf("- View all hostel management\n");
                printf("- Add/Remove Managers\n");
                printf("- Set Hostel Rules & Policies\n");
                printf("- Control over all features\n");
                printf("- Generate Hostel Reports\n");
                pressEnterToContinue();
            }
            break;
        case 2:
            if (signup("owners.txt", "Owner")) {
                printf("\nCongratulations! Owner account successfully established.\n");
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
    char password[MAX_PASSWORD];
    char fileUsername[MAX_USERNAME], filePassword[MAX_PASSWORD];
    char line[MAX_LINE];
    int found = 0;

    printf("                                %s LOGIN\n", role);
    printf("Please enter your login information.\n\n");

    // Get username and password from user
    printf("Username: ");
    fgets(current_username, MAX_USERNAME, stdin);
    current_username[strcspn(current_username, "\n")] = '\0'; // Remove newline

    printf("Password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline

    printf("\nVerifying your information...\n");

    // Read file to check credentials
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("\nNo %s accounts found in the system.\n", role);
        printf("Please create an account first by selecting the signup option.\n\n");
        return 0;
    }

    while (fgets(line, MAX_LINE, file)) {
        // Parse username and password from file (format: username password)
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
    return 1; // Login successful
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

    // Check if username is empty
    if (strlen(username) == 0) {
        printf("\nUsername cannot be empty.\n");
        printf("Please enter a valid username for your account.\n\n");
        return 0;
    }

    printf("Create a password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = '\0';

    // Check if password is empty
    if (strlen(password) == 0) {
        printf("\nPassword cannot be empty.\n");
        printf("Please create a secure password for your account.\n\n");
        return 0;
    }

    printf("\nChecking username availability...\n");

    // Check if username already exists
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

    // Create new account
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
