from datetime import datetime, timedelta

class TimeUtils:
    def __init__(self):
        self.datetime = datetime.now()

    def getCurrentTime(self):
        formatter = "%H:%M:%S"
        return self.datetime.strftime(formatter)

    def getCurrentDate(self):
        formatter = "%Y-%m-%d"
        return self.datetime.strftime(formatter)

    def addSeconds(self, seconds):
        new_datetime = self.datetime + timedelta(seconds=seconds)
        formatter = "%H:%M:%S"
        return new_datetime.strftime(formatter)

    def stringToDatetime(self, string):
        if ' ' not in string:
            raise ValueError("String must contain a space")
        date_str, time_str = string.split(' ', 1)
        if '-' not in date_str:
            raise ValueError("Invalid date format")
        date_parts = date_str.split('-')
        if len(date_parts) != 3:
            raise ValueError("Invalid date format")
        date_str_formatted = f"{date_parts[0]}-{date_parts[1].zfill(2)}-{date_parts[2].zfill(2)}"
        return datetime.strptime(f"{date_str_formatted} {time_str}", "%Y-%m-%d %H:%M:%S")

    def datetimeToString(self, datetime_obj):
        formatter = "%Y-%m-%d %H:%M:%S"
        return datetime_obj.strftime(formatter)

    def getMinutes(self, stringTime1, stringTime2):
        time1 = self.stringToDatetime(stringTime1)
        time2 = self.stringToDatetime(stringTime2)
        if time1 > time2:
            time1, time2 = time2, time1
        diff = time2 - time1
        total_seconds = diff.total_seconds()
        minutes_floor = total_seconds // 60
        return int(round(minutes_floor))

    def getFormatTime(self, year, month, day, hour, minute, second):
        time_item = datetime(year, month, day, hour, minute, second)
        formatter = "%Y-%m-%d %H:%M:%S"
        return time_item.strftime(formatter)