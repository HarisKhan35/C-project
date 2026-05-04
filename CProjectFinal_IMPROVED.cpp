#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

/* ============= CONSTANTS & MACROS ============= */
#define MAX_RECORDS 20
#define MAX_NAME_LEN 50
#define MAX_STRING_LEN 100
#define RECORD_FILE "record.dat"
#define TEMP_FILE "Temp.dat"
#define INVALID_CODE -1

/* ============= STRUCTURES ============= */
typedef struct Inventory {
    char name[MAX_NAME_LEN];
    float price;
    float discount_percent;
    bool is_available;
    char condition[MAX_NAME_LEN];
    bool has_ammo;
    bool installment_available;
    int gun_code;
    int legal_code;
    char gun_detail[MAX_STRING_LEN];
    bool payment_due;
    char storage_area[MAX_NAME_LEN];
    char best_customer[MAX_NAME_LEN];
    char profit_or_loss[MAX_NAME_LEN];
    bool more_stock;
    char ammo_stock[MAX_NAME_LEN];
    bool changes_required;
    char important_notes[MAX_NAME_LEN];
    char reminders[MAX_NAME_LEN];
    char colors_available[MAX_NAME_LEN];
} Inventory;

/* ============= FUNCTION DECLARATIONS ============= */
void addInventory(void);
void inputInventory(Inventory *I);
void saveInitialRecords(Inventory rec[], int n);
void displayInventory(void);
void searchInventory(void);
void updateDiscount(void);
void removeInventory(void);
void countInventory(void);
void updatePriceByCode(void);
void displayProfitItems(void);
void displayLossItems(void);
void searchByName(void);
void displayByStorageArea(void);
void displayByColor(void);
void showGunRecord(void);

/* ============= UTILITY FUNCTIONS ============= */
void clearInputBuffer(void);
bool isValidPrice(float price);
bool isValidCode(int code);
bool stringToLowercase(char *str);
bool fileExists(const char *filename);
void printErrorMessage(const char *message);
void printSuccessMessage(const char *message);

/* ============= MAIN FUNCTION ============= */
int main(void)
{
    int choice = 0;

    Inventory Rec[MAX_RECORDS] = {
        {"M416", 1000, 0.0, true, "New", true, false, 123, 1122, "Assault rifle", false, "Backside", "Harry", "Profit", false, "10K", false, "Good", "None", "Black"},
        {"Scar-L", 600, 0.0, true, "New", true, false, 213, 2211, "Assault rifle", false, "Inventory", "None", "Loss", false, "5K", false, "Average", "None", "Brown"},
        {"AUG-43", 800, 0.0, true, "New", true, false, 312, 1221, "Assault rifle", false, "Storage", "Zyrx", "Profit", false, "2.5K", false, "Good", "None", "Green"},
        {"UMP-45", 400, 0.0, true, "New", true, false, 345, 2112, "SMG", false, "Inventory", "None", "Profit", false, "5K", false, "Good", "None", "Brown"},
        {"S12K", 1000, 0.0, true, "New", true, false, 567, 3211, "Shotgun", false, "Backside", "Harry", "Profit", false, "12 Boxes", false, "Ammo", "None", "Grey"},
        {"DBS", 1500, 0.0, true, "New", true, false, 789, 4211, "Shotgun", false, "Storage", "None", "Loss", false, "24 Boxes", false, "Stable", "None", "Dark Grey"},
        {"S686", 700, 0.0, true, "New", true, false, 567, 4231, "Shotgun", false, "Inventory", "Robert", "Profit", false, "12 Boxes", false, "Ammo", "None", "Red"},
        {"S1897", 800, 0.0, true, "New", true, false, 657, 9911, "Shotgun", false, "Inventory", "None", "Low", false, "31 Boxes", false, "Sell", "None", "Grey"},
        {"M24", 600, 0.0, true, "New", true, false, 456, 8711, "Sniper", false, "Inventory", "Harry", "Profit", false, "1K", false, "Ammo", "None", "Dark Grey"},
        {"AWM", 1500, 0.0, true, "New", true, false, 999, 8799, "Sniper", false, "Backside", "Smith", "Profit", false, "10 Boxes", false, "Expensive", "None", "Green"}
    };

    saveInitialRecords(Rec, 10);

    do {
        printf("\n============ INVENTORY MANAGEMENT SYSTEM ============\n");
        printf("1.  Add Inventory\n");
        printf("2.  Display Inventory\n");
        printf("3.  Search by Gun Code\n");
        printf("4.  Update Discount\n");
        printf("5.  Remove Inventory\n");
        printf("6.  Count Records\n");
        printf("7.  Update Price\n");
        printf("8.  Display Profit Items\n");
        printf("9.  Display Loss Items\n");
        printf("10. Search by Name\n");
        printf("11. Display by Storage Area\n");
        printf("12. Display by Color\n");
        printf("13. Show Specific Gun Record\n");
        printf("14. Save Initial Records Again\n");
        printf("15. Exit\n");
        printf("=====================================================\n");
        printf("Enter your choice (1-15): ");
        
        if (scanf("%d", &choice) != 1) {
            printErrorMessage("Invalid input! Please enter a number.");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addInventory();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                searchInventory();
                break;
            case 4:
                updateDiscount();
                break;
            case 5:
                removeInventory();
                break;
            case 6:
                countInventory();
                break;
            case 7:
                updatePriceByCode();
                break;
            case 8:
                displayProfitItems();
                break;
            case 9:
                displayLossItems();
                break;
            case 10:
                searchByName();
                break;
            case 11:
                displayByStorageArea();
                break;
            case 12:
                displayByColor();
                break;
            case 13:
                showGunRecord();
                break;
            case 14:
                saveInitialRecords(Rec, 10);
                printSuccessMessage("Initial records saved successfully!");
                break;
            case 15:
                printf("\nThank you for using Inventory Management System. Goodbye!\n\n");
                break;
            default:
                printErrorMessage("Invalid choice! Please enter a number between 1-15.");
        }
    } while (choice != 15);

    return 0;
}

