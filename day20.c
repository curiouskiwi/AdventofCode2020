// Advent of Code - Day 20
// @curiouskiwi @gary_anderson
// 21 Dec 2020


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define DIM 12
#define DATAFILE "data.txt"
// #define DIM 3
// #define DATAFILE "sample.txt"
#define NUMTILES DIM * DIM

typedef struct tile
{
    int num;
    uint16_t top;
    uint16_t toprev;
    uint16_t bottom;
    uint16_t bottomrev;
    uint16_t left;
    uint16_t leftrev;
    uint16_t right;
    uint16_t rightrev;
    int topn;
    int bottomn;
    int leftn;
    int rightn;
    int neighbours;
    char grid[8][8];
}
TILE;

TILE tiles[NUMTILES];

int layout[DIM][DIM];

char final[DIM*8][DIM*8];

void printTile(TILE t);
void printLine(char *s);
uint16_t bitrev(uint16_t n);
int adjacent(int ctr, uint16_t edge);
void place(int ctr);
bool rotate(int tile);
void order();
bool fliplr(int tile);
void printimage();
void printgrid(int r, int c, char grid[r][c]);
void rotategrid(int r, int c, char grid[r][c]);
void fliplrgrid(int r, int c, char grid[r][c]);
void printpicture();

int checkmonsters();
int checkmonsters2();
int findamonster();


int main(void)
{
    FILE *f = fopen(DATAFILE, "r");
    if (!f) return -1;

    int counter = -1;
    char buffer[12];

    while (fgets(buffer, sizeof(buffer), f))
    {
        if (buffer[0] == '\n')
            continue;
        counter++;
        if (buffer[0] == 'T')
        {
            // printf("%s", buffer);
            sscanf(buffer, "Tile %i", &tiles[counter].num);
        }

        // printf("%i\n", tiles[counter].num);
        tiles[counter].left = tiles[counter].right = tiles[counter].top = tiles[counter].bottom = 0;
        for (int i = 0; i < 10; i++)
        {
            fgets(buffer, sizeof(buffer), f);
            {
                // printLine(buffer);
                // printf("%s", buffer);
                // ..##.#..#.
                if (i == 0)
                {
                    // set tiles[counter].top
                    for (int j = 9; j >= 0; j--)
                    {
                        tiles[counter].top <<= 1;
                        if (buffer[j] == '#')
                            tiles[counter].top |= 1;
                    }
                }
                if (i == 9)
                {
                    for (int k = 9; k >= 0; k--)
                    {
                        tiles[counter].bottomrev <<= 1;
                        if (buffer[k] == '#')
                            tiles[counter].bottomrev |= 1;
                    }
                }
                if (buffer[0] == '#')
                {
                    tiles[counter].leftrev |= (1 << i);
                // update tiles[counter].left
                }
                if (buffer[9] == '#')
                {
                // update tiles[counter].right
                    tiles[counter].right |= (1 << i);
                }
            }
            // fill the grid without edges
            if (i > 0 && i < 9)
            {
                for (int col = 1; col < 9; col++)
                {
                    tiles[counter].grid[i-1][col-1] = buffer[col];
                }
            }
        }
        tiles[counter].toprev = bitrev(tiles[counter].top);
        tiles[counter].bottom = bitrev(tiles[counter].bottomrev);
        tiles[counter].left = bitrev(tiles[counter].leftrev);
        tiles[counter].rightrev = bitrev(tiles[counter].right);
    }

    if (counter + 1 != NUMTILES)
    {
        printf("ERROR\n");
    }

    long answer = 1;
    for (int i = 0; i < counter+1; i++)
    {
        tiles[i].topn = adjacent(i, tiles[i].top);
        tiles[i].bottomn = adjacent(i, tiles[i].bottom);
        tiles[i].leftn = adjacent(i, tiles[i].left);
        tiles[i].rightn = adjacent(i, tiles[i].right);
        // printTile(tiles[i]);

        int totalNeighbours = 0;
        if (tiles[i].topn >= 0) totalNeighbours++;
        if (tiles[i].bottomn >= 0) totalNeighbours++;
        if (tiles[i].leftn >= 0) totalNeighbours++;
        if (tiles[i].rightn >= 0) totalNeighbours++;

        tiles[i].neighbours = totalNeighbours;
        //printf("%i: %i\n", tiles[i].num, tiles[i].neighbours);
        if (tiles[i].neighbours == 2)
        {
            // printf("%i\n", tiles[i].num);
            answer *= tiles[i].num;
        }
    }
    printf("Part 1: %li\n", answer); //20913499394191

    printf("layout.....\n");
    order();
    // printimage();

    // next step is to find the monsters
    //printpicture();

    // need to build the picture array

    int hashes = 0;
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            int need = layout[i][j];
            for (int k = 0; k < 8; k++)
            {
                char *tmp = tiles[need].grid[k];
                for (int l = 0; l < 8; l++)
                {
                    if (tmp[l] == '#') hashes++;
                    final[i*8+k][j*8+l] = tmp[l];
                }
            }
        }
    }

    //int mstr = checkmonsters();
    printf("MONSTERS?\n");
    //int monsters = checkmonsters2();
    int monsters = findamonster();
    if (monsters) printpicture();

    printf("Monsters: %i\n", monsters);
    int monsterhashes = 15;
    printf("Part 2: %i\n", hashes - (monsterhashes*monsters));
}


