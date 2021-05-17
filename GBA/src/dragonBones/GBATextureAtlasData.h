/** @file GBATextureAtlasData.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include <dragonBones/DragonBonesHeaders.h>
#include <GBA/Graphics/Texture.hpp>

DRAGONBONES_NAMESPACE_BEGIN

class GBATextureAtlasData : public TextureAtlasData
{
	BIND_CLASS_TYPE_B(GBATextureAtlasData);

private:
	sf::Texture* _renderTexture;

public:
	GBATextureAtlasData();
	~GBATextureAtlasData();

	virtual TextureData* createTexture() const override;

	sf::Texture* getRenderTexture() const { return _renderTexture; }

	void setRenderTexture(sf::Texture* value);
};

DRAGONBONES_NAMESPACE_END
