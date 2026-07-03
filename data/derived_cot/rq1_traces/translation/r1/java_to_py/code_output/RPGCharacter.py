class RPGCharacter:
    def __init__(self, name, hp, attack_power, defense, level=1):
        self.name = name
        self.hp = hp
        self.attack_power = attack_power
        self.defense = defense
        self.level = level
        self.exp = 0
    
    def attack(self, other_character):
        damage = max(self.attack_power - other_character.defense, 1)
        other_character.hp -= damage
    
    def heal(self):
        self.hp += 10
        if self.hp > 100:
            self.hp = 100
        return self.hp
    
    def gainExp(self, amount):
        while amount != 0:
            required = self.level * 100 - self.exp
            if amount >= required:
                amount -= required
                self.levelUp()
            else:
                self.exp += amount
                amount = 0
    
    def levelUp(self):
        if self.level < 100:
            self.level += 1
            self.exp = 0
            self.hp += 20
            self.attack_power += 5
            self.defense += 5
        return [self.level, self.hp, self.attack_power, self.defense]
    
    def isAlive(self):
        return self.hp > 0
    
    def getName(self):
        return self.name
    
    def getHp(self):
        return self.hp
    
    def getAttackPower(self):
        return self.attack_power
    
    def getDefense(self):
        return self.defense
    
    def getLevel(self):
        return self.level
    
    def getExp(self):
        return self.exp