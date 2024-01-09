// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for qsort function
#define MAX_RECORDS 100
struct Record {
    int id;
    char name[50];
    int age;
};

// Global array to store records
struct Record database[MAX_RECORDS];

// Global variable to track the number of records in the database
int numRecords = 0;

// Function to add a new record to the database
void addRecord(int id, const char *name, int age) {
    if (numRecords < MAX_RECORDS) {
        struct Record newRecord;
        newRecord.id = id;
        strncpy(newRecord.name, name, sizeof(newRecord.name));
        newRecord.age = age;

        database[numRecords++] = newRecord;
        printf("Record added successfully.\n");
    } else {
        printf("Database is full. Cannot add more records.\n");
    }
}

// Function to display all records in the database
void displayRecords() {
    if (numRecords > 0) {
        printf("ID\tName\tAge\n");
        for (int i = 0; i < numRecords; ++i) {
            printf("%d\t%s\t%d\n", database[i].id, database[i].name, database[i].age);
        }
    } else {
        printf("No records found in the database.\n");
    }
}

// Function to search for a record by ID
void searchRecord(int id) {
    for (int i = 0; i < numRecords; ++i) {
        if (database[i].id == id) {
            printf("Record found:\n");
            printf("ID\tName\tAge\n");
            printf("%d\t%s\t%d\n", database[i].id, database[i].name, database[i].age);
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}

// Function to update a record by ID
void updateRecord(int id, const char *newName, int newAge) {
    for (int i = 0; i < numRecords; ++i) {
        if (database[i].id == id) {
            strncpy(database[i].name, newName, sizeof(database[i].name));
            database[i].age = newAge;
            printf("Record updated successfully.\n");
            return;
        }
    }
    printf("Record with ID %d not found. Cannot update.\n", id);
}

// Function to delete a record by ID
void deleteRecord(int id) {
    for (int i = 0; i < numRecords; ++i) {
        if (database[i].id == id) {
            // Move the last record to the position of the record to be deleted
            database[i] = database[numRecords - 1];
            numRecords--;
            printf("Record deleted successfully.\n");
            return;
        }
    }
}    
    printf("Record with ID %d not found. Cannot delete.\n", id);
}
// Function to save records to a file
void saveRecordsToFile(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(database, sizeof(struct Record), numRecords, file);
        fclose(file);
        printf("Records saved to %s successfully.\n", filename);
    } else {
        printf("Error opening file for saving records.\n");
    }
}    
    // Function to load records from a file
void loadRecordsFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        numRecords = fread(database, sizeof(struct Record), MAX_RECORDS, file);
        fclose(file);
        printf("Records loaded from %s successfully.\n", filename);
    } else {
        printf("Error opening file for loading records.\n");
        
    }
}    
// Comparison function for sorting records by ID
int compareByID(const void *a, const void *b) {
    return ((struct Record *)a)->id - ((struct Record *)b)->id;
}

// Function to sort records by ID
void sortRecordsByID() {
    qsort(database, numRecords, sizeof(struct Record), compareByID);
    printf("Records sorted by ID.\n");
}
void searchRecordByName(const char *name) {
    int found = 0;
    for (int i = 0; i < numRecords; ++i) {
        if (strcmp(database[i].name, name) == 0) {
            if (!found) {
                printf("Records found:\n");
                printf("ID\tName\tAge\n");
                found = 1;
            }
            printf("%d\t%s\t%d\n", database[i].id, database[i].name, database[i].age);
        }
    }
    if (!found) {
        printf("No records with the name '%s' found.\n", name);
    }
}    
float calculateAverageAge() {
    if (numRecords > 0) {
        int totalAge = 0;
        for (int i = 0; i < numRecords; ++i) {
            totalAge += database[i].age;
        }
        return (float)totalAge / numRecords;
    } else {
        printf("No records found in the database.\n");
        return 0.0;
    }
}
void displayStatistics() {
    if (numRecords > 0) {
        int minAge = database[0].age;
        int maxAge = database[0].age;

        for (int i = 1; i < numRecords; ++i) {
            if (database[i].age < minAge) {
                minAge = database[i].age;
            }
            if (database[i].age > maxAge) {
                maxAge = database[i].age;
            }
        }

        printf("Statistics:\n");
        printf("Minimum Age: %d\n", minAge);
        printf("Maximum Age: %d\n", maxAge);
    } else {
        printf("No records found in the database.\n");
    }
}
void displayRecordsInRange(int minAge, int maxAge) {
    int found = 0;
    for (int i = 0; i < numRecords; ++i) {
        if (database[i].age >= minAge && database[i].age <= maxAge) {
            if (!found) {
                printf("Records in the specified age range:\n");
                printf("ID\tName\tAge\n");
                found = 1;
            }
            printf("%d\t%s\t%d\n", database[i].id, database[i].name, database[i].age);
        }
    }
    if (!found) {
        printf("No records found in the specified age range.\n");
    }
}
void displayRecordsByAgeGroup() {
    if (numRecords > 0) {
        printf("Records by age group:\n");
        printf("Age Group\tCount\n");

        // Assuming age groups of 10 years
        for (int groupStart = 0; groupStart < 100; groupStart += 10) {
            int groupEnd = groupStart + 9;
            int count = 0;

            for (int i = 0; i < numRecords; ++i) {
                if (database[i].age >= groupStart && database[i].age <= groupEnd) {
                    count++;
                }
            }

            if (count > 0) {
                printf("%d-%d\t\t%d\n", groupStart, groupEnd, count);
            }
        }
    } else {
        printf("No records found in the database.\n");
    }
}
// Comparison function for sorting records by name
int compareByName(const void *a, const void *b) {
    return strcmp(((struct Record *)a)->name, ((struct Record *)b)->name);
}

