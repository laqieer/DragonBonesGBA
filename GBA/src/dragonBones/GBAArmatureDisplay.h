#pragma once

/** @file GBAArmatureDisplay.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include <GBA/Graphics/Rect.hpp>
#include <GBA/Graphics/Drawable.hpp>

#include <dragonBones/DragonBonesHeaders.h>

DRAGONBONES_NAMESPACE_BEGIN

class GBAArmatureProxy;
class GBAEventDispatcher;

class GBAArmatureDisplay : public sf::Drawable
{
private:
	GBAArmatureProxy* _proxy = nullptr;

	sf::Vector2f _pos;

public:
	GBAArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName = "", const std::string& skinName = "", const std::string& textureAtlasName = "");
	~GBAArmatureDisplay();

	void setPosition(const sf::Vector2f& pos) { _pos = pos; }
	const sf::Vector2f& getPosition() { return _pos; }

	Armature* getArmature() const;
	Animation* getAnimation() const;

	GBAEventDispatcher* getEventDispatcher();

	GBAArmatureProxy* getArmatureProxy() const;

	sf::FloatRect getBoundingBox();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};

DRAGONBONES_NAMESPACE_END
