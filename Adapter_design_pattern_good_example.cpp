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
class PaymentGateway{
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentGateway() = default;
};

//concrete class
class PaypalGateway : public PaymentGateway{
public:
    void pay(int amount) override{
        std::cout<<"Payment done using paypal for amount "<<amount<<std::endl;
    }
};

//adaptee
class StripePaymentGateway{
public:
    void makePayment(int amount){
        std::cout<<"Payment done using Stripe for amount "<<amount<<std::endl;
    }
};

//Adapter

class PaymentGatewayAdapter : public PaymentGateway{
private:
    StripePaymentGateway stripe;
public:
    void pay(int amount) override{
        stripe.makePayment(amount);
    }
};


int main()
{
   //existing implementation
    std::unique_ptr<PaymentGateway> payment = std::make_unique<PaypalGateway>();
    
    payment->pay(1000);
    std::cout<<"\n";
    //replace with new implementation
    payment = std::make_unique<PaymentGatewayAdapter>();
    
    payment->pay(1000);
    
    //now suppose in future we need RazorPay as well, what will u do?
    //ans is we will create another adpater for RazorPay
    //also another good design would be used a factory method here 
    /*
    
        class PaymentFactory
        {
        public:
        
            static std::unique_ptr<PaymentGateway>
            createGateway(const std::string& type)
            {
                if(type == "paypal")
                    return std::make_unique<PaypalGateway>();
        
                if(type == "stripe")
                    return std::make_unique<StripeAdapter>();
        
                if(type == "razorpay")
                    return std::make_unique<RazorpayAdapter>();
        
                return nullptr;
            }
        };
                auto payment =
            PaymentFactory::createGateway("stripe");
        
        payment->pay(1000);
    
    
    
    */
    

}
