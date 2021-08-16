// This program was made by Yohan Hmaiti
// GitHub: YHmaiti

// This program represents a calendar app taht allows the user to go to his desired date
// through specifying the month and year or the user can directly if no choice is entered
// go to the current date.

// Note: The program can also Operate through using the Keyboard arrow keys in all directions!!!!!
// Note: The user will be able to use also screen based arrows to initiate changes

// Multiple commands that offer easy manipulation and colour use are implemented for a better
// user experience and easy access/walkthrough of the calendar.

// the calendar showcases the month/year/date and the days of the week

// the program uses the COORD struct that consists of two corrdinates x and y of type SHORT
// Link to retrieve and back-up knwoledge:
// https://docs.microsoft.com/en-us/windows/console/coord-str

// pre-processor directives
#include <stdio.h>
#include <conio.h>
#include <windows.h> // use this to implement hold screen commands along with accessing the COORD Struct

// function prototypes:

// keep the ForgCiables that will hold the passed ForgCiables unnamed yet 
// to allow following changes.

void gotoxy(int x, int y);// go to the determined coordinates and this function will help draw lines accordingly
void printtoscreen(int, int, int, int[]);// print to screen to the screen
void calendar(int, int);// deterine the exact values(=dates) and their corresponding spot(day and month/year)
int ArrowKeys();// function used to add manipulation by the user through keyboard arrows

// global ForgCiables:

