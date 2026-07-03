#include <string>
#include <unordered_map>
#include <variant>
#include <optional>

class Hotel {
private:
    std::string name;
    std::unordered_map<std::string, int> available_rooms;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> booked_rooms;

public:
    Hotel(const std::string& name, const std::unordered_map<std::string, int>& rooms)
        : name(name), available_rooms(rooms), booked_rooms() {}

    std::variant<std::string, int, bool> book_room(const std::string& room_type, int room_number, const std::string& name) {
        if (available_rooms.find(room_type) == available_rooms.end()) {
            return false;
        }

        int available_count = available_rooms.at(room_type);
        if (room_number <= available_count) {
            if (booked_rooms.find(room_type) == booked_rooms.end()) {
                booked_rooms[room_type] = {};
            }
            booked_rooms[room_type][name] = room_number;
            available_rooms[room_type] -= room_number;
            return "Success!";
        } else if (available_count != 0) {
            return available_count;
        } else {
            return false;
        }
    }

    bool check_in(const std::string& room_type, int room_number, const std::string& name) {
        if (booked_rooms.find(room_type) == booked_rooms.end()) {
            return false;
        }

        auto& booking_map = booked_rooms[room_type];
        auto booking_iter = booking_map.find(name);
        if (booking_iter == booking_map.end()) {
            return false;
        }

        int booked_count = booking_iter->second;
        if (room_number > booked_count) {
            return false;
        }

        if (room_number == booked_count) {
            booking_map.erase(name);
        } else {
            booking_map[name] = booked_count - room_number;
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

    int get_available_rooms(const std::string& room_type) const {
        return available_rooms.at(room_type);
    }
};