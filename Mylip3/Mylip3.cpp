#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric> // Add this header
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
    ~Person();

    std::string getFirstName() const;
    std::string getLastName() const;
    double getFinalGrade() const;
    void inputData();
    void outputData() const;
    void calculateFinalGrade(bool useMedian);
    bool isValid() const;

    friend std::istream& operator>>(std::istream& is, Person& person);
};

Person::Person() : examResult(0.0), finalGrade(0.0) {}

Person::~Person() {}

std::string Person::getFirstName() const {
    return firstName;
}

std::string Person::getLastName() const {
    return lastName;
}

double Person::getFinalGrade() const {
    return finalGrade;
}

void Person::inputData() {
    // Implement if needed
}

void Person::outputData() const {
    // Implement if needed
}

void Person::calculateFinalGrade(bool useMedian) {
    double totalHomework = std::accumulate(homeworkResults.begin(), homeworkResults.end(), 0.0);

    double averageHomework = totalHomework / static_cast<double>(homeworkResults.size());
    finalGrade = useMedian ? (averageHomework + examResult) / 2.0 : averageHomework + examResult;
}

bool Person::isValid() const {
    return !firstName.empty() && !lastName.empty() && !homeworkResults.empty();
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
                break;
            }

            students.push_back(student);
        }
        inputFile.close();

        auto startRead = std::chrono::high_resolution_clock::now();

        // Generate random student data for testing
        for (int i = 1; i <= 5; ++i) {
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

        auto endRead = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationRead = endRead - startRead;
        std::cout << "Time taken to read data and generate random students: " << durationRead.count() << " seconds\n";

        // Sorting and categorization...
        auto startSort = std::chrono::high_resolution_clock::now();

        // Perform sorting and categorization here...
        // Assuming you want to sort students based on their final grade in ascending order
        std::sort(students.begin(), students.end(), [](const Person& a, const Person& b) {
            return a.getFinalGrade() < b.getFinalGrade();
            });

        auto endSort = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationSort = endSort - startSort;
        std::cout << "Time taken for sorting: " << durationSort.count() << " seconds\n";

        // Output to new files...
        auto startOutput = std::chrono::high_resolution_clock::now();

        // Perform output to new files here...
        // Assuming you want to output the sorted students to a new file
        std::ofstream sortedOutputFile("SortedStudents.txt");
        if (!sortedOutputFile.is_open()) {
            throw std::runtime_error("Error: Could not open sorted output file");
        }

        for (const auto& student : students) {
            sortedOutputFile << student.getFirstName() << " " << student.getLastName() << " " << student.getFinalGrade() << "\n";
        }

        sortedOutputFile.close();

        auto endOutput = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationOutput = endOutput - startOutput;
        std::cout << "Time taken for output to new files: " << durationOutput.count() << " seconds\n";
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