// Function to sort records by name
void sortRecordsByName() {
    qsort(database, numRecords, sizeof(struct Record), compareByName);
    printf("Records sorted by name.\n");
}
// Comparison function for sorting records by age
int compareByAge(const void *a, const void *b) {
    return ((struct Record *)a)->age - ((struct Record *)b)->age;
}

// Function to sort records by age
void sortRecordsByAge() {
    qsort(database, numRecords, sizeof(struct Record), compareByAge);
    printf("Records sorted by age.\n");
}
// Function to set the maximum number of records
void setMaxRecords(int max) {
    if (max >= numRecords) {
        MAX_RECORDS = max;
        printf("Maximum number of records set to %d.\n", MAX_RECORDS);
    } else {
        printf("Cannot set the maximum number of records to a value less than the current number of records.\n");
    }
}
void deleteAllRecords() {
    numRecords = 0;
    printf("All records deleted successfully.\n");
}
void displayMenu() {
    printf("Menu:\n");
    printf("1. Add Record\n");
    printf("2. Display Records\n");
    printf("3. Search Record\n");
    printf("4. Update Record\n");
    printf("5. Delete Record\n");
    printf("6. Save Records to File\n");
    printf("7. Load Records from File\n");
    printf("8. Calculate Average Age\n");
    printf("9. Display Statistics\n");
    printf("10. Display Records in Range\n");
    printf("11. Display Records by Age Group\n");
    printf("12. Sort Records by Name\n");
    printf("13. Sort Records by Age\n");
    printf("14. Set Max Records\n");
    printf("15. Delete All Records\n");
    printf("16. Exit\n");
}
int main() {
    int choice;

    do {
        displayMenu();  // Afficher le menu interactif
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Ajouter un enregistrement
                int id, age;
                char name[50];
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter age: ");
                scanf("%d", &age);
                addRecord(id, name, age);
                break;
            }
            case 2:
                // Afficher les enregistrements
                displayRecords();
                break;
            case 3: {
                // Rechercher un enregistrement
                int id;
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchRecord(id);
                break;
            }
            case 4: {
                // Mettre à jour un enregistrement
                int id, newAge;
                char newName[50];
                printf("Enter ID to update: ");
                scanf("%d", &id);
                printf("Enter new name: ");
                scanf("%s", newName);
                printf("Enter new age: ");
                scanf("%d", &newAge);
                updateRecord(id, newName, newAge);
                break;
            }
            case 5: {
                // Supprimer un enregistrement
                int id;
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteRecord(id);
                break;
            }
            case 6: {
                // Sauvegarder les enregistrements dans un fichier
                char filename[50];
                printf("Enter the filename to save records: ");
                scanf("%s", filename);
                saveRecordsToFile(filename);
                break;
            }
            case 7: {
                // Charger les enregistrements depuis un fichier
                char filename[50];
                printf("Enter the filename to load records: ");
                scanf("%s", filename);
                loadRecordsFromFile(filename);
                break;
            }
            case 8:
                // Calculer la moyenne d'âge
                printf("Average Age: %.2f\n", calculateAverageAge());
                break;
            case 9:
                // Afficher les statistiques
                displayStatistics();
                break;
            case 10: {
                // Afficher les enregistrements dans une plage d'âge
                int minAge, maxAge;
                printf("Enter the minimum age: ");
                scanf("%d", &minAge);
                printf("Enter the maximum age: ");
                scanf("%d", &maxAge);
                displayRecordsInRange(minAge, maxAge);
                break;
            }
            case 11:
                // Afficher les enregistrements par groupe d'âge
                displayRecordsByAgeGroup();
                break;
            case 12:
                // Trier les enregistrements par nom
                sortRecordsByName();
                break;
            case 13:
                // Trier les enregistrements par âge
                sortRecordsByAge();
                break;
            case 14: {
                // Définir le nombre maximal d'enregistrements
                int maxRecords;
                printf("Enter the maximum number of records: ");
                scanf("%d", &maxRecords);
                setMaxRecords(maxRecords);
                break;
            }
            case 15:
                // Supprimer tous les enregistrements
                deleteAllRecords();
                break;
            case 16:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 16);

    return 0;
}
