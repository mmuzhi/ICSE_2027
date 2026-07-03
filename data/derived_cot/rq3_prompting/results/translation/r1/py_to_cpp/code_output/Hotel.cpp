#include <string>
#include <map>
#include <variant>
#include <optional>

class Hotel {
public:
    std::string name;
    std::map<std::string, int> available_rooms;
    std::map<std::string, std::map<std::string, int>> booked_rooms;

    Hotel(const std::string& name, const std::map<std::string, int>& rooms)
        : name(name), available_rooms(rooms) {}

    std::variant<std::string, int, bool> book_room(const std::string& room_type, int room_number, const std::string& name) {
        auto it = available_rooms.find(room_type);
        if (it == available_rooms.end()) {
            return false;
        }
        int& remaining = it->second;
        if (room_number <= remaining) {
            booked_rooms[room_type][name] = room_number;
            remaining -= room_number;
            return std::string("Success!");
        } else if (remaining != 0) {
            return remaining;
        } else {
            return false;
        }
    }

    std::optional<bool> check_in(const std::string& room_type, int room_number, const std::string& name) {
        auto it = booked_rooms.find(room_type);
        if (it == booked_rooms.end()) {
            return std::optional<bool>(false);  // failure
        }
        auto& inner_map = it->second;
        auto name_it = inner_map.find(name);
        if (name_it != inner_map.end()) {
            int& booked_qty = name_it->second;
            if (room_number > booked_qty) {
                return std::optional<bool>(false);
            } else if (room_number == booked_qty) {
                inner_map.erase(name_it);
            } else {
                booked_qty -= room_number;
            }
        }
        // If name not found, do nothing and return success (nullopt)
        return std::nullopt;  // success
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
        return available_rooms.at(room_type);  // throws if missing, matching Python KeyError
    }
};