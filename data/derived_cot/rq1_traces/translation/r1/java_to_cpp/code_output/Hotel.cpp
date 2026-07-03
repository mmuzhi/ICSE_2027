#include <iostream>
#include <map>
#include <string>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const std::map<std::string, int>& m) {
    os << "{";
    bool first = true;
    for (const auto& p : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << p.first << "=" << p.second;
    }
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::map<std::string, std::map<std::string, int>>& m) {
    os << "{";
    bool first = true;
    for (const auto& p : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << p.first << "=" << p.second;
    }
    os << "}";
    return os;
}

class Hotel {
private:
    std::string name;
    std::map<std::string, int> availableRooms;
    std::map<std::string, std::map<std::string, int>> bookedRooms;

public:
    Hotel(const std::string& name, const std::map<std::string, int>& rooms)
        : name(name), availableRooms(rooms) {}

    std::string bookRoom(const std::string& roomType, int roomNumber, const std::string& guestName) {
        if (availableRooms.find(roomType) == availableRooms.end()) {
            return "False";
        }

        int available = availableRooms[roomType];
        if (roomNumber <= available) {
            bookedRooms[roomType][guestName] = roomNumber;
            availableRooms[roomType] = available - roomNumber;
            return "Success!";
        } else {
            return "False";
        }
    }

    bool checkIn(const std::string& roomType, int roomNumber, const std::string& guestName) {
        auto roomIt = bookedRooms.find(roomType);
        if (roomIt == bookedRooms.end()) {
            return false;
        }

        auto& innerMap = roomIt->second;
        auto guestIt = innerMap.find(guestName);
        if (guestIt == innerMap.end()) {
            return false;
        }

        int booked = guestIt->second;
        if (roomNumber > booked) {
            return false;
        } else if (roomNumber == booked) {
            innerMap.erase(guestIt);
        } else {
            guestIt->second = booked - roomNumber;
        }
        return true;
    }

    void checkOut(const std::string& roomType, int roomNumber) {
        availableRooms[roomType] += roomNumber;
    }

    int getAvailableRooms(const std::string& roomType) const {
        auto it = availableRooms.find(roomType);
        if (it != availableRooms.end()) {
            return it->second;
        }
        return 0;
    }

    friend int main();
};

int main() {
    std::map<std::string, int> rooms;
    rooms["single"] = 3;
    rooms["double"] = 2;
    Hotel hotel("Test Hotel", rooms);

    std::cout << std::boolalpha;

    std::cout << hotel.bookRoom("single", 2, "guest 1") << std::endl;
    std::cout << hotel.bookRoom("triple", 2, "guest 1") << std::endl;
    std::cout << hotel.bookRoom("single", 2, "guest 2") << std::endl;
    std::cout << hotel.bookRoom("single", 1, "guest 2") << std::endl;
    std::cout << hotel.bookRoom("single", 3, "guest 1") << std::endl;
    std::cout << hotel.bookRoom("single", 100, "guest 1") << std::endl;

    hotel.checkIn("single", 1, "guest 1");
    std::cout << hotel.bookedRooms << std::endl;
    std::cout << hotel.checkIn("single", 3, "guest 1") << std::endl;
    std::cout << hotel.checkIn("double", 1, "guest 1") << std::endl;
    hotel.checkIn("double", 1, "guest 2");
    std::cout << hotel.bookedRooms << std::endl;

    hotel.checkOut("single", 1);
    std::cout << hotel.availableRooms << std::endl;
    hotel.checkOut("triple", 2);
    std::cout << hotel.availableRooms << std::endl;

    std::cout << hotel.getAvailableRooms("single") << std::endl;

    return 0;
}