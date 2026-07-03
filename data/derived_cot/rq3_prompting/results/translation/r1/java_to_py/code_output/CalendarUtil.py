from datetime import datetime, timedelta
from typing import List, Tuple

class Event:
    def __init__(self, date: datetime, start_time: datetime, end_time: datetime, description: str):
        self.date = date
        self.start_time = start_time
        self.end_time = end_time
        self.description = description

    def __eq__(self, other):
        if not isinstance(other, Event):
            return False
        return (self.date == other.date and
                self.start_time == other.start_time and
                self.end_time == other.end_time and
                self.description == other.description)

    def __hash__(self):
        return hash((self.date, self.start_time, self.end_time, self.description))

class CalendarUtil:
    def __init__(self):
        self.events = []

    def add_event(self, event: Event):
        self.events.append(event)

    def remove_event(self, event: Event):
        try:
            self.events.remove(event)
        except ValueError:
            pass  # Java's ArrayList.remove silently does nothing if not present

    def get_events(self, date: datetime) -> List[Event]:
        return [e for e in self.events if e.date.date() == date.date()]

    def is_available(self, start_time: datetime, end_time: datetime) -> bool:
        return not any(
            start_time < e.end_time and end_time > e.start_time
            for e in self.events
        )

    def get_available_slots(self, date: datetime) -> List[Tuple[datetime, datetime]]:
        available_slots = []
        start_time = date.replace(hour=0, minute=0)   # keep original seconds/microseconds
        end_time = date.replace(hour=23, minute=59)   # keep original seconds/microseconds
        while start_time < end_time:
            slot_end_time = start_time + timedelta(hours=1)
            if self.is_available(start_time, slot_end_time):
                available_slots.append((start_time, slot_end_time))
            start_time = slot_end_time
        return available_slots

    def get_upcoming_events(self, num_events: int) -> List[Event]:
        now = datetime.now()
        return [e for e in self.events if e.start_time > now][:num_events]