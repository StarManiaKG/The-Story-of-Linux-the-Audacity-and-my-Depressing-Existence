#pragma once

namespace slade
{
class ArchiveEntry;

class ModifyOffsetsDialog : public wxDialog
{
public:
	ModifyOffsetsDialog();
	~ModifyOffsetsDialog() override = default;

	Vec2i offset() const;
	int   alignType() const;
	bool  autoOffset() const;
	bool  relativeOffset() const;
	bool  xOffChange() const;
	bool  yOffChange() const;
	Vec2i calculateOffsets(int xoff, int yoff, int width, int height) const;
	bool  apply(ArchiveEntry& entry) const;

private:
	wxChoice* combo_aligntype_ = nullptr;

	wxTextCtrl* entry_xoff_    = nullptr;
	wxTextCtrl* entry_yoff_    = nullptr;
	wxCheckBox* cbox_relative_ = nullptr;

	wxRadioButton* opt_set_  = nullptr;
	wxRadioButton* opt_auto_ = nullptr;

	// Events
	void onOptSet(wxCommandEvent& e);
	void onOptAuto(wxCommandEvent& e);
};
} // namespace slade
