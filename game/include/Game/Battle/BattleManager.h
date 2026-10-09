#pragma once

#include <memory>
#include <map>
#include <string>

class Battle;

class BattleManager {

public:
    BattleManager(){}
    ~BattleManager(){}

    void AddBattle(std::string battleName, std::shared_ptr<Battle> battle);
    bool HasBattle(std::string battleName){return battles.count(battleName) > 0;}
    std::shared_ptr<Battle> GetBattle(std::string battleName);
private:
    std::map<std::string, std::shared_ptr<Battle>> battles;
};