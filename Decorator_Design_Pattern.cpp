/*
Decorator design pattern:
Decorator lets you add new behavior (or extra capabilities) to an object at runtime 
without modifying its class.
eg Coffee, SimpleCoffee, Coffe+milk, Coffe +milk + sugar etc.

Without decorator present we can create a base class Cofee and then inherite the other coffee.
But it will lead to INHERITANCE EXOPLOSION and too many classes.
class Coffee {};
class CoffeeWithMilk {};
class CoffeeWithSugar {};
class CoffeeWithMilkAndSugar {};
class CoffeeWithMilkSugarCream {};

Decorator Wrap an object with another object that adds behavior.
*/

#include <iostream>
#include <string>

using namespace std;

//component interface
class Coffee{
public:
   virtual double cost() = 0;
   virtual string getDescription() = 0;
   virtual ~Coffee() = default;
};

//concrete component
class SimpleCoffee : public Coffee{
public:

    double cost() override{
        return 50.0;
    }
    
    string getDescription() override{
        return "Simple coffee";
    }
    
};

//decorator base class
//decorator is a Coffee
//decorator has a Coffee
class CoffeeDecorator : public Coffee{
protected: //imp it is protected
    Coffee* coffee;
public:
    CoffeeDecorator(Coffee* c) : coffee(c){}
};

//concrete decorator

class Milk : public CoffeeDecorator{
public:
    Milk(Coffee* c) : CoffeeDecorator(c) {}//very imp step. Similar to java's Super
    
    double cost(){
        return coffee->cost() + 10.0;
        //coffee is a data member of CoffeeDecorator
        //It is marked protected so derive class can access it
    }
    
    string getDescription(){
        return coffee->getDescription() + " Milk ";
    }
    
};

class Sugar : public CoffeeDecorator{
public:
    Sugar(Coffee* c) : CoffeeDecorator(c){}
    
    double cost(){
        return coffee->cost() + 20.0;
    }
    
    string getDescription(){
        return coffee->getDescription() + " Sugar ";
    }
    
};


//client CoffeeDecorator
int main(){
    //client code does not knwo about decorator
    Coffee* coffee = new SimpleCoffee();
    cout<<"Cost is "<<coffee->cost()<<endl;
    cout<<"Desc is "<<coffee->getDescription()<<endl;
    cout<<"After Milk"<<endl;
    coffee = new Milk(coffee);
    cout<<"Cost is "<<coffee->cost()<<endl;
    cout<<"Desc is "<<coffee->getDescription()<<endl;
    cout<<"After Sugar"<<endl;
    coffee = new Sugar(coffee);
    cout<<"Cost is "<<coffee->cost()<<endl;
    cout<<"Desc is "<<coffee->getDescription()<<endl;
    
    //also we can directly do this
    Coffee* c = new SimpleCoffee();
    c = new Sugar(new Milk(c));
    cout<<"Cost is "<<c->cost()<<endl;
    cout<<"Desc is "<<c->getDescription()<<endl;
}

