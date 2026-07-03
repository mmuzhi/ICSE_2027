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

    std::string book_room(std::string roomType, int roomNumber, std::string name) {
        if (availableRooms.find(roomType) == availableRooms.end()) {
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

    bool check_in(std::string roomType, int roomNumber, std::string name) {
        auto& guestMap = bookedRooms[roomType];
        auto it = guestMap.find(name);
        if (it == guestMap.end()) {
            return false;
        }

        int booked = it->second;
        if (roomNumber > booked) {
            return false;
        } else if (roomNumber == booked) {
            guestMap.erase(it);
        } else {
            guestMap[name] = booked - roomNumber;
        }
        return true;
    }

    void check_out(std::string roomType, int roomNumber) {
        int current = availableRooms[roomType];
        availableRooms[roomType] = current + roomNumber;
    }

    int get_available_rooms(std::string roomType) {
        auto it = availableRooms.find(roomType);
        if (it != availableRooms.end()) {
            return it->second;
        }
        return 0;
    }
};

int main() {
    std::unordered_map<std::string, int> rooms;
    rooms["single"] = 3;
    rooms["double"] = 2;
    Hotel hotel("Test Hotel", rooms);

    std::cout << hotel.book_room("single", 2, "guest 1") << std::endl;
    std::cout << hotel.book_room("triple", 2, "guest 1") << std::endl;
    std::cout << hotel.book_room("single", 2, "guest 2") << std::endl;
    std::cout << hotel.book_room("single", 1, "guest 2") << std::endl;
    std::cout << hotel.book_room("single", 3, "guest 1") << std::endl;
    std::cout << hotel.book_room("single", 100, "guest 1") << std::endl;

    std::cout << "Booked after first checkIn: ";
    for (const auto& entry : hotel.bookedRooms["single"]) {
        std::cout << entry.first << ": " << entry.second << " ";
    }
    std::cout << std::endl;

    std::cout << hotel.check_in("single", 1, "guest 1") << std::endl;
    std::cout << hotel.check_in("single", 3, "guest 1") << std::endl;
    std::cout << hotel.check_in("double", 1, "guest 1") << std::endl;
    hotel.check_in("double", 1, "guest 2");

    std::cout << "Booked after second checkIn: ";
    for (const auto& entry : hotel.bookedRooms["double"]) {
        std::cout << entry.first << ": " << entry.second << " ";
    }
    std::cout << std::endl;

    std::cout << "Available Rooms: ";
    for (const auto& entry : hotel.availableRooms) {
        std::cout << entry.first << ": " << entry.second << " ";
    }
    std::cout << std::endl;

    hotel.check_out("single", 1);
    std::cout << "Available Rooms after checkOut: ";
    for (const auto& entry : hotel.availableRooms) {
        std::cout << entry.first << ": " << entry.second << " ";
    }
    std::cout << std::endl;

    hotel.check_out("triple", 2);
    std::cout << "Available Rooms after second checkOut: ";
    for (const auto& entry : hotel.availableRooms) {
        std::cout << entry.first << ": " << entry.second << " ";
    }
    std::cout << std::endl;

    std::cout << "Available single rooms: " << hotel.get_available_rooms("single") << std::endl;

    return 0;
}