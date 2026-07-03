import datetime

class TimeUtils:
    def __init__(self):
        self.datetime = datetime.datetime.now()

    def getCurrentTime(self):
        return self.datetime.strftime("%H:%M:%S")

    def getCurrentDate(self):
        return self.datetime.strftime("%Y-%m-%d")

    def addSeconds(self, seconds):
        newDatetime = self.datetime + datetime.timedelta(seconds=seconds)
        return newDatetime.strftime("%H:%M:%S")

    def stringToDatetime(self, string):
        return datetime.datetime.strptime(string, "%Y-%m-%d %H:%M:%S")

    def datetimeToString(self, datetime_val):
        return datetime_val.strftime("%Y-%m-%d %H:%M:%S")

    def getMinutes(self, stringTime1, stringTime2):
        time1 = self.stringToDatetime(stringTime1)
        time2 = self.stringToDatetime(stringTime2)
        delta = time2 - time1
        total_seconds = delta.total_seconds()
        total_seconds_int = int(total_seconds)
        
        if total_seconds_int >= 0:
            minutes = total_seconds_int // 60
        else:
            minutes = - ((-total_seconds_int) // 60)
        
        if minutes < -2147483648 or minutes > 2147483647:
            raise OverflowError("integer overflow")
        return minutes

    def getFormatTime(self, year, month, day, hour, minute, second):
        timeItem = datetime.datetime(year, month, day, hour, minute, second)
        return timeItem.strftime("%Y-%m-%d %H:%M:%S")