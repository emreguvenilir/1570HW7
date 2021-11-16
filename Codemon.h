#ifndef FS2021_CS1570_HW6_CODEMON_H
#define FS2021_CS1570_HW6_CODEMON_H

#include "Skill.h"

const int MAX_SKILL_SIZE = 6;
const string NOEFFECT = "None"; 
const string SUNNY = "Sunny"; // all damage dealt is doubled 
const string HAIL = "Hail"; // does 1/16 damaged to the first two codemon 
const string SNOW = "Snow"; // all damage is halved 
const string RAIN = "Rain"; // all attacks have 50% to miss 

class Codemon{
    friend class Contestant;
public:
    Codemon(){}
    Codemon(const string name, const string type, const int level, const int hp);
    //Pre: nSkill is defined, skills is valid, SIZE is > 0
    //Post: none
    //Description: Add a new skill to the skills array
    bool insertNewSkill(const Skill& skill);
    //Pre: None
    //Post: Skill return type
    //Desc: Getter function for the index of the skill array
    const Skill getSkill(const int index) const { return m_skillList[index]; }
    //Pre: m_name is valid
    //Post: String return type
    //Desc: Getter
    const string getName() const {return m_name;}
    //Pre: None
    //Post: string type returned
    //Desc: Sets a random weather condition
    static string setWeather();
    //Pre: string healed is valid
    //Post: Codemon type returned
    //Desc: heals all pokemon based on a condition
    Codemon & operator()(const string healed);
private:
    string m_name;
    string m_type;
    int m_level;
    int m_hp;
    int m_numSkillsOwned = 0;
    Skill m_skillList[MAX_SKILL_SIZE];

    int m_currentHp;
    static string m_weather;
    bool m_comatose;
};

#endif //FS2021_CS1570_HW6_CODEMON_H
