#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseKnight;
class Events;
class BaseItem;

enum ItemType {Antidote = 0, PhoenixDownI, PhoenixDownII, PhoenixDownIII, PhoenixDownIV};

class BaseItem {
public:
    ItemType itemType;
public:
    virtual bool canUse ( BaseKnight * knight );
    virtual void use ( BaseKnight * knight );
};
class Antidote_Item: public BaseItem{
public:
Antidote_Item(){itemType = Antidote;}
    bool canUse(BaseKnight* knight){return BaseItem::canUse(knight);}
    void use(BaseKnight* knight){BaseItem::use(knight);}
};
class PhoenixDownI_Item: public BaseItem{
public: 
PhoenixDownI_Item(){itemType = PhoenixDownI;}
    bool canUse(BaseKnight* knight){return BaseItem::canUse(knight);}
    void use(BaseKnight* knight){BaseItem::use(knight);}
};
class PhoenixDownII_Item: public BaseItem{
public:
PhoenixDownII_Item(){itemType = PhoenixDownII;}
    bool canUse(BaseKnight* knight){return BaseItem::canUse(knight);}
    void use(BaseKnight* knight){BaseItem::use(knight);}
};
class PhoenixDownIII_Item: public BaseItem{
public:
PhoenixDownIII_Item(){itemType = PhoenixDownIII;}
    bool canUse(BaseKnight* knight){return BaseItem::canUse(knight);}
    void use(BaseKnight* knight){BaseItem::use(knight);}
};
class PhoenixDownIV_Item: public BaseItem{
public:
PhoenixDownIV_Item(){itemType = PhoenixDownIV;}
    bool canUse(BaseKnight* knight){return BaseItem::canUse(knight);}
    void use(BaseKnight* knight){BaseItem::use(knight);}
};


class Node{
public:
    BaseItem* input;
    Node* next;
public:
    Node(BaseItem* input, Node* next):input(input),next(next){}
    ~Node(){delete input;}
};
class BaseBag {
protected:
    BaseKnight* knight;
    int s = 0;
    int cap = 0;
    Node* head = nullptr;
public:
    BaseBag(BaseKnight* knight, int antinote, int phoenixDownI, int cap){
        this->knight = knight;
        this->cap = cap;
        while(s != cap && phoenixDownI--) this->insertFirst(new PhoenixDownI_Item());
        while(s != cap && antinote--) this->insertFirst(new Antidote_Item());
    }
    virtual bool insertFirst(BaseItem * item){
        if(s == cap) return false;
        head = new Node(item, head);
        s ++;
        return true;
    }
    virtual BaseItem * get(ItemType itemType){
        Node* temp = head;
        while(temp && temp->input->itemType != itemType) temp = temp->next;
        if(temp){
            swap(head->input, temp->input);
            head->input->use(knight);
            remove();   
        }
        return nullptr;        
    }
    void checkHP(){
        Node* temp = head;
        while(temp && !temp->input->canUse(knight)) temp = temp->next;
        if(temp){
            swap(head->input, temp->input);
            head->input->use(knight);
            remove();
        }
    }
    void remove(){
        if(s == 0) return;
        s --;
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    virtual string toString() const{
        string result = "Bag[count=" + to_string(s) + ";";
        if(s == 0) return result + "]";
        Node* temp = head;
        while(temp){
            string typestring[] = { "Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
            result += typestring[temp->input->itemType] + ",";
            temp = temp->next;
        }
        result[result.length() - 1] = ']';
        return  result;
    }
    ~BaseBag(){while(s) remove();}
};
class Bag_PaladinKnight : public BaseBag{
public:
    Bag_PaladinKnight(BaseKnight* knight, int antinote, int phoenixDownI):BaseBag(knight, antinote, phoenixDownI, -1){
    }
};
class Bag_LancelotKnight : public BaseBag{
public:
    Bag_LancelotKnight(BaseKnight* knight, int antinote, int phoenixDownI):BaseBag(knight, antinote, phoenixDownI, 16){
    }
};
class Bag_NormalKnight : public BaseBag{
public:
    Bag_NormalKnight(BaseKnight* knight, int antinote, int phoenixDownI):BaseBag(knight, antinote, phoenixDownI, 19){
    }
};

class Bag_DragonKnight : public BaseBag{
public:
    Bag_DragonKnight(BaseKnight* knight, int antinote, int phoenixDownI):BaseBag(knight,0, phoenixDownI, 14){
    }
};

enum OpponentType {MadBear = 1, Bandit, LordLupin, Elf, Troll, Tornbery, 
QueenOfCards, NinaDeRings, DurianGarden, OmegaWeapon, Hades};
class BaseOpponent{
public:
    static bool winOmegaWeapon; 
    static bool WinHades;
protected:
    int i;
    OpponentType type;
    int gil_reward[5] = {100,150,450,750,800};
public:
    static BaseOpponent * create(int i, OpponentType opponentType);
    virtual void NewKnight(BaseKnight* knight) = 0;
    virtual OpponentType Type(){return type;}
};
class MadBear_1: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class Bandit_2: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class LordLupin_3: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class Elf_4: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class Troll_5: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class Tornbery_6: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class QueenOfCards_7: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class NinaDeRings_8: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class DurianGarden_9: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class OmegaWeapon_10: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};
class Hades_11: public BaseOpponent{
    void NewKnight(BaseKnight* knight);
};


enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil_reward;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

