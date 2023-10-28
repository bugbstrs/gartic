export module Config;

import <string>;

namespace Config {
	// File related
	export const std::string dictionaryFilePath = "./words.txt";
	// export std::string SQLiteFilePath = "";
	// export std::string logFilePath = "";

	// Timer related
	export const int defaultMinutes = 1;
	export const int defaultResolution = 12;
}