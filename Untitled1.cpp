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

class Warden : public Person {
private:
    string designation;

public:
    Warden(const string& _name, int _age, char _gender, const string& _designation)
        : Person(_name, _age, _gender), designation(_designation) {}

    void displayRole() const override {
        cout << "Warden" << endl;
    }
};

class Staff : public Person {
private:
    string role;

public:
    Staff(const string& _name, int _age, char _gender, const string& _role)
        : Person(_name, _age, _gender), role(_role) {}

    void displayRole() const override {
        cout << "Staff" << endl;
    }
};

class Room {
private:
    int roomNumber;
    int capacity;
    vector<Person*> occupants;

public:
    Room(int _roomNumber, int _capacity)
        : roomNumber(_roomNumber), capacity(_capacity) {}

    int getRoomNumber() const {
        return roomNumber;
    }

    int getCapacity() const {
        return capacity;
    }

    int getOccupancy() const {
        return occupants.size();
    }

    bool isAvailable() const {
        return occupants.size() < capacity;
    }

    bool addOccupant(Person* person) {
        if (occupants.size() < capacity) {
            occupants.push_back(person);
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const Room& room) {
        os << "Room Number: " << room.roomNumber << endl;
        os << "Capacity: " << room.capacity << endl;
        os << "Occupancy: " << room.occupants.size() << endl;
        os << "Occupants: ";
        for (const auto& occupant : room.occupants) {
            os << occupant->getName() << " ";
        }
        os << endl;
        return os;
    }
};

class Hostel {
private:
    vector<Room> rooms;
    vector<Student> students;
    vector<Warden> wardens;
    vector<Staff> staff;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void addWarden(const Warden& warden) {
        wardens.push_back(warden);
    }

    void addStaff(const Staff& staffMember) {
        staff.push_back(staffMember);
    }

    bool assignRoomToStudent(const Student& student, int roomNumber) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber && room.isAvailable()) {
                return room.addOccupant(new Student(student));
            }
        }
        return false;
    }

    void displayRoomInformation(int roomNumber) const {
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

    // Add students
    Student student1("John Doe", 20, 'M', 101);
    Student student2("Jane Smith", 19, 'F', 102);
    hostel.addStudent(student1);
    hostel.addStudent(student2);

    // Add wardens
    Warden warden1("David Brown", 35, 'M', "Senior Warden");
    Warden warden2("Emily Johnson", 40, 'F', "Assistant Warden");
    hostel.addWarden(warden1);
    hostel.addWarden(warden2);

    // Add staff
    Staff staff1("Alex Wilson", 28, 'M', "Security");
    Staff staff2("Olivia Davis", 25, 'F', "Housekeeping");
    hostel.addStaff(staff1);
    hostel.addStaff(staff2);

    // Assign rooms to students
    hostel.assignRoomToStudent(student1, 101);
    hostel.assignRoomToStudent(student2, 102);

    // Display room information
    hostel.displayRoomInformation(101);

    return 0;
}
