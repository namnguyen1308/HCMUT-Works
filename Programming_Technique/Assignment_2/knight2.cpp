#include "knight2.h"



bool BaseOpponent::winOmegaWeapon = false;
bool BaseOpponent::WinHades = false;


/* * * BEGIN implementation of class BaseOpponent * * */
BaseOpponent * BaseOpponent::create(int i, OpponentType opponentType){
    BaseOpponent * opponent;
    if(opponentType == 1) opponent = new MadBear_1();
    else if(opponentType == 2) opponent = new Bandit_2();
    else if(opponentType == 3) opponent = new LordLupin_3();
    else if(opponentType == 4) opponent = new Elf_4();
    else if(opponentType == 5) opponent = new Troll_5();
    else if(opponentType == 6) opponent = new Tornbery_6();
    else if(opponentType == 7) opponent = new QueenOfCards_7();
    else if(opponentType == 8) opponent = new NinaDeRings_8();
    else if(opponentType == 9) opponent = new DurianGarden_9();
    else if(opponentType == 10) opponent = new OmegaWeapon_10();
    else  opponent = new Hades_11();
    opponent->i = i;
    opponent->type = opponentType;
    return opponent;
}

void MadBear_1::NewKnight(BaseKnight* knight){
    int levelO = (this->i + this->Type())%10;
    if( levelO < knight->getLevel()) knight->setgil_reward(knight->getgil_reward() + gil_reward[0]);
    else knight->setHP(knight->getHP() - gil_reward[0]/10 * ( levelO + 1 - knight->getLevel()));   
}

void Bandit_2::NewKnight(BaseKnight* knight){
    int levelO = (this->i + this->Type())%10;
    if( levelO < knight->getLevel()) knight->setgil_reward(knight->getgil_reward() + gil_reward[1]);
    else knight->setHP(knight->getHP() - gil_reward[1]/10 * ( levelO + 1 - knight->getLevel()));
}

void LordLupin_3::NewKnight(BaseKnight* knight){
   int levelO = (this->i + this->Type())%10;
    if( levelO < knight->getLevel()) knight->setgil_reward(knight->getgil_reward() + gil_reward[2]);
    else knight->setHP(knight->getHP() - gil_reward[2]/10 * ( levelO + 1 - knight->getLevel()));
}

void Elf_4::NewKnight(BaseKnight* knight){
    int levelO = (this->i + this->Type())%10;
    if( levelO < knight->getLevel()) knight->setgil_reward(knight->getgil_reward() + gil_reward[3]);
    else knight->setHP(knight->getHP() - gil_reward[3]/10 * ( levelO + 1 - knight->getLevel()));
}

void Troll_5::NewKnight(BaseKnight* knight){
   int levelO = (this->i + this->Type())%10;
    if( levelO < knight->getLevel()) knight->setgil_reward(knight->getgil_reward() +gil_reward[4]);
    else knight->setHP(knight->getHP() - 95 * ( levelO + 1 - knight->getLevel()));
}

void Tornbery_6::NewKnight(BaseKnight* knight){
    int levelO = (this->i + this->Type())%10;
    if( levelO < knight->getLevel()) knight->setLevel(knight->getLevel() + 1);
    else if(knight->getKnightType() == DRAGON);
    else knight->be_Poisoned(true);
}

void QueenOfCards_7::NewKnight(BaseKnight* knight){
    int levelO = (this->i + this->Type())%10;
    if( levelO < knight->getLevel()) knight->setgil_reward(knight->getgil_reward() * 2);
    else if(knight->getKnightType() == PALADIN) return;
    else knight->setgil_reward(knight->getgil_reward() / 2);
}

void NinaDeRings_8::NewKnight(BaseKnight* knight){
    if(knight->getHP() >= knight->getMaxHp() / 3 || knight->getgil_reward() < 50) return;

    knight->setgil_reward(knight->getgil_reward() - 50);
    knight->setHP(knight->getHP() + knight->getMaxHp()/5);
}

