// LogicalAndMaintainable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

struct SimpleDate 
{
    int month;
    int year;

    static SimpleDate now() 
    {
        // This function should return the current date.
        // For simplicity, let's assume the current date is August 2020.
        return { 8, 2020 };
    }
};

struct Income 
{
    int year;
    int amount;
};

std::vector<Income> calculateIncome(SimpleDate startDate, int baseSalary) 
{
    std::vector<Income> incomes;
    SimpleDate currentDate = SimpleDate::now();
    int monthlySalary = baseSalary / 12;

    for (int year = startDate.year; year <= currentDate.year; ++year) 
    {
        int monthsWorked = 12;

        if (year == startDate.year) 
        {
            monthsWorked -= (startDate.month - 1);
        }
        if (year == currentDate.year) 
        {
            monthsWorked = currentDate.month - 1;
        }

        int income = monthsWorked * monthlySalary;
        incomes.push_back({ year, income });
    }

    return incomes;
}

int main() 
{
    SimpleDate startDate = { 2, 2018 };
    int baseSalary = 60000;

    std::vector<Income> incomes = calculateIncome(startDate, baseSalary);

    for (const auto& income : incomes) 
    {
        std::cout << income.year << ": " << income.amount << std::endl;
    }

    return 0;
}
