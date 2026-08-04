/******************************************************************************
The State Pattern is a behavioral design pattern that allows an object to change 
its behavior when its internal state changes. Instead of using large if-else or 
switch statements, each state is represented as a separate class.
eg without state pattern:
class MediaPlayer
{
private:
    std::string state = "STOPPED";

public:

    void play()
    {
        if(state == "STOPPED")
        {
            std::cout << "Start Playing\n";
            state = "PLAYING";
        }
        else if(state == "PAUSED")
        {
            std::cout << "Resume Playing\n";
            state = "PLAYING";
        }
        else
        {
            std::cout << "Already Playing\n";
        }
    }

    void pause()
    {
        if(state == "PLAYING")
        {
            std::cout << "Paused\n";
            state = "PAUSED";
        }
        else
        {
            std::cout << "Cannot Pause\n";
        }
    }

    void stop()
    {
        if(state == "PLAYING" || state == "PAUSED")
        {
            std::cout << "Stopped\n";
            state = "STOPPED";
        }
    }
};

If new states come, if else grows which creates problem.

*******************************************************************************/
/******************************************************************************
State Design Pattern

Instead of using large if-else statements to check the current state,
we represent each state as a separate class.

Example:
Media Player

States:
1. Stopped
2. Playing
3. Paused

Operations:
play()
pause()
stop()
******************************************************************************/

#include <iostream>
#include <string>
#include <memory>

class MediaPlayer; //forward declaration

//State interface
class PlayerState{
public:
    virtual void play(MediaPlayer& player) = 0;
    virtual void pause(MediaPlayer& player) = 0;
    virtual void stop(MediaPlayer& player) = 0;
    virtual std::string name() const = 0;
    virtual ~PlayerState() = default;
};

//context

class MediaPlayer{
private:
    std::unique_ptr<PlayerState> state;
public:
    MediaPlayer(std::unique_ptr<PlayerState> initialState) : state(std::move(initialState)){
        std::cout<<"MediaPlayer initialized with state "<<state->name()<<std::endl;
    }
    
    void setState(std::unique_ptr<PlayerState> newState){
        std::cout<<"Moving from "<<state->name()<<" to "<<newState->name()<<std::endl;
        state = std::move(newState);
    }
    
        // Delegate to whichever state is current
    void pressPlay()  { state->play(*this); }
    void pressPause() { state->pause(*this); }
    void pressStop()  { state->stop(*this); }

    std::string currentState() const { return state->name(); }
    
};

// ----- Concrete States -----
class StoppedState : public PlayerState {
public:
    void play(MediaPlayer& player) override;
    void pause(MediaPlayer& player) override {
        std::cout << "Can't pause — player is stopped.\n";
    }
    void stop(MediaPlayer& player) override {
        std::cout << "Already stopped.\n";
    }
    std::string name() const override { return "Stopped"; }
};

class PlayingState : public PlayerState {
public:
    void play(MediaPlayer& player) override {
        std::cout << "Already playing.\n";
    }
    void pause(MediaPlayer& player) override;
    void stop(MediaPlayer& player) override;
    std::string name() const override { return "Playing"; }
};

class PausedState : public PlayerState {
public:
    void play(MediaPlayer& player) override;
    void pause(MediaPlayer& player) override {
        std::cout << "Already paused.\n";
    }
    void stop(MediaPlayer& player) override;
    std::string name() const override { return "Paused"; }
};

// ----- Transition logic (defined after all classes are visible) -----
void StoppedState::play(MediaPlayer& player) {
    std::cout << "Starting playback.\n";
    player.setState(std::make_unique<PlayingState>());
}

void PlayingState::pause(MediaPlayer& player) {
    std::cout << "Pausing playback.\n";
    player.setState(std::make_unique<PausedState>());
}

void PlayingState::stop(MediaPlayer& player) {
    std::cout << "Stopping playback.\n";
    player.setState(std::make_unique<StoppedState>());
}

void PausedState::play(MediaPlayer& player) {
    std::cout << "Resuming playback.\n";
    player.setState(std::make_unique<PlayingState>());
}

void PausedState::stop(MediaPlayer& player) {
    std::cout << "Stopping from pause.\n";
    player.setState(std::make_unique<StoppedState>());
}



int main()
{
   
    MediaPlayer player(std::make_unique<StoppedState>());

    player.pressPlay();   // Stopped -> Playing
    player.pressPause();  // Playing -> Paused
    player.pressPlay();   // Paused -> Playing (resume)
    player.pressPause();  // Playing -> Paused
    player.pressStop();   // Paused -> Stopped
    player.pressPause();  // invalid: stays Stopped, prints message

    return 0; 

}