void DurianGarden_9::NewKnight(BaseKnight* knight){knight->setHP(knight->getMaxHp());}

void OmegaWeapon_10::NewKnight(BaseKnight* knight){
    if(this->winOmegaWeapon);
    else if (knight->getLevel() == 10 && knight->getHP() == knight->getMaxHp())
    {
        knight -> setgil_reward(999);
        this -> winOmegaWeapon = true;
    }
    else knight-> setHP(0);
}

void Hades_11::NewKnight(BaseKnight* knight){
    this->WinHades = (knight->getLevel() == 10 || this->WinHades);
    if(!this->WinHades) knight->setHP(0);
}

/* * * END implementation of class BaseOpponent * * */


/* * * BEGIN implementation of class BaseKnight * * */
bool isPrime(int maxhp){
    int count = 0;
    for(int i = 1; i <= maxhp; i++) 
        if(maxhp % i == 0) count ++;
    return count == 2;
}
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil_reward, int antidote, int phoenixdownI){
    BaseKnight* knight;
    if(maxhp == 435 || maxhp == 453 || maxhp == 534 || maxhp == 543 || maxhp == 345 || maxhp == 354 ) knight = new DragonKnight(antidote, phoenixdownI);
    else if(maxhp == 888){knight = new LancelotKnight(antidote, phoenixdownI);}
    else if(isPrime(maxhp)){knight = new PaladinKnight(antidote, phoenixdownI);}
    else{knight = new NormalKnight(antidote, phoenixdownI);}
    knight->id = id;
    knight->maxhp = knight->hp = maxhp;
    knight->level = level;
    knight->gil_reward = gil_reward;
    return knight;
}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format cout must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil_reward)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
bool PaladinKnight::fight_opponent(BaseOpponent * opponent){
    OpponentType type = opponent->Type();
    if(type == 1) gil_reward += 100;
    else if(type == 2) gil_reward += 150;
    else if(type == 3) gil_reward += 450;
    else if(type == 4) gil_reward += 750;
    else if(type == 5) gil_reward += 800;
    else if(type == 8 && hp < maxhp / 3) hp += maxhp / 5;
    else if(type == Hades && this->level >= 8) BaseOpponent::WinHades = true;
    else opponent->NewKnight(this);
    return this->hp > 0;
}
bool LancelotKnight::fight_opponent(BaseOpponent * opponent){
    OpponentType type = opponent->Type();
    if(type == 1) gil_reward += 100;
    else if(type == 2) gil_reward += 150;
    else if(type == 3) gil_reward += 450;
    else if(type == 4) gil_reward += 750;
    else if(type == 5) gil_reward += 800;
    else opponent->NewKnight(this);
    return this->hp > 0;
}
bool DragonKnight::fight_opponent(BaseOpponent * opponent){
    OpponentType type = opponent->Type();
    if(type == OmegaWeapon){
        if(!BaseOpponent::winOmegaWeapon){
            level = 10;
            gil_reward = 999;
            BaseOpponent::winOmegaWeapon = true;
        }
    }
    else opponent->NewKnight(this); 
    return this->hp > 0;
}
bool NormalKnight::fight_opponent(BaseOpponent * opponent){
   OpponentType type = opponent->Type();
    if(type == OmegaWeapon){
        if(!BaseOpponent::winOmegaWeapon && level==10&&hp==maxhp&&knightType==NORMAL){
            level = 10;
            gil_reward = 999;
            BaseOpponent::winOmegaWeapon = true;
        }
        else if(!BaseOpponent::winOmegaWeapon) this->setHP(0);
    }
    else opponent->NewKnight(this); 
    return this->hp > 0;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights (const string & file_armyknights){
    ifstream file(file_armyknights);
    file >> s;
    event_codes = new BaseKnight*[s];
    int maxhp, level, phoenixdownI, gil_reward, antidote;
    for(int i = 0; i < s; i++){
        file >> maxhp >> level >> phoenixdownI >> gil_reward >> antidote;
        event_codes[i] = BaseKnight::create(i + 1, maxhp, level, gil_reward,antidote, phoenixdownI);
    }    
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}
void ArmyKnights::printResult(bool win) const 
{
    cout << (win ? "WIN" : "LOSE") << endl;
}
bool ArmyKnights::fight(BaseOpponent * opponent){
    while(s){
        BaseKnight * knight = lastKnight();
        knight->fight_opponent(opponent);
        if(knight->getHP() > 0) break;
        s --;
        delete knight;
        break;
    }
    if(BaseOpponent::WinHades) this->ishasPaladinShield = true;
    delete opponent;
    if(s == 0) return false;
    for(int i = s - 1; i > 0; i--){
        int res = event_codes[i]->getgil_reward() - 999;

        if(res <= 0) return this->count();
        event_codes[i]->setgil_reward(999);
        event_codes[i-1]->setgil_reward(event_codes[i-1]->getgil_reward() + res);
    }
    int res = event_codes[s - 1]->getgil_reward() - 999;

    if(res > 0) event_codes[s - 1]->setgil_reward(999);
    return this->count();
}
bool ArmyKnights::adventure (Events * events){
    BaseOpponent::winOmegaWeapon = BaseOpponent::WinHades = false;
    for(int i = 0; i < events->count(); i++){
        int Num_evt = events->get(i);
        if(Num_evt >= 1 && Num_evt <= 11){
            this->fight(BaseOpponent::create(i,OpponentType(Num_evt)));
        }
        else if(Num_evt == 95){this->ishasPaladinShield = true;}
        else if(Num_evt == 96){this->ishasLancelotSpear = true;}
        else if(Num_evt == 97){this->ishasGuinevereHair = true;}
        else if(Num_evt == 98){this->ishasExcaliburSword = ishasPaladinShield && ishasLancelotSpear && ishasGuinevereHair;}
        else if(Num_evt == 112){this->Insert_Item(new PhoenixDownII_Item());}
        else if(Num_evt == 113){this->Insert_Item(new PhoenixDownIII_Item());}
        else if(Num_evt == 114){this->Insert_Item(new PhoenixDownIV_Item());}
        else if(Num_evt == 99){return this->Ultimecia();}
        this->printInfo();
        if(s == 0) return false;
    } 
    return true;    
}
void ArmyKnights::Insert_Item( BaseItem* item){
    for(int j = s - 1; j >= 0; j--) {if(event_codes[j]->setBag(item)) return;}
    delete item; 
}
bool ArmyKnights::Ultimecia(){
    if(ishasExcaliburSword){
        this->printInfo();
    }
    else if(!ishasGuinevereHair || !ishasLancelotSpear || !ishasPaladinShield){
        for(int i = 0; i < s; i++ ) delete event_codes[i];
        s = 0;
        this->printInfo();
    }
    else{
        int HpUltimecia = 5000;
        BaseKnight* last = nullptr;
        int sNo = 0;
        while(s){
            HpUltimecia -= lastKnight()->knightBaseDamage();
            if(lastKnight()->knightBaseDamage() == 0){
                sNo++;
                if(!last){
                    last = lastKnight();
                    s --;
                    continue;
                }
            }
            while (HpUltimecia = 0){
                if(sNo > 0){
                    s += sNo;
                    if(last) event_codes[s - 1] = last;
                    this->printInfo();
                    s -= sNo;
                    if(last) delete last;
                    return true;
                }
                break;
            }
            delete lastKnight();
            s --;
        }
        if(last) delete last;
        this->printInfo();
    }  
    return s > 0;
}   
ArmyKnights::~ArmyKnights(){
    for(int i = 0; i < s; i++) delete event_codes[i];
    delete[] event_codes;
}
/* * * END implementation of class ArmyKnights * * */

bool BaseItem::canUse ( BaseKnight * knight ){return knight->check_Itemtype(itemType);}
void BaseItem::use ( BaseKnight * knight ){knight->Use_Item(itemType);}
