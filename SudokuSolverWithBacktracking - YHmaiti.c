// This program was made by Yohan Hmaiti 
// on 06/23/2021
// GitHub: YHmaiti

// Sudoku Solver with choice of random grid or personalized one
// Uses backtracking algorithm
// The game has the option to showcase the sudoku rules in detail
// The game has also the option to show a brief definition and history of sudoku
// The game has the option to get learning links regarding multiple characteristics of sudoku
// ranging from its definition, history, improving skills of it and so forth and so on

// Functionalities:
// 1. see the definition and history of sudoku along with the links regarding sudoku's definition/history/learning/mastering
// 2. see the sudoku rules explained in detail and showcased in a clear manner
// 3. create a sudoku table randomly and have the user chose its level of difficulty and to either solve it himself, see the solution
//    directly or exit back to the main menu
// 4. the player enters his own sudoku table and solves it, the answer gets checked and the table entered if its valid too
//    the user has also the option to go back to the main menu after that
// 5. exit option of the program that leads t final messages to the user
// END of the program is a: message from creator

// Pre-processor directives
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Using the system header file stdbool.h allows you to use bool as a Boolean data type. true evaluates to 1 and false evaluates to 0.
// bool x = true; <=> x = 1; same thing for equals false except then we have a 0

// Function prototypes:
int valid();
void definition();
void SudokuRules();
void Generate(); 
void CreateRandom(int oneorzero); 
void transfer_Row(int number1,int number2);
void transfer_Column(int number1,int number2);
void transfer_GroupRows(int numm1,int numm2); 
void transfer_GroupColumns(int numm1,int numm2); 
void Empty_Table(int cst);
void push(int coordinate1, int coordinate2, int coordinate3);
struct Stack *pop();
void sudokualgorithm(int p[9][9]); 
int Safe(int a[9][9],int row, int col, int position);
void display(int table[9][9]);
void transfer_array();
int table[9][9];
int array[9][9];
int constant = 0;
int num = 1;

// stack struct
struct Stack {

    struct Stack *prev;
    struct Stack *next;

    // elements for each entered number to be placed
    int row;
    int column;

    // number reresents the actual value of the number
    int number;

};

// create an initial pointer to the top of the stack initially set to NULL
// as the stack is empty
struct Stack *top = NULL;

void definition() {

    printf("\nSudoku is a logic-based, combinatorial number-placement puzzle. In classic sudoku, the objective is to fill a 9x9 grid with digits");
    printf("\nso that each column, each row, and each of the nine 3x3 subgrids that compose the grid (also called boxes, blocks, or regions) contains all");
    printf("\nof the digits from 1 to 9. The puzzle setter provides a partially completed grid, which for a well-posed puzzle has a single solution.\n\n");

    printf("French newspapers featured variations of the Sudoku puzzles in the 19th century, and the puzzle has appeared since 1979 in puzzle books under the name\n");
    printf("Number Place. However, the modern Sudoku only began to gain widespread popularity in 1986 when it was published by the Japanese puzzle company Nikoli \nunder the");
    printf("name Sudoku, meaning single number. It first appeared in a U.S. newspaper, and then The Times (London), in 2004, thanks to the efforts of\nWayne Gould, who");
    printf("devised a computer program to rapidly produce unique puzzles.\n\n");

    printf("Links for additional information:\n");
    printf("\t=> http://www.sudoku-space.com/sudoku.php \n");
    printf("\t=> https://www.learn-sudoku.com/what-is-sudoku.html \n");
    printf("\t=> https://en.wikipedia.org/wiki/Sudoku \n");
    printf("\t=> https://brilliant.org/wiki/sudoku/ \n\n");

}

void SudokuRules() {

    printf("\nRule 1 :\n\t- A traditional sudoku puzzle has 9 rows and 9 columns.\n\t- Each row needs to have numbers from 1 to 9!");
    printf("\nRule 2 :\n\t- Rows cannot contain duplicate numbers! No rows should be similar.");
    printf("\nRule 3 :\n\t- Columns must contain numbers from 1 to 9 only!\n\t- Columns cannot contain duplicate numbers! No columns should be simlar");
    printf("\nRULE 4 :\n\t- The region represents a 3x3 box. 9 regions exist in the traditional sudoku puzzle.\n\t- Each region must only contain numbers from 1 to 9!");
    printf("\nRule 5 :\n\t- Each region is different from another.\n\t- Every region is unique and doesn't contain duplcates.\n\n\n");

}

