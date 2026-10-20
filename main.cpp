#include <iostream>
#include "cube.cpp"
#include <unordered_map>
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

    unordered_map<CUBE, bool,cubehasher> hashmap;
    unordered_map<CUBE,int, cubehasher> disti;
    unordered_map<CUBE, CUBE, cubehasher> parent;
    unordered_map<CUBE, char, cubehasher> move;

    queue<CUBE> q;
    q.push(cube);
    hashmap[cube] = true;
    disti[cube] = 0;

    while (!q.empty()){
        CUBE top = q.front(); q.pop();
        CUBE current = top;

        if (top == cubeEnd){
            top.print_square();
            printf("Happy %d !!!!!!!\n",disti[cubeEnd]);
            break;
        }

        // Test back
        current.turn_back_clock();
        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'b';
        }

        current.turn_back_counter();
        current.turn_back_counter();

        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'B';
        }

        current.turn_back_clock();

        // Test right
        current.turn_right_clock();
        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'R';
        }

        current.turn_right_counter();
        current.turn_right_counter();

        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'r';
        }

        current.turn_right_clock();

        // Test bottom
        current.turn_bottom_clock();
        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'd';
        }

        current.turn_bottom_counter();
        current.turn_bottom_counter();

        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'D';
        }

        current.turn_bottom_clock();
    }

    string solution;
    CUBE final = cubeEnd;
    final.print_square();

    while (parent.find(final) != parent.end()){
        printf("%c\n",move[final]);
        solution += move[final];
        final = parent[final];
        final.print_square();
    }

    reverse(solution.begin(), solution.end());
    printf("Solution: %s\n", solution.c_str());

}