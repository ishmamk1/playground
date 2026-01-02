#include "Field.hpp"
#include <iostream>

using namespace std;

int main() {
    // Test the default constructor
    Field f1;
    cout << "Default field size: " << f1.get_size() << endl;
    cout << "Default number of mines: " << f1.get_num_mines() << endl;
    cout << "Default field layout:" << endl;
    cout << f1.to_string() << endl;

    // Test the non-default constructor
    Field f2(10, 4);
    cout << "Custom field size: " << f2.get_size() << endl;
    cout << "Custom number of mines: " << f2.get_num_mines() << endl;
    cout << "Answer layout (with mines):" << endl;
    cout << f2.answer_string() << endl;

    // Check individual cells
    cout << "Cell 0 has mine? " << (f2.has_mine(0) ? "yes" : "no") << endl;
    cout << "Neighbor mines near cell 0: " << f2.neighbor_mines(0) << endl;

    // Mark a cell as checked
    f2.mark_checked(0);
    cout << "Cell 0 is checked? " << (f2.is_checked(0) ? "true" : "false") << endl;

    // Print the visible layout (to_string)
    cout << "Visible layout:" << endl;
    cout << f2.to_string() << endl;

    return 0;
}