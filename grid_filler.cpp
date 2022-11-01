#include <iostream>

using namespace std;

/* Author: Yuan Bo
 * Date: 2021/4/1
 *
 *
 * Usage:
 * This function don't have any syntax, user should follow the question to crate the their grid
 * grid is random.
 *
 * */

int **gridCanvas(int height, int width);

int **gridWithImpassible(int **gridCanvas, int height, int width, int impassibleNum);

void printGrid(int **grid, int height, int width, char fillChar);

bool XYchecker(int **grid, int userPickX, int userPickY);

int **fillGrid(int **grid, int userPickX, int userPickY, int height, int width, char fillChar, int fillCounter);

int main(int argc, char **argv) {
    int **grid;
    int width, height, percentImpassible, impassibleNum, userPickX, userPickY;
    char fillChar = '*';
    char percentConform = 'n';

    cout << "Enter the width of your grid: ";
    cin >> width;
    cout << "Enter the height of your grid ";
    cin >> height;

    //Keep ask user the percent number of the impassible unit if user enter some value greater than 40 and said n during conform.
    while (percentConform == 'n' || percentConform == 'N') {
        cout << "percent\n";
        cin >> percentImpassible;
        //When user enter some number greater than 40, enter the conform to double check.
        if (percentImpassible > 40) {
            cout << "Over 40 percent impassible unit may not be a good grid. Are you sure you want do it?\n";
            cout << "enter y to conform or enter n to enter a new percent number y/n: ";
            cin >> percentConform;
            //When user enter some value not 'n' 'N' 'y' 'Y', tell user this is a invalid command and let user enter the percent again.
            if (percentConform != 'n' && percentConform != 'y' && percentConform != 'N' && percentConform != 'Y') {
                cout << "invalid command, please enter your percentage again";
                percentConform = 'n';
            }
        } else {
            //When user entered some value less than 40, don't have to ask the user to conform and automatically set the conform to 'y'
            percentConform = 'y';
        }
    }

    //get the impassible unit number (a int) by use height times width times the percent and times 0.01.
    impassibleNum = width * height * percentImpassible * 0.01;
    //use gridCanvas function to crate a empty grid(list) with the correct size.
    grid = gridCanvas(height, width);
    //use gridWithImpassible function to fill the impassible unit in to the empty grid(list)
    grid = gridWithImpassible(grid, height, width, impassibleNum);
    //print the grid after sign in the impassible unit.
    printGrid(grid, height, width, fillChar);

    //ask user for the place they want fill and sign the X and Y value to the "userPickX" and "userPickY";
    cout << "enter X & Y for the place you want fill\n";
    cout << "Enter X: ";
    cin >> userPickX;
    cout << "Enter Y: ";
    cin >> userPickY;

    //check if the place already have an impassible unit, if no, enter the if statement.
    if (XYchecker(grid, userPickX, userPickY)) {
        //ask user for a char they want fill in to the grid.
        cout << "What character do you want fill in your grid?\n";
        cin >> fillChar;
        //set the user picked coordinate to number 2 in the 2D list;
        grid[userPickY][userPickX] = 2;
        //pass all the variables in to recursive function, more detail is in line 145.
        grid = fillGrid(grid, userPickX, userPickY, height, width, fillChar, 0);

        //print out the final grid.
        printGrid(grid, height, width, fillChar);

    } else {
        //if user picked some place already have impassible unit, print the next line and end the function.
        cout << "The place you chosen already have an impassible symbol";
        cout << endl;
    }

    //delete the array before end the function.
    for (int i = 0; i < width; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    //function end
    return 0;
}

// gridCanvas will use the height and width user given to system crate an 2D int array.
int **gridCanvas(int height, int width) {
    int **canvas = new int *[width];
    for (int i = 0; i < width; i++) {
        canvas[i] = new int[height];
    }
    return canvas;
}

//gridWithImpassible will use the canvas crate in "gridCanvas" and take the number of the impassible unit number
int **gridWithImpassible(int **grid, int height, int width, int ImpassibleNum) {
    int randomX;
    int randomY;
    //use srand(time(0)) to make sure the random X and Y will be different each time.
    srand(time(0));
    //keep adding impassible unit until there are no more need to sign in
    while (ImpassibleNum != 0) {
        //keep get an random X and random Y, if random X and Y is not already signed, sign it to 1 (1 is the impassible unit)
        randomX = rand() % height;
        randomY = rand() % width;
        if (grid[randomY][randomX] == 0) {
            grid[randomY][randomX] = 1;
            //after succeed signed an impassible unit, let impassible number -1.
            ImpassibleNum -= 1;
        }
    }
    return grid;
}

//the printGrid will take the 2D array(the grid), the height of the array, width of the array and the char user want to fill in.
void printGrid(int **array, int height, int width, char fillChar) {
    //clear the canvas before everytime print a new grid.
    system("clear");
    //checking every unit of the array, if the number is 0, print a space shows there are nothing here. if is 1, print # as an impassible unit. if is 2, print the char user want fill it.
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) {
            if (array[y][x] == 0) {
                cout << " ";
            } else if (array[y][x] == 1) {
                cout << "#";
            } else if (array[y][x] == 2) {
                cout << fillChar;
            }
        }
        cout << endl;
    }
}

