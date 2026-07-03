import datetime

class TimeUtils:
    def __init__(self):
        self.datetime = datetime.datetime.now()

    def get_current_time(self) -> str:
        return self.datetime.strftime("%H:%M:%S")

    def get_current_date(self) -> str:
        return self.datetime.strftime("%Y-%m-%d")

    def add_seconds(self, seconds: int) -> str:
        self.datetime += datetime.timedelta(seconds=seconds)
        return self.datetime.strftime("%H:%M:%S")

    def string_to_datetime(self, string: str) -> datetime.datetime:
        return datetime.datetime.strptime(string, "%Y-%m-%d %H:%M:%S")

    def datetime_to_string(self, dt: datetime.datetime) -> str:
        return dt.strftime("%Y-%m-%d %H:%M:%S")

    def get_minutes(self, string_time1: str, string_time2: str) -> int:
        time1 = self.string_to_datetime(string_time1)
        time2 = self.string_to_datetime(string_time2)
        return int((time2 - time1).total_seconds() / 60)

    def get_format_time(self, year: int, month: int, day: int, hour: int, minute: int, second: int) -> str:
        dt = datetime.datetime(year, month, day, hour, minute, second)
        return dt.strftime("%Y-%m-%d %H:%M:%S")