#include <climits>
#include "Codemon.h"

using namespace std;

Codemon::Codemon(const string name, const string type, const int level, const int hp){
    m_name = name;
    m_type = type,
    m_level = level;
    m_hp = hp;
    m_currentHp = hp;
    m_comatose = false;
}
Codemon & Codemon::operator()(const string healed)
{
  if(healed=="heal")
  {
    m_currentHp = m_hp;
    m_comatose = false;
  }
  return *this;
}
bool Codemon::insertNewSkill(const Skill& skill){
    bool success = true;
    if(m_numSkillsOwned > (MAX_SKILL_SIZE-1))
        success = false;
    else
        m_skillList[m_numSkillsOwned++] = skill;
    return success;
}
string Codemon::m_weather = "";
string Codemon::setWeather()
{
  string w;
  const int POSSIBILITIES=5,NONE=1,SUN=2,HAILNUM=3,SNOWWY=4;
  int randWeather = rand()%POSSIBILITIES+1;
  if(randWeather==NONE)
  {
    w = NOEFFECT;
  }
  else if(randWeather==SUN)
  {
    w = SUNNY;
  }
  else if(randWeather==HAILNUM)
  {
    w = HAIL;
  }
  else if(randWeather==SNOWWY)
  {
    w = SNOW;
  }
  else
  {
    w = RAIN;
  }
  m_weather= w;
  return m_weather;
}
