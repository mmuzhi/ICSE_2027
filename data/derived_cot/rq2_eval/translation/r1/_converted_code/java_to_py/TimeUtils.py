import datetime

class TimeUtils:

    def __init__(self):
        self.datetime = datetime.datetime.now()

    def get_current_time(self):
        return self.datetime.strftime('%H:%M:%S')

    def get_current_date(self):
        return self.datetime.strftime('%Y-%m-%d')

    def add_seconds(self, seconds):
        newDatetime = self.datetime + datetime.timedelta(seconds=seconds)
        return newDatetime.strftime('%H:%M:%S')

    def string_to_datetime(self, string):
        return datetime.datetime.strptime(string, '%Y-%m-%d %H:%M:%S')

    def datetime_to_string(self, datetime_val):
        return datetime_val.strftime('%Y-%m-%d %H:%M:%S')

    def get_minutes(self, stringTime1, stringTime2):
        time1 = self.string_to_datetime(stringTime1)
        time2 = self.string_to_datetime(stringTime2)
        delta = time2 - time1
        total_seconds = delta.total_seconds()
        total_seconds_int = int(total_seconds)
        if total_seconds_int >= 0:
            minutes = total_seconds_int // 60
        else:
            minutes = -(-total_seconds_int // 60)
        if minutes < -2147483648 or minutes > 2147483647:
            raise OverflowError('integer overflow')
        return minutes

    def get_format_time(self, year, month, day, hour, minute, second):
        timeItem = datetime.datetime(year, month, day, hour, minute, second)
        return timeItem.strftime('%Y-%m-%d %H:%M:%S')