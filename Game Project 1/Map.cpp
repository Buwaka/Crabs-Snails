#include "stdafx.h"
#include "Map.h"
#include <algorithm>
#include "utils.h"


Map::Map()
{

}

Map::~Map()
{
	SDL_FreeSurface(m_pCollissionMapSurface);
	//delete m_pCollissionMapSurface;
	//delete m_pMapTexture;
	Mix_FreeMusic(m_BGM);
}

void Map::Update()
{
	//m_Lastview = m_CurrentView;
	//startposition
}

void Map::Init(std::string map, std::string collissionmap, int tilesizeX, int tilesizeY, const Window* window)
{
	m_PathTexture = map;
	m_PathCollissionMap = collissionmap;
	m_TileSizeX = tilesizeX;
	m_TileSizeY = tilesizeY;
	m_pCollissionMapSurface = Sutils::LoadSurface(collissionmap);
	m_Map.Init(m_pCollissionMapSurface, tilesizeX);

	m_BGM = Mix_LoadMUS("resources/mapTheme.wav");

	m_pMapTexture = std::make_shared<Texture>(map);
	m_pWindow = window;
	m_Width = (int)m_pMapTexture->GetWidth();
	m_Height = (int)m_pMapTexture->GetHeight();

	m_Startposition = { 0, (float)m_Height };
}

void Map::Draw() const
{
	//float left, bottom, width, height;
	//bottom = Sutils::lerpS(m_Lastview.bottom, view.bottom, interpolate);
	//left   = Sutils::lerpS(m_Lastview.left  , view.left  , interpolate);
	//width  = Sutils::lerpS(m_Lastview.width , view.width , interpolate);
	//height = Sutils::lerpS(m_Lastview.height, view.height, interpolate);

	//m_pMapTexture->Draw({ 0,0, width, height }, Rectf{left, bottom, width, height});

	//m_CurrentView = view;

	m_pMapTexture->Draw(Rectf{}, Rectf{});
}

bool Map::IsCollission(Vector2f position, Vector2f movement, Grid* extra) const
{
	Vector2f fposition = (position + movement);

	bool OutOfBoundsX = fposition.x > m_Width  || fposition.x < 0;
	bool OutOfBoundsY = fposition.y > m_Height || fposition.y < 0;

	if ( (movement.x > 0 && fposition.x >= m_Width) || 
		(movement.x < 0  && fposition.x < 0)	   ||
		(movement.y > 0 && fposition.y >= m_Height) ||
		(movement.y < 0 && fposition.y < 0) )
	{
		return true;
	}

	Sutils::RGBA temp = Sutils::GetRGBA(fposition, m_pCollissionMapSurface);
	//std::cout << (int)temp.Red << (int)temp.Green <<(int)temp.Blue <<std::endl;
	if (extra != nullptr)
	{
		return ((m_Map + *extra).Getvalue(fposition.ToPoint2f())) ? false : true;
	}
	return (m_Map.Getvalue(fposition.ToPoint2f())) ? false : true;

}

Rectf Map::GetDimension() const
{
	return Rectf{0,0, (float)m_Width, (float)m_Height};
}

Grid Map::GetGrid() const
{
	return m_Map;
}

Mix_Music * Map::GetBGM()
{
	return m_BGM;
}


