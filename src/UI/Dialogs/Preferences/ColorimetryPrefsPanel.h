#pragma once

#include "PrefsPanelBase.h"

class wxSpinCtrlDouble;

namespace slade
{
class ColorimetryPrefsPanel : public PrefsPanelBase
{
public:
	ColorimetryPrefsPanel(wxWindow* parent);
	~ColorimetryPrefsPanel() = default;

	void init() override;
	void applyPreferences() override;

private:
	wxSpinCtrlDouble* spin_grey_r_            = nullptr;
	wxSpinCtrlDouble* spin_grey_g_            = nullptr;
	wxSpinCtrlDouble* spin_grey_b_            = nullptr;
	wxSpinCtrlDouble* spin_factor_r_          = nullptr;
	wxSpinCtrlDouble* spin_factor_g_          = nullptr;
	wxSpinCtrlDouble* spin_factor_b_          = nullptr;
	wxSpinCtrlDouble* spin_factor_h_          = nullptr;
	wxSpinCtrlDouble* spin_factor_s_          = nullptr;
	wxSpinCtrlDouble* spin_factor_l_          = nullptr;
	wxSpinCtrlDouble* spin_tristim_x_         = nullptr;
	wxSpinCtrlDouble* spin_tristim_z_         = nullptr;
	wxSpinCtrlDouble* spin_cie_kl_            = nullptr;
	wxSpinCtrlDouble* spin_cie_k1_            = nullptr;
	wxSpinCtrlDouble* spin_cie_k2_            = nullptr;
	wxSpinCtrlDouble* spin_cie_kc_            = nullptr;
	wxSpinCtrlDouble* spin_cie_kh_            = nullptr;
	wxChoice*         choice_colmatch_        = nullptr;
	wxChoice*         choice_presets_grey_    = nullptr;
	wxChoice*         choice_presets_tristim_ = nullptr;

	void setupLayout();

	// Events
	void onChoiceGreyscalePresetSelected(wxCommandEvent& e);
	void onChoiceTristimPresetSelected(wxCommandEvent& e);
};
} // namespace slade
