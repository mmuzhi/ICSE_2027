#include <string>
#include <algorithm>

struct LevelUpResult {
    int new_level;
    int new_hp;
    int new_attack;
    int new_defense;
};

class RPGCharacter {
private:
    std::string name;
    int hp;
    int attack_power;
    int defense;
    int level;
    int exp;

public:
    RPGCharacter(std::string name, int hp, int attack_power, int defense, int level = 1)
        : name(name), hp(hp), attack_power(attack_power), defense(defense), level(level), exp(0) {}

    void attack(RPGCharacter& other) {
        int damage = std::max(this->attack_power - other.defense, 1);
        other.hp -= damage;
    }

    int heal() {
        this->hp += 10;
        if (this->hp > 100) {
            this->hp = 100;
        }
        return this->hp;
    }

    void gain_exp(int amount) {
        while (amount != 0) {
            if (this->exp + amount >= this->level * 100) {
                amount -= (this->level * 100 - this->exp);
                this->level_up();
            } else {
                this->exp += amount;
                amount = 0;
            }
        }
    }

    LevelUpResult level_up() {
        if (this->level < 100) {
            this->level++;
            this->exp = 0;
            this->hp += 20;
            this->attack_power += 5;
            this->defense += 5;
        }
        return LevelUpResult{this->level, this->hp, this->attack_power, this->defense};
    }

    bool is_alive() {
        return this->hp > 0;
    }
};