#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void hello(char *name)
{
    printf("Hello, %s\n", name);
    printf("%c\n", *name);
    while (*name != '\0')
    {
        printf("%c", *name);
        name++;
    }
    printf("\n");
}
int *matrix_multiply(int *A, int *B, int *C, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i * N + j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
    return C;
}
int *matrix_add(int *A, int *B, int *C, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i * N + j] = A[i * N + j] + B[i * N + j];
        }
    }
    return C;
}

int *memc()
{
    int *mem = malloc(sizeof(int));
    printf("%p\n", &mem);
    return mem;
}
void freemem(int *mem)
{
    free(mem);
    printf("Freed %d", *mem);
}
void genRandomImage(int width, int height, const char* filename)
{
        // Seed the random number generator
    srand(time(0));

    // Allocate memory for the image
    unsigned char* image = (unsigned char*)malloc(3 * width * height);

    // Check if memory allocation was successful
    if (image == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Fill the image with random pixel values
    for (int i = 0; i < 3 * width * height; i++) {
        image[i] = rand() % 256; // Random value between 0 and 255
    }

    // Open the file for writing
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file for writing\n");
        free(image);
        return;
    }

    // Write the PPM header
    fprintf(file, "P6\n%d %d\n255\n", width, height);

    // Write the pixel data
    fwrite(image, 3, width * height, file);

    // Close the file
    fclose(file);

    // Free the allocated memory
    free(image);

    printf("Random image generated: %s\n", filename);
}

//Linked list
struct Node {
    int data;
    struct Node* next;
};

void insert_node(struct Node** head, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void delete_node(struct Node** head, int data) {
    struct Node* temp = *head, *prev;

    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void print_list(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
