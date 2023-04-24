#include "game_club.h"
#include <regex>
#include <algorithm>

using namespace std;


void game_club::input_from_file(const string filename) {
    ifstream in(filename);

    if(!in.is_open()){
        cerr << "File does not exists";
        throw myException(myException::ExceptionType::FileNotFound);
    }
        in >> this->number_of_tables;
        if(number_of_tables < 1 ){
            cerr << "Yours input is: "<< number_of_tables << endl;
            throw myException(myException::ExceptionType::WrongValue);
        }
        in.ignore();

        int time_hours, time_minutes;
        int close_hours, close_minutes;
        char delimiter;
        in >> time_hours >> delimiter >> time_minutes >> close_hours >> delimiter >> close_minutes;
        if (time_hours > 23 || time_minutes > 59 || time_hours < 0 || time_minutes < 0 ) {
            cerr << "Yours input is: "<< time_hours << ":" << time_minutes << endl;
            throw myException(myException::ExceptionType::ExceededMaxValue);
        }
        //sum_time = time_hours * 60 + time_minutes;
        set_open_time(time_hours * 60 + time_minutes);

        if (close_hours > 23 || close_minutes > 59 || close_hours < 0 || close_minutes < 0 ) {
            cerr << "Yours input is: "<< close_hours << ":" << time_minutes << endl;
            throw myException(myException::ExceptionType::ExceededMaxValue);
        }
        set_close_time(close_hours * 60 + close_minutes);
        in >> this->cost_for_hour;
        if(cost_for_hour <= 0 ){
            cerr << "Yours input is: "<< cost_for_hour << endl;
            throw myException(myException::ExceptionType::WrongValue);
        }
        in.clear();

        string line;
        int id, table_num;
        int sum_time = -1;
        string name;
        actions action;
        //clients names should pass this pattern a..z, 0..9,_, -
        regex pattern("^[a-z0-9_-]+$");

        while (in >> time_hours >> delimiter >> time_minutes >> id >> name ) {
            table_num = 0;
            if (time_hours > 23 || time_minutes > 59 || time_hours < 0 || time_minutes < 0 ) {
                cerr << "Yours input is: "<< time_hours << ":" << time_minutes << endl;
                throw myException(myException::ExceptionType::ExceededMaxValue);
            }
            if( sum_time > time_hours * 60 + time_minutes && sum_time!= -1 ) {
                cerr << "Yours input is: "<< time_hours << ":" << time_minutes << endl;
                throw myException(myException::ExceptionType::WrongOrder);
            }
                sum_time = time_hours * 60 + time_minutes;
                action.set_time(sum_time);

            if( !events.contains(id)){
                cerr << "Yours input is: " << id << endl;
                throw myException(myException::ExceptionType::WrongId);
            }
            action.set_action_id(id);

            if(regex_match(name, pattern))action.set_name(name);
            else{
                cerr << "Yours input is: "<< name << endl;
                throw myException(myException::ExceptionType::WrongName);

            }
            if( id == 2 ){
                in >> table_num;
                if( table_num > number_of_tables ){
                    cerr << "Yours input is: " << id << endl;
                    throw myException(myException::ExceptionType::WrongTableNum);
                }
                action.set_table_number(table_num);
            } else action.set_table_number(table_num);
            logs.push_back(action);
        }
        in.close();

}




void game_club::id_event( actions& action ){
    switch(action.get_action_id()){

        case 1:
            cout << action;
            if(action.get_time() < open_time || action.get_time() > close_time){
                action.set_action_id(13);
                action.set_name("NotOpenYet");
                action.set_table_number(0);
                cout << action;
                break;
            }
            if(clients.contains(action.get_name())){
                action.set_action_id(13);
                action.set_name("YouShallNotPass");
                action.set_table_number(0);
                cout << action;
            }
            clients.insert(action.get_name());
            break;

        case 2:
            cout << action;
            if(tables[action.get_table_number() - 1] == " "){
                tables[action.get_table_number() - 1] = action.get_name();
                clients.insert(action.get_name());
                margin.insert(pair< int, int> (action.get_table_number(), action.get_time()*-1));
            }
            else{
                action.set_action_id(13);
                action.set_name("PlaceIsBusy");
                action.set_table_number(0);
                cout << action;
            }
            break;

        case 3:
            cout << action;
            clients.insert(action.get_name());
            if(find(tables.begin(), tables.end(), " ") != tables.end()){
               // queue.push_back(action.get_name());
                action.set_action_id(13);
                action.set_name("ICanWaitNoLonger");
                cout << action;
            }
            else{
                queue.push_back(action.get_name());
            }
            if(queue.size() > tables.size()){
                action.set_action_id(4);
                cout << action;
                clients.erase(action.get_name());
                queue.pop_back();
            }
            break;

        case 4:
            cout << action;
            if(!clients.contains(action.get_name())){
                action.set_action_id(13);
                action.set_name("ClientUnknown");
                action.set_table_number(0);
                cout << action;
            }
            else{
                if(!queue.empty()){
                    action.set_action_id(12);
                    auto tn = find(tables.begin(), tables.end(), action.get_name());
                    int tbl = distance(tables.begin(), tn) + 1;
                    replace(tables.begin(), tables.end(), action.get_name(), queue.front());
                    clients.erase(action.get_name());
                    action.set_name(queue.front());
                    queue.pop_front();
                    action.set_table_number(tbl);
                    margin.insert(pair< int, int>(action.get_table_number(),action.get_time()));
                    margin.insert(pair< int, int>(action.get_table_number(),action.get_time()*-1));
                    cout << action;
                } else{
                    int a = action.get_table_number();
                    string b = action.get_name();
                }
                if(action.get_action_id() !=12) {
                    auto tn = find(tables.begin(), tables.end(), action.get_name());
                    int tbl = distance(tables.begin(), tn) + 1;
                    action.set_table_number(tbl);
                    margin.insert(pair< int, int>(action.get_table_number(),action.get_time()));
                    clients.erase(action.get_name());
                    tables[action.get_table_number() - 1] = " ";
                }
            }
            break;
    }
}


void game_club::revenue_calculation(){

        tables.resize(number_of_tables, " ");
        rubles.resize(number_of_tables,0);
        tools::time_to_format(open_time);
        cout << endl;

        for( auto i =0; i < logs.size(); i++){
            id_event(logs[i]);
        }

        actions tmp;
        for(auto i = 0; i < tables.size(); i++){
            if( tables[i] != " "){
                tmp.set_time(close_time);
                tmp.set_name(*clients.begin());
                margin.insert(pair< int, int>( i+1 ,tmp.get_time()));
                clients.erase(clients.begin());
                tmp.set_action_id(11);
                tables[i] = " ";
                cout << tmp;
            }
        }

        int sum;
        int cost_for_session;
        vector <int> time_for_session(number_of_tables,0);

        for(auto it = margin.begin(); it != margin.end(); it = margin.upper_bound(it->first)){
            int key = it->first;
            auto range = margin.equal_range(key);
            for(auto i = range.first; i != range.second; i++){
                if(std::next(i) == range.second) break;
                sum = i->second + std::next(i)->second;
                time_for_session.at(key-1) += sum;
                cost_for_session = sum / 60;
                if( sum%60 != 0) cost_for_session++;
                rubles[key-1] += cost_for_session * cost_for_hour;
            }
        }
        tools::time_to_format(close_time);
        cout << endl;

        for (int i = 0; i < number_of_tables; ++i) {
            cout << i+1 << " " << rubles[i] << " ";
            tools::time_to_format(time_for_session.at(i));
            cout << endl;
        }
};



