#include "RenderWorld.h"



RenderWorld::RenderWorld(sf::RenderWindow * rwindow){
	this->window = rwindow;
	InitRes();
}


RenderWorld::~RenderWorld(){
}

//Grab all our resources & stick them onto our sprites
void RenderWorld::InitRes(){
	Ambulance = std::make_unique<TexturedSprite>("./Resources/Images/Ambulance.png");
}
void RenderWorld::Render(World &const world) {
	RenderEntites(world);
}
void RenderWorld::RenderEntites(World &const world) {
	if (world.EntityList[world.player.PlayerId])
	{
		CameraLocation = sf::Vector2f(world.EntityList[world.player.PlayerId]->Pos.x - CameraSize.x*0.5, world.EntityList[world.player.PlayerId]->Pos.y - CameraSize.y*0.5);
	}
	for (int id = 0; id < world.HighestEntityLocation; ++id)
	{
		if (world.EntityList[id] && world.EntityList[id]->Alive)
		{
			//Render this guy
			RenderEntity(*world.EntityList[id].get());
		}
	}
}
void RenderWorld::RenderEntity(Entity &const entity) {
	switch(entity.Type){
	case Entity::EntityType::Ambulence:
		Ambulance->Render(*window, sf::Vector2f(entity.Pos.x, entity.Pos.y) - CameraLocation, entity.Rotation);
		break;
	}
}
void RenderWorld::RenderTerrain(World &const world) {

}