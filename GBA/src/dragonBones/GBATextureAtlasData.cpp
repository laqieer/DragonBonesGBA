/** @file GBATextureAtlasData.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/
#include "GBATextureAtlasData.h"

#include <memory>

#include <Rect.hpp>
#include <Vector2.hpp>

#include "GBATextureData.h"

DRAGONBONES_NAMESPACE_BEGIN

GBATextureAtlasData::GBATextureAtlasData()
{
	_onClear();
}

GBATextureAtlasData::~GBATextureAtlasData()
{
	_onClear();
}

void GBATextureAtlasData::setRenderTexture(gba::Texture* value)
{
	if (_renderTexture == value)
	{
		return;
	}

	_renderTexture = value;

	if (_renderTexture != nullptr)
	{
		for (const auto& pair : textures)
		{
			const auto textureData = static_cast<GBATextureData*>(pair.second);

			if (textureData->texture == nullptr)
			{
				dragonBones::Rectangle region;
				region.x = textureData->region.x;
				region.y = textureData->region.y;
				region.width = textureData->rotated ? textureData->region.height : textureData->region.width;
				region.height = textureData->rotated ? textureData->region.width : textureData->region.height;

				textureData->texture = _renderTexture;
				textureData->region = std::move(region);
			}
		}
	}
}

TextureData* GBATextureAtlasData::createTexture() const
{
	return BaseObject::borrowObject<GBATextureData>();
}

DRAGONBONES_NAMESPACE_END
