#ifndef IDRAWABLEPETUTILITY_H
#define IDRAWABLEPETUTILITY_H
class IDrawablePetUtility
{
public:
    virtual ~IDrawablePetUtility(){} 
    virtual void drawPetUsual() = 0;
    virtual void drawPetSleep() = 0;
    virtual void drawPetDeath() = 0;
    virtual void drawPetSad() = 0;
    virtual void drawPetHappy() = 0;
};

#endif