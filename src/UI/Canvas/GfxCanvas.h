#pragma once

#include "Graphics/SImage/SImage.h"
#include "OGLCanvas.h"
#include "OpenGL/GLTexture.h"

namespace slade
{
class SImage;
class SBrush;
class GLTexture;
class Translation;

class GfxCanvas : public OGLCanvas
{
public:
	enum class View
	{
		Default,
		Centered,
		Sprite,
		HUD,
		Tiled
	};

	enum class EditMode
	{
		None,
		Paint,
		Erase,
		Translate
	};

	GfxCanvas(wxWindow* parent, int id);
	~GfxCanvas() = default;

	SImage& image() { return image_; }

	void    setViewType(View type) { view_type_ = type; }
	View    viewType() const { return view_type_; }
	void    setScale(double scale);
	bool    allowDrag() const { return allow_drag_; }
	void    allowDrag(bool allow) { allow_drag_ = allow; }
	bool    allowScroll() const { return allow_scroll_; }
	void    allowScroll(bool allow) { allow_scroll_ = allow; }
	void    setPaintColour(const ColRGBA& col) { paint_colour_.set(col); }
	void    setEditingMode(EditMode mode) { editing_mode_ = mode; }
	void    setTranslation(Translation* tr) { translation_ = tr; }
	void    setBrush(SBrush* br) { brush_ = br; }
	SBrush* brush() const { return brush_; }
	ColRGBA paintColour() const { return paint_colour_; }

	void draw() override;
	void drawImage();
	void drawOffsetLines() const;
	void updateImageTexture();
	void endOffsetDrag();
	void paintPixel(int x, int y);
	void brushCanvas(int x, int y);
	void pickColour(int x, int y);
	void generateBrushShadow();

	void zoomToFit(bool mag = true, double padding = 0.0f);
	void resetOffsets() { offset_.x = offset_.y = 0; }

	bool  onImage(int x, int y) const;
	Vec2i imageCoords(int x, int y) const;

private:
	SImage       image_;
	View         view_type_ = View::Default;
	double       scale_     = 1.;
	Vec2d        offset_; // panning offsets (not image offsets)
	unsigned     tex_image_      = 0;
	bool         update_texture_ = false;
	bool         image_hilight_  = false;
	bool         allow_drag_     = false;
	bool         allow_scroll_   = false;
	Vec2i        drag_pos_       = { 0, 0 };
	Vec2i        drag_origin_    = { -1, -1 };
	Vec2i        mouse_prev_;
	EditMode     editing_mode_ = EditMode::None;
	ColRGBA      paint_colour_ = ColRGBA::BLACK; // the colour to apply to pixels in editing mode 1
	Translation* translation_  = nullptr;        // the translation to apply to pixels in editing mode 3
	bool         drawing_      = false;          // true if a drawing operation is ongoing
	bool*        drawing_mask_ = nullptr;        // keeps track of which pixels were already modified in this pass
	SBrush*      brush_        = nullptr;        // the brush used to paint the image
	Vec2i        cursor_pos_   = { -1, -1 };     // position of cursor, relative to image
	Vec2i        prev_pos_     = { -1, -1 };     // previous position of cursor
	unsigned     tex_brush_    = 0;              // preview the effect of the brush

	// Signal connections
	sigslot::scoped_connection sc_image_changed_;

	// Events
	void onMouseLeftDown(wxMouseEvent& e);
	void onMouseRightDown(wxMouseEvent& e);
	void onMouseLeftUp(wxMouseEvent& e);
	void onMouseMovement(wxMouseEvent& e);
	void onMouseLeaving(wxMouseEvent& e);
	void onKeyDown(wxKeyEvent& e);
};
} // namespace slade

DECLARE_EVENT_TYPE(wxEVT_GFXCANVAS_OFFSET_CHANGED, -1)
DECLARE_EVENT_TYPE(wxEVT_GFXCANVAS_PIXELS_CHANGED, -1)
DECLARE_EVENT_TYPE(wxEVT_GFXCANVAS_COLOUR_PICKED, -1)