void display(int table[9][9]) {

    // i and j are counters
    int i = 0;
    int j = 0;

    // for loops used to display the table
    for (i = 0; i < 9; i++) {

        printf("*************************************\n");

        for (j = 0; j < 9; j++) {

            // if statement used to print the last element with a closing band
            if(j == 8)

                printf("| %d |", table[i][j]);

            else

                printf("| %d ", table[i][j]);

        }

        printf("\n");

        // if statement used when we reach the end to end the table
        if (i == 8) {

            printf("*************************************\n\n");

        }

    }

}

// transfer the sae content in table array to arr1 array
void transfer_array() {

    int i = 0 , j = 0;

    for (i = 0; i < 9; i++) {

        for (j = 0; j < 9; j++) {

            array[i][j] = table[i][j];

        }

    }

}

// check the user's input
int valid() {

    int i = 0, j = 0;

    while(i < 9) {

        for (j = 0; j < 9; j++) {

            if(array[i][j] != table[i][j])

                return 0;

        }

        i++;

    }

    return 1;

}

// execute popping operation from the stack
// return the top of the stack
struct Stack *pop() {

    if (top == NULL)

        return NULL;

    else {

        // create a temporary pointer to oint to the current top
        struct Stack *t = top;

        // update top of the stack
        top = top->prev;

        // return the stored top
        return t;

    }

}

// check if it is safe to insert the number of choice in the chosen position
int Safe(int a[9][9],int row, int col, int position) {

    int i = 0, j = 0;

    // check the row
    for (i = 0; i < 9; i++) {

        if (a[row][i] == position) {

            return 0;

        }

    }

    // check the column
    for (i = 0; i < 9; i++) {

        if (a[i][col] == position) {

            return 0;

        }

    }

    // check the region
    int row1 = row - row % 3;
    int col1 = col - col % 3;

    // for loop used to check if the move is valid based on the whole region
    // meaning based on the whole box the insertion will occur in
    for (i = row1; i < (row1 + 3); i++) {

        for (j = col1; j < (col1 + 3); j++) {

            if (a[i][j] == position) {

                return 0;

            }

        }

    }

    // return one if all the requirements were met successfully
    return 1;
}

// push onto the stack
// coordinate1 represents the row of the current number
// coordinate2 represents the column of the current number
// coordinate3 represents the value of the number itself
void push(int coordinate1, int coordinate2, int coordinate3) {

    // allocate memory for a new stack pointer temp
    struct Stack *temp = (struct Stack *)malloc(sizeof(struct Stack));

    temp->next = NULL;
    temp->prev = top;

    // update top
    top = temp;

    // update the content of temp based on the integers passed to the function
    temp->row = coordinate1;
    temp->column = coordinate2;
    temp->number = coordinate3;

}

// function to empty the table of the sudoku game
void Empty_Table(int cst) {

    while (cst > 0) {

        int box = rand() % ((9 * 9) + 1);

        int i = box / 9;
        int j = box % 9;

        if (j != 0)

            j = j-1;

        if (table[i][j] != 0) {

            table[i][j]=0;
            cst--;

        }

    }

}

// sudoku solving algorithm used with the help of global variable constant
// and the use of stack implement using Doubly LL
void sudokualgorithm(int p[9][9]) {

    int i = 0, j = 0, q = 0, k = 0;

    while (constant == 0) {

    for (i = 0; i < 9; i++) {

        for (j = 0; j < 9; j++) {

            if (p[i][j] == 0) {

                q = 202;

                int pos;

                for (pos = num; pos <= 9; pos++) {

                    if (Safe(table, i, j, pos) == 1) {

                        q = 10;

                        p[i][j] = pos;

                        push(i,j,pos);

                        num = 1;

                        break;

                    }
                }

                if (q != 10) {

                    struct Stack *temp = pop();

                    if (temp == NULL){

                        constant = 100;
                        printf("no");

                    }

                    else {

                        p[temp->row][temp->column] = 0;

                        num = temp->number + 1;
                    }

                    k = 1;

                    break;

                }

            }

            else if (i == 8 && j == 8 && q == 0) {

                constant = 200;

            }

        }

        if (k == 1){

            break;

        }

    }

    }

    return;

}

