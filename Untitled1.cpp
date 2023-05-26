#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
protected:
    string name;
    int age;
    char gender;

public:
    Person(const string& _name, int _age, char _gender)
        : name(_name), age(_age), gender(_gender) {}

    virtual ~Person() {}

    string getName() const {
        return name;
    }

    virtual void displayRole() const = 0;
};

class Student : public Person {
private:
    int rollNumber;

public:
    Student(const string& _name, int _age, char _gender, int _rollNumber)
        : Person(_name, _age, _gender), rollNumber(_rollNumber) {}

    void displayRole() const override {
        cout << "Student" << endl;
    }
};

class Staff : public Person {
private:
    string job;
    char shift;

public:
    Staff(const string& _name, int _age, char _gender, const string& _job, char _shift)
        : Person(_name, _age, _gender), job(_job), shift(_shift) {}

    void displayRole() const override {
        cout << "Staff" << endl;
    }
};

class Room {
private:
    int roomNumber;
    int capacity;
    vector<Person*> borders;

public:
    Room(int _roomNumber, int _capacity)
        : roomNumber(_roomNumber), capacity(_capacity) {}

    int getRoomNumber() const {
        return roomNumber;
    }

    int getCapacity() const {
        return capacity;
    }

    int getvacancy() const {
        return borders.size();
    }

    bool isAvailable() const {
        return borders.size() < capacity;
    }

    bool addborder(Person* person) {
        if (borders.size() < capacity) {
            borders.push_back(person);
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const Room& room) {
        os << "Room Number: " << room.roomNumber << endl;
        os << "Capacity: " << room.capacity << endl;
        os << "Vacancy: " << room.borders.size() << endl;
        os << "borders: ";
        for (const auto& border : room.borders) {
            os << border->getName() << " ";
        }
        os << endl;
        return os;
    }
};

class Hostel {
private:
    vector<Room> rooms;
    vector<Student> students;
    vector<Staff> staff;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void addStaff(const Staff& staffMember) {
        staff.push_back(staffMember);
    }

    bool assignRoomToStudent(const Student& student, int roomNumber) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber && room.isAvailable()) {
                return room.addborder(new Student(student));
            }
        }
        return false;
    }

    void displayRoomInfo(int roomNumber) const {
        for (const auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber) {
                cout << room;
                return;
            }
        }
        cout << "Room not found!" << endl;
    }
};

int main() {
    Hostel hostel;

    Student student1("Talha Kabir", 22, 'M', 101);
    Student student2("Sana Khan", 23, 'F', 102);
    hostel.addStudent(student1);
    hostel.addStudent(student2);

    Staff staff1("Rahim Mia", 28, 'M', "Security", 'N');
    Staff staff2("Jarina Begum", 42, 'F', "Cook", 'D');
    hostel.addStaff(staff1);
    hostel.addStaff(staff2);

    hostel.assignRoomToStudent(student1, 101);
    hostel.assignRoomToStudent(student2, 102);

    hostel.displayRoomInfo(101);

    return 0;
}
