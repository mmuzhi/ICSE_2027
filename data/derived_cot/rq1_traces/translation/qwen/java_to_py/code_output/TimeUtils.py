from datetime import datetime

class TimeUtils:
    def __init__(self):
        self.datetime = datetime.now()

    def get_current_time(self):
        return self.datetime.strftime("%H:%M:%S")

    def get_current_date(self):
        return self.datetime.strftime("%Y-%m-%d")

    def add_seconds(self, seconds):
        new_datetime = self.datetime + datetime.timedelta(seconds=seconds)
        return new_datetime.strftime("%H:%M:%S")

    def string_to_datetime(self, string):
        formatter = "%Y-%m-%d %H:%M:%S"
        return datetime.strptime(string, formatter)

    def datetime_to_string(self, datetime_obj):
        formatter = "%Y-%m-%d %H:%M:%S"
        return datetime_obj.strftime(formatter)

    def get_minutes(self, string_time1, string_time2):
        time1 = self.string_to_datetime(string_time1)
        time2 = self.string_to_datetime(string_time2)
        diff = time2 - time1
        total_seconds = diff.total_seconds()
        return round(total_seconds / 60)

    def get_format_time(self, year, month, day, hour, minute, second):
        datetime_obj = datetime(year, month, day, hour, minute, second)
        formatter = "%Y-%m-%d %H:%M:%S"
        return datetime_obj.strftime(formatter)