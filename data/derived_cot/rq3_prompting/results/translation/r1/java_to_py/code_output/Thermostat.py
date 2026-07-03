class Thermostat:
    def __init__(self, current_temperature: float, target_temperature: float, mode: str):
        self.currentTemperature = current_temperature
        self.targetTemperature = target_temperature
        self.mode = mode

    def getTargetTemperature(self) -> float:
        return self.targetTemperature

    def setTargetTemperature(self, temperature: float) -> None:
        self.targetTemperature = temperature

    def getMode(self) -> str:
        return self.mode

    def setMode(self, mode: str) -> bool:
        if mode == "heat" or mode == "cool":
            self.mode = mode
            return True
        else:
            return False

    def autoSetMode(self) -> None:
        if self.currentTemperature < self.targetTemperature:
            self.mode = "heat"
        else:
            self.mode = "cool"

    def autoCheckConflict(self) -> bool:
        if self.currentTemperature > self.targetTemperature:
            if self.mode == "cool":
                return True
            else:
                self.autoSetMode()
                return False
        else:
            if self.mode == "heat":
                return True
            else:
                self.autoSetMode()
                return False

    def simulateOperation(self) -> int:
        self.autoSetMode()
        use_time = 0
        if self.mode == "heat":
            while self.currentTemperature < self.targetTemperature:
                self.currentTemperature += 1.0
                use_time += 1
        else:
            while self.currentTemperature > self.targetTemperature:
                self.currentTemperature -= 1.0
                use_time += 1
        return use_time