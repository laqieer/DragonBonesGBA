/** @file GBATextureData.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include <memory>

#include <dragonBones/DragonBonesHeaders.h>

#include <Sprite.hpp>

DRAGONBONES_NAMESPACE_BEGIN

class GBATextureData : public TextureData
{
	BIND_CLASS_TYPE_B(GBATextureData);

public:
	gba::Texture*			texture;

public:
	GBATextureData()
	{
		_onClear();
	}

	virtual ~GBATextureData()
	{
		_onClear();
	}

	void _onClear() override
	{
		texture = nullptr;

		TextureData::_onClear();
	}

	void setTexture(gba::Texture *value)
	{
		auto size = value->size;

		region.x = 0.f;
		region.y = 0.f;
		region.width = static_cast<float>(size.x);
		region.height = static_cast<float>(size.y);

		texture = value;
	}
};

DRAGONBONES_NAMESPACE_END
