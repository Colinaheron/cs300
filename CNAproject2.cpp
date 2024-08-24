//Colin Aheron SNHU CS300 2024
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cctype>

// Course class to represent each course
class Course {
public:
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;

    Course(const std::string& number, const std::string& title)
        : courseNumber(number), courseTitle(title) {}

    void addPrerequisite(const std::string& prereq) {
        prerequisites.push_back(prereq);
    }
};

// Function to load data from file into the data structure
void loadDataStructure(std::vector<Course>& courses) {
    std::string filename;
    std::cout << "Enter the file name containing course data: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    courses.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string courseNumber, courseTitle, prereq;

        if (std::getline(iss, courseNumber, ',') &&
            std::getline(iss, courseTitle, ',')) {
            Course course(courseNumber, courseTitle);

            while (std::getline(iss, prereq, ',')) {
                if (!prereq.empty()) {
                    course.addPrerequisite(prereq);
                }
            }

            courses.push_back(course);
        }
    }

    std::cout << "Data loaded successfully.\n";
}

// Function to print the course list in alphanumeric order
void printCourseList(const std::vector<Course>& courses) {
    std::vector<Course> sortedCourses = courses;
    std::sort(sortedCourses.begin(), sortedCourses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    std::cout << "Here is a sample schedule:\n";
    for (const auto& course : sortedCourses) {
        std::cout << course.courseNumber << ", " << course.courseTitle << "\n";
    }
}

// Helper function to convert a string to lowercase
std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return s;
}


// Function to print information about a specific course (case-insensitive)
void printCourseInfo(const std::vector<Course>& courses) {
    std::string courseNumber;
    std::cout << "What course do you want to know about? ";
    std::cin >> courseNumber;

    // Convert input to lowercase for case-insensitive comparison
    std::string lowerCourseNumber = toLower(courseNumber);

    auto it = std::find_if(courses.begin(), courses.end(),
        [&lowerCourseNumber](const Course& c) {
            return toLower(c.courseNumber) == lowerCourseNumber;
        });

    if (it != courses.end()) {
        std::cout << it->courseNumber << ", " << it->courseTitle << "\n";
        if (!it->prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (size_t i = 0; i < it->prerequisites.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << it->prerequisites[i];
            }
            std::cout << "\n";
        }
    }
    else {
        std::cout << "Course not found.\n";
    }
}

// Function to display the menu and get user choice
int displayMenu() {
    int choice;
    std::cout << "\n1. Load Data Structure.\n"
        << "2. Print Course List.\n"
        << "3. Print Course.\n"
        << "9. Exit\n"
        << "What would you like to do? ";
    std::cin >> choice;
    return choice;
}

int main() {
    std::vector<Course> courses;
    bool dataLoaded = false;

    std::cout << "Welcome to the course planner.\n";

    while (true) {
        int choice = displayMenu();

        switch (choice) {
        case 1:
            try {
                loadDataStructure(courses);
                dataLoaded = true;
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            break;
        case 2:
            if (dataLoaded) {
                printCourseList(courses);
            }
            else {
                std::cout << "Please load data first.\n";
            }
            break;
        case 3:
            if (dataLoaded) {
                printCourseInfo(courses);
            }
            else {
                std::cout << "Please load data first.\n";
            }
            break;
        case 9:
            std::cout << "Thank you for using the course planner!\n";
            return 0;
        default:
            std::cout << choice << " is not a valid option.\n";
        }
    }

    return 0;
}