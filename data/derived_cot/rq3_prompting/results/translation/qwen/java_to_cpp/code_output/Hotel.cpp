#include <iostream>
#include <unordered_map>
#include <string>

class Hotel {
private:
    std::string name;
    std::unordered_map<std::string, int> availableRooms;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> bookedRooms;

public:
    Hotel(std::string name, std::unordered_map<std::string, int> rooms) 
        : name(std::move(name)), availableRooms(std::move(rooms)) {
        bookedRooms.clear();
    }

    std::string bookRoom(std::string roomType, int roomNumber, std::string name) {
        if (!availableRooms.count(roomType)) {
            return "False";
        }

        int available = availableRooms[roomType];
        if (roomNumber <= available) {
            bookedRooms[roomType][name] = roomNumber;
            availableRooms[roomType] = available - roomNumber;
            return "Success!";
        } else {
            return "False";
        }
    }

    bool checkIn(std::string roomType, int roomNumber, std::string name) {
        if (!bookedRooms.count(roomType) || !bookedRooms[roomType].count(name)) {
            return false;
        }

        int booked = bookedRooms[roomType][name];
        if (roomNumber > booked) {
            return false;
        } else if (roomNumber == booked) {
            bookedRooms[roomType].erase(name);
        } else {
            bookedRooms[roomType][name] = booked - roomNumber;
        }
        return true;
    }

    void checkOut(std::string roomType, int roomNumber) {
        availableRooms[roomType] += roomNumber;
    }

    int getAvailableRooms(std::string roomType) {
        return availableRooms[roomType];
    }
};

int main() {
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