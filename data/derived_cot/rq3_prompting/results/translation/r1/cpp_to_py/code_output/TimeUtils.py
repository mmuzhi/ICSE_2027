import datetime
import time

class TimeUtils:
    def __init__(self):
        self.datetime = datetime.datetime.now()

    def get_current_time(self):
        return self.datetime.strftime("%H:%M:%S")

    def get_current_date(self):
        return self.datetime.strftime("%Y-%m-%d")

    def add_seconds(self, seconds):
        self.datetime += datetime.timedelta(seconds=seconds)
        return self.datetime.strftime("%H:%M:%S")

    def string_to_datetime(self, s):
        return datetime.datetime.strptime(s, "%Y-%m-%d %H:%M:%S")

    def datetime_to_string(self, dt):
        return dt.strftime("%Y-%m-%d %H:%M:%S")

    def get_minutes(self, string_time1, string_time2):
        dt1 = self.string_to_datetime(string_time1)
        dt2 = self.string_to_datetime(string_time2)
        # Use time.mktime to get POSIX timestamps (treats naive datetimes as local)
        t1 = time.mktime(dt1.timetuple())
        t2 = time.mktime(dt2.timetuple())
        return int((t2 - t1) / 60)

    def get_format_time(self, year, month, day, hour, minute, second):
        dt = datetime.datetime(year, month, day, hour, minute, second)
        return dt.strftime("%Y-%m-%d %H:%M:%S")