/** @file GBASlot.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @author Patryk (PsychoX) Ludwikowski <psychoxivi@gmail.com>
 ** @license MIT License
 **/

#include "GBASlot.h"

#include "GBAArmatureProxy.h"
#include "GBADisplay.h"
#include "GBATextureAtlasData.h"
#include "GBATextureData.h"

#include <tonc_types.h>
#include <tonc_mgba.h>

DRAGONBONES_NAMESPACE_BEGIN

void GBASlot::_updateVisible()
{
	_renderDisplay->setVisible(_parent->getVisible());
}

void GBASlot::_updateBlendMode()
{
}

void GBASlot::_updateColor()
{
}

void GBASlot::_initDisplay(void* value, bool isRetain)
{
}

void GBASlot::_disposeDisplay(void* value, bool isRelease)
{
	if (!isRelease && value)
	{
		delete static_cast<GBANode*>(value);
	}
}

void GBASlot::_onUpdateDisplay()
{
	_renderDisplay = static_cast<GBANode*>(_display != nullptr ? _display : _rawDisplay);
	_renderDisplay->setZOffset(_slotData->zOrder);
    mgba_printf(LOG_INFO, "_onUpdateDisplay: _renderDisplay: 0x%x", _renderDisplay);
}

void GBASlot::_addDisplay()
{
	auto arm = static_cast<GBAArmatureProxy*>(_armature->getDisplay());
	arm->addNode(_renderDisplay);
}

void GBASlot::_replaceDisplay(void* value, bool isArmatureDisplay)
{
	auto prevDisplay = static_cast<GBANode*>(value);

	auto arm = static_cast<GBAArmatureProxy*>(_armature->getDisplay());

	_renderDisplay->setZOffset(prevDisplay->getZOffset());

	arm->removeNode(prevDisplay);
	arm->addNode(_renderDisplay);

	arm->sortNodes();

	_textureScale = 1.f;

}

void GBASlot::_removeDisplay()
{
	auto arm = static_cast<GBAArmatureProxy*>(_armature->getDisplay());
	arm->removeNode(static_cast<GBANode*>(_renderDisplay));
}

void GBASlot::_updateZOrder()
{
	_renderDisplay->setZOffset(_slotData->zOrder);
	auto arm = static_cast<GBAArmatureProxy*>(_armature->getDisplay());
	arm->sortNodes();
}

