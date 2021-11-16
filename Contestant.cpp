#include <climits>
#include "Contestant.h"

#include <iostream>

using namespace std;

Contestant::Contestant(){
    cout << "What's your name, contestant?" << endl;
    getline(cin, m_name);
    m_numCodemonsOwned = 0;
    m_numItemsOwned = 0;
    m_openPocketIndex = 0;
    m_openBackpackIndex = 0;
    m_volume = rand() % 100 + 1;
}

Contestant::Contestant(string name){
m_name = name;
m_numCodemonsOwned = 0;
m_numItemsOwned = 0;
m_openPocketIndex = 0;
m_openBackpackIndex = 0;

m_volume = rand() % 100 + 1;
}
bool Contestant::insertNewCodemon(const Codemon& newCodemon){
    bool success = true;
    if(m_openPocketIndex > (POCKET_SIZE-1))
        success = false;
    else
        m_pocket[m_openPocketIndex++] = newCodemon;
    return success;
}

bool Contestant::insertNewItem(const Item& newItem){
    bool success = true;
    if(m_openBackpackIndex > (BACKPACK_SIZE-1))
        success = false;
    else
        m_backpack[m_openBackpackIndex++] = newItem;
    return success;
}

void Contestant::prepare(){
    cout << "Let's prepare you for the combat, contestant " << m_name << "!" << endl;
    char codemonChoice;
    do{
        cout << "Do you want to add a new Codemon? (y/n)" << endl;
        cin >> codemonChoice;
        if(codemonChoice == 'y'){
            cout << "Name of the Codemon?" << endl;
            cin >> m_pocket[m_numCodemonsOwned].m_name;
            cout << "The Codemon's type?" << endl;
            cin >> m_pocket[m_numCodemonsOwned].m_type;
            cout << "The Codemon's level?" << endl;
            cin >> m_pocket[m_numCodemonsOwned].m_level;
            cout << "The Codemon's HP?" << endl;
            cin >> m_pocket[m_numCodemonsOwned].m_hp;

            char skillChoice;
            do{
                cout << "Do you want to add a new skill for this Codemon? (y/n)" << endl;
                cin >> skillChoice;
                if(skillChoice == 'y'){
                    string skillName;
                    int skillDmg;
                    cout << "Name of the skill?" << endl;
                    cin >> skillName;
                    cout << "The skill's base damage?" << endl;
                    cin >> skillDmg;
                    m_pocket[m_numCodemonsOwned].insertNewSkill(Skill(skillName, skillDmg));
                }
            } while(skillChoice != 'n');

            m_numCodemonsOwned++;
        }
    } while(codemonChoice != 'n');

    char itemChoice;
    do{
        cout << "Do you want to add a new item? (y/n)" << endl;
        cin >> itemChoice;
        if(itemChoice == 'y'){
            cout << "Name of the item?" << endl;
            cin.ignore(INT_MAX, '\n');
            getline(cin, m_backpack[m_numItemsOwned].m_name);
            cout << "Purpose of the item?" << endl;
            getline(cin, m_backpack[m_numItemsOwned].m_purpose);
            cout << "Duration effect of the item?" << endl;
            cin >> m_backpack[m_numItemsOwned].m_effectDuration;
            m_numItemsOwned++;
        }
    } while(itemChoice != 'n');
}

void Contestant::print() const {
    cout << "Contestant name: " << m_name << endl;
    cout << "Number of Codemons owned: " << m_numCodemonsOwned << endl;
    if(m_numCodemonsOwned > 0){
        cout << "Pocket list:" << endl;
        for(int i=0; i<m_numCodemonsOwned; i++){
            cout << "\t\t" << i+1 << ") " << m_pocket[i].m_name << endl;
        }
    }
    if(m_numItemsOwned > 0){
        cout << "Backpack list:" << endl;
        for(int i=0; i<m_numItemsOwned; i++){
            cout << "\t\t" << i+1 << ") " << m_backpack[i].m_name << endl;
        }
    }
}

