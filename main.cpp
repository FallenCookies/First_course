#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <exception>
#include <algorithm>
#include <iomanip>
using namespace std;
class Date {
public:
    Date(int year,int month, int day){
        Year=year;
        Month=month;
        Day=day;
    }
    int GetYear() const{
        return Year;
    }
    int GetMonth() const{
        return Month;
    }
    int GetDay() const{
        return Day;
    }

private:
    int Year,Month,Day;
};

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear()<rhs.GetYear()) {
        return true;
    }else{
        if(lhs.GetYear()>rhs.GetYear())
            return false;
        if(lhs.GetMonth()<rhs.GetMonth())
            return true;
        else{
            if(lhs.GetMonth()>rhs.GetMonth())
                return false;
            if(lhs.GetDay()<rhs.GetDay())
                return true;
            else{
                return false;
            }
        }
    }
}

ostream& operator << (ostream &s, const Date &d) {
    s <<d.GetYear()<<'-'<<d.GetMonth()<<'-'<<d.GetDay();
    return s;
}
bool cmp(const string& lhs,const string& rhs){
    return lhs<rhs;
}
class Database {
public:
    void AddEvent(const Date& date, const string& event){
        try {
        for (const auto &item:map1.at(date)) {
            if (item == event)
                return;
        }
        map1[date].push_back(event);
        sort(begin(map1.at(date)),end(map1.at(date)));
        }
        catch(exception& e){
            map1[date].push_back(event);
        }
    }

    bool DeleteEvent(const Date& date, const string& event){
        try {
            for (ptrdiff_t i = 0; i < map1.at(date).size(); i++) {
                if (map1.at(date)[i] == event) {
                    map1.at(date).erase(map1.at(date).begin() + i);
                    cout << "Deleted successfully" <<endl;
                    if(map1.at(date).empty()){
                        map1.erase(date);
                    }
                    return true;
                }
            }
        }catch (exception& e) {
            cout << "Event not found" << endl;
            return false;
        }
        cout << "Event not found" << endl;
        return false;
    }
    int  DeleteDate(const Date& date){
        int count=0;
        try {
            count = map1.at(date).size();
            map1.at(date).clear();
        }catch (exception& e){
            return count;
        }
        return count;

    }
    void Find(const Date& date) const  {
        try {
            if (!map1.at(date).empty()) {
                for (const auto &item:map1.at(date)) {
                    cout << item <<endl;
                }
            }
        }catch (exception& e){

        }
    }
    Date Check_Date(const string& date){
        bool otric=false;
        int tmp_day=0,tmp_month=0,tmp_year=0;
        stringstream ss;
        ss<<date;
        ss>>tmp_year;
        ss.ignore();
        if(!isdigit(ss.peek())){
            ss.get();
            otric=true;
            if(!isdigit(ss.peek())){
                throw invalid_argument("Wrong date format: "+date);
            }
        }
        ss>>tmp_month;
        if(otric)
            tmp_month=-tmp_month;
        otric= false;
        ss.ignore();
        if(!isdigit(ss.peek())){
            ss.get();
            otric=true;
            if(!isdigit(ss.peek())){
                throw invalid_argument("Wrong date format: "+date);
            }
        }
        ss>>tmp_day;
        if(ss.peek()!=-1){
            throw invalid_argument("Wrong date format: "+date);
        }
        if(tmp_month<1 || tmp_month>12){
            throw invalid_argument("Month value is invalid: "+to_string(tmp_month));
        }
        if(otric)
            tmp_day=-tmp_day;
        if(tmp_day<1 || tmp_day>31){
            throw invalid_argument("Day value is invalid: "+to_string(tmp_day));
        }
        Date dt(tmp_year,tmp_month,tmp_day);
        return dt;

    }
    void Print() const{
        for(const auto& item:map1){
            for (const auto& item2:item.second)
            {
                cout<<setw(4);
                cout<<setfill('0');
                cout << item.first.GetYear()<<"-";
                cout<<setw(2);
                cout << item.first.GetMonth()<<"-";
                cout<<setw(2);
                cout << item.first.GetDay()<< " " << item2 <<endl;
            }
        }
    }

private:
    map<Date,vector<string>> map1;

};


int main() {
    Database db;
    string command,command1,date,event;
    try {
     while (getline(cin, command)) {
         stringstream ss;
         ss<<command;
         ss>>command1>>date>>event;
         if (command1=="Add"){
             db.AddEvent(db.Check_Date(date),event);
             command1.clear();
             date.clear();
             event.clear();
         }else {
             if (command1 == "Del") {
                 Date dt = db.Check_Date(date);
                 if (event.empty()) {
                     cout << "Deleted " << db.DeleteDate(dt) << " events" <<endl;
                 } else {
                     db.DeleteEvent(db.Check_Date(date), event);
                 }
                 command1.clear();
                 date.clear();
                 event.clear();
             }else{
                 if (command1=="Find"){
                     db.Find(db.Check_Date(date));
                     command1.clear();
                     date.clear();
                     event.clear();
                 }else{
                     if (command1=="Print"){
                         db.Print();
                         command1.clear();
                         date.clear();
                         event.clear();
                     }else{
                         if (command1=="")
                         {

                         }else{
                             cout<<"Unknown command: "+command1<<endl;
                             command1.clear();
                             date.clear();
                             event.clear();
                         }
                     }

                 }
             }
         }
    }
    }catch(exception& e){
        cout<<e.what();
        return 1;
    }


    return 0;
}