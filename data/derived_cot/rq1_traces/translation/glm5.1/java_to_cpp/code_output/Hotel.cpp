#include <iostream>
#include <string>
#include <unordered_map>

void printMap(std::ostream& os, const std::unordered_map<std::string, int>& m) {
    os << "{";
    bool first = true;
    for (const auto& p : m) {
        if (!first) os << ", ";
        first = false;
        os << p.first << "=" << p.second;
    }
    os << "}";
}

void printNestedMap(std::ostream& os, const std::unordered_map<std::string, std::unordered_map<std::string, int>>& m) {
    os << "{";
    bool first = true;
    for (const auto& p : m) {
        if (!first) os << ", ";
        first = false;
        os << p.first << "=";
        printMap(os, p.second);
    }
    os << "}";
}

class Hotel {
public:
    std::string name;
    std::unordered_map<std::string, int> availableRooms;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> bookedRooms;

    Hotel(const std::string& name, const std::unordered_map<std::string, int>& rooms)
        : name(name), availableRooms(rooms), bookedRooms() {}

    std::string bookRoom(const std::string& roomType, int roomNumber, const std::string& guestName) {
        if (availableRooms.find(roomType) == availableRooms.end()) {
            return "False";
        }

        int available = availableRooms[roomType];
        if (roomNumber <= available) {
            if (bookedRooms.find(roomType) == bookedRooms.end()) {
                bookedRooms[roomType] = std::unordered_map<std::string, int>();
            }
            bookedRooms[roomType][guestName] = roomNumber;
            availableRooms[roomType] = available - roomNumber;
            return "Success!";
        } else {
            return "False";
        }
    }

    bool checkIn(const std::string& roomType, int roomNumber, const std::string& guestName) {
        if (bookedRooms.find(roomType) == bookedRooms.end() ||
            bookedRooms[roomType].find(guestName) == bookedRooms[roomType].end()) {
            return false;
        }

        int booked = bookedRooms[roomType][guestName];
        if (roomNumber > booked) {
            return false;
        } else if (roomNumber == booked) {
            bookedRooms[roomType].erase(guestName);
        } else {
            bookedRooms[roomType][guestName] = booked - roomNumber;
        }
        return true;
    }

    void checkOut(const std::string& roomType, int roomNumber) {
        int current = 0;
        auto it = availableRooms.find(roomType);
        if (it != availableRooms.end()) {
            current = it->second;
        }
        availableRooms[roomType] = current + roomNumber;
    }

    int getAvailableRooms(const std::string& roomType) {
        auto it = availableRooms.find(roomType);
        if (it != availableRooms.end()) {
            return it->second;
        }
        return 0;
    }
};

int main() {
    std::cout << std::boolalpha;

    std::unordered_map<std::string, int> rooms;
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
    printNestedMap(std::cout, hotel.bookedRooms);
    std::cout << std::endl;
    std::cout << hotel.checkIn("single", 3, "guest 1") << std::endl;
    std::cout << hotel.checkIn("double", 1, "guest 1") << std::endl;
    hotel.checkIn("double", 1, "guest 2");
    printNestedMap(std::cout, hotel.bookedRooms);
    std::cout << std::endl;

    hotel.checkOut("single", 1);
    printMap(std::cout, hotel.availableRooms);
    std::cout << std::endl;
    hotel.checkOut("triple", 2);
    printMap(std::cout, hotel.availableRooms);
    std::cout << std::endl;

    std::cout << hotel.getAvailableRooms("single") << std::endl;

    return 0;
}