/** @file GBAFactory.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include <string>
#include <vector>
#include <memory>

#include <dragonBones/DragonBonesHeaders.h>

#include <Texture.hpp>

#include "GBAEventDispatcher.h"

DRAGONBONES_NAMESPACE_BEGIN

class GBAArmatureProxy;
class GBATextureData;

class GBAFactory : public BaseFactory
{
protected:
	static DragonBones*											_dragonBonesInstance;
	static GBAFactory*											_factory;

	std::unique_ptr<GBAEventDispatcher>						_soundEventDispatcher;

public:
	GBAFactory();
	~GBAFactory();

public:
	DragonBonesData* loadDragonBonesData(const std::string& filePath, const std::string& name = "");
	TextureAtlasData* loadTextureAtlasData(const std::string& filePath, gba::Texture* atlasTexture, const std::string& name = "", float scale = 1.0f);
	GBAArmatureProxy* buildArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName = "", const std::string& skinName = "", const std::string& textureAtlasName = "") const;
	gba::Texture* getTextureDisplay(const std::string& textureName, const std::string& dragonBonesName = "") const;

	void addSoundEventListener(const std::function<void(EventObject*)>& listener)
	{
		//_soundEventDispatcher->addDBEventListener(EventObject::SOUND_EVENT, listener);
	}

	void update(float lastUpdate);

	static GBAFactory* get() { return _factory; }

protected:
	TextureAtlasData* _buildTextureAtlasData(TextureAtlasData* textureAtlasData, void* textureAtlas) const override;
	Armature* _buildArmature(const BuildArmaturePackage& dataPackage) const override;
	Slot* _buildSlot(const BuildArmaturePackage& dataPackage, const SlotData* slotData, Armature* armature) const override;
};

DRAGONBONES_NAMESPACE_END
