#include "RenderWorld.h"



RenderWorld::RenderWorld(sf::RenderWindow * rwindow){
	this->window = rwindow;
	InitRes();
	CameraView = sf::View();
	MiniMap = sf::View(sf::Vector2f(World::WorldSize*Scale/2, World::WorldSize*Scale/2),sf::Vector2f(World::WorldSize*Scale, World::WorldSize*Scale));
	MiniMap.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	Marker = sf::CircleShape(10 * Scale);
	Marker.setFillColor(sf::Color::Green);
	Marker.setOrigin(sf::Vector2f(20 * Scale, 20 * Scale));
	BackGround = std::make_unique<sf::RectangleShape>(sf::Vector2f(0,0));
	BackGround->setFillColor(sf::Color::White);
	BackGround->setSize(sf::Vector2f(1, 1)* Scale * World::WorldSize);
}


RenderWorld::~RenderWorld(){
}

//Grab all our resources & stick them onto our sprites
void RenderWorld::InitRes(){
	Ambulance = std::make_unique<TexturedSprite>("./Resources/Images/Ambulance.png", sf::Vector2f(Scale * 2 * 1.5 / 672.0, Scale * 2 * 3.744 / 1544.0));
	RoadSprite = std::make_unique<TexturedSprite>("./Resources/Images/BlockRoad.png", sf::Vector2f((World::BlockSize + World::RoadWidth), (World::BlockSize + World::RoadWidth))*(Scale / 900.0f));
	OuterRoadSprite = std::make_unique<TexturedSprite>("./Resources/Images/OuterRoad.png", sf::Vector2f((World::BlockSize + World::RoadWidth)/900.0f, 0.5*World::RoadWidth / 200.0f)*Scale);
	HospitalSprite = std::make_unique<TexturedSprite>("./Resources/Images/Hospital.png", sf::Vector2f(World::RoadWidth/2, World::RoadWidth/2)*(Scale/1800.0f));
	for (int i = 0; i < 2; ++i) {
		Buildings.emplace_back(std::make_unique<TexturedSprite>("./Resources/Images/Building" + std::to_string(i) + ".png", sf::Vector2f(Scale * 10.0 / 1800.0, Scale * 10.0 / 1800.0)));
	}
	for (int i = 0; i < 3; ++i) {
		Cars.emplace_back(std::make_unique<TexturedSprite>("./Resources/Images/Car" + std::to_string(i) + ".png", sf::Vector2f(Scale * 2 * 1.5 / 672.0, Scale * 2 * 3.744 / 1544.0)));
	}
}
void RenderWorld::Render(World &const world) {
	if (world.EntityList[world.Player.PlayerId])
	{
		CameraLocation = sf::Vector2f(world.EntityList[world.Player.PlayerId]->Pos.x, world.EntityList[world.Player.PlayerId]->Pos.y);
		CameraView.setCenter(CameraLocation*Scale);
		CameraView.setRotation((world.EntityList[world.Player.PlayerId]->Rotation * 180/3.14)+90);
	}
	window->setView(CameraView);
	RenderTerrain(world);
	RenderEntites(world);
	//RenderNodes(world);
	RenderMiniMap(world);
	//Fuck me man this is the only thing that gets the GUI to work :/
	BackGround->setFillColor(sf::Color::Transparent);
	window->draw(*BackGround.get());
}
//hm doesn't work
void RenderWorld::ResetDrawSpace() {
	window->setView(window->getDefaultView());
	window->resetGLStates();
	window->draw(*BackGround.get());
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
void RenderWorld::RenderNodes(World &const world) {
	for (auto & node : world.RoadNetwork.NodeMap)
	{
		Marker.setOrigin(sf::Vector2f(10 * Scale, 10 * Scale));
		Marker.setFillColor(sf::Color(0, 0, 255, 125));
		if (node.Target) {
			Marker.setFillColor(sf::Color(0, 255, 255, 125));
		}
		Marker.setPosition(((sf::Vector2f(node.X, node.Y))*Scale));
		window->draw(Marker);
	}
}
void RenderWorld::RenderEntity(Entity &const entity) {
	switch(entity.Type){
	case Entity::EntityType::Ambulence:
		Ambulance->Render(*window, ((sf::Vector2f(entity.Pos.x, entity.Pos.y))*Scale), entity.Rotation);
		break;
	case Entity::EntityType::Building:
		Buildings[entity.Id%Buildings.size()]->Render(*window, ((sf::Vector2f(entity.Pos.x, entity.Pos.y))*Scale), entity.Rotation);
		break;
	case Entity::EntityType::Car:
		Cars[entity.Id%Cars.size()]->Render(*window, ((sf::Vector2f(entity.Pos.x, entity.Pos.y))*Scale), entity.Rotation);
		break;
	case Entity::EntityType::Accident:
		Marker.setOrigin(sf::Vector2f(10 * Scale, 10 * Scale));
		Marker.setFillColor(sf::Color(255,0,0,125));
		Marker.setPosition(((sf::Vector2f(entity.Pos.x, entity.Pos.y))*Scale));
		window->draw(Marker);
		break;
	}
}
void RenderWorld::RenderTerrain(World &const world) {
	for (int x = 0; x < World::BlockCount; ++x) {
		for (int y = 0; y < World::BlockCount; ++y) {
			float xp = (x * (World::BlockSize + World::RoadWidth)) + (World::BlockSize + World::RoadWidth)/2 + World::RoadWidth/2;
			float yp = (y * (World::BlockSize + World::RoadWidth)) + (World::BlockSize + World::RoadWidth)/2 + World::RoadWidth/2;
			RoadSprite->Render(*window, ((sf::Vector2f(xp, yp))*Scale), 0);
		}
	}
	//Outer loop
	for (int x = 0; x < World::BlockCount; ++x) {
		{
			float xp = (x * (World::BlockSize + World::RoadWidth)) + (World::BlockSize + World::RoadWidth) / 2 + World::RoadWidth / 2;
			float yp = World::RoadWidth / 4;
			OuterRoadSprite->Render(*window, ((sf::Vector2f(xp, yp))*Scale), -3.14 / 2);
		}
		{
			float xp = (x * (World::BlockSize + World::RoadWidth)) + (World::BlockSize + World::RoadWidth) / 2 + World::RoadWidth / 2;
			float yp = World::WorldSize - World::RoadWidth / 4;
			OuterRoadSprite->Render(*window, ((sf::Vector2f(xp, yp))*Scale), -3.14 / 2);
		}
	}
	for (int y = 0; y < World::BlockCount; ++y) {
		{
			float yp = (y * (World::BlockSize + World::RoadWidth)) + (World::BlockSize + World::RoadWidth) / 2 + World::RoadWidth / 2;
			float xp = World::RoadWidth / 4;
			OuterRoadSprite->Render(*window, ((sf::Vector2f(xp, yp))*Scale), 0);
		}
		{
			float yp = (y * (World::BlockSize + World::RoadWidth)) + (World::BlockSize + World::RoadWidth) / 2 + World::RoadWidth / 2;
			float xp = World::WorldSize - World::RoadWidth / 4;
			OuterRoadSprite->Render(*window, ((sf::Vector2f(xp, yp))*Scale), 3.14);
		}
	}
	HospitalSprite->Render(*window, ((sf::Vector2f(World::RoadWidth/4, World::RoadWidth/4))*Scale), -3.14/2);
}
void RenderWorld::RenderMiniMap(World &const world) {
	window->setView(MiniMap);
	BackGround->setFillColor(sf::Color::White);
	window->draw(*BackGround.get());

	RenderTerrain(world);
	Marker.setOrigin(sf::Vector2f(10 * Scale, 10 * Scale));
	//Draw buildings first ...
	for (int id = 0; id < world.HighestEntityLocation; ++id)
	{
		if (world.EntityList[id] && world.EntityList[id]->Alive)
		{
			auto & entity = *world.EntityList[id].get();
			switch (entity.Type) {
			case Entity::EntityType::Building:
				Buildings[entity.Id%Buildings.size()]->Render(*window, ((sf::Vector2f(entity.Pos.x, entity.Pos.y))*Scale), entity.Rotation);
				break;
			}
		}
	}
	for (int id = 0; id < world.HighestEntityLocation; ++id)
	{
		if (world.EntityList[id] && world.EntityList[id]->Alive)
		{
			auto & entity = *world.EntityList[id].get();
			switch (entity.Type) {
			case Entity::EntityType::Ambulence:
				Marker.setFillColor(sf::Color::Green);
				Marker.setPosition(((sf::Vector2f(entity.Pos.x, entity.Pos.y))*Scale));
				window->draw(Marker);
				break;
			case Entity::EntityType::Accident:
				Marker.setFillColor(sf::Color::Red);
				Marker.setPosition(((sf::Vector2f(entity.Pos.x, entity.Pos.y))*Scale));
				window->draw(Marker);
				break;
			/*case Entity::EntityType::Car:
				Cars[0]->Render(*window, ((sf::Vector2f(entity.Pos.x, entity.Pos.y))*Scale), entity.Rotation);
				break;*/
			}
		}
	}
	//RenderNodes(world);
	window->setView(window->getDefaultView());
}