    bool isPoisoned= false;
public:
    bool check_Itemtype(ItemType type){
        if(type == Antidote) return this->isPoisoned;
        else if(type == PhoenixDownI) return hp <= 0;
        else if(type == PhoenixDownII) return hp <  maxhp / 4;
        else if(type == PhoenixDownIII) return hp <  maxhp / 3;
        return hp <  maxhp / 2;
    }
    void Use_Item(ItemType type){
        if(type == Antidote) this->isPoisoned= false;
        else if(type == PhoenixDownI) this->hp = this->maxhp;
        else if(type == PhoenixDownII) this->hp = this->maxhp;
        else if(type == PhoenixDownIII)  hp = (hp <= 0) ? maxhp / 3 : (hp + maxhp / 4);
        else  hp = (hp <= 0) ? maxhp / 2 : (hp + maxhp / 5);
    }
public:

    int getHP(){return hp;}
    int getLevel(){return level;}
    int getMaxHp(){return maxhp;}
    bool getPoisoned(){return isPoisoned;}
    int getgil_reward(){ return gil_reward;}
    KnightType getKnightType(){return knightType;}
    void setHP(int hp){
        if(this->hp > hp){
            this->hp = hp;
            bag->checkHP();
            if(this->hp <= 0 && gil_reward >= 100){
                this->hp = maxhp / 2;
                gil_reward -= 100;
            }   
        }
        else this->hp = hp;

        if(hp > maxhp) this->hp = maxhp;
    }
    void setLevel(int level){
        if(level > 10) this->level = 10;
        else this->level = level;
    }
    void be_Poisoned(bool poisoned){
        this->isPoisoned= poisoned;
        if(knightType == DRAGON) this->isPoisoned= false;
        if(poisoned) bag->get(Antidote);
        if(this->isPoisoned){
            isPoisoned= false;
            hp -= 10;
            bag->remove();
            bag->remove();
            bag->remove();
            bag->checkHP();
        }     
    }
    void setgil_reward(int gil_reward){
        this->gil_reward = gil_reward;
    }
    bool setBag(BaseItem* item){
        return bag->insertFirst(item);
    }


public:
    static BaseKnight * create(int id, int maxhp, int level, int gil_reward, int antidote, int phoenixdownI);
    string toString() const;

    virtual bool fight_opponent(BaseOpponent * opponent) = 0;
    int knightBaseDamage(){
        double dame[] = {0.06,0.05,0.075,0};;
        return dame[this->knightType]*this->level * this->hp;
    }
    ~BaseKnight(){delete bag;};
};
class PaladinKnight : public BaseKnight{
public:
    PaladinKnight(int antidote, int phoenixdownI){
        knightType = PALADIN;
        bag = new Bag_PaladinKnight(this, antidote, phoenixdownI); 
    }
    bool fight_opponent(BaseOpponent * opponent);
};
class LancelotKnight : public BaseKnight{
public:
    LancelotKnight(int antidote, int phoenixdownI){
        knightType = LANCELOT;
        bag = new Bag_LancelotKnight(this, antidote, phoenixdownI);
    }
    bool fight_opponent(BaseOpponent * opponent);
};
class DragonKnight : public BaseKnight{
public:
    DragonKnight(int antidote, int phoenixdownI){
        knightType = DRAGON;
        bag = new Bag_DragonKnight(this, antidote, phoenixdownI);
    }
    bool fight_opponent(BaseOpponent * opponent);
};
class NormalKnight : public BaseKnight{
public:
    NormalKnight(int antidote, int phoenixdownI){
        knightType = NORMAL;
        bag = new Bag_NormalKnight(this, antidote, phoenixdownI);
    }
    bool fight_opponent(BaseOpponent * opponent);
};
class Events {
private:
    int* event_codes;
    int s;
public:
    Events(string file_events){
        ifstream file(file_events);
        file >> s;
        event_codes = new int[s];
        for(int i = 0; i < s; i++) file >> event_codes[i];
    }
    int get(int i) const{return event_codes[i];}
    int count() const{return s;}
    ~Events(){delete[] event_codes;}
};

class ArmyKnights {
private:
    BaseKnight** event_codes;
    int s;
    bool ishasPaladinShield = false, ishasLancelotSpear = false, ishasGuinevereHair = false, ishasExcaliburSword = false;    
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    void Insert_Item( BaseItem* item);
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    bool Ultimecia();
    int count() const{ return this->s;}
    BaseKnight * lastKnight() const{ return this->event_codes[s - 1];}
    bool hasPaladinShield() const{ return ishasPaladinShield;}
    bool hasLancelotSpear() const{ return ishasLancelotSpear;}
    bool hasGuinevereHair() const{ return ishasGuinevereHair;}
    bool hasExcaliburSword() const{ return ishasExcaliburSword;}
    void printInfo() const;
    void printResult(bool win) const;
};


class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure(){armyKnights =nullptr; events =nullptr;}
    void loadArmyKnights(const string & file){armyKnights = new ArmyKnights(file);}
    void loadEvents(const string & file){events = new Events(file);}
    void run(){armyKnights->printResult(armyKnights->adventure(events));}
    ~KnightAdventure(){
        
        delete armyKnights;
        delete events;
    }
};

#endif // __KNIGHT2_H__