#include <iostream>
#include <Windows.h>

using namespace std;



typedef char* (__stdcall* f_cypher)(char* source, int key);
HINSTANCE hGetProcIDDLL = LoadLibrary("D:\\VSrepo\\Assignment4\\x64\\Debug\\CaesarCypher.dll");
f_cypher encrypt = (f_cypher)GetProcAddress(hGetProcIDDLL, "encrypt");
f_cypher decrypt = (f_cypher)GetProcAddress(hGetProcIDDLL, "decrypt");

class FileReader {
public:
	static string read(string path) {
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
	static void write(string path, string text) {
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

class Interface : public FileReader, public FileWriter {
public:
	static void Run() {
		cout << "Chose the mode (normal or secret):" << endl;
		string mode = "";
		cin >> mode;
		if (mode == "normal") {
			cout << "Chose the operation (encrypt or decrypt):" << endl;
			string operation = "";
			cin >> operation;
			cout << "Enter input file path:" << endl;
			string inputPath = "";
			cin >> inputPath;
			cout << "Enter output file path:" << endl;
			string outputPath = "";
			cin >> outputPath;
			cout << "Enter encryption key:" << endl;
			int key = 0;
			cin >> key;
			string rText = read(inputPath);
			char* input = (char*)rText.c_str();
			if (operation == "encrypt") {
				char* output = encrypt(input, key);
				write(outputPath, (string)output);
			}
			else if (operation == "decrypt") {
				char* output = decrypt(input, key);
				write(outputPath, (string)output);
			}
		}
		else if (mode == "secret") {

		}
	}
};

int main() {
	Interface* ui = new Interface();
	ui->Run();
	return 0;
}