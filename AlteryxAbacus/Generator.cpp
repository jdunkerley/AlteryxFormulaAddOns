#include "stdafx.h"
#include "AlteryxAbacus.h"
#include <string>
#include <random>
#include <vector>
#include "AlteryxAbacusUtils.h"
#include <array>

static std::random_device rd;
static std::mt19937_64 rand_generator(rd());

template <class T>
static T getUniformInt(T min, T max)
{
	return std::uniform_int_distribution<T>(min, max)(rand_generator);
}

static auto getCharacter(wchar_t const* input, const size_t length)
{
	if (length == 0)
	{
		return L'\0';
	}

	return input[getUniformInt<size_t>(0, length - 1u)];
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
	const auto sets_count = charsets.size();

	for (auto i = 0LLU; i < length; i++) {
		auto index = -1;
		if (pattern[i] >= L'0' && pattern[i] <= L'9')
		{
			index = static_cast<int>(pattern[i] - L'0');
		} else if (pattern[i] >= L'A' && pattern[i] <= L'Z')
		{
			index = static_cast<int>(pattern[i] - L'A') + 10;
		}

		if (index >= 0 && sets_count > index)
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

extern "C" long _declspec(dllexport) _stdcall RandomSeed(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = nVarType_DOUBLE;

	if (nNumArgs > 1 || pArgs[0].nVarType != nVarType_DOUBLE)
	{
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnError(L"RandomSeed Arguments: <Seed:Number>", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->isNull = false;
	pReturnValue->dVal = -1;

	if (nNumArgs == 0 || pArgs[0].isNull)
	{
		rand_generator.seed(rd());
	}
	else if (nNumArgs == 1 && pArgs[0].nVarType == nVarType_DOUBLE)
	{
		rand_generator.seed(static_cast<unsigned long long>(pArgs[0].dVal));
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall Random(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = nVarType_DOUBLE;

	pReturnValue->isNull = false;
	pReturnValue->dVal = std::uniform_real_distribution<double>(0, 1)(rand_generator);
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall RandomInt(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = nVarType_DOUBLE;

	if (nNumArgs < 1 || nNumArgs > 2 || pArgs[0].nVarType != nVarType_DOUBLE || (nNumArgs == 2 && pArgs[1].nVarType != nNumArgs))
	{
		pReturnValue->isNull = true;
		return AlteryxAbacusUtils::ReturnError(L"RandomInt Arguments: [Min:Number] <Max:Number>", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->isNull = false;
	if (pArgs[0].isNull || (nNumArgs == 2 && pArgs[1].isNull))
	{
		pReturnValue->isNull = true;
	}
	else if (nNumArgs == 1)
	{
		pReturnValue->dVal = static_cast<double>(getUniformInt<long long>(0, static_cast<long long>(pArgs[0].dVal)));
	}
	else
	{
		pReturnValue->dVal = static_cast<double>(getUniformInt<long long>(static_cast<long long>(pArgs[0].dVal), static_cast<long long>(pArgs[1].dVal)));
	}
	
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
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
		const auto size = static_cast<unsigned long long>(nNumArgs) - 1ULL;
		std::vector<const wchar_t*> charsets(size);
		std::vector<size_t> lengths(size);
		for (auto i = 1ULL; i <= size; i++)
		{
			if (nVarType_DOUBLE == pArgs[i].nVarType)
			{
				return AlteryxAbacusUtils::ReturnError(L"Arguments: [Pattern] [CharSet1] ... [CharSetN]", pReturnValue, nNumArgs, pArgs);
			}

			if (pArgs[i].isNull)
			{
				charsets[i - 1ULL] = L"";
				lengths[i - 1ULL] = 0;
			}
			else {
				charsets[i - 1ULL] = pArgs[i].pVal;
				lengths[i - 1ULL] = wcslen(pArgs[i].pVal);
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
		const int ip = cidr_parts[i] + getUniformInt(0, (1 << std::max<int>(8 - range, 0)) - 1);
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
	const int randomItem = getUniformInt(0, nNumArgs - 1);

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