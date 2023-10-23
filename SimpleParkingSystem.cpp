#include<iostream>
#include <ctime>
#include <vector>
#include <list>
#include <set>
#include <iomanip>
#include <fstream>

using namespace std;
class CarTime{
private:
    int year, month, day, hour, minute, second;
public:
    void setTime(){
        time_t tt = time(NULL);
        tm* t = localtime(&tt);
        year = t->tm_year + 1900;
        month = t->tm_mon;
        day = t->tm_mday;
        hour = t->tm_hour;
        minute = t->tm_min;
        second = t->tm_sec;
    }
    int getYear(){
        return year;
    }
    int getMonth(){
        return month;
    }
    int getDay(){
        return day;
    }
    int getHour(){
        return hour;
    }
    int getMinute(){
        return minute;
    }
    int getSecond(){
        return second;
    }
};

class Car : public CarTime{
private:
    string name;
    CarTime ct;
public:
    Car(){}
    Car(string name){
        this->name = name;
        ct.setTime();
    }
    string getName(){
        return this->name;
    }
    void setName(string name){
        this->name = name;
    }
    string getTime(){
        string time = to_string(ct.getHour())+":"+to_string(ct.getMinute());
        return time;
    }
    int getCarHour(){
        return ct.getHour();
    }
    int getCarMinute(){
        return ct.getMinute();
    }
    int getCarMonth(){
        return ct.getMonth();
    }
    int getCarDay(){
        return ct.getDay();
    }
};

class Log{
private:
    string name;
    string entryTime;
    string departureTime;
    string remainTime;
    double cost;
    int month;
    int day;
public:
    string getName(){
        return name;
    }
    string getEntryTime(){
        return entryTime;
    }
    string getDepartureTime(){
        return departureTime;
    }
    string getRemainTime(){
        return remainTime;
    }
    double getCost(){
        return cost;
    }
    int getMonth(){
        return month;
    }
    int getDay(){
        return day;
    }

    Log(const string &name, const string &entryTime, const string &departureTime, const string &remainTime, double cost,
        int month, int day) : name(name), entryTime(entryTime), departureTime(departureTime), remainTime(remainTime),
                              cost(cost), month(month), day(day) {}

    void setName(const string &name) {
        this->name = name;
    }
    void setEntryTime(const string &entryTime) {
        this->entryTime = entryTime;
    }
    void setDepartureTime(const string &departureTime) {
        this->departureTime = departureTime;
    }
    void setRemainTime(const string &remainTime) {
        this->remainTime = remainTime;
    }
    void setCost(const double &cost) {
        this->cost = cost;
    }
};

class ParkingLot{
private:
    int allParkingPlace = 3;
    int remainParkingPlace = 3;
    int parkingPerHour = 10;
    int allWaitingPlace = 0;
    vector<Car> parkingPlace;
    list<Car> waitingPlace;
    vector<Log> logs;
    set<int> monthTable;
    set<int> dayTable;
public:
    void setAllParingPlace(int num){
        allParkingPlace = num;
    }
    void setParkingPerHour(int money){
        parkingPerHour = money;
    }
    int getAllWaitingPlace(){
        return allWaitingPlace;
    }
    int getAllParkingPlace(){
        return allParkingPlace;
    }
    int getRemainParkingPlace(){
        return remainParkingPlace;
    }
    int getParkingPerHour(){
        return parkingPerHour;
    }
    vector<Car>& getAllCar(){
        return parkingPlace;
    }
    list<Car>& getAllWait(){
        return waitingPlace;
    }
    void setTimeTable(int month, int day){
        monthTable.insert(month);
        dayTable.insert(day);
    }
    set<int>& getMonthTable(){
        return monthTable;
    }
    set<int>& getDayTable(){
        return dayTable;
    }
    bool addCar(Car c){
        if(remainParkingPlace > 0){
            parkingPlace.push_back(c);
            remainParkingPlace--;
            return true;
        } else{
            waitingPlace.push_back(c);
            allWaitingPlace++;
            return false;
        }
    }

