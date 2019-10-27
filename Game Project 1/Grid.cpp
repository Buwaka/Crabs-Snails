#include "stdafx.h"
#include "Grid.h"
#include "utils.h"
#include <algorithm>
#include <numeric>


Grid::Grid()
{
}

Grid::Grid(int x, int y, int tilesize)
{
	SetMapDimension(x, y);
	m_tilesize = tilesize;
}

Grid::Grid(const SDL_Surface * surface, int tilesize)
{
	map = RGBAGridToGrid( SurfaceToRGBAGrid(surface, tilesize) );

	m_tilesize = tilesize;
}

Grid::Grid(const std::string path, int tilesize)
{
	SDL_Surface* temp = Sutils::LoadSurface(path);
	map = RGBAGridToGrid(SurfaceToRGBAGrid(temp, tilesize));

	SDL_FreeSurface(temp);
	delete temp;

	m_tilesize = tilesize;
}



Grid::~Grid()
{
}

Grid::Grid(const Grid & other)
{
	m_tilesize = other.m_tilesize;
	map = other.map;
}

Grid & Grid::operator=(const Grid & other)
{
	m_tilesize = other.m_tilesize;
	map = other.map;
	return *this;
}

Grid::Grid(Grid && other)
{
	if (this != &other) // prevent self-move
	{
		*this = other;
	}
}

Grid & Grid::operator=(Grid && other)
{
	if (this != &other) // prevent self-move
	{
		*this = other;
	}
	return *this;
}

std::vector<std::vector<Sutils::RGBA>> Grid::SurfaceToRGBAGrid(const SDL_Surface * surface, int tilesize)
{
	int x = (int) std::floor(tilesize / 2);
	int y = (int)std::floor(tilesize / 2);
	std::vector<std::vector<Sutils::RGBA>> full;

	for (y = y; y < surface->h ; y += tilesize)
	{
		std::vector<Sutils::RGBA> temp;
		for (x = x; x < surface->w ; x += tilesize)
		{
			temp.push_back(Sutils::GetRGBA(Vector2f{ (float) x, (float) y }, surface));
		}
		full.push_back(temp);
		x = (int)std::floor(tilesize / 2);
	}

	return full;
}

void Grid::Init(const std::string path, int tilesize)
{
	SDL_Surface* temp = Sutils::LoadSurface(path);
	map = RGBAGridToGrid(SurfaceToRGBAGrid(temp, tilesize));

	SDL_FreeSurface(temp);
	delete temp;

	m_tilesize = tilesize;
}

void Grid::Init(const SDL_Surface * surface, int tilesize)
{
	map = RGBAGridToGrid(SurfaceToRGBAGrid(surface, tilesize));

	m_tilesize = tilesize;
}

bool Grid::Getvalue(int x, int y) const
{
	int x1 = (int) std::floor(x / m_tilesize);
	x1 = Sutils::clamp(x1, 0, GetGridWidth() - 1);

	int y1 = (int) std::floor(y / m_tilesize);
	y1 = Sutils::clamp(y1, 0, GetGridHeight() - 1);

	return map[y1][x1];
}

bool Grid::Getvalue(Vector2I pos) const
{
	return Getvalue(pos.x, pos.y);
}

bool Grid::Getvalue(Point2f pos) const
{
	return Getvalue((int) pos.x, (int) pos.y);
}

bool Grid::GetvalueGrid(int x, int y) const
{
	return map[y][x];
}

bool Grid::GetvalueGrid(Vector2I pos) const
{
	return GetvalueGrid(pos.x, pos.y);
}

bool Grid::GetvalueGrid(Point2f pos) const
{
	return GetvalueGrid((int) pos.x, (int) pos.y);
}

Vector2I Grid::GetGridPosition(int x, int y) const
{
	int x1 = (int)std::floor(x / m_tilesize);
	x1 = Sutils::clamp(x1, 0, GetWidth());

	int y1 = (int)std::floor(y / m_tilesize);
	y1 = Sutils::clamp(y1, 0, GetHeight());

	return Vector2I{ x1,y1 };
}

Vector2I Grid::GetGridPosition(Vector2I pos) const
{
	return GetGridPosition(pos.x, pos.y);
}

Vector2I Grid::GetGridPosition(Point2f pos) const
{
	return GetGridPosition((int) pos.x, (int) pos.y);
}

void Grid::SetGridValue(int x, int y, bool value)
{
	map[y][x] = value;
}

void Grid::SetValue(int x, int y, bool value)
{
	map[y / m_tilesize][x / m_tilesize] = value;
}

int Grid::GetWidth() const
{
	return(int)map[0].size() * m_tilesize;
}

int Grid::GetGridWidth() const
{
	return(int)map[0].size();
}

int Grid::GetHeight() const
{
	return(int)map.size() * m_tilesize;
}

int Grid::GetGridHeight() const
{
	return(int)map.size();
}

void Grid::SetMapDimension(int x, int y)
{
	map.resize(y);

	std::fill(map.begin(), map.end(), std::vector<bool>(x,true));
}

std::vector<std::vector<bool>>* Grid::GetMap()
{
	return &map;
}

std::vector<std::vector<bool>> Grid::RGBAGridToGrid(const std::vector<std::vector<Sutils::RGBA>> RGBAGrid)
{
	std::vector<std::vector<bool>> full;

	for (int y = 0; y < (int) RGBAGrid.size(); y++)
	{
		std::vector<bool> temp;
		for (int x = 0; x < (int)RGBAGrid[y].size(); x++)
		{
			if (RGBAGrid[y][x].Red > 0 && RGBAGrid[y][x].Green > 0 && RGBAGrid[y][x].Blue > 0)
			{
				temp.push_back(true);
			}
			else
			{
				temp.push_back(false);
			}
		}
		full.push_back(temp);
	}

	return full;
}

bool operator==(const Vector2I & lhs, const Vector2I & rhs)
{
	return ( lhs.x == rhs.x && lhs.y == rhs.y);
}

Vector2I operator+(const Vector2I & lhs, const Vector2I & rhs)
{
	return Vector2I{ lhs.x + rhs.x, lhs.y + rhs.y };
}

Grid operator+(const Grid & lhs, const Grid & rhs)
{
	Grid temp(std::min(lhs.GetGridWidth(), rhs.GetGridWidth()), std::min(lhs.GetGridHeight(), rhs.GetGridHeight()), lhs.m_tilesize);// copy schrijven
	//temp.SetMapDimension(std::min(lhs.GetGridWidth(), rhs.GetGridWidth()), std::min(lhs.GetGridHeight(), rhs.GetGridHeight()));

	for (int i = 0; i < std::min(lhs.GetGridHeight(), rhs.GetGridHeight()); i++)
	{
		for (int j = 0; j < std::min(lhs.GetGridWidth(), rhs.GetGridWidth()); j++)
		{
			temp.SetGridValue(j, i,lhs.GetvalueGrid(j,i) && rhs.GetvalueGrid(j, i));
		}
	}

	return temp;
}
