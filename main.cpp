#include <iostream>
#include "cube.cpp"
#include <unordered_map>
#include <queue>

using namespace std;

int main(){
    CUBE cubeEnd;
    cubeEnd.turn_back_clock();
    cubeEnd.print_square();
    cubeEnd.turn_back_counter();
    CUBE cube;

    // Init
    //cube.print_square();

    // Test back switching
    // cube.turn_back_clock();
    // cube.print_square();

    // cube.turn_back_counter();
    // cube.print_square();

    // Test right switching
    // cube.turn_right_clock();
    // cube.print_square();

    // cube.turn_right_counter();
    // cube.print_square();

    // Test bottom switching
    // cube.turn_bottom_clock();
    // cube.print_square();

    // cube.turn_bottom_counter();
    // cube.print_square();

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
            move[current] = 'B';
        }

        current.turn_back_counter();
        current.turn_back_counter();

        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'F';
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
            move[current] = 'L';
        }

        current.turn_right_clock();

        // Test bottom
        current.turn_bottom_clock();
        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'B';
        }

        current.turn_bottom_counter();
        current.turn_bottom_counter();

        if (hashmap.find(current) == hashmap.end()){
            hashmap[current] = true;
            q.push(current);
            disti[current] = disti[top]+1;
            parent[current] = top;
            move[current] = 'T';
        }

        current.turn_bottom_clock();
    }

    CUBE final = cubeEnd;
    final.print_square();
    while (parent.find(final) != parent.end()){
        final = parent[final];
        final.print_square();
        printf("%c\n",move[final]);
    }


}