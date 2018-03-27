#pragma once
#include <string>

class MapLink {
public:
//Constructors
	//\Create a closed link with mapID = 0
	MapLink() : open(false), mapID(0) {}
	//\Take a bool and unsigned to create a MapLink
	MapLink(bool open, unsigned mapID) : open(open), mapID(mapID) {}

//Queries
	//\Tell whether the link is open or not
	bool isOpen() { return open; }

//Accessors
	//\Get the ID of the link
	unsigned getMapID() { return mapID; }

private:
	/*The "open" flag determines whether or not a particular tile actually links to a new map.
	  Every tile contains a "MapLink" member, however, the majority of tiles don't actually link
	  to a new map. Before checking WHERE a tile links to, the "open" flag is checked first. If it
	  is false, than that particular tile does not link anywhere and checking the "mapID" becomes redundant.*/
	bool open;
	/*The ID of the map that is going to be linked to, if the player steps on a tile that is considered "open,"
	  then the "mapID" is checked and the corresponding map is loaded*/
	unsigned mapID;
};

bool s2b(std::string s);