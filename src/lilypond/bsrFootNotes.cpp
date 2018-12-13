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

#include <sstream>
#include <iomanip> // for 'setw()'

#include "bsrFootNotes.h"

#include "utilities.h"

#include "bsrOptions.h"
#include "brailleOptions.h"


using namespace std;

namespace MusicXML2
{

//______________________________________________________________________________
S_bsrFootNotesElement bsrFootNotesElement::create (
  int    inputLineNumber,
  string footNoteText)
{
  bsrFootNotesElement* o =
    new bsrFootNotesElement (
      inputLineNumber, footNoteText);
  assert(o!=0);
  return o;
}

bsrFootNotesElement::bsrFootNotesElement (
  int    inputLineNumber,
  string footNoteText)
    : bsrElement (inputLineNumber)
{
  fFootNoteText = footNoteText;

  fFootNotesElementCellsList =
    bsrCellsList::create (inputLineNumber);
}

bsrFootNotesElement::~bsrFootNotesElement ()
{}

void bsrFootNotesElement::acceptIn (basevisitor* v)
{
#ifdef TRACE_OPTIONS
  if (gBsrOptions->fTraceBsrVisitors) {
    gLogIOstream <<
      "% ==> bsrFootNotesElement::acceptIn ()" <<
      endl;
  }
#endif
      
  if (visitor<S_bsrFootNotesElement>*
    p =
      dynamic_cast<visitor<S_bsrFootNotesElement>*> (v)) {
        S_bsrFootNotesElement elem = this;
        
#ifdef TRACE_OPTIONS
        if (gBsrOptions->fTraceBsrVisitors) {
          gLogIOstream <<
            "% ==> Launching bsrFootNotesElement::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void bsrFootNotesElement::acceptOut (basevisitor* v)
{
#ifdef TRACE_OPTIONS
  if (gBsrOptions->fTraceBsrVisitors) {
    gLogIOstream <<
      "% ==> bsrFootNotesElement::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_bsrFootNotesElement>*
    p =
      dynamic_cast<visitor<S_bsrFootNotesElement>*> (v)) {
        S_bsrFootNotesElement elem = this;
      
#ifdef TRACE_OPTIONS
        if (gBsrOptions->fTraceBsrVisitors) {
          gLogIOstream <<
            "% ==> Launching bsrFootNotesElement::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void bsrFootNotesElement::browseData (basevisitor* v)
{
}

string bsrFootNotesElement::asString () const
{
  stringstream s;

  s <<
    "FootNotesElement" <<
    // JMI ", fFootNoteText: " <<
    ", \"" << fFootNoteText << "\"" <<
    ", line " << fInputLineNumber;

  return s.str ();
}

void bsrFootNotesElement::print (ostream& os)
{
  os <<
    "FootNotesElement" <<
    ", line " << fInputLineNumber <<
    endl;

  gIndenter++;
  
  os <<
    "footNoteText " << " : \"" << fFootNoteText << "\"" <<
    endl;

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_bsrFootNotesElement& elt)
{
  elt->print (os);
  return os;
}

//______________________________________________________________________________
S_bsrFootNotes bsrFootNotes::create (
  int inputLineNumber)
{
  bsrFootNotes* o =
    new bsrFootNotes (
      inputLineNumber);
  assert(o!=0);
  return o;
}

bsrFootNotes::bsrFootNotes (
  int inputLineNumber)
    : bsrLine (
        inputLineNumber,
        0, // JMI ???
        gBrailleOptions->fCellsPerLine)
{}

bsrFootNotes::~bsrFootNotes ()
{}

void bsrFootNotes::acceptIn (basevisitor* v)
{
#ifdef TRACE_OPTIONS
  if (gBsrOptions->fTraceBsrVisitors) {
    gLogIOstream <<
      "% ==> bsrFootNotes::acceptIn ()" <<
      endl;
  }
#endif
      
  if (visitor<S_bsrFootNotes>*
    p =
      dynamic_cast<visitor<S_bsrFootNotes>*> (v)) {
        S_bsrFootNotes elem = this;
        
#ifdef TRACE_OPTIONS
        if (gBsrOptions->fTraceBsrVisitors) {
          gLogIOstream <<
            "% ==> Launching bsrFootNotes::visitStart ()" <<
            endl;
        }
#endif
        p->visitStart (elem);
  }
}

void bsrFootNotes::acceptOut (basevisitor* v)
{
#ifdef TRACE_OPTIONS
  if (gBsrOptions->fTraceBsrVisitors) {
    gLogIOstream <<
      "% ==> bsrFootNotes::acceptOut ()" <<
      endl;
  }
#endif

  if (visitor<S_bsrFootNotes>*
    p =
      dynamic_cast<visitor<S_bsrFootNotes>*> (v)) {
        S_bsrFootNotes elem = this;
      
#ifdef TRACE_OPTIONS
        if (gBsrOptions->fTraceBsrVisitors) {
          gLogIOstream <<
            "% ==> Launching bsrFootNotes::visitEnd ()" <<
            endl;
        }
#endif
        p->visitEnd (elem);
  }
}

void bsrFootNotes::browseData (basevisitor* v)
{
  for (
    list<S_bsrFootNotesElement>::const_iterator i =
      fFootNotesElementsList.begin ();
    i != fFootNotesElementsList.end ();
    i++ ) {
    // browse the element
    bsrBrowser<bsrFootNotesElement> browser (v);
    browser.browse (*(*i));
  } // for
}

void bsrFootNotes::print (ostream& os)
{
  os <<
    "FootNotes" <<
    endl;

  gIndenter++;
  
  // print the notes if any
  const int fieldWidth = 19;

  int footNotesElementsListSize = fFootNotesElementsList.size ();
  
  if (footNotesElementsListSize || gBsrOptions->fDisplayBsrDetails) {
    os <<
      setw (fieldWidth) <<
      "footNotesElementsList" << " : " <<
      endl;
      
    if (footNotesElementsListSize) {
      gIndenter++;
  
      list<S_bsrFootNotesElement>::const_iterator
        iBegin = fFootNotesElementsList.begin (),
        iEnd   = fFootNotesElementsList.end (),
        i      = iBegin;
      for ( ; ; ) {
        os << (*i);
        if (++i == iEnd) break;
        os << endl;
      } // for
  
      os <<
        endl;
        
      gIndenter--;
    }
    else {
      os <<
        "none" <<
      endl;
    }
  }

  gIndenter--;
}

ostream& operator<< (ostream& os, const S_bsrFootNotes& elt)
{
  elt->print (os);
  return os;
}


}