/*----------------------
  Copyright (C): OpenGATE Collaboration

  This software is distributed under the terms
  of the GNU Lesser General  Public Licence (LGPL)
  See LICENSE.md for further details
  ----------------------*/

#include <sstream>
#include "GateUIterminal.hh"

//-----------------------------------------------------------
void GateUIterminal::EnableG4Messages(bool b)
{
  mEnableG4Message = b;
}
//-----------------------------------------------------------


//-----------------------------------------------------------
G4int GateUIterminal::ReceiveG4cout(const G4String& coutString)
{
  if (mEnableG4Message)
    std::cout << coutString << std::flush;
  return 0;
}
//-----------------------------------------------------------

//-----------------------------------------------------------
G4int GateUIterminal::ReceiveG4cerr(const G4String& cerrString)
{
  std::cerr << "[G4-cerr] " <<  cerrString << std::flush;
  // Check if this error is 'command not found' (or related) to stop Gate
  bool isMacroError = false;
  std::string::size_type i = cerrString.find("***** COMMAND NOT FOUND <", 0);
  isMacroError = isMacroError || (i != std::string::npos);
  i = cerrString.find("***** Illegal application state <", 0);
  isMacroError = isMacroError || (i != std::string::npos);
  i = cerrString.find("***** Illegal parameter (", 0);
  isMacroError = isMacroError || (i != std::string::npos);
  i = cerrString.find("***** Can not open a macro file <", 0);
  isMacroError = isMacroError || (i != std::string::npos);
  i = cerrString.find("ERROR: Can not open a macro file <", 0);
  isMacroError = isMacroError || (i != std::string::npos);

  if (isMacroError) {
    std::cerr << "[Gate] Sorry, error in a macro command : abort.\n";
    exit(-1);
  }

  return 0;
}
//-----------------------------------------------------------

