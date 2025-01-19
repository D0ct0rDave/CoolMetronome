//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Metronome.res");
USEFORM("GUI.cpp", oForm);
USEUNIT("OMidiOut.cpp");
USEFORM("GUIFromTo.cpp", oDLGFromTo);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(ToForm), &oForm);
         Application->CreateForm(__classid(ToDLGFromTo), &oDLGFromTo);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
