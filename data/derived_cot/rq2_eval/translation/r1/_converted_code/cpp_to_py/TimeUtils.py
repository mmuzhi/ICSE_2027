import time

class TimeUtils:
    def __init__(self):
        self._timestamp = time.time()

    def get_current_time(self):
        t = time.localtime(self._timestamp)
        return time.strftime("%H:%M:%S", t)

    def get_current_date(self):
        t = time.localtime(self._timestamp)
        return time.strftime("%Y-%m-%d", t)

    def add_seconds(self, seconds):
        self._timestamp += seconds
        t = time.localtime(self._timestamp)
        return time.strftime("%H:%M:%S", t)

    def string_to_datetime(self, s):
        t = time.strptime(s, "%Y-%m-%d %H:%M:%S")
        new_tuple = (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, t.tm_wday, t.tm_yday, 0)
        return time.struct_time(new_tuple)

    def datetime_to_string(self, dt):
        return time.strftime("%Y-%m-%d %H:%M:%S", dt)

    def get_minutes(self, string_time1, string_time2):
        time1 = self.string_to_datetime(string_time1)
        time2 = self.string_to_datetime(string_time2)
        t1 = time.mktime(time1)
        t2 = time.mktime(time2)
        diff_seconds = t2 - t1
        return int(diff_seconds / 60)

    def get_format_time(self, year, month, day, hour, minute, second):
        t_tuple = (year, month, day, hour, minute, second, 0, 0, 0)
        return time.strftime("%Y-%m-%d %H:%M:%S", t_tuple)