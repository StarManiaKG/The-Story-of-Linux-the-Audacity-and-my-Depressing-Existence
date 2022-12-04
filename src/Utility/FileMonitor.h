#pragma once

namespace slade
{
class Archive;

class FileMonitor : public wxTimer
{
public:
	FileMonitor(string_view filename, bool start = true);
	virtual ~FileMonitor() = default;

	wxProcess*    process() const { return process_.get(); }
	const string& filename() const { return filename_; }

	virtual void fileModified() {}
	virtual void processTerminated() {}

	void Notify() override;
	void onEndProcess(wxProcessEvent& e);

protected:
	string filename_;
	time_t file_modified_;

private:
	unique_ptr<wxProcess> process_;
};

class DB2MapFileMonitor : public FileMonitor
{
public:
	DB2MapFileMonitor(string_view filename, Archive* archive, string_view map_name);
	~DB2MapFileMonitor() = default;

	void fileModified() override;
	void processTerminated() override;

private:
	Archive* archive_ = nullptr;
	string   map_name_;
};
} // namespace slade
