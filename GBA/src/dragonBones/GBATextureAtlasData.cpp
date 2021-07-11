/** @file GBATextureAtlasData.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/
#include "GBATextureAtlasData.h"

#include <memory>

#include <Rect.hpp>
#include <Vector2.hpp>

#include "GBATextureData.h"

#include <tonc_types.h>
#include "tonc_mgba.h"

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
    mgba_printf(LOG_INFO, "setRenderTexture: texture: 0x%x", value);

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

            mgba_printf(LOG_INFO, "textureData: 0x%x", textureData);

			if (textureData->texture == nullptr)
			{
				dragonBones::Rectangle region;
				region.x = textureData->region.x;
				region.y = textureData->region.y;
				region.width = textureData->rotated ? textureData->region.height : textureData->region.width;
				region.height = textureData->rotated ? textureData->region.width : textureData->region.height;

				textureData->texture = _renderTexture;
				textureData->region = std::move(region);

                mgba_printf(LOG_INFO, "textureData->region: x: %f, y: %f, w: %f, h: %f", textureData->region.x, textureData->region.y, textureData->region.width, textureData->region.height);

                gba::IntRect *rect = new gba::IntRect((int)region.x, (int)region.y, (int)region.width, (int)region.height);
                gba::Sprite *sprite = new gba::Sprite(value, rect);
                sprite->draw(new dragonBones::Transform());
			}
		}
	}
}

TextureData* GBATextureAtlasData::createTexture() const
{
	return BaseObject::borrowObject<GBATextureData>();
}

DRAGONBONES_NAMESPACE_END
