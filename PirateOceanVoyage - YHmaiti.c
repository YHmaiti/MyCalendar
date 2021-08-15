// Yohan Hmaiti made this program

// This program is made to help the user and his crew make decisions related to his treasure
// search trip in addition to providing him with the multiple options and needs based on his choices
// and the situation of his crew, clipper, material and provisions

// Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants for Arrays
#define STRLENGTH 30
#define NUMCREW 5
#define NUMSUPPLIES 4

// Constants for Distances (measured in miles)
#define CANARY 1261
#define GRENADA 3110
#define FINAL 500
#define DISTANCE 4871

// Function Signatures - do not change these
void setup(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int *captaintype, int *funds, int *distanceperday);
int countcrew(int crewstatus[NUMCREW]);
void printstatus(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW]);
void getsupplies(char supplytypes[NUMSUPPLIES][STRLENGTH], int supplies[NUMSUPPLIES], int *funds);
void dailyreport(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int funds, int traveled);
void rest(int supplies[NUMSUPPLIES], char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int *days);
int fish();
int max(int a, int b);
int min(int a, int b);
void event(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int *days, int supplies[NUMSUPPLIES]);

//Main function - This is the final version of main.  Any changes you make while
//creating the functions should be removed prior to submission.
int main(void) {

    //crewnames and supplytypes are arrays of strings to store the names of the crew members
    //and the types of supplies that can be purchased and taken on the voyage
    char crewnames[NUMCREW][STRLENGTH];
    char supplytypes[NUMSUPPLIES][STRLENGTH] = {"Food", "Clothes", "Ship Parts", "Shovels"};

    //stop indicates whether or not the user would like to stop at a port
    //crewstatus indicates the status of each crew member, corresponding to the order of names
    //supplies has a total for each type of supply, corresponding to the order of supplies
    char stop;
    int crewstatus[NUMCREW], supplies[NUMSUPPLIES];

    //the distanceperday and funds depends on the captaintype the user selects
    //day is the current day, traveled is the total miles traveled, i is a loop counter
    //and action stores the intended action of the user for the day
    int distanceperday, captaintype, funds, traveled=0, day=1;
    int i, action;

    //seed the pseudorandom number generator
    srand(time(0));

    //initialize each variable with information from the user
    setup(crewnames, crewstatus, supplies, &captaintype, &funds, &distanceperday);

    //begin the game by purchasing initial supplies
    printf("\nBefore leaving Port Marin, you should purchase some supplies.\n");
    getsupplies(supplytypes, supplies, &funds);

    //continue the voyage until the ship reaches the intended destination
    //if all crew members perish, the journey cannot continui
    while (traveled < DISTANCE && countcrew(crewstatus) > 0) {

        printf("\n\n--It is day #%d.--\n", day);

        //check to see if the ship has reached the next port
        if (traveled >= (GRENADA+CANARY) && traveled < (GRENADA + CANARY + distanceperday)) {

            printf("You have arrived at Grenada, at the edge of the Carribbean Sea.\n");
            printf("Would you like to make port? (Y/N)\n");
            scanf(" %c", &stop);

            if (stop == 'Y' || stop == 'y')

                getsupplies(supplytypes, supplies, &funds);

            traveled = (GRENADA+CANARY) + distanceperday;

        }

        else if (traveled >= CANARY && traveled < (CANARY + distanceperday) ) {

            printf("You have arrived at the Canary Islands.\n");
            printf("Would you like to make port? (Y/N)\n");
            scanf(" %c", &stop);

            if (stop == 'Y' || stop == 'y')

                getsupplies(supplytypes, supplies, &funds);


            traveled = CANARY + distanceperday;

        }

        //if between destinations: print the daily report and process the user's action for the day
        else {

            dailyreport(crewnames, crewstatus, supplies, funds, traveled);

            printf("\nWhat would you like to do?\n");
            printf("1 - Fish\n");
            printf("2 - Rest\n");
            printf("3 - Continue\n");
            scanf("%d", &action);

            if (action == 1) {

                supplies[0] += fish();

            }

            else if (action == 2) {

                day--;
                rest(supplies, crewnames, crewstatus, &day);

            }

            else {

                traveled += distanceperday;
                supplies[0] = max(supplies[0] - countcrew(crewstatus) * 2, 0);
                event(crewnames, crewstatus, &day, supplies);

            }

        }

        day++;

    }

    printf("\n\n");

    //The final printout changes based on which condition broke the while loop
    if (countcrew(crewstatus) == 0) {

        printf("Your crew has perished in the search for treasure. :(\n");

        printstatus(crewnames, crewstatus);

    }

    else {

        printf("Your crew has made it safely to the island.\n");

        printstatus(crewnames, crewstatus);

        if (supplies[3] >= countcrew(crewstatus))

            printf("You have enough shovels to dig up the treasure!\n");

        else

            printf("Unfortunately, you will not be able to dig up the treasure.\n");

    }

    return 0;

}