void skillLookUp(const Contestant contestants[], const int SIZE){
    char lookUpChoice;
    do{
        cout << "Hello, do you want to look up a skill? (y/n)" << endl;
        cin >> lookUpChoice;
        if(lookUpChoice == 'y'){
            cout << "What skill do you want to look up?" << endl;
            string skillToLookUp;
            cin.ignore(INT_MAX, '\n');
            getline(cin, skillToLookUp);
            bool firstTime = true;
            int listCounter = 1;
            for(int i=0; i<SIZE; i++){
                for(int j=0; j<POCKET_SIZE; j++){
                    for(int k=0; k<MAX_SKILL_SIZE; k++){
                        if(contestants[i].m_pocket[j].getSkill(k).getMName() == skillToLookUp){
                            if(firstTime){
                                cout << "Skill name: " << skillToLookUp << endl;
                                cout << "Base damage: " << contestants[i].m_pocket[j].getSkill(k).getMBaseDmg() << endl;
                                cout << "Acquired by: " << endl;
                                firstTime = false;
                            }
                            cout << "\t\t" << listCounter++ << ") " << contestants[i].m_pocket[j].getName()
                                 << " (" << contestants[i].m_name << ")" << endl;
                        }
                    }
                }
            }
        }
    } while (lookUpChoice!='n');
}
Contestant & Contestant::operator +(const Codemon & newCodemon)
{
    if(m_numCodemonsOwned<POCKET_SIZE)
    {
        m_pocket[m_numCodemonsOwned]= newCodemon;
    }
    else
    {
      int lowestLevel=0;
      for(int i=0;i<POCKET_SIZE;i++)
      {
        if(m_pocket[lowestLevel].m_level > m_pocket[i].m_level)
        {
            lowestLevel = i;
        }
      }
      m_pocket[lowestLevel] = newCodemon;
    }
    m_numCodemonsOwned++;
    return *this;
}
Contestant & Contestant::operator -(const Codemon & newCodemon)
{
    bool present =false;
    int index;
    for(int i=0;i<m_numCodemonsOwned;i++)
    {
        if(m_pocket[i].getName() ==newCodemon.getName())
        {
            present = true;
            m_pocket[i]= Codemon();
            index = i;
            m_numCodemonsOwned--;
        }
    }
    for(int j=index;j<m_numCodemonsOwned-1;j++)
    {
      m_pocket[j] = m_pocket[j+1];    
    }
    if(present ==false)
    {
        cout << "\nThe Codemon cannot be removed as it does not exist." << endl;
    }
    return *this;
}
Contestant & Contestant::operator -=(const Codemon & newCodemon)
{
  bool present =false;
  int index;
  for(int i=0;i<m_numCodemonsOwned;i++)
  {
    if(m_pocket[i].getName() ==newCodemon.getName())
    {
      present = true;
      m_pocket[i]= Codemon();
      index = i;
      m_numCodemonsOwned--;
    }
  }
  for(int j=index;j<m_numCodemonsOwned-1;j++)
  {
    m_pocket[j] = m_pocket[j+1];    
  }
    
  if(present ==false)
  {
    cout << "\nThe Codemon cannot be removed as it does not exist." << endl;
  }
  return *this;
}
Contestant & Contestant::operator +=(const Codemon & newCodemon)
{
    if(m_numCodemonsOwned<POCKET_SIZE)
    {
      m_pocket[m_numCodemonsOwned]= newCodemon;
    }
   // insertNewCodemon(newCodemon);
    else
    {
      int lowestLevel=0;
      for(int i=0;i<POCKET_SIZE;i++)
      {
        if(m_pocket[lowestLevel].m_level > m_pocket[i].m_level)
        {
            lowestLevel = i;
        }
      }
      m_pocket[lowestLevel] = newCodemon;
    }
    m_numCodemonsOwned++;
    return *this;
}


