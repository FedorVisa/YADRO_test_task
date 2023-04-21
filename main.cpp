#include <iostream>
#include "game_club.h"
int main(int argc, char *argv[]) {
try {
    game_club club;
    string filename;
    club.input_from_file("input.txt");
   // club.input_from_file(argv[1]);
    club.revenue_calculation();
    return 0;
} catch ( const myException& e){
    cout << "Error occurred: " << e.what() << endl;
    return 0;
} catch (const exception& e){
    cout << "Some error occurred " << e.what() <<  endl;
    return 0;
}
}