// Pre-conditions:  none
// Post-conditions: each input parameter should be assigned an initial value
void setup(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int *captaintype, int *funds, int *distanceperday) {

    // i is a counter
    int i;

    // Print the multiple captain type options for the user to chose from as a trip start up
    printf("You may now take your ship and crew from Port Marin, Spain to the hidden\n");
    printf("island in the Caribbean on the old pirate's map.\n\n");
    printf("How will you travel?\n");
    printf("1. - As a merchant\n");
    printf("2. - As a privateer\n");
    printf("3. - As a pirate\n");

    // Prompt the user for the captain type choice
    scanf("%d", captaintype);

    // if statement used in case the user chooses the merchant option
    if (*captaintype == 1){

        printf("As a merchant, you begin your trip with 1000 gold pieces.\n");
        printf("You will be sailing your clipper, with an average speed of 80 miles per day.\n");

        // Set the distance that can be travelled daily to 80
        *distanceperday = 80;

        // Set the funds available to 1000
        *funds = 1000;

    }

    // else if statement used in case the user chooses the privateer option
    else if (*captaintype == 2){

        printf("As a privateer, you begin your trip with 900 gold pieces.\n");
        printf("You will be sailing your clipper, with an average speed of 90 miles per day.\n");

        // Set the distance that can be travelled daily to 90
        *distanceperday = 90;

        // Set the funds available to 900
        *funds = 900;

    }

    // else if statement used in case the user chooses the pirate option
    else if (*captaintype == 3){

        printf("As a pirate, you begin your trip with 800 gold pieces.\n");
        printf("You will be sailing your clipper, with an average speed of 100 miles per day.\n");

        // Set the distance that can be travelled daily to 100
        *distanceperday = 100;

        // Set the available funds to 800
        *funds = 800;


    }

    // Prompt the user for his name
    // and store it in the first position
    printf("\nWhat is your name, Captain?\n");
    scanf("%s", crewnames[0]);

    // Ask the user for the names of his crew-members
    printf("Who are the other members of your crew?\n");

    // for loop used to store the names of the rest of the crew
    for (i = 1; i < NUMCREW; i++){

        printf("%d:", i);
        scanf("%s", crewnames[i]);

    }

    // for loop used to set all the supplies quantity to 0
    for (i = 0; i < NUMSUPPLIES; i++)

        supplies[i] = 0;

    // for loop used to said the health status of each member
    // to healthy
    for (i = 0; i < NUMCREW; i++)

        crewstatus[i] = 2;

    return;

}

// Pre-conditions:  crewstatus is an array of numerical indicators for the status of each crew member
//                  0 - deceased, 1 - ill, 2 - healthy
// Post-conditions: returns the number of crew members that are alive
int countcrew(int crewstatus[NUMCREW]) {

    // alive represents the number of crew-members not dead
    int alive = 0;

    // i is a counter
    int i;

    // for loop used to count the number of members alive
    for (i = 0; i < NUMCREW; i++){

        // if statement used to count alive members by excluding the dead cases
        if (crewstatus[i] != 0)

            alive++;

    }

    // return the number of alive members
    return alive;

}

