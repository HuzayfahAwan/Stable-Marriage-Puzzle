#include <iostream>
using namespace std;

void printArray(int marriages[], int solutionNumber) {
    // prints the solution inside of the marriages array in a T-chart
    cout << "Solution Number: " << solutionNumber << "\n\n" << "Man\tWoman\n";
    for (int i = 0; i < 3; i++) {
        cout << i << "\t" << marriages[i] << endl;
    }
    cout << endl;
}

void backtrack(int marriages[], int* index) {
    *index -= 1; // go back one index -> perform pointer arithmetic by going back 1 memory box or 4 bytes in memory since you're dealing with integers
    if (*index < 0) return; // if the index value is less than 0, then terminate the method
    marriages[*index]++; // once you backtrack, increment the index value, so that value can be checked later in main() when calling tests()
    if (marriages[*index] > 2) { // if the value in the index of the marriages array is greater than 2, then reset it to 0 and backtrack
        marriages[*index] = 0;
        backtrack(marriages, index);
    }
}

bool tests(int marriages[], int index, int mp[][3], int wp [][3]) {
    // loop through each index of the marriages array up until the current index in main() so far
    for (int i = 0; i < index; i++) {
        // these variables tell what each component of the array translates to in the context of the problem, making the code more readable
        int newMan = index, newWoman = marriages[index], currentMan = i, currentWoman = marriages[i];
        if (currentWoman == newWoman) return false; // if any of the previous indices equal the value currently being checked -> test fail
        // if the new man prefers the current previous woman over his partner and the current previous woman prefers the new man over her partner -> test fail
        else if (mp[newMan][currentWoman] < mp[newMan][newWoman] && wp[currentWoman][newMan] < wp[currentWoman][currentMan]) return false;
        // if the new woman prefers the current previous man over her partner and the current previous man prefers the new woman over his partner -> test fail
        else if (mp[currentMan][newWoman] < mp[currentMan][currentWoman] && wp[newWoman][currentMan] < wp[newWoman][newMan]) return false;
    }
    return true; // if false isn't returned at this point, then all tests must have passed, so return true
}

int main() {
    int index = 0, solutionNum = 0; // keeps track of the index of the marriages array and the current solution number
    // this array holds the marriage pairings with the index number tracking the man # and the value inside each index tracking the woman #
    int marriages[3] = {0};
    /* this array holds the preference's of each man towards each woman -> the row number tracks the man #, the column number tracks the woman #, and
       the value inside each column tells you what place the man ranks each woman (0, the highest, to 2, the lowest) */
    int mp[3][3] = { {0, 2, 1}, {0, 2, 1}, {1, 2, 0} }; 
    // the array below does the same thing as the man's preference's array above but this array is for the preference's of each woman instead
    int wp[3][3] = { {2, 1, 0}, {0, 1, 2}, {2, 0, 1} };
    while (index != -1) { // if the index is backtracked to less than 0, then all solutions have been found and printed
        if (index > 2) {
            solutionNum++;
            printArray(marriages, solutionNum);
            backtrack(marriages, &index);
        } else if (marriages[index] > 2) { // if the value inside of an index in the marriages array is greater than 2, then you must backtrack
            marriages[index] = 0;
            backtrack(marriages, &index);
        } 
        else if (tests(marriages, index, mp, wp)) index++; // if all tests pass, then move to the next index to pair up the next couples
        else marriages[index]++; // if one of the tests above fail, then increment the value inside the current index of the marriages array
    }
    return 0;
}