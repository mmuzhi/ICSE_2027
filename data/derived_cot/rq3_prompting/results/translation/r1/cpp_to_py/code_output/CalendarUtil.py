import datetime
from typing import List, Tuple, Optional

class Event:
    def __init__(self, date: datetime.datetime, start_time: datetime.datetime,
                 end_time: datetime.datetime, description: str):
        self.date = date
        self.start_time = start_time
        self.end_time = end_time
        self.description = description

    def __eq__(self, other):
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
        try:
            idx = self.events.index(event)
            del self.events[idx]
        except ValueError:
            pass

    def get_events(self, date: datetime.datetime) -> List[Event]:
        events_on_date: List[Event] = []
        for e in self.events:
            if (e.date.year == date.year and
                e.date.month == date.month and
                e.date.day == date.day):
                events_on_date.append(e)
        return events_on_date

    def is_available(self, start_time: datetime.datetime,
                     end_time: datetime.datetime) -> bool:
        for e in self.events:
            if start_time < e.end_time and end_time > e.start_time:
                return False
        return True

    def get_available_slots(self, date: datetime.datetime) -> List[Tuple[datetime.datetime, datetime.datetime]]:
        available_slots: List[Tuple[datetime.datetime, datetime.datetime]] = []
        start_time = date
        end_time = date + datetime.timedelta(hours=24) - datetime.timedelta(seconds=1)

        while start_time < end_time:
            slot_end_time = start_time + datetime.timedelta(hours=1)
            if self.is_available(start_time, slot_end_time):
                available_slots.append((start_time, slot_end_time))
            start_time = slot_end_time

        return available_slots

    def get_upcoming_events(self, num_events: int) -> List[Event]:
        now = datetime.datetime.now()
        upcoming: List[Event] = []
        for e in self.events:
            if e.start_time >= now:
                upcoming.append(e)
                if len(upcoming) == num_events:
                    break
        return upcoming


def time_from_timestamp(timestamp: int) -> datetime.datetime:
    return datetime.datetime.fromtimestamp(timestamp)