// This program is written by: Yohan Hmaiti 
// GitHub: YHmaiti

// This program identifies if someone who is infected by COVID19 is at the location that the current user is at or
// wants to go to, and if so, what their rank is on the sorted list of infected people. If no one is infected at that
// location, it will be identified accordingly.

// an output file will be generated!!!! called out.txt

// pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// structure:  point
typedef struct point {

    // integer coordinate x
    int x;

    // integer coordinate y
    int y;

    // distance from a designated point after calculation
    int distance;

} point;

// Global Variables X and Y representing my coordinates of my current position
int X;
int Y;

// function prototypes
int compareTo(point *point1, point *point2);
void sort(point arraypts[], int lengtharr, int threshhold);
int determine_distance(point cur_point, point myposition);
point* ReadData(FILE *ifp, int num_points, int myx, int myy);
int binarySearch(point pts[], point current, int numberpts);
void insertionsort(point p[], int left, int right);
void merge(point arraypts[], int left, int mid, int right);
void mergesort(point points[], int left, int right, int threshhold);

// main function
int main(void) {

    // variable declaration

    // t represents the threshold used to determine the type of sorting
    // to be used
    int t;

    // num_points represents the number of points scanned equivalent to the number
    // of people that are infected
    int num_points;

    // search_points represents the number of points to search for
    int search_points;

    // i is a counter
    int i = 0;

    // j is a counter
    int j = 0;

    // create a pointer p of type struct point
    point *p;

    // open the file containing the data to be scanned in read mode
    FILE *ifp = fopen("Covid19CoordinatesSurroundingPeople.txt", "r");

    // open the file in write mode that will contain the needed output
    FILE *ofp = fopen("out.txt", "w");

    // Check if the file to be read was found and not NULL
    if (ifp != NULL) {

        // Scan the elements needed from the File and store them accordingly in
        // the order given by the assignment.
        fscanf(ifp,"%d",&X);
        fscanf(ifp,"%d",&Y);
        fscanf(ifp,"%d",&num_points);
        fscanf(ifp,"%d",&search_points);
        fscanf(ifp,"%d",&t);

        // call the function that will read the data from the file
        p = ReadData(ifp, num_points, X, Y);

        // Call the sort function to start the sorting process
        sort(p, num_points-1, t);

        // for loop used to print the data information accordingly to
        // the designated output file
        for (i = 0; i < num_points; i++) {

            fprintf(ofp,"%d %d\n", p[i].x, p[i].y);

        }

        // while loop used to search for the points through the file
        // representing search_points
        while (j < search_points) {

            // x and y are two integers that will tore the current
            // coordinates scanned from the file at each time the while loop
            // runs.
            // x for the x coordinates
            int x;

            // y for the y coordinates
            int y;

            // scan the file for the two coordinates of the current point to be searched
            fscanf(ifp,"%d %d", &x, &y);

            // create a variable of type structure point to hold the current scanned coordinates to be used
            point current_point;

            // fill the current_point elements
            current_point.x = x;
            current_point.y = y;

            // create a variable result that will store the returned value from the binary search function
            int result;

            // call the binary search function and store the returned integer value in result
            result = binarySearch(p, current_point, num_points - 1);

            // if statement used if the returned value from the binary search is superior or equal to 0
            if (result >= 0)

                fprintf(ofp,"%d %d found at rank %d\n", x, y,result + 1);

            // else statement used if the returned value from binary search is negative
            else

                fprintf(ofp,"%d %d not found\n", x, y);

            // increment j
            j++;

        }

        printf("out.txt file was generated successfully\n\n");

        // close the input file
        fclose(ifp);

        // close the output file
        fclose(ofp);

        // free the allocated memory for the array of type struct point
        // through the pointer p
        free(p);

    }

    // end of the main function
    return 0;
}

// Remaining functions:

// Pre-conditions: The function takes a file pointer ifp representing the input file
//                 num_points is the number of points scanned from the input file
//                 myx and myy represent the X and Y global variables accordingly
// Post-conditions: The function will return an array of points in which each index represents
//                  a point with an x, y coordinates and a distance calculated through the ue
//                  of determine_distance function
point* ReadData(FILE *ifp, int num_points, int myx, int myy) {

    // initialize a counter
    int counter = 0;

    // create a variable of type struct point to store the current coordinates set Global in the beginning
    // representing X and Y which represent my current location
    point myLocation = {myx, myy};

    // Allocate memory for an array of type struct point that will hold all the data
    // of the points accordingly from the input file passed to the function
    point *Arr_points = (point*)malloc(num_points * sizeof(point));

    // while loop used to store the data needed into the array allocated
    // of all the points which total is num_points
    // along with calculating their distance from my current location
    while (counter < num_points) {

        // scan from the input file the x and y coordinates and store them accordingly
        // in the array
        fscanf(ifp,"%d", &Arr_points[counter].x);
        fscanf(ifp,"%d", &Arr_points[counter].y);

        // store the distance of each point from my current location using the global coordinates X and Y
        // passed to the function and store the distance accordingly through the array after
        // calling the determine_distance function
        Arr_points[counter].distance = determine_distance(Arr_points[counter], myLocation);

        // increment the counter
        counter++;

    }

    // return the array after being filled accordingly
    return Arr_points;
}

