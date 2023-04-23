#include <iostream>
#include "game_club.h"
int main(int argc, char *argv[]) {
try {
    game_club club;
    std::string filename;
    //club.input_from_file("input.txt");
    club.input_from_file(argv[1]);
    club.revenue_calculation();
    return 0;
} catch ( const myException& e){
    std::cerr << "Error occurred: " << e.what() << std::endl;
    return 0;
} catch (const std::exception& e){
    std::cerr << "Some error occurred: " << e.what() <<  std::endl;
    return 0;
}
}
