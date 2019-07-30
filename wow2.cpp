#include<cstdio>
#include<list>
#include<cstring>
#include<cmath>
#include <iostream>
using namespace std;

int M, N, R, K, T,hour,minute;

class City;
class Commander;
class Warrior;
class CityList;
class Weapon;
class Sword;
class Bomb;
class Arrow;
class Dragon;
class Ninja;
class Iceman;
class Lion;
class Wolf;


class Weapon{
protected:
	int id; 
	char* name; 
	int force; 
public:
	Weapon(){}
	Weapon(int idIn, int forceIn = 0);
	Weapon(Weapon *w){ id = w->id; name = w->name; force = w->force; }
	char* getName();
	int getForce();
	void setForce(int forceIn);
};

class Sword :public Weapon{
public:
	Sword(int forceIn);
	void swordUsed(); 
};

class Bomb : public Weapon{
public:
	Bomb(int isgood);
};

class Arrow :public Weapon{
public:
	Arrow(int times); 
	bool arrowUsed(); 
};

class City{
	friend class CityList;
	friend class Warrior;
protected:
	int cityNo;
	City *west;
	City *east;
	char *flag;
	int element;
	int redwin;
	int bluewin;
	Warrior *fromRed;
	Warrior *fromBlue;
public:
	City(int cityNoIn, City *w = NULL, City *e = NULL);
	City* insertAsWest(const int &cityNoIn);
	City * insertAsEast(const int &cityNoIn);
	void addElement(){ element += 10; } 
	void warriorArrived(Warrior *warriorIn);
	void fight();
	void raiseFlag(char *color);
	void getCityElement();
	int getCityNo();
	void removeWarrior(Warrior *deadwarrior);
	void useBomb();
};

class CityList{
private:
	int totalCityNo;
	City *Red;
	City *Blue;
protected:
	void init(){
		Red = new City(0);
		Blue = new City(totalCityNo + 1);
		Red->west = NULL;
		Red->east = Blue;
		Blue->west = Red;
		Blue->east = NULL;
	}
public:
	CityList(int totalCity);
	void LionRunAway();
	int March();
	bool PrintMarch();
	void SendArrow();
	void UseBomb();
	void Fight();
	void WarriorReport();
	City * getCity(const char *name);
	void ProduceElement();
	void getElement();
};

class Warrior{
protected:
	int no;
	int element;
	int force;
	char *type;
	Commander *commander;
	City *inCity;
	bool taskCompleted;
	Weapon weapon[3];

public:
	Warrior(Commander *c, CityList *cl, int noIn, int elementIn, int forceIn, char *typeIn);
	~Warrior(){ delete[]type; }
	int getNo(){ return no; }
	void setType(char * typeIn){ type = typeIn; }
	char *getType(){ return type; }
	void setElement(int elementIn){ element = elementIn; }
	int getElement(){ return element; }
	int decreseElement(int decreasedValue){ return element -= decreasedValue; }
	void setForce(int forceIn){ force = forceIn; }
	int getForce(){ return force; }
	Commander &getCommander(){ return *commander; }
	City& getCity(){ return *inCity; }
	int getWeaponForce(int windex);
	void sendArrow();
	bool hasBomb();
	bool useBomb();
	bool useBombjudgement();
	bool march();
	void attack(Warrior *enemy);
	void fakeAttack(Warrior *enemy);
	void fightBack(Warrior *enemy);
	void sendBackElement(int elementIn);
	void getBonus();
	void reportWeaponUsage();

	void update(){}
	bool runaway(){ return false; }
	void hurray(){}
	void acquireWeapon(Warrior *enemy){}
};

class Dragon :public Warrior{
private:
	double morale;
public:
	Dragon(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn);
	void hurray();
};

class Ninja :public Warrior{
public:
	Ninja(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn);
};

class Iceman :public Warrior{
public:
	Iceman(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn);
};

class Lion :public Warrior{
private:
	int loyalty;
public:
	Lion(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn);
	bool runaway();
	void update(){ loyalty -= K; }
};

class Wolf :public Warrior{
public:
	Wolf(Commander *c, CityList *cl, int noIn, int lifeIn, int forceIn);
	void acquireWeapon(Warrior *enemy);
};



