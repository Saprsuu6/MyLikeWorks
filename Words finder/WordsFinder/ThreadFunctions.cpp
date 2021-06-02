#include "ThreadFunctions.h"
#include "Regular.h"

void NewFiles(string& text, string& path, size_t& index, MyStruct* strct) {
	text = strct->text;
	path = "New files\\" + strct->fileName;
	index = path.find('.');
	path.insert(index, 1, 'N');
	strct->file->Write(path, text);
}

void MakeReport(string& report, string& temp_path, MyStruct* strct) {
	report = "Path: " + temp_path
		+ "     Size: " + to_string(strct->size)
		+ "     Attribute: " + strct->atribute
		+ "     Amount not accept words: "
		+ to_string(strct->notAcceptWords.size()) + "\n";
	strct->file->Write("Report.txt", report);
	wstring wreport(report.begin(), report.end());
	SendMessage(*strct->window->GethList(), LB_ADDSTRING, 0, LPARAM(wreport.c_str()));
}

void Searching(MyStruct* strct) {	
	ResetEvent(strct->hEvent);

	_finddata_t fileinfo;

	wstring counter;
	intptr_t snapshot_number = _findfirst(strct->path.c_str(), &fileinfo);
	intptr_t success = snapshot_number;

	while (success != -1) {
		if (WaitForSingleObject(strct->mutexWriter, INFINITE) == WAIT_OBJECT_0
			&& WaitForSingleObject(strct->mutexReader, INFINITE) == WAIT_OBJECT_0) {

			string some_name = fileinfo.name;

			if (some_name != "." && some_name != "..") {
				strct->temp_path = strct->path;
				strct->temp_path.replace(strct->temp_path.find("*.*"), 3, "");

				if (fileinfo.attrib & 16) {
					strct->repFileName = some_name;
					strct->fileName = strct->repFileName;
					strct->path = strct->temp_path + some_name + "\\*.*";
					strct->size = fileinfo.size;

					ReleaseMutex(strct->mutexWriter);
					ReleaseMutex(strct->mutexReader);

					strct->counter++;
					Searching(strct);
					strct->counterResult = 100 / strct->counter;
					strct->counter--;

					counter = to_wstring(strct->counterResult) + L'%';
					strct->window->SetProgress(counter);

					strct->repFileName = some_name;
					strct->path.replace(strct->path.find(strct->repFileName + "\\"), strct->repFileName.length() + 1, "");
				}
				else if (fileinfo.attrib & 32) {
					strct->fileName = some_name;
					strct->temp_path += some_name;
					strct->size = fileinfo.size;
					strct->SetAtribute(fileinfo);

					strct->text = strct->file->Read(strct->temp_path);

					SetEvent(strct->hEvent);
				}
			}
		}

		ReleaseMutex(strct->mutexWriter);
		ReleaseMutex(strct->mutexReader);

		success = _findnext(snapshot_number, &fileinfo);		
	}

	if (strct->counterResult == 100) {
		strct->exitTemp = true;
	}

	_findclose(success);
}

void Changing(MyStruct* strct) {
	Regular regex(strct->notAcceptWords.size());
	regex.Fill(*strct);

	string text;
	string path;
	size_t index;
	string report;
	string temp_path;

	if (WaitForSingleObject(strct->hEvent, INFINITE) == WAIT_OBJECT_0) {
		ResetEvent(strct->hEvent);

		while (true) {
			if (strct->exitTemp) {
				break;
			}

			if (WaitForSingleObject(strct->mutexWriter, INFINITE) == WAIT_OBJECT_0) {
				temp_path = strct->temp_path;
				WaitForSingleObject(strct->mutexReader, INFINITE);
			}
			ReleaseMutex(strct->mutexWriter);

			regex.Cheking(strct->text, *strct);
			NewFiles(text, path, index, strct);
			MakeReport(report, temp_path, strct);

			strct->temp_path.replace(strct->temp_path.find(strct->fileName.c_str()), strct->fileName.length(), "");

			SetEvent(strct->hEvent);
			ReleaseMutex(strct->mutexReader);
		}
	}

	strct->window->FinishWork();
}