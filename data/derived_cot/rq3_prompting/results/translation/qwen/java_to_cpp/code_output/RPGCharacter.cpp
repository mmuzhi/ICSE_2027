#include <string>
#include <vector>

class RPGCharacter {
private:
    std::string name;
    int hp;
    int attackPower;
    int defense;
    int level;
    int exp;

public:
    // Constructor with 5 parameters
    RPGCharacter(const std::string& name, int hp, int attackPower, int defense, int level) {
        this->name = name;
        this->hp = hp;
        this->attackPower = attackPower;
        this->defense = defense;
        this->level = level;
        this->exp = 0;
    }

    // Constructor with 4 parameters (calls the 5-parameter constructor with level=1)
    RPGCharacter(const std::string& name, int hp, int attackPower, int defense) : RPGCharacter(name, hp, attackPower, defense, 1) {}

    // Attack method
    void attack(RPGCharacter& otherCharacter) {
        int damage = std::max(this->attackPower - otherCharacter.defense, 1);
        otherCharacter.hp -= damage;
    }

    // Heal method
    int heal() {
        this->hp += 10;
        if (this->hp > 100) {
            this->hp = 100;
        }
        return this->hp;
    }

    // Gain experience method
    void gainExp(int amount) {
        while (amount != 0) {
            if (this->exp + amount >= this->level * 100) {
                int needed = this->level * 100 - this->exp;
                amount -= needed;
                this->exp = this->level * 100;
                levelUp();
            } else {
                this->exp += amount;
                amount = 0;
            }
        }
    }

    // Level up method
    std::vector<int> levelUp() {
        if (this->level < 100) {
            this->level += 1;
            this->exp = 0;
            this->hp += 20;
            this->attackPower += 5;
            this->defense += 5;
        }
        return {this->level, this->hp, this->attackPower, this->defense};
    }

    // Check if character is alive
    bool isAlive() {
        return this->hp > 0;
    }

    // Getters
    std::string getName() const { return this->name; }
    int getHp() const { return this->hp; }
    int getAttackPower() const { return this->attackPower; }
    int getDefense() const { return this->defense; }
    int getLevel() const { return this->level; }
    int getExp() const { return this->exp; }
};