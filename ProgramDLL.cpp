#include <stdio.h>
#include <stdlib.h>

// Structure to represent an Insurance Policy
struct Insurance {
    struct Insurance* prev;
    int policyNumber;
    int policyPremium;
    int policyStatus;
    int policyAgentCode;
    struct Insurance* next;
};

// Insert a new insurance policy at the end
void InsertPolicy(struct Insurance** head) {
    struct Insurance* newPolicy = (struct Insurance*)malloc(sizeof(struct Insurance));
    if (!newPolicy) {
        printf("Memory allocation failed\n");
        return;
    }
    printf("Policy Number: ");
    scanf("%d", &newPolicy->policyNumber);
    printf("Policy Premium: ");
    scanf("%d", &newPolicy->policyPremium);
    printf("Policy Status: ");
    scanf("%d", &newPolicy->policyStatus);
    printf("Policy Agent Code: ");
    scanf("%d", &newPolicy->policyAgentCode);
    newPolicy->next = NULL;

    if (*head == NULL) {
        *head = newPolicy;
        newPolicy->prev = NULL;
    } else {
        struct Insurance* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newPolicy;
        newPolicy->prev = temp;
    }
    printf("Policy added successfully!\n");
}

// Delete an insurance policy by policy number
void DeletePolicy(struct Insurance** head) {
    int policyNumber;
    printf("Enter the Policy Number you want to delete: ");
    scanf("%d", &policyNumber);

    struct Insurance* temp = *head;

    while (temp != NULL && temp->policyNumber != policyNumber) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Policy not found.\n");
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
    printf("Policy deleted successfully!\n");
}

// Search for a policy by policy number
void SearchPolicy(struct Insurance* head) {
    int policyNumber;
    printf("Enter the Policy Number to search: ");
    scanf("%d", &policyNumber);

    struct Insurance* temp = head;
    while (temp != NULL) {
        if (temp->policyNumber == policyNumber) {
            printf("Policy found!\n");
            printf("Policy Number: %d\n", temp->policyNumber);
            printf("Policy Premium: %d\n", temp->policyPremium);
            printf("Policy Status: %d\n", temp->policyStatus);
            printf("Policy Agent Code: %d\n", temp->policyAgentCode);
            return;
        }
        temp = temp->next;
    }
    printf("Policy not found.\n");
}

// Find and display the policy with the highest premium
void PolicyWithHighestPremium(struct Insurance* head) {
    if (head == NULL) {
        printf("No policies available.\n");
        return;
    }

    struct Insurance* temp = head;
    struct Insurance* highest = head;

    while (temp != NULL) {
        if (temp->policyPremium > highest->policyPremium) {
            highest = temp;
        }
        temp = temp->next;
    }

    printf("Policy with the highest premium:\n");
    printf("Policy Number: %d\n", highest->policyNumber);
    printf("Premium Amount: %d\n", highest->policyPremium);
}

// Display all policies
void DisplayPolicies(struct Insurance* head) {
    if (head == NULL) {
        printf("No policies to display.\n");
        return;
    }

    struct Insurance* temp = head;
    while (temp != NULL) {
        printf("Policy Number: %d\n", temp->policyNumber);
        printf("Policy Premium: %d\n", temp->policyPremium);
        printf("Policy Status: %d\n", temp->policyStatus);
        printf("Policy Agent Code: %d\n\n", temp->policyAgentCode);
        temp = temp->next;
    }
}

// Free the entire linked list to avoid memory leaks
void FreeAllPolicies(struct Insurance* head) {
    struct Insurance* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice;
    struct Insurance* head = NULL;

    do {
        printf("\n--- Insurance Company Management System ---\n");
        printf("1. Insert a Policy\n");
        printf("2. Delete a Policy\n");
        printf("3. Search Policy Details\n");
        printf("4. Find Policy with Highest Premium\n");
        printf("5. Display All Policies\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                InsertPolicy(&head);
                break;
            case 2:
                DeletePolicy(&head);
                break;
            case 3:
                SearchPolicy(head);
                break;
            case 4:
                PolicyWithHighestPremium(head);
                break;
            case 5:
                DisplayPolicies(head);
                break;
            case 6:
                printf("Exiting program. Cleaning up memory...\n");
                FreeAllPolicies(head);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