// Function taht generates a table
void Generate() {

  int counter1 = 1;
  int counter2 = 1;

  int i = 0, j = 0;

  for (i = 0; i < 9; i++) {

      counter1 = counter2;

      for (j = 0; j < 9; j++) {

          if (counter1 <= 9) {

              table[i][j] = counter1;
              counter1++;

          }

          else {

              counter1 = 1;
              table[i][j] = counter1;
              counter1++;

          }

      }

      counter2 = counter2 + 3;

      if (counter2 > 9) {

        counter2 = (counter2 % 9) + 1;

      }

    }

    return;

}

// Generate_Random generates randomn numbers according to sudou rules
// one or zeor will be passed successively in order to initiate a randomness
// based on the idea of interchanging the values between rows and columns
void CreateRandom(int oneorzero) {

  // i is a counter
  int i = 0;

  // low and up represent positioning
  int low = 0;
  int up = 2;

  // num1 and num2 are integers used to store the randomn numbers
  int num1, num2 ;

  // for loop used to generate the randomn numbers
  for (i = 1; i <= 3; i++) {

      // generate num1 accordingly
      num1 = (rand() % ((up - low) + 1)) + low;

      // generate num2 ina way that it is unique compared to num1
      // the while loop fulfills the sudoku rules as defined by the game rules
      while (num1 == num2) {

          num2 = (rand() % ((up - low) + 1)) + low;

      } //To ensure both the numbers aren't equal

      up += 3;
      low += 3;

      if (oneorzero == 1)

          transfer_Row(num1, num2);

      else if (oneorzero == 0)

          transfer_Column(num1, num2);

    }

    return;

}

// interchange columns within the same region/block
void transfer_Column(int number1,int number2) {

  // t is a temporary integer used to fascilate the interchange of the numbers within
  // the columns passed to the function(number1 and number2)
  int t;

  // i is a counter
  int i = 0;

  //  for loop used to run through the whole 9 numbers within the column chosen
  // the loop helps achieve the interchange
  for (i = 0; i < 9; i++) {

    t = table[i][number1];
    table[i][number1] = table[i][number2];
    table[i][number2] = t;

  }

  return;

}

// interchange rows within the same region/block
void transfer_Row(int number1,int number2) {

  // i is a counter
  int i = 0;

  // t is a temporary integer used to fascilate the interchange of the numbers within
  // the rows passed to the function(number1 and number2)
  int t;

  // for loop used to run through the whole  9 numbers within the row chosen
  // the loop helps achiee the Interchange
  for (i = 0; i < 9; i++) {

    t = table[number1][i];
    table[number1][i] = table[number2][i];
    table[number2][i] = t;

  }

  return;

}

// interchange two columns
void transfer_GroupColumns(int numm1,int numm2) {

  // i and j are counters
  int i = 0, j = 0;

  // t is a variable set to help in the interchange
  int t;

  // for loops used to execute the interchange between the columns accordingly
  for (i = 1; i <= 3; i++) {

    for (j = 0; j < 9; j++) {

      t = table[j][numm1];
      table[j][numm1] = table[j][numm2];
      table[j][numm2] = t;

    }

    // increment both passed values to the function
    numm1++;
    numm2++;

  }

  return;

}

// interchange two rows
void transfer_GroupRows(int numm1,int numm2) {

  // i and j are counters
  int i,j;

  // tmp is a variable set to help in the interchange
  int tmp;

  // for loops used to execute the interchange between the rows accordingly
  for (i = 1; i <= 3; i++) {

    for (j = 0; j < 9; j++) {

      tmp = table[numm1][j];
      table[numm1][j] = table[numm2][j];
      table[numm2][j] = tmp;

    }

    // increment both passed values to the function
    numm1++;
    numm2++;

  }

  return;

}

