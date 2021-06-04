#include "splashkit.h"

using namespace std;
#define NUM_VALS 20

void draw_values(const int values[], int size)
{
    int x = 0;
    int y;
    int rect_height;
    int rect_width = screen_width() / size;

    for (int i = 0; i < size; i++)
    {
        rect_height = values[i];
        y = screen_height() - rect_height;

        fill_rectangle(COLOR_PINK, x, y, rect_width, rect_height);
        draw_rectangle(COLOR_WHITE, x, y, rect_width, rect_height);

        x += rect_width;
    }
}

void swap(int &value1, int &value2)
{
    int temp = value1;
    value1 = value2;
    value2 = temp;
}

void draw_sort(int values[], int size)
{
    clear_screen(COLOR_PLUM);
    draw_values(values, size);
    refresh_screen(60);
}

void random_fill_array(int values[], int size)
{
    for (int i = 0; i < size; i++)
    {
        values[i] = rnd(screen_height()) + 1;
    }
}
void bubble_sort(int values[], int size)
{
    for (int j = 0; j < size; j++)
    {
        if (values[j] > values[j + 1])
        {
            swap(values[j], values[j + 1]);
            draw_sort(values, size);
        }
    }
    for (int i = 0; i < size - 1; i++)
    {
        if (values[i] > values[i + 1])
        {
            swap(values[i], values[i + 1]);
            draw_sort(values, size);
        }
    }
}
void selection_sort(int values[], int size)
{
    int i , j , min_idx;

    for(i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < size; j++)
        {
            if(values[j] < values[min_idx])
            {
                min_idx = j;
                swap(values[min_idx] , values[i]);
                draw_sort(values, size);
            }
        }
    }
}
void cocktail_sort(int values[], int size) //Sorts array in both directions alternatively
{
    int start = 0;
    bool swapped = true;
    int end = size - 1;

    while (swapped)
    {
        //resetting the swapped elements on entering the loop
        //since the loop,might be true in previous iteration. 
        swapped = false;
        //loop from left to right as in bubble sort from the largest value from the left or right and if the left value
        //is large it is swapped, the largest number will reside at the end of array
        for (int i = 0; i < end; i++)
        {
            if (values[i] > values[i + 1])
            {
                swap(values[i], values[i + 1]);
                swapped = true;
                draw_sort(values, size);
            }
            else //if nothing moves, array is sorted and resetting the everything so it maybe used in next step.
            {
                swapped = false;
            }

        }
        //loop from right to left such as the opposite direction doing the same comparison as before and 
        //are swapped if needed.
        for (int i = end - 1; i < start; i--)
        {
            if (values[i] > values[i + 1])
            {
                swap(values[i], values[i + 1]);
                swapped = true;
                draw_sort(values, size);
            }
            else
            {
                swapped = false;
            }
             
        }
    }
    
}

void handle_input(int values[], int size)
{

    if (key_typed(R_KEY))
    {
        random_fill_array(values, size);
    }
    else if (key_typed(D_KEY))
    {
        bubble_sort(values, size);
    }
    else if (key_typed(S_KEY))
    {
        cocktail_sort(values, size);
    }
    else if(key_typed(J_KEY))
    {
        selection_sort(values , size);
    }
}

int main()
{
    int values[NUM_VALS];

    open_window("Sort Visualiser", 800, 600);

    random_fill_array(values, NUM_VALS);

    while (not quit_requested())
    {
        process_events();
        handle_input(values, NUM_VALS);

        draw_sort(values, NUM_VALS);
    }

    return 0;
}

//link for the video:
//https://d2l.deakin.edu.au/d2l/ext/rp/882859/lti/framedlaunch/e120dab2-1355-47b4-9d02-5491b8a89ec8