/* ============= UTILITY FUNCTION IMPLEMENTATIONS ============= */
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool isValidPrice(float price)
{
    return price > 0;
}

bool isValidCode(int code)
{
    return code > 0 && code <= 9999;
}

bool stringToLowercase(char *str)
{
    if (str == NULL) return false;
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
    return true;
}

bool fileExists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

void printErrorMessage(const char *message)
{
    printf("\n[ERROR] %s\n", message);
}

void printSuccessMessage(const char *message)
{
    printf("\n[SUCCESS] %s\n", message);
}

/* ============= MAIN FUNCTION IMPLEMENTATIONS ============= */
void addInventory(void)
{
    Inventory I;
    memset(&I, 0, sizeof(Inventory));
    
    inputInventory(&I);
    
    FILE *f = fopen(RECORD_FILE, "ab");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for writing.");
        return;
    }
    
    if (fwrite(&I, sizeof(I), 1, f) != 1) {
        printErrorMessage("Failed to write record to file.");
    } else {
        printSuccessMessage("Gun record added successfully!");
    }
    
    fclose(f);
}

void inputInventory(Inventory *I)
{
    clearInputBuffer();
    
    printf("\n--- Adding New Gun Inventory ---\n");
    
    printf("Enter gun name (max %d characters): ", MAX_NAME_LEN - 1);
    if (fgets(I->name, sizeof(I->name), stdin) == NULL) {
        printErrorMessage("Failed to read gun name.");
        return;
    }
    // Remove newline from fgets
    I->name[strcspn(I->name, "\n")] = '\0';
    
    if (strlen(I->name) == 0) {
        printErrorMessage("Gun name cannot be empty!");
        return;
    }

    printf("Enter price of this gun: $");
    if (scanf("%f", &I->price) != 1) {
        printErrorMessage("Invalid price entered.");
        clearInputBuffer();
        return;
    }
    
    if (!isValidPrice(I->price)) {
        printErrorMessage("Price must be greater than 0.");
        return;
    }

    printf("Enter discount in percent (0-100): ");
    if (scanf("%f", &I->discount_percent) != 1) {
        printErrorMessage("Invalid discount entered.");
        clearInputBuffer();
        return;
    }
    
    if (I->discount_percent < 0 || I->discount_percent > 100) {
        printErrorMessage("Discount must be between 0 and 100.");
        return;
    }

    printf("Enter gun code (1-9999): ");
    if (scanf("%d", &I->gun_code) != 1) {
        printErrorMessage("Invalid gun code entered.");
        clearInputBuffer();
        return;
    }
    
    if (!isValidCode(I->gun_code)) {
        printErrorMessage("Gun code must be between 1 and 9999.");
        return;
    }
    
    I->is_available = true;
    I->has_ammo = true;
}

