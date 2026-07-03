class Thermostat:
    def __init__(self, current_temperature: float, target_temperature: float, mode: str):
        self.currentTemperature = current_temperature
        self._targetTemperature = target_temperature
        self._mode = mode

    def getTargetTemperature(self) -> float:
        return self._targetTemperature

    def setTargetTemperature(self, temperature: float) -> None:
        self._targetTemperature = temperature

    def getMode(self) -> str:
        return self._mode

    def setMode(self, mode: str) -> bool:
        if mode == "heat" or mode == "cool":
            self._mode = mode
            return True
        else:
            return False

    def autoSetMode(self) -> None:
        if self.currentTemperature < self._targetTemperature:
            self._mode = "heat"
        else:
            self._mode = "cool"

    def autoCheckConflict(self) -> bool:
        if self.currentTemperature > self._targetTemperature:
            if self._mode == "cool":
                return True
            else:
                self.autoSetMode()
                return False
        else:
            if self._mode == "heat":
                return True
            else:
                self.autoSetMode()
                return False

    def simulateOperation(self) -> int:
        self.autoSetMode()
        use_time = 0
        if self._mode == "heat":
            while self.currentTemperature < self._targetTemperature:
                self.currentTemperature += 1
                use_time += 1
        else:
            while self.currentTemperature > self._targetTemperature:
                self.currentTemperature -= 1
                use_time += 1
        return use_time