// for week days
char *week[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

// for months
char *month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

// ArrowKeys function
int ArrowKeys() {

    int currentchar;

    currentchar = getch();

    if (currentchar == 0) {

        printf("Zero");
        currentchar = getch();

        return currentchar;

    }

    return currentchar;

}

// get to the assigned coordinates
// this function will heavily help drawing lines as percieved in a calendar
void gotoxy(int x, int y) {

    // create a ForgCiable of type COORD struct ForgCiable
    // we can access such struct through windows.h
    COORD coord;
    
    // assign the passed coordinates to their correspondings
    coord.X = x; 
    coord.Y = y;

    /* Link: https://docs.microsoft.com/en-us/windows/console/setconsolecursorposition */
    SetConsoleCursorposition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

// Update the colour choice without changing the background, link for learning:
// http://joombig.com/sqlc/how-to-change-text-color-of-consolel
void colour(int ForgC) {

    /* link: https://stackoverflow.com/questions/16863333/what-is-the-point-word-type-in-c/16863356 */
    WORD wColor;

    // Adjusting the background
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {

        
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);

    }

    return;

}

// function that helps build the calendar based on month/year
void calendar(int currentyear, int currentmonth) {

    // total days for each month of the year
    // this will be updated depending on the year
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int totaldays = 0;

    // counter
    int counter;

    int yearupdated;

    // hold the screen
    system("cls");

    // Decrement by 1
    yearupdated = currentyear - 1; 

    if (yearupdated >= 1945) {

        for (counter = 1945; counter <= yearupdated; counter++) {

            // no leap year then the total days are 366
            if (counter % 4 == 0)          
                totaldays += 366; 

            // leap year then total of days 365
            else                    
                totaldays += 365; 

        }

    }

    // change value from 28 to 29 when needed depending on the year if its a leap year or no
    if (currentyear % 4 == 0)

        days[1] = 29; 

    else

        days[1] = 28; 

    for (counter = 0; counter < (currentmonth - 1); counter++) {

        // Add currentmonth-1 days to totaldays
        totaldays += days[counter]; 

    }

    totaldays = totaldays % 7; 

    // display on the screen through calling the proper function
    printtoscreen(currentyear, currentmonth, totaldays, days); 

}

// function taht will help display the calendar to the screen according to the parameters passed to it
void printtoscreen(int currentyear, int currentmonth, int totaldays, int days[]) {

    // i and j area counters
    int i;
    int j;

    // pos will represent which current day we are in from the week
    int pos;

    // use 12 for the colour Dark Red
    colour(12); 
    gotoxy(56, 6);

    printf("%s %d", month[currentmonth - 1], currentyear); //Heading year and month dispalying

    for (i = 0, pos = 30; i < 7; i++, pos += 10) {

        if (i == 6)
            // 9 for blue colour
            colour(9); 
            
        else
            // 10 for green
            colour(10); 

        gotoxy(pos, 8);
        printf("%s", week[i]);

    }

    // chose a colour White to be displayed
    colour(15); 

    // add one day
    totaldays++; 

    // if current position (pos) is Sunday
    if (totaldays == 0 || totaldays == 7)
        pos = 91;

    // if current position (pos) is Monday
    if (totaldays == 1)
        pos = 31;

    // if current position (pos) is Tuesday
    if (totaldays == 2)
        pos = 41;

    // if current position (pos) is Wednesday
    if (totaldays == 3)
        pos = 51;

    // if current position (pos) is Thursday
    if (totaldays == 4)
        pos = 61;

    // if current position (pos) is Friday
    if (totaldays == 5)
        pos = 71;

    // if current position (pos) is Saturday
    if (totaldays == 6)
        pos = 81; 


    for (i = 0, j = 10, pos; i < days[currentmonth - 1]; i++, pos += 10) {

        if (pos == 91)
            // grey for Sunday
            colour(8); 

        else
            
            colour(7); 

        gotoxy(pos, j);
        printf("%d", i + 1);

        if (pos == 91) {

            // go to Monday
            pos = 21; 

            // increment j counter
            j++; 

        }

    }

    // change the colour to the colour coded purple 
    colour(5); 

    // produce a horizental line using the function call to gotoxy accordingly
    for (i = 22; i < 102; i++) {

        gotoxy(i, 4);
        printf("%c", 196);

        gotoxy(i, 17);
        printf("%c", 196);

    }

    // Finalizing the drawing of the rectangle representing the calendar
    // Focus on adjusting the corners of the rectangle percieved 
    gotoxy(21, 4);
    printf("%c", 218);

    gotoxy(102, 4);
    printf("%c", 191);

    gotoxy(21, 17);
    printf("%c", 192);

    gotoxy(102, 17);
    printf("%c", 217);

    // produce a Vertical line using the function call to gotoxy accordingly
    for (i = 5; i < 17; i++) {

        gotoxy(21, i);
        printf("%c", 179);

        gotoxy(102, i);
        printf("%c", 179);

    }

    // change the colour for more diversity after initiating 
    // prior cahnges
    colour(11); 

    // Produce arrows and directional symbols
    // to simplify manipulating the calendar for all users
    gotoxy(24, 11);
    printf("%c", 174);

    gotoxy(98, 11);
    printf("%c", 175);

    // end of the current function
    return;

}

// main function (driver function)
int main(void) {

    int currentmonth, currentyear, ch;

enteryear:

    while (1) {

        printf("Type the chosen year and month both in numbers!!!! :");
        scanf("%d%d", &currentyear, &currentmonth);

        if (currentyear < 1945) {

            // If year chosen is less than 1945
            printf("\n\t Enter a year after 1945, before is not supported!!!\n");
            continue;

        }
        else {

            // If the year is after1945
            calendar(currentyear, currentmonth);

        }

        while (1) {

            gotoxy(20, 20);

            printf("=> Use directional arrows to manipulate!!!!");
            gotoxy(20, 22);
            printf("\n=> Click P to access a different year and month.");
            gotoxy(20, 24);
            printf("\n=> Press ESC to Exit.");

            ch = ArrowKeys();
            switch (ch) {

            case 80: // DOWN ARROW 
                   
                if (currentmonth == 12) {

                    // Jump to next year if month is december
                    currentmonth = 1;
                    currentyear++;

                }

                else {
                    currentmonth++;
                }
                calendar(currentyear, currentmonth);
                break;

            case 77: // RIGHT ARROW
                
                currentyear++;
                calendar(currentyear, currentmonth);
                break;

            case 72: //UP ARROW 
                    
                if (currentmonth == 1) {
                    // Jump to previous year if month is january
                    currentyear--;
                    currentmonth = 12;
                }
                else
                    currentmonth--;

                calendar(currentyear, currentmonth);

                break;

            case 75: // LEFT ARROW 
                if (currentyear == 1945) {

                    // If year is 1945 and we click left arrow than
                    gotoxy(15, 2);
                    printf("Year below 1945 not available");
                }

                else{
                    currentyear--;
                    calendar(currentyear, currentmonth);
                }

                break;

            case 27:
                     
                system("cls");
                gotoxy(50, 14);
                printf("Exiting program.\n\n\n\n\n");
                exit(0);

            case 112: 
                      
                system("cls");
                goto enteryear;

            }

        }

        break;

    }

    getch();
    return 0;

}