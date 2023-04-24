#include "tools.h"

using namespace std;

    void tools::time_to_format( int time ){
        string output_hours, output_minutes;
        output_hours = to_string(time/60);
        if(time/60 <10 ) output_hours = "0" + output_hours;
        output_minutes = to_string(time%60);
        if(time%60 <10 ) output_minutes = "0" + output_minutes;
        cout << output_hours << ":" << output_minutes;
    }
