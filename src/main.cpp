#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(Plankton, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto planktonButton = CCMenuItemSpriteExtra::create(
			CCSprite::create("AHP_PlanktonButton.png"_spr),
			this,
			menu_selector(Plankton::onPalnkton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(planktonButton);

		planktonButton->setID("plankton-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onPalnkton(CCObject*) {
		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto plankton = CCSprite::create("AHP_Plankton.png"_spr);
		auto text = CCLabelBMFont::create("All Hail Plankton", "bigFont.fnt");
		plankton->setPositionX(winSize.width / 2);
		text->setPositionX(winSize.width / 2);

		plankton->setPositionY(winSize.height / 2);
		text->setPositionY(winSize.height / 1.5);

		this->addChild(plankton);
		this->addChild(text);

		FMODAudioEngine::sharedEngine()->playEffect("AllHailPlankton.mp3"_spr);

		plankton->runAction(
				CCSequence::create(
					CCDelayTime::create(2.0f),
					CCFadeOut::create(2.f),
					CCCallFunc::create(plankton, callfunc_selector(CCLayer::removeFromParent)),
					nullptr
				)
			);

		text->runAction(
				CCSequence::create(
					CCDelayTime::create(2.0f),
					CCFadeOut::create(2.f),
					CCCallFunc::create(text, callfunc_selector(CCLayer::removeFromParent)),
					nullptr
				)
			);
	}
};