void saveInitialRecords(Inventory rec[], int n)
{
    FILE *f = fopen(RECORD_FILE, "wb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for writing.");
        return;
    }
    
    int written = 0;
    for (int i = 0; i < n; i++) {
        if (fwrite(&rec[i], sizeof(Inventory), 1, f) == 1) {
            written++;
        }
    }
    
    fclose(f);
    printf("[INFO] Saved %d initial records.\n", written);
}

void displayInventory(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found. Please add some records first.");
        return;
    }

    Inventory I;
    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    printf("\n========== GUN INVENTORY ==========\n");
    printf("%-20s | %-10s | %-6s\n", "Name", "Price", "Code");
    printf("-----------------------------------\n");
    
    int count = 0;
    while (fread(&I, sizeof(I), 1, f) == 1) {
        printf("%-20s | $%-9.2f | %-6d\n", I.name, I.price, I.gun_code);
        count++;
    }
    
    if (count == 0) {
        printf("No records found.\n");
    } else {
        printf("-----------------------------------\n");
        printf("Total guns: %d\n", count);
    }
    
    fclose(f);
}

void searchInventory(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    int code;
    
    printf("\n--- Search by Gun Code ---\n");
    printf("Enter gun code: ");
    if (scanf("%d", &code) != 1) {
        printErrorMessage("Invalid code entered.");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    if (!isValidCode(code)) {
        printErrorMessage("Gun code must be between 1 and 9999.");
        return;
    }

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    bool found = false;
    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (I.gun_code == code) {
            printf("\n[FOUND] Gun Details:\n");
            printf("Name: %s\n", I.name);
            printf("Price: $%.2f\n", I.price);
            printf("Discount: %.1f%%\n", I.discount_percent);
            printf("Gun Code: %d\n", I.gun_code);
            printf("Condition: %s\n", I.condition);
            printf("Storage Area: %s\n", I.storage_area);
            printf("Color: %s\n", I.colors_available);
            found = true;
            break;
        }
    }
    
    if (!found) {
        printErrorMessage("No gun found with this code.");
    }
    
    fclose(f);
}

void updateDiscount(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    float new_discount;
    int code;
    bool found = false;

    printf("\n--- Update Discount ---\n");
    printf("Enter gun code: ");
    if (scanf("%d", &code) != 1) {
        printErrorMessage("Invalid code entered.");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    if (!isValidCode(code)) {
        printErrorMessage("Gun code must be between 1 and 9999.");
        return;
    }

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    FILE *tf = fopen(TEMP_FILE, "wb");
    if (tf == NULL) {
        printErrorMessage("Unable to create temporary file.");
        fclose(f);
        return;
    }

    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (I.gun_code == code) {
            found = true;
            printf("Enter new discount (0-100): ");
            if (scanf("%f", &new_discount) != 1) {
                printErrorMessage("Invalid discount entered.");
                clearInputBuffer();
                fwrite(&I, sizeof(I), 1, tf);
                continue;
            }
            clearInputBuffer();
            
            if (new_discount < 0 || new_discount > 100) {
                printErrorMessage("Discount must be between 0 and 100.");
                fwrite(&I, sizeof(I), 1, tf);
                continue;
            }
            
            I.discount_percent = new_discount;
        }
        fwrite(&I, sizeof(I), 1, tf);
    }

    fclose(f);
    fclose(tf);

    if (found) {
        remove(RECORD_FILE);
        rename(TEMP_FILE, RECORD_FILE);
        printSuccessMessage("Discount updated successfully!");
    } else {
        remove(TEMP_FILE);
        printErrorMessage("No gun found with this code.");
    }
}