Contestant & Contestant::operator +(const Item & newItem)
{
    if(m_numItemsOwned < BACKPACK_SIZE)
    {
        m_backpack[m_numItemsOwned] = newItem;
        m_numItemsOwned++;
    }
    else
    {
        cout << "Your backpack is full!" << endl;
    }
    return *this;
}
Contestant & Contestant::operator +=(const Item & newItem)
{
    if(m_numItemsOwned < BACKPACK_SIZE)
    {
        m_backpack[m_numItemsOwned] = newItem;
        m_numItemsOwned++;
        return *this;
    }
    else
    {
        cout << "Your backpack is full!" << endl;
    }
    return *this;
}
Contestant & Contestant::operator -=(const Item & newItem)
{
  bool present =false;
  int index=0;
  for(int i=0;i<m_numItemsOwned;i++)
  {
    if(m_backpack[i].m_name ==newItem.m_name)
    {
      present = true;
      m_backpack[i]= Item();
      index = i;
      m_numItemsOwned--;
    }
  }
  for(int j=index;j<m_numItemsOwned-1;j++)
  {
    m_backpack[j] = m_backpack[j+1];    
  }
  if(present ==false)
  {
    cout << "\nThe Item cannot be removed as it does not exist." << endl;
  }
  return *this;
}
Contestant & Contestant::operator -(const Item & newItem)
{
  bool present =false;
  int index;
  for(int i=0;i<m_numItemsOwned;i++)
  {
    if(m_backpack[i].m_name ==newItem.m_name)
    {
      present = true;
      m_backpack[i]= Item();
      index = i;
      m_numItemsOwned--;
    }
  }
  for(int j=index;j<m_numItemsOwned-1;j++)
  {
    m_backpack[j] = m_backpack[j+1];    
  }
  if(present ==false)
  {
    cout << "\nThe Item cannot be removed as it does not exist." << endl;
  }
  return *this;
}
  

Contestant & Contestant::operator()(const string healed)
{
  if(healed=="heal")
  {
    for(int i=0;i<m_numCodemonsOwned;i++)
    {
        m_pocket[i].m_currentHp = m_pocket[i].m_hp;
    }
  }
  return *this;
}
void Contestant::shuffle()
{
  Codemon temp;
  for(int i=0;i<m_numCodemonsOwned;i++)
  {
    int randPos = rand()%m_numCodemonsOwned;
    temp = m_pocket[i];
    m_pocket[i] = m_pocket[randPos];
    m_pocket[randPos] = temp;
  }
}

