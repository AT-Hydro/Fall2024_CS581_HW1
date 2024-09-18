/*
Name:  Ali Takallou
Email: atakallou@crimson.ua.edu
Course Section: CS 581
Homework #:1
Instructions to compile the program: icx -O3 -o HW1 HW1.c
Instructions to run the program: HW1 <number of Rows> <number of Columns> <maxmium number of Generations>
*/




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>



// Function to generate the next generation of the game
void gen_game_life(int rows, int cols, int *flag ,int **matrix, int **next_gen_matrix) {
    *flag = 0;
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            
            int value = 0;
    
            value += matrix[i + 1][j - 1] + matrix[i - 1][j + 1] + matrix[i - 1][j - 1]
                          + matrix[i + 1][j + 1] + matrix[i][j - 1] + matrix[i][j + 1]
                          + matrix[i - 1][j] + matrix[i + 1][j];
            if (matrix[i][j] == 1) {
                if (value == 0 || value == 1) {
                    next_gen_matrix[i][j] = 0;
                    *flag = 1;
                } else if (value >= 4) {
                    next_gen_matrix[i][j] = 0;
                    *flag = 1;
                } else if (value == 2 || value == 3) {
                    next_gen_matrix[i][j] = 1;
                }
            } else {
                if (value == 3) {
                    next_gen_matrix[i][j] = 1;
                    *flag = 1;
                }
            }
        }
    }
}



// Function to initialize the matrix with random values
void initialize_matrix(int rows, int cols, int **matrix) {
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            matrix[i][j] = rand() % 2;
        }
    }
}

// Function to print the matrix
void print_matrix(int rows, int cols, int **matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to dynamically allocate a 2D matrix
int **allocate_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

// Function to free a dynamically allocated matrix
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Main function
int main(int argc, char *argv[]) {
	
    // Check if exactly three arguments are passed (program name + 3 arguments)
    if (argc != 4) {
        printf("Usage: %s <rows> <cols> <n_generations>\n", argv[0]);
        return 1;  // Exit with error code
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int n_generations = atoi(argv[3]);
	// Adjust for border padding (for game logic)
    rows += 2;
    cols += 2;
    

    // Dynamically allocate memory for the matrices
    int **matrix = allocate_matrix(rows, cols);
    int **next_gen_matrix = allocate_matrix(rows, cols);

    // Initialize matrices to zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
            next_gen_matrix[i][j] = 0;
        }
    }

    // Initialize matrix with random values
    //srand(42);
    initialize_matrix(rows, cols, matrix);

    //printf("Initial Matrix:\n");
    //print_matrix(rows, cols, matrix); 
    // Get user input for maximum number of generations 


    clock_t start_time = clock();
    int flag = 0;
    for (int number = 1; number < n_generations + 1; number++) {
    
        gen_game_life(rows, cols, &flag, matrix, next_gen_matrix);

        // If no changes were made in the generation (flag is 0), end the game
        if (flag == 0) {
            printf("Game ended in generation %d (no changes) and the time taken is %f seconds\n", 
                number, (double)(clock() - start_time) / CLOCKS_PER_SEC);
            break;
        }

        // Copy next_gen_matrix to matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = next_gen_matrix[i][j];
            }
        }

        if (number == n_generations) {
            printf("Maximum generation reached and the time taken is %f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
        }
    }

    // Free dynamically allocated memory
    free_matrix(matrix, rows);
    free_matrix(next_gen_matrix, rows);

    return 0;
}
