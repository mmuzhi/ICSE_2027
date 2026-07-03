class WeatherSystem:
    def __init__(self, city: str):
        self.temperature: float = None
        self.weather: str = None
        self.city: str = city
        self.weatherList: dict = {}

    def setCity(self, city: str) -> None:
        self.city = city

    def getCity(self) -> str:
        return self.city

    def setTemperature(self, temperature: float) -> None:
        self.temperature = temperature

    def celsiusToFahrenheit(self) -> float:
        return (self.temperature * 9 / 5) + 32

    def fahrenheitToCelsius(self) -> float:
        return (self.temperature - 32) * 5 / 9

    def query(self, weatherList: dict, tmpUnits: str) -> list:
        self.weatherList = weatherList
        if self.city not in weatherList:
            return [False]

        cityWeather = weatherList[self.city]
        self.temperature = cityWeather["temperature"]
        self.weather = cityWeather["weather"]
        currentUnits = cityWeather["temperature units"]

        if currentUnits != tmpUnits:
            if tmpUnits == "celsius":
                self.temperature = self.fahrenheitToCelsius()
            elif tmpUnits == "fahrenheit":
                self.temperature = self.celsiusToFahrenheit()

        return [self.temperature, self.weather]