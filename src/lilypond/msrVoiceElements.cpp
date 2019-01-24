/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifdef VC6
# pragma warning (disable : 4786)
#endif

#include <climits>      // INT_MIN, INT_MAX

#include "msrVoiceElements.h"

#include "msrOptions.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
msrVoiceElement::msrVoiceElement (
  int inputLineNumber)
    : msrElement (inputLineNumber)
{
  fVoiceNumber = "???";
  fPositionInVoice = rational (INT_MIN, 1);
}

msrVoiceElement::~msrVoiceElement ()
{}

void msrVoiceElement::acceptIn (basevisitor* v)
{
  if (gMsrOptions->fTraceMsrVisitors) {
    gLogIOstream <<
      "% ==> msrVoiceElement::acceptIn ()" <<
      endl;
  }
      
  if (visitor<S_msrVoiceElement>*
    p =
      dynamic_cast<visitor<S_msrVoiceElement>*> (v)) {
        S_msrVoiceElement elem = this;
        
        if (gMsrOptions->fTraceMsrVisitors) {
          gLogIOstream <<
            "% ==> Launching msrVoiceElement::visitStart ()" <<
            endl;
        }
        p->visitStart (elem);
  }
}

void msrVoiceElement::acceptOut (basevisitor* v)
{
  if (gMsrOptions->fTraceMsrVisitors) {
    gLogIOstream <<
      "% ==> msrVoiceElement::acceptOut ()" <<
      endl;
  }

  if (visitor<S_msrVoiceElement>*
    p =
      dynamic_cast<visitor<S_msrVoiceElement>*> (v)) {
        S_msrVoiceElement elem = this;
      
        if (gMsrOptions->fTraceMsrVisitors) {
          gLogIOstream <<
            "% ==> Launching msrVoiceElement::visitEnd ()" <<
            endl;
        }
        p->visitEnd (elem);
  }
}

string msrVoiceElement::asString () const
{
  // this is overriden all in actual elements
  return "??? msrVoiceElement::asString () ???";
}

string msrVoiceElement::asShortString () const
{
  // this can be overriden in actual elements
  return asString ();
}

void msrVoiceElement::print (ostream& os)
{
  os << asString () << endl;
}

ostream& operator<< (ostream& os, const S_msrVoiceElement& elt)
{
  elt->print (os);
  return os;
}


}
