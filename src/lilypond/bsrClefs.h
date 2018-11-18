/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef ___bsrClefs___
#define ___bsrClefs___

#include "bsrBrailleElements.h"


using namespace std;

namespace MusicXML2 
{

//______________________________________________________________________________
class bsrClef : public bsrBrailleElement
{
  public:
          
    // creation
    // ------------------------------------------------------

    static SMARTP<bsrClef> create (
      int inputLineNumber);

  protected:

    // constructors/destructor
    // ------------------------------------------------------

    bsrClef (
      int inputLineNumber);
      
    virtual ~bsrClef ();
  
  public:

    // set and get
    // ------------------------------------------------------
                  

    // services
    // ------------------------------------------------------
                  
  public:

    // visitors
    // ------------------------------------------------------

    virtual void          acceptIn  (basevisitor* v);
    virtual void          acceptOut (basevisitor* v);

    virtual void          browseData (basevisitor* v);

  public:

    // print
    // ------------------------------------------------------

    string                asString () const;

    virtual void          print (ostream& os);

  private:

    // fields
    // ------------------------------------------------------

};
typedef SMARTP<bsrClef> S_bsrClef;
EXP ostream& operator<< (ostream& os, const S_bsrClef& elt);


} // namespace MusicXML2


#endif