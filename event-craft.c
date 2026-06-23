#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define ADMIN_PASS "admin123"   // change this to whatever you want

// ================= GLOBAL ARRAYS (NO STRUCTURES) =================

// ---- Users ----
char userName[MAX][50];
char userOrg[MAX][50];
char userDesignation[MAX][50];
char userCnic[MAX][20];
char userPhone[MAX][20];
char userEmail[MAX][50];
char userPassword[MAX][30];
int  userVerified[MAX];
int  userCount = 0;

// ---- Events ----
int   eventId[MAX];
char  eventName[MAX][50];
char  eventType[MAX][30];
char  eventVenue[MAX][50];
char  eventDate[MAX][20];
float eventBudget[MAX];
int   eventGuests[MAX];
int   eventCount = 0;

// ---- Complaints ----
char complaintEmail[MAX][50];
char complaintText[MAX][200];
int  complaintResolved[MAX];
int  complaintCount = 0;

// ================= UTIL =================

void clearScreen() {
    printf("\n----------------------------------------\n");
}

// Clears leftover characters (like the newline) from the input buffer
void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Safely reads a full line (allows spaces) into a string of given size
void readLine(char buffer[], int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

// Safely reads an integer, re-prompting on bad input
int readInt() {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Invalid input, please enter a number: ");
        flushInput();
    }
    flushInput();
    return value;
}

// Safely reads a float, re-prompting on bad input
float readFloat() {
    float value;
    while (scanf("%f", &value) != 1) {
        printf("Invalid input, please enter a number: ");
        flushInput();
    }
    flushInput();
    return value;
}

// ================= FACILITIES =================

void viewFacilities() {
    printf("\n=== EVENT FACILITIES ===\n");
    printf("1. Birthday Event\n");
    printf("2. Wedding Event\n");
    printf("3. Corporate Event\n");
    printf("4. Budget Management\n");
}

// ================= SIGNUP =================

