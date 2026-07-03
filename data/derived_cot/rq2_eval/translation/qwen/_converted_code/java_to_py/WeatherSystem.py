class WeatherSystem:
    def __init__(self, city):
        self._temperature = None
        self._weather = None
        self._city = city
        self._weather_list = {}

    def set_city(self, city):
        self._city = city

    def get_city(self):
        return self._city

    def set_temperature(self, temperature):
        self._temperature = temperature

    def celsius_to_fahrenheit(self):
        if self._temperature is None:
            raise ValueError("Temperature is not set.")
        return (self._temperature * 9 / 5) + 32

    def fahrenheit_to_celsius(self):
        if self._temperature is None:
            raise ValueError("Temperature is not set.")
        return (self._temperature - 32) * 5 / 9

    def query(self, weather_list, tmp_units):
        self._weather_list = weather_list
        if self._city not in self._weather_list:
            return [False]
        
        city_weather = self._weather_list[self._city]
        self._temperature = city_weather.get("temperature")
        self._weather = city_weather.get("weather")
        current_units = city_weather.get("temperature units")

        if current_units != tmp_units:
            if tmp_units == "celsius":
                self._temperature = self.fahrenheit_to_celsius()
            elif tmp_units == "fahrenheit":
                self._temperature = self.celsius_to_fahrenheit()
        
        return [self._temperature, self._weather]