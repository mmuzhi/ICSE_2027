import datetime
from typing import List, Tuple, Optional

class Event:
    def __init__(self, date: datetime.datetime, start_time: datetime.datetime, end_time: datetime.datetime, description: str):
        self.date = date
        self.start_time = start_time
        self.end_time = end_time
        self.description = description

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Event):
            return False
        return (self.date == other.date and 
                self.start_time == other.start_time and 
                self.end_time == other.end_time and 
                self.description == other.description)

    def __hash__(self) -> int:
        return hash((self.date, self.start_time, self.end_time, self.description))

class CalendarUtil:
    def __init__(self):
        self.events: List[Event] = []

    def add_event(self, event: Event) -> None:
        self.events.append(event)

    def remove_event(self, event: Event) -> None:
        if event in self.events:
            self.events.remove(event)

    def get_events(self, date: datetime.datetime) -> List[Event]:
        target_date = date.date()
        return [event for event in self.events if event.date.date() == target_date]

    def is_available(self, start_time: datetime.datetime, end_time: datetime.datetime) -> bool:
        for event in self.events:
            if start_time < event.end_time and end_time > event.start_time:
                return False
        return True

    def get_available_slots(self, date: datetime.datetime) -> List[Tuple[datetime.datetime, datetime.datetime]]:
        available_slots = []
        start_time = date.replace(hour=0, minute=0, second=0, microsecond=0)
        end_time = date.replace(hour=23, minute=59, second=59, microsecond=999999)
        current = start_time
        while current < end_time:
            slot_end = current + datetime.timedelta(hours=1)
            if slot_end > end_time:
                slot_end = end_time
            if self.is_available(current, slot_end):
                available_slots.append((current, slot_end))
            current = slot_end
        return available_slots

    def get_upcoming_events(self, num_events: int) -> List[Event]:
        now = datetime.datetime.now()
        future_events = [event for event in self.events if event.start_time > now]
        future_events.sort(key=lambda event: event.start_time)
        return future_events[:num_events]