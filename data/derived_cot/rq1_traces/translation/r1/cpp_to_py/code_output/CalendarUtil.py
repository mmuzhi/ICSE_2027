import datetime
import time

class Event:
    def __init__(self, date, start_time, end_time, description):
        self.date = date
        self.start_time = start_time
        self.end_time = end_time
        self.description = description

    def __eq__(self, other):
        if not isinstance(other, Event):
            return NotImplemented
        return (self.date == other.date and
                self.start_time == other.start_time and
                self.end_time == other.end_time and
                self.description == other.description)

class CalendarUtil:
    def __init__(self):
        self.events = []

    def add_event(self, event):
        self.events.append(event)

    def remove_event(self, event):
        if event in self.events:
            self.events.remove(event)

    def get_events(self, date):
        def get_local_ymd(utc_dt):
            timestamp = utc_dt.timestamp()
            local_tm = time.localtime(timestamp)
            return (local_tm.tm_year, local_tm.tm_mon, local_tm.tm_mday)
        
        input_ymd = get_local_ymd(date)
        events_on_date = []
        for event in self.events:
            event_ymd = get_local_ymd(event.date)
            if input_ymd == event_ymd:
                events_on_date.append(event)
        return events_on_date

    def is_available(self, start_time, end_time):
        for event in self.events:
            if start_time < event.end_time and end_time > event.start_time:
                return False
        return True

    def get_available_slots(self, date):
        start_time_utc = date
        end_time_utc = date + datetime.timedelta(days=1) - datetime.timedelta(seconds=1)
        
        available_slots = []
        current = start_time_utc
        one_hour = datetime.timedelta(hours=1)
        
        while current < end_time_utc:
            slot_end = current + one_hour
            if self.is_available(current, slot_end):
                available_slots.append((current, slot_end))
            current = slot_end
            
        return available_slots

    def get_upcoming_events(self, num_events):
        now = datetime.datetime.utcnow()
        upcoming_events = []
        for event in self.events:
            if event.start_time >= now:
                upcoming_events.append(event)
                if len(upcoming_events) == num_events:
                    break
        return upcoming_events

def time_from_timestamp(timestamp):
    return datetime.datetime.utcfromtimestamp(timestamp)