void removeInventory(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    int code;
    bool removed = false;

    printf("\n--- Remove Gun Record ---\n");
    printf("Enter gun code to remove: ");
    if (scanf("%d", &code) != 1) {
        printErrorMessage("Invalid code entered.");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    if (!isValidCode(code)) {
        printErrorMessage("Gun code must be between 1 and 9999.");
        return;
    }

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    FILE *t = fopen(TEMP_FILE, "wb");
    if (t == NULL) {
        printErrorMessage("Unable to create temporary file.");
        fclose(f);
        return;
    }

    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (I.gun_code != code) {
            fwrite(&I, sizeof(I), 1, t);
        } else {
            removed = true;
        }
    }

    fclose(f);
    fclose(t);

    remove(RECORD_FILE);
    rename(TEMP_FILE, RECORD_FILE);
    
    if (removed) {
        printSuccessMessage("Gun record removed successfully!");
    } else {
        printErrorMessage("No gun found with this code.");
    }
}

void countInventory(void)
{
    if (!fileExists(RECORD_FILE)) {
        printf("[INFO] No records found. Total Records: 0\n");
        return;
    }

    Inventory I;
    int count = 0;

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    while (fread(&I, sizeof(I), 1, f) == 1) {
        count++;
    }

    fclose(f);
    printf("\n[INFO] Total Records: %d\n", count);
}

void updatePriceByCode(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    float new_price;
    int code;
    bool found = false;

    printf("\n--- Update Price ---\n");
    printf("Enter gun code: ");
    if (scanf("%d", &code) != 1) {
        printErrorMessage("Invalid code entered.");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    if (!isValidCode(code)) {
        printErrorMessage("Gun code must be between 1 and 9999.");
        return;
    }

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    FILE *tf = fopen(TEMP_FILE, "wb");
    if (tf == NULL) {
        printErrorMessage("Unable to create temporary file.");
        fclose(f);
        return;
    }

    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (I.gun_code == code) {
            found = true;
            printf("Enter new price: $");
            if (scanf("%f", &new_price) != 1) {
                printErrorMessage("Invalid price entered.");
                clearInputBuffer();
                fwrite(&I, sizeof(I), 1, tf);
                continue;
            }
            clearInputBuffer();
            
            if (!isValidPrice(new_price)) {
                printErrorMessage("Price must be greater than 0.");
                fwrite(&I, sizeof(I), 1, tf);
                continue;
            }
            
            I.price = new_price;
        }
        fwrite(&I, sizeof(I), 1, tf);
    }

    fclose(f);
    fclose(tf);

    if (found) {
        remove(RECORD_FILE);
        rename(TEMP_FILE, RECORD_FILE);
        printSuccessMessage("Price updated successfully!");
    } else {
        remove(TEMP_FILE);
        printErrorMessage("No gun found with this code.");
    }
}

void displayProfitItems(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    printf("\n========== PROFIT ITEMS ==========\n");
    int count = 0;
    
    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (strcmp(I.profit_or_loss, "Profit") == 0) {
            printf("%s - $%.2f\n", I.name, I.price);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No profit items found.\n");
    } else {
        printf("Total profit items: %d\n", count);
    }
    
    fclose(f);
}

void displayLossItems(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    printf("\n========== LOSS ITEMS ==========\n");
    int count = 0;
    
    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (strcmp(I.profit_or_loss, "Loss") == 0 || strcmp(I.profit_or_loss, "Low") == 0) {
            printf("%s - $%.2f\n", I.name, I.price);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No loss items found.\n");
    } else {
        printf("Total loss items: %d\n", count);
    }
    
    fclose(f);
}