// Pre-conditions:  crew names is an array of strings for the crew members
//                  crewstatus is an array of numerical indicators for the status of each crew member
//                  0 - deceased, 1 - ill, 2 - healthy
// Post-conditions: none
void printstatus(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW]) {

    // status[3][STRLENGTH] is an array of the multiple health statuses possible
    char status[3][STRLENGTH] = {"Deceased", "Ill", "Healthy"};

    // i is a counter
    int i;

    // for loop used to determine each member's health status
    for (i = 0; i < NUMCREW; i++){

        // if statement of when the member is deceased
        if (crewstatus[i] == 0)

            printf("%s is: %s\n", crewnames[i], status[0]);

        // else if statement of when the member is ill
        else if (crewstatus[i] == 1)

            printf("%s is: %s\n", crewnames[i], status[1]);

        // else if statement of when the member is healthy
        else if (crewstatus[i] == 2)

            printf("%s is: %s\n", crewnames[i], status[2]);

    }

    return;

}

// Pre-conditions:  supplytypes in an array of strings and gives the name of each supply type
//                  supplies is an array of integers representing how many of each type the crew has
//                  funds represents how many gold pieces the crew has to spend
// Post-conditions: the user may choose to buy supplies: incrementing values in supplies and
//                  decrementing funds
void getsupplies(char supplytypes[NUMSUPPLIES][STRLENGTH], int supplies[NUMSUPPLIES], int *funds) {

    // supplycosts[NUMSUPPLIES] is an array of the cost of each supply
    int supplycosts[NUMSUPPLIES] = {1, 2, 20, 10};

    // quantity is the the amount of a designated supply the user wants
    int quantity = 0;

    // action is number the user chooses from the option menu
    int action = 0;

    // i is a counter
    int i;

    // result is the amount of funds after purchase
    int result = 0;

    // while loop used when the user chooses to shop
    // and did not yet leave the store
    while (action != 5){

        // print how many funds the user has
        printf("\nYou have %d gold pieces\n", *funds);

        printf("Available supplies:\n");

        // for loop used to display each supply option and its cost
        for (i = 0; i < NUMSUPPLIES; i ++){

            printf("%d. %s - %d gold pieces\n", i + 1, supplytypes[i], supplycosts[i]);

        }

        // print the option of leaving the store
        printf("5. Leave Store\n");

        // prompt the user for the option he wants
        scanf("%d",&action);

        // if statement used when the user wants food
        if (action == 1){

            supplycosts[action - 1] = 1;

            printf("How many pounds of food do you want to buy?\n");

        }

        // else if statement used when the user wants clothes
        else if (action == 2){

            supplycosts[action - 1] = 2;
            printf("How many sets of clothes do you want to buy?\n");

        }

        // else if statement used when the user wants ship parts
        else if (action == 3){

            supplycosts[action - 1] = 20;

            printf("How many extra ship parts do you want to buy?\n");

        }

        // else if statement used when the user wants shovels
        else if (action == 4){

            supplycosts[action - 1] = 10;

            printf("How many shovels do you want to buy?\n");

        }

        // else if statement used when the user wants to quit
        else if (action == 5){

            break;

        }

        // else statement used if the option  is not available
        else

            printf("Sorry!the choice you made is not available.\n");


        // scan the user's desired quantity for the supply
        scanf(" %d",&quantity);

        // equation that calculates the remaining funds
        result = *funds - (supplycosts[action - 1] * quantity);

        // if statement used if the funds are not enough depending
        // on the supply and quantity chosen
        if (result < 0){

            if (action == 1)

                printf("sorry, you cannot afford that much food.\n");

            else if (action == 2)

                printf("Sorry, you cannot afford that many sets of clothes.\n");

            else if (action == 3)

                printf("sorry, you cannot afford that many ship parts\n");

            else if (action == 4)

                printf("Sorry, you cannot afford that many shovels\n");

            continue;

        }

        // else statement used to update the funds and supply quantity
        // at each time a purchase was successfully done
        else {

            *funds = result;

            supplies[action-1] += quantity;

            continue ;

        }

        // set action to 0 after each finished attempt
        action = 0;

    }

}

