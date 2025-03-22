// IncomeCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <unordered_map>

struct SimpleDate
{
    int month;
    int year;
    SimpleDate(int m, int y) : month(m), year(y) {}
    static SimpleDate now() { return SimpleDate(8, 2025); }
};

struct Income
{
    int year;
    int amount;
    Income(const int& y, const int& a) : year(y), amount(a) {}
};

class IncomeCalculator
{
private:
    SimpleDate startDate;
    int baseSalaryPerYear;
public:
    IncomeCalculator(const SimpleDate& startDate, int baseSalaryPerYear) :
        startDate(startDate), baseSalaryPerYear(baseSalaryPerYear)
    { }

    // Calaculate income per year until the present date
    std::vector<Income> calculateIncome() const
    {
        int i = 0;
        std::vector<Income> incomePerYear;
        SimpleDate currentDate = SimpleDate::now();

        // Iterate through each year and month from the start date to the current date
        for(int year = startDate.year; year <= currentDate.year; ++year)
        {
            int startMonth = (year == startDate.year) ? startDate.month : 1;
            int endMonth = (year == currentDate.year) ? currentDate.month - 1 : 12;

            // Calculate the number of month worked in the current year
            int monthsWorked = endMonth - startMonth + 1;
            if (monthsWorked > 0)
            {
                int income = (round(baseSalaryPerYear / 12)) * monthsWorked;
                incomePerYear.push_back(Income(year, income));
            }
        }
        return incomePerYear;
    }
};

int main()
{
    SimpleDate startDate(8, 2023);
    int baseSalaryPerYear = 65000;

    IncomeCalculator calculator(startDate, baseSalaryPerYear);

    auto incomeperyear = calculator.calculateIncome();
    std::cout << "Income per year :\n";
    for (const auto& entry : incomeperyear)
        std::cout << entry.year << ": $" << std::setw(6) << entry.amount << std::endl;

    return 0;
}
