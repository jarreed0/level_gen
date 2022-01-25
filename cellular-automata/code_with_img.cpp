#include <iostream>

#define MAP_WIDTH 100
#define MAP_HEIGHT 60
int ALIVE = 1;
int DEAD = 0;
int map[MAP_WIDTH][MAP_HEIGHT];

double aliveProb = 58;
int generations = 10;
int seed = time(NULL);

void genCave() {
 srand(seed);
 for(int h = 0; h < MAP_HEIGHT; h++) {
  for(int w = 0; w < MAP_WIDTH; w++) {
   map[h][w]=ALIVE;
   if(rand() % 100 > aliveProb) map[h][w]=DEAD;
  }
 }
}

void displayCave(int sx, int sy, int width, int height) {
 for(int h = sy; h < sy+height; h++) {
  for(int w = sx; w < sx+width; w++) {
   if(map[h][w]==ALIVE) { std::cout << "#"; 
   } else { std::cout << "."; }
  }
  std::cout << std::endl;
 }
 std::cout << std::endl;
}
void displayCave() {
 displayCave(0, 0, MAP_WIDTH, MAP_HEIGHT);
}

void saveIMG(std::string filename) {
 FILE* pgmimg;
 std::string ext = ".pgm";
 pgmimg = fopen((filename+ext).c_str(), "wb");
 fprintf(pgmimg, "P2\n");
 fprintf(pgmimg, "%d %d\n", MAP_WIDTH, MAP_HEIGHT);
 fprintf(pgmimg, "255\n");
 for (int h = 0; h < MAP_HEIGHT; h++) {
  for (int w = 0; w < MAP_WIDTH; w++) {
   fprintf(pgmimg, "%d ", (!map[h][w])*255);
  }
  fprintf(pgmimg, "\n");
 }
 fclose(pgmimg);
}

int sum(int c, int y, int x) {
 int count = 0;
 for(int h=y-c; h<c*2+1 + y-c; h++) {
  for(int w=x-c; w<c*2+1 + x-c; w++) {
   if(h==y-c || w==x-c || h==y+c || w==x+c) {
    count+=map[h][w];
    //std::cout << map[h][w];
   } else {
    //std::cout << ".";
   }
  }
  //std::cout << std::endl;
 }
 //std::cout << count << std::endl;
 //std::cout << std::endl;
 return count;
}

int main() {
 genCave();

 std::cout << "Generation #0:" << std::endl;
 displayCave();
 saveIMG("gen0");

 for(int gen = 0; gen < generations; gen++) {
  for(int h = 0; h < MAP_HEIGHT; h++) {
   for(int w = 0; w < MAP_WIDTH; w++) {
    int count = sum(1, h, w);
    if(map[h][w]==DEAD && count >= 6) map[h][w]=ALIVE;
    if(map[h][w]==ALIVE && count <= 3) map[h][w]=DEAD;
   }
  }
 std::cout << "Generation #" << gen+1 << ":" << std::endl;
 displayCave();
 saveIMG("gen"+std::to_string((gen+1)));
 }
 return 0;
}
