/*
Interviewer: An Amazon pickup location has various lockers for packages to be dropped off and picked up. We have both packages and lockers of varying sizes. Model the lockers, packages, and pickup location and implement an algorithm to find the best possible empty locker for a given package efficiently.

Start with Clarifying Questions
A sample communication between a candidate and an interview can look like:

What are the sizes for packages and lockers?
Small, Medium, Large
Can I assume that a package should go to the corresponding locker size?
Yes
What if there is no small locker left and a small package arrives?
Good question, if there is no locker with matching size of the package, the package should go to the next locker size available (e.g. Small package goes inside of a medium locker)
Nice, how many lockers from each size exist in the pickup location?
It changes per pickup location. Your model should be able to handle that.
Understood, what if a package arrives and there is no valid locker available?
Your pickup location should not accept the package.
What do you mean by finding an empty locker efficiently?
Well, customers drop and pick up packages constantly. The lockers becomes full and empty constantly as well. Your code should be able to find an available locker very quickly.
And the list of questions can go on (consider the interview time as well when asking questions) but you got the idea.

Propose Your Solution
Before you try to write any code, communicate with the interviewer about your approach (absolutely important). The interviewer might be able to help you right away if your solution cannot handle the requirements properly.

Note that there is no best solution for a problem. It’s a matter of proposing a good enough solution while being able to justify it. At first, you start with mentioning your classes, like separate classes for PickupLocation, Locker, and Package. For the logic, one possible solution is to use queues to track empty lockers for each size and a hash map to keep track of used lockers. Once you get a green light from the interviewer on your general approach, start coding your solution.

One possible implementation looks like the below (remember that there is no best answer and your code can be much different from this):
*/



#include <iostream>
#include <unordered_map>

using namespace std;

enum class SIZES
{
    SMALL = 0,
    MEDIUM = 1,
    LARGE = 2
};

class Package
{
    SIZES packageSize;
    string packageID;

public:
    Package(const SIZES& sz, const string& _id) : packageSize(sz), packageID(_id){}
    ~Package(){}

    SIZES getSize() const { return packageSize; }
    string getID() const { return packageID; }
};

class Locker
{
    SIZES lockerSize;
    string lockerID;
    Package* packageInsideLocker = NULL;

public:
    Locker(const SIZES& sz, const string& _id) : lockerSize(sz), lockerID(_id){}
    ~Locker()
    {
        delete packageInsideLocker;
    }

    SIZES getSize() const { return lockerSize; }
    string getID() const { return lockerID; }
    void FillLocker(Package* package) { packageInsideLocker = package; }
    const Package* EmptyLocker()
    {
        Package* locker = packageInsideLocker;
        packageInsideLocker = NULL;
        return locker;
    }
    bool IsEmpty() const { return packageInsideLocker == NULL; }
};

class PickUpLocation
{
    // we will make id be identifier to each locker
    unordered_map<string, Locker*> availableLocker;

public:
    // pass in locker id and sizes to create location locker
    PickUpLocation(const unordered_map<string, SIZES>& Lockers)
    {
        for (const auto& locker : Lockers)
        {
            Locker* lock = new Locker(locker.second, locker.first);
            availableLocker.insert(make_pair(locker.first, lock));
        }
    }
    ~PickUpLocation(){}

    void EnlistLocker()
    {
        for (const auto& locker : availableLocker)
        {
            cout << locker.first << endl;
        }
    }

    int GetLocationLockerSizes() const { return availableLocker.size(); }

    int GetAllFreeLocker() const 
    {
        int count = 0;
        for (const auto& locker : availableLocker)
        {
            if (locker.second->IsEmpty()) count++;
        }
        return count;
    }

    const Package* RetrieveLockerByID(string id)
    {
        for (const auto& locker : availableLocker)
        {
            if (locker.first == id)
            {
                // empty the locker
                auto lock = locker.second;
                return lock->EmptyLocker();
            }
        }

        //if we didn't find the locker        
        throw invalid_argument("locker id does not exits!");
    }

    const Package* RetrieveLockerBySIZE(SIZES sz)
    {
        for (const auto& locker : availableLocker)
        {
            if (locker.second->getSize() == sz)
            {
                // empty the locker
                auto lock = locker.second;
                return lock->EmptyLocker();
            }
        }

        //if we didn't find the locker        
        throw invalid_argument("locker id does not exits!");
    }

    bool AssignLocker(Package* pack)
    {
        for (const auto& locker : availableLocker)
        {
            // check if it is available and it fit right size
            auto loc = locker.second;
            if (loc->IsEmpty() && pack->getSize() <= loc->getSize())
            {
                loc->FillLocker(pack);
                return true;
            }
        }
        return false;
    }
    
};

int main()
{
    const unordered_map<string, SIZES> newLockers =
    {
        {"L001", SIZES::SMALL},
        {"L002", SIZES::MEDIUM},
        {"L003", SIZES::LARGE},
    };
    Package pk1(SIZES::SMALL, "pk01");
    Package pk2(SIZES::LARGE, "pk02");

    PickUpLocation ikorodu(newLockers);
    cout << "Total number of locker: " << ikorodu.GetLocationLockerSizes() << endl;
    cout << "Number of free locker: " << ikorodu.GetAllFreeLocker() << endl;
    ikorodu.EnlistLocker();
    
    if (!ikorodu.AssignLocker(&pk1))
    {
        cout << "failed to add packer to locker\n";
    }
    cout << "Number of free locker: " << ikorodu.GetAllFreeLocker() << endl;
    
    if (!ikorodu.AssignLocker(&pk2))
    {
        cout << "failed to add packer to locker\n";
    }
    cout << "Number of free locker: " << ikorodu.GetAllFreeLocker() << endl;
    if (!ikorodu.AssignLocker(&pk2))
    {
        cout << "failed to add packer to locker\n";
    }
    cout << "Number of free locker: " << ikorodu.GetAllFreeLocker() << endl;
    cout << "\n";
}
