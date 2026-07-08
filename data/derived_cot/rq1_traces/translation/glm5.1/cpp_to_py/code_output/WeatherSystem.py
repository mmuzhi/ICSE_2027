from dataclasses import dataclass
from typing import Dict, Tuple, Optional

@dataclass
class WeatherInfo:
    weather: str
    temperature: float
    temperature_units: str

class WeatherSystem:
    def __init__(self, city: str):
        self.city: str = city
        self.temperature: float = 0.0
        self.weather: str = ""
        self.weather_list: Dict[str, WeatherInfo] = {}

    def query(self, weather_list: Dict[str, WeatherInfo], tmp_units: str = "celsius") -> Optional[Tuple[float, str]]:
        # In C++, assigning the map creates a copy. In Python, we assign the reference.
        # A shallow copy `.copy()` is used here to mimic C++ value semantics 
        # so that external modifications to `weather_list` don't affect the internal state.
        self.weather_list = weather_list.copy()
        
        if self.city not in self.weather_list:
            return (0.0, "")
        else:
            info = self.weather_list[self.city]
            self.temperature = info.temperature
            self.weather = info.weather

        if info.temperature_units != tmp_units:
            if tmp_units == "celsius":
                return (self.fahrenheit_to_celsius(), self.weather)
            elif tmp_units == "fahrenheit":
                return (self.celsius_to_fahrenheit(), self.weather)
            # Note: If tmp_units is neither "celsius" nor "fahrenheit" and doesn't match,
            # the C++ code has undefined behavior (falls off the end of a non-void function).
            # In Python, this implicitly returns None, which is the closest sane equivalent.
        else:
            return (self.temperature, self.weather)

    def set_city(self, city: str) -> None:
        self.city = city

    def set_temperature(self, temperature: float) -> None:
        self.temperature = temperature

    def celsius_to_fahrenheit(self) -> float:
        return (self.temperature * 9 / 5) + 32

    def fahrenheit_to_celsius(self) -> float:
        return (self.temperature - 32) * 5 / 9

    def get_city(self) -> str:
        return self.city