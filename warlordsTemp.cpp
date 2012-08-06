/*
Christopher Pierce
Warlords game
Written 08/01/2012
Last Modified 08/01/2012
Game pits zues vs poseidon vs hades in a 
pokemon-like text based fighter game
*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;

struct  warlord
{
  string name;
  string type;
  string weakness;
  unsigned int attackDamage;
  unsigned int defenceValue;
  int totalHealth;
  int currentHealth;
  bool isTurn;
} zues, poseidon, hades, chosen, challenger;

//functions for the player to use
//offence
int attack(warlord chosen, warlord challenger, int weakMultiplier)
  {
      if(challenger.weakness == chosen.type){ weakMultiplier = 2; }
      else weakMultiplier = 1;
      
      return(((chosen.attackDamage - challenger.defenceValue) * weakMultiplier) + (rand() % 6));
  }

//defence
int defend(warlord &chosen, warlord &challenger, int weakMultiplier)
  {
      if (chosen.defenceValue > 10) { return 0; }
      else chosen.defenceValue += 1;
     
      return(0);
  }

//what the player can do, and what happens next
int chooseMenu(int selection, int weakMultiplier, warlord &chosen, warlord &challenger)
  {
    if(selection == 1)
      {
        cout << "You did: " << attack(chosen, challenger, weakMultiplier);
        cout <<" Damage to " << challenger.name << endl;
        challenger.currentHealth -= attack(chosen, challenger, weakMultiplier);
      }
    else if (selection == 2)
      {
        defend(chosen, challenger, weakMultiplier);
        cout << chosen.name << "'s defence value is: " << chosen.defenceValue << endl;
      }
    else if (selection == 3)
      { 
        cout << "You forfit. That means your both a coward, and a loser. I'm sure your mother is proud. \n";
        exit(0); 
      }
    else cout << "You didnt enter a 1 or a 2 or a 3! Bad user!!! you should go cry in shame! " << endl;
  }
  //end of player's functions


//begining of "ai's" functions
int challengersChoice(int aiSelection, int weakMultiplier, int aiDamageDone, warlord &chosen, warlord &challenger) 
  {
    //call to random to give 0 or a 1.
    aiSelection = rand() % 2;
    cout << "The computer decided to: ";
    if(aiSelection == 0)
      {
        cout << " Attack \n";
        aiDamageDone = (((chosen.currentHealth -= (challenger.attackDamage - chosen.defenceValue)) * weakMultiplier) + (rand() %6));
        cout << challenger.name << " did " << aiDamageDone << " damage " << "to: " << chosen.name << endl;
        return(aiDamageDone);
      }
    else if(aiSelection == 1) 
      {
        cout << " Defend \n"; 
        cout << " Computer's defence value is: " << challenger.defenceValue << endl;
        if(challenger.defenceValue > 10) 
          {
            return 0;
          }
        else return(challenger.defenceValue += 1);
      }  
    else cout <<"challengersChoice() messed up somehow.. \n";
  }
//end of the "ai's" functions


int main()
{
  int weakMultiplier=0;
  int warlordSelection=0;
  int selection=0;
  int aiSelection=0;
  int aiDamageDone=0;  
  int random = rand() % 6;
  bool isValid=0;
   

  warlord();

  warlord zues;
  zues.name="zues";
  zues.type="electric";
  zues.weakness="fire";
  zues.attackDamage=27;
  zues.defenceValue=8;
  zues.totalHealth=500; 
  zues.currentHealth=500;
  zues.isTurn=0;
 
  warlord poseidon;
  poseidon.name="poseidon";
  poseidon.type="water";
  poseidon.weakness="electric";
  poseidon.attackDamage=23;
  poseidon.defenceValue=4;
  poseidon.totalHealth=620;
  poseidon.currentHealth=620; 
  poseidon.isTurn=0;  

  warlord hades; 
  hades.name="hades";
  hades.type="fire";
  hades.weakness="water";
  hades.attackDamage=29;
  hades.defenceValue=3;
  hades.totalHealth=570;
  hades.currentHealth=670;
  hades.isTurn=0;

  warlord choosen;
  chosen.name=" ";
  chosen.type=" ";
  chosen.weakness=" ";
  chosen.attackDamage=0;
  chosen.defenceValue=0;
  chosen.totalHealth=0;
  chosen.currentHealth=0; 
  chosen.isTurn=0;

  warlord challenger;
  challenger.name=" ";
  challenger.type=" ";
  challenger.weakness=" ";
  challenger.attackDamage=0;
  challenger.defenceValue=0;
  challenger.totalHealth=0;
  challenger.currentHealth=0;
  challenger.isTurn=0;

  
  cout << "Welcome to warlords. Please select your character. 1 for Zues, 2 for Poseidon, and 3 for Hades.\n" 
       << "Anthing else is garbage, and you will be yelled at for inputting garbage.\n";
 
  
 checkWarlordSelection:

  cin >> warlordSelection;
  do
    {
      if(warlordSelection == 1)
        { 
         cout << "You chose Zues.\n";
         chosen = zues;
         chosen.isTurn = 1;
         challenger = poseidon;
         isValid=1;
        }
      else if(warlordSelection == 2) 
        {
          cout << "You chose Poseidon. \n";
          chosen = poseidon;
          chosen.isTurn = 1;
          challenger = hades;
          isValid=1;
        } 
      else if(warlordSelection == 3) 
        {
          cout << "You chose Hades. \n";
          chosen = hades;
          chosen.isTurn = 1;
          challenger = zues;
          isValid=1;
        }
      else 
        {
          cout << "You didnt enter in a 1 or a 2 or a 3. you didnt follow instructions. Bad user! \n";
          cout << "Please select your character. 1 for zues, 2 for Poseidon, and 3 for Hades.\n"
               << "Anthing else is garbage, and you will be yelled at for inputting garbage.\n";
          isValid = 0;
          //goto checkWarlordSelection;
        }
     }  
     while(!isValid);
  
  cout << "Type: " << chosen.type << " Weakness: " << chosen.weakness << endl; 
  cout << "Attack: " << chosen.attackDamage << " Defence value: " << chosen.defenceValue << endl;
  cout << "Total Health: " << chosen.totalHealth << " currentHealth " << chosen.currentHealth << endl; 
  cout << endl;
 
  cout << "Your challenger today is: " << challenger.name << endl;

  //control loop so the warlords fight to the death! 
  do
  {  
    cout << "It's your turn! Enter 1 to attack, 2 to defend, or 3 to give up! " << endl;
    cin >> selection;
    cout << endl;

    if(selection > 0 && selection < 4) {isValid=1; }
    else isValid=0;   

    chooseMenu(selection, weakMultiplier, chosen, challenger);
    cout << "Enemy " << challenger.name << " has only: " << challenger.currentHealth << " health remaining! " << endl;
    challengersChoice(aiSelection, weakMultiplier, aiDamageDone, chosen, challenger);
    cout << "Your warlord: " << chosen.name << " has only: " << chosen.currentHealth << " health remaining! " << endl;
 
  }
  while(chosen.currentHealth > 0 && challenger.currentHealth > 0);
  
  if(challenger.currentHealth <= 0) { cout << "You win! Congradulations." << endl; }
  else cout << "You were born a looser, and now you have gone and earned your reputation. " << "GAME OVER " << endl;

  return 0;
}