void printTile(TILE t)
{
    printf("Num:\t%i\nTop:\t%x %x\nRight:\t%x %x\nBottom:\t%x %x\nLeft:\t%x %x\n",
            t.num, t.top, t.toprev, t.right, t.rightrev,t.bottom, t.bottomrev, t.left, t.leftrev);

    printf("Neighbours: %i\n", t.neighbours);
    printf("Top: %i Right: %i Bottom: %i Left: %i\n", t.topn, t.rightn, t.bottomn, t.leftn);

}

void printLine(char *s)
{
    while (*s++)
    {
        if (*s == '.') printf("0");
        else printf("1");
    }
    printf("\n");
}

uint16_t bitrev(uint16_t n)
{
    uint16_t out = 0;
    for (int i = 0; i < 10; i++)
    {
        out <<= 1;
        if (n & 1)
            out |= 1;
        n >>= 1;
    }
    return out;
}

int adjacent(int ctr, uint16_t edge)
{

    for (int i = 0; i < NUMTILES; i++)
    {
        if (i == ctr)
        {
            continue;
        }
        if (edge == tiles[i].top || edge == tiles[i].toprev ||
            edge == tiles[i].bottom || edge == tiles[i].bottomrev ||
            edge == tiles[i].left || edge == tiles[i].leftrev ||
            edge == tiles[i].right || edge == tiles[i].rightrev)
            {
                return i;
            }
    }
    return -1;
}