// Pre-conditions:  crew names is an array of strings for the crew members
//                  crewstatus is an array of numerical indicators for the status of each crew member
//                  0 - deceased, 1 - ill, 2 - healthy
//                  supplies is an array of integers representing how many of each type the crew has
//                  funds represents how many gold pieces the crew has to spend
//                  traveled represents the total number of miles the ship has traveled from the beginning
// Post-conditions: none
void dailyreport(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int funds, int traveled) {

    // print statement used to update the user of the miles travelled
    printf("You have travelled %d miles\n", traveled);

    // function call to print the health status reports
    printstatus(crewnames, crewstatus);

    printf("\n\n");

    // if statement used to set the food supply to 0 when they run out of it
    if (supplies[0] < 0)

        supplies[0] = 0;

    // Update the user of the funds and food still available
    printf("You have %d gold pieces\n", funds);
    printf("You have %d pounds of food\n", supplies[0]);

    // if statement used to update the remaining miles to reach the CANARY
    if (traveled < CANARY && traveled >= 0)

        printf("You are %d miles away from your next destination\n\n", (CANARY - traveled));

    // else if statement used to determine the remaining miles to reach GRENADA
    else if (traveled >= CANARY && traveled < GRENADA)

        printf("You are %d miles away from your next destination\n\n", (GRENADA - traveled));

    // else if statement used to determine the remaining miles to reach the final destination
    else if(traveled >= GRENADA && traveled < DISTANCE)

        printf("You are %d miles away from your next destination\n\n", (DISTANCE - traveled));

}

// Pre-conditions:  a and b are both integers
// Post-conditions: the larger value will be returned
int max(int a, int b) {

    // if statement used when a superior to b
    // or a is equal to b
    if (a >= b)

        // return the highest value a
        return a;

    // if statement used when b superior to a
    if (b > a)

        // return the highest value b
        return b;

}

// Pre-conditions:  a and b are both integers
// Post-conditions: the smaller value will be returned
int min(int a, int b) {

    // if statement used when a inferior to b
    // or a is equal to b
    if (a <= b)

        // return the smallest value a
        return a;

    // if statement used when b is inferior to a
    if (b < a)

        // return the smallest value b
        return b;

}

// Pre-conditions:  supplies is an array of integers representing how many of each type the crew has
//                  crew names is an array of strings for the crew members
//                  crewstatus is an array of numerical indicators for the status of each crew member
//                  0 - deceased, 1 - ill, 2 - healthy
//                  days represents the current day
// Post-conditions: the user will select a number of days to rest for. update days to reflect this number
//                  there is a small chance an ill crew member will recover during rest days
void rest(int supplies[NUMSUPPLIES], char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int *days) {

    // firstrand is a randomly generated number that represents a
    // health state either deceased or ill
    int firstrand = rand() % 2;

    // secondrand is a randomly generated number that represents
    // a number of a crew member
    int secondrand = rand() % 5;

    // Prompt the user for the number of rest days
    printf("How many days would you like to rest for?\n\n");
    scanf("%d", days);

    // Equation used to subtract the number of food pounds consumed
    // during each rest day
    supplies[0] -= (*days * 2 * NUMCREW);

    // if statement used to change the health status of an ill
    // member to healthy
    if (firstrand == 1 && crewstatus[secondrand] == 1)

        crewstatus[secondrand] == 2;

    return;

}

// Pre-conditions:  none
// Post-conditions: returns the number of pounds of fish gained by the ship
int fish() {

    // num is a randomly generated number between 0 and 3
    int num = rand() % 4;

    // if statement used to determine the amount of fish captured
    // num * 50 is represents the pounds of fish caught
    printf("Your crew lowers the nets and pulls up %d pounds of fish.", num * 50 );

    // return the value of pounds of fish pulled
    return num * 50;

}

