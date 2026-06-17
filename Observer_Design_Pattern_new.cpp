#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

// Forward declaration
class ObservableInterface;

// --- Observer Interface ---
class ObserverInterface {
public:
    virtual ~ObserverInterface() = default;
    // The observer pulls data from the subject passed via pointer
    virtual void update(ObservableInterface* obj) = 0;
};

// --- Observable Interface ---
class ObservableInterface {
protected:
    // Managed directly in the interface
    std::vector<std::shared_ptr<ObserverInterface>> observers;

public:
    virtual ~ObservableInterface() = default;

    // Implemented directly in the interface
    void add(std::shared_ptr<ObserverInterface> obj) {
        if (obj) {
            observers.push_back(obj);
        }
    }

    // Implemented directly in the interface
    void remove(std::shared_ptr<ObserverInterface> obj) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), obj), 
            observers.end()
        );
    }

    // Notifies all registered observers
    void notify() {
        for (const auto& observer : observers) {
            if (observer) {
                observer->update(this);  //or we can simply pass the tmpertaure here observer->update(tempertaure)
            }
        }
    }

    // Pure virtual data methods for concrete classes to implement
    virtual void setData(int data) = 0;
    virtual int getData() const = 0;
};

// --- Real-Life Concrete Observable: WeatherStation ---
class WeatherStation : public ObservableInterface {
private:
    int temperature = 0; // The data being tracked

public:
    // Sets new temperature and automatically updates all displays
    void setData(int data) override {
        std::cout << "\n[WeatherStation] Sensing new temperature: " << data << "°C\n";
        temperature = data;
        notify(); 
    }

    int getData() const override {
        return temperature;
    }
};

// --- Real-Life Concrete Observer: PhoneDisplay ---
class PhoneDisplay : public ObserverInterface {
private:
    std::string deviceOwner;

public:
    PhoneDisplay(std::string owner) : deviceOwner(std::move(owner)) {}

    void update(ObservableInterface* obj) override {
        if (obj) {
            // Pulling the updated temperature from the WeatherStation
            int currentTemp = obj->getData();
            std::cout << " -> [" << deviceOwner << "'s Phone] Display updated to: " << currentTemp << "°C\n";
        }
    }
};

// --- Main Execution ---
int main() {
    // Create our real-world subject
    auto weatherStation = std::make_shared<WeatherStation>();

    // Create real-world observers
    auto alicePhone = std::make_shared<PhoneDisplay>("Alice");
    auto bobPhone = std::make_shared<PhoneDisplay>("Bob");

    // Register devices to the weather station
    weatherStation->add(alicePhone);
    weatherStation->add(bobPhone);

    // Simulate temperature changes
    weatherStation->setData(24);
    weatherStation->setData(30);
    
    // Unregister Alice's device
    std::cout << "\n--- Alice disconnects from Weather Station ---\n";
    weatherStation->remove(alicePhone);

    // Next update will only hit Bob's phone
    weatherStation->setData(18);

    return 0;
}
