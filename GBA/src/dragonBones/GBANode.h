/** @file GBANode.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include <dragonBones/DragonBonesHeaders.h>

#include <Rect.hpp>

DRAGONBONES_NAMESPACE_BEGIN

class GBANode
{
protected:
	Transform _transform;

	bool _visible = true;

	int _zOffset = 0;

public:
	GBANode() = default;
	virtual ~GBANode() = default;

	void setZOffset(int zOffset) { _zOffset = zOffset; }
	int getZOffset() const { return _zOffset; }

	void setMatrix(const Transform& globalTransform, const gba::Vector2f& offset, float scaleX, float scaleY)
	{
        //_transform = Transform(offset.x, offset.y, 0.0f, 0.0f, scaleX, scaleY);
        _transform = Transform();
        _transform.x = offset.x;
        _transform.y = offset.y;
        _transform.scaleX = scaleX;
        _transform.scaleY = scaleY;

        _transform.add(globalTransform);
	}

	virtual void setVisible(bool visible) { _visible = visible; }

	//virtual void setColor(const gba::Color& color) = 0;

	virtual gba::IntRect getBoundingBox() const = 0;
};

DRAGONBONES_NAMESPACE_END
