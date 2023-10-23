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
        cout << "         ͣ�����շѱ�׼��ÿСʱ " << pl.getParkingPerHour() << " Ԫ" << endl;
        cout << "**************** Ŀǰͣ����� **************" << endl;
        cout << "*                                          *" << endl;
        cout << " �� "<< pl.getAllParkingPlace() << " ����λ,ʣ�� " << pl.getRemainParkingPlace() << " ����λ���Ⱥ����� " << pl.getAllWaitingPlace() << " ����" << endl;
        cout << "*                                          *" << endl;
        cout << "********************************************" << endl;
        cout << "                 ͣ��������ϵͳ                " << endl;
        cout << "--------------------------------------------" << endl;
        cout << "       1.  ��������ͣ��������" << endl;
        cout << "       2.  �����뿪ͣ��������" << endl;
        cout << "       3.  ͣ����ͣ����Ϣ��ʾ" << endl;
        cout << "       4.  �����ͣ����Ϣ��ʾ" << endl;
        cout << "       5.  ��������" << endl;
        cout << "       6.  ͣ������̨����" << endl;
        cout << "       7.  ��ʾͣ���շ���ϸ��" << endl;
        cout << "       0.  �˳�ϵͳ" << endl;
        cout << "��ѡ��";
        cin >> op;
        cout << endl;
        switch (op) {
            case 1: {
                string name;
                cout << "���복�ƺţ� ";
                cin >> name;
                if(name == "0"){
                    cout << "�Ƿ����ƺţ��������0���������ƺ�..." << endl;
                    break;
                }
                cout << endl;
                if(pl.findCarWait(name).getName() == "0" && pl.findCar(name).getName() == "0"){
                    Car c(name);
                    if (pl.addCar(c)) {
                        cout << "*** ������" << c.getName() << "���ѳɹ�ͣ�ڡ�ͣ������" << endl;
                    } else {
                        cout << "--- ������" << c.getName() << "����ʱͣ�ڡ������" << endl;
                    }

                } else {
                    cout << "����������ͬ���յĳ��������ǲ������Ƴ���������ȥ����..." << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                string name;
                cout << "������Ҫ�뿪�ĳ��ƺţ� ";
                cin >> name;
                Car c = pl.findCar(name);
                time_t tt = time(NULL);
                tm* t = localtime(&tt);
                string nowtime = to_string(t->tm_hour)+":"+to_string(t->tm_min);
                if(c.getName() != "0"){
                    int hourCost = (t->tm_hour-c.getCarHour())*pl.getParkingPerHour();
                    int minCost = 100*(t->tm_min-c.getCarMinute())*pl.getParkingPerHour()/60;
                    double cost = hourCost + (double)minCost/100;
                    cout << "----------------- ���ƺţ�" << c.getName() << " -------------------" << endl;
                    cout << " |                                             |" << endl;
                    cout << " | ����ʱ�� |  �뿪ʱ��  |  ͣ��ʱ��  | Ӧ�տ� |" << endl;
                    cout << " ===============================================" << endl;
                    cout << " |  "<< c.getTime() << "   |    "<< nowtime <<"  |   "<< t->tm_hour-c.getCarHour() << ":" <<
                    t->tm_min-c.getCarMinute()  <<"     |  " << cost
                    <<"  |" << endl;
                    cout << "�Һܿɰ��������Ǯ��" << endl;
                    string entryTime = to_string(c.getCarMonth())+"��"+ to_string(c.getCarDay())+"��"+" "+to_string(c.getCarHour())+":"+
                                       to_string(c.getCarMinute());
                    string departureTime = to_string(t->tm_mon)+"��"+ to_string(t->tm_mday)+"��"+" "+ to_string(t->tm_hour)+":"+ to_string(t->tm_min);
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
                    cout << "ͣ�����ڲ��޴˳���" << endl;
                    getchar();
                }
                system("pause");
                break;
            }
            case 3:{
                cout << "��ͣ������Ŀǰ��Ϣ��" << endl;
                vector<Car> carList = pl.getAllCar();
                for (int i = 0; i < pl.getAllParkingPlace()-pl.getRemainParkingPlace(); ++i) {
                    cout << "��� " << i+1 << "�� ������" << carList[i].getName() << "�� " << carList[i].getCarHour() << "ʱ- " << carList[i].getCarMinute() << " �ֽ��롶ͣ��������" << endl;
                }
                system("pause");
                break;
            }
            case 4:{
                cout << "�������Ŀǰ��Ϣ��" << endl;
                list<Car> waitList = pl.getAllWait();
                int i = 1;
                for(auto it=waitList.begin();it != waitList.end(); it++){
                    cout << "��� " << i++ << "�� ������" << it->getName() << "�� " << it->getCarHour() << "ʱ- " << it->getCarMinute() << " �ֽ��롶�������" << endl;
                }
                system("pause");
                break;
            }
            case 5:{
                string name;
                cout << "������Ҫ���ҵĳ��ƺţ� ";
                cin >> name;
                Car c = pl.findCar(name);
                if(c.getName() != "0"){
                    cout << "������" << c.getName() << "���� " << c.getCarHour() << " ʱ " << c.getCarMinute() << " �ֽ��롶ͣ������" << endl;
                } else {
                    c = pl.findCarWait(name);
                    if(c.getName() != "0"){
                        cout << "������" << c.getName() << "���� " << c.getCarHour() << " ʱ " << c.getCarMinute() << " �ֽ��롶�����" << endl;
                    }
                    else{
                        cout << "���޴˳�����" << endl;
                    }
                }
                system("pause");
                break;
            }
            case 6:{
                int op;
                do {
                    cout << "********************************************" << endl;
                    cout << "               ͣ������̨����ϵͳ               " << endl;
                    cout << "=============================================" << endl;
                    cout << "      1.����ͣ������λ��Ŀ" << endl;
                    cout << "      2.����ͣ�����շѱ�׼" << endl;
                    cout << "      0.�˳���̨����ϵͳ" << endl;
                    cout << " ��ѡ��" << endl;
                    cin >> op;
                    switch (op) {
                        case 1:{
                            cout << "Ŀǰ��λ��Ŀ�� " << pl.getAllParkingPlace() << endl;
                            cout << "������Ҫ���ĵ���Ŀ�� ";
                            int num;
                            cin >> num;
                            if(num <= 0){
                                cout << endl;
                                cout << " ��Ч�����룡 " << endl;
                                break;
                            } else {
                                if(pl.expandParkingLot(num)){
                                    cout << endl;
                                    cout << " ���ĳɹ�����ǰ�ĳ�λ��Ŀ�ǣ�" << pl.getAllParkingPlace() << endl;

                                } else {
                                    cout << "������ǿ�ȱ����ڳ���λ������������ڵ�ǰ���г�������Ŀ����ǰ���е���ĿΪ��" << pl.getAllParkingPlace()-pl.getRemainParkingPlace() << endl;
                                    break;
                                }
                                break;
                            }
                            system("pause");
                        }
                        case 2:{
                            cout << "Ŀǰ�շѱ�׼�� " << pl.getParkingPerHour() << endl;
                            cout << "������Ҫ���ĵ���Ŀ�� ";
                            int num;
                            cin >> num;
                            if(num < 0){
                                cout << endl;
                                cout << " ��Ч�����룡 ��ô�����˵���Ǯ��" << endl;
                                break;
                                system("pause");
                            } else {
                                cout << endl;
                                pl.setParkingPerHour(num);
                                cout << " ���ĳɹ�����ǰ���շѱ�׼�ǣ�" << pl.getParkingPerHour() << endl;
                                if(num == 0){
                                    cout << "�����Ҫ���˰�������ͣ������" << endl;
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
                    cout << "��ǰû�м�¼��������г����뿪������~" << endl;
                    break;
                } else {
                    time_t tt = time(NULL);
                    tm* t = localtime(&tt);
                    string date = to_string(t->tm_year+1900)+"-"+to_string(t->tm_mon)+"-"+to_string(t->tm_mday)+".txt";
                    fstream f;
                    f.open(date,ios::out|ios::app);
                    double totalMonth = 0;
                    double totalDay = 0;
                    f << "         ��ͣ�����������շ���ϸ��" << endl;
                    f << " =======================================================" << endl;
                    f << " |  ���ƺ�  |  ����ʱ��  | �뿪ʱ�� | ͣ��ʱ�� |  ����  |" << endl;
                    f << " =======================================================" << endl;


                    cout << "         ��ͣ�����������շ���ϸ��" << endl;
                    cout << " =======================================================" << endl;
                    cout << " |  ���ƺ�  |  ����ʱ��  | �뿪ʱ�� | ͣ��ʱ�� |  ����  |" << endl;
                    cout << " =======================================================" << endl;
                    for(int i : month){
                        for(int j : day){
                            vector<Log> logs = pl.getLogs(i,j);
                            for(auto log : logs){
                                cout << log.getName() << "   " << log.getEntryTime() << "   " << log.getDepartureTime() << "    " << log.getRemainTime() << "    " << fixed << setprecision(2) << log.getCost() << endl;
                                totalDay += log.getCost();

                                f << log.getName() << "   " << log.getEntryTime() << "   " << log.getDepartureTime() << "    " << log.getRemainTime() << "    " << fixed << setprecision(2) << log.getCost() << endl;
                            }

                            f << "���պϼ�                                 " << totalDay << endl;
                            cout << "���պϼ�                                 " << totalDay << endl;
                            totalMonth += totalDay;
                        }

                        f << "--------------------------------------------------------" << endl;
                        f <<  i << "�·ݺϼ�                                   "  << totalMonth  << endl;
                        f << " =======================================================" << endl;

                        cout << "--------------------------------------------------------" << endl;
                        cout << i << "�·ݺϼ�                                  "  <<  totalMonth  << endl;
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