// put the tiles into order
void order()
{
    // top left
    int tile;
    for (tile = 0; tile < NUMTILES; tile++)
    {
        if (tiles[tile].neighbours == 2)
        {
            layout[0][0] = tile;
            break;
        }
    }
    // we want the top/left to have no neighbours
    while (tiles[tile].leftn != -1 || tiles[tile].topn != -1)
    {
        if (!rotate(tile)) {printf("line335\n");return;}
    }


     // top row  to be put into loop from layout[0][1] to [0][NUMTILES-2]
    for (int c = 1; c < DIM-1; c++)
    {
        tile = tiles[layout[0][c-1]].rightn;
        layout[0][c]  = tile;
        while (tiles[tile].topn != -1)
        {
            if (!rotate(tile)) {printf("line346\n");return;}
        }
        if (tiles[tile].left != tiles[layout[0][c-1]].rightrev)
        {
            fliplr(tile);
        }
    }
    // top right corner
    tile = tiles[layout[0][DIM-2]].rightn;
    layout[0][DIM-1] = tile;
    while (tiles[tile].rightn != -1 || tiles[tile].topn != -1)
    {
        if (!rotate(tile)) {printf("line359\n");return;}

    }


    // from row 1 to end
    for (int r = 1; r < DIM; r++)
    {
        // special handling for the first tile in each row
        tile = tiles[layout[r-1][0]].bottomn;
        layout[r][0] = tile;

        while (tiles[tile].topn != layout[r-1][0])
        {
            if (!rotate(tile)) {printf("line370\n");return;}
        }

        if (tiles[tile].top != tiles[layout[r-1][0]].bottomrev)
        {
            fliplr(tile);
        }


        // other in row from [1][1] to [1][DIM-1]
        for (int t = 1; t < DIM; t++)
        {
            tile = tiles[layout[r][t-1]].rightn;
            // printf("checking...\n");
            // printf("layout[%i][%i]\n", r, t);
            layout[r][t] = tile;
            while (tiles[tile].topn != layout[r-1][t])
            {
                if (!rotate(tile)) {printf("line387\n");return;}

            }
            if (tiles[tile].left != tiles[layout[r][t-1]].rightrev)
            {
                fliplr(tile);
            }
        }
    }
}


void printgrid(int r, int c, char grid[r][c])
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}


void rotategrid(int r, int c, char grid[r][c])
{
    int newgrid[r][c];

    for (int row = 0; row < r; row++)
    {
        for (int col = 0; col < c; col++)
        {
            newgrid[c-1-col][row] = grid[row][col];
        }
    }
    for (int row = 0; row < r; row++)
    {
        for (int col = 0; col < c; col++)
        {
            grid[row][col] = newgrid[row][col];
        }
    }
}

void fliplrgrid(int r, int c, char grid[r][c])
{
    for (int row = 0; row < r; row++)
    {
        for (int col = 0; col < c/2; col++)
        {
            int newpos = c - 1 - col;
            char temp = grid[row][col];
            grid[row][col] = grid[row][newpos];
            grid[row][newpos] = temp;
        }
    }
}

void fliptbgrid(int r, int c, char grid[r][c])
{
    for (int row = 0; row < r/2; row++)
    {
        for (int col = 0; col < c; col++)
        {
            int newpos = r - 1 - row;
            char temp = grid[row][col];
            grid[row][col] = grid[newpos][col];
            grid[newpos][col] = temp;
        }
    }
}

// r>t  b>r l>b t>l  //anti-clockwise
bool rotate(int tile)
{
    // printf("rotating from...\n");
    // printTile(tiles[tile]);
    // printf("BEFORE ROTATE:\n");
    // printgrid(8,8,tiles[tile].grid);
    //printf("rotating %i ... ", tile);
    if (tile == -1)
    {
        printf("ERROR! TILE -1\n");
        printf("TILE ERROR: \n");
        printTile(tiles[tile]);
        return false;
    }

    TILE t = tiles[tile];
    tiles[tile].top = t.right;
    tiles[tile].toprev = t.rightrev;
    tiles[tile].topn = t.rightn;

    tiles[tile].right = t.bottom;
    tiles[tile].rightrev = t.bottomrev;
    tiles[tile].rightn = t.bottomn;

    tiles[tile].bottom = t.left;
    tiles[tile].bottomrev = t.leftrev;
    tiles[tile].bottomn = t.leftn;

    tiles[tile].left = t.top;
    tiles[tile].leftrev = t.toprev;
    tiles[tile].leftn = t.topn;

    rotategrid(8,8,tiles[tile].grid);

    // printf("Rotated to:");
    // printTile(tiles[tile]);

    // printf("AFTER ROTATE:\n");
    // printgrid(8,8,tiles[tile].grid);
    return true;


}
// flip left to right
bool fliplr(tile)
{
    // printf("flipping from...\n");
    // printTile(tiles[tile]);
    TILE t = tiles[tile];
    tiles[tile].left = t.rightrev;
    tiles[tile].leftrev = t.right;
    tiles[tile].leftn = t.rightn;

    tiles[tile].right = t.leftrev;
    tiles[tile].rightrev = t.left;
    tiles[tile].rightn = t.leftn;

    tiles[tile].top = t.toprev;
    tiles[tile].toprev = t.top;
    tiles[tile].bottom = t.bottomrev;
    tiles[tile].bottomrev = t.bottom;

    fliplrgrid(8,8, tiles[tile].grid);

    // printf("AFTER FLIP:\n");
    // printgrid(8,8,tiles[tile].grid);
    return true;

}

