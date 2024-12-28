#include <stdio.h>
#include <stdlib.h>

// Contiguous Memory Allocation (Fixed size array)
void contiguous_allocation() {
    int n;
    printf("Enter the number of elements to allocate: ");
    scanf("%d", &n);
    
    // Allocating contiguous memory using malloc
    int *arr = (int*) malloc(n * sizeof(int));
    
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Initialize and print allocated memory
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("The allocated memory contains: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Freeing allocated memory
    free(arr);
    printf("Contiguous memory deallocated.\n");
}

// Linked Allocation
void linked_allocation() {
    struct Node {
        int data;
        struct Node* next;
    };
    
    int n;
    printf("Enter the number of elements to allocate: ");
    scanf("%d", &n);
    
    struct Node* head = NULL;
    struct Node* temp = NULL;
    struct Node* current = NULL;
    
    for (int i = 0; i < n; i++) {
        temp = (struct Node*) malloc(sizeof(struct Node));
        if (temp == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
        printf("Enter element %d: ", i+1);
        scanf("%d", &temp->data);
        temp->next = NULL;
        
        if (head == NULL) {
            head = temp;
            current = head;
        } else {
            current->next = temp;
            current = temp;
        }
    }
    
    printf("Linked list created with elements: ");
    current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    
    // Freeing the memory
    current = head;
    struct Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    printf("Linked memory deallocated.\n");
}

// Indexed Allocation
void indexed_allocation() {
    int n;
    printf("Enter the number of elements to allocate: ");
    scanf("%d", &n);
    
    // Allocating index table
    int *indexTable = (int*) malloc(n * sizeof(int));
    if (indexTable == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Allocating the actual data blocks using indexed allocation
    int **dataBlocks = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dataBlocks[i] = (int*) malloc(sizeof(int)); // Each block will hold 1 integer
        if (dataBlocks[i] == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
    }
    
    // Input values
    for (int i = 0; i < n; i++) {
        printf("Enter element for block %d: ", i + 1);
        scanf("%d", dataBlocks[i]);
        indexTable[i] = i; // The index table points to the data blocks
    }
    
    // Display indexed allocation data
    printf("Indexed allocation data: \n");
    for (int i = 0; i < n; i++) {
        printf("Index %d -> Data: %d\n", indexTable[i], *dataBlocks[i]);
    }
    
    // Freeing the memory
    for (int i = 0; i < n; i++) {
        free(dataBlocks[i]);
    }
    free(dataBlocks);
    free(indexTable);
    printf("Indexed memory deallocated.\n");
}

int main() {
    int choice;
    
    printf("Choose the memory allocation strategy:\n");
    printf("1. Contiguous Allocation\n");
    printf("2. Linked Allocation\n");
    printf("3. Indexed Allocation\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            contiguous_allocation();
            break;
        case 2:
            linked_allocation();
            break;
        case 3:
            indexed_allocation();
            break;
        default:
            printf("Invalid choice!\n");
    }
    
    return 0;
}