int emailExists(char email[]) {
    int i;
	for (i = 0; i < userCount; i++) {
        if (strcmp(userEmail[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

void signup() {
    if (userCount >= MAX) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    printf("\n=== SIGNUP ===\n");

    int i = userCount; // index for the new user

    printf("Name: ");
    readLine(userName[i], sizeof(userName[i]));

    printf("Organization: ");
    readLine(userOrg[i], sizeof(userOrg[i]));

    printf("Designation: ");
    readLine(userDesignation[i], sizeof(userDesignation[i]));

    printf("CNIC: ");
    readLine(userCnic[i], sizeof(userCnic[i]));

    printf("Phone: ");
    readLine(userPhone[i], sizeof(userPhone[i]));

    printf("Email: ");
    readLine(userEmail[i], sizeof(userEmail[i]));

    if (emailExists(userEmail[i])) {
        printf("An account with this email already exists. Signup cancelled.\n");
        return;
    }

    printf("Password: ");
    readLine(userPassword[i], sizeof(userPassword[i]));

    userVerified[i] = 0;

    userCount++;

    printf("Signup Successful! Wait for admin verification.\n");
}

// ================= LOGIN =================

int login(char email[], char pass[]) {
    int i;
	for (i = 0; i < userCount; i++) {
        if (strcmp(userEmail[i], email) == 0 &&
            strcmp(userPassword[i], pass) == 0) {
            if (userVerified[i] == 1)
                return i;
            else {
                printf("User not verified by admin yet!\n");
                return -2;
            }
        }
    }
    return -1;
}

// ================= EVENT FUNCTIONS =================

void addEvent() {
    if (eventCount >= MAX) {
        printf("Event limit reached. Cannot add more events.\n");
        return;
    }

    printf("\n=== ADD EVENT ===\n");

    int i = eventCount; // index for the new event
    eventId[i] = eventCount + 1;

    printf("Name: ");
    readLine(eventName[i], sizeof(eventName[i]));

    printf("Type: ");
    readLine(eventType[i], sizeof(eventType[i]));

    printf("Venue: ");
    readLine(eventVenue[i], sizeof(eventVenue[i]));

    printf("Date: ");
    readLine(eventDate[i], sizeof(eventDate[i]));

    printf("Budget: ");
    eventBudget[i] = readFloat();

    printf("Guests: ");
    eventGuests[i] = readInt();

    eventCount++;

    printf("Event Added!\n");
}

void viewEvents() {
    printf("\n=== ALL EVENTS ===\n");

    if (eventCount == 0) {
        printf("No events found.\n");
        return;
    }

    int i;
	for (i = 0; i < eventCount; i++) {
        printf("\nID: %d\nName: %s\nType: %s\nVenue: %s\nDate: %s\nBudget: %.2f\nGuests: %d\n",
               eventId[i], eventName[i], eventType[i],
               eventVenue[i], eventDate[i],
               eventBudget[i], eventGuests[i]);
    }
}

void searchEvent() {
    char name[50];
    printf("Enter event name: ");
    readLine(name, sizeof(name));

    int i;
	for (i = 0; i < eventCount; i++) {
        if (strcmp(eventName[i], name) == 0) {
            printf("Event Found!\n");
            printf("Venue: %s | Budget: %.2f\n", eventVenue[i], eventBudget[i]);
            return;
        }
    }
    printf("Not Found!\n");
}

void updateEvent() {
    printf("Enter event ID: ");
    int id = readInt();

    int i;
	for (i = 0; i < eventCount; i++) {
        if (eventId[i] == id) {
            printf("New Budget: ");
            eventBudget[i] = readFloat();

            printf("New Guests: ");
            eventGuests[i] = readInt();

            printf("Updated!\n");
            return;
        }
    }
    printf("Event ID not found.\n");
}

void deleteEvent() {
    printf("Enter ID to delete: ");
    int id = readInt();

    int i;
	for (i = 0; i < eventCount; i++) {
        if (eventId[i] == id) {
            int j;
			for (j = i; j < eventCount - 1; j++) {
                eventId[j]     = eventId[j + 1];
                strcpy(eventName[j], eventName[j + 1]);
                strcpy(eventType[j], eventType[j + 1]);
                strcpy(eventVenue[j], eventVenue[j + 1]);
                strcpy(eventDate[j], eventDate[j + 1]);
                eventBudget[j] = eventBudget[j + 1];
                eventGuests[j] = eventGuests[j + 1];
            }
            eventCount--;
            printf("Deleted!\n");
            return;
        }
    }
    printf("Event ID not found.\n");
}

// ================= TRACK =================

void trackEvents() {
    printf("\n=== TRACKING EVENTS ===\n");
    if (eventCount == 0) {
        printf("No events to track.\n");
        return;
    }
    int i;
	for (i = 0; i < eventCount; i++) {
        printf("Event: %s -> Upcoming\n", eventName[i]);
    }
}

// ================= BUDGET =================

void budgetInfo() {
    float total = 0;
    printf("\n=== BUDGET INFO ===\n");

    if (eventCount == 0) {
        printf("No events found.\n");
        return;
    }

    int i;
	for (i = 0; i < eventCount; i++) {
        printf("%s : %.2f\n", eventName[i], eventBudget[i]);
        total += eventBudget[i];
    }

    printf("Total Budget: %.2f\n", total);
}

// ================= GUEST INFO =================

void guestInfo() {
    printf("\n=== GUEST INFO ===\n");
    if (eventCount == 0) {
        printf("No events found.\n");
        return;
    }
    int i;
	for (i = 0; i < eventCount; i++) {
        printf("%s : %d guests\n", eventName[i], eventGuests[i]);
    }
}

// ================= COMPLAINT =================

void addComplaint(char email[]) {
    if (complaintCount >= MAX) {
        printf("Complaint limit reached.\n");
        return;
    }

    int i = complaintCount;

    printf("Enter complaint: ");
    readLine(complaintText[i], sizeof(complaintText[i]));
    strcpy(complaintEmail[i], email);
    complaintResolved[i] = 0;
    complaintCount++;
    printf("Complaint submitted!\n");
}

// ================= ADMIN: USER MANAGEMENT =================

void verifyUsers() {
    if (userCount == 0) {
        printf("No users registered yet.\n");
        return;
    }

    printf("\n=== VERIFY USERS ===\n");
    printf("1. Verify a specific user\n2. Verify ALL users\n");
    int choice = readInt();

    if (choice == 2) {
        int i;
		for (i = 0; i < userCount; i++)
            userVerified[i] = 1;
        printf("All users verified!\n");
        return;
    }

    char email[50];
    printf("Enter user email to verify: ");
    readLine(email, sizeof(email));

    int i;
	for (i = 0; i < userCount; i++) {
        if (strcmp(userEmail[i], email) == 0) {
            userVerified[i] = 1;
            printf("User %s verified!\n", userName[i]);
            return;
        }
    }
    printf("User not found.\n");
}

void viewUsers() {
    printf("\n=== ALL USERS ===\n");
    if (userCount == 0) {
        printf("No users registered yet.\n");
        return;
    }
    int i;
	for (i = 0; i < userCount; i++) {
        printf("\nName: %s\nOrg: %s\nDesignation: %s\nCNIC: %s\nPhone: %s\nEmail: %s\nVerified: %s\n",
               userName[i], userOrg[i], userDesignation[i],
               userCnic[i], userPhone[i], userEmail[i],
               userVerified[i] ? "Yes" : "No");
    }
}

void searchUser() {
    char email[50];
    printf("Enter user email: ");
    readLine(email, sizeof(email));

    int i;
	for (i = 0; i < userCount; i++) {
        if (strcmp(userEmail[i], email) == 0) {
            printf("\nName: %s\nOrg: %s\nDesignation: %s\nCNIC: %s\nPhone: %s\nEmail: %s\nVerified: %s\n",
                   userName[i], userOrg[i], userDesignation[i],
                   userCnic[i], userPhone[i], userEmail[i],
                   userVerified[i] ? "Yes" : "No");
            return;
        }
    }
    printf("User not found.\n");
}

void deleteUser() {
    char email[50];
    printf("Enter user email to delete: ");
    readLine(email, sizeof(email));

    int i;
	for (i = 0; i < userCount; i++) {
        if (strcmp(userEmail[i], email) == 0) {
            int j;
			for (j = i; j < userCount - 1; j++) {
                strcpy(userName[j], userName[j + 1]);
                strcpy(userOrg[j], userOrg[j + 1]);
                strcpy(userDesignation[j], userDesignation[j + 1]);
                strcpy(userCnic[j], userCnic[j + 1]);
                strcpy(userPhone[j], userPhone[j + 1]);
                strcpy(userEmail[j], userEmail[j + 1]);
                strcpy(userPassword[j], userPassword[j + 1]);
                userVerified[j] = userVerified[j + 1];
            }
            userCount--;
            printf("User deleted!\n");
            return;
        }
    }
    printf("User not found.\n");
}

// ================= ADMIN: COMPLAINTS =================

void viewComplaints() {
    printf("\n=== ALL COMPLAINTS ===\n");
    if (complaintCount == 0) {
        printf("No complaints found.\n");
        return;
    }
    int i;
	for (i = 0; i < complaintCount; i++) {
        printf("%d. [%s] %s -> %s\n", i + 1,
               complaintResolved[i] ? "RESOLVED" : "PENDING",
               complaintEmail[i], complaintText[i]);
    }
}

void resolveComplaint() {
    viewComplaints();
    if (complaintCount == 0) return;

    printf("Enter complaint number to mark as resolved: ");
    int num = readInt();

    if (num < 1 || num > complaintCount) {
        printf("Invalid complaint number.\n");
        return;
    }

    complaintResolved[num - 1] = 1;
    printf("Complaint marked as resolved!\n");
}

// ================= ADMIN PANEL =================

int adminLogin() {
    char pass[30];
    printf("Enter admin password: ");
    readLine(pass, sizeof(pass));
    return strcmp(pass, ADMIN_PASS) == 0;
}

void adminPanel() {
    if (!adminLogin()) {
        printf("Incorrect admin password!\n");
        return;
    }

    int choice;

    while (1) {
        printf("\n=== ADMIN PANEL ===\n");
        printf("1. Verify Users\n2. View Users\n3. Search User\n4. Delete User\n");
        printf("5. View Complaints\n6. Resolve Complaint\n7. Exit\n");
        choice = readInt();

        switch (choice) {
            case 1: verifyUsers(); break;
            case 2: viewUsers(); break;
            case 3: searchUser(); break;
            case 4: deleteUser(); break;
            case 5: viewComplaints(); break;
            case 6: resolveComplaint(); break;
            case 7: return;
            default: printf("Invalid choice.\n");
        }
    }
}

// ================= CLIENT MENU =================

void clientMenu(char email[]) {
    int choice;

    while (1) {
        printf("\n=== CLIENT MENU ===\n");
        printf("1. View Facilities\n2. Add Event\n3. View Events\n4. Search Event\n5. Update Event\n");
        printf("6. Delete Event\n7. Track\n8. Budget\n9. Guest Info\n10. Complaint\n11. Logout\n");
        choice = readInt();

        switch (choice) {
            case 1: viewFacilities(); break;
            case 2: addEvent(); break;
            case 3: viewEvents(); break;
            case 4: searchEvent(); break;
            case 5: updateEvent(); break;
            case 6: deleteEvent(); break;
            case 7: trackEvents(); break;
            case 8: budgetInfo(); break;
            case 9: guestInfo(); break;
            case 10: addComplaint(email); break;
            case 11: return;
            default: printf("Invalid choice.\n");
        }
    }
}

// ================= MAIN =================

int main() {
    int choice;

    printf("Welcome to Event Craft\n");

    while (1) {
        printf("\n=== EVENT CRAFT ===\n");
        printf("1. Signup\n2. Login (Client)\n3. Admin Panel\n4. View Facilities\n5. Exit\n");
        printf("Select:\n");
        choice = readInt();
        

        if (choice == 1) {
            signup();
        }
        else if (choice == 2) {
            char email[50], pass[30];
            printf("Email: ");
            readLine(email, sizeof(email));
            printf("Password: ");
            readLine(pass, sizeof(pass));

            int idx = login(email, pass);

            if (idx >= 0) {
                printf("Login Successful!\n");
                clientMenu(email);
            }
        }
        else if (choice == 3) {
            adminPanel();
        }
        else if (choice == 4) {
            viewFacilities();
        }
        else if (choice == 5) {
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
