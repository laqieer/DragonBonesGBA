/** @file GBAFactory.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include "GBAFactory.h"

#include <fstream>
#include <sstream>
#include <memory>

#include <GBA/Graphics.hpp>

#include "GBASlot.h"
#include "GBATextureData.h"
#include "GBATextureAtlasData.h"
#include "GBAArmatureProxy.h"
#include "GBADisplay.h"
#include "GBAEventDispatcher.h"

DRAGONBONES_NAMESPACE_BEGIN

DragonBones* GBAFactory::_dragonBonesInstance;
GBAFactory* GBAFactory::_factory;

GBAFactory::GBAFactory()
{
	_factory = this;

	if (_dragonBonesInstance == nullptr)
	{
		_soundEventDispatcher = std::make_unique<GBAEventDispatcher>();

		_dragonBonesInstance = new DragonBones(_soundEventDispatcher.get());
	}

	_dragonBones = _dragonBonesInstance;
}

GBAFactory::~GBAFactory()
{
	clear();

	if (_dragonBonesInstance)
	{
		delete _dragonBonesInstance;
	}
}

DragonBonesData* GBAFactory::loadDragonBonesData(const std::string& filePath, const std::string& name)
{
	if (!name.empty())
	{
		const auto existedData = getDragonBonesData(name);

		if (existedData)
			return existedData;
	}

	std::stringstream data;

	std::ifstream json(filePath);

	if (json.bad())
		return nullptr;

	data << json.rdbuf();

	if (data.str().empty())
		return nullptr;

	return parseDragonBonesData(data.str().c_str(), name, 1.0f);
}

TextureAtlasData* GBAFactory::loadTextureAtlasData(const std::string& filePath, sf::Texture* atlasTexture, const std::string& name, float scale)
{
	std::stringstream data;

	std::ifstream json(filePath);

	if (json.bad())
		return nullptr;

	data << json.rdbuf();

	if (data.str().empty())
		return nullptr;

	return static_cast<GBATextureAtlasData*>(BaseFactory::parseTextureAtlasData(data.str().c_str(), atlasTexture, name, scale));
}

GBAArmatureProxy* GBAFactory::buildArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName, const std::string& skinName, const std::string& textureAtlasName) const
{
	const auto armature = buildArmature(armatureName, dragonBonesName, skinName, textureAtlasName);

	if (armature != nullptr)
	{
		_dragonBones->getClock()->add(armature);

		return static_cast<GBAArmatureProxy*>(armature->getDisplay());
	}

	return nullptr;
}

sf::Texture* GBAFactory::getTextureDisplay(const std::string& textureName, const std::string& dragonBonesName) const
{
	const auto textureData = static_cast<GBATextureData*>(_getTextureData(dragonBonesName, textureName));
	if (textureData != nullptr && textureData->texture != nullptr)
	{
		return textureData->texture;
	}

	return nullptr;
}

void GBAFactory::update(float lastUpdate)
{
	_dragonBonesInstance->advanceTime(lastUpdate);
}

TextureAtlasData* GBAFactory::_buildTextureAtlasData(TextureAtlasData* textureAtlasData, void* textureAtlas) const
{
	auto textureAtlasData_ = static_cast<GBATextureAtlasData*>(textureAtlasData);

	if (textureAtlasData != nullptr)
	{
		if (textureAtlas != nullptr)
		{
			textureAtlasData_->setRenderTexture(static_cast<sf::Texture*>(textureAtlas));
		}
		else
		{
			DRAGONBONES_ASSERT(false, "No atlas texture");
		}
	}
	else
	{
		textureAtlasData_ = BaseObject::borrowObject<GBATextureAtlasData>();
	}

	return textureAtlasData_;
}

Armature* GBAFactory::_buildArmature(const BuildArmaturePackage& dataPackage) const
{
	const auto armature = BaseObject::borrowObject<Armature>();
	const auto armatureDisplay = new GBAArmatureProxy();

	armature->init(dataPackage.armature, armatureDisplay, armatureDisplay, _dragonBones);

	return armature;
}

Slot* GBAFactory::_buildSlot(const BuildArmaturePackage& dataPackage, const SlotData* slotData, Armature* armature) const
{
	auto slot = BaseObject::borrowObject<GBASlot>();
	auto wrapperDisplay = new GBADisplay();

	slot->init(slotData, armature, wrapperDisplay, wrapperDisplay);

	return slot;
}

DRAGONBONES_NAMESPACE_END
