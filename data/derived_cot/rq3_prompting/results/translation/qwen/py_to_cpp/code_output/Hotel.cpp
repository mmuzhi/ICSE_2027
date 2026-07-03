#include <unordered_map>
#include <string>
#include <variant>

class Hotel {
private:
    std::unordered_map<std::string, int> available_rooms;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> booked_rooms;

public:
    Hotel(const std::string& name, const std::unordered_map<std::string, int>& rooms)
        : available_rooms(rooms), booked_rooms() {}

    std::variant<std::string, int, bool> book_room(const std::string& room_type, int room_number, const std::string& name) {
        if (available_rooms.find(room_type) == available_rooms.end()) {
            return false;
        }

        if (room_number <= available_rooms[room_type]) {
            if (booked_rooms.find(room_type) == booked_rooms.end()) {
                booked_rooms[room_type] = {};
            }
            booked_rooms[room_type][name] = room_number;
            available_rooms[room_type] -= room_number;
            return "Success!";
        } else if (available_rooms[room_type] != 0) {
            return available_rooms[room_type];
        } else {
            return false;
        }
    }

    bool check_in(const std::string& room_type, int room_number, const std::string& name) {
        if (booked_rooms.find(room_type) == booked_rooms.end()) {
            return false;
        }

        auto& name_rooms = booked_rooms[room_type];
        if (name_rooms.find(name) == name_rooms.end()) {
            return false;
        }

        int booked_quantity = name_rooms[name];
        if (room_number > booked_quantity) {
            return false;
        }

        if (room_number == booked_quantity) {
            name_rooms.erase(name);
        } else {
            name_rooms[name] -= room_number;
        }

        return true;
    }

    void check_out(const std::string& room_type, int room_number) {
        if (available_rooms.find(room_type) != available_rooms.end()) {
            available_rooms[room_type] += room_number;
        } else {
            available_rooms[room_type] = room_number;
        }
    }

    int get_available_rooms(const std::string& room_type) {
        return available_rooms.at(room_type);
    }
};