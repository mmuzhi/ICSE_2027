class WeatherSystem:
    def __init__(self, city):
        self.temperature = None
        self.weather = None
        self.city = city
        self.weatherList = None

    def setCity(self, city):
        self.city = city

    def getCity(self):
        return self.city

    def setTemperature(self, temperature):
        self.temperature = temperature

    def celsiusToFahrenheit(self):
        return (self.temperature * 9 / 5) + 32

    def fahrenheitToCelsius(self):
        return (self.temperature - 32) * 5 / 9

    def query(self, weatherList, tmpUnits):
        self.weatherList = weatherList
        if self.city not in weatherList:
            return (False,)
        
        city_weather = weatherList[self.city]
        self.temperature = city_weather['temperature']
        self.weather = city_weather['weather']
        current_units = city_weather['temperature units']
        
        if current_units != tmpUnits:
            if tmpUnits == 'celsius':
                self.temperature = self.fahrenheitToCelsius()
            elif tmpUnits == 'fahrenheit':
                self.temperature = self.celsiusToFahrenheit()
        
        return (self.temperature, self.weather)