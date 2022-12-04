#pragma once

#include "Archive/Archive.h"

namespace slade
{
class WolfArchive : public TreelessArchive
{
public:
	WolfArchive() : TreelessArchive("wolf") {}
	~WolfArchive() = default;

	// Wolf3D specific
	uint32_t getEntryOffset(ArchiveEntry* entry) const;
	void     setEntryOffset(ArchiveEntry* entry, uint32_t offset) const;

	// Opening
	bool open(string_view filename) override; // Open from File
	bool open(MemChunk& mc) override;         // Open from MemChunk

	bool openAudio(MemChunk& head, MemChunk& data);
	bool openGraph(MemChunk& head, MemChunk& data, MemChunk& dict);
	bool openMaps(MemChunk& head, MemChunk& data);

	// Writing/Saving
	bool write(MemChunk& mc, bool update = true) override; // Write to MemChunk

	// Misc
	bool     loadEntryData(ArchiveEntry* entry) override;
	unsigned numEntries() override { return rootDir()->numEntries(); }

	// Entry addition/removal
	shared_ptr<ArchiveEntry> addEntry(
		shared_ptr<ArchiveEntry> entry,
		unsigned                 position = 0xFFFFFFFF,
		ArchiveDir*              dir      = nullptr) override;
	shared_ptr<ArchiveEntry> addEntry(shared_ptr<ArchiveEntry> entry, string_view add_namespace) override;

	// Entry modification
	bool renameEntry(ArchiveEntry* entry, string_view name, bool force = false) override { return false; }

	static bool isWolfArchive(MemChunk& mc);
	static bool isWolfArchive(const string& filename);

private:
	struct WolfHandle
	{
		uint32_t offset;
		uint16_t size;
	};

	uint16_t spritestart_;
	uint16_t soundstart_;
};
} // namespace slade
