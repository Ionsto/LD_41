#include "RenderWorld.h"



RenderWorld::RenderWorld(sf::RenderWindow * rwindow){
	this->window = rwindow;
}


RenderWorld::~RenderWorld(){
}

//Grab all our resources & stick them onto our sprites
void RenderWorld::InitRes(){

}
void RenderWorld::Render(World &const world) {

}
void RenderWorld::RenderEntites(World &const world) {
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
		break;
	}
}
void RenderWorld::RenderTerrain(World &const world) {

}