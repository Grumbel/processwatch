#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

void PrintProcessNameAndID( DWORD processID )
{
  TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
  TCHAR szFilename[MAX_PATH] = TEXT("<unknown>");

  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                PROCESS_VM_READ,
                                FALSE, processID);

  if (hProcess != NULL)
  {
    HMODULE hModule;
    DWORD cbNeeded;

    if ( EnumProcessModules( hProcess, &hModule, sizeof(hModule), &cbNeeded) )
    {
      GetModuleBaseName( hProcess, hModule, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );
      GetModuleFileNameEx( hProcess, hModule, szFilename, sizeof(szFilename)/sizeof(TCHAR) );
    }
    
    CloseHandle( hProcess );
  }

  _tprintf( TEXT("  %16s %-60s (PID: %u)\n"), szProcessName, szFilename, processID );
}

int main()
{
  while(true)
  {
    SYSTEMTIME sys_time;
    GetSystemTime(&sys_time);

    _tprintf( TEXT("%d-%02d-%02dT%02d:%02d:%02dZ\n"),
              sys_time.wYear,
              sys_time.wMonth,
              sys_time.wDay,
              sys_time.wHour,
              sys_time.wMinute,
              sys_time.wSecond);
            
    DWORD aProcesses[1024];
    DWORD cbNeeded;
  
    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
      return 1;
    }
    else
    {
      DWORD cProcesses = cbNeeded / sizeof(DWORD);

      for (unsigned int i = 0; i < cProcesses; ++i)
      {
        if( aProcesses[i] != 0 )
        {
          PrintProcessNameAndID( aProcesses[i] );
        }
      }
    }
    _tprintf( TEXT("\n") );
 
    Sleep(60 * 1000);
  }

  return 0;
}

/* EOF */
