/******************************************************************************
Facade design pattern is structural design pattern
It provides a simpple, unified interface to a complex 
subsystem of classes.
eg: we have a food ordering system and without facade pattern
client has to create each object in a correct order.
createOrder();
payement();
assignDelivery();
notify();
deliver() etc. 
But facde pattern gives a simpe class OrderFacadeService 
and c lient simply call OrderFacadeService.createOrder();

*******************************************************************************/

#include <iostream>
#include <memory>
#include <string>


class OrderService{
public:
 void createOrder(){
     std::cout<<"order created"<<std::endl;
 }
    
};

class DelieryAssignmentService{
public:
 void assignDelivery(){
     std::cout<<"Delivery partner assigned"<<std::endl;
 }
    
};

class PaymentService{
public:
 void pay(){
     std::cout<<"payement done"<<std::endl;
 }
    
};

class NotificationService{
public:
 void notify(){
     std::cout<<"notified to user"<<std::endl;
 }
    
};

class DeliveryService{
public:
 void deliver(){
     std::cout<<"Order delivered."<<std::endl;
 }
    
};

class FoodOrderingFacade{
public:
    void placeOrder(){
        os.createOrder();
        ps.pay();
        das.assignDelivery();
        ns.notify();
        ds.deliver();
    }

private:
    OrderService os;
    DelieryAssignmentService das;
    PaymentService ps;
    NotificationService ns;
    DeliveryService ds;
};

int main()
{
    //Client will call only FoodOrderingFacade 
    FoodOrderingFacade facade;
    facade.placeOrder();

}