    void addLog(Log log){
        logs.push_back(log);
    }

    vector<Log> getLogs(int month, int day){
        vector<Log> ans;
        for(auto i : logs){
            if(i.getMonth() == month && i.getDay() == day){
                ans.push_back(i);
            }
        }
        return ans;
    }

    bool expandParkingLot(int num){
        if(num < allParkingPlace - remainParkingPlace){
            return false;
        } else {
            while (!waitingPlace.empty()){
                parkingPlace.push_back(waitingPlace.front());
                waitingPlace.pop_front();
                allWaitingPlace--;
                if(parkingPlace.size() == allParkingPlace){
                    break;

                }
            }
            setAllParingPlace(num);
            remainParkingPlace = allParkingPlace - parkingPlace.size();
            return true;
        }
    }

    Car findCar(string name){
        auto it = parkingPlace.begin();
        for(it;it != parkingPlace.end();it++){
            if(it->getName() == name){
                return *it;
            }
        }
        return Car("0");
    }

    Car findCarWait(string name){
        for(auto it = waitingPlace.begin(); it != waitingPlace.end(); it++){
            if(it->getName() == name){
                return *it;
            }
        }
        return Car("0");
    }

    bool deleteCar(string name){
        for(auto it = parkingPlace.begin();it != parkingPlace.end(); it++){
            if(it->getName() == name){
                if(!waitingPlace.empty()){
                    *it = waitingPlace.front();
                    Car c = *it;
                    waitingPlace.pop_front();
                    allWaitingPlace--;
                } else {
                    parkingPlace.erase(it);
                    remainParkingPlace++;
                }
                return true;
            }
        }
        return false;
    }
};


