/*
1. Add items to the vending machine in fixed number of slots
2. Payment using card or cash
3. Select item to dispense
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Product
{
public:
    virtual float GetPrice() = 0;
};

class Payment
{
public:
    virtual float CheckOut(Product* p) = 0;
};

// Create Drink Classes
class Water : public Product
{
public:
    float GetPrice()
    {
        return 1.0;
    }
};

class Coke : public Product
{
public:
    float GetPrice()
    {
        return 1.2;
    }
};

class CardPayment : public Payment
{
public:
    float CheckOut(Product* p) override
    {
        return 0.8 * p->GetPrice();
    }
};

class CashPayment : public Payment
{
public:
    float CheckOut(Product* p) override
    {
        return 1.0 * p->GetPrice();
    }
};

class VendingMachine
{
    unordered_map<string, Product*> slots;
    int capacity;
public:
    VendingMachine(int cap) : capacity(cap) {}
    ~VendingMachine(){}

    bool AddProduct(string id, Product* p)
    {
        if (slots.size() >= capacity)
        {
            return false;
        }
        slots.insert({ id, p });
        return true;
    }

    Product* PlaceOrder(string id)
    {        
        Product* res = NULL;
        if (slots.find(id) != slots.end())
        {
            res = slots[id];
        }
        return res;
    }

    float Checkout(vector<Product*> prod, Payment* pay)
    {
        float total = 0;
        for (auto p : prod)
        {
            total += pay->CheckOut(p);
        }
        return total;
    }
};

class Customer
{
    VendingMachine* vm;
    vector<Product*> cart;

public:
    Customer(VendingMachine* _vm) : vm(_vm) {}

    ~Customer()
    {
        delete vm;
        for (auto* c : cart)
        {
            delete c;
        }
    }

    bool Select(string id)
    {
        Product* p = vm->PlaceOrder(id);

        if (p != NULL)
        {
            cart.push_back(p);
            return true;
        }
        return false;
    }

    float CheckOut(Payment* payment)
    {
        return vm->Checkout(cart, payment);
    }
};




int main()
{
    Product* W1 = new Water();
    Product* W2 = new Water();
    Product* W3 = new Water();
    Product* C1 = new Coke();
    Product* C2 = new Coke();
    Product* C3 = new Coke();

    // stock up our vending machine
    VendingMachine* vm = new VendingMachine(6);
    vm->AddProduct("W1", W1);
    vm->AddProduct("W2", W2);
    vm->AddProduct("W3", W3);
    vm->AddProduct("C1", C1);
    vm->AddProduct("C2", C2);
    vm->AddProduct("C3", C3);

    // Create customer
    Customer* cus = new Customer(vm);
    cus->Select("W1");
    cus->Select("C1");

    // Create payment
    Payment* card = new CardPayment();

    float pay = cus->CheckOut(card);

    cout << "total due payment: " << pay << "\n";
}
