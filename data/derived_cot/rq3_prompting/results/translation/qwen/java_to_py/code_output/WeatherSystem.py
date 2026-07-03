class WeatherSystem:
    def __init__(self, city):
        self.temperature = None
        self.weather = None
        self.city = city
        self.weatherList = {}

    def setCity(self, city):
        self.city = city

    def getCity(self):
        return self.city

    def setTemperature(self, temperature):
        self.temperature = temperature

    def celsiusToFahrenheit(self):
        if self.temperature is None:
            raise TypeError("Temperature is None, cannot convert")
        return (self.temperature * 9 / 5) + 32

    def fahrenheitToCelsius(self):
        if self.temperature is None:
            raise TypeError("Temperature is None, cannot convert")
        return (self.temperature - 32) * 5 / 9

    def query(self, weatherList, tmpUnits):
        self.weatherList = weatherList
        
        if self.city not in self.weatherList:
            return [False]
        
        city_weather = self.weatherList[self.city]
        self.temperature = city_weather.get("temperature")
        self.weather = city_weather.get("weather")
        current_units = city_weather.get("temperature units")
        
        if current_units != tmpUnits:
            if tmpUnits == "celsius":
                self.temperature = self.fahrenheitToCelsius()
            elif tmpUnits == "fahrenheit":
                self.temperature = self.celsiusToFahrenheit()
        
        return [self.temperature, self.weather]