class Commander{
private:
	int lifeleft;
	char *name;
	int life[5];
	char *types[5]; 
	int force[5];
	int no;
	int count[5]; 
	int currentType;
	City *west;
	City *east;
	int cityNo;
	int enemyNo;
	CityList *clist;

public:
	Commander() : no(0), currentType(0), enemyNo(0), west(NULL), east(NULL),clist(NULL){} 
	void setTotalLife(int totalLifeIn) { lifeleft = totalLifeIn; }
	int getLifeLeft(){	return lifeleft; }
	void reportLifeLeft(){ printf("%03d:50 %d elements in %s headquarter\n", hour,lifeleft, name); }
	void sendBonus(){ lifeleft -= 8;}
	char *getName(){ return name; }
	void setForce(int f0, int f1, int f2, int f3, int f4);
	void addLife(int lifeIn){ lifeleft += lifeIn; }
	int getCityNo(){ return cityNo; }
	void addEnemy(){ enemyNo++; }
	void setTypes(char **typesIn);
	void setLife(int l0, int l1, int l2, int l3, int l4);
	void setName(char *color);
	void setCityList(CityList *cl);
	void makeWarrior();
	void resetCommander();
	bool isconquered();
	~Commander(){
		for (int i = 0; i < 5; i++){
			delete[] types[i];
		}
		delete name;
	}
}red,blue;


Weapon::Weapon(int idIn, int forceIn) :id(idIn), force(forceIn){
	switch (idIn){
	case 0:name = "sword"; break;
	case 1:name = "bomb"; break;
	case 2:name = "arrow"; break;
	}
}

char * Weapon::getName(){ return name; }

int Weapon::getForce(){ return force; }

void Weapon::setForce(int forceIn){ force = forceIn; }

Sword::Sword(int forceIn) :Weapon(0, forceIn){}

void Sword::swordUsed(){ force = int(force*0.8); }

Bomb::Bomb(int isgood) :Weapon(1, isgood){}

Arrow::Arrow(int times=3) : Weapon(2, times){}

bool Arrow::arrowUsed(){
	if (force == 0)
		return false;
	--force;
	return true;
}

City::City(int cityNoIn, City *w, City *e )
	: cityNo(cityNoIn), west(w), east(e){
	bluewin = 0;
	redwin = 0;
	flag = NULL;
	element = 0;
	fromRed = NULL;
	fromBlue = NULL;
}
City * City::insertAsWest(const int &cityNoIn){
	City *x = new City(cityNoIn, west, this);
	west->east = x; west = x;
	return x;
}
City * City::insertAsEast(const int &cityNoIn){
	City *x = new City(cityNoIn, this, east);
	east->west = x; east = x;
	return x;
}
void City::warriorArrived(Warrior *warriorIn){
	char *tname = warriorIn->getCommander().getName();
	if (strcmp(tname,"red")==0){
		fromRed = warriorIn;
	}
	else{
		fromBlue = warriorIn;
	}
	if (cityNo!=0 && cityNo!=N+1)
		printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n", hour,tname, warriorIn->getType(), warriorIn->getNo(), cityNo, warriorIn->getElement(), warriorIn->getForce());
}
void City::fight(){
	if (fromRed && !fromBlue){
		if (fromRed->getElement() <= 0)
			fromRed = NULL;
		return;
	}
	else if (!fromRed && fromBlue){
		if (fromBlue->getElement() <= 0)
			fromBlue = NULL;
		return;
	}
	if (fromRed && fromBlue){ 
		if (fromRed->getElement() <= 0 && fromBlue->getElement() <= 0){
			fromRed = NULL;          
			fromBlue = NULL;
			redwin = 0;
			bluewin = 0;
			return;
		}
		else if (fromRed->getElement() <= 0){ 
			fromBlue->fakeAttack(fromRed);
			if (++bluewin == 2)
				raiseFlag("blue");
			return;
		}
		else if (fromBlue->getElement() <= 0){
			fromRed->fakeAttack(fromBlue);
			if (++redwin == 2)
				raiseFlag("red");
			return;
		}
		if (flag && (strcmp(flag, "red")== 0) || cityNo % 2) 
			fromRed->attack(fromBlue);
		else	
			fromBlue->attack(fromRed);
	}
	if (fromRed && !fromBlue ){ 
		if (++redwin == 2)
			raiseFlag("red");
	}
	else if (fromBlue && !fromRed){ 
		if (++bluewin == 2)
			raiseFlag("blue");
	}
	else{  
		redwin = 0;
		bluewin = 0;
	}
}
void City::raiseFlag(char *color){
	flag = color;
	printf("%03d:40 %s flag raised in city %d\n", hour, flag, cityNo);
	redwin = 0;
	bluewin = 0;
}
void City::getCityElement(){
	if (fromRed && !fromBlue && element>0){
		fromRed->getCommander().addLife(element);
		printf("%03d:%02d red %s %d earned %d elements for his headquarter\n", hour,minute, fromRed->getType(),fromRed->getNo(),element);
		element = 0;
	}
	else if (fromBlue && !fromRed && element>0){
		fromBlue->getCommander().addLife(element);
		printf("%03d:%02d blue %s %d earned %d elements for his headquarter\n", hour,minute, fromBlue->getType(), fromBlue->getNo(), element);
		element = 0;
	}
}
int City::getCityNo(){ return cityNo; }
void City::removeWarrior(Warrior *deadwarrior){
	if (strcmp(deadwarrior->getCommander().getName(), "red") == 0)
		fromRed = NULL;
	else
		fromBlue = NULL;
}
void City::useBomb(){
	if (fromRed->getElement() > 0 && fromBlue->getElement() > 0)
	{ 
		if ((fromRed->hasBomb() && fromRed->useBomb())||(fromBlue->hasBomb() && fromBlue->useBomb()))
		{
			removeWarrior(fromRed);
			removeWarrior(fromBlue);
		}
	}
}