void searchByName(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    char search_name[MAX_NAME_LEN];

    printf("\n--- Search by Gun Name ---\n");
    printf("Enter gun name: ");
    
    clearInputBuffer();
    if (fgets(search_name, sizeof(search_name), stdin) == NULL) {
        printErrorMessage("Failed to read gun name.");
        return;
    }
    
    search_name[strcspn(search_name, "\n")] = '\0';
    
    if (strlen(search_name) == 0) {
        printErrorMessage("Gun name cannot be empty!");
        return;
    }

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    bool found = false;
    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (strcasecmp(I.name, search_name) == 0) {
            printf("\n[FOUND] Gun Details:\n");
            printf("Name: %s\n", I.name);
            printf("Price: $%.2f\n", I.price);
            printf("Discount: %.1f%%\n", I.discount_percent);
            printf("Gun Code: %d\n", I.gun_code);
            printf("Condition: %s\n", I.condition);
            printf("Storage Area: %s\n", I.storage_area);
            printf("Color: %s\n", I.colors_available);
            found = true;
            break;
        }
    }

    if (!found) {
        printErrorMessage("No gun found with this name.");
    }
    
    fclose(f);
}

void displayByStorageArea(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    char area[MAX_NAME_LEN];

    printf("\n--- Search by Storage Area ---\n");
    printf("Enter storage area name: ");
    
    if (scanf("%49s", area) != 1) {
        printErrorMessage("Invalid input entered.");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    printf("\n========== GUNS BY STORAGE AREA ==========\n");
    int count = 0;
    
    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (strcmp(I.storage_area, area) == 0) {
            printf("%s - $%.2f\n", I.name, I.price);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No guns found in storage area: %s\n", area);
    } else {
        printf("Total guns in %s: %d\n", area, count);
    }
    
    fclose(f);
}

void displayByColor(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    char color[MAX_NAME_LEN];

    printf("\n--- Search by Color ---\n");
    printf("Enter color: ");
    
    if (scanf("%49s", color) != 1) {
        printErrorMessage("Invalid input entered.");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    printf("\n========== GUNS BY COLOR ==========\n");
    int count = 0;
    
    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (strcmp(I.colors_available, color) == 0) {
            printf("%s - $%.2f\n", I.name, I.price);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No guns found with color: %s\n", color);
    } else {
        printf("Total guns in %s: %d\n", color, count);
    }
    
    fclose(f);
}

void showGunRecord(void)
{
    if (!fileExists(RECORD_FILE)) {
        printErrorMessage("No records file found.");
        return;
    }

    Inventory I;
    int code;

    printf("\n--- Display Gun Record ---\n");
    printf("Enter gun code: ");
    
    if (scanf("%d", &code) != 1) {
        printErrorMessage("Invalid code entered.");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    if (!isValidCode(code)) {
        printErrorMessage("Gun code must be between 1 and 9999.");
        return;
    }

    FILE *f = fopen(RECORD_FILE, "rb");
    if (f == NULL) {
        printErrorMessage("Unable to open record file for reading.");
        return;
    }

    bool found = false;
    while (fread(&I, sizeof(I), 1, f) == 1) {
        if (I.gun_code == code) {
            printf("\n========== COMPLETE GUN RECORD ==========\n");
            printf("Name: %s\n", I.name);
            printf("Price: $%.2f\n", I.price);
            printf("Discount: %.1f%%\n", I.discount_percent);
            printf("Gun Code: %d\n", I.gun_code);
            printf("Legal Code: %d\n", I.legal_code);
            printf("Condition: %s\n", I.condition);
            printf("Storage Area: %s\n", I.storage_area);
            printf("Color Available: %s\n", I.colors_available);
            printf("Gun Detail: %s\n", I.gun_detail);
            printf("Best Customer: %s\n", I.best_customer);
            printf("Profit/Loss Status: %s\n", I.profit_or_loss);
            printf("Available: %s\n", I.is_available ? "Yes" : "No");
            printf("Has Ammo: %s\n", I.has_ammo ? "Yes" : "No");
            printf("Installment Available: %s\n", I.installment_available ? "Yes" : "No");
            printf("=========================================
");
            found = true;
            break;
        }
    }

    if (!found) {
        printErrorMessage("No gun found with this code.");
    }
    
    fclose(f);
}