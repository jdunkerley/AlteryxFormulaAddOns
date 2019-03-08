#include "stdafx.h"
#include "AlteryxAbacus.h"
#include <string>
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

static void createFromStandard(wchar_t const* pattern, const size_t length, wchar_t * output)
{
	static const wchar_t* upper = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static const size_t upper_length = wcslen(upper);
	static const wchar_t* lower = L"abcdefghijklmnopqrstuvwxyz";
	static const size_t lower_length = wcslen(lower);
	static const wchar_t* number = L"0123456789";
	static const size_t number_length = wcslen(number);

	for (auto i = 0LLU; i < length; i++) {
		switch (pattern[i])
		{
		case L'A':
			output[i] = getCharacter(upper, upper_length);
			break;
		case L'a':
			output[i] = getCharacter(lower, lower_length);
			break;
		case L'#':
			output[i] = getCharacter(number, number_length);
			break;
		default:
			output[i] = pattern[i];
			break;
		}
	}

	output[length] = '\0';
}

static void createFromCharset(wchar_t const* pattern, const size_t length, std::vector<const wchar_t*> const& charsets, std::vector<size_t> const& lengths, wchar_t * output)
{
	const auto setscount = charsets.size();

	for (auto i = 0LLU; i < length; i++) {
		auto index = -1;
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
				output[0] = new_char;
				return;
			}
			output[i] = new_char;
		} else
		{
			output[i] = pattern[i];
		}
	}

	output[length] = '\0';
}

extern "C" long _declspec(dllexport) _stdcall RandomString(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
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

	auto *pStringRet = static_cast<wchar_t *>(GlobalAlloc(GMEM_FIXED, (pattern_size + 1) * sizeof(wchar_t)));

	if (1 == nNumArgs) 
	{
		createFromStandard(pArgs[0].pVal, pattern_size, pStringRet);
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
				charsets[i-1] = L"";
				lengths[i-1] = 0;
			}
			else {
				charsets[i-1] = pArgs[i].pVal;
				lengths[i-1] = wcslen(pArgs[i].pVal);
			}
		}

		createFromCharset(pArgs[0].pVal, pattern_size, charsets, lengths, pStringRet);
		if (pStringRet[0] == 0) {
			pReturnValue->isNull = true;
		}
	}

	pReturnValue->pVal = pStringRet;
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall RandomIPAddress(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	pReturnValue->nVarType = nVarType_WCHAR;

	if (nNumArgs > 1 || (nNumArgs == 1 && nVarType_WCHAR != pArgs[0].nVarType))
	{
		return AlteryxAbacusUtils::ReturnError(L"Arguments: [CIDR]", pReturnValue, nNumArgs, pArgs);
	}

	if (nNumArgs == 1 && pArgs[0].isNull)
	{
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	std::array<int, 5> cidr_parts{};
	if (nNumArgs == 0)
	{
		cidr_parts[0] = 0;
		cidr_parts[1] = 0;
		cidr_parts[2] = 0;
		cidr_parts[3] = 0;
		cidr_parts[4] = 0;
	}
	else
	{
		const auto cidr = pArgs[0].pVal;
		wchar_t *end;
		if (cidr[0] < L'0' || cidr[0] > L'9' || (cidr_parts[0] = wcstoul(cidr, &end, 10)) > 255 || *end != L'.' ||
			end[1] < L'0' || end[1] > L'9' || (cidr_parts[1] = wcstoul(end + 1, &end, 10)) > 255 || *end != L'.' ||
			end[1] < L'0' || end[1] > L'9' || (cidr_parts[2] = wcstoul(end + 1, &end, 10)) > 255 || *end != L'.' ||
			end[1] < L'0' || end[1] > L'9' || (cidr_parts[3] = wcstoul(end + 1, &end, 10)) > 255 || *end != L'/' ||
			end[1] < L'0' || end[1] > L'9' || (cidr_parts[4] = wcstoul(end + 1, &end, 10)) > 32 || *end != L'\0')
		{
			return AlteryxAbacusUtils::ReturnError(L"Invalid CIDR passed", pReturnValue, nNumArgs, pArgs);
		}
	}

	auto range = cidr_parts[4];
	auto *pStringRet = static_cast<wchar_t *>(GlobalAlloc(GMEM_FIXED, 16 * sizeof(wchar_t)));
	wchar_t *end = pStringRet;
	for (auto i = 0; i < 4; i++)
	{
		const int ip = cidr_parts[i] + getUniformInt((1 << std::max<int>(8 - range, 0)) - 1);
		range = max(0, range - 8);
		_itow_s(ip, end, 16 * sizeof(wchar_t), 10);
		end += (ip < 10 ? 2 : (ip < 100 ? 3 : 4));
		*(end - 1) = L'.';
	}
	*(end - 1) = L'\0';

	pReturnValue->pVal = pStringRet;
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall RandomItem(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
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