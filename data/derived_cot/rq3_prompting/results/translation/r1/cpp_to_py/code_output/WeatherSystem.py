class WeatherSystem:
    def __init__(self, city: str):
        self.city = city
        self.temperature = 0.0
        self.weather = ""
        self.weather_list = {}

    def query(self, weather_list: dict, tmp_units: str = "celsius"):
        # Copy the dictionary to match C++ copy semantics (parameter is const ref)
        self.weather_list = dict(weather_list)

        if self.city not in self.weather_list:
            return (0.0, "")

        data = self.weather_list[self.city]
        self.temperature = data["temperature"]
        self.weather = data["weather"]

        if data["temperature_units"] != tmp_units:
            if tmp_units == "celsius":
                return (self.fahrenheit_to_celsius(), self.weather)
            elif tmp_units == "fahrenheit":
                return (self.celsius_to_fahrenheit(), self.weather)
            # No else: undefined behavior in C++ for unknown units, mimic here
        else:
            return (self.temperature, self.weather)

    def set_city(self, city: str):
        self.city = city

    def set_temperature(self, temperature: float):
        self.temperature = temperature

    def celsius_to_fahrenheit(self) -> float:
        return (self.temperature * 9 / 5) + 32

    def fahrenheit_to_celsius(self) -> float:
        return (self.temperature - 32) * 5 / 9

    def get_city(self) -> str:
        return self.city