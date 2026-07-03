#include <unordered_map>
#include <string>
#include <optional>
#include <variant>
#include <stdexcept>

class Hotel {
private:
    std::string name;
    std::unordered_map<std::string, int> available_rooms;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> booked_rooms;

public:
    Hotel(const std::string& name, const std::unordered_map<std::string, int>& rooms)
        : name(name), available_rooms(rooms) {}

    std::variant<std::string, int, bool> book_room(const std::string& room_type, int room_number, const std::string& name) {
        auto it = available_rooms.find(room_type);
        if (it == available_rooms.end()) {
            return false;
        }

        int& available = it->second;
        if (room_number <= available) {
            booked_rooms[room_type][name] = room_number;
            available -= room_number;
            return std::string("Success!");
        } else if (available > 0) {
            return available;
        } else {
            return false;
        }
    }

    std::optional<bool> check_in(const std::string& room_type, int room_number, const std::string& name) {
        auto it_room = booked_rooms.find(room_type);
        if (it_room == booked_rooms.end()) {
            return false;
        }

        auto& inner_map = it_room->second;
        auto it_guest = inner_map.find(name);
        if (it_guest == inner_map.end()) {
            return false;
        }

        int& booked_count = it_guest->second;
        if (room_number > booked_count) {
            return false;
        } else if (room_number == booked_count) {
            inner_map.erase(it_guest);
            return std::nullopt;
        } else {
            booked_count -= room_number;
            return std::nullopt;
        }
    }

    void check_out(const std::string& room_type, int room_number) {
        auto it = available_rooms.find(room_type);
        if (it != available_rooms.end()) {
            it->second += room_number;
        } else {
            available_rooms[room_type] = room_number;
        }
    }

    int get_available_rooms(const std::string& room_type) {
        return available_rooms.at(room_type);
    }
};