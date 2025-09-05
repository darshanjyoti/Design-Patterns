//Stretegy design pattern is a behaviour design pattern that allows you to choose
//diffrent algorithm or behaviour at run time

//Stretegy design pattern defines a family of algorithms, put them into separate classes so that
//can be changed at runtime

//when to use stretegy design patter??
//1. when you have multiple ways to perfrom a task
//2. when you want to avoid if else condition
//3. when you want to switch algorithm at run time

//Code 

#include <iostream>
#include <string>
#include <memory>

//Payment stretegy interface
class IPaymentStrategy{
    public:
        virtual void pay(double amount) = 0;
        virtual ~IPaymentStrategy() = default; 
    
};

//Conscrete class
class UPIPayment : public IPaymentStrategy{
    private:
     std::string pin;
    
    public:
     UPIPayment(std::string pin) : pin(pin) {}
     
     void pay(double amount) override{
         std::cout<<"Processing UPI Payment for amount "<<amount<<std::endl;
     }
    
};

class PaypalPayment : public IPaymentStrategy{
    private:
     std::string username;
     std::string password;
    
    public:
     PaypalPayment(std::string username, std::string password) : username(username), password(password){}
     
     void pay(double amount) override{
         std::cout<<"Processing Paypal payment for amount "<<amount<<std::endl;
     }
    
};

class NetBankingPayment : public IPaymentStrategy{
    private:
     std::string account_no;
    
    public:
     NetBankingPayment(std::string account_no) : account_no(account_no){}
     
     void pay(double amount) override{
         std::cout<<"Processing NetBanking Payment for amount "<<amount<<std::endl;
     }
    
};

//Context class
class PaymentProcessor{
    private:
       std::unique_ptr<IPaymentStrategy> paymentStrategy;
    public:

        void setPaymentStrategy(std::unique_ptr<IPaymentStrategy> strategy){
           paymentStrategy = std::move(strategy);
        }
        
        void processPayment(double amount){
            if(paymentStrategy)
                paymentStrategy->pay(amount);
            else
                std::cout<<"No payment strategy"<<std::endl;
        }
        
    
};

//client class

int main()
{
    double amount = 0;
    int payment = 0;
    std::unique_ptr<IPaymentStrategy> paymentStrategy;
    
    std::cout<<"Enter amount "<<std::endl;
    std::cin>>amount;
    
    std::cout<<"Enter payment stretegy: 1 for UPI, 2 for Paypal, 3 for NetBanking"<<std::endl;
    std::cin>>payment;
    
      PaymentProcessor paymentProcessor;
    
    if(payment == 1){
        paymentProcessor.setPaymentStrategy(std::make_unique<UPIPayment>("123"));
    }
    else if(payment == 2){
        paymentProcessor.setPaymentStrategy(std::make_unique<PaypalPayment>("username", "password"));
    }
    else if(payment == 3){
        paymentProcessor.setPaymentStrategy(std::make_unique<NetBankingPayment>("1234"));
    }
    else{
        std::cout<<"Not a valid payment method"<<std::endl;
        return -1;
    }
    
    
    paymentProcessor.processPayment(amount);
    
    return 0;
}
