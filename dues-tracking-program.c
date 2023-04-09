#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dues {
    float amount;
    char date[11];
    char name[20];
    char surname[20];
    int apartment_no;
};

void add_record() {
    struct dues new_record;
    
    // Prompt the user to enter the record details
    printf("\nEnter the amount of dues paid: ");
    scanf("%f", &new_record.amount);
    printf("Enter the payment date (dd-mm-yyyy): ");
    scanf("%s", new_record.date);
    printf("Enter the payer's name: ");
    scanf("%s", new_record.name);
    printf("Enter the payer's surname: ");
    scanf("%s", new_record.surname);
    printf("Enter the apartment number: ");
    scanf("%d", &new_record.apartment_no);

    // Open the file and write the record to it
    FILE *file = fopen("dues.txt", "a");
    if (file == NULL) {
        printf("File cannot be opened.");
        return;
    }
    fprintf(file, "%-15.2f %-15s %-15s %-15s %-15d\n", new_record.amount, new_record.date, new_record.name, new_record.surname, new_record.apartment_no);
    printf("\nRecord added.\n");
    fclose(file);
    
    system("pause");
}
void show_all_records() {	
	FILE *file = fopen("dues.txt", "r");
    if (file == NULL) {
        printf("File cannot be opened.");
        return;
    }
    
    // Print the header row and separator
    printf("\nDues records:\n\n");
    printf("%-15s %-15s %-15s %-15s %-15s\n", "Amount", "Date", "Name", "Surname", "Apartment No");
    printf("-------------------------------------------------------------------------\n");
    
    // Read the file and print each record to the console
    struct dues record;
    while (fscanf(file, "%f %s %s %s %d\n", &record.amount, record.date, record.name, record.surname, &record.apartment_no) != EOF) {
        printf("%-15.2f %-15s %-15s %-15s %-15d\n", record.amount, record.date, record.name, record.surname, record.apartment_no);
    }
    fclose(file);
	
	system("pause");
}
void apartment_information() {
    // get the apartment number to search for from the user
    int apartment_number;
    printf("\nEnter the apartment number: ");
    scanf("%d", &apartment_number);
    
	if(apartment_number > 30 || apartment_number <= 0) {
		printf("Apartment numbers must be between 1 and 30!\nPlease make a valid selection.\n");
		system("pause");
		return;
	}

    // open the file for reading
    FILE *file = fopen("dues.txt", "r");
    if (file == NULL) {
        printf("Could not open file.");
        return;
    }

    // find and print the payment information for the requested apartment number
    struct dues info;
    int found = 0;
    while (fscanf(file, "%f %s %s %s %d\n", &info.amount, info.date, info.name, info.surname, &info.apartment_no) != EOF) {
        if (info.apartment_no == apartment_number) {
            found = 1;
            printf("\nPayment information:\n\n");
            printf("%-15s %-15s %-15s %-15s %-15s\n", "Amount", "Date", "First Name", "Last Name", "Apartment Number");
            printf("------------------------------------------------------------------------\n");
            printf("%-15.2f %-15s %-15s %-15s %-15d\n", info.amount, info.date, info.name, info.surname, info.apartment_no);
        }
    }

    // if no payments were found for the requested apartment number, let the user know
    if (!found) {
        printf("\nApartment %d has not made any payments.\n", apartment_number);
    }

    // close the file
    fclose(file);

    system("pause");
}
void outstanding_fees(int membership_fee) {
	// Open the file
	FILE *file = fopen("dues.txt", "r");
	// If the file cannot be opened, print an error message and exit the function
	if (file == NULL) {
	printf("Could not open the file.\n");
	return;
	}
	
	// Define variables to calculate the number of apartments with debt and the total debt amount
	int apartments_with_debt_count = 0;
	float total_debt = 0;
	struct dues debt;
	
	// Print the list of apartments with debt
	printf("------------------------------------\n");
	printf("List of apartments with dues debt:\n");
	printf("------------------------------------\n");
	while (fscanf(file, "%f %s %s %s %d\n", &debt.amount, debt.date, debt.name, debt.surname, &debt.apartment_no) != EOF) { 
	    if ((debt.amount - membership_fee) < 0) { // Check if there is a debt for the dues
	        printf("Dues debt of apartment %d: %.2f\n", debt.apartment_no, -(debt.amount - membership_fee));
	        apartments_with_debt_count++;
	        total_debt = total_debt + (debt.amount - membership_fee);
	    }
	}
	
	// If there is no apartment with debt, print a message. Otherwise, print the number of apartments with debt and the total debt amount
	if (apartments_with_debt_count == 0) {
	    printf("There are no apartments with dues debt.\n");
	} else {
	    printf("Total dues debt: %.2f\n", -(total_debt));
	}
	
	fclose(file);
	    
	system("pause");
}
void update_info() {
	int apartmentNo;
	float duesAmount;
	char duesDate[11];
	char firstName[20], lastName[20];
	
	printf("Apartment number to be updated: ");
	scanf("%d", &apartmentNo);
	
	if (apartmentNo > 30 || apartmentNo <= 0) {
	    printf("Apartment numbers should be between 0-30!\nPlease make a selection again.\n");
	    system("pause");
	    return;
	}
	
	// Creating a new dues struct.
	struct dues updated;
	
	// Opening the "dues.txt" file in read mode.
	FILE *file;
	file = fopen("dues.txt", "r");
	if (file == NULL) {
	    // If the file cannot be opened, print an error message and exit the program.
	    printf("File could not be opened!");
	    exit(1);
	}
	
	// Creating a temporary file.
	FILE *tempFile;
	tempFile = fopen("temp_dues.txt", "w");
	
	// Define a variable to check if there is a record for the apartment number.
	int apartmentExists = 0;
	while (fscanf(file, "%f %s %s %s %d\n", &updated.amount, updated.date, updated.name, updated.surname, &updated.apartment_no) != EOF) {
	    // If the apartment number of the read line is equal to the one we are looking for, we will update the record.
	    if (updated.apartment_no == apartmentNo) {
	        apartmentExists = 1;
	        printf("Dues amount: ");
	        scanf("%f", &duesAmount);
	        printf("Dues date (dd/mm/yyyy): ");
	        scanf("%s", duesDate);
	        printf("First name: ");
	        scanf("%s", firstName);
	        printf("Last name: ");
	        scanf("%s", lastName);
	
	        // Save the updated record to the dues struct.
	        updated.amount = duesAmount;
	        strcpy(updated.date, duesDate);
	        strcpy(updated.name, firstName);
	        strcpy(updated.surname, lastName);
	    }
	
	    // Write the read line to the temporary file.
	    fprintf(tempFile, "%-15.2f %-15s %-15s %-15s %-15d\n", updated.amount, updated.date, updated.name, updated.surname, updated.apartment_no);
	}
	
	// Close the files.
	fclose(file);
	fclose(tempFile);
	
	// Delete the old file and rename the temporary file.
	remove("dues.txt");
	rename("temp_dues.txt", "dues.txt");
	
	// If there is a record for the apartment number, print "Update done." message, otherwise print an error message.
	if (apartmentExists) {
	    printf("Update done.\n");
	} else {
	    printf("There is no record for this apartment number!\n");
	}
	
	system("pause");
	}
