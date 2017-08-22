xcopy "./dep/cef/bin/Release" "./QCefViewSDK/bin/release_x86" /s /e /y /i
xcopy "./dep/cef/Resources" "./QCefViewSDK/bin/release_x86/resources" /s /e /y /i
xcopy "./dep/cef/bin/Debug" "./QCefViewSDK/bin/debug_x86" /s /e /y /i
xcopy "./dep/cef/Resources" "./QCefViewSDK/bin/debug_x86/resources" /s /e /y /i
pause