void GBASlot::_updateFrame()
{
	const auto currentVerticesData = (_deformVertices != nullptr && _display == _meshDisplay) ? _deformVertices->verticesData : nullptr;
	auto currentTextureData = static_cast<GBATextureData*>(_textureData);

	auto display = static_cast<GBADisplay*>(_renderDisplay);

    mgba_printf(LOG_INFO, "_updateFrame: _displayIndex: %d, _display: 0x%x, _textureData: 0x%x, texture: 0x%x", _displayIndex, _display, currentTextureData, currentTextureData->texture);

	if (_displayIndex >= 0 && _display != nullptr && currentTextureData != nullptr)
    //if (false)
	{
        // confusing: currentTextureData: 0x0, null: 0x0, not null: true, true ???
        //mgba_printf(LOG_INFO, "currentTextureData: 0x%x, null: 0x%x, not null: %s, %s", currentTextureData, nullptr, (currentTextureData != nullptr) ? "true" : "false", (_displayIndex >= 0 && _display != nullptr && currentTextureData != nullptr)? "true" : "false");
		if (currentTextureData->texture != nullptr)
		{
			if (currentVerticesData != nullptr) // Mesh
			{
			//	const auto data = currentVerticesData->data;
			//	const auto intArray = data->intArray;
			//	const auto floatArray = data->floatArray;
			//	const unsigned vertexCount = intArray[currentVerticesData->offset + (unsigned)BinaryOffset::MeshVertexCount];
			//	const unsigned triangleCount = intArray[currentVerticesData->offset + (unsigned)BinaryOffset::MeshTriangleCount];
			//	int vertexOffset = intArray[currentVerticesData->offset + (unsigned)BinaryOffset::MeshFloatOffset];

			//	if (vertexOffset < 0)
			//	{
			//		vertexOffset += 65536;
			//	}

			//	const unsigned uvOffset = vertexOffset + vertexCount * 2;

			//	const auto& region = currentTextureData->region;

			//	std::vector<gba::Vertex> vertices(vertexCount);

			//	std::vector<std::vector<int>> verticesInTriagles;

			//	std::vector<uint16_t> vertexIndices(triangleCount * 3);

			//	for (std::size_t i = 0, l = vertexCount * 2; i < l; i += 2)
			//	{
			//		const auto iH = i / 2;

			//		const auto x = floatArray[vertexOffset + i];
			//		const auto y = floatArray[vertexOffset + i + 1];
			//		auto u = floatArray[uvOffset + i];
			//		auto v = floatArray[uvOffset + i + 1];

			//		gba::Vertex vertexData;
			//		vertexData.position = { x, y };

			//		if (currentTextureData->rotated)
			//		{
			//			vertexData.texCoords.x = (region.x + (1.0f - v) * region.width);
			//			vertexData.texCoords.y = (region.y + u * region.height);
			//		}
			//		else
			//		{
			//			vertexData.texCoords.x = (region.x + u * region.width);
			//			vertexData.texCoords.y = (region.y + v * region.height);
			//		}

			//		vertexData.color = gba::Color::White;
			//		
			//		vertices[iH] = vertexData;
			//	}

			//	for (std::size_t i = 0; i < triangleCount * 3; ++i)
			//	{
			//		vertexIndices.push_back(intArray[currentVerticesData->offset + (unsigned)BinaryOffset::MeshVertexIndices + i]);
			//	}

			//	std::vector<gba::Vertex> verticesDisplay;

			//	verticesInTriagles.resize(vertices.size());

			//	// sorting
			//	for (unsigned int i = 0; i < vertexIndices.size(); i++)
			//	{
			//		verticesInTriagles[vertexIndices[i]].push_back(i);
			//		verticesDisplay.push_back(vertices[vertexIndices[i]]);
			//	}

			//	_textureScale = 1.f;

			//	display->texture = currentTextureData->texture;
			//	display->verticesDisplay = std::move(verticesDisplay);
			//	display->verticesInTriagles = std::move(verticesInTriagles);
			//	display->primitiveType = gba::PrimitiveType::Triangles;

			//	const auto isSkinned = currentVerticesData->weight != nullptr;
			//	if (isSkinned)
			//	{
			//		_identityTransform();
			//	}
			}
			else // Normal texture
			{
				const auto scale = currentTextureData->parent->scale * _armature->_armatureData->scale;
				const auto height = (currentTextureData->rotated ? currentTextureData->region.width : currentTextureData->region.height) * scale;
				_textureScale = scale; 

				auto texRect =currentTextureData->region;

				display->texture = currentTextureData->texture;

				//display->verticesDisplay.resize(4);
				//display->verticesDisplay[0].texCoords = gba::Vector2f(texRect.x, 					texRect.y);
				//display->verticesDisplay[1].texCoords = gba::Vector2f(texRect.x, 					texRect.y + texRect.height);
				//display->verticesDisplay[2].texCoords = gba::Vector2f(texRect.x + texRect.width, 	texRect.y);
				//display->verticesDisplay[3].texCoords = gba::Vector2f(texRect.x + texRect.width, 	texRect.y + texRect.height);


				//float boundsWidth = static_cast<float>(std::abs(texRect.width));
				//float boundsheight = static_cast<float>(std::abs(texRect.height));

				//display->verticesDisplay[0].position = gba::Vector2f(0.f, 0.f);
				//display->verticesDisplay[1].position = gba::Vector2f(0.f, boundsheight);
				//display->verticesDisplay[2].position = gba::Vector2f(boundsWidth, 0.f);
				//display->verticesDisplay[3].position = gba::Vector2f(boundsWidth, boundsheight);

				//display->setColor(gba::Color::White);

                gba::IntRect *region = new gba::IntRect((int)texRect.x, (int)texRect.y, (int)texRect.width, (int)texRect.height);
                display->sprite = new gba::Sprite(display->texture, region);

                mgba_printf(LOG_INFO, "display->sprite: texture: 0x%x, texRect: x %.2f y %.2f w %.2f h %.2f", display->texture, texRect.x, texRect.y, texRect.width, texRect.height);
                mgba_printf(LOG_INFO, "display->sprite: texture: 0x%x, rect: x %d y %d w %d h %d", display->texture, region->getPosition().x, region->getPosition().y, region->getSize().x, region->getSize().y);
			}

			_visibleDirty = true;
			_blendModeDirty = true;
			_colorDirty = true;

			return;
		}
	}

	_renderDisplay->setVisible(false);
}

