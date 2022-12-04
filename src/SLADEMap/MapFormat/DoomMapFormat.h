#pragma once

#include "MapFormatHandler.h"

namespace slade
{
class ThingList;
class SectorList;
class LineList;
class SideList;
class VertexList;

class DoomMapFormat : public MapFormatHandler
{
public:
	struct Vertex
	{
		short x;
		short y;
	};

	struct SideDef
	{
		short x_offset;
		short y_offset;
		char  tex_upper[8];
		char  tex_lower[8];
		char  tex_middle[8];
		short sector;
	};

	struct LineDef
	{
		uint16_t vertex1;
		uint16_t vertex2;
		uint16_t flags;
		uint16_t type;
		uint16_t sector_tag;
		uint16_t side1;
		uint16_t side2;
	};

	struct Sector
	{
		short f_height;
		short c_height;
		char  f_tex[8];
		char  c_tex[8];
		short light;
		short special;
		short tag;
	};

	struct Thing
	{
		short x;
		short y;
		short angle;
		short type;
		short flags;
	};

	bool readMap(Archive::MapDesc map, MapObjectCollection& map_data, PropertyList& map_extra_props) override;
	vector<unique_ptr<ArchiveEntry>> writeMap(const MapObjectCollection& map_data, const PropertyList& map_extra_props)
		override;

protected:
	virtual bool readVERTEXES(ArchiveEntry* entry, MapObjectCollection& map_data) const;
	virtual bool readSIDEDEFS(ArchiveEntry* entry, MapObjectCollection& map_data) const;
	virtual bool readLINEDEFS(ArchiveEntry* entry, MapObjectCollection& map_data) const;
	virtual bool readSECTORS(ArchiveEntry* entry, MapObjectCollection& map_data) const;
	virtual bool readTHINGS(ArchiveEntry* entry, MapObjectCollection& map_data) const;

	virtual unique_ptr<ArchiveEntry> writeVERTEXES(const VertexList& vertices) const;
	virtual unique_ptr<ArchiveEntry> writeSIDEDEFS(const SideList& sides) const;
	virtual unique_ptr<ArchiveEntry> writeLINEDEFS(const LineList& lines) const;
	virtual unique_ptr<ArchiveEntry> writeSECTORS(const SectorList& sectors) const;
	virtual unique_ptr<ArchiveEntry> writeTHINGS(const ThingList& things) const;
};
} // namespace slade
