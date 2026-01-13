/******************************************************************************

 Singleton design pattern
 This is not thread safe.

*******************************************************************************/

#include <iostream>
using namespace std;

class Singleton{
public:
    
    static Singleton* getInstance(){
        if(m_SingleTonPtr == nullptr){
            m_SingleTonPtr = new Singleton();
        }
        return m_SingleTonPtr;
    }
    
    static void deleteInstance(){
        if(m_SingleTonPtr != nullptr){
            delete m_SingleTonPtr;
            m_SingleTonPtr = nullptr;
        }
        
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
    
    //static instance
    static Singleton* m_SingleTonPtr;
};

Singleton* Singleton::m_SingleTonPtr = nullptr;

int main()
{
    Singleton::getInstance();
    Singleton::getInstance();
    Singleton::getInstance();
    
    Singleton::deleteInstance();
    Singleton::deleteInstance();
    Singleton::deleteInstance();
    //only one Constructor called and Destructor called

    return 0;
}
