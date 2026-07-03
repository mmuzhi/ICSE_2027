import datetime

class TimeUtils:
    def __init__(self):
        self.datetime = datetime.datetime.now()

    def getCurrentTime(self):
        return self.datetime.strftime("%H:%M:%S")

    def getCurrentDate(self):
        return self.datetime.strftime("%Y-%m-%d")

    def addSeconds(self, seconds):
        new_datetime = self.datetime + datetime.timedelta(seconds=seconds)
        return new_datetime.strftime("%H:%M:%S")

    def stringToDatetime(self, string):
        # Parse "yyyy-M-d H:m:s" with variable-width components
        date_part, time_part = string.split(' ')
        year, month, day = map(int, date_part.split('-'))
        hour, minute, second = map(int, time_part.split(':'))
        return datetime.datetime(year, month, day, hour, minute, second)

    def datetimeToString(self, dt):
        return dt.strftime("%Y-%m-%d %H:%M:%S")

    def getMinutes(self, stringTime1, stringTime2):
        t1 = self.stringToDatetime(stringTime1)
        t2 = self.stringToDatetime(stringTime2)
        diff_seconds = (t2 - t1).total_seconds()
        # truncate toward zero to match Java's ChronoUnit.MINUTES.between
        minutes = int(diff_seconds / 60)
        return minutes

    def getFormatTime(self, year, month, day, hour, minute, second):
        dt = datetime.datetime(year, month, day, hour, minute, second)
        return dt.strftime("%Y-%m-%d %H:%M:%S")