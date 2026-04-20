#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct CUBE{
    // Liste des 8 coins de devant haut gauche a devant bas droite puis la meme chose pour la face de derriere
    
    // Set it to the end position
    // Each idx is a specific corner
    // I need to associate a corner to an IDX
    // If IDX of corners matches their position in the list we have a solved cube
    char reprensentation[8] = {0,1,2,3,4,5,6,7};

    bool operator==(const CUBE& other) const{
        for (int i = 0; i < 8; ++i){
            if (reprensentation[i] != other.reprensentation[i]){
                return false;
            }
        }
        return true;
    }

    // TOP = White
    // BOTTOM = Yellow
    // LEFT = Red
    // RIGHT = Orange
    // FRONT = Blue
    // BACK = Green

    // Corner TOP BACK LEFT -> id = 0 -> colors are White Red Green
    // Corner TOP BACK RIGHT -> id = 1 -> colors are White Green Orange
    // Corner BOTTOM BACK LEFT -> id = 2 -> colors are Yellow Green Red




    // Implement a way to turn the cube around easily
    // If we know that the TOP LEFT FRONT corner is correct we can replace moving it by the reverse operation on the other side
    // Only need to move BACK, RIGHT, BOTTOM

    // Turns the backface of the cube clockwise
    // The backface is idx 0 -> 3
    void turn_back_clock(){
        // Face 
        // 0 1 
        // 2 3


        int lastValue = reprensentation[1];
        int order[4] = {3,2,0,1};

        for (int i = 3; i >= 1; --i){
            reprensentation[order[i]] = reprensentation[order[i-1]];
        }
        reprensentation[3] = lastValue;
    }
    // Turns the backface of the cube counterclockwise
    // The backface is idx 0 -> 3
    void turn_back_counter(){
        turn_back_clock();
        turn_back_clock();
        turn_back_clock();
    }

    // // Turns the frontface of the cube clockwise
    // // The backface is idx 4 -> 7
    // void turn_front_clock(){
    //     int lastValue = reprensentation[7];
    //     for (int i = 7; i >= 5;--i){
    //         reprensentation[i] = reprensentation[i-1];
    //     }
    //     reprensentation[4] = lastValue;
    // }

    // // Turns the frontface of the cube counterclockwise
    // // The backface is idx 4 -> 7
    // void turn_front_counter(){
    //     turn_front_clock();
    //     turn_front_clock();
    //     turn_front_clock();
    // }


    //Turns the right face clockwise
    // Idx are -> 1,3,5,7
    void turn_right_clock(){
        // The Face
        // 5 1
        // 7 3

        // Clockwise


        // Clockwise means that 1 goes to 3
        // 3 goes to 7
        // 7 goes to 5
        // 5 goes to 1
        int lastValue = reprensentation[1];
        int order[4] = {3,7,5,1};

        for (int i = 3; i >= 1; --i){
            reprensentation[order[i]] = reprensentation[order[i-1]];
        }
        reprensentation[3] = lastValue;
    }

    void turn_right_counter(){
        turn_right_clock();
        turn_right_clock();
        turn_right_clock();
    }

    //Turns the right face clockwise
    void turn_bottom_clock(){
        // The Face
        // 6 7
        // 2 3

        // Clockwise


        // Clockwise means that 1 goes to 3
        // 3 goes to 7
        // 7 goes to 5
        // 5 goes to 1
        int lastValue = reprensentation[3];
        int order[4] = {7,6,2,3};

        for (int i = 3; i >= 1; --i){
            reprensentation[order[i]] = reprensentation[order[i-1]];
        }
        reprensentation[7] = lastValue;
    }

    void turn_bottom_counter(){
        turn_bottom_clock();
        turn_bottom_clock();
        turn_bottom_clock();
    }

    void print_square(){
        for (int i = 0; i < 8; ++i){
            printf("%d ",reprensentation[i]);
        }
        printf("\n");
        printf("\n");
    }



    void read_from_input(){
        // TODO : read input to initialise the cune state
        // This will be a bit hard but help me do the rest easily

        char couleurs[24];
        int currIdx = 0;
        while (currIdx < 24){
            char curr;
            cin >> curr;
            if (curr != ' '){
                couleurs[currIdx] = curr;
                ++currIdx;
            }
        }

        printf("Read this\n");

        for (int i = 0; i < 24; ++i){
            printf("%c ",couleurs[i]);
        }
        printf("\n");

        // The corner that the face belongs to
        int cornerIdx[24] = {0,1,4,5,0,4,4,5,5,1,2,6,6,7,7,3,6,7,2,3,2,3,0,1};

        // For each corner 8 the 3 color it has
        vector<vector<char> > corner(8,vector<char>());

        for (int i = 0; i < 24;++i){
            corner[cornerIdx[i]].push_back(couleurs[i]);
        }

        for (int i = 0; i < 8; ++i){
            sort(corner[i].begin(),corner[i].end());
        }

        printf("Corners\n");

        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 3; ++j){
                printf("%c ",corner[i][j]);
            }
            printf("\n");
        }

        // The colors the corner of idx should have
        vector<vector<char> > cornerColors = {
            {'G','R','W'},
            {'G','O','W'},
            {'G','R','Y'},
            {'G','O','Y'},
            {'B','R','W'},
            {'B','O','W'},
            {'B','R','Y'},
            {'B','O','Y'}
        };

        // For a corner position the corner idx
        vector<int> actualIdx(8,-1);

        for (int i = 0; i < 8; ++i){
            vector<char> currentCorner = corner[i];
            for (int j = 0; j < 8; ++j){
                if (currentCorner == cornerColors[j]){
                    actualIdx[i] = j;
                    printf("Corner idx of pos %d is %d\n",i,j);
                    break;
                }
            }
        }
        for (int i = 0; i < 8; ++i){
            reprensentation[i] = actualIdx[i];    
        }
        
    }
};

struct cubehasher{
    size_t operator()(const CUBE& p) const{
        size_t sum = 0;
        int power = 1;
        for (int i = 0; i < 8; ++i){
            sum += (p.reprensentation[i] * power);
            power*=10;
        }
        return sum;
    }
};