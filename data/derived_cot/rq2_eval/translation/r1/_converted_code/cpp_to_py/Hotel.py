class Hotel:
    def __init__(self, name, rooms):
        self.name = name
        self.available_rooms = rooms.copy()
        self.booked_rooms = {}
    
    def book_room(self, room_type, room_number, name):
        if room_type not in self.available_rooms:
            return "False."
        
        available_count = self.available_rooms[room_type]
        if room_number <= available_count:
            if room_type not in self.booked_rooms:
                self.booked_rooms[room_type] = {}
            self.booked_rooms[room_type][name] = room_number
            self.available_rooms[room_type] = available_count - room_number
            return "Success!"
        elif available_count != 0:
            return str(available_count)
        else:
            return "False."
    
    def check_in(self, room_type, room_number, name):
        if room_type not in self.booked_rooms:
            return False
        
        room_dict = self.booked_rooms[room_type]
        if name not in room_dict:
            return False
        
        booked_count = room_dict[name]
        if room_number > booked_count:
            return False
        elif room_number == booked_count:
            del room_dict[name]
            if not room_dict:
                del self.booked_rooms[room_type]
        else:
            room_dict[name] = booked_count - room_number
        return True
    
    def check_out(self, room_type, room_number):
        if room_type in self.available_rooms:
            self.available_rooms[room_type] += room_number
        else:
            self.available_rooms[room_type] = room_number
    
    def get_available_rooms(self, room_type):
        return self.available_rooms.get(room_type, 0)