#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::vector<double> homeworkResults;
    double examResult;
    double finalGrade;

public:
    Person();
    Person(const Person& other);
    ~Person();

    Person& operator=(const Person& other);

    friend std::istream& operator>>(std::istream& is, Person& person);

    void inputData();
    void outputData() const;
    void calculateFinalGrade(bool useMedian);
    bool isValid() const;

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
    double totalHomework = 0.0;
    for (double score : homeworkResults) {
        totalHomework += score;
    }

    double averageHomework = totalHomework / static_cast<double>(homeworkResults.size());
    finalGrade = useMedian ? (averageHomework + examResult) / 2.0 : averageHomework + examResult;
}

bool Person::isValid() const {
    return !firstName.empty() && !lastName.empty() && !homeworkResults.empty();
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

// Function to convert int to string using std::ostringstream
std::string intToString(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

int main() {
    try {
        std::ifstream inputFile("Students.txt");
        if (!inputFile.is_open()) {
            throw std::runtime_error("Error: Could not open file 'Students.txt'");
        }

        std::vector<Person> students;
        while (true) {
            Person student;
            inputFile >> student;

            // Check if the read data is valid
            if (!student.isValid()) {
                break; // Break the loop if the data is not valid
            }

            students.push_back(student);
        }
        inputFile.close();

        auto startRead = std::chrono::high_resolution_clock::now();

        // Generate random student data for testing
        for (int i = 1; i <= 5; ++i) { // Changed the loop to generate 5 files for simplicity
            std::ofstream outputFile("RandomStudents" + intToString(i) + ".txt");
            if (!outputFile.is_open()) {
                throw std::runtime_error("Error: Could not open output file");
            }

            outputFile << "Name" << i << " Surname" << i << " ";
            for (int j = 0; j < 5; ++j) {
                outputFile << rand() % 11 << " ";
            }
            outputFile << rand() % 11 << " -1\n";

            outputFile.close();
        }

        // Sorting and categorization...
        // Output to new files...

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - startRead;
        std::cout << "Time taken to read data and generate random students: " << duration.count() << " seconds\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception occurred." << std::endl;
        return 1;
    }

    std::cout << "Program executed successfully.\n";
    return 0;
}