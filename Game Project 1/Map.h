#pragma once
#include "Texture.h"
#include <iostream>
#include "Vector2f.h"
#include "Grid.h"
#include <memory>

class Map
{
public:
	explicit Map();
	Map(const Map& other) = delete;
	Map& operator=(const Map& other) = delete;
	Map(Map&& other) = delete;
	Map& operator=(Map&& other) = delete;
	~Map();

	void Init(std::string map, std::string collissionmap, int tilesizeX, int tilesizeY, const Window* window);
	void Draw() const;
	void Update();

	bool IsCollission(Vector2f position, Vector2f movement, Grid* extra = nullptr) const;
	Rectf GetDimension() const;
	Grid GetGrid() const;
	Mix_Music* GetBGM();

	int m_TileSizeX, m_TileSizeY, m_Width, m_Height;
private:
	SDL_Surface* m_pCollissionMapSurface;
	std::shared_ptr<Texture> m_pMapTexture;
	Grid m_Map;
	std::string m_PathTexture, m_PathCollissionMap;
	bool m_IsCreationOK;
	const Window * m_pWindow;
	/*Rectf m_CurrentView{}, m_Lastview{};*/
	Point2f m_Startposition{};

	Mix_Music* m_BGM;

};

