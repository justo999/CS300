// Justin Fanesi
// CS 300 Project 2
<iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Course class definition
class Course {
public:
    string title;
    vector<string> prerequisites;

    Course(string t, vector<string> prereqs) : title(t), prerequisites(prereqs) {}
};
 // Function to load the course data
void loadDataStructure(const string& fileName, unordered_map<string, Course>& courseMap) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Parsing the line and creating Course objects
        size_t pos = line.find(',');
        string courseCode = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        string courseTitle = line.substr(0, pos);
        line.erase(0, pos + 1);

        vector<string> prerequisites;
        while (!line.empty()) {
            pos = line.find(',');
            string prereq = line.substr(0, pos);
            prerequisites.push_back(prereq);
            if (pos == string::npos) break;
            line.erase(0, pos + 1);
        }

        Course course(courseTitle, prerequisites);

        // Use emplace to insert into unordered_map
        courseMap.emplace(courseCode, course);
    }

    file.close();
}


// Function to print course list in alphanumeric order
void printCourseList(const unordered_map<string, Course>& courseMap) {
    vector<string> courseCodes;
    for (const auto& entry : courseMap) {
        courseCodes.push_back(entry.first);
    }

    sort(courseCodes.begin(), courseCodes.end());

    cout << "Here is a sample schedule:" << endl;
    for (const auto& code : courseCodes) {
        cout << code << ", " << courseMap.at(code).title << endl;
    }
}

// Function to print course information
void printCourse(const unordered_map<string, Course>& courseMap) {
    string courseCode;
    cout << "What course do you want to know about? ";
    cin >> courseCode;

    transform(courseCode.begin(), courseCode.end(), courseCode.begin(), ::toupper);

    if (courseMap.find(courseCode) != courseMap.end()) {
        const Course& course = courseMap.at(courseCode);
        cout << courseCode << ", " << course.title << endl;
        cout << "Prerequisites: ";

        // Check if there are prerequisites
        if (!course.prerequisites.empty()) {
            // Print the first prerequisite
            cout << course.prerequisites[0];

            // Print the remaining prerequisites with commas
            for (size_t i = 1; i < course.prerequisites.size(); ++i) {
                cout << ", " << course.prerequisites[i];
            }
        }

        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}

int main() {
    unordered_map<string, Course> courseMap;

    cout << "Welcome to the course planner." << endl;

    int choice;
    do {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            string fileName = "ABCU_Advising_Program_Input.txt";
            loadDataStructure(fileName, courseMap);
            cout << "Data loaded successfully." << endl;
        }
        break;

        case 2:
            printCourseList(courseMap);
            break;
        case 3:
            printCourse(courseMap);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    } while (choice != 9);

    return 0;
}
