from datetime import datetime, time, timedelta
from typing import List, Optional, Tuple

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
        self.events: List[Event] = []

    def add_event(self, event: Event) -> None:
        self.events.append(event)

    def remove_event(self, event: Event) -> None:
        self.events.remove(event)

    def get_events(self, date: datetime) -> List[Event]:
        target_date = date.date()
        return [event for event in self.events if event.date.date() == target_date]

    def is_available(self, start_time: datetime, end_time: datetime) -> bool:
        for event in self.events:
            if event.start_time < end_time and event.end_time > start_time:
                return False
        return True

    def get_available_slots(self, date: datetime) -> List[Tuple[datetime, datetime]]:
        start_of_day = datetime.combine(date.date(), time.min)
        end_of_day = datetime.combine(date.date(), time.max)
        available_slots = []
        current_time = start_of_day

        while current_time < end_of_day:
            slot_end = current_time + timedelta(hours=1)
            if self.is_available(current_time, slot_end):
                available_slots.append((current_time, slot_end))
            current_time = slot_end

        return available_slots

    def get_upcoming_events(self, num_events: int) -> List[Event]:
        now = datetime.now()
        upcoming = [event for event in self.events if event.start_time > now]
        return upcoming[:num_events]