int main(){
    ParkingLot pl;
    int op;
    do{
        cout << "         停车场收费标准：每小时 " << pl.getParkingPerHour() << " 元" << endl;
        cout << "**************** 目前停车情况 **************" << endl;
        cout << "*                                          *" << endl;
        cout << " 共 "<< pl.getAllParkingPlace() << " 个车位,剩下 " << pl.getRemainParkingPlace() << " 个空位，等候区有 " << pl.getAllWaitingPlace() << " 辆车" << endl;
        cout << "*                                          *" << endl;
        cout << "********************************************" << endl;
        cout << "                 停车场管理系统                " << endl;
        cout << "--------------------------------------------" << endl;
        cout << "       1.  汽车到达停车场操作" << endl;
        cout << "       2.  汽车离开停车场操作" << endl;
        cout << "       3.  停车场停车信息显示" << endl;
        cout << "       4.  便道上停车信息显示" << endl;
        cout << "       5.  查找汽车" << endl;
        cout << "       6.  停车场后台管理" << endl;
        cout << "       7.  显示停车收费明细表" << endl;
        cout << "       0.  退出系统" << endl;
        cout << "请选择：";
        cin >> op;
        cout << endl;
        switch (op) {
            case 1: {
                string name;
                cout << "输入车牌号： ";
                cin >> name;
                if(name == "0"){
                    cout << "非法车牌号，请输入非0的其它车牌号..." << endl;
                    break;
                }
                cout << endl;
                if(pl.findCarWait(name).getName() == "0" && pl.findCar(name).getName() == "0"){
                    Car c(name);
                    if (pl.addCar(c)) {
                        cout << "*** 车辆《" << c.getName() << "》已成功停在《停车场》" << endl;
                    } else {
                        cout << "--- 车辆《" << c.getName() << "》暂时停在《便道》" << endl;
                    }

                } else {
                    cout << "不能输入相同牌照的车辆，您是不是套牌车（，建议去自首..." << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                string name;
                cout << "请输入要离开的车牌号： ";
                cin >> name;
                Car c = pl.findCar(name);
                time_t tt = time(NULL);
                tm* t = localtime(&tt);
                string nowtime = to_string(t->tm_hour)+":"+to_string(t->tm_min);
                if(c.getName() != "0"){
                    int hourCost = (t->tm_hour-c.getCarHour())*pl.getParkingPerHour();
                    int minCost = 100*(t->tm_min-c.getCarMinute())*pl.getParkingPerHour()/60;
                    double cost = hourCost + (double)minCost/100;
                    cout << "----------------- 车牌号：" << c.getName() << " -------------------" << endl;
                    cout << " |                                             |" << endl;
                    cout << " | 进入时间 |  离开时间  |  停留时间  | 应收款 |" << endl;
                    cout << " ===============================================" << endl;
                    cout << " |  "<< c.getTime() << "   |    "<< nowtime <<"  |   "<< t->tm_hour-c.getCarHour() << ":" <<
                    t->tm_min-c.getCarMinute()  <<"     |  " << cost
                    <<"  |" << endl;
                    cout << "我很可爱，请给我钱！" << endl;
                    string entryTime = to_string(c.getCarMonth())+"月"+ to_string(c.getCarDay())+"日"+" "+to_string(c.getCarHour())+":"+
                                       to_string(c.getCarMinute());
                    string departureTime = to_string(t->tm_mon)+"月"+ to_string(t->tm_mday)+"日"+" "+ to_string(t->tm_hour)+":"+ to_string(t->tm_min);
                    string remainTime = to_string(t->tm_hour-c.getCarHour())+":"+ to_string(t->tm_min-c.getCarMinute());
                    int month = t->tm_mon;
                    int day = t->tm_mday;
                    Log log(c.getName(),entryTime,departureTime,remainTime,cost,month,day);
                    pl.addLog(log);
                    pl.deleteCar(name);
                    pl.setTimeTable(month,day);
                    getchar();
                }
                else if(c.getName() == "0"){
                    cout << "停车场内查无此车！" << endl;
                    getchar();
                }
                system("pause");
                break;
            }
            case 3:{
                cout << "《停车场》目前信息：" << endl;
                vector<Car> carList = pl.getAllCar();
                for (int i = 0; i < pl.getAllParkingPlace()-pl.getRemainParkingPlace(); ++i) {
                    cout << "序号 " << i+1 << "： 车辆《" << carList[i].getName() << "》 " << carList[i].getCarHour() << "时- " << carList[i].getCarMinute() << " 分进入《停车场》！" << endl;
                }
                system("pause");
                break;
            }
            case 4:{
                cout << "《便道》目前信息：" << endl;
                list<Car> waitList = pl.getAllWait();
                int i = 1;
                for(auto it=waitList.begin();it != waitList.end(); it++){
                    cout << "序号 " << i++ << "： 车辆《" << it->getName() << "》 " << it->getCarHour() << "时- " << it->getCarMinute() << " 分进入《便道》！" << endl;
                }
                system("pause");
                break;
            }
            case 5:{
                string name;
                cout << "请输入要查找的车牌号： ";
                cin >> name;
                Car c = pl.findCar(name);
                if(c.getName() != "0"){
                    cout << "车辆《" << c.getName() << "》于 " << c.getCarHour() << " 时 " << c.getCarMinute() << " 分进入《停车场》" << endl;
                } else {
                    c = pl.findCarWait(name);
                    if(c.getName() != "0"){
                        cout << "车辆《" << c.getName() << "》于 " << c.getCarHour() << " 时 " << c.getCarMinute() << " 分进入《便道》" << endl;
                    }
                    else{
                        cout << "查无此车喵！" << endl;
                    }
                }
                system("pause");
                break;
            }
            case 6:{
                int op;
                do {
                    cout << "********************************************" << endl;
                    cout << "               停车场后台管理系统               " << endl;
                    cout << "=============================================" << endl;
                    cout << "      1.更改停车场车位数目" << endl;
                    cout << "      2.更改停车场收费标准" << endl;
                    cout << "      0.退出后台管理系统" << endl;
                    cout << " 请选择：" << endl;
                    cin >> op;
                    switch (op) {
                        case 1:{
                            cout << "目前车位数目： " << pl.getAllParkingPlace() << endl;
                            cout << "请输入要更改的数目： ";
                            int num;
                            cin >> num;
                            if(num <= 0){
                                cout << endl;
                                cout << " 无效的输入！ " << endl;
                                break;
                            } else {
                                if(pl.expandParkingLot(num)){
                                    cout << endl;
                                    cout << " 更改成功，当前的车位数目是：" << pl.getAllParkingPlace() << endl;

                                } else {
                                    cout << "您不能强迫别人腾出车位喵，请输入大于当前已有车数的数目，当前存有的数目为：" << pl.getAllParkingPlace()-pl.getRemainParkingPlace() << endl;
                                    break;
                                }
                                break;
                            }
                            system("pause");
                        }
                        case 2:{
                            cout << "目前收费标准： " << pl.getParkingPerHour() << endl;
                            cout << "请输入要更改的数目： ";
                            int num;
                            cin >> num;
                            if(num < 0){
                                cout << endl;
                                cout << " 无效的输入！ 怎么会有人倒贴钱（" << endl;
                                break;
                                system("pause");
                            } else {
                                cout << endl;
                                pl.setParkingPerHour(num);
                                cout << " 更改成功，当前的收费标准是：" << pl.getParkingPerHour() << endl;
                                if(num == 0){
                                    cout << "您真的要别人白嫖您的停车场吗？" << endl;
                                }
                                system("pause");
                                break;
                            }
                            system("pause");
                        }
                        default:
                            break;
                    }
                }while(op!=0);
                system("pause");
                break;
            }
            case 7:{
                set<int> month = pl.getMonthTable();
                set<int> day = pl.getDayTable();
                if(month.empty()){
                    cout << "当前没有记录喵，请进行车辆离开操作喵~" << endl;
                    break;
                } else {
                    time_t tt = time(NULL);
                    tm* t = localtime(&tt);
                    string date = to_string(t->tm_year+1900)+"-"+to_string(t->tm_mon)+"-"+to_string(t->tm_mday)+".txt";
                    fstream f;
                    f.open(date,ios::out|ios::app);
                    double totalMonth = 0;
                    double totalDay = 0;
                    f << "         《停车场》汽车收费明细表" << endl;
                    f << " =======================================================" << endl;
                    f << " |  车牌号  |  进入时间  | 离开时间 | 停留时间 |  费用  |" << endl;
                    f << " =======================================================" << endl;


                    cout << "         《停车场》汽车收费明细表" << endl;
                    cout << " =======================================================" << endl;
                    cout << " |  车牌号  |  进入时间  | 离开时间 | 停留时间 |  费用  |" << endl;
                    cout << " =======================================================" << endl;
                    for(int i : month){
                        for(int j : day){
                            vector<Log> logs = pl.getLogs(i,j);
                            for(auto log : logs){
                                cout << log.getName() << "   " << log.getEntryTime() << "   " << log.getDepartureTime() << "    " << log.getRemainTime() << "    " << fixed << setprecision(2) << log.getCost() << endl;
                                totalDay += log.getCost();

                                f << log.getName() << "   " << log.getEntryTime() << "   " << log.getDepartureTime() << "    " << log.getRemainTime() << "    " << fixed << setprecision(2) << log.getCost() << endl;
                            }

                            f << "当日合计                                 " << totalDay << endl;
                            cout << "当日合计                                 " << totalDay << endl;
                            totalMonth += totalDay;
                        }

                        f << "--------------------------------------------------------" << endl;
                        f <<  i << "月份合计                                   "  << totalMonth  << endl;
                        f << " =======================================================" << endl;

                        cout << "--------------------------------------------------------" << endl;
                        cout << i << "月份合计                                  "  <<  totalMonth  << endl;
                        cout << " =======================================================" << endl;
                    }
                    f.close();
                }
                system("pause");
                break;
            }
            case 0:
                break;
            default:
                break;
        }
        system("cls");
    } while (op != 0);
    return 0;
}
