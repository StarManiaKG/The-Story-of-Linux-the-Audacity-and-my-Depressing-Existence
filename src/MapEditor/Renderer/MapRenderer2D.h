#pragma once

#include "MapEditor/MapEditor.h"
#include "SLADEMap/MapObject/MapObject.h"
#include "Utility/Colour.h"

namespace slade
{
// Forward declarations
class ItemSelection;
class MapLine;
class MapSector;
class MapThing;
class ObjectEditGroup;
class SLADEMap;
namespace game
{
	class ThingType;
}

class MapRenderer2D
{
public:
	MapRenderer2D(SLADEMap* map) : map_{ map } {}
	~MapRenderer2D();

	double viewScaleInv() const { return view_scale_inv_; }

	// Vertices
	bool setupVertexRendering(float size_scale, bool overlay = false) const;
	void renderVertices(float alpha = 1.0f);
	void renderVerticesVBO();
	void renderVerticesImmediate();
	void renderVertexHilight(int index, float fade) const;
	void renderVertexSelection(const ItemSelection& selection, float fade = 1.0f) const;

	// Lines
	ColRGBA lineColour(MapLine* line, bool ignore_filter = false) const;
	void    renderLines(bool show_direction, float alpha = 1.0f);
	void    renderLinesVBO(bool show_direction, float alpha);
	void    renderLinesImmediate(bool show_direction, float alpha);
	void    renderLineHilight(int index, float fade) const;
	void    renderLineSelection(const ItemSelection& selection, float fade = 1.0f) const;
	void    renderTaggedLines(vector<MapLine*>& lines, float fade) const;
	void    renderTaggingLines(vector<MapLine*>& lines, float fade) const;

	// Things
	enum ThingDrawType
	{
		Square,
		Round,
		Sprite,
		SquareSprite,
		FramedSprite,
	};
	bool setupThingOverlay() const;
	void renderThingOverlay(double x, double y, double radius, bool point) const;
	void renderRoundThing(
		double                   x,
		double                   y,
		double                   angle,
		const game::ThingType&   type,
		const MapObject::ArgSet& args,
		float                    alpha       = 1.0f,
		double                   radius_mult = 1.0) const;
	bool renderSpriteThing(
		double                   x,
		double                   y,
		double                   angle,
		const game::ThingType&   type,
		const MapObject::ArgSet& args,
		unsigned                 index,
		float                    alpha     = 1.0f,
		bool                     fitradius = false);
	void renderSimpleSquareThing(
		double                   x,
		double                   y,
		double                   angle,
		const game::ThingType&   type,
		const MapObject::ArgSet& args,
		float                    alpha = 1.0f) const;
	bool renderSquareThing(
		double                   x,
		double                   y,
		double                   angle,
		const game::ThingType&   type,
		const MapObject::ArgSet& args,
		float                    alpha    = 1.0f,
		bool                     showicon = true,
		bool                     framed   = false) const;
	void renderThings(float alpha = 1.0f, bool force_dir = false);
	void renderThingsImmediate(float alpha);
	void renderThingHilight(int index, float fade) const;
	void renderThingSelection(const ItemSelection& selection, float fade = 1.0f) const;
	void renderTaggedThings(vector<MapThing*>& things, float fade) const;
	void renderTaggingThings(vector<MapThing*>& things, float fade) const;
	void renderPathedThings(vector<MapThing*>& things);
	void renderPointLightPreviews(float alpha, int hilight_index) const;

	// Flats (sectors)
	void renderFlats(int type = 0, bool texture = true, float alpha = 1.0f);
	void renderFlatsImmediate(int type, bool texture, float alpha);
	void renderFlatsVBO(int type, bool texture, float alpha);
	void renderFlatHilight(int index, float fade) const;
	void renderFlatSelection(const ItemSelection& selection, float fade = 1.0f);
	void renderTaggedFlats(vector<MapSector*>& sectors, float fade) const;

	// Moving
	void renderMovingVertices(const vector<mapeditor::Item>& vertices, Vec2d move_vec) const;
	void renderMovingLines(const vector<mapeditor::Item>& lines, Vec2d move_vec) const;
	void renderMovingSectors(const vector<mapeditor::Item>& sectors, Vec2d move_vec) const;
	void renderMovingThings(const vector<mapeditor::Item>& things, Vec2d move_vec);

	// Paste
	void renderPasteThings(vector<MapThing*>& things, Vec2d pos);

	// Object Edit
	void renderObjectEditGroup(ObjectEditGroup* group);

	// VBOs
	void updateVerticesVBO();
	void updateLinesVBO(bool show_direction, float base_alpha);
	void updateFlatsVBO();

	// Misc
	void setScale(double scale)
	{
		view_scale_     = scale;
		view_scale_inv_ = 1.0 / scale;
	}
	void   updateVisibility(Vec2d view_tl, Vec2d view_br);
	void   forceUpdate(float line_alpha = 1.0f);
	double scaledRadius(int radius) const;
	bool   visOK() const;
	void   clearTextureCache() { tex_flats_.clear(); }

private:
	SLADEMap* map_ = nullptr;
	// unsigned  tex_last_         = 0;
	long vertices_updated_ = 0;
	long lines_updated_    = 0;
	long flats_updated_    = 0;

	// VBOs etc
	unsigned vbo_vertices_ = 0;
	unsigned vbo_lines_    = 0;
	unsigned vbo_flats_    = 0;

	// Display lists
	unsigned list_vertices_ = 0;
	unsigned list_lines_    = 0;

	// Visibility
	enum
	{
		VIS_LEFT  = 1,
		VIS_RIGHT = 2,
		VIS_ABOVE = 4,
		VIS_BELOW = 8,
		VIS_SMALL = 16,
	};
	vector<uint8_t> vis_v_;
	vector<uint8_t> vis_l_;
	vector<uint8_t> vis_t_;
	vector<uint8_t> vis_s_;

	// Structs
	struct GLVert
	{
		float x, y;
		float r, g, b, a;
	};
	struct GLLine
	{
		GLVert v1, v2;   // The line itself
		GLVert dv1, dv2; // Direction tab
	};

	// Other
	bool     lines_dirs_     = false;
	unsigned n_vertices_     = 0;
	unsigned n_lines_        = 0;
	unsigned n_things_       = 0;
	double   view_scale_     = 0.;
	double   view_scale_inv_ = 0.;
	bool     things_angles_  = false;

	vector<unsigned> tex_flats_;
	int              last_flat_type_ = -1;
	vector<unsigned> thing_sprites_;
	long             thing_sprites_updated_ = 0;

	// Thing paths
	enum class PathType
	{
		Normal,
		NormalBoth,
		Dragon,
		DragonBoth
	};
	struct ThingPath
	{
		unsigned from_index;
		unsigned to_index;
		PathType type;
	};
	vector<ThingPath> thing_paths_;
	long              thing_paths_updated_ = 0;
};
} // namespace slade
