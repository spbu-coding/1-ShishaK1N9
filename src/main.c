/*
 * Rectangle(?) and Simpson's algorithms
 *
 * Roman Shishkin
 * Last update: 06.10.2020
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define array_length(x) (sizeof(x) / sizeof(x[0]))
#define error_print(...) fprintf(stderr, __VA_ARGS__)

const int RECTANGLE_ARRAY[] = {6, 10, 20, 100, 500, 1000};
const double PI = 3.14159;

void check_error(double left_border, double right_border)
{
    if(left_border < 0)
    {
        error_print("Whoops, looks like something went wrong:\n"
                    "Left border cannot be less than 0.\n");
        exit(EXIT_FAILURE);
    }
    if(right_border > PI)
    {
        error_print("Whoops, looks like something went wrong:\n"
                    "Right border cannot be more than Pi.\n");
        exit(EXIT_FAILURE);
    }
    if(left_border > PI)
    {
        error_print("Whoops, looks like something went wrong:\n"
                    "Left border cannot be more than Pi.\n");
        exit(EXIT_FAILURE);
    }
    if(right_border < 0)
    {
        error_print("Whoops, looks like something went wrong.\n"
                    "Right border cannot be less than 0.\n");
        exit(EXIT_FAILURE);
    }
    if(left_border > right_border)
    {
        error_print("Whoops, looks like something went wrong.\n"
                    "Left border cannot be more than right border.\n");
        exit(EXIT_FAILURE);
    }
}

void input_border(double *left_border, double *right_border)
{
    printf("Insert left border: ");
    scanf("%lf", left_border);
    printf("Insert right border: ");
    scanf("%lf", right_border);
}

double rectangle_rule(double left_border, double right_border, int rectangle_quantity)
{
    double step = (right_border - left_border) / rectangle_quantity,  middle = (left_border + left_border + step) / 2;
    double square = 0.0;
    while(rectangle_quantity > 0)
    {
        square += sin(middle) * step;
        middle += step;
        rectangle_quantity--;
    }
    return square;
}

double simpsons_rule(double left_border, double right_border, int rectangle_quantity)
{
    double step = (right_border - left_border) / rectangle_quantity, square = 0.0;
    double active_left = left_border, active_right = left_border + step;
    while(rectangle_quantity > 0)
    {
        square += step / 6 * (sin(active_left) + 4 * sin((active_left + active_right) / 2) + sin(active_right));
        active_left += step;
        active_right += step;
        rectangle_quantity--;
    }
    return square;
}

void output_square(double left_border, double right_border, int *array, int length)
{
    for(int index = 0; index < length; index++)
    {
        double rectangle_square = rectangle_rule(left_border, right_border, *(array + index));
        double simpsons_square = simpsons_rule(left_border, right_border, *(array + index));
        printf("%d %.5lf %.5lf\n", *(array + index), rectangle_square, simpsons_square);
    }
}

int main()
{
    double left_border, right_border;
    input_border(&left_border, &right_border);
    check_error(left_border, right_border);
    output_square(left_border, right_border, &RECTANGLE_ARRAY, array_length(RECTANGLE_ARRAY));
    return 0;
}