// Pre-conditions:  crew names is an array of strings for the crew members
//                  crewstatus is an array of numerical indicators for the status of each crew member
//                  0 - deceased, 1 - ill, 2 - healthy
//                  days represents the current day
//                  supplies is an array of integers representing how many of each type the crew has
// Post-conditions: the status of a crew member or supplies may be affected by a random event,
//                  some events cause the ship to be delayed a certain number of days
void event(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int *days, int supplies[NUMSUPPLIES]) {

    // rand_event_num is a random event number generated
    int rand_event_num = rand() % 10;

    // gained_ship_parts is a random number of ship parts gained
    int gained_ship_parts = (rand() % 4) + 1;

    // gained_pounds_food is a random number of food pounds gained
    int gained_pounds_food = (rand() % 51) + 10;

    // pounds_food_lost is a random number of food pounds lost
    int pounds_food_lost = (rand() % 51) + 5;

    // rand_num_member is a random number of a random crew member
    int rand_num_member = (rand() % 5);

    // addition represents the number of days spent in each event
    int addition;

    // if statement used to set the food supply number to 0
    // at each time a day passes without the crew having food
    if (supplies[0] <= 0){

        supplies[0] = 0;
        printf("You have no food!\n");

        // increment the event number by 2 at each time
        // when there is no food
        rand_event_num += 2;

    }

    // else if statement used to set the event number to 9
    // if the event number is over 9
    else if (rand_event_num > 9){

        rand_event_num = 9;

    }

    // else if statement used when the event number is 3
    // update the supply number 2 at each time the event happens
    else if (rand_event_num == 3){

        supplies[2] += gained_ship_parts;

        // Update the trip day count
        *days = *days + 1;

        // Event 3 takes one day
        addition = 1;

        // Print the event scenario
        printf("Another pirate ship pulls alongside and attacks!\n");
        printf("You fend them off and take %d extra ship parts.\n", gained_ship_parts);
        printf("You spend the day recovering.\n\n");

    }

    // else if statement used when the event number is 4
    // Update the supply number 0 at each time the event occurs
    else if (rand_event_num == 4){

        supplies[0] += gained_pounds_food;

        // Update the trip day count
        *days++;

        // event 4 takes one day
        addition = 1;

        // Print the event scenario
        printf("Another pirate ship pulls alongside and attacks!\n");
        printf("You fend them off and take %d pounds of their food.",gained_pounds_food);
        printf("You spend the day recovering.\n\n");

    }

    // else if statement used when the event number is 5
    // Update the supply number 0 at each time the event occurs
    else if (rand_event_num == 5){

        supplies[0] -= pounds_food_lost;

        // Update the trip day count
        *days++;

        // Event 5 takes one day
        addition = 1;

        // Print the event scenario
        printf("Another pirate ship pulls alongside and attacks!\n");
        printf("They took %d pounds of food and you spend the day recovering.", pounds_food_lost);

    }

    // else if statement used when the event number is 6
    else if (rand_event_num == 6){

        // Print the event scenario
        printf("\nFog surrounds your ship.  Drop anchor for one day.\n");

        // Update the trip day count
        *days++;

        // Event 6 takes 1 day
        addition = 1;

    }

    // else if statement used when the event number is 7
    else if (rand_event_num == 7){

        // Print the event scenario
        printf("\nAn ocean storm batters your ship.  Drop anchor for two days.\n");

        // Update the trip day count
        *days = *days + 2;

        // Event 7 takes 2 days
        addition = 2;
    }

    // else if statement used when the event number is 8
    else if (rand_event_num == 8){

        // if statement used when the crew has ship parts
        if (supplies[2] > 0){

            // Print the event scenario
            printf("\nA part of your ship has broken!You replace the broken part. It takes one day.\n\n");

            // Update the trip day count
            *days++;

            // Event 8 in this case takes 1 day
            addition = 1;

        }

        // else if statement  used when the crew has 0 ship parts
        else if (supplies[2] == 0){

            printf("A part of your ship has broken!\n");
            printf("You have no replacement parts.  It takes three days to repair.");

            // Update the trip day count
            *days = *days + 3;

            // Event 8 in this case takes 3 days
            addition = 3;

        }

    }

    // else if statement used when the event number is 9
    else if (rand_event_num == 9){

        // if statement used when the crewstatus of the random member chosen
        // is healthy to change it to ill
        if (crewstatus[rand_num_member] == 2){

            crewstatus[rand_num_member] = 1;

            // Print the change of health status
            printf("\n%s has fallen ill.\n", crewnames[rand_num_member]);

        }

        // else if statement used when the crewstatus of the random member
        // chosen is ill to change it to deceased
        else if (crewstatus[rand_num_member] == 1){

            crewstatus[rand_num_member] = 0;

            // Print the change of health status
            printf("\n%s has died.\n", crewnames[rand_num_member]);

        }

    }

    // else if statement used when the event number generated is
    // either 0, 1 or 2
    else if (rand_event_num >=0 && rand_event_num <= 2)

        // The event day count is 0 in this case
        addition = 0;

    // Equation that updates the  quantity of food supplies
    // at each time an event occurs
    supplies[0] -= (addition * 2 * NUMCREW);

    return;

}

