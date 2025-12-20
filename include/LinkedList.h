#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <fstream>
#include <ctime>

// ============ LINKED LIST NODE ============
class ListNode {
public:
    int courseId;
    std::string courseName;
    double score;
    time_t completionDate;
    ListNode* next;
    ListNode* prev;

    ListNode(int id, std::string name, double s);
};

// ============ LINKED LIST CLASS ============
class LinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int size;

public:
    LinkedList();
    ~LinkedList();
    
    void append(int courseId, std::string courseName, double score);
    void display();
    double getAverageScore();
    int getSize() const;
    std::string serialize() const;
    void deserialize(std::ifstream& file);
    void clear();
};

#endif // LINKEDLIST_H
