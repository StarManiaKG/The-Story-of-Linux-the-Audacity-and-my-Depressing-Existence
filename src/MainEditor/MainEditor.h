#pragma once

// Forward declarations
class wxWindow;

namespace slade
{
class Archive;
class ArchiveEntry;
class ArchivePanel;
class EntryPanel;
class MainWindow;
class Palette;

namespace maineditor
{
	enum class NewEntryType
	{
		Empty,
		Text,
		Palette,
		Animated,
		Switches
	};

	bool init();

	MainWindow*           window();
	wxWindow*             windowWx();
	Archive*              currentArchive();
	ArchiveEntry*         currentEntry();
	vector<ArchiveEntry*> currentEntrySelection();
	Palette*              currentPalette(ArchiveEntry* entry = nullptr);
	ArchivePanel*         currentArchivePanel();
	EntryPanel*           currentEntryPanel();

	void openTextureEditor(Archive* archive, ArchiveEntry* entry = nullptr);
	void openMapEditor(Archive* archive);
	void openArchiveTab(Archive* archive);
	void openEntry(ArchiveEntry* entry);

	void setGlobalPaletteFromArchive(Archive* archive);

#ifdef USE_WEBVIEW_STARTPAGE
	void openDocs(string_view page_name = "");
#endif
}; // namespace maineditor
} // namespace slade

// Define for less cumbersome maineditor::window()
#define theMainWindow maineditor::window()
