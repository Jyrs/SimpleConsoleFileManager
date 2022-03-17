

#include<iostream>
#include<fstream>
#include<string>
#include<filesystem>
#include<algorithm>


using namespace std;
namespace fs = std::filesystem;




void showMenu()
{
	cout << "\n 1. Create file\n 2. Rename file\n 3. Delete file\n 4. copy file\n 5. Show file\n 9. <\n 0. >";
}


void showFileDirectory(const fs::path& p)
{

	cout << "-----------------------------------\n";
	cout << "cur path:" << p << endl;
	cout << "-----------------------------------\n";
	cout << setiosflags(ios::left);
	cout << setw(40) << "  Name" << setw(20) << "Size(Kb)" << setw(20) << "Type\n";
	cout << "-----------------------------------\n";
	for (auto curPath : fs::directory_iterator(fs::current_path())) {
		if (curPath.is_directory())
			cout << " > " << setw(40) << curPath.path().filename() << setw(20)
			<< curPath.file_size() << setw(10) << "folder" << endl;
	}
	for (auto curPath : fs::directory_iterator(fs::current_path())) {
		if (curPath.is_regular_file())
			cout << "   " << setw(40) << curPath.path().filename() << setw(20)
			<< curPath.file_size() << setw(10) << "file" << endl;
	}
}
void ShowFile(const fs::path& p)
{
	string fileShow;

	cout << "Enter filename: ";
	cin >> fileShow;
	if (fs::exists(fileShow))
	{
		ifstream txtFile(p.string() + "\\" + fileShow);
		if (txtFile.is_open()) {
			while (!txtFile.eof()) {
				string tmp;
				getline(txtFile, tmp);
				cout << tmp << endl;
			}
			txtFile.close();
		}
		else
		{
			cout << "The file cannot be opened or it does not exist.\n";
		}
	}
	else cout << "\nDirectory not found";

}

void selectNextDirectory(fs::path& p)
{
	string folderName;
	cin >> folderName;
	if (fs::exists(folderName))
	{
		fs::current_path(folderName);
	}
	else cout << "\nDirectory not found";
}

void renameFile(fs::path& p)
{
	string lastName;
	string nameForRename;
	cin >> lastName;
	cin >> nameForRename;
	if (fs::exists(lastName))
		fs::rename(lastName, nameForRename);
	else cout << "\nDirectory not found";
}

void createFile()
{
	string newFolderName;
	cin >> newFolderName;
	if (!fs::exists(newFolderName))
		cout << fs::create_directory(newFolderName) ? "Directory create succesful \n" : "Directory create error\n";
	else  cout << "Object not found\n";
}
void deleteFile()
{
	string deleteFolderName;
	cin >> deleteFolderName;
	if (fs::exists(deleteFolderName))
		cout << fs::remove(deleteFolderName) ? "Object delete succesful \n" : "Directory delete error\n";
	else cout << "Object not found\n";
}

void copyFile()
{
	string copyPathNameFrom;
	string copyPathNameTo;
	cin >> copyPathNameFrom;
	cin >> copyPathNameTo;
	if (!fs::exists(copyPathNameFrom)) {
		fs::copy(copyPathNameFrom, copyPathNameTo);
		cout << "A copy was created in the specified directory\n";
	}
	else cout << "Object not found\n";
}



int main()
{
	fs::path currentPath = fs::current_path();
	string varMenu;
	while (true)
	{
		system("cls");
		showFileDirectory(currentPath);
		showMenu();
		cout << "\nSelect a number from the menu: ";
		cin >> varMenu;
		if (varMenu == "1" || varMenu == "create") createFile();
		else if (varMenu == "2" || varMenu == "rename") renameFile(currentPath);
		else if (varMenu == "3" || varMenu == "delete") deleteFile();
		else if (varMenu == "4" || varMenu == "copy") copyFile();
		else if (varMenu == "5" || varMenu == "show") ShowFile(currentPath);
		else if (varMenu == "9" || varMenu == "<") { fs::current_path("../"); currentPath = fs::current_path(); }
		else if (varMenu == "0" || varMenu == ">") selectNextDirectory(currentPath);
		else cout << "Incorrect!\n";

		system("pause");
	}
	return 0;
}