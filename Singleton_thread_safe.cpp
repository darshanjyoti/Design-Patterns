/******************************************************************************

 Singleton design pattern
 //Mayer's singleton -- Thread safe and lazy initialization

*******************************************************************************/

#include <iostream>
#include <vector>
#include <thread>
using namespace std;

class Singleton{
public:
    
    //return reference not pointer
    static Singleton& getInstance(){
        static Singleton instance; //thread safe since c++ 11 and lazy initialization
        return instance;
    }
    //delete copy constructor and copy assignmenet operator
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
    
    //private constructor and destructor
private:
    Singleton(){
        cout<<"Constructor called"<<endl;
    }
    ~Singleton(){
        cout<<"Destructor called"<<endl;
    }
};

void initiateSingleton(){
    Singleton::getInstance();
}

int main()
{
    vector<thread> threads;
    
    for(int i=0; i<10; i++){
        threads.emplace_back(initiateSingleton);
    }
    
    for(auto& t : threads){
        if(t.joinable()){
            t.join();
        }
    }
    //only one Constructor called and Destructor called

    return 0;
}