CityList::CityList(int totalCity) :totalCityNo(totalCity){
	init();
	for (int i = 1; i <= N; i++)
		Blue->insertAsWest(i);
}
void CityList::LionRunAway(){
	City *t = Red; 
	while (t!= NULL){ 
		if (t->fromRed && strcmp(t->fromRed->getType(), "lion") == 0)
			if (t->fromRed->runaway())
				t->fromRed=NULL;
		if (t->fromBlue && strcmp(t->fromBlue->getType() , "lion") == 0)
			if (t->fromBlue->runaway())
				t->fromBlue=NULL;
		t = t->east;
	}
}
bool CityList::PrintMarch(){
	int tag=March();
	City *t = Red;
	if (tag == 1){	
		printf("%03d:10 blue %s %d marched to red headquater with %d elements and force %d\n", hour,t->fromBlue->getType(), t->fromBlue->getNo(), t->fromBlue->getElement(), t->fromBlue->getForce());
		printf("%03d:10 red headquater was taken\n",hour);
		return true;
	}
	while (t!= Blue){
		if (t->fromRed)
			printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n", hour, t->fromRed->getType(), t->fromRed->getNo(), t->getCityNo(), t->fromRed->getElement(), t->fromRed->getForce());
		if (t->fromBlue)
			printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n", hour, t->fromBlue->getType(), t->fromBlue->getNo(), t->getCityNo(), t->fromBlue->getElement(), t->fromBlue->getForce());
		t = t->east;
	}
	if (t->fromRed)
		printf("%03d:10 red %s %d marched to blue headquater with %d elements and force %d\n", hour, t->fromRed->getType(), t->fromRed->getNo(), t->fromRed->getElement(), t->fromRed->getForce());
	if (tag==2){  
		printf("%03d:10 blue headquater was taken\n", hour);
		return true;
	}		
	return false;
}
int CityList::March(){
	City *t = Red;
	while (t->east != NULL){
		if (t->east->fromBlue)
			if (t->east->fromBlue->march())
				return 1;	
		t = t->east;
	}
	t = Blue;
	while (t->west != NULL){
		if (t->west->fromRed)
			if (t->west->fromRed->march())
				return 2; 
		t = t->west;
	}
	return 0;	
}