//check is X and Y already have some value.
bool XYchecker(int **grid, int X, int Y) {
    if (grid[Y][X] == 1 || grid[Y][X] == 2) {
        return false;
    }

    return true;
}

/* This recursive will take 7 variables.
 *
 * int **grid: recursive will keep getting and return the newest grid to fill next char in to the grid.
 * int X: this variable will take the X user picked first and keep moving to see if there are any char are able to fill horizontally.
 * int Y: this variable will take the Y user picked first and keep moving to see if there are any char are able to fill vertically.
 * int height: this variable would never change, keep get and return the height user pick.
 * int width: this variable would never change, keep get and return the width user pick.
 * char fillChar: this variable would never change, keep get and return the char user picked and pass it to the "printGrid" function to print it.
 * int fillCounter: this variable start at 0 and will keep adding 1 while there is a new char be put in the grid.
 * Anyone can change the value of  "if (fillCounter % 1 == 0) " to adjust the rate of the char print on the canvas. 1 is the lowest rate.
 */

int **fillGrid(int **grid, int X, int Y, int height, int width, char fillChar, int fillCounter) {
    if (fillCounter % 1 == 0) {
        printGrid(grid, height, width, fillChar);
        cout << endl;
    }
    // when X is greater than 0 and also check is (X - 1) able to fill the char, if both passed enter this if statement.
    if (X > 0 && XYchecker(grid, (X - 1), Y)) {
        grid[Y][X - 1] = 2;
        fillGrid(grid, (X - 1), Y, height, width, fillChar, (fillCounter + 1));
    }
    // when Y is greater than 0 and also check is (Y - 1) able to fill the char, if both passed enter this if statement.
    if (Y > 0 && XYchecker(grid, X, (Y - 1))) {
        grid[Y - 1][X] = 2;
        fillGrid(grid, X, (Y - 1), height, width, fillChar, (fillCounter + 1));
    }
    // when X is less or equal than width and also check is (X + 1) able to fill the char, if both passed enter this if statement.
    if (X < (height - 1) && XYchecker(grid, (X + 1), Y)) {
        grid[Y][X + 1] = 2;
        fillGrid(grid, (X + 1), Y, height, width, fillChar, (fillCounter + 1));
    }
    // when Y is less or equal than height and also check is (Y + 1) able to fill the char, if both passed enter this if statement.
    if (Y < (width - 1) && XYchecker(grid, X, (Y + 1))) {
        grid[Y + 1][X] = 2;
        fillGrid(grid, X, (Y + 1), height, width, fillChar, (fillCounter + 1));
    }

    return grid;
}
