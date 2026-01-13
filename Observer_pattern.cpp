/******************************************************************************
Observer design pattern:
Observer pattern defines one to many dependencies where multiple objects automatically 
get notified when one object changes state.

key idea: Subject doesn’t know who is observing it — it just notifies them.
All observers must implement an update() method, and that update() method is called by 
the Subject whenever its state changes.


| Role             | Responsibility                   |
| ---------------- | -------------------------------- |
| Subject          | Holds state & notifies observers |
| Observer         | Reacts to state changes          |
| ConcreteSubject  | Actual data source               |
| ConcreteObserver | Actual listener                  |


*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Observer Interface
class Observer{
public:
    virtual void update(float temperature) = 0;
    virtual ~Observer() = default;
};

//subject Interface
class Subject{
public:
    virtual void subscribe(Observer* obs) = 0;
    virtual void unsubscribe(Observer* obs) = 0;
    virtual void notify() = 0;
    virtual ~Subject() = default;
};

//Concrete Subject
class WeatherStation : public Subject{
private:
    float temperature;
    vector<Observer*> observers;
public:
    void subscribe(Observer* obs) override{
        observers.push_back(obs);
    }
    
    void unsubscribe(Observer* obs) override{
        // Use C++20 std::erase
        std::erase(observers, obs);
    }
    
    void setTemperature(float temp){
        temperature = temp;
        notify();
    }
    
    void notify(){
        for(auto& obs : observers){
            obs->update(temperature);
        }
    }
    
};

//concrete obserever
class MobileDisplay : public Observer{
public:
    void update(float temp) override{
        cout<<"Mobile update temperature "<<temp<<endl;
    }
};

class WebsiteDisplay : public Observer{
public:
    void update(float temp) override{
        cout<<"Website update temperature "<<temp<<endl;
    }
};

int main()
{
    WeatherStation station;
    
    Observer* mobile = new MobileDisplay();
    Observer* website = new WebsiteDisplay();
    
    //subscribe
    station.subscribe(mobile);
    station.subscribe(website);
    
    //state chnage so automatic notification
    station.setTemperature(30.30);
    
    //unsubscribe
    station.unsubscribe(mobile);
    
    station.setTemperature(35.35);//only website notify
    
    station.unsubscribe(website);
    
    station.setTemperature(77.30); //no notification 
    
    delete mobile;
    delete website;

    return 0;
}
