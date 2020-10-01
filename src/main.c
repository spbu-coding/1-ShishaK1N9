/*
 * Rectangle(?) and Simpson's algorithms
 *
 * Roman Shishkin
 * Last update: 30.09.2020
*/
#include <stdio.h>
#include <math.h>

#define array_length(x) (sizeof(x) / sizeof(x[0]))

const int RECTANGLE_ARRAY[] = {6, 10, 20, 100, 500, 1000};

void input(double *first_scan, double *last_scan)
{
    printf("Insert left border: ");
    scanf("%lf", first_scan);
    printf("Insert right border: ");
    scanf("%lf", last_scan);
}

double rectangle_rule(double left_border, double right_border, int quantity)
{
    double step = (right_border - left_border) / quantity,  middle = (left_border + left_border + step) / 2;
    double square = 0.0;
    while(quantity > 0)
    {
        square += sin(middle) * step;
        middle += step;
        quantity--;
    }
    return square;
}

double simpsons_rule(double left_border, double right_border, int quantity)
{
    double step = (right_border - left_border) / quantity, square = 0.0;
    double active_left = left_border, active_right = left_border + step;
    while(quantity > 0)
    {
        square += step / 6 * (sin(active_left) + 4 * sin((active_left + active_right) / 2) + sin(active_right));
        active_left += step;
        active_right += step;
        quantity--;
    }
    return square;
}

void output(double left_border, double right_border, int *array, int length)
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
    double left_border = 0.0, right_border = 0.0;
    input(&left_border, &right_border);
    output(left_border, right_border, &RECTANGLE_ARRAY, array_length(RECTANGLE_ARRAY));
    return 0;
}
