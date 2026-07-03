import time
from datetime import datetime, timedelta

class TimeUtils:
    def __init__(self):
        self.datetime = time.localtime()

    def get_current_time(self):
        return time.strftime("%H:%M:%S", self.datetime)

    def get_current_date(self):
        return time.strftime("%Y-%m-%d", self.datetime)

    def add_seconds(self, seconds):
        timestamp = time.mktime(self.datetime) + seconds
        new_datetime = time.localtime(timestamp)
        self.datetime = new_datetime
        return time.strftime("%H:%M:%S", new_datetime)

    def string_to_datetime(self, str):
        return time.strptime(str, "%Y-%m-%d %H:%M:%S")

    def datetime_to_string(self, datetime_struct):
        return time.strftime("%Y-%m-%d %H:%M:%S", datetime_struct)

    def get_minutes(self, string_time1, string_time2):
        time1 = time.strptime(string_time1, "%Y-%m-%d %H:%M:%S")
        time2 = time.strptime(string_time2, "%Y-%m-%d %H:%M:%S")
        timestamp1 = time.mktime(time1)
        timestamp2 = time.mktime(time2)
        return int((timestamp2 - timestamp1) / 60)

    def get_format_time(self, year, month, day, hour, minute, second):
        tm = time.struct_time((year, month, day, hour, minute, second, 0, 0, -1))
        return time.strftime("%Y-%m-%d %H:%M:%S", tm)