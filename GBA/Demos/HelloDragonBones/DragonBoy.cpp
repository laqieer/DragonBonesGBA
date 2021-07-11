/** @file DragonBoy.cpp
 ** @author Piotr Krupa (piotrkrupa06@gmail.com)
 ** @license MIT License
 **/

#include <tonc.h>
#include "tonc_mgba.h"

#include <dragonBones/GBAFactory.h>
#include <dragonBones/GBAArmatureDisplay.h>

#include "Texture.hpp"
#include <dragonBones/GBATextureAtlasData.h>

int main()
{
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ_2D | DCNT_OBJ;

    OAM_CLEAR();

	float deltaTime = 1.f / 60;

	gba::Texture texture("DragonBoy_tex.png");
    mgba_printf(LOG_INFO, "texture: 0x%x, id %d", &texture, texture.id);

	dragonBones::GBAFactory factory;

	factory.loadDragonBonesData("DragonBoy_ske.json");
	dragonBones::GBATextureAtlasData *textureAtlasData = dynamic_cast<dragonBones::GBATextureAtlasData *>(factory.loadTextureAtlasData("DragonBoy_tex.json", &texture));

    mgba_printf(LOG_INFO, "factory: 0x%x, textureAtlasData: 0x%x, _renderTexture: 0x%x", factory.get(), textureAtlasData, textureAtlasData->getRenderTexture());

	auto armatureDisplay = new dragonBones::GBAArmatureDisplay("Dragon");
	armatureDisplay->getAnimation()->play("walk");
	armatureDisplay->setPosition({ 120.f, 0.f });

    mgba_printf(LOG_INFO, "armatureDisplay: proxy: 0x%x, position: (%d, %d)", armatureDisplay->getArmatureProxy(), (int)armatureDisplay->getPosition().x, (int)armatureDisplay->getPosition().y);

    irq_init(NULL);
    irq_enable(II_VBLANK);

	while (true)
	{
        armatureDisplay->draw();
        VBlankIntrWait();
		factory.update(deltaTime);
	}
	
	return 0;
}
