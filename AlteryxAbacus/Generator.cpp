#include "stdafx.h"
#include "AlteryxAbacus.h"
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include "AlteryxAbacusUtils.h"
#include <array>

const std::wstring upper = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::wstring lower = L"abcdefghijklmnopqrstuvwxyz";
const std::wstring number = L"0123456789";

static std::random_device rd;
static std::mt19937 mt19937(rd());

static int getUniformInt(int max)
{
	return std::uniform_int_distribution<int>(0, max)(mt19937);
}

static auto getCharacter(std::wstring input)
{
	if (input.length() == 0)
	{
		return L'?';
	}
	return input[getUniformInt(input.length()-1)];
}

static std::vector<std::wstring> &splitStrW(const std::wstring &InputString, wchar_t delimiterChar, std::vector<std::wstring> &ResultVec) {
	std::wstringstream sStream(InputString);
	std::wstring item;

	while (std::getline(sStream, item, delimiterChar)) {
		ResultVec.push_back(item);
	}

	return ResultVec;
}

static int parseInt(const std::wstring &InputString)
{
	std::size_t index = 0;
	try {
		const auto result = std::stoi(InputString, &index);
		if (index == InputString.length()) {
			return result;
		}
	} catch(...)
	{		
	}

	return -1;
}

static std::wstring createFromStandard(std::wstring const& pattern)
{
	const auto length = pattern.length();
	std::wstringstream output;

	for (auto i = 0LLU; i < length; i++) {
		switch (pattern[i])
		{
		case L'A':
			output << getCharacter(upper);
			break;
		case L'a':
			output << getCharacter(lower);
			break;
		case L'#':
			output << getCharacter(number);
			break;
		default:
			output << pattern[i];
			break;
		}
	}

	return output.str();
}

static std::wstring createFromCharset(std::wstring const& pattern, std::vector<std::wstring> const& charsets)
{
	const auto length = pattern.length();
	const int setscount = charsets.size();
	std::wstringstream output;

	for (auto i = 0LLU; i < length; i++) {
		int index = -1;
		if (pattern[i] >= L'0' && pattern[i] <= L'9')
		{
			index = static_cast<int>(pattern[i] - L'0');
		} else if (pattern[i] >= L'A' && pattern[i] <= L'Z')
		{
			index = static_cast<int>(pattern[i] - L'A') + 10;
		}

		if (index >= 0 && setscount > index)
		{
			output << getCharacter(charsets[index]);
		} else
		{
			output << pattern[i];
		}
	}

	return output.str();
}

extern "C" long _declspec(dllexport) _stdcall RandomStringFromTemplate(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = nVarType_WCHAR;

	if (nNumArgs < 1 || nVarType_WCHAR != pArgs[0].nVarType)
	{
		return AlteryxAbacusUtils::ReturnError(L"Arguments: [Pattern]", pReturnValue, nNumArgs, pArgs);
	}

	const std::wstring pattern(pArgs[0].pVal);
	
	if (1 == nNumArgs) 
	{
		std::wstring output = createFromStandard(pattern);
		AlteryxAbacusUtils::SetString(pReturnValue, output.c_str());
	}
	else
	{
		std::vector<std::wstring> charsets(nNumArgs - 1);
		for (auto i = 1; i < nNumArgs; i++)
		{
			if (nVarType_DOUBLE == pArgs[i].nVarType)
			{
				return AlteryxAbacusUtils::ReturnError(L"Arguments: [Pattern] [CharSet1] ... [CharSetN]", pReturnValue, nNumArgs, pArgs);
			}

			const std::wstring tmp(pArgs[i].pVal);
			charsets.push_back(tmp);
		}

		std::wstring output = createFromCharset(pattern, charsets);
		AlteryxAbacusUtils::SetString(pReturnValue, output.c_str());
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall RandomIPAddress(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = nVarType_WCHAR;

	if (nNumArgs > 1 || (nNumArgs == 1 && nVarType_WCHAR != pArgs[0].nVarType))
	{
		return AlteryxAbacusUtils::ReturnError(L"Arguments: [CIDR]", pReturnValue, nNumArgs, pArgs);
	}

	const std::wstring CIDR = nNumArgs == 1 ? std::wstring(pArgs[0].pVal) : L"0.0.0.0/0";
	std::vector<std::wstring> cidr_parts;
	splitStrW(CIDR, L'/', cidr_parts);

	if (cidr_parts.size() != 2)
	{
		return AlteryxAbacusUtils::ReturnError(L"Invalid CIDR passed", pReturnValue, nNumArgs, pArgs);
	}

	int range;
	if ((range = parseInt(cidr_parts[1])) < 0 || range > 32)
	{
		return AlteryxAbacusUtils::ReturnError(L"Invalid CIDR mask value passed", pReturnValue, nNumArgs, pArgs);
	}

	std::vector<std::wstring> ip_parts;
	splitStrW(cidr_parts[0], L'.', ip_parts);
	std::array<int, 4> ip_numbers{};
	if (ip_parts.size() != 4 ||
		(ip_numbers[0] = parseInt(ip_parts[0])) < 0 || ip_numbers[0] > 255 ||
		(ip_numbers[1] = parseInt(ip_parts[1])) < 0 || ip_numbers[0] > 255 ||
		(ip_numbers[2] = parseInt(ip_parts[2])) < 0 || ip_numbers[0] > 255 ||
		(ip_numbers[3] = parseInt(ip_parts[3])) < 0 || ip_numbers[0] > 255
		)
	{
		return AlteryxAbacusUtils::ReturnError(L"Invalid IP Address passed", pReturnValue, nNumArgs, pArgs);
	}

	std::wstringstream output;
	for (auto i = 0; i < 4; i++)
	{
		const int mask = getUniformInt((1 << std::max<int>(8 - range, 0)) - 1);
		range = max(0, range - 8);

		output << ip_numbers[i] + mask;

		if (i < 3)
		{
			output << L'.';
		}
	}

	AlteryxAbacusUtils::SetString(pReturnValue, output.str().c_str());
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}