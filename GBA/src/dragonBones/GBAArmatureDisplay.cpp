/** @file GBAArmatureDisplay.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "GBAArmatureDisplay.h"

#include "GBAArmatureProxy.h"

DRAGONBONES_NAMESPACE_BEGIN

GBAArmatureDisplay::GBAArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName, const std::string& skinName, const std::string& textureAtlasName)
{
	_proxy = GBAFactory::get()->buildArmatureDisplay(armatureName, dragonBonesName, skinName, textureAtlasName);
}

GBAArmatureDisplay::~GBAArmatureDisplay()
{
	_proxy->dispose(true);
	_proxy = nullptr;
}

Armature* GBAArmatureDisplay::getArmature() const
{
	if (_proxy)
		return _proxy->getArmature();

	return nullptr;
}

Animation* GBAArmatureDisplay::getAnimation() const
{
	if (_proxy)
		return _proxy->getAnimation();

	return nullptr;
}

GBAEventDispatcher* GBAArmatureDisplay::getEventDispatcher()
{
	if (_proxy)
		return _proxy->getEventDispatcher();

	return nullptr;
}

GBAArmatureProxy* GBAArmatureDisplay::getArmatureProxy() const
{
	return _proxy;
}

gba::IntRect GBAArmatureDisplay::getBoundingBox()
{
	if (_proxy)
		return _proxy->getBoundingBox();

	return gba::IntRect();
}

void GBAArmatureDisplay::draw() const
{
	if (_proxy)
		_proxy->draw(_pos);
}

DRAGONBONES_NAMESPACE_END
