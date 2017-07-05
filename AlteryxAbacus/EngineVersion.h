#ifndef ENGINE_VERSION_H

#define ENGINE_VERSION_H

#include <array>

class EngineVersion
{
	static std::array<int, 4> versionParts;

	static std::wstring dllPath;
public:

	static std::array<int, 4> GetEngineVersion();

	static std::wstring GetEnginePath();
};

#endif