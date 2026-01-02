#include "Game.hpp"
#include <iostream>
using namespace std;

//TODO: define default constructor of Game class.
Game::Game() : area(7,2) {}

//TODO: define non-default constructor of Game class.
Game::Game(int size, int num_mines) : area(size, num_mines) {}

//TODO: Ensure users to enter a cell index in [0, size).
//      return the input number.
//ensure to enter a valid index num whose cell is not checked yet, return num.
//Hint: which method of area to call to find out whether a cell in it is checked or not?
//Here are the steps.
//First, print "Please choose a cell (the first starts from 0): "
//and input an int for num from console.
//Keep asking for input num as long as num is 
//not in [0, size) or the corresponding cell is
//checked, where size is the capacity of data member area.
//begin
//    If num is out of range, that is, not in [0, size), 
//    prompt "Enter an integer in [0, size-1]: ",
//    replace size-1 by the actual value of 
//    given parameter size in this method.
//    Otherwise, the cell must be checked (why??), prompt 
//    "Cell … is already chosen. Please re-enter: ", 
//    where … is the value of num
//
//    Re-enter num
//end
//return num
int Game::input() const {
    int index;

    while (true) {
        cout << "Please choose a cell (the first starts from 0): \n";
        cin >> index;
        if (index < 0 || index >= area.get_size()) {
            cout << "Enter an integer in the interval [0, " << area.get_size() - 1 << "]: \n";
        } else if (area.is_checked(index)) {
            cout << "Cell " << index << " is already chosen. Please re-enter: ";
        } else {
            return index;
        }
    }
}

//TODO: code to show how to play a game. 
//Star with an empty layout of field,
//keep choosing a valid index for an unchecked cell 
//until one of the following happens.
//(a) A cell with a mine is chosen, 
//    in that case, print "Mine explodes! Game ends."
//(b) All cells without mines are found out, 
//    in that case, print 
//    "Congratulations! Find out all the cells without mines."
//(c) After the game, print the layout of fields 
//    where mines are marked as * 
//    and nonmines are marked by its number of neighbor(s).
void Game::play() {
    // start with empty layout
    cout << area.empty_layout_string();
    int available_slots = area.get_size() - area.get_num_mines();
    // while (num_mines > 0)
    while (available_slots > 0) {
        int index = input();

        if (area.has_mine(index)) {
            cout << "Mine explodes! Game ends.\n";
            break;
        } else {
            area.mark_checked(index);
            available_slots--;
            cout << area.to_string();
        }
    }

    if (available_slots == 0) cout << "Congratulations! Find out all the cells without mines.\n";
    cout << area.answer_string();
}   
