#include "stdafx.h"
#include "EngineVersion.h"
#include "AlteryxAbacus.h"
#include "AlteryxAbacusUtils.h"
#include <cmath>

std::array<int, 4> EngineVersion::versionParts{ -1, 0, 0, 0 };

std::wstring EngineVersion::dllPath;

std::wstring EngineVersion::GetEnginePath()
{
	if (!dllPath.empty())
	{
		return dllPath;
	}

	WCHAR fileName[MAX_PATH];
	GetModuleFileNameW(nullptr, fileName, MAX_PATH);
	dllPath = std::wstring(fileName);
	return GetEnginePath();
}

std::array<int, 4> EngineVersion::GetEngineVersion()
{
	if (versionParts[0] != -1)
	{
		return versionParts;
	}

	WCHAR fileName[MAX_PATH];
	GetModuleFileNameW(nullptr, fileName, MAX_PATH);

	DWORD handle = 0;
	DWORD size = GetFileVersionInfoSize(fileName, &handle);

	BYTE* versionInfo = new BYTE[size];
	if (GetFileVersionInfoW(fileName, 0, size, versionInfo))
	{
		UINT len = 0;
		VS_FIXEDFILEINFO* vsfi = nullptr;
		VerQueryValue(versionInfo, L"\\", reinterpret_cast<void**>(&vsfi), &len);
		versionParts[0] = HIWORD(vsfi->dwFileVersionMS);
		versionParts[1] = LOWORD(vsfi->dwFileVersionMS);
		versionParts[2] = HIWORD(vsfi->dwFileVersionLS);
		versionParts[3] = LOWORD(vsfi->dwFileVersionLS);
	}

	delete[] versionInfo;
	return versionParts;
}

//// a way to error a function from XML
extern "C" long _declspec(dllexport) _stdcall Version(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	if (nNumArgs > 2 || (nNumArgs > 0 && pArgs[0].nVarType != 1) || (nNumArgs > 1 && pArgs[1].nVarType != 1))
	{
		return AlteryxAbacusUtils::ReturnError(L"Arguments: [MajorIndex (1-4)] [MinorIndex (1-4)]", pReturnValue, nNumArgs, pArgs);
	}

	auto version = EngineVersion::GetEngineVersion();
	int major = version[0];
	int minor = version[1];

	if (nNumArgs > 0 && 1 == pArgs[0].nVarType)
	{
		auto idx = pArgs[0].isNull ? -1 : (static_cast<int>(pArgs[0].dVal) - 1);
		if (idx < -1 || idx > 3)
		{
			return AlteryxAbacusUtils::ReturnError(L"Argument 1 Outside of version parts range (1 - 4)", pReturnValue, nNumArgs, pArgs);
		}

		major = version[idx];
		minor = 0;
	}
	if (2 == nNumArgs && 1 == pArgs[1].nVarType)
	{
		auto idx = pArgs[1].isNull ? -1 : (static_cast<int>(pArgs[1].dVal) - 1);
		if (idx < -1 || idx > 3)
		{
			return AlteryxAbacusUtils::ReturnError(L"Argument 2 Outside of version parts range (1 - 4)", pReturnValue, nNumArgs, pArgs);
		}

		minor = version[idx];
	}

	pReturnValue->isNull = 0;
	pReturnValue->dVal = major + (minor ? minor / std::pow(10, ceil(std::log10(minor))) : 0.0);
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

//// a way to error a function from XML
extern "C" long _declspec(dllexport) _stdcall EnginePath(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = 1;

	if (1 == nNumArgs && 1 == pArgs[0].nVarType)
	{
		auto idx = static_cast<int>(pArgs[0].dVal) - 1;

	}
	AlteryxAbacusUtils::SetString(pReturnValue, EngineVersion::GetEnginePath().c_str());
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}
