/** @file GBANode.h
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#pragma once

#include <dragonBones/DragonBonesHeaders.h>

#include <GBA/Graphics/Drawable.hpp>
#include <GBA/Graphics/Color.hpp>
#include <GBA/Graphics/Rect.hpp>

DRAGONBONES_NAMESPACE_BEGIN

class GBANode : public sf::Drawable
{
protected:
	sf::Transform _transform;

	bool _visible = true;

	int _zOffset = 0;

public:
	GBANode() = default;
	virtual ~GBANode() = default;

	void setZOffset(int zOffset) { _zOffset = zOffset; }
	int getZOffset() const { return _zOffset; }

	void setMatrix(const Matrix& matrix, const sf::Vector2f& offset, float scaleX, float scaleY)
	{
		_transform = sf::Transform(
			matrix.a * scaleX, matrix.c * scaleY, offset.x,
			matrix.b * scaleX, matrix.d * scaleY, offset.y,
			0.f, 0.f, 1.f
		);
	}

	virtual void setVisible(bool visible) { _visible = visible; }

	virtual void setColor(const sf::Color& color) = 0;

	virtual sf::FloatRect getBoundingBox() const = 0;
};

DRAGONBONES_NAMESPACE_END