void CityList::SendArrow(){
	City *t = Red;
	while (t->east != NULL){
		if (t->fromRed)
			t->fromRed->sendArrow();
		if (t->fromBlue)
			t->fromBlue->sendArrow();
		t = t->east;
	}
}
void CityList::UseBomb(){
	City *t = Red->east;
	while (t->east != NULL){
		if (t->fromRed && t->fromBlue){
			t->useBomb();
		}
		t = t->east;
	}
}
void CityList::Fight(){
	City *t = Red->east;
	while (t!=Blue){
		t->fight();
		t = t->east;
	}
}
void CityList::WarriorReport(){
	City *t = Red;
	while (t->east != NULL){
		if (t->fromRed){
			t->fromRed->reportWeaponUsage();
		}
		if (t->fromBlue){
			t->fromBlue->reportWeaponUsage();
		}
		t = t->east;
	}
}
City * CityList::getCity(const char *name){
	if (strcmp(name, "red")==0)
		return Red;
	else
		return Blue;
}
void CityList::ProduceElement(){
	City *t = Red->east;
	while (t!=Blue){
		t->addElement();
		t = t->east;
	}
}
void CityList::getElement(){
	City *t = Red->east;
	while (t != Blue){
		t->getCityElement();
		t = t->east;
	}
}

Warrior::Warrior(Commander *c, CityList *cl, int noIn, int elementIn, int forceIn, char *typeIn) 
	:commander(c), no(noIn), element(elementIn), force(forceIn), type(typeIn), taskCompleted(false) {
	inCity = cl->getCity(c->getName());
	weapon[0]= new Sword(0);
	weapon[1] = new Bomb(0);
	weapon[2] = new Arrow(0);
}
void Warrior::sendArrow(){
	if (weapon[2].getForce()) {
		if (strcmp(commander->getName(), "red") == 0){	
			if (inCity->east!=NULL && inCity->east->east!=NULL && inCity->east->fromBlue != NULL){		
				weapon[2].setForce(weapon[2].getForce() - 1); 
				if (inCity->east->fromBlue->decreseElement(R) <= 0) 
					printf("%03d:35 red %s %d shot and killed blue %s %d\n", hour, type, no, inCity->east->fromBlue->type, inCity->east->fromBlue->no);
				else
					printf("%03d:35 red %s %d shot\n", hour, type, no);
			}
		}
		else{		
			if (inCity->west!=NULL && inCity->west->west!=NULL && inCity->west->fromRed != NULL){
				weapon[2].setForce(weapon[2].getForce() - 1);
				if (inCity->west->fromRed->decreseElement(R) <= 0){
					printf("%03d:35 blue %s %d shot and killed red %s %d\n", hour, type, no, inCity->west->fromRed->type, inCity->west->fromRed->no);
				}else
					printf("%03d:35 blue %s %d shot\n", hour, type, no);
			}

		}
	}
}
bool Warrior::hasBomb(){
	if (weapon[1].getForce())
		return true;
	return false;
}
bool Warrior::useBomb(){
	if (useBombjudgement()){

		if (strcmp(commander->getName(), "red") == 0){
			printf("%03d:38 red %s %d used a bomb and killed blue %s %d\n", hour, type, no, inCity->fromBlue->type, inCity->fromBlue->no);
		}
		else{
			printf("%03d:38 blue %s %d used a bomb and killed red %s %d\n", hour, type, no, inCity->fromRed->type, inCity->fromRed->no);
		}
		return true;
	}
	return false;
}
bool Warrior::useBombjudgement(){
		if (strcmp(commander->getName(), "red") == 0){ 
				if ((inCity->flag &&(inCity->flag , "red")==0 ) || inCity->cityNo % 2  ){ 
					if (inCity->fromBlue->getElement() - force - weapon[0].getForce() > 0){ 
						if (getElement() - inCity->fromBlue->getForce() / 2 - inCity->fromBlue->weapon[0].getForce() <= 0){	//红方受反击后死亡 
							return true; 
						}
					}
				}
				else{	
					if (getElement() - inCity->fromBlue->getForce() - inCity->fromBlue->weapon[0].getForce() <= 0){ //红方受反击后死亡 
						return true;
					}
				}
		}
		else{
				if ((inCity->flag && (inCity->flag, "red") == 0) || inCity->cityNo % 2){
					if (getElement() - inCity->fromRed->getForce() - inCity->fromRed->weapon[0].getForce() <= 0){
						return true;
					}
				}
				else{
					if (inCity->fromRed->getElement() - force - weapon[0].getForce() > 0){
						if (getElement() - inCity->fromRed->getForce() / 2 - inCity->fromRed->weapon[0].getForce() <= 0){
							return true;
						}
					}
				}
		}
}
bool Warrior::march(){
	if (taskCompleted) return false; 
	if (strcmp(type, "iceman") == 0){
		if (strcmp(commander->getName(), "red") == 0){
			if (inCity->getCityNo() % 2 == 1 && inCity->getCityNo() != 0){
				if (element -= 9 <= 0)
					element = 1;
				force += 20;
			}
		}
		else{
			if (inCity->getCityNo() % 2 == N % 2){
				if (element -= 9 <= 0)
					element = 1;
				force += 20;
			}
		}
	}
	if (strcmp(commander->getName(), "red") == 0){
		inCity->fromRed = NULL;
		inCity = inCity->east;
		inCity->fromRed = this;
		if (inCity->east == NULL){	
			blue.addEnemy();
			return blue.isconquered();	
		}
	}
	else{		
		inCity->fromBlue = NULL;
		inCity = inCity->west;
		inCity->fromBlue = this;
		if (inCity->west == NULL){ 
			red.addEnemy(); 
			return red.isconquered(); 
		}
	}
	return false;
}
void Warrior::attack(Warrior *enemy){
	enemy->element -= (force + weapon[0].getForce());
	weapon[0].setForce(weapon[0].getForce() * 0.8);
	printf("%03d:40 %s %s %d attacked %s %s %d in city %d with %d elemtns and force %d\n", hour,commander->getName(), type, no, enemy->commander->getName(), enemy->type, enemy->no, getCity().cityNo, element, force);
	if (enemy->element <= 0){
		printf("%03d:40 %s %s %d was killed in city %d\n", hour, enemy->commander->getName(), enemy->type, enemy->no, getCity().cityNo);
		if (strcmp(type, "dragon") == 0){
			hurray();
		}
		if (strcmp(type, "wolf") == 0){
			acquireWeapon(enemy);
		}
		getBonus();
		if (strcmp(enemy->commander->getName(), "red") == 0){
			inCity->fromRed = NULL;
		}
		else{
			inCity->fromBlue = NULL;
		}
		inCity->getCityElement();
	}
	else{	
		if (strcmp(enemy->commander->getName(), "ninja")){	
			enemy->fightBack(this); 
		}
	}
}
void Warrior::fakeAttack(Warrior *enemy){ 
	if (strcmp(type, "dragon") == 0){
		hurray();
	}
	if (strcmp(type, "wolf") == 0){
		acquireWeapon(enemy);
	}
	getBonus();
	if (strcmp(enemy->commander->getName(), "red") == 0){
		inCity->fromRed = NULL;
	}
	else{
		inCity->fromBlue = NULL;
	}
	inCity->getCityElement();
}
void Warrior::fightBack(Warrior *enemy){
	enemy->element -= (force / 2 + weapon[0].getForce());
	if (enemy->element <= 0){
		printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n", hour, commander->getName(), getType(), getNo(), enemy->commander->getName(), enemy->type, enemy->no, getCity().cityNo);
		printf("%03d:40 %s %s %d was killed in city %d\n",hour, enemy->commander->getName(), enemy->type, enemy->no, getCity().cityNo);
		if (strcmp(type, "dragon") == 0){
			hurray();
		}
		if (strcmp(type, "wolf") == 0){
			acquireWeapon(enemy);
		}
		getBonus();
		if (strcmp(enemy->commander->getName(), "red") == 0){
			inCity->fromRed = NULL;
		}
		else{
			inCity->fromBlue = NULL;
		}
		inCity->getCityElement();
	}
	else{
		printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n", hour, commander->getName(), getType(), getNo(), enemy->commander->getName(), enemy->type, enemy->no, getCity().cityNo);
		if (strcmp(type, "lion") == 0) 
			update();
		if (strcmp(enemy->type, "lion") == 0)
			enemy->update();
	}
}
void Warrior::sendBackElement(int elementIn){
	printf("%03d:40 %s %s %d earned %d elements for his headquarter\n", hour, commander->getName(), type, no, elementIn);
	commander->addLife(elementIn);
}
void Warrior::getBonus(){
	if (commander->getLifeLeft() >= 8){
		element += 8;
		commander->sendBonus();
	}
}
void Warrior::reportWeaponUsage(){
	printf("%03d:55 %s %s %d has ",hour, commander->getName(), type, no);
	if (weapon[2].getForce()){
		printf("arrow(%d)", weapon[2].getForce());
		if (weapon[1].getForce()){
			printf(",bomb");
			if (weapon[0].getForce()){
				printf(",sword(%d)", weapon[0].getForce());
			}
		}
		else{
			if (weapon[0].getForce()){
				printf(",sword(%d)", weapon[0].getForce());
			}
		}
	}
	else{
		if (weapon[1].getForce()){
			printf("bomb");
			if (weapon[0].getForce()){
				printf(",sword(%d)", weapon[0].getForce());
			}
		}
		else{
			if (weapon[0].getForce()){
				printf("sword(%d)", weapon[0].getForce());
			}
			else
				printf("no weapon");
		}
	}
	printf("\n");
}
int Warrior::getWeaponForce(int windex){ return weapon[windex].getForce(); }

