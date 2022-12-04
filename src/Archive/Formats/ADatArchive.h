#pragma once

#include "Archive/Archive.h"

namespace slade
{
class ADatArchive : public Archive
{
public:
	ADatArchive() : Archive("adat") {}
	~ADatArchive() = default;

	// Opening
	bool open(MemChunk& mc) override; // Open from MemChunk

	// Writing/Saving
	bool write(MemChunk& mc, bool update = true) override;         // Write to MemChunk
	bool write(string_view filename, bool update = true) override; // Write to File

	// Misc
	bool loadEntryData(ArchiveEntry* entry) override;

	// Static functions
	static bool isADatArchive(MemChunk& mc);
	static bool isADatArchive(const string& filename);

private:
	static const int DIRENTRY = 144;
};
} // namespace slade
