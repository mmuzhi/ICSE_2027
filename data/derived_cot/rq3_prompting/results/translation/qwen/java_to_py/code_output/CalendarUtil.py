import datetime
from dataclasses import dataclass, field
from typing import List, Tuple
from dataclasses import dataclass

@dataclass
class Event:
    date: datetime.datetime
    start_time: datetime.datetime
    end_time: datetime.datetime
    description: str = field(compare=False)

    def __eq__(self, other):
        if not isinstance(other, Event):
            return False
        return (
            self.date == other.date and
            self.start_time == other.start_time and
            self.end_time == other.end_time and
            self.description == other.description
        )

    def __hash__(self):
        return hash((
            self.date,
            self.start_time,
            self.end_time,
            self.description
        ))

class CalendarUtil:
    def __init__(self):
        self.events: List[Event] = []

    def add_event(self, event):
        self.events.append(event)

    def remove_event(self, event):
        self.events.remove(event)

    def get_events(self, date: datetime.datetime) -> List[Event]:
        return [
            event for event in self.events
            if event.date.date() == date.date()
        ]

    def is_available(self, start_time: datetime.datetime, end_time: datetime.datetime) -> bool:
        return not any(
            start_time < event.end_time and end_time > event.start_time
            for event in self.events
        )

    def get_available_slots(self, date: datetime.datetime) -> List[Tuple[datetime.datetime, datetime.datetime]]:
        start_time = date.replace(hour=0, minute=0, second=0, microsecond=0)
        end_time = date.replace(hour=23, minute=59, second=0, microsecond=0)
        slots = []
        while start_time < end_time:
            slot_end_time = start_time + datetime.timedelta(hours=1)
            if self.is_available(start_time, slot_end_time):
                slots.append((start_time, slot_end_time))
            start_time = slot_end_time
        return slots

    def get_upcoming_events(self, num_events: int) -> List[Event]:
        now = datetime.datetime.now()
        return [
            event for event in self.events
            if event.start_time > now
        ][:num_events]