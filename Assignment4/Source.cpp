#include <iostream>

using namespace std;

class FileReader {
public:
	string read(string path) {
		FILE* myFile;
		const char* cPath = path.c_str();
		fopen_s(&myFile, cPath, "r");
		if (myFile == NULL) {
			throw exception();
			return "";
		}
		char symbol;
		string output = "";
		while ((symbol = fgetc(myFile)) != EOF) {
			output += symbol;
		}
		fclose(myFile);
		return output;
	}
};

class FileWriter {
public:
	void write(string path, string text) {
		FILE* myFile;
		const char* cPath = path.c_str();
		fopen_s(&myFile, cPath, "w");
		if (myFile == NULL) {
			throw exception();
			return;
		}
		char symbol;
		fprintf(myFile, "%s", text.c_str());
		fflush(myFile);
		fclose(myFile);
		return;
	}
};

int main() {
	FileReader* reader = new FileReader;
	FileWriter* writer = new FileWriter;
	writer->write("D:\\VSrepo\\doc.txt", "text++");
	cout << reader->read("D:\\VSrepo\\doc.txt");
	return 0;
}