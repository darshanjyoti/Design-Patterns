/******************************************************************************
Builder design pattern is a creational design pattern that helps
to creates complex object in one step. This is very helpful when the object has 
many optional parameter or need complex steps to build the the object.
eg suppose we have a class Computer. it has mandatory cpu and ram 
but it can have optionally ssd, wifi, graphic etc.
Without builder pattern we can write multiple constructor but it leads to
constructor telescoping problem. 

*******************************************************************************/

#include <iostream>
#include <string>

class Computer{
public:
    std::string cpu;
    int ram;
    
    int ssd = 0;
    bool wifi = false;
    bool bluetooth = false;
    std::string gpu = "";
    
    void display() const
    {
        std::cout << "CPU : " << cpu << '\n';
        std::cout << "RAM : " << ram << " GB\n";
        std::cout << "SSD : " << ssd << " GB\n";
        std::cout << "GPU : " << gpu << '\n';
        std::cout << "Wifi : " << std::boolalpha << wifi << '\n';
        std::cout << "Bluetooth : " << bluetooth << '\n';
    }
    
};

//builder class

class ComputerBuilder{
private:
    Computer computer;
public:
    ComputerBuilder(const std::string& cpu, int ram){
        computer.cpu = cpu;
        computer.ram = ram;
    }
    
    ComputerBuilder& setSSD(int ssd){
        computer.ssd = ssd;
        return *this;
    }
    
    ComputerBuilder& setWIFI(bool wifi){
        computer.wifi = wifi;
        return *this;
    }
    
    ComputerBuilder& setBLUETOOTH(bool bluetooth){
        computer.bluetooth = bluetooth;
        return *this;
    }
    
    ComputerBuilder& setGPU(const std::string& gpu){
        computer.gpu = gpu;
        return *this;
    }
    
    //build function which return the final object
    Computer build(){
        return computer;
    }
    
};


int main()
{
    Computer gamingPC = ComputerBuilder("Intel i5", 3)
                        .setSSD(4)
                        .setWIFI(true)
                        .setBLUETOOTH(false)
                        .setGPU("NVDIA")
                        .build();
                        
    
    gamingPC.display();                       
    

}
