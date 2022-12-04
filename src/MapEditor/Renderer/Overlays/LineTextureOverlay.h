#pragma once

#include "MCOverlay.h"

namespace slade
{
class MapLine;
class MapSide;

class LineTextureOverlay : public MCOverlay
{
public:
	LineTextureOverlay()  = default;
	~LineTextureOverlay() = default;

	void openLines(vector<MapLine*>& list);
	void close(bool cancel) override;
	void update(long frametime) override;

	// Drawing
	void updateLayout(int width, int height);
	void draw(int width, int height, float fade) override;

	// Input
	void mouseMotion(int x, int y) override;
	void mouseLeftClick() override;
	void mouseRightClick() override;
	void keyDown(string_view key) override;

private:
	vector<MapLine*> lines_;
	int              selected_side_ = 0;

	struct TexInfo
	{
		Vec2i          position;
		bool           hover;
		vector<string> textures;
		bool           changed;

		TexInfo()
		{
			hover   = false;
			changed = false;
		}

		void checkHover(int x, int y, int halfsize)
		{
			if (x >= position.x - halfsize && x <= position.x + halfsize && y >= position.y - halfsize
				&& y <= position.y + halfsize)
				hover = true;
			else
				hover = false;
		}
	};

	// Texture info
	enum
	{
		FrontUpper = 0,
		FrontMiddle,
		FrontLower,
		BackUpper,
		BackMiddle,
		BackLower,
	};
	TexInfo textures_[6];
	bool    side1_ = false;
	bool    side2_ = false;

	// Drawing info
	int tex_size_    = 0;
	int last_width_  = 0;
	int last_height_ = 0;

	// Helper functions
	void addTexture(TexInfo& inf, string_view texture) const;
	void drawTexture(float alpha, int size, TexInfo& tex, string_view position) const;
	void browseTexture(TexInfo& tex, string_view position);
};
} // namespace slade
