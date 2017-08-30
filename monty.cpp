#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <math.h>

//global variables
const int num_games = 10000000;

//Function: get a random integer between 1 and max (inclusive)
int getrand(int max){
  return (max*double(std::rand()))/(RAND_MAX)+1;
}

//returns the door number that is neither door_1 nor door_2
int other_door(int door_1, int door_2){
  if (door_1 == door_2) //check for quantum indeterminacy
    return 0;
  switch(door_1+door_2){ //simplified Look Up Table
    case 5:
      return 1;
    case 4:
      return 2;
    case 3:
      return 3;
    default:
      return 0; //error
  }
}

//returns the door number that monty opens
int monty(int winner, int choice){
  //if player chose the winning door
  if(winner == choice)
    return (winner + getrand(2) - 1) % 3 + 1; //reveal other door at random
  //else player chose a loosing door
  return other_door(winner, choice);
}

/* Function: play the game
* Car is stored behind a door at random.
* Player picks door at random.
* Monty picks a door to discard.
* If stay == false, switch player choice.
* Return true if player picked the correct door.
*/
bool play(bool stay){
  int const winning_door = getrand(3); //car is placed behind a random door
  int player_choice = getrand(3); //player chooses a random door

//monty opens a door
  int open_door = monty(winning_door, player_choice);

//player switches doors if not staying with current choice
  if (!stay){
    player_choice = other_door(player_choice, open_door);
  }

  if (winning_door == player_choice)
    return true;

  return false;
}


int main(){

  //initialize random number generator srand
  std::srand(std::time(NULL));

  /* Simple Solution
  * Assume Monty Hall chooses the door to be discarded at random.
  * Assume switching must be defined before playing.
  */

  //play the game (call)

  //never switch doors
  int switch_wins = 0;
  for(int i = 0; i < num_games; i++){
    bool win = play(false);
    if(win)
      switch_wins++;
  }

  //always stay
  int stay_wins = 0;
  for(int i = 0; i < num_games; i++){
    bool win = play(true);
    if(win)
      stay_wins++;
  }

  //calculate percent wins
  double per_switch, per_stay = 0.0;
  per_switch = double(switch_wins)/num_games*100;
  per_stay = double(stay_wins)/num_games*100;

  //print comparison
  std::cout << std::scientific << std::setprecision(1);
  std::cout << std::endl << "For " << double(num_games) << " games played:" << std::endl;
  std::cout << std::fixed << std::setprecision(3);
  std::cout << "Switching resulted in " << switch_wins << " wins ";
  std::cout << "(~" << per_switch << "%)" << std::endl;
  std::cout << "Staying resulted in " << stay_wins << " wins ";
  std::cout << "(~" << per_stay << "%)" << std::endl << std::endl;

  return 0;
}
