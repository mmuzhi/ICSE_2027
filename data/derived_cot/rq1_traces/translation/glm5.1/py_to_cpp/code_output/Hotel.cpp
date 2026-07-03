#include <string>
#include <map>
#include <variant>

class Hotel {
public:
    std::string name;
    std::map<std::string, int> available_rooms;
    std::map<std::string, std::map<std::string, int>> booked_rooms;

    Hotel(std::string name, std::map<std::string, int> rooms)
        : name(std::move(name)), available_rooms(std::move(rooms)) {}

    std::variant<std::string, int, bool> book_room(const std::string& room_type, int room_number, const std::string& name) {
        // Check if there are any rooms of the specified type available
        if (available_rooms.find(room_type) == available_rooms.end()) {
            return false;
        }

        if (room_number <= available_rooms[room_type]) {
            // Book the room by adding it to the booked_rooms dictionary
            booked_rooms[room_type][name] = room_number;
            available_rooms[room_type] -= room_number;
            return "Success!";
        } else if (available_rooms[room_type] != 0) {
            return available_rooms[room_type];
        } else {
            return false;
        }
    }

    std::variant<std::monostate, bool> check_in(const std::string& room_type, int room_number, const std::string& name) {
        // Check if the room of the specified type and number is booked
        if (booked_rooms.find(room_type) == booked_rooms.end()) {
            return false;
        }
        
        auto& inner_map = booked_rooms[room_type];
        if (inner_map.find(name) != inner_map.end()) {
            if (room_number > inner_map[name]) {
                return false;
            } else if (room_number == inner_map[name]) {
                // Check in the room by removing it from the booked_rooms dictionary
                inner_map.erase(name);
            } else {
                inner_map[name] -= room_number;
            }
        }
        
        return std::monostate{}; // Equivalent to Python's None
    }

    void check_out(const std::string& room_type, int room_number) {
        // If room_type is new, operator[] will default-initialize the value to 0 before adding
        available_rooms[room_type] += room_number;
    }

    int get_available_rooms(const std::string& room_type) {
        // .at() throws std::out_of_range if the key doesn't exist, matching Python's KeyError
        return available_rooms.at(room_type);
    }
};