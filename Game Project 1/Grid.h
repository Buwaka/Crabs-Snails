#pragma once
#include <vector>
#include <string>
#include "utils.h"

class Grid
{
public:



	Grid();
	Grid(int x, int y, int tilesize);
	Grid(const SDL_Surface * surface, int tilesize);
	Grid(const std::string path, int tilesize);
	~Grid();
	Grid(const Grid& other);
	Grid& operator=(const Grid& other);
	Grid(Grid&& other);
	Grid& operator=(Grid&& other);

	static std::vector<std::vector<Sutils::RGBA>> SurfaceToRGBAGrid(const SDL_Surface* surface, int tilesize = 1);

	void Init(const std::string path, int tilesize);
	void Init(const SDL_Surface * surface, int tilesize);

	bool Getvalue(int x, int y) const;
	bool Getvalue(Vector2I pos) const;
	bool Getvalue(Point2f pos) const;
	bool GetvalueGrid(int x, int y) const;
	bool GetvalueGrid(Vector2I pos) const;
	bool GetvalueGrid(Point2f pos) const;

	Vector2I GetGridPosition(int x, int y) const;
	Vector2I GetGridPosition(Vector2I pos) const;
	Vector2I GetGridPosition(Point2f pos) const;

	void SetGridValue(int x, int y, bool value);
	void SetValue(int x, int y, bool value);

	friend Grid operator+(const Grid& lhs, const Grid& rhs);


	int GetWidth() const;
	int GetGridWidth() const;
	int GetHeight() const;
	int GetGridHeight() const;
	int m_tilesize;

private:
	void SetMapDimension(int x, int y); //only for init
	std::vector<std::vector<bool>>* GetMap();

	std::vector<std::vector<bool>> map; // map[y][x]

	std::vector<std::vector<bool>> RGBAGridToGrid(const std::vector<std::vector<Sutils::RGBA>> RGBAGrid);
};

bool operator==(const Vector2I& lhs, const Vector2I& rhs);
Vector2I operator+(const Vector2I& lhs, const Vector2I& rhs);
Grid operator+(const Grid& lhs, const Grid& rhs);