// passing the corners
void place(int ctr)
{
    printf("t: %i r: %i l: %i b: %i\n", tiles[ctr].topn, tiles[ctr].rightn,
        tiles[ctr].leftn, tiles[ctr].bottomn);
}


void printimage()
{
    printf("\n*****FINAL IMAGE*****\n");
    for (int i = 0; i < DIM; i++)
    {
        printf("ROW %i\n", i);
        for (int j = 0; j < DIM; j++)
        {
            printf("Index: %i\n", layout[i][j]);
            //printTile(tiles[layout[i][j]]);
            //printgrid(8,8,tiles[layout[i][j]].grid);
        }
        printf("\n");
    }
    printf("\n");
}

void printpicture()
{
   for (int i = 0; i < DIM * 8; i++)
    {
        for (int j = 0; j < DIM *8; j++)
        {
            printf("%c", final[i][j]);
        }
        printf("\n");
    }
}



int checkmonsters()
{
    int monsters=0;
    for (int r = 0; r < 4; r++)
    {
        for (int flip = 0; flip < 2; flip++)
        {
            // printf("checking for monsters on %i %i\n", r, flip);
            monsters += findamonster();

            rotategrid(DIM*8, DIM*8, final);
            // printgrid(DIM*8, DIM*8, final);
        }
        fliplrgrid(DIM*8, DIM*8, final);
    }
    return monsters;

    //return 0;
}


int checkmonsters2()
{
    int monsters=0;
    for (int i = 0; i < 2; i++)
    {
        monsters += findamonster();
        fliplrgrid(DIM*8, DIM*8, final);
        monsters += findamonster();
        fliptbgrid(DIM*8, DIM*8, final);
        monsters += findamonster();
        fliplrgrid(DIM*8, DIM*8, final);
        monsters += findamonster();
        rotategrid(DIM*8, DIM*8, final);
    }
    return monsters;
}

int findamonster()
{
    int monsters = 0;
    for (int i = 0; i < DIM * 8 - 2; i++)
    {
        for (int j = 0; j < DIM * 8 - 17; j++)
        {
           //  printf("checking row %i starting at col %i\n", i, j);
            if (
                final[i][j+19] == '#' &&
                final[i+1][j+1] =='#' &&
                final[i+1][j+6] =='#' &&
                final[i+1][j+7] =='#' &&
                final[i+1][j+12] =='#' &&
                final[i+1][j+13] =='#' &&
                final[i+1][j+18] =='#' &&
                final[i+1][j+19] =='#' &&
                final[i+1][j+20] =='#' &&
                final[i+2][j+2] =='#' &&
                final[i+2][j+5] =='#' &&
                final[i+2][j+8] =='#' &&
                final[i+2][j+11] =='#' &&
                final[i+2][j+14] =='#' &&
                final[i+2][j+17] == '#')
                {

                    // printf("found at %i %i\n", i, j);
                    monsters++;
                    final[i][j+19] =
                    final[i+1][j+1] =
                    final[i+1][j+6] =
                    final[i+1][j+7] =
                    final[i+1][j+12] =
                    final[i+1][j+13] =
                    final[i+1][j+18] =
                    final[i+1][j+19] =
                    final[i+1][j+20] =
                    final[i+2][j+2] =
                    final[i+2][j+5] =
                    final[i+2][j+8] =
                    final[i+2][j+11] =
                    final[i+2][j+14] =
                    final[i+2][j+17] = '0';
                }
        }
    }
    return monsters;
}

