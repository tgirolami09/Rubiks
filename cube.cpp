#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <array>

using namespace std;

// Corner slots (index in the arrays):
//   back face  : 0 = top-left, 1 = top-right, 2 = bottom-left, 3 = bottom-right
//   front face : 4 = top-left, 5 = top-right, 6 = bottom-left, 7 = bottom-right

// Twist of a piece = position (0, 1 or 2)

// A move == two tables -> slot i holds the piece that was in slot PERM[i], twist increases by TWIST[i] (mod 3).

// Generated from the cube geometry (there should be excatly 4 changes in any list)
static const array<int,8> BACK_CLOCK_PERM      = {2,0,3,1,4,5,6,7};
static const array<int,8> BACK_CLOCK_TWIST     = {1,2,2,1,0,0,0,0};
static const array<int,8> BACK_COUNTER_PERM    = {1,3,0,2,4,5,6,7};
static const array<int,8> BACK_COUNTER_TWIST   = {1,2,2,1,0,0,0,0};

static const array<int,8> RIGHT_CLOCK_PERM     = {0,5,2,1,4,7,6,3};
static const array<int,8> RIGHT_CLOCK_TWIST    = {0,1,0,2,0,2,0,1};
static const array<int,8> RIGHT_COUNTER_PERM   = {0,3,2,7,4,1,6,5};
static const array<int,8> RIGHT_COUNTER_TWIST  = {0,1,0,2,0,2,0,1};

static const array<int,8> BOTTOM_CLOCK_PERM     = {0,1,6,2,4,5,7,3};
static const array<int,8> BOTTOM_CLOCK_TWIST    = {0,0,0,0,0,0,0,0};
static const array<int,8> BOTTOM_COUNTER_PERM   = {0,1,3,7,4,5,2,6};
static const array<int,8> BOTTOM_COUNTER_TWIST  = {0,0,0,0,0,0,0,0};

struct CUBE{
    // Liste des 8 coins de devant haut gauche a devant bas droite puis la meme chose pour la face de derriere
    
    // Set it to the end position
    // Each idx is a specific corner
    // I need to associate a corner to an IDX
    // If IDX of corners matches their position in the list we have a solved cube
    array<char,8> reprensentation = {0,1,2,3,4,5,6,7};
    // orientation[idx] = twist (0, 1 or 2) of the piece in that slot
    // Alls 0's means solved
    array<char,8> orientation = {0,0,0,0,0,0,0,0};

    bool operator==(const CUBE& other) const{
        return reprensentation == other.reprensentation && orientation == other.orientation;
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

    // Applies a move by its two tables
    void apply(const array<int,8>& perm, const array<int,8>& twist){
        array<char,8> nextRep;
        array<char,8> nextOrien;

        // By construction of the permutations
        for (int i = 0; i < 8; ++i){
            nextRep[i] = reprensentation[perm[i]];
            nextOrien[i] = (orientation[perm[i]] + twist[i]) % 3;
        }

        reprensentation = nextRep;
        orientation = nextOrien;
    }

    void turn_back_clock(){
        apply(BACK_CLOCK_PERM, BACK_CLOCK_TWIST);
    }
    
    void turn_back_counter(){
        apply(BACK_COUNTER_PERM, BACK_COUNTER_TWIST);
    }

    void turn_right_clock(){
        apply(RIGHT_CLOCK_PERM, RIGHT_CLOCK_TWIST);
    }
    
    void turn_right_counter(){
        apply(RIGHT_COUNTER_PERM, RIGHT_COUNTER_TWIST);
    }

    void turn_bottom_clock(){
        apply(BOTTOM_CLOCK_PERM, BOTTOM_CLOCK_TWIST);
    }
   
    void turn_bottom_counter(){
        apply(BOTTOM_COUNTER_PERM, BOTTOM_COUNTER_TWIST);
    }

    void print_square(){
        for (int i = 0; i < 8; ++i){
            printf("%d ",reprensentation[i]);
        }
        printf("\n");

        for (int i = 0; i < 8; ++i){
            printf("%d ",orientation[i]);
        }
        printf("\n");
        printf("\n");
    }

    void read_from_input(){
        array<char,24> couleurs;

        for (int i = 0; i < 24; ++i){
            // Ca marche tout seul en fait
            cin >> couleurs[i];
        }

        // Pour chaque coins on donne l'ordre des 3 couleurs avec celui de haut/bas en premier puis dans le sens horaire en partant de devant
        const array<array<int,3>,8> stickers = {{
            {0,4,22}, {1,23,9}, {18,20,10}, {19,15,21},
            {2,6,5},  {3,8,7},  {16,11,12}, {17,13,14}
        }};

        // The colors the corner of idx should have
        const array<array<char,3>,8> cornerColors = {{
            {'G','R','W'},
            {'G','O','W'},
            {'G','R','Y'},
            {'G','O','Y'},
            {'B','R','W'},
            {'B','O','W'},
            {'B','R','Y'},
            {'B','O','Y'}
        }};

        for (int slot = 0; slot < 8; ++slot){
            array<char,3> c;
            int twist = -1;

            for (int j = 0; j < 3; ++j){
                c[j] = couleurs[stickers[slot][j]];
                if (c[j] == 'W' || c[j] == 'Y'){
                    // on sait de combien on est "twisté" puisque celui ci est censé être 0
                    twist = j;
                }
            }
            
            sort(c.begin(), c.end());

            int piece = -1;
            for (int p = 0; p < 8; ++p){
                if (c == cornerColors[p]){
                    piece = p;
                    break;
                }
            }

            reprensentation[slot] = piece;
            orientation[slot] = twist;
        }
    }
};

struct cubehasher{
    size_t operator()(const CUBE& p) const{
        size_t sum = 0;

        for (int i = 0; i < 8; ++i){
            // on fait un truc correct mais qui parait vraiment bizare
            // (on multiplie le running par 1 de plus que ce qu'on rajouter au max)
            // (ca revient juste à faire une base 24 je crois)
            sum = sum * 24 + p.reprensentation[i] * 3 + p.orientation[i];
        }

        return sum;
    }
};