void GBASlot::_updateMesh()
{
	//const auto scale = _armature->_armatureData->scale;
	//const auto& deformVertices = _deformVertices->vertices;
	//const auto& bones = _deformVertices->bones;
	//const auto verticesData = _deformVertices->verticesData;
	//const auto weightData = verticesData->weight;

	//const auto hasFFD = !deformVertices.empty();
	//const auto meshDisplay = static_cast<GBADisplay*>(_renderDisplay);


	//if (weightData != nullptr)
	//{
	//	const auto data = verticesData->data;
	//	const auto intArray = data->intArray;
	//	const auto floatArray = data->floatArray;
	//	const auto vertexCount = (std::size_t)intArray[verticesData->offset + (unsigned)BinaryOffset::MeshVertexCount];
	//	int weightFloatOffset = intArray[weightData->offset + (unsigned)BinaryOffset::WeigthFloatOffset];

	//	if (weightFloatOffset < 0)
	//	{
	//		weightFloatOffset += 65536;
	//	}

	//	for (
	//		std::size_t i = 0, iD = 0, iB = weightData->offset + (unsigned)BinaryOffset::WeigthBoneIndices + bones.size(), iV = (std::size_t)weightFloatOffset, iF = 0;
	//		i < vertexCount;
	//		++i
	//		)
	//	{
	//		const auto boneCount = (std::size_t)intArray[iB++];
	//		auto xG = 0.0f, yG = 0.0f;
	//		for (std::size_t j = 0; j < boneCount; ++j)
	//		{
	//			const auto boneIndex = (unsigned)intArray[iB++];
	//			const auto bone = bones[boneIndex];
	//			if (bone != nullptr)
	//			{
	//				const auto& matrix = bone->globalTransformMatrix;
	//				const auto weight = floatArray[iV++];
	//				auto xL = floatArray[iV++] * scale;
	//				auto yL = floatArray[iV++] * scale;

	//				if (hasFFD)
	//				{
	//					xL += deformVertices[iF++];
	//					yL += deformVertices[iF++];
	//				}

	//				xG += (matrix.a * xL + matrix.c * yL + matrix.tx) * weight;
	//				yG += (matrix.b * xL + matrix.d * yL + matrix.ty) * weight;
	//			}
	//		}

	//		auto& vertsDisplay = meshDisplay->verticesDisplay;

	//		for (auto vert : meshDisplay->verticesInTriagles[i])
	//		{
	//			auto& vertexPosition = vertsDisplay[vert].position;
	//			vertexPosition = { xG, yG };
	//		}
	//	}
	//}
	//else if (hasFFD)
	//{
	//	const auto data = verticesData->data;
	//	const auto intArray = data->intArray;
	//	const auto floatArray = data->floatArray;
	//	const auto vertexCount = (std::size_t)intArray[verticesData->offset + (unsigned)BinaryOffset::MeshVertexCount];
	//	int vertexOffset = (std::size_t)intArray[verticesData->offset + (unsigned)BinaryOffset::MeshFloatOffset];

	//	if (vertexOffset < 0)
	//	{
	//		vertexOffset += 65536;
	//	}

	//	for (std::size_t i = 0, l = vertexCount * 2; i < l; i += 2)
	//	{
	//		const auto iH = i / 2;
	//		const auto xG = floatArray[vertexOffset + i] * scale + deformVertices[i];
	//		const auto yG = floatArray[vertexOffset + i + 1] * scale + deformVertices[i + 1];

	//		auto& vertsDisplay = meshDisplay->verticesDisplay;

	//		for (auto vert : meshDisplay->verticesInTriagles[iH])
	//		{
	//			auto& vertexPosition = vertsDisplay[vert].position;
	//			vertexPosition = { xG, yG };
	//		}
	//	}
	//}
}

void GBASlot::_identityTransform()
{
	_renderDisplay->setMatrix(Transform(), gba::Vector2f(), _textureScale, _textureScale);
}

void GBASlot::_updateTransform()
{
    //FIXME: convert transform with pivot
    //mgba_printf(LOG_INFO, "_updateTransform: global: x: %.2f, y: %.2f, skew: %.2f, rotation: %.2f, scaleX: %.2f, scaleY: %.2f", global.x, global.y, global.skew, global.rotation, global.scaleX, global.scaleY);
	//gba::Vector2f pos(
	//	globalTransformMatrix.tx,
	//	globalTransformMatrix.ty
	//);

    //gba::Vector2f pos;
    //pos.x = 0;
    //pos.y = 0;
    Transform globalTransform;
    globalTransform.fromMatrix(globalTransformMatrix);
	//if (_renderDisplay == _rawDisplay || _renderDisplay == _meshDisplay)
	//{
	//	globalTransform.x -= globalTransformMatrix.a * _pivotX + globalTransformMatrix.c * _pivotY;
	//	globalTransform.y -= globalTransformMatrix.b * _pivotX + globalTransformMatrix.d * _pivotY;
	//}
	//else
	//{
	//	globalTransform.x -= globalTransformMatrix.a - globalTransformMatrix.c;
	//	globalTransform.y -= globalTransformMatrix.b - globalTransformMatrix.d;
	//}
    globalTransform.scaleX *= _textureScale;
    globalTransform.scaleY *= _textureScale;

    mgba_printf(LOG_INFO, "_updateTransform: globalTransform: x: %.2f, y: %.2f, pivot: (%.2f, %.2f), skew: %.2f, rotation: %.2f, scaleX: %.2f, scaleY: %.2f", globalTransform.x, globalTransform.y, _pivotX, _pivotY, globalTransform.skew, globalTransform.rotation, globalTransform.scaleX, globalTransform.scaleY);

	_renderDisplay->setPivot(_pivotX, _pivotY);
	//_renderDisplay->setPivot(0, 0);
	//_renderDisplay->setMatrix(globalTransform, pos, _textureScale, _textureScale);
    _renderDisplay->setTransform(globalTransform);
}

void GBASlot::_onClear()
{
	Slot::_onClear();

	_textureScale = 1.0f;
	_renderDisplay = nullptr;
}

DRAGONBONES_NAMESPACE_END
