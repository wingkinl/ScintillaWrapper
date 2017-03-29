function DoParameterTypesReplacement(sText)
{
  var sOutput = sText;

  //Misc fixups
  sOutput = sOutput.replace(/int GetDocPointer/g, "void* GetDocPointer");
  sOutput = sOutput.replace(/int pointer/g, "_In_ void* pointer");
  sOutput = sOutput.replace(/int GetCharacterPointer/g, "const char* GetCharacterPointer");
  sOutput = sOutput.replace(/int GetRangePointer/g, "void* GetRangePointer");
  sOutput = sOutput.replace(/int PrivateLexerCall/g, "void* PrivateLexerCall");

  //replace int with the SAL version of int
  sOutput = sOutput.replace(/\(int /g, "(_In_ int ");
  sOutput = sOutput.replace(/, int/g, ", _In_ int");

  //replace string with const char*
  sOutput = sOutput.replace(/string /g, "_In_ const char* ");
  
  //Replace position with Sci_Position
  sOutput = sOutput.replace(/position /g, "Sci_Position ");
  sOutput = sOutput.replace(/\(Sci_Position /g, "(_In_ Sci_Position ");

  //Replace bool with BOOL
  sOutput = sOutput.replace(/bool/g, "BOOL");
  sOutput = sOutput.replace(/\(BOOL /g, "(_In_ BOOL ");
  sOutput = sOutput.replace(/, BOOL/g, ", _In_ BOOL");

  //Replace textrange with Sci_TextRange*
  sOutput = sOutput.replace(/textrange /g, "_Inout_ Sci_TextRange* ");
  
  //Replace cells with char*
  sOutput = sOutput.replace(/cells /g, "_In_ char* ");

  //Replace stringresult with char*
  sOutput = sOutput.replace(/stringresult /g, "_Out_ char* ");

  //Replace colour with COLORREF
  sOutput = sOutput.replace(/colour /g, "COLORREF ");
  sOutput = sOutput.replace(/\(COLORREF /g, "(_In_ COLORREF ");
  sOutput = sOutput.replace(/, COLORREF/g, ", _In_ COLORREF");

  //Replace colour with Sci_TextToFind*
  sOutput = sOutput.replace(/findtext /g, "_In_ Sci_TextToFind* ");
  
  //Replace keymod with DWORD
  sOutput = sOutput.replace(/keymod /g, "_In_ DWORD ");
  
  //Replace formatrange with Sci_RangeToFormat
  sOutput = sOutput.replace(/formatrange /g, "_In_ Sci_RangeToFormat* ");

  return sOutput;
}

function FindBodyParameters(sLine)
{
  var nStartParameters = sLine.indexOf("(");
  var nEndParameters = sLine.indexOf(")");
  var sParameters = sLine.substr(nStartParameters+1, nEndParameters - nStartParameters - 1);

  //Change the parameter types to something which the C++ compiler understands
  sParameters = DoParameterTypesReplacement(sParameters);

  //No first parameter
  if (sParameters.charAt(0) == ",")
    sParameters = "0" + sParameters;
  else
    sParameters = "static_cast<WPARAM>(" + sParameters;
  
  //No second parameter
  if (sParameters.charAt(sParameters.length-1) == ",")
    sParameters += " 0";
  else
  {
    var nComma = sParameters.indexOf(", ");
    var sTemp = sParameters.substr(0, nComma + 2);
    sTemp += "static_cast<LPARAM>(";
    sTemp += sParameters.substr(nComma + 1, sParameters.length - nComma);
    sParameters = sTemp;
  }
    
  //Remove the parameter types from the parameter string
  sParameters = sParameters.replace(/const char\*\ /g, "");
  sParameters = sParameters.replace(/Sci_Position\ /g, "");
  sParameters = sParameters.replace(/int\ /g, "");  
  sParameters = sParameters.replace(/BOOL\ /g, "");
  sParameters = sParameters.replace(/Sci_TextRange\*\ /g, "");
  sParameters = sParameters.replace(/char\*\ /g, "");
  sParameters = sParameters.replace(/COLORREF\ /g, "");
  sParameters = sParameters.replace(/Sci_TextToFind\*\ /g, "");
  sParameters = sParameters.replace(/DWORD\ /g, "");
  sParameters = sParameters.replace(/Sci_RangeToFormat\*\ /g, "");
  
  return sParameters;
}

function FindHeaderParameters(sLine)
{
  //find the parameters
  var nStartParameters = sLine.indexOf("(");
  var nEndParameters = sLine.indexOf(")");
  var sParameters = sLine.substr(nStartParameters+1, nEndParameters - nStartParameters - 1);

  //Change the parameter types to something which the C++ compiler understands
  sParameters = DoParameterTypesReplacement(sParameters);

  //No first parameter
  if (sParameters.charAt(0) == ",")
    sParameters = sParameters.substr(2, sParameters.length - 2);
  
  //No second parameter
  if (sParameters.charAt(sParameters.length-1) == ",")
    sParameters = sParameters.substr(0, sParameters.length - 1);
    
  return sParameters;
}

function FindFunctionNameAndReturn(sLine)
{
  //Find the name of the function
  var nFirstSpace = sLine.indexOf(" ");
  var sTemp = sLine.substr(nFirstSpace+1, sLine.length - nFirstSpace);
  var nEquals = sTemp.indexOf("=");
  var sFunction = sTemp.substr(0, nEquals);

  return sFunction;
}

function FindFunctionName(sLine)
{
  //Find the name of the function
  var nFirstSpace = sLine.indexOf(" ");
  var sTemp = sLine.substr(nFirstSpace+1, sLine.length - nFirstSpace);
  nFirstSpace = sTemp.indexOf(" ");
  sTemp = sTemp.substr(nFirstSpace+1, sTemp.length - nFirstSpace);
  var nEquals = sTemp.indexOf("=");
  var sFunction = sTemp.substr(0, nEquals);

  return sFunction;
}

function HandleFunctionHeader(sLine)
{
  //parse out the parameters from the line
  var sParameters = FindHeaderParameters(sLine);
  
  //Find the name of the function
  var sFunctionNameAndReturn = FindFunctionNameAndReturn(sLine);
  
  //Replace SetFocus with SCISetFocus (to avoid conflict with CWnd::SetFocus)
  sFunctionNameAndReturn = sFunctionNameAndReturn.replace(/SetFocus/g, "SCISetFocus");
  
  //Create the header output line
  var sOutput = sFunctionNameAndReturn + "(" + sParameters + ")" + ";";
  
  //Change the parameter types to something which the C++ compiler understands
  sOutput = DoParameterTypesReplacement(sOutput);

  return sOutput;
}

function HandleFunctionBody(sLine)
{
  //Get the basic function header from the other function
  var sHeader = HandleFunctionHeader(sLine);
  
  //Trim off the terminating ";"
  var sHeader = sHeader.substr(0, sHeader.length - 1);
  
  //Add the C++ class scoping
  var nFirstSpace = sHeader.indexOf(" ");
  var sBody = sHeader.substr(0, nFirstSpace + 1) + " CScintillaCtrl::" + sHeader.substr(nFirstSpace + 1, sHeader.length - nFirstSpace - 1);

  //Remove any padding between the scoping
  //sBody = sParameters.replace(/:: /g, "::");
  
  //Remove any padding before the class name
  sBody = sBody.replace(/\  CScintillaCtrl::/, " CScintillaCtrl::");

  //Work out the message type from the line
  var sMessage = "SCI_" + FindFunctionName(sLine).toUpperCase();

  //parse out the parameters from the line
  var sParameters = FindBodyParameters(sLine, false);
  
  //Add the start of the function
  sBody += "\r\n" + "{\r\n";
  
  //Have we a return value from this function
  if (FindFunctionNameAndReturn(sLine).indexOf("void") != 0)
  {
    sBody += "  return Call(";
  }
  else
  {
    //Add the "Call" function
    sBody += "  Call(";
  }
  
  //Complete the function body
  sBody += sMessage + ", " + sParameters + ");\r\n}\r\n";

  return sBody;
}



//The actual script implementation

//Ensure the number of arguments are correct
if (WScript.Arguments.length < 1)
{
  WScript.Echo("Usage: ConvertScintillaiface PathToScintillaiface [/CPP]");
  WScript.Quit(1);
}

//Create the file system object
var g_FSO = new ActiveXObject("Scripting.FileSystemObject");

//Open the file as text for parsing
var ifaceFile = g_FSO.OpenTextFile(WScript.Arguments(0), 1, false);

var bCreateHeader = true;
if (WScript.Arguments.length >= 2) 
{
  if (WScript.Arguments(1) == "/CPP")
    bCreateHeader = false;
}

//Read in all the text from the file
var bHandlingDeprecatedCategory = false;
var sLine;
while(!ifaceFile.AtEndOfStream)
{
  sLine = ifaceFile.ReadLine();
  if (sLine.length)
  {
    if (sLine.charAt(0) != "#")
    {
      if (sLine.indexOf("fun") == 0)
      {
        if (!bHandlingDeprecatedCategory)
        {
          if (bCreateHeader)
            WScript.Echo(HandleFunctionHeader(sLine, true));
          else
            WScript.Echo(HandleFunctionBody(sLine));
        }
      }
      else if (sLine.indexOf("get") == 0)
      {
        var sFunctionName = FindFunctionName(sLine);        

        if (!bHandlingDeprecatedCategory && sFunctionName != "GetDirectFunction" && sFunctionName != "GetDirectPointer")
        {
          if (bCreateHeader)
            WScript.Echo(HandleFunctionHeader(sLine, true));
          else
            WScript.Echo(HandleFunctionBody(sLine));
        }
      }
      else if (sLine.indexOf("set") == 0)
      {
        if (!bHandlingDeprecatedCategory)
        {
          if (bCreateHeader)
            WScript.Echo(HandleFunctionHeader(sLine, true));
          else
            WScript.Echo(HandleFunctionBody(sLine));
        }
      }
      else if (sLine.indexOf("cat") == 0)
      {
        if (sLine.indexOf("Deprecated") != -1)
          bHandlingDeprecatedCategory = true;
        else
          bHandlingDeprecatedCategory = false;
      }
    }
  }
}


