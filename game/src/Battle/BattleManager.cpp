#include <Game/Battle/BattleManager.h>

void BattleManager::AddBattle(std::string battleName, std::shared_ptr<Battle> battle)
{
    battles[battleName] = battle;
}

std::shared_ptr<Battle> BattleManager::GetBattle(std::string battleName)
{
    if(HasBattle(battleName))
    {
        return battles[battleName];
    }
    return nullptr;
}
