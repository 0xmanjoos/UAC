#include <windows.h>
#define WIN32_LEAN_AND_MEAN
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
				elevate();
				MessageBox(0, "BIGBOY", "lOoKiT mE mOoOm :D, iM a bIg bOI noW!!", 0);
		} else {
			exit(0);
		}
	return 0;
	}
}
