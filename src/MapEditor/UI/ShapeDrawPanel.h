#pragma once

class wxBoxSizer;

namespace slade
{
class ShapeDrawPanel : public wxPanel
{
public:
	ShapeDrawPanel(wxWindow* parent);
	~ShapeDrawPanel() = default;

	void showShapeOptions(int shape);

private:
	wxChoice*   choice_shape_ = nullptr;
	wxCheckBox* cb_centered_  = nullptr;
	wxCheckBox* cb_lockratio_ = nullptr;
	wxBoxSizer* sizer_main_   = nullptr;
	wxSpinCtrl* spin_sides_   = nullptr;
	wxPanel*    panel_sides_  = nullptr;
};
} // namespace slade
