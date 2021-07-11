#pragma once

/** @file GBAArmatureProxy.hp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include <vector>

#include <dragonBones/DragonBonesHeaders.h>
#include <Rect.hpp>

#include "GBANode.h"
#include "GBAFactory.h"
#include "GBAEventDispatcher.h"

DRAGONBONES_NAMESPACE_BEGIN

class GBADisplay;
class GBANode;

class GBAArmatureProxy : public GBANode, public IArmatureProxy
{
	friend GBAFactory;

protected:
	Armature*				_armature = nullptr;
	GBAEventDispatcher		_dispatcher;

	gba::Vector2f			_position;

	std::vector<GBANode*>	_nodes;

protected:
	GBAArmatureProxy() = default;
	~GBAArmatureProxy() = default;

public:
	bool hasDBEventListener(const std::string& type) const override { return true; }
	void addDBEventListener(const std::string& type, const std::function<void(EventObject*)>& listener) override;
	void removeDBEventListener(const std::string& type, const std::function<void(EventObject*)>& listener) override;
	void dispatchDBEvent(const std::string& type, EventObject* value) override;

	GBAEventDispatcher* getEventDispatcher() { return &_dispatcher; }

	void addNode(GBANode* node);
	void removeNode(GBANode* node);
	void sortNodes();

	void dbInit(Armature* armature) override;
	void dbClear() override;
	void dbUpdate() override;

	void dispose(bool disposeProxy) override;

	Armature* getArmature() const override { return _armature; }
	Animation* getAnimation() const override { return _armature->getAnimation(); }

	void setVisible(bool visible) override;
	//void setColor(const gba::Color& color) override;

	gba::IntRect getBoundingBox() const override;

//protected:
	void draw(gba::Vector2f position) const;

};

DRAGONBONES_NAMESPACE_END
