#include "File.h"

namespace File {
	Str readFile(Str path) {
		ifstream file(path, ios::ate | ios::binary);

		if (!file) {
			cerr << path << " not found!\n";
			return nullptr;
		}

		int size = file.tellg();
		file.seekg(0);

		char* source = new char[size + 1];

		file.read(source, size);
		source[size] = '\0';

		file.close();

		return source;
	}
}