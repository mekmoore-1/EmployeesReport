#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> //ifstream
#include <vector>
#include <algorithm>
#include <random>

// Information of Employees
struct Employees
{
    std::string empName;
    std::string empNumber;
    double hourlyRate;
    double hoursWorked;
    double grossPay;
};




// Function prototypes
void parseString(std::string &line, std::string &field);
void readCSVFile(std::vector<Employees> &Workers);
void printTable(std::vector<Employees> &Workers);
void randomize(std::vector<Employees> &Workers);

int main()
{
    // Created vector to hold all of the employees
    std::vector<Employees> Workers;
    //Reads from the file
    readCSVFile(Workers);

    // Calculated the gross pay for each of the employees
    for (int i = 0; i < Workers.size(); i++)
    {
        Workers[i].grossPay =
            Workers[i].hourlyRate * Workers[i].hoursWorked;
    }

    // Prints the employees in original order
    std::cout << "\nTABLE 1 (ORIGINAL ORDER)\n";
    printTable(Workers);

    // Randomizes the vector of employees
    randomize(Workers);

    // Prints the workers/employees
    std::cout << "\nTABLE 2 - RANDOM ORDER\n";
    printTable(Workers);

    //  Sorted by gross pay from highest to lowest
    std::sort(Workers.begin(), Workers.end(),
        [](const Employees &a, const Employees &b)
        {
            return a.grossPay > b.grossPay;
        });

    // Table 3 Organized File Header
    std::cout << "\nTABLE 3 - SORTED BY GROSS PAY IN DESCENDING ORDER\n";
    printTable(Workers);

    return 0;
}


// Takes one field from the CSV line
void parseString(std::string &line, std::string &field)
{
    int location;

    location = line.find(',');

    field = line.substr(0, location);

    line = line.substr(location + 1, line.length());
}


// Reads the CSV file
void readCSVFile(std::vector<Employees> &employees)
{
    std::ifstream csvFile;

    std::string line;
    std::string empName;
    std::string empNum;
    std::string empRate;
    std::string empTime;

    csvFile.open("C:/Users/eacs/Desktop/EmployeeData.csv");

    if (!csvFile.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    // Reads the header line
    std::getline(csvFile, line);

    // reads one complete line at a time
    while (std::getline(csvFile, line))
    {
        Employees employee;

        parseString(line, empName);
        parseString(line, empNum);
        parseString(line, empRate);
        parseString(line, empTime);

        //String to integer readings
        employee.empName = (empName);
        employee.empNumber = (empNum);
        employee.hourlyRate = std::stod(empRate);
        employee.hoursWorked = std::stod(empTime);

        employee.grossPay =
            employee.hourlyRate * employee.hoursWorked;

        employees.push_back(employee);
    }

    csvFile.close();
}


// Prints the employee table
void printTable(std::vector<Employees> &employees)
{
    std::cout << "-----------------------------------------------------------------------------------------\n";

    std::cout << std::left << std::setw(17) << "NAME"
              << std::right << std::setw(15) << "EMPNUMBER"
              << std::setw(15) << "HOURLY RATE"
              << std::setw(15) << "HOURS WORKED"
              << std::setw(15) << "GROSS PAY"
              << std::endl;

    std::cout << "-----------------------------------------------------------------------------------------\n";

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < employees.size(); i++)
    {
        std::cout << std::left << std::setw(17)
                  << employees[i].empName;

        std::cout << std::right << std::setw(15)
                  << employees[i].empNumber;

        std::cout << std::setw(15)
                  << "$" << employees[i].hourlyRate;

        std::cout << std::setw(14)
                  << employees[i].hoursWorked;

        std::cout << std::setw(14)
                  << "$" << employees[i].grossPay;

        std::cout << std::endl;
    }

    std::cout << std::endl;
}


// Randomizes the employee vector
void randomize(std::vector<Employees> &employees)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(employees.begin(), employees.end(), generator);
}
