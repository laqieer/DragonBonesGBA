#pragma once

/** @file GBAArmatureDisplay.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include <Rect.hpp>

#include <dragonBones/DragonBonesHeaders.h>

DRAGONBONES_NAMESPACE_BEGIN

class GBAArmatureProxy;
class GBAEventDispatcher;

class GBAArmatureDisplay
{
private:
	GBAArmatureProxy* _proxy = nullptr;

	gba::Vector2f _pos;

public:
	GBAArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName = "", const std::string& skinName = "", const std::string& textureAtlasName = "");
	~GBAArmatureDisplay();

	void setPosition(const gba::Vector2f& pos) { _pos = pos; }
	const gba::Vector2f& getPosition() { return _pos; }

	Armature* getArmature() const;
	Animation* getAnimation() const;

	GBAEventDispatcher* getEventDispatcher();

	GBAArmatureProxy* getArmatureProxy() const;

	gba::IntRect getBoundingBox();

//protected:
	void draw() const;
};

DRAGONBONES_NAMESPACE_END
