#include <iostream>

#define MAP_WIDTH 100
#define MAP_HEIGHT 60
int ALIVE = 1;
int DEAD = 0;
int map[MAP_HEIGHT][MAP_WIDTH];
int seed = time(NULL);

int aliveProb = 58;
int generations = 10;

void genCave() {
    srand(seed);
    for(int h=0; h<MAP_HEIGHT; h++) {
        for(int w=0; w<MAP_WIDTH; w++) {
            map[h][w]=ALIVE;
            if(rand() % 100 > aliveProb) map[h][w]=DEAD;
        }
    }
}

int near(int x, int y) {
    int count=0;
    for(int h=y-1; h<2+y; h++) {
        for(int w=x-1; w<2+x; w++) {
            if(!(w==x && h==y)) {
                count+=map[h][w];
                //std::cout << map[h][w];
            } else {
                //std::cout << ".";
            }
        }
        //std::cout << std::endl;
    }
    //std::cout << count << std::endl;
    return count;
}

void displayCave() {
    for(int h=0; h<MAP_HEIGHT; h++) {
        for(int w=0; w<MAP_WIDTH; w++) {
            if(map[h][w]) {
                std::cout << ".";
            } else {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    genCave();
    //near(20, 20);
    displayCave();
    for(int gen=0; gen<generations; gen++) {
        for(int h=1; h<MAP_HEIGHT-1; h++) {
            for(int w=1; w<MAP_WIDTH-1; w++) {
                int count = near(w, h);
                if(map[h][w] == DEAD && count >= 6) map[h][w] = ALIVE;
                if(map[h][w] == ALIVE && count <= 3) map[h][w] = DEAD;
            }
        }
        displayCave();
        std::cout << std::endl;
    }
    displayCave();
    return 0;
}