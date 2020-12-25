#include "stdafx.h"
#include "AlteryxAbacus.h"
#include "AlteryxAbacusUtils.h"
#include <string>
#include <deque>
#include <map>
#include <sstream>

static std::map<std::wstring, std::wstring> stringLookup;
static std::map<std::wstring, double> doubleLookup;
static std::map<std::wstring, std::deque<double>> listLookup;

static size_t get_index(const size_t size, double dVal)
{
	if (dVal < 0)
	{
		const auto shift = static_cast<size_t>(-dVal);
		return shift > size ? size : size - shift;
	}

	return static_cast<size_t>(dVal);
}

extern "C" long _declspec(dllexport) _stdcall VarTextExists(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 1 || nNumArgs > 2 || pArgs[0].nVarType == 1)
	{
		return AlteryxAbacusUtils::ReturnError(L"VarTextExists: Syntax error - key:string argument.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	if (pArgs[0].isNull)
	{
		pReturnValue->isNull = true;
	}
	else
	{
		const std::wstring key(pArgs[0].pVal);
		pReturnValue->isNull = false;
		const auto stringFind = stringLookup.find(key);
		pReturnValue->dVal = stringFind != stringLookup.end();
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarNumExists(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 1 || nNumArgs > 2 || pArgs[0].nVarType == 1)
	{
		return AlteryxAbacusUtils::ReturnError(L"VarNumExists: Syntax error - key:string argument.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	if (pArgs[0].isNull)
	{
		pReturnValue->isNull = true;
	}
	else
	{
		const std::wstring key(pArgs[0].pVal);
		pReturnValue->isNull = false;
		const auto doubleFind = doubleLookup.find(key);
		pReturnValue->dVal = doubleFind != doubleLookup.end();
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarListExists(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 1 || nNumArgs > 2 || pArgs[0].nVarType == 1)
	{
		return AlteryxAbacusUtils::ReturnError(L"VarListExists: Syntax error - key:string argument.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	if (pArgs[0].isNull)
	{
		pReturnValue->isNull = true;
	}
	else
	{
		const std::wstring key(pArgs[0].pVal);
		pReturnValue->isNull = false;
		const auto listFind = listLookup.find(key);
		pReturnValue->dVal = listFind != listLookup.end();
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarText(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 1 || pArgs[0].nVarType == 1 || (nNumArgs > 1 && pArgs[1].nVarType != 2) || (nNumArgs > 2 && pArgs[2].nVarType != 1) || nNumArgs > 3)
	{
		return AlteryxAbacusUtils::ReturnError(L"VarText: Syntax error - key:string [value:string] [setIfTrue:boolean = true] arguments.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 2;
	if (pArgs[0].isNull)
	{
		pReturnValue->isNull = true;
	}
	else
	{
		const std::wstring key(pArgs[0].pVal);

		if (nNumArgs > 1 && (nNumArgs < 3 || pArgs[2].isNull || pArgs[2].dVal != 0))
		{
			if (pArgs[1].isNull)
			{
				stringLookup.erase(key);
			}
			else
			{
				const std::wstring value(pArgs[1].pVal);
				stringLookup[key] = value;
			}
		}

		const auto stringFind = stringLookup.find(key);
		if (stringFind != stringLookup.end())
		{
			AlteryxAbacusUtils::SetString(pReturnValue, stringFind->second.c_str());
		}
		else
		{
			pReturnValue->isNull = true;
		}
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarNum(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 1 || pArgs[0].nVarType == 1 || (nNumArgs > 1 && pArgs[1].nVarType != 1) || (nNumArgs > 2 && pArgs[2].nVarType != 1) || nNumArgs > 3)
	{
		return AlteryxAbacusUtils::ReturnError(L"VarNum: Syntax error - key:string [value:number] [setIfTrue:boolean = true] arguments.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	if (pArgs[0].isNull)
	{
		pReturnValue->isNull = true;
	}
	else
	{
		const std::wstring key(pArgs[0].pVal);

		if (nNumArgs > 1 && (nNumArgs < 3 || pArgs[2].isNull || pArgs[2].dVal != 0))
		{
			if (pArgs[1].isNull)
			{
				doubleLookup.erase(key);
			}
			else
			{
				doubleLookup[key] = pArgs[1].dVal;
			}
		}

		const auto doubleFind = doubleLookup.find(key);
		if (doubleFind != doubleLookup.end())
		{
			pReturnValue->dVal = doubleFind->second;
		}
		else
		{
			pReturnValue->isNull = true;
		}
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarListLength(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 1 || nNumArgs > 2 || pArgs[0].nVarType != 2)
	{
		return AlteryxAbacusUtils::ReturnError(L"VarListLength: Syntax error - key:string argument.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	pReturnValue->isNull = true;
	if (!pArgs[0].isNull)
	{
		const std::wstring key(pArgs[0].pVal);
		const auto listFind = listLookup.find(key);
		if (listFind != listLookup.end())
		{
			pReturnValue->isNull = false;
			pReturnValue->dVal = static_cast<double>(listFind->second.size());
		}
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarListGet(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs != 2 || pArgs[0].nVarType != 2 || pArgs[1].nVarType != 1)
	{
		return AlteryxAbacusUtils::ReturnError(L"VarListGet: Syntax error - key:string index:integer arguments.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	pReturnValue->isNull = true;
	if (!pArgs[0].isNull && !pArgs[1].isNull)
	{
		const std::wstring key(pArgs[0].pVal);
		const auto listFind = listLookup.find(key);
		if (listFind != listLookup.end())
		{
			const auto size = listFind->second.size();
			const auto index = get_index(size, pArgs[1].dVal);
			if (index >= 0 && index < size)
			{
				pReturnValue->isNull = false;
				pReturnValue->dVal = listFind->second[index];
			}
		}
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarListAdd(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 2 || nNumArgs > 3 || pArgs[0].nVarType != 2 || pArgs[1].nVarType != 1 || (nNumArgs > 2 && pArgs[2].nVarType != 1))
	{
		return AlteryxAbacusUtils::ReturnError(L"VarListAdd: Syntax error - key:string [value:number] [setIfTrue:boolean = true] arguments.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	pReturnValue->isNull = true;

	if (nNumArgs == 3 && !pArgs[2].isNull && pArgs[2].dVal == 0)
	{
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	if (!pArgs[0].isNull && !pArgs[1].isNull)
	{
		const std::wstring key(pArgs[0].pVal);
		const auto listFind = listLookup.find(key);
		if (listFind != listLookup.end())
		{
			listFind->second.push_back(pArgs[1].dVal);
		}
		else
		{
			const std::deque<double> vector({ pArgs[1].dVal });
			listLookup[key] = vector;
		}

		pReturnValue->isNull = false;
		pReturnValue->dVal = pArgs[1].dVal;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarListSet(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 3 || nNumArgs > 4 || pArgs[0].nVarType != 2 || pArgs[1].nVarType != 1 || pArgs[2].nVarType != 1 || (nNumArgs == 4 && pArgs[3].nVarType != 1))
	{
		return AlteryxAbacusUtils::ReturnError(L"VarListSet: Syntax error - key:string index:integer value:number [setIfTrue:boolean = true] arguments.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	pReturnValue->isNull = true;

	if (nNumArgs == 4 && !pArgs[3].isNull && pArgs[3].dVal == 0)
	{
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	if (!pArgs[0].isNull && !pArgs[1].isNull && !pArgs[2].isNull)
	{
		const std::wstring key(pArgs[0].pVal);
		const auto listFind = listLookup.find(key);
		if (listFind != listLookup.end())
		{
			const auto size = listFind->second.size();
			const auto index = get_index(size, pArgs[1].dVal);
			if (index < 0 || index >= size)
			{
				return AlteryxAbacusUtils::ReturnError(L"Cannot set as index out of range", pReturnValue, nNumArgs, pArgs);
			}
			listFind->second[index] = pArgs[2].dVal;
		}
		else
		{
			return AlteryxAbacusUtils::ReturnError(L"Cannot set as index out of range", pReturnValue, nNumArgs, pArgs);
		}

		pReturnValue->isNull = false;
		pReturnValue->dVal = pArgs[2].dVal;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarListInsert(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 3 || nNumArgs > 4 || pArgs[0].nVarType != 2 || pArgs[1].nVarType != 1 || pArgs[2].nVarType != 1 || (nNumArgs == 4 && pArgs[3].nVarType != 1))
	{
		return AlteryxAbacusUtils::ReturnError(L"VarListInsert: Syntax error - key:string index:integer value:number [setIfTrue:boolean = true] arguments.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	pReturnValue->isNull = true;

	if (nNumArgs == 4 && !pArgs[3].isNull && pArgs[3].dVal == 0)
	{
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	if (!pArgs[0].isNull && !pArgs[1].isNull && !pArgs[2].isNull)
	{
		const std::wstring key(pArgs[0].pVal);
		const auto listFind = listLookup.find(key);
		if (listFind != listLookup.end())
		{
			const auto size = listFind->second.size();
			const auto index = get_index(size, pArgs[1].dVal);
			if (index < 0 || index > size)
			{
				return AlteryxAbacusUtils::ReturnError(L"Cannot insert as index out of range", pReturnValue, nNumArgs, pArgs);
			}
			listFind->second.insert(listFind->second.begin() + index, pArgs[2].dVal);
		}
		else
		{
			if (pArgs[1].dVal != 0)
			{
				return AlteryxAbacusUtils::ReturnError(L"Cannot insert as index out of range", pReturnValue, nNumArgs, pArgs);
			}
			const std::deque<double> vector({ pArgs[2].dVal });
			listLookup[key] = vector;
		}

		pReturnValue->isNull = false;
		pReturnValue->dVal = pArgs[2].dVal;
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarListRemove(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs < 2 || nNumArgs > 3 || pArgs[0].nVarType != 2 || pArgs[1].nVarType != 1 || (nNumArgs == 3 && pArgs[2].nVarType != 1))
	{
		return AlteryxAbacusUtils::ReturnError(L"VarListRemove: Syntax error - key:string index:integer [setIfTrue:boolean = true] arguments.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	pReturnValue->isNull = true;

	if (nNumArgs == 3 && !pArgs[2].isNull && pArgs[2].dVal == 0)
	{
		return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
	}

	if (!pArgs[0].isNull && !pArgs[1].isNull)
	{
		const std::wstring key(pArgs[0].pVal);
		const auto listFind = listLookup.find(key);
		if (listFind != listLookup.end())
		{
			const auto size = listFind->second.size();
			const auto index = get_index(size, pArgs[1].dVal);
			if (index >= 0 && index < size)
			{
				const auto it = listFind->second.begin() + index;
				pReturnValue->isNull = false;
				pReturnValue->dVal = *it;
				listFind->second.erase(it);
			}
		}
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarListIndexOf(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs != 2 || pArgs[0].nVarType != 2 || pArgs[1].nVarType != 1)
	{
		return AlteryxAbacusUtils::ReturnError(L"VarListIndexOf: Syntax error - key:string value:double arguments.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	pReturnValue->isNull = true;

	if (!pArgs[0].isNull && !pArgs[1].isNull)
	{
		const std::wstring key(pArgs[0].pVal);
		const auto listFind = listLookup.find(key);
		if (listFind != listLookup.end())
		{
			const auto size = listFind->second.size();
			auto index = get_index(size, 0);
			while (index < size)
			{
				const auto it = listFind->second.begin() + index;
				if (*it == pArgs[1].dVal)
				{
					pReturnValue->isNull = false;
					pReturnValue->dVal = (double)index;
					return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
				}

				index++;
			}
		}
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarReset(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	if (nNumArgs > 1 || (nNumArgs == 1 && pArgs[0].nVarType == 1))
	{
		return AlteryxAbacusUtils::ReturnError(L"VarReset: Takes an optional string key argument.", pReturnValue, nNumArgs, pArgs);
	}

	pReturnValue->nVarType = 1;
	pReturnValue->isNull = true;

	if (nNumArgs == 1)
	{
		if (!pArgs[0].isNull) {
			const std::wstring key(pArgs[0].pVal);
			doubleLookup.erase(key);
			stringLookup.erase(key);
			listLookup.erase(key);
		}
	}
	else {
		stringLookup.clear();
		doubleLookup.clear();
		listLookup.clear();
	}

	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}

extern "C" long _declspec(dllexport) _stdcall VarPrint(int nNumArgs, FormulaAddInData * pArgs, FormulaAddInData * pReturnValue)
{
	pReturnValue->nVarType = 2;
	pReturnValue->isNull = false;

	std::wstringstream buffer;

	for (const auto& pair : stringLookup)
	{
		buffer << "text\t";
		buffer << pair.first;
		buffer << "\t";
		buffer << pair.second;
		buffer << "\n";
	}

	for (const auto& pair : doubleLookup)
	{
		buffer << "num\t";
		buffer << pair.first;
		buffer << "\t";
		buffer << pair.second;
		buffer << "\n";
	}

	for (const auto& pair : listLookup)
	{
		buffer << "list\t";
		buffer << pair.first;
		buffer << "\t";

		bool first = true;
		for (const auto value : pair.second)
		{
			if (!first)
			{
				buffer << ",";
			}
			buffer << value;
			first = false;
		}
		buffer << "\n";
	}

	AlteryxAbacusUtils::SetString(pReturnValue, buffer.str().c_str());
	return AlteryxAbacusUtils::ReturnSuccess(nNumArgs, pArgs);
}