// Pre-conditions: The function takes two points
//                 myposition is the point representing my current location
//                 cur_point is the point that we need to calculate the distance of it from myposition
// Post-conditions: The function returns an integer representing the distance calculated
int determine_distance(point cur_point, point myposition) {

    return sqrt(pow((cur_point.x - myposition.x), 2) + pow((cur_point.y - myposition.y), 2));

}

// Pre-conditions: The function takes a points array passed to it
//                 numberpts represents the number of points within the array passed
//                 current is the point currently passed to the function from main
// Post-conditions: The function returns mid if the search was successful and the point
//                  at the mid index is the same as the current point passed to the function
//                  The function returns a negative number if the binary search was not successful
int binarySearch(point pts[], point current, int numberpts) {

    // intialize two variables i and j that will be used within the binary search
    // i represents low in the standard binary search
    // j represents high in the standard binary search
    int i = 0;
    int j = numberpts;

    // mid is an integer that will store the value of the index of
    // the middle during the binary search
    int mid;

    // create a variable of type struct point that will store the
    // coordinated of my current location accordingly
    point myposition;
    myposition.x = X;
    myposition.y = Y;

    // Determine the distance of the current point passed from my position
    // through calling determine_distance function and store the value
    // in the distance section of the struct for current
    current.distance = determine_distance(current, myposition) ;

    // while loop used to do the search starting from the first element
    // until reaching the last point possible
    // i is the same as low represented in the course
    // j is the same as high represented in the course
    while (i <= j) {

        // calculating mid and updating it for each iteration
        mid = (i + j)/2;

        // if statement used if the value returned is equal to 0
        if (compareTo(&pts[mid], &current) == 0)

            // return the mid value determined
            return mid;

        // if statement used when the result is negative
        if (compareTo(&pts[mid], &current) <0)

            // update i
            i = mid + 1;

        // else if statement used if the value returned by compareTo is positive
        else if (compareTo(&pts[mid], &current) > 0)

            // update j
            j = mid - 1;

    }

    // return a negative number in case the search fails
    return -999;
}

// Pre-conditions: The functions takes two point addresses using two point pointers to
//                 the points to be compared: point 1 and point 2
// Post-conditions: The function returns 0 if the two locations pointed to are identical
//                  The function returns the result value calculated depending on the adequate
//                  comparison made through if statement, where we use to compare based on
//                  the first characteristics of the points that are not similar
int compareTo(point *point1, point *point2) {

    // if statement used to compare the distances of the two points passed
    // in the case if the distances are different we return the result of the
    // substraction
    if (point1->distance != point2->distance) {

        int result = point1->distance - point2->distance;

        return result;

    }

    // if statement used in the case where the points have the same distance
    // we compare the difference between the two x coordinates, if it they are
    // different we return the result of their substraction
    if (point1->x != point2->x) {

        int result2 =  point1->x - point2->x;

        return result2;

    }

    // if statement used in the case where both prior if statements did not work
    // we compare the y coordinates of both points, if they are different
    // return the result of their substraction
    if (point1->y != point2->y) {

        int result3 = point1->y - point2->y;

        return result3;

    }

    // return 0 if none of the prior if statements worked
    // meaning the two points have the same positioning in terms
    // of x, y and distance
    return 0;
}

// Pre-conditions: The function takes three integers and an array of type point passed to it
//                 left represents the index of the first point (low)
//                 right represents the index of the last point(high)
//                 mid represents the index of the middle of the array
// Post-conditions: Two arrays are leftarray and rightarray are merged accordingly
//                  The merge will lead to obtaining a sorted array arraypts
void merge(point arraypts[], int left, int mid, int right) {

    // i, j and k are counters
    int i = 0;
    int j = 0;
    int k = 0;

    // length1 is the length/size of the array to the left
    // length2 is the length/size of the array to the right
    int length1 = (mid - left) + 1;
    int length2 = right - mid;

    // allocate memory for two temporary arrays using the length1 and length2 accordingly
    point *leftarray = (point*)malloc(length1 * sizeof(point));
    point *rightarray = (point*)malloc(length2 * sizeof(point));

    // for loop used to copy the data to the leftarray
    // from the array passed to the function containing the points
    for (i = 0; i < length1; i++)

        leftarray[i] = arraypts[i + left];

    // for loop used to copy the data to the right array
    // from the passed array to the function containing the points
    for (i = 0; i < length2; i++)

        rightarray[i] = arraypts[i + mid + 1];

    // i is the initial index of first subarray
    // j is the initial index of second subarray
    // k is the initial index of merged subarray
    i = 0;
    j = 0;
    k = left;

    // while loop  used to compare the elements and insert them accordingly with
    // smaller element first to the arraypts
    while (i < length1 && j < length2) {

        // if statement used to compare the element at the ith index of left array
        // to the one at the j index of the right array
        // the lowest of both will be inserted first
        if (compareTo(&leftarray[i], &rightarray[j]) < 0) {

            arraypts[k] = leftarray[i];

            // increment i
            i++;

        }

        // else statement used if the comparison of the point at the i th index of the left array
        // to the point in the right array at the j th index result in 0 or a positive number
        // meaning the if statement prior to this wasn't true
        else {

            arraypts[k] = rightarray[j];

            // increment j
            j++;

        }

        // increment k
        k++;

    }

    // while loop used to copy the remaining elements of the leftarray
    // to arraypts if there are any remaining
    while (i < length1) {

        arraypts[k] = leftarray[i];

        // increment i and k
        i++;
        k++;

    }

    // while loop used to copy the remaining elements to
    // arraypts if there are any remaining
    while (j < length2) {

        arraypts[k] = rightarray[j];

        // increment j and k
        j++;
        k++;

    }

    // free the allocated memory for both left and right arrays used
    // during the sorting
    free(leftarray);
    free(rightarray);

}

// Pre-conditions: The function takes an array of type point containing the points scanned
//                 left represents the index of the first point of the array (low)
//                 right represents the index of the last point of the array (high)
//                 threshhold represents the integer value that will be used to do the comparison
//                 that will determine which sorting method to be used accordingly
// Post-conditions: The function will either call insertion sort or merge sort depending
//                  on the comparison of the length of the array with the threshhold value
//                  if the length is less or equal to the threshhold value insertion sort will be used
//                  else mergesort and merge functions will be called accordingly
void mergesort(point points[], int left, int right, int threshhold) {

    // integer mid that will represent the index of the value of the middle
    // of the current array of points passed
    int mid;

    // if statement used in the case where the number of points
    // in the array is less or equal to the value of the threshold
    // the following statement calls the insertion sort function
    if ((right - left) <= threshhold)

        insertionsort(points, left, right);

    // else statement used if the number of points in the array is superior
    // to the value of the threshold
    else {

        // if statement used to call the merge sorting function accordingly
        if (left < right) {

            // determine the middle of the array
            mid = (left + right) / 2;

            // Sort the first and second halves
            // merge both sorted halves afterwards
            mergesort(points,left,mid, threshhold);
            mergesort(points,mid+1,right, threshhold);
            merge(points,left,mid,right);

        }

    }

}

// Pre-conditions: The function takes an array of type point containing the points scanned
//                 The array within the function will be called p
//                 left represents the index of the first point of the array (low)
//                 right represents the index of the last point of the array (high)
// Post-conditions: The function will sort the array passed to it (p) according to the
//                  insertion sort method
void insertionsort(point p[], int left, int right) {

    // i and j are counters
    int i = 0;
    int j = 0;

    // curr is a struct point type variable that will represent the current
    // point at the current iteration
    point curr;

    // for loop used to traverse each element of the array
    // to achieve the insertion sort using inner loop and comparisons
    for (i = left + 1; i <= right; i++) {

        // curr represents the point at the current iteration
        // which gets updated at each iteration
		curr = p[i];

        // for loop used to compare the current ^point curr with the previous points
        // through comparing curr's characteristics with the ones of the points at
        // prior indexes through calling the compareTo function
        for (j = i - 1; j >= left; j--) {

            // if statement used if a positive value is returned
            // meaning that the substracting that occurred resulted in a (+) integer
            if (compareTo(&p[j], &curr) > 0)

                // shift the current element at the j index to the one after it
                p[j + 1] = p[j];

            // else statement used to break out of the inner loop
            // if the comparison through the compareTo function returned
            // a value equal to 0 or negative
            else

                break;

            }

        // update the following index of j with curr
        p[j + 1] = curr;

    }

}

// Pre-conditions: The function takes an array of points, its length
//                 and the threshold that will afterwards be passed to the mergesort function
//                 where it will be used.
// Post-conditions: The function will call the merge sort function
//                  in which we will determine either to use mergesort
//                  or insertion sorting method.
//                  the array of points, the first index of it(low), the last index of it(high)
//                  and the threshold will be passed to the function called.
void sort(point arraypts[], int lengtharr, int threshhold) {

    mergesort(arraypts, 0, lengtharr, threshhold);

}

// GitHub: YHmaiti