#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::vector<double> homeworkResults;
    double examResult;
    double finalGrade;

public:
    // Constructors
    Person();
    Person(const Person& other);
    ~Person();

    // Assignment-copy operator
    Person& operator=(const Person& other);

    // Overloaded >> operator
    friend std::istream& operator>>(std::istream& is, Person& person);

    // Data input method
    void inputData();

    // Data output method
    void outputData() const;

    // Calculation method for the final grade
    void calculateFinalGrade(bool useMedian);

    // Getter functions
    std::string getFirstName() const;
    std::string getLastName() const;
    double getFinalGrade() const;
};

Person::Person() : examResult(0.0), finalGrade(0.0) {}

Person::Person(const Person& other) : firstName(other.firstName), lastName(other.lastName), homeworkResults(other.homeworkResults), examResult(other.examResult), finalGrade(other.finalGrade) {}

Person::~Person() {}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        homeworkResults = other.homeworkResults;
        examResult = other.examResult;
        finalGrade = other.finalGrade;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, Person& person) {
    is >> person.firstName >> person.lastName;
    double score;
    while (is >> score) {
        if (score < 0) {
            break;
        }
        person.homeworkResults.push_back(score);
    }
    is >> person.examResult;
    return is;
}

void Person::inputData() {
    // No changes here
}

void Person::outputData() const {
    // No changes here
}

void Person::calculateFinalGrade(bool useMedian) {
    // Calculate the final grade based on homework and exam results
    double totalHomework = 0.0;
    for (double score : homeworkResults) {
        totalHomework += score;
    }

    double averageHomework = totalHomework / static_cast<double>(homeworkResults.size());

    // Use either average or median based on the flag
    finalGrade = useMedian ? (averageHomework + examResult) / 2.0 : averageHomework + examResult;
}

std::string Person::getFirstName() const {
    return firstName;
}

std::string Person::getLastName() const {
    return lastName;
}

double Person::getFinalGrade() const {
    return finalGrade;
}

int main() {
    // Reading data from "Students.txt"
    std::ifstream inputFile("Students.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file 'Students.txt'\n";
        return 1;
    }

    // Vector to store student objects
    std::vector<Person> students;

    // Read data from the file
    while (!inputFile.eof()) {
        Person student;
        inputFile >> student;
        students.push_back(student);
    }

    // Close the input file
    inputFile.close();

    // Output the header
    std::cout << std::setw(12) << "Name" << std::setw(12) << "Surname"
        << std::setw(18) << "Final (Avg.)" << std::setw(15) << "Final (Med.)\n";
    std::cout << std::setfill('-') << std::setw(60) << "" << std::setfill(' ') << std::endl;

    // Output the data for each student
    for (Person& student : students) {
        student.calculateFinalGrade(false); // Calculate average
        std::cout << std::setw(12) << student.getFirstName() << std::setw(12) << student.getLastName()
            << std::setw(18) << std::fixed << std::setprecision(2) << student.getFinalGrade();

        student.calculateFinalGrade(true); // Calculate median
        std::cout << std::setw(15) << std::fixed << std::setprecision(2) << student.getFinalGrade() << std::endl;
    }

    std::cout << "Program executed successfully.\n";  // Add this line for confirmation

    return 0;
}