#include <iostream>
#include "cube.cpp"
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    // To check we are done (since init is solved)
    CUBE cubeEnd;

    CUBE cube;
    cube.read_from_input();
    cube.print_square();

    vector<char> move(NB_STATES, 0);

    queue<CUBE> q;
    q.push(cubeEnd);
    move[cube_index(cubeEnd)] = -1;

    while (!q.empty()){
        CUBE top = q.front(); q.pop();
        CUBE current = top;

        // Test back
        current.turn_back_clock();
        // New state
        if (move[cube_index(current)] == 0){
            q.push(current);
            move[cube_index(current)] = 'B';
        }

        current.turn_back_counter();
        current.turn_back_counter();

        if (move[cube_index(current)] == 0){
            q.push(current);
            move[cube_index(current)] = 'b';
        }

        current.turn_back_clock();

        // Test right
        current.turn_right_clock();
        if (move[cube_index(current)] == 0){
            q.push(current);
            move[cube_index(current)] = 'r';
        }

        current.turn_right_counter();
        current.turn_right_counter();

        if (move[cube_index(current)] == 0){
            q.push(current);
            move[cube_index(current)] = 'R';
        }

        current.turn_right_clock();

        // Test bottom
        current.turn_bottom_clock();
        if (move[cube_index(current)] == 0){
            q.push(current);
            move[cube_index(current)] = 'D';
        }

        current.turn_bottom_counter();
        current.turn_bottom_counter();

        if (move[cube_index(current)] == 0){
            q.push(current);
            move[cube_index(current)] = 'd';
        }

        current.turn_bottom_clock();
    }

    string solution;

    // Start on the cube we got
    CUBE curr = cube;
    while (!(curr == cubeEnd)){
        char mov = move[cube_index(curr)];

        solution += mov;
        printf("%c\n",mov);

        // Undo the turn the search did -> we get the "parent"
        if (mov == 'B'){
            curr.turn_back_counter();
        }
        else if (mov == 'b'){
            curr.turn_back_clock();
        }
        else if (mov == 'r'){
            curr.turn_right_counter();
        }
        else if (mov == 'R'){
            curr.turn_right_clock();
        }
        else if (mov == 'D'){
            curr.turn_bottom_counter();
        }
        else if (mov == 'd'){
            curr.turn_bottom_clock();
        }
        curr.print_square();
    }

    printf("Solution: %s\n", solution.c_str());

}