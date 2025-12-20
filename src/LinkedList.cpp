#include "LinkedList.h"
#include "UtilityFunctions.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// ============ LINKED LIST NODE ============
ListNode::ListNode(int id, string name, double s)
    : courseId(id), courseName(name), score(s), next(nullptr), prev(nullptr) {
    time(&completionDate);
}

// ============ LINKED LIST CLASS ============
LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

LinkedList::~LinkedList() {
    ListNode* current = head;
    while (current) {
        ListNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void LinkedList::append(int courseId, string courseName, double score) {
    ListNode* newNode = new ListNode(courseId, courseName, score);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void LinkedList::display() {
    cout << "\n========== Completed Courses History ==========\n";
    ListNode* current = head;
    int count = 1;
    while (current) {
        cout << count++ << ". " << current->courseName
            << " (ID: " << current->courseId << ") - Score: "
            << fixed << setprecision(1) << current->score << "/100\n";
        current = current->next;
    }
    if (size == 0) cout << "No completed courses yet.\n";
    cout << "=============================================\n\n";
}

double LinkedList::getAverageScore() {
    if (size == 0) return 0.0;
    double total = 0.0;
    ListNode* current = head;
    while (current) {
        total += current->score;
        current = current->next;
    }
    return total / size;
}

int LinkedList::getSize() const { return size; }

string LinkedList::serialize() const {
    stringstream ss;
    ss << size << "\n";
    ListNode* current = head;
    while (current) {
        ss << current->courseId << "," << current->courseName << ","
           << current->score << "," << current->completionDate << "\n";
        current = current->next;
    }
    return ss.str();
}

void LinkedList::deserialize(ifstream& file) {
    int count;
    file >> count;
    file.ignore();
    
    for (int i = 0; i < count; i++) {
        string line;
        getline(file, line);
        if (!line.empty()) {
            vector<string> parts = split(line, ',');
            if (parts.size() >= 3) {
                append(stoi(parts[0]), parts[1], stod(parts[2]));
            }
        }
    }
}

void LinkedList::clear() {
    ListNode* current = head;
    while (current) {
        ListNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}
