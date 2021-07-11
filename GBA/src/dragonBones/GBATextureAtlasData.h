/** @file GBATextureAtlasData.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include <dragonBones/DragonBonesHeaders.h>
#include <Texture.hpp>

DRAGONBONES_NAMESPACE_BEGIN

class GBATextureAtlasData : public TextureAtlasData
{
	BIND_CLASS_TYPE_B(GBATextureAtlasData);

private:
	gba::Texture* _renderTexture;

public:
	GBATextureAtlasData();
	~GBATextureAtlasData();

	virtual TextureData* createTexture() const override;

	gba::Texture* getRenderTexture() const { return _renderTexture; }

	void setRenderTexture(gba::Texture* value);
};

DRAGONBONES_NAMESPACE_END