void delete_record() {
	int apartmentNo, found = 0;
	FILE *fp, *temp;
	struct dues record;
	
	printf("Enter the apartment number to be deleted: ");
	scanf("%d", &apartmentNo);
	
	fp = fopen("dues.txt", "rb"); // open dues.txt file for reading
	temp = fopen("temp.txt", "wb"); // create a temporary file
	
	// read each record from the file. If the record with the specified apartment number is found, do not write it to the temporary file. Write all other records to the temporary file.
	while (fscanf(fp, "%f %s %s %s %d\n", &record.amount, record.date, record.name, record.surname, &record.apartment_no) != EOF) { 
	    if (record.apartment_no == apartmentNo) {  
	        found = 1;
	        continue;  
	    }
	    fprintf(temp,"%-15.2f %-15s %-15s %-15s %-15d\n",record.amount, record.date, record.name, record.surname, record.apartment_no); 
	}
	
	fclose(fp);
	fclose(temp);
	remove("dues.txt"); // delete the old file
	rename("temp.txt", "dues.txt"); // rename the temporary file
	
	// If the record is found and deleted, display a message saying it has been deleted. Otherwise, display an error message.
	if (found == 1) { 
	    printf("Apartment record has been deleted.\n");
	} else {
	    printf("Apartment number not found!\n");
	}
	
	system("pause");
	}

int main() {

	int choice;
	int membership_fee;
	
	printf("Enter membership fee: ");
	scanf("%d", &membership_fee);
	
	do {
	    system("cls");
	    printf("\n------------------");
	    printf("\nMembership Tracking Menu");
	    printf("\n------------------");
	    printf("\n1- Add record");
	    printf("\n2- Show all records");
	    printf("\n3- Show record by apartment");
	    printf("\n4- List members with outstanding fees");
	    printf("\n5- Update record");
	    printf("\n6- Delete record");
	    printf("\n7- Exit");
	    printf("\n---------------------------");
	    printf("\nEnter your choice: ");
	    scanf("%d", &choice);
	    switch (choice) {
	        case 1:
	            add_record();
	            break;
	        case 2:
	            show_all_records();
	            break;
	        case 3:
	            apartment_information();
	            break;
	        case 4:
	            outstanding_fees(membership_fee);
	            break;
	        case 5:
	            update_info();
	            break;
	        case 6:
	            delete_record();
	            break;
	        case 7:
	            printf("\n-----------------------------\n");
	            printf("| Exiting program.           |");
	            printf("\n-----------------------------\n");
	            break;
	        default:
	            printf("Invalid choice. Please try again.\n");      
	            system("pause");
	            break;
	    }
	} while (choice != 7);
	
	return 0;
}