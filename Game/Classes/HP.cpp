#include "HP.h"

/////////////////////////////////////////////////////////
#define HERO 0
#define OPP_HERO 1
#define BING 2
#define OPP_BING 3
/////////////////////////////////////////////////////////

int HP::getMax() {
	return this->max_HP;
}

int HP::getCur() {
	return this->cur_Hp;
}

void HP::changeCur(int delta) {
	int changedHP = cur_Hp + delta;
	if (changedHP <= 0){cur_Hp = 0;}
	else if (changedHP > max_HP) cur_Hp = max_HP;
	else cur_Hp = changedHP;
	return;
}

void HP::changeMax(int delta) {
	int cdmax = max_HP + delta;
	if (cdmax > 0) {
		max_HP = cdmax;	for (int i = max_HP / 1000; i; i--) {
			Hp1000 = Sprite::create("HP/1000hp.png");
			if (Hp1000 == NULL) return;
			Hp1000->setPosition(bloodrect->getPositionX() + i * (1000.0 / max_HP)*bloodrect->getContentSize().width,
				bloodrect->getPositionY() + bloodrect->getContentSize().height - Hp1000->getContentSize().height);
		}
	}
	else CCLOG("MaxBloodError");
	return;
}


void HP::changeVel(int delta) {
	velocity += delta;
	return;
}

void HP::initial(Vec2 position,Size size,bool enemyOrAlly)
{
	//位置信息要重新修改，考虑实际图片像素问题
	bloodrect = Sprite::create("HP/bloodrect.png");
	bloodrect->setPosition(position.x, position.y + 10);
	setScaleX(((float)(size.width)) / (size.width));
	setScaleY(10.0 / bloodrect->getContentSize().height);
	this->addChild(bloodrect, 0);
	
	/*if (enemyOrAlly)
		curBlood = Sprite::create("HP/RedBlood.png");
	else*/
		curBlood = Sprite::create("HP/GreenBlood.png");

	curBlood->setPosition(bloodrect->getPositionX(), bloodrect->getPositionY());
	curBlood->setScaleY((float)bloodrect->getContentSize().height / curBlood->getContentSize().height);
	curBlood->setScaleX((float)bloodrect->getContentSize().width / curBlood->getContentSize().width);
	this->addChild(curBlood, 1);

	for (int i = max_HP / 1000; i; i--) {
		Hp1000 = Sprite::create("HP/1000hp.png");
		if (Hp1000 == NULL) return;
		Hp1000->setPosition(bloodrect->getPositionX() + (i * (1000.0 / max_HP) - 0.5) * bloodrect->getContentSize().width,
			bloodrect->getPositionY() + bloodrect->getContentSize().height - Hp1000->getContentSize().height);

		this->addChild(Hp1000, 2);
	}
	emptyBlood = Sprite::create("HP/emptyrect.png");
	emptyBlood->setPosition(bloodrect->getPositionX() + bloodrect->getContentSize().width - emptyBlood->getContentSize().width
		, bloodrect->getPositionY());
	emptyBlood->setScaleX(bloodrect->getContentSize().width/emptyBlood->getContentSize().width);
	this->addChild(emptyBlood, 0);
	return;
}

void HP::fresh() {
	changeCur(velocity);
	curBlood->setScaleX(((float)cur_Hp/max_HP)*(bloodrect->getContentSize().width / curBlood->getContentSize().width));
	return;
}
HP::~HP() {
	//delete(this);
}

