#ifndef ALTERYX_ADDIN_UTILS_H__
	#define ALTERYX_ADDIN_UTILS_H__

	#include "AlteryxAbacus.h"

	class AlteryxAbacusUtils
	{
		// Function To Actually Set A String On A Return (inc GlobalAlloc)
		static void DoSetString(FormulaAddInData* pReturnValue, const wchar_t* pString);

		// Fix a Bug from Pre 10.5, should be retired
		static void DoResetNull(int nNumArgs, FormulaAddInData* pArgs);

	public:
		// Function To Set A String On A Return (inc GlobalAlloc)
		static void SetString(FormulaAddInData *pReturnValue, const wchar_t *pString);

		// Correct NULL and return success value
		static long ReturnError(const wchar_t *pString, FormulaAddInData *pReturnValue, int nNumArgs, FormulaAddInData *pArgs);

		// Correct NULL and return success value
		static long ReturnSuccess(int nNumArgs, FormulaAddInData *pArgs);

		// Copy From Source To Target
		static void CopyValue(const FormulaAddInData *source, FormulaAddInData *target);
	};
#endif