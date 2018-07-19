#ifndef FORMULAADDIN_H__
	#define FORMULAADDIN_H__

	const int nVarType_DOUBLE = 1;
	const int nVarType_WCHAR = 2;

	//  API definition for Formula functions plug ins
	struct FormulaAddInData
	{
		int nVarType;  // 1 for double, 2 for wchar_t
		int isNull; // 1 if NULL, 0 if valid

		double dVal; // valid if nVarType==1 && isNull==0
		const wchar_t * pVal; // valid if nVarType==2 && isNull==0

		inline FormulaAddInData()
		{
			memset(this, 0, sizeof(*this));
		}
	};

	// Formula function signature.  The function exposed in the <Dll><EntryPoint> of the
	// FormulaAddIn XML MUST have exactly this signature.
	// this MUST be thread safe
	//
	// return 1 for success
	//	If 1, place return value in pReturnValue.  If returning a string, it MUST be allocated with
	//		GlobalAlloc and will be free'd with GlobalFree
	// or 0 for failure.
	//	If 0, place a string in the pReturnValue that represents the error message
	//		Again, the string MUST be allocated with GlobalAlloc
	typedef long(_stdcall * FormulaAddInPlugin)(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue);
#endif