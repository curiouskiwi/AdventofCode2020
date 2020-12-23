// Advent of Code - Day 22
// @curiouskiwi @gary_anderson
// 22 Dec 2020


#include <stdio.h>
#include <stdbool.h>

 #define NUMCARDS 50
// #define NUMCARDS 10

typedef struct deck
{
    int front;
    int rear;
    int itemcount;
    int cards[NUMCARDS];
}
DECK;

// DECK player[2] =   {{0, NUMCARDS/2 - 1, NUMCARDS/2, {9, 2, 6, 3, 1}},
//                     {0, NUMCARDS/2 - 1, NUMCARDS/2, {5, 8, 4, 7, 10}}
//                     };

DECK player[2] =
    {
    {0, NUMCARDS/2 - 1, NUMCARDS/2, {26,16,33,8,5,46,12,47,39,27,50,10,34,20,23,11,43,14,18,1,48,28,31,38,41}},
    {0, NUMCARDS/2 - 1, NUMCARDS/2, {45,7,9,4,15,19,49,3,36,25,24,2,21,37,35,44,29,13,32,22,17,30,42,40,6}}
    };

int gameplayed = 0;

DECK *playgame(DECK *a, DECK *b);
void insert(int data, DECK *d);
int playCard(DECK *d);
bool isEmpty(DECK *d);
bool isFull(DECK *d);
int size(DECK *d);
int look(DECK *d, int n);



int main(void)
{
    DECK *winner = playgame(player, player+1);

    int score = 0;
    for (int i = NUMCARDS; i > 0; i--)
    {
        score += playCard(winner) * i;
    }

    printf("Part 2: %i\n", score);

}



DECK *playgame(DECK *one, DECK *two)
{
    gameplayed++;




    int lastvisited[NUMCARDS][NUMCARDS] = {0};
    int currentrepeat = -1;
    int repeatrun = 0;
    int rounds_played = 0;
    int repeatlen = 0;

    while (!(isEmpty(one) || isEmpty(two)))
    {
         rounds_played++;
        // this is a cheating way to avoid infinite loop... test larger numbers until they return the same
        // if (rounds_played >800)        {
        //     return one;
        // }

        int a = playCard(one);
        int b = playCard(two);
     
        if (lastvisited[a-1][b-1])
        {
            int thisrepeat = rounds_played - lastvisited[a-1][b-1];
            if (thisrepeat > repeatlen)
            {
                repeatrun = 0;
                repeatlen = thisrepeat;
            }
            else
            {
                repeatrun++;

                if (repeatrun == repeatlen)
                {
                    // printf("ENDING! (%i) rounds: %i\n", repeatrun, rounds_played);
                    return one;
                }
            }

        }
            lastvisited[a-1][b-1] = rounds_played;
        if (rounds_played==999) printf("Run=%d, Len=%d\n", repeatrun, repeatlen);

        // Do we need to play Recursive Combat?
        if (size(one) >= a && size(two) >= b)
        {
            // create new decks for game
            DECK newone, newtwo;
            newone.front = 0;
            newone.rear = a - 1;
            newone.itemcount = a;
            for (int i = 0; i <  a; i++)
            {
                newone.cards[i] = look(one, i);
            }
            newtwo.front = 0;
            newtwo.rear = b - 1;
            newtwo.itemcount = b;
            for (int i = 0; i <  b; i++)
            {
                newtwo.cards[i] = look(two, i);
            }
            // give winner the cards with winner's card first
            if (playgame(&newone, &newtwo) == &newone)
            {
                insert(a, one);
                insert(b, one);
            }
            else
            {
                insert(b, two);
                insert(a, two);
            }
        }

    // we aren't being recursive!
       else
        {
            if (a > b)
            {
                insert(a, one);
                insert(b, one);
            }
            else
            {
                insert(b, two);
                insert(a, two);
            }
        }

    }
    // calculate winner score
    DECK *winner = isEmpty(two) ? one : two;

    return winner;
}


void insert(int data, DECK *d)
{

   if(!isFull(d))
   {

      if(d->rear == NUMCARDS-1)
      {
         d->rear = -1;
      }

      d->cards[++d->rear] = data;
      d->itemcount++;
   }
}

int playCard(DECK *d)
{
   int data = d->cards[d->front++];

   if(d->front == NUMCARDS)
   {
      d->front = 0;
   }

   d->itemcount--;
   return data;
}
// n is the number past the front
int look(DECK *d, int n)
{
  return d->cards[(d->front + n)%NUMCARDS];
}

bool isEmpty(DECK *d)
{
   return d->itemcount == 0;
}

bool isFull(DECK *d)
{
  return d->itemcount == NUMCARDS;
}

int size(DECK *d)
{
   return d->itemcount;
}
