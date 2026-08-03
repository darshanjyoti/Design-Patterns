/******************************************************************************
Adapter design pattern is a structural design pattern that allow
two incompatible interfaces to work together by contverting one interfacesto another 
that client expects.
In simple terms, adapter acts as a bridge between two incompatible
interfaces.
Suppose we have an interface Printer with a function print().

A concrete implementation is HPPrinter.

Client code:

std::unique_ptr<Printer> printer = std::make_unique<HPPrinter>();
printer->print();

Now, suppose we want to replace HPPrinter with a third-party library.

The third-party library provides a class LegacyPrinter with a function
oldPrint() instead of print().

Without the Adapter Pattern, we would have to modify all the client code to
use LegacyPrinter and call oldPrint(), resulting in changes throughout the
application.

With the Adapter Pattern, we create a PrinterAdapter that implements the
Printer interface and internally delegates the call to LegacyPrinter::oldPrint().

Now the client only needs to use:

std::unique_ptr<Printer> printer = std::make_unique<PrinterAdapter>();
printer->print();

The rest of the application continues to use the Printer interface without
knowing that a third-party library is being used underneath.

In a well-designed application, even object creation is usually hidden behind
a Factory or Dependency Injection, so the client code may not need to change
at all.

*******************************************************************************/

#include <iostream>
#include <string>
#include <memory>

//target interface

class Printer{
public:
    virtual void print() = 0;
    virtual ~Printer() = default;
    
};

//adaptee
class LegacyPrinter{
public:
    void oldPrint(){
        std::cout<<"Printing using legacy printer";
    }
};

//Adapter

class PrinterAdapter : public Printer{
private:
    LegacyPrinter legacyPrinter;
public:
    void print() override{
        legacyPrinter.oldPrint();
    }
    
};

int main()
{
    std::unique_ptr<Printer> ptr = std::make_unique<PrinterAdapter>();
    
    ptr->print(); //still caliing print()
    

}
