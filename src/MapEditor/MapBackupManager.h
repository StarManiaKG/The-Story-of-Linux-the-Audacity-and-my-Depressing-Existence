#pragma once

namespace slade
{
class ArchiveEntry;
class Archive;
class MapBackupManager
{
public:
	MapBackupManager()  = default;
	~MapBackupManager() = default;

	bool writeBackup(vector<unique_ptr<ArchiveEntry>>& map_data, string_view archive_name, string_view map_name) const;
	Archive* openBackup(string_view archive_name, string_view map_name) const;
};
} // namespace slade
