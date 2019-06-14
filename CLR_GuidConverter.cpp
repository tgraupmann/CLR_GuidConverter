// reference: https://docs.microsoft.com/en-us/cpp/dotnet/how-to-convert-between-system-guid-and-guid?view=vs-2019
//
// convert_guids.cpp
// compile with: /clr
#include "pch.h"
#include <windows.h>
#include <stdio.h>

using namespace System;

Guid FromGUID(_GUID& guid) {
	return Guid(guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
}

_GUID ToGUID(Guid& guid) {
	array<Byte>^ guidData = guid.ToByteArray();
	pin_ptr<Byte> data = &(guidData[0]);

	return *(_GUID*)data;
}

int main() {
	_GUID ng = { 0x11111111,0x2222,0x3333,0x44,0x55,0x55,0x55,0x55,0x55,0x55,0x55 };
	Guid mg;

	Console::WriteLine((mg = FromGUID(ng)).ToString());
	_GUID ng2 = ToGUID(mg);

	printf_s("%x-%x-%x-", ng2.Data1, ng2.Data2, ng2.Data3);
	for (int i = 0; i < 8; i++) {
		if (i == 2)
			printf_s("-");
		printf_s("%x", ng2.Data4[i]);
	}
	printf_s("\n");
}