int main(void) {

    // integer to be used to determine whenever the menu shall be printed
    // to ask the user again to selct a desired option
    int reprompting_cst = 0;

    // additional variables to be used as counters or to store scaned variables
    // and help manage switches and interchanges between rows and the columns
    // for example level stores the level of hardship of the game preferred by
    // the user
    // var1 and var2 will be used to help execute interchanges as designed through the
    // algorithm
    int i = 0, j = 0;
    int var1, var2;
    int level;

    printf("\nWelcome to this Awesome Sudoku Game! Read The options available below::::>\n\n");

    do {

      printf("Options:\n");
      printf("1-> Definition of Sudoku, overview of the game's history and useful learning links. [click (1)]\n");
      printf("2-> Rules of Sudoku and their explanation. [click (2)]\n");
      printf("3-> Create a Sudoku Game. [click(3)]\n");
      printf("4-> Solve a Sudoku (if you have one Sudoku table ready!). [click(4)]\n");
      printf("5-> Exit the Sudoku Game. [click (5)]\n\n");
      printf("=> Choose an option:");

      // choice will store the chosen option by the user
      int choice;
      scanf("%d", &choice);

      // switch statements based on the choice
      switch (choice) {

          case 1:
            definition();
            break;

          case 2:
            SudokuRules();
            break;

          case 3:
            printf("\nGreat! we will generate a sudoku puzzle based on your desired difficulty:\n1. Easy \n2. Intermediate\n3. Hard\n");
            int lvl;

            printf("\nEnter your choice:");
            scanf("%d",&lvl);

            // create a sudoku puzzle
            Generate();

            // seed the random number generator
            srand(time(0));

            CreateRandom(1);

            CreateRandom(0);

            int interchange_values[] = {0, 3 ,6};

            for (i = 1; i <= 2; i++) {

                var1 = interchange_values[rand() % 3];
                var2 = interchange_values[rand() % 3];

                while(var1 == var2){

                    var1 = interchange_values[rand() % 3];

                }

                if (i == 1)

                    transfer_GroupRows(var1, var2);

                else

                    transfer_GroupColumns(var1, var2);

            }

          // copy the array
          transfer_array();

          // while loop used in case a wrong lvl value is entered
          while (lvl>3 || lvl<1) {

              printf("\n\nThe value entered is not valid, please chose from the given options: 1. Easy | 2. Medium | 3. Hard\n");
              printf("Enter the level desired:");
              scanf("%d", &lvl);

          }

          if (lvl == 1) {

              level = rand() % 6;
              level = level + 40;

          }

          else if (lvl == 2) {

              level = rand() % 6;
              level = level + 30;

          }

          else if (lvl == 3) {

              level = rand() % 6;
              level = level + 20;

          }

          //
          Empty_Table(level);

          printf("\n");

          //
          display(table);

          printf("\n1. Enter your work and check it.\n2. View the solution.\n3. Exit to general menu.\nEnter Option:");

          int choice2;
          scanf("%d", &choice2);

          printf("\n\n");

          if (choice2 == 1) {

              int i = 0, j = 0;

              for (i = 0; i < 9; i++) {

                  for (j = 0; j < 9; j++) {

                      scanf("%d", &table[i][j]);

                  }

              }

              if (valid() == 1)

                  printf("\n****Great job! your solution is validated correct!****\n");

              else

                  printf("Sorry, wrong answer!\n");

          }

          else if (choice2 == 2) {

              display(array);

          }

          // end case 3
          break;

          case 4:
              printf("\n\nImportant: \n=> type a 9*9 Sudoku in Matrix \n=> Each line needs to have 9 single space seperated numbers\n N.B: For any blank space enter '0'\n");

              // i and j are counters
              int i = 0, j = 0;

              for (i = 0; i < 9; i++) {

                  for (j = 0; j < 9; j++) {

                      scanf("%d", &array[i][j]);

                  }

              }

              sudokualgorithm(array);

              if (constant == 200)

                  display(array);

              else

                  printf("\nThe entered Sudoku cannot be solved, make sure to check the entered details and try again!\n\n");

              // end case 4
              break;

          // case 5 is the exit options
          // so we can change the reprompting_cst to any other value different
          // than 0 to terminate the while loop and exit the sudoku solver program
          case 5:
              reprompting_cst = 1;
              break;// end case 5

          // set a default print expression if the choice entered is invalid
          default:
              printf("\nThe choice entered is invalid, try again......\n");

        // end of the switch statements
        }

    // end of the while loop
    }while (reprompting_cst == 0);

    char enter;
    // Ownership
    printf("\n\n*******This program was made by Yohan Hmaiti!*******\n");
    printf("\n->I hope you had a great experience playing the game!\n\n");
    printf("Press Enter to close the program.........");
    scanf("%c",&enter);

    // end of the main function
    return 0;

}

// GitHub: YHmaiti
