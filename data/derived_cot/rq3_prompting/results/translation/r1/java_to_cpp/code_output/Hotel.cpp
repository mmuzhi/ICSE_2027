#include <iostream>
#include <map>
#include <string>
#include <sstream>

// Helper: print std::map in Java's HashMap toString style
std::ostream& operator<<(std::ostream& os, const std::map<std::string, int>& m) {
    os << "{";
    bool first = true;
    for (const auto& p : m) {
        if (!first) os << ", ";
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
        if (!first) os << ", ";
        first = false;
        os << p.first << "=" << p.second;   // uses the overload above
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

    std::string bookRoom(const std::string& roomType, int roomNumber, const std::string& name) {
        auto it = availableRooms.find(roomType);
        if (it == availableRooms.end()) {
            return "False";
        }
        int available = it->second;
        if (roomNumber <= available) {
            bookedRooms[roomType][name] = roomNumber;
            availableRooms[roomType] = available - roomNumber;
            return "Success!";
        } else {
            return "False";
        }
    }

    bool checkIn(const std::string& roomType, int roomNumber, const std::string& name) {
        auto itType = bookedRooms.find(roomType);
        if (itType == bookedRooms.end()) return false;
        auto itName = itType->second.find(name);
        if (itName == itType->second.end()) return false;

        int booked = itName->second;
        if (roomNumber > booked) {
            return false;
        } else if (roomNumber == booked) {
            itType->second.erase(itName);
        } else {
            itName->second = booked - roomNumber;
        }
        return true;
    }

    void checkOut(const std::string& roomType, int roomNumber) {
        availableRooms[roomType] += roomNumber;
    }

    int getAvailableRooms(const std::string& roomType) {
        auto it = availableRooms.find(roomType);
        return (it != availableRooms.end()) ? it->second : 0;
    }

    // For printing bookedRooms (used in main)
    const std::map<std::string, std::map<std::string, int>>& getBookedRooms() const {
        return bookedRooms;
    }

    const std::map<std::string, int>& getAvailableRoomsMap() const {
        return availableRooms;
    }
};

int main() {
    std::map<std::string, int> rooms;
    rooms["single"] = 3;
    rooms["double"] = 2;
    Hotel hotel("Test Hotel", rooms);

    std::cout << hotel.bookRoom("single", 2, "guest 1") << std::endl;
    std::cout << hotel.bookRoom("triple", 2, "guest 1") << std::endl;
    std::cout << hotel.bookRoom("single", 2, "guest 2") << std::endl;
    std::cout << hotel.bookRoom("single", 1, "guest 2") << std::endl;
    std::cout << hotel.bookRoom("single", 3, "guest 1") << std::endl;
    std::cout << hotel.bookRoom("single", 100, "guest 1") << std::endl;

    hotel.checkIn("single", 1, "guest 1");
    std::cout << hotel.getBookedRooms() << std::endl;
    std::cout << (hotel.checkIn("single", 3, "guest 1") ? "true" : "false") << std::endl;
    std::cout << (hotel.checkIn("double", 1, "guest 1") ? "true" : "false") << std::endl;
    hotel.checkIn("double", 1, "guest 2");
    std::cout << hotel.getBookedRooms() << std::endl;

    hotel.checkOut("single", 1);
    std::cout << hotel.getAvailableRoomsMap() << std::endl;
    hotel.checkOut("triple", 2);
    std::cout << hotel.getAvailableRoomsMap() << std::endl;

    std::cout << hotel.getAvailableRooms("single") << std::endl;

    return 0;
}