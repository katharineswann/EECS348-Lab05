//Name: Katharine Swann
//Description: Use C to create the two described programs
//             these programs will read from pdfs

#include <stdio.h>

//Program problem #1: Sales Report
//read 12 monthly sales and generate a sales report
//report should include the following: 
//1) a title for the report
//2) a tabular report of the month and sales in two columns
    //one for the month (January, February, etc.) and one for
    //corresponding sales
//3) the sales summary (w/ month with the lowest sale, month with
    //the highest sales and the average sales)
//4) a six-month moving average also in a tabular format
//5) tabular listing of months and sales w/ the
    //sales from highest to lowest

#define MONTHS 12 //value 12, for the 12 months of the year

//avg of array
double average(double array[], int size) {
    double total = 0.0;
    for (int i = 0; i < size; ++i) {
        total = total + array[i];
    }
    return total / size;
}

//find the index where the minimum value in array is
int minimum(double array[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i) {
        if (array[i] < array[index]) {
            index = i;
        }
    }
    return index;
}

//find the index where the maximum value in array is
int maximum(double array[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i) {
        if (array[i] > array[index]) {
            index = i;
        }
    }
    return index;
}

//sort array largest to smallest
void highest_to_lowest(double array[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (array[i] < array[j]) {
                double temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main() {
    const char *months[MONTHS] = {
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
    };

    double sales[MONTHS];

    FILE *file = fopen("problem-1.tsv", "r"); //file name of provided input from pdf given
    for (int i = 0; i < MONTHS; ++i) {
        if (fscanf(file, "%lf", &sales[i]) != 1) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    printf("\nMonthly Sales Report for 2022:");
    printf("\n");
    printf("\n");

    printf("Month\t\tSales\n"); //two tab space between columns
    for (int i = 0; i < MONTHS; ++i) {
        printf("%-15s $%.2f\n", months[i], sales[i]); //to the second decimal
    }//- left aligns months, but $ sign not with lf value
    printf("\n");

    int index1 = minimum(sales, MONTHS);
    int index2 = maximum(sales, MONTHS);
    double avg = average(sales, MONTHS);

    printf("Sales summary:\n");
    printf("Minimum sales: $%.2lf (%s)\n", sales[index1], months[index1]);
    printf("Maximum sales: $%.2lf (%s)\n", sales[index2], months[index2]);
    printf("Average sales: $%.2lf\n", avg);
    printf("\n");

    printf("Six-Month Moving Average Report:\n");
    for (int i = 5; i < MONTHS; ++i) {
        double moving_average = average(sales + i - 5, 6);
        printf("%-15s %-15s $%.2f\n", months[i - 5], months[i], moving_average);
    }
    printf("\n");

    highest_to_lowest(sales, MONTHS);
    printf("Sales Report (Highest to Lowest):\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < MONTHS; ++i) {
        printf("%-15s $%.2f\n", months[i], sales[i]);
    }
    printf("\n");

    //Program problem #2: Determining a football score possibilities
    //read an NFL score by a team and determine score possibilities
    //score is expected to be 2 or higher (so program stop if <= 1)
    int score;

    do {
        printf("Enter the NFL score: ");
        scanf("%d", &score); //store user input to variable score

        if (score <= 1) {
            printf("Program terminated because score less than or equal to 1 was entered\n");
            break;
        }

        printf("possible combinations of scoring plays:\n"); //use nested for loop
    
        //TD = 6 points
        //FG = 3 points
        //Safety = 2 points
        //TD + 2 = 8 points
        //TD + 1 = 7 points

        for (int td1 = 0; td1 <= score / 6; td1++) { //break up game score based on points per type of plays
            for (int fg = 0; fg <= score / 3; fg++) {
                for (int td2 = 0; td2 <= (score - td1 * 6 - fg * 3) / 6; td2++) { 
                    for (int fg = 0; fg <= (score - td1 * 6 - td2 * 6 - fg * 3) / 3; fg++) {
                        int safety = (score - td1 * 6 - td2 * 6 - fg * 3 - fg * 3);
                        
                        if (safety >= 0 && safety % 2 == 0) { //boolean and
                            printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                                td1, fg, td2, fg, safety / 2);
                        }
                    }
                }
            }
        }

        printf("\n");

    } while (score >= 2); //otherwise terminate

    return 0;
}