#ifndef DOWNLOAD_LIST_MODEL_H
#define DOWNLOAD_LIST_MODEL_H

class DownloadListModel {

private:
	DownloadListModel(const DownloadListModel& rhs);
	DownloadListModel& operator=(const DownloadListModel& rhs);

public:
	DownloadListModel();
	virtual ~DownloadListModel();

};

#endif // DOWNLOAD_LIST_MODEL_H
