#include "Item.h"

Item::Item(const string name, const string purpose, const int duration){
    m_name = name;
    m_purpose = purpose;
    m_effectDuration = duration;
}
