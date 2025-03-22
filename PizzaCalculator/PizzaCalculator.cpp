// PizzaCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Pizza Base Class
class Base
{
private:
    std::string name;
    double price;
public:
    Base(const std::string& name, const double& price) : 
        name(name), price(price)
    { }

    std::string getName() const { return name;  }

    double getPrice() const { return price;  }
};

// Pizza Size Class
class Size
{
private:
    std::string name;
    double price;
public:
    Size(const std::string& name, const double& price) :
        name(name), price(price)
    {
    }

    std::string getName() const { return name; }

    double getPrice() const { return price; }
};

// Pizza Topping Class
class Topping
{
private:
    std::string name;
    double price;
public:
    Topping(const std::string& name, const double& price) :
        name(name), price(price)
    {
    }

    std::string getName() const { return name; }

    double getPrice() const { return price; }
};

class Pizza 
{
private:
    Base base;
    Size size;
    std::vector<Topping> toppings;
public:
    Pizza(const Base& base, const Size& size) :
        base(base), size(size)
    { }

    void addTopping(const Topping& topping) { toppings.push_back(topping); }

    double calculateTotalPrice() const
    {
        double totalPrice = base.getPrice() + size.getPrice();

        for (const auto& t : toppings)
        {
            totalPrice += t.getPrice();
        }

        return totalPrice;
    }
};

template<typename T>
void display_options(const std::unordered_map<std::string, T>& options, const std::string& title)
{
    cout << title << ": \n";
    for (const auto& op : options)
    {
        cout << "- " << op.first << ": $" << op.second.getPrice() << endl;
    }
}

//stock get_user_choice(const std::unordered_map<std::string, stock>options, const std::string& prompt);




int main()
{
    Pizza P1(Base("B1", 2.3), Size("S", 4.9));
    cout << "P1 cost: " << P1.calculateTotalPrice() << endl;

    Pizza P2(Base("B1", 2.3), Size("S", 4.9));
    P2.addTopping(Topping("cherry", 3.2));
    P2.addTopping(Topping("cocoa", 2.2));
    cout << "P2 cost: " << P2.calculateTotalPrice() << endl;

    Pizza P3(Base("B1", 2.3), Size("S", 4.9));
    cout << "P3 cost: " << P3.calculateTotalPrice() << endl;

    Pizza P4(Base("B1", 2.3), Size("S", 4.9));
    cout << "P4 cost: " << P4.calculateTotalPrice() << endl;
    return 0;
}