Contestant & Contestant::operator *(Contestant & opponent)
{
  const int DEAD =0;
  string permWeather = m_pocket[0].setWeather();
  bool codemonAlive = false,opponentCodemonAlive=false,codemonFound=true,oppCodemonFound=true;
  int count=0,oppCount=0;//comatose index count
  int turnCount =1;
  shuffle();
  opponent.shuffle();

  if(permWeather==NOEFFECT)
  {
    cout << "It is perfect out!"<<endl;
    if(m_volume> opponent.m_volume)
    {
      cout << m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        if(turnCount%2!=0)
        {
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          opponent.m_pocket[oppCount].m_currentHp -= (m_pocket[count].getSkill(randSkill).getMBaseDmg());
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;
        }
        else if(turnCount%2==0)
        {
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          m_pocket[count].m_currentHp -= (opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg());
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
    }
    else
    {
      cout << opponent.m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        if(turnCount%2==0)
        {
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          opponent.m_pocket[oppCount].m_currentHp -= m_pocket[count].getSkill(randSkill).getMBaseDmg();
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;
        }
        else if(turnCount%2!=0)
        {
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          m_pocket[count].m_currentHp -= opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg();
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
      
    }
  }
  else if(permWeather==SUNNY)
  {
    cout << "It is sunny out!"<<endl;
    if(m_volume> opponent.m_volume)
    {
      cout << m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        const int SUN_MULTIPLIER =2;
        if(turnCount%2!=0)
        {
          
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          opponent.m_pocket[oppCount].m_currentHp -= SUN_MULTIPLIER*(m_pocket[count].getSkill(randSkill).getMBaseDmg());
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;
        }
        else if(turnCount%2==0)
        {
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          m_pocket[count].m_currentHp -= SUN_MULTIPLIER*(opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg());
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
    }
    else
    {
      cout << opponent.m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        const int SUN_MULTIPLIER =2;
        if(turnCount%2==0)
        {
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          opponent.m_pocket[oppCount].m_currentHp -= SUN_MULTIPLIER*(m_pocket[count].getSkill(randSkill).getMBaseDmg());
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;
        }
        else if(turnCount%2!=0)
        {
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          m_pocket[count].m_currentHp -= SUN_MULTIPLIER*(opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg());
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
    }
  }
  else if(permWeather==HAIL)
  {
    cout << "It is hailing!"<<endl;
    if(m_volume> opponent.m_volume)
    {
      const double HAIL_MULTIPLIER = (15.0/16);
      cout << m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        if(turnCount%2!=0)
        {
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          opponent.m_pocket[oppCount].m_currentHp -= (m_pocket[count].getSkill(randSkill).getMBaseDmg());
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;

          if(count == m_numCodemonsOwned-1)
          {
            (m_pocket[count].m_currentHp)-= ((HAIL_MULTIPLIER)*m_pocket[count].m_hp);
            if(m_pocket[count].m_currentHp <= DEAD)
            {
              m_pocket[count].m_comatose=true;
              count++;
            }
          }
          else
          {
            (m_pocket[count].m_currentHp)-= ((HAIL_MULTIPLIER)*m_pocket[count].m_hp);
            (m_pocket[count+1].m_currentHp)-= ((HAIL_MULTIPLIER)*m_pocket[count+1].m_hp);
            if(m_pocket[count].m_currentHp <= DEAD)
            {
              m_pocket[count].m_comatose=true;
              count++;
            }
          }
          if(oppCount == opponent.m_numCodemonsOwned-1)
          {
            (opponent.m_pocket[oppCount].m_currentHp)-= ((HAIL_MULTIPLIER)*opponent.m_pocket[oppCount].m_hp);
            if(opponent.m_pocket[oppCount].m_currentHp <= DEAD)
            {
              opponent.m_pocket[oppCount].m_comatose=true;
              oppCount++;
            }
          }
          else
          {
            (opponent.m_pocket[oppCount].m_currentHp)-= ((HAIL_MULTIPLIER)*opponent.m_pocket[oppCount].m_hp);
            (opponent.m_pocket[oppCount+1].m_currentHp)-= ((HAIL_MULTIPLIER)*opponent.m_pocket[oppCount+1].m_hp);
            if(opponent.m_pocket[oppCount].m_currentHp <= DEAD)
            {
              opponent.m_pocket[oppCount].m_comatose=true;
              oppCount++;
            }
          }
        }
        else if(turnCount%2==0)
        {
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          m_pocket[count].m_currentHp -= (opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg());
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
          if(count == m_numCodemonsOwned-1)
          {
            (m_pocket[count].m_currentHp)-= ((HAIL_MULTIPLIER)*m_pocket[count].m_hp);
            if(m_pocket[count].m_currentHp <= DEAD)
            {
              m_pocket[count].m_comatose=true;
              count++;
            }
          }
          else
          {
            (m_pocket[count].m_currentHp)-= ((HAIL_MULTIPLIER)*m_pocket[count].m_hp);
            (m_pocket[count+1].m_currentHp)-= ((HAIL_MULTIPLIER)*m_pocket[count+1].m_hp);
            if(m_pocket[count].m_currentHp <= DEAD)
            {
              m_pocket[count].m_comatose=true;
              count++;
            }
          }
          if(oppCount == opponent.m_numCodemonsOwned-1)
          {
            (opponent.m_pocket[oppCount].m_currentHp)-= ((HAIL_MULTIPLIER)*opponent.m_pocket[oppCount].m_hp);
            if(opponent.m_pocket[oppCount].m_currentHp <= DEAD)
            {
              opponent.m_pocket[oppCount].m_comatose=true;
              oppCount++;
            }
          }
          else
          {
            (opponent.m_pocket[oppCount].m_currentHp)-= ((HAIL_MULTIPLIER)*opponent.m_pocket[oppCount].m_hp);
            (opponent.m_pocket[oppCount+1].m_currentHp)-= ((HAIL_MULTIPLIER)*opponent.m_pocket[oppCount+1].m_hp);
            if(opponent.m_pocket[oppCount].m_currentHp <= DEAD)
            {
              opponent.m_pocket[oppCount].m_comatose=true;
              oppCount++;
            }
          }
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
      
    }
    else
    {
      cout << opponent.m_name << " will attack first." <<endl;
    }
  }
  else if(permWeather==SNOW)
  {
    cout << "It is snowing!"<<endl;
    const int SNOW_MULTIPLIER=2;
    if(m_volume> opponent.m_volume)
    {
      cout << m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        if(turnCount%2!=0)
        {
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          opponent.m_pocket[oppCount].m_currentHp -= (m_pocket[count].getSkill(randSkill).getMBaseDmg())/SNOW_MULTIPLIER;
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;
        }
        else if(turnCount%2==0)
        {
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          m_pocket[count].m_currentHp -= (opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg())/SNOW_MULTIPLIER;
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
    }
    else
    {
      cout << opponent.m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        if(turnCount%2==0)
        {
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          opponent.m_pocket[oppCount].m_currentHp -= (m_pocket[count].getSkill(randSkill).getMBaseDmg())/SNOW_MULTIPLIER;
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;
        }
        else if(turnCount%2!=0)
        {
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          m_pocket[count].m_currentHp -= (opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg())/SNOW_MULTIPLIER;
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
    }
  }
  else if(permWeather==RAIN)
  {
    cout << "It is raining!"<<endl;
    const int RAIN_VAL =2;
    if(m_volume> opponent.m_volume)
    {
      cout << m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        if(turnCount%2!=0)
        {
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          int damageZero = (rand() % RAIN_VAL);

          if(damageZero==0)
          {
            opponent.m_pocket[oppCount].m_currentHp -= (m_pocket[count].getSkill(randSkill).getMBaseDmg());
          }
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;
        }
        else if(turnCount%2==0)
        {
          int damageZero = (rand() % RAIN_VAL);
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          if(damageZero == 0)
          {
            m_pocket[count].m_currentHp -= (opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg());
          }
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
    }
    else
    {
      cout << opponent.m_name << " will attack first." <<endl;
      while(codemonFound==true)
      {
        if(m_pocket[count].m_comatose==false)
        {
          codemonFound = false;
        }
        count++;
      }
      while(oppCodemonFound==true)
      {
        if(opponent.m_pocket[oppCount].m_comatose==false)
        {
          oppCodemonFound=false;
        }
        oppCount++;
      }

      while(m_pocket[count].m_comatose == false && opponent.m_pocket[oppCount].m_comatose == false && count < m_numCodemonsOwned && oppCount < opponent.m_numCodemonsOwned)
      {
        if(turnCount%2==0)
        {
          int damageZero = (rand() % RAIN_VAL);
          int randSkill = rand() % m_pocket[count].m_numSkillsOwned;
          if(damageZero==0)
          {
            opponent.m_pocket[oppCount].m_currentHp -= (m_pocket[count].getSkill(randSkill).getMBaseDmg());
          }
          if(opponent.m_pocket[oppCount].m_currentHp<=DEAD)
          {
            opponent.m_pocket[oppCount].m_comatose = true;
            oppCount++;
          }
          turnCount++;
        }
        else if(turnCount%2!=0)
        {
          
          int damageZero = (rand() % RAIN_VAL);
          int randSkill = rand() % m_pocket[oppCount].m_numSkillsOwned;
          if(damageZero==0)
          {
            m_pocket[count].m_currentHp -= (opponent.m_pocket[oppCount].getSkill(randSkill).getMBaseDmg());
          }
          if(m_pocket[count].m_currentHp<=DEAD)
          {
            m_pocket[count].m_comatose = true;
            count++;
          }
          turnCount++;
        }
      }
      for(int i=0;i<m_numCodemonsOwned;i++)
      {
        if(m_pocket[i].m_comatose==false)
        {
          codemonAlive = true;
        }
      }
      for(int i=0;i<opponent.m_numCodemonsOwned;i++)
      {
        if(opponent.m_pocket[i].m_comatose==false)
        {
          opponentCodemonAlive = true;
        }
      }

      if(codemonAlive==true && opponentCodemonAlive == false)
      {
        return *this;
      }
      else
      {
        return opponent;
      }
    }
  }
  return *this;
}