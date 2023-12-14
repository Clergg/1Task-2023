#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <locale>

class Person {
private:
    std::string first_name;
    std::string last_name;
    double homework_score;
    double exam_score;
    double final_grade;

public:
    Person(const std::string& _first_name, const std::string& _last_name, double _homework_score, double _exam_score)
        : first_name(_first_name), last_name(_last_name), homework_score(_homework_score), exam_score(_exam_score) {
        final_grade = 0.0;
    }

    Person& operator=(const Person& other) {
        if (this == &other) {
            return *this;
        }
        first_name = other.first_name;
        last_name = other.last_name;
        homework_score = other.homework_score;
        exam_score = other.exam_score;
        final_grade = other.final_grade;
        return *this;
    }

    Person(const Person& other) {
        first_name = other.first_name;
        last_name = other.last_name;
        homework_score = other.homework_score;
        exam_score = other.exam_score;
        final_grade = other.final_grade;
    }

    ~Person() {
        // Clean up resources here if necessary
    }

    void display_data() const {
        std::cout << first_name << "\t" << last_name << "\t" << std::fixed << std::setprecision(2) << final_grade << std::endl;
    }

    void calculate_final_grade(bool use_average) {
        if (use_average) {
            final_grade = (homework_score + exam_score) / 2;
        }
        else {
            // You can implement median-based calculation here
        }
    }
};

Person create_random_person() {
    static const std::string first_names[] = { "minos", "david", "Alex", "Elena", "macxi", "tamon" };
    static const std::string last_names[] = { "jiles", "billy", "Brown", "Lee", "brond", "Kim" };

    std::string random_first_name = first_names[rand() % 6];
    std::string random_last_name = last_names[rand() % 6];
    double random_score1 = static_cast<double>(rand() % 101);
    double random_score2 = static_cast<double>(rand() % 101);

    return Person(random_first_name, random_last_name, random_score1, random_score2);
}

int main() {
    std::locale::global(std::locale("en_US.UTF-8"));

    srand(static_cast<unsigned int>(time(0)));

    int num_people;
    std::cout << "Enter the number of people: ";
    std::cin >> num_people;

    std::vector<Person> people;
    people.reserve(num_people);

    for (int i = 0; i < num_people; ++i) {
        Person person = create_random_person();
        person.calculate_final_grade(true); // Use the average
        people.push_back(person);
    }

    std::cout << "First Name\tLast Name\tFinal Grade" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    for (const Person& person : people) {
        person.display_data();
    }

    return 0;
}