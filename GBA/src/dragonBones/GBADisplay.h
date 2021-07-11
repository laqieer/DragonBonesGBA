/** @file GBADisplay.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @author Patryk (PsychoX) Ludwikowski <psychoxivi@gmail.com>
 ** @license MIT License 
 **/

#pragma once

#include <vector>

#include <Rect.hpp>
#include <Texture.hpp>
#include <Sprite.hpp>

#include <dragonBones/DragonBonesHeaders.h>

#include "GBANode.h"

DRAGONBONES_NAMESPACE_BEGIN

class GBADisplay : public GBANode
{
public:
    gba::Texture* texture = nullptr;
    gba::Sprite* sprite = nullptr;

protected:

public:
	GBADisplay() = default;
	~GBADisplay() = default;

public:
	//void setColor(const gba::Color& color) override
	//{
	//}

	gba::IntRect getBoundingBox() const override
	{
  		return *(sprite->rect);
	}

//protected:
	void draw(Transform *transform, int id) const
	{
        Transform trans(*transform);
        trans.add(_transform);

        //sprite = gba::Sprite::sprites[id];

		if (_visible)
		{
            //sprite->draw(&trans);
            gba::Sprite::sprites[id]->draw(&trans);
		}
	}
};

DRAGONBONES_NAMESPACE_END