Dragon::Dragon(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn) :Warrior(c, cl, noIn, lifeIn, attackIn, "Dragon"){
	switch (noIn % 3){
	case 0:weapon[0].setForce(attackIn*0.2); break;
	case 1:weapon[1].setForce(1); break;
	case 2:weapon[2].setForce(3); break;
	}
	morale = c->getLifeLeft() / (double)lifeIn;
	printf("Its morale is %.2f\n", morale);
}
void Dragon::hurray(){
	if (morale>0.8) 
		printf("%03d:40 %s dragon %d yelled in city %d\n", hour, commander->getName(), getNo(), inCity->getCityNo());
}
Ninja::Ninja(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn) :Warrior(c, cl, noIn, lifeIn, attackIn, "ninja"){
	switch (noIn % 3){
	case 0:weapon[0].setForce(attackIn*0.2); weapon[1].setForce(1); break;
	case 1:weapon[1].setForce(1); weapon[2].setForce(R); break;
	case 2:weapon[2].setForce(3); weapon[0].setForce(attackIn*0.2); break;
	}
}
Iceman::Iceman(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn):Warrior(c, cl, noIn, lifeIn, attackIn, "iceman"){

	switch (noIn % 3){
	case 0:weapon[0].setForce(attackIn*0.2); break; 
	case 1:weapon[1].setForce(1); break;
	case 2:weapon[2].setForce(3); break;
	}
}

Lion::Lion(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn) :Warrior(c, cl, noIn, lifeIn, attackIn, "lion"){
	loyalty = c->getLifeLeft(); 
	printf("It's loyalty is %d\n", loyalty);
}
bool Lion::runaway(){
	if (loyalty <= 0){
		printf("%03d:05 %s lion %d ran away\n",hour, getCommander().getName(), getNo());
		return true;
	}
	return false;
}
Wolf::Wolf(Commander *c, CityList *cl, int noIn, int lifeIn, int attackIn) : Warrior(c, cl, noIn, lifeIn, attackIn, "wolf"){}
void Wolf::acquireWeapon(Warrior *enemy){ 
	for (int i = 0; i < 3; i++){ 
		if (!weapon[i].getForce()){
			weapon[i].setForce(enemy->getWeaponForce(i));
		}
	}
}

void Commander::setCityList(CityList *cl){ clist = cl; }
void Commander::setForce(int f0, int f1, int f2, int f3, int f4){
	force[0] = f0;
	force[1] = f1;
	force[2] = f2;
	force[3] = f3;
	force[4] = f4;
}
void Commander::setTypes(char **typesIn){
	for (int i = 0; i < 5; i++) {
		types[i] = new char[strlen(typesIn[i]) + 1];
		strcpy(types[i], typesIn[i]);
	}
}
void Commander::setLife(int l0, int l1, int l2, int l3, int l4){
	life[0] = l0;
	life[1] = l1;
	life[2] = l2;
	life[3] = l3;
	life[4] = l4;
}
void Commander::setName(char *color){
	name = new char[strlen(color) + 1];
	strcpy(name, color);
	if (strcmp(color, "red") == 0)
		cityNo = 0;
	else
		cityNo = N + 1;
}
void Commander::makeWarrior(){
	int typeindex = currentType % 5;
	if (lifeleft >= life[typeindex]){
		lifeleft -= life[typeindex];
		count[typeindex]++;
		printf("%03d:00 %s %s %d born\n", 
			hour, name, types[typeindex], no + 1);
		Warrior *wr;
		if (strcmp(types[typeindex], "dragon")==0){
			wr = new Dragon(this, clist, no + 1, life[typeindex], force[typeindex]);
		}
		else if (strcmp(types[typeindex], "ninja") == 0){
			wr = new Ninja(this, clist, no + 1, life[typeindex], force[typeindex]);
		}
		else if (strcmp(types[typeindex] , "iceman") == 0){
			wr = new Iceman(this, clist, no + 1, life[typeindex], force[typeindex]);
		}
		else if (strcmp(types[typeindex] , "lion") == 0){
			wr = new Lion(this, clist, no + 1, life[typeindex], force[typeindex]);
		}
		else{
			wr = new Wolf(this, clist, no + 1, life[typeindex], force[typeindex]);
		}
		clist->getCity(name)->warriorArrived(wr);
		currentType++;
		no++;
	}
}
void Commander::resetCommander(){
	 no = 0; 
	 currentType = 0; 
	 clist = NULL;
	 east = NULL;
	 west = NULL;
	 enemyNo = 0;
	 lifeleft = 0;

	for (int i = 0; i < 5; i++)
		count[i] = 0;
}
bool Commander::isconquered(){
	if (enemyNo == 2){
		return true;
	}
	return false;
}


