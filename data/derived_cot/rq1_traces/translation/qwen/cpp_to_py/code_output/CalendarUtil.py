from datetime import datetime, timedelta
from typing import List, Optional

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

class CalendarUtil:
    def __init__(self):
        self.events: List[Event] = []

    def add_event(self, event: Event) -> None:
        self.events.append(event)

    def remove_event(self, event: Event) -> None:
        for i, existing_event in enumerate(self.events):
            if existing_event == event:
                del self.events[i]
                return

    def get_events(self, date: datetime) -> List[Event]:
        target_date = datetime.combine(date.date(), datetime.min.time())
        result = []
        for event in self.events:
            event_date = datetime.combine(event.date.date(), datetime.min.time())
            if event_date == target_date:
                result.append(event)
        return result

    def is_available(self, start_time: datetime, end_time: datetime) -> bool:
        current_time = start_time
        while current_time < end_time:
            if self._is_overlapping(current_time, current_time + timedelta(minutes=30), end_time):
                return False
            current_time += timedelta(minutes=30)
        return True

    def _is_overlapping(self, start1: datetime, end1: datetime, end2: datetime) -> bool:
        return start1 < end2 and end1 > end2

    def get_available_slots(self, date: datetime) -> List[tuple]:
        start_time = date.replace(hour=0, minute=0, second=0)
        end_time = (date + timedelta(days=1)).replace(hour=0, minute=0, second=0) - timedelta(seconds=1)
        slots = []
        current = start_time
        while current < end_time:
            slot_end = current + timedelta(hours=1)
            if self.is_available(current, slot_end):
                slots.append((current, slot_end))
            current = slot_end
        return slots

    def get_upcoming_events(self, num_events: int) -> List[Event]:
        now = datetime.now()
        upcoming = []
        for event in self.events:
            if event.start_time >= now:
                upcoming.append(event)
                if len(upcoming) == num_events:
                    break
        return upcoming