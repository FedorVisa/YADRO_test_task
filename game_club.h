//
// Created by Kotozzavrik on 18.04.2023.
//
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <deque>
#include "myException.cpp"


#ifndef YADRO_GAME_CLUB_H
#define YADRO_GAME_CLUB_H

using namespace std;

class game_club {
private:
    class actions{
    private:
        int time;
        int action_id;
        int table_number;
        string name;
    public:
        actions() {table_number = 0;}
        actions(int time, int id, string name) :time(time), action_id(id), name(name){}
        void set_table_number(int number){ this->table_number = number;}
        void set_time(int time)   { this->time = time;}
        void set_action_id(int id){ this->action_id = id;}
        void set_name(string name){ this->name = name;}

        int get_time() const { return time; }
        int get_action_id() const { return action_id; }
        int get_table_number() const { return table_number; }
        const string &get_name() const { return name; }


        friend ostream& operator << ( ostream& os, const actions& act){
            time_to_format(act.get_time());
            os << " " << act.get_action_id() << " " << act.get_name();
            if(act.table_number != 0) os << " " << act.get_table_number();
            os << endl;
            return os;
        }


    };
    int number_of_tables, cost_for_hour, open_time, close_time;
    vector < int > events {1, 2, 3, 4, 11, 12, 13};
    vector < actions > logs;
    set <string> clients;
    vector <string> tables;
    deque <string> queue;
    // table num time
    multimap< int, int > margin;
    vector <int> rubles;

public:
    game_club() {}
    game_club(int n_tables, int cost, int open, int close, int input_size)
            : number_of_tables(n_tables), cost_for_hour(cost), open_time(open), close_time(close)
    {}

    int get_number_of_tables() const { return number_of_tables; }
    int get_cost_for_hour() const { return cost_for_hour; }
    int get_open_time() const { return open_time; }
    int get_close_time() const { return close_time; }

    void set_number_of_tables(int n) { this->number_of_tables = n; }
    void set_cost_for_hour(int cost) { this->cost_for_hour = cost; }
    void set_open_time(int open)     { this->open_time = open; }
    void set_close_time(int close)   { this->close_time = close; }

    void input_from_file(const string filename);
    static void time_to_format( int time );
    void revenue_calculation();
    void id_event( actions& action);
    void output_cost_hours();
};


#endif //YADRO_GAME_CLUB_H