bool event(CityList *cl, int timeIn){
	minute = timeIn % 60;
	hour = timeIn / 60;
	switch (minute){
	case 0:
		red.makeWarrior();
		blue.makeWarrior();
		break;
	case 5:
		cl->LionRunAway(); break;
	case 10: 
		if(cl->PrintMarch())
			return true; 
		break;
	case 20: 
		cl->ProduceElement(); break;
	case 30:
		cl->getElement(); break;
	case 35: 
		cl->SendArrow(); break;
	case 38: 
		cl->UseBomb(); break;
	case 40: 
		cl->Fight(); break;
	case 50: 
		red.reportLifeLeft();
		blue.reportLifeLeft();
		break;
	case 55: 
		cl->WarriorReport();
		break;
	}
	return false;
}

int main()
{
	
	int testNo;
	scanf("%d", &testNo);
	char *redTypes[5] = { "iceman", "lion", "wolf", "ninja", "dragon" };
	char *blueTypes[5] = { "lion", "dragon", "ninja", "iceman", "wolf" };
	int *tlife = new int[testNo], *dlife = new int[testNo], *nlife = new int[testNo], *ilife = new int[testNo], *llife = new int[testNo], *wlife = new int[testNo];
	int *m = new int[testNo], *n = new int[testNo], *r = new int[testNo], *k = new int[testNo], *t = new int[testNo];
	int *dforce = new int[testNo], *nforce = new int[testNo], *iforce = new int[testNo], *lforce = new int[testNo], *wforce = new int[testNo];
	for (int i = 0; i < testNo; i++){
		scanf("%d %d %d %d %d", &m[i], &n[i], &r[i], &k[i], &t[i]);
		scanf("%d %d %d %d %d", &dlife[i], &nlife[i], &ilife[i], &llife[i], &wlife[i]);
		scanf("%d %d %d %d %d", &dforce[i], &nforce[i], &iforce[i], &lforce[i], &wforce[i]);
	}

	red.setTypes(redTypes);
	blue.setTypes(blueTypes);
	red.setName("red");
	blue.setName("blue");
	

	for (int caseNo = 0; caseNo < testNo; caseNo++){
		M = m[caseNo]; N = n[caseNo]; R = r[caseNo]; K = k[caseNo]; T = t[caseNo];
		CityList *citylist;
		red.resetCommander();
		blue.resetCommander();
		printf("Case:%d\n", caseNo + 1);
		red.setTotalLife(M);
		blue.setTotalLife(M);
		red.setLife(ilife[caseNo], llife[caseNo], wlife[caseNo], nlife[caseNo], dlife[caseNo]);
		red.setForce(iforce[caseNo], lforce[caseNo], wforce[caseNo], nforce[caseNo], dforce[caseNo]);
		blue.setLife(llife[caseNo], dlife[caseNo], nlife[caseNo], ilife[caseNo], wlife[caseNo]);
		blue.setForce(lforce[caseNo], dforce[caseNo], nforce[caseNo], iforce[caseNo], wforce[caseNo]);
		citylist = new CityList(N);
		red.setCityList(citylist);
		blue.setCityList(citylist);
		for (int time = 0; time < T; time++){
			if (event(citylist,time))
				break;	
		}
		delete[] citylist;
	}
	delete[] tlife;
	delete[] dlife;
	delete[] nlife;
	delete[] llife;
	delete[] wlife;
	return 0;
}
