// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#ifndef STDAFX
# define STDAFX

#include <SDKDDKVer.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <tchar.h>
#include <strsafe.h>

#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <tchar.h>
#include <iostream>

#endif