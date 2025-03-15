
#include "Jack_libFS2025.h"
#include <ctype.h>  // For tolower()

// Function to display the menu
void displayMenu() {
    
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    
    printf("\nPress Enter to continue...");
    for (char ch = '\0'; ch != '\n'; ch = getchar()); // go to the end of the line
}

int main() {
    
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is John Doe.\n\n"
                          "I am a computer science student passionate about systems programming.\n"
                          "This project involves creating a file system library in C.\n"
                          "I hope you find my implementation useful!";
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    while (1) {
        choice = -1;
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        for (char ch = '\0'; ch != '\n'; ch = getchar()); // go to the end of the line

        switch (choice) {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                if (file_index != -1) {
                    printf("Error: A file is open. Please close the current file first.");
                } else {
                    printf("Enter the filename to open: ");
                    fgets(filename, MAX_FILENAME, stdin);
                    filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                    file_index = fileOpen(filename);
                    if (file_index == -1) {
                        printf("Error opening file.\n");
                    }
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);
                    if (fileWrite(file_index, introduction) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file 
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Reading from file '%s'...\n", filename);
                    
                    // Leave one byte for the null terminator
                    int bytesRead = fileRead(file_index, buffer, sizeof(buffer) - 1);
                    
                    if (bytesRead == -1) {
                        printf("Error reading from file.\n");
                    } else {
                        buffer[bytesRead] = '\0';
                        
                        printf("File contents: %s\n", buffer);
                    }
                }
                waitForUser();
                break;
                
            case 5:
                if (fileClose(file_index) != 0) {
                    printf("Error closing file %s.\n", filename);
                } else {
                    file_index = -1;
                }
                waitForUser();
                break;
                
            case 6:
                printf("Enter the filename to delete: ");
                
                char fileToDelete[MAX_FILENAME];
                
                fgets(fileToDelete, MAX_FILENAME, stdin);
                fileToDelete[strcspn(fileToDelete, "\n")] = '\0'; // Remove newline
                
                int deletedFileIndex = fileDelete(fileToDelete);
                
                if (deletedFileIndex == -1) {
                    printf("Error deleting file.\n");
                } else if (file_index == deletedFileIndex) {
                    // The current file was deleted
                    file_index = -1;
                }
                waitForUser();
                break;
                
            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}

