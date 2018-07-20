#include "stdafx.h"
#include "AlteryxAbacus.h"
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include "AlteryxAbacusUtils.h"
#include <array>

static int getUniformInt(int max)
{
	static std::random_device rd;
	static std::mt19937 mt19937(rd());

	return std::uniform_int_distribution<int>(0, max)(mt19937);
}

static auto getCharacter(wchar_t const* input, const size_t length)
{
	if (length == 0)
	{
		return L'\0';
	}
	return input[getUniformInt(length - 1)];
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

static std::wstring createFromStandard(wchar_t const* pattern, const size_t length)
{
	static const wchar_t* upper = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static const size_t upper_length = wcslen(upper);
	static const wchar_t* lower = L"abcdefghijklmnopqrstuvwxyz";
	static const size_t lower_length = wcslen(lower);
	static const wchar_t* number = L"0123456789";
	static const size_t number_length = wcslen(number);

	std::wstringstream output;

	for (auto i = 0LLU; i < length; i++) {
		switch (pattern[i])
		{
		case L'A':
			output << getCharacter(upper, upper_length);
			break;
		case L'a':
			output << getCharacter(lower, lower_length);
			break;
		case L'#':
			output << getCharacter(number, number_length);
			break;
		default:
			output << pattern[i];
			break;
		}
	}

	return output.str();
}

static std::wstring createFromCharset(wchar_t const* pattern, const size_t length, std::vector<const wchar_t*> const& charsets, std::vector<size_t> const& lengths)
{
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
			const auto new_char = getCharacter(charsets[index], lengths[index]);
			if (new_char == L'\0')
			{
				return L"";
			}
			output << new_char;
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

	if (pArgs[0].isNull)
	{
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	const size_t pattern_size = std::wcslen(pArgs[0].pVal);
	if (0 == pattern_size)
	{
		AlteryxAbacusUtils::SetString(pReturnValue, pArgs[0].pVal);
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}
	
	if (1 == nNumArgs) 
	{
		std::wstring output = createFromStandard(pArgs[0].pVal, pattern_size);
		AlteryxAbacusUtils::SetString(pReturnValue, output.c_str());
	}
	else
	{
		std::vector<const wchar_t*> charsets(nNumArgs - 1);
		std::vector<size_t> lengths(nNumArgs - 1);
		for (auto i = 1; i < nNumArgs; i++)
		{
			if (nVarType_DOUBLE == pArgs[i].nVarType)
			{
				return AlteryxAbacusUtils::ReturnError(L"Arguments: [Pattern] [CharSet1] ... [CharSetN]", pReturnValue, nNumArgs, pArgs);
			}

			if (pArgs[i].isNull)
			{
				charsets.emplace_back(L"");
				lengths.emplace_back(0);
			}
			else {
				charsets.emplace_back(pArgs[i].pVal);
				lengths.emplace_back(wcslen(pArgs[i].pVal));
			}
		}

		std::wstring output = createFromCharset(pArgs[0].pVal, pattern_size, charsets, lengths);
		if (output.length() == 0) {
			pReturnValue->isNull = true;
		}
		else {
			AlteryxAbacusUtils::SetString(pReturnValue, output.c_str());
		}
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

	if (pArgs[0].isNull)
	{
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
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

extern "C" long _declspec(dllexport) _stdcall RandomValueFromList(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	if (nNumArgs == 0)
	{
		pReturnValue->nVarType = nVarType_WCHAR;
		return AlteryxAbacusUtils::ReturnError(L"Arguments: [Value1] ... [ValueN]", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = pArgs[0].nVarType;
	const int randomItem = getUniformInt(nNumArgs - 1);

	if (pArgs[randomItem].isNull)
	{
		pReturnValue->isNull = true;
	} else if (pReturnValue->nVarType == nVarType_DOUBLE)
	{
		pReturnValue->dVal = pArgs[randomItem].dVal;
	} else
	{
		AlteryxAbacusUtils::CopyValue(&pArgs[randomItem], pReturnValue);
	}
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}