#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

using namespace std;

int _tmain( int argc, TCHAR *argv[] )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    
	// Define launch string for CreateProcess (see below).
    string argString = "nw.exe package.json";
    
    // Combine our constant arguments (program and package) with the passed file
	// name argument (if one has been passed).
    if(argv[1]) {
	    string fileName = argv[1];
    	argString += " " + fileName;
    }
    
    // Convert our argument string to a TCHAR so CreateProcess doesn't complain.
    TCHAR *arg_tchar = new TCHAR[argString.size()+1];
    arg_tchar[argString.size()]=0;
    std::copy(argString.begin(), argString.end(), arg_tchar);
    
    // Start the child process. 
    if( !CreateProcess( NULL,   // No module name (use command line)
        arg_tchar,      // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return 1;
    }
}
