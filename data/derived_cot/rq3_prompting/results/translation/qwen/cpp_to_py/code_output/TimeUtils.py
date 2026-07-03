import datetime

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

    def get_minutes(self, s1, s2):
        t1 = self.string_to_datetime(s1)
        t2 = self.string_to_datetime(s2)
        diff_seconds = (t2 - t1).total_seconds()
        return int(diff_seconds // 60)

    def get_format_time(self, year, month, day, hour, minute, second):
        dt = datetime.datetime(year, month, day, hour, minute, second)
        return dt.strftime("%Y-%m-%d %H:%M:%S")