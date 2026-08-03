/******************************************************************************
The command design pattern is a behavioural design pattren
that encapsulates a request as an object.
instead of asking an object to perform an action deirectly
we wrap the request inside a command object and execute the 
command later.
This decouples the sender (Invoker) from the receiver (the class that actually
performs the work).

One of the biggest advantages of this pattern is that once a request becomes an
object, it can be:

1. Queued
   - Store ICommand objects inside std::queue and execute them later.
   - Useful for background jobs and thread pools.

2. Logged
   - Store executed ICommand objects in a history list for auditing.

3. Retried
   - If execution fails, push the same ICommand object into a retry queue.

4. Scheduled
   - Execute the command after a delay or at a specific time.

5. Undo/Redo
   - Commands can implement undo() and be stored in an undo stack.


*******************************************************************************/

#include <iostream>
#include <string>
#include <memory>
#include <queue>

//command interface

class ICommand{
public:
    virtual void execute() = 0;
    virtual ~ICommand() = default;
    
};

//receiver [it does not knbow about command]

class AppLauncher{
public:
    void launch(const std::string& appname){
        std::cout<<"Launching app "<<appname<<std::endl;
    }
    
};

class URLLauncher{
public:
    void open(const std::string& url){
        std::cout<<"opening url "<<url<<std::endl;
    }
    
};

//concrete command

class AppLaunchCommand : public ICommand{
private:
    AppLauncher& launcher;
    std::string appname;
public:
    AppLaunchCommand(AppLauncher& launcher, const std::string& appname) : 
                    launcher(launcher), appname(appname){}

    void execute() override{
        launcher.launch(appname);
    }
    
};

class URLLauncherCommand : public ICommand{
private:
    URLLauncher& launcher;
    std::string url;
public:
    URLLauncherCommand(URLLauncher& launcher, const std::string& url) : 
                    launcher(launcher), url(url){}

    void execute() override{
        launcher.open(url);
    }
    
};

//factory

class CommandFactory{
private:
    inline static AppLauncher applauncher; //inline otherwise we need to defone it again 
    inline static URLLauncher urllauncher;
public:
    static std::unique_ptr<ICommand> createCommand(const std::string& cmd){
        
        if(cmd == "APPLAUNCH"){
            return std::make_unique<AppLaunchCommand>(applauncher, "notepad.exe");
        }
        else if(cmd == "OPENURL"){
            return std::make_unique<URLLauncherCommand>(urllauncher, "https::google.com");
        }
        return nullptr;
    }
};

//backend dispatcher/ Invoker
//it does not how to launch, it just delegates the task
class BackendDispatcher{
public:
    void processMessage(const std::string& msg){
        auto command = CommandFactory::createCommand(msg);
        
        if(command){
            command->execute();
        }
    }
};




int main()
{
   
    BackendDispatcher dispatcher;
    
    dispatcher.processMessage("APPLAUNCH");
    
    dispatcher.processMessage("OPENURL");

}
