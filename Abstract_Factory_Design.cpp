/******************************************************************************
While factory pattern gives one object, abstract factory pattern 
gives a family of related object. eg in a GUI library we have button, checkbox
, text but these are different for windows and macos.
So we will have a GUIFactory which as WindowsFactory and MacFactory 
which creates the diffrent button, checkbox, tetx etc

*******************************************************************************/

#include <iostream>
#include <memory>
#include <string>

//abstract product

class Button{
public:
    virtual void click() = 0;
    virtual ~Button() = default;
};

class Checkbox{
public:
    virtual void check() = 0;
    virtual ~Checkbox() = default;
};

//concreat product

class WindowsButton : public Button{
public:
    void click() override{
        std::cout<<"Windows button clicked"<<std::endl;
    }
};

class MacButton : public Button{
public:
    void click() override{
        std::cout<<"Mac button clicked"<<std::endl;
    }
};

class WindowsCheckbox : public Checkbox{
public:
    void check() override{
        std::cout<<"Windows checkbox checked"<<std::endl;
    }
};

class MacCheckBox : public Checkbox{
public:
    void check() override{
        std::cout<<"Mac checkbox clicked"<<std::endl;
    }
};

//abstract factory

class GUIFactory{
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    
    virtual ~GUIFactory() = default;
};

//Concrete factory

class WindowsFactory : public GUIFactory{
public:
    std::unique_ptr<Button> createButton() override{
        return std::make_unique<WindowsButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override{
        return std::make_unique<WindowsCheckbox>();
    }
};

class MacFactory : public GUIFactory{
public:
    std::unique_ptr<Button> createButton() override{
        return std::make_unique<MacButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override{
        return std::make_unique<MacCheckBox>();
    }
};

class Application{
public:
    void createUI(GUIFactory& factory){
        auto button = factory.createButton();
        
        auto checkbox = factory.createCheckbox();
        
        button->click();
        checkbox->check();
    }
    
};



int main()
{
    bool win = true;
        
    Application app;
   
    if(win){
        WindowsFactory factory;
        app.createUI(factory);
    }
    else{
        MacFactory factory;
        app.createUI(factory);
    }

}
