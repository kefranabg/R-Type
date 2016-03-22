// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
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