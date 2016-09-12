/*
  MusicXML Library
  Copyright (C) Grame 2006-2013

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#ifndef __lilypond__
#define __lilypond__

#include <sstream>
#include <vector>
#include <string>
#include <map>

#include "exports.h"
#include "typedefs.h"
#include "smartpointer.h"

namespace MusicXML2 
{

class lilypondvisitor;

class lilypondparam;
class lilypondelement;
class lilypondpart;
class lilypondlyrics;

typedef SMARTP<lilypondparam>    Slilypondparam;
typedef SMARTP<lilypondelement>  Slilypondelement;
typedef SMARTP<lilypondpart>     Slilypondpart;
typedef SMARTP<lilypondlyrics>   Slilypondlyrics;

EXP std::ostream& operator<< (std::ostream& os, const Slilypondparam&   param);
EXP std::ostream& operator<< (std::ostream& os, const Slilypondelement& elt);
//EXP std::ostream& operator<< (std::ostream& os, const Slilypondpart& elt);
//EXP std::ostream& operator<< (std::ostream& os, const Slilypondlyrics& elt);

/*!
\addtogroup lilypond
@{
*/


/*!
\brief A lilypondcmd parameter representation.

  A parameter is represented by its value.
*/
//______________________________________________________________________________
class EXP lilypondparam : public smartable {
  public:
    
    static SMARTP<lilypondparam> create(std::string value, bool quote=true);
    static SMARTP<lilypondparam> create(long value, bool quote=true);

    //! the parameter value
    void        set (std::string value, bool quote=true);
    void        set (long value, bool quote=true);
    std::string get () const        { return fValue; }
    bool        quote () const      { return fQuote; }

    virtual void print (std::ostream& os);
        
  protected:
 
    lilypondparam(std::string value, bool quote);
    lilypondparam(long value, bool quote);
    virtual ~lilypondparam ();
        
  private:

    std::string   fValue;
    bool          fQuote;
};

/*!
\brief A generic lilypond element representation.

  An element is represented by its name and the
  list of its enclosed elements plus optional parameters.
*/
//______________________________________________________________________________
class EXP lilypondelement : public smartable {
  public:
 
    static SMARTP<lilypondelement> create(std::string name, std::string sep=" ");
    
    long addSubElement (Slilypondelement& elt);

    long addParam   (Slilypondparam& param);
    long addParam   (Slilypondparam param);
    
    virtual void print (std::ostream& os);

    //! the element name
    void          setName (std::string name) { fName = name; }
    std::string   getName () const           { return fName; }

    std::string   getStart () const          { return fStartList; }
    std::string   getEnd () const            { return fEndList; }
    std::string   getSep () const            { return fSep; }
    
    std::vector<Slilypondelement>& elements()             { return fSubElements; }
    const std::vector<Slilypondelement>& elements() const { return fSubElements; }
    const std::vector<Slilypondparam>& parameters() const { return fParams; }
    
    bool empty () const { return fSubElements.empty(); }

  protected:
 
    lilypondelement(std::string name, std::string sep=" ");
    virtual ~lilypondelement();

    std::string fName;
    
    //! the contained element start marker (defaults to empty)
    std::string fStartList;
    //! the contained element end marker (defaults to empty)
    std::string fEndList;
    //! the element separator (defaults to space)
    std::string fSep;
    
    //! list of the enclosed elements
    std::vector<Slilypondelement> fSubElements;
    
    //! list of optional parameters
    std::vector<Slilypondparam> fParams;  
    
  private:
  
    bool fDebug;
    void dumpElements(); // DEBUG
    void dumpParams();   // DEBUG
};

/*!
\brief A lilypond note duration representation.

  A note duration is represented by a numerator 
    (denotes the number of beats), a denominator (denotes the beat value)
     and optional dots.
     Triplets are repesented as 1/3, 1/6, ... quintuplets, septuplets and so on
     are handled analogously.
*/
//______________________________________________________________________________
class EXP lilypondnoteduration {
  public:
  
    lilypondnoteduration(long num, long denom, long dots=0) 
            { set (num, denom, dots); }
    virtual ~lilypondnoteduration() {}
        
    void set (long num, long denom, long dots=0) 
        { fNum=num; fDenom=denom; fDots=dots; }
    lilypondnoteduration& operator= (const lilypondnoteduration& dur) 
        { fNum=dur.fNum; fDenom=dur.fDenom; fDots=dur.fDots; return *this; }
    bool operator!= (const lilypondnoteduration& dur) const 
        { return (fNum!=dur.fNum) || (fDenom!=dur.fDenom) || (fDots!=dur.fDots); }

    long  fNum;
    long  fDenom;
    long  fDots;
};

/*!
\brief A lilypond note representation.

  A note is represented by its name, optional accidentals,
    duration (in the form of numerator/denominator) and optional dots.
*/
//______________________________________________________________________________
class EXP lilypondnote : public lilypondelement {
  public:

    static SMARTP<lilypondnote> create(unsigned short voice);
    static SMARTP<lilypondnote> create(unsigned short voice, std::string name, char octave,
                                            lilypondnoteduration& dur, std::string acc="");

    void set (unsigned short voice, std::string name, char octave, lilypondnoteduration& dur, std::string acc);
    void setName (const std::string name)     { fNote = name; } 
    void setOctave (char octave)          { fOctave = octave; }
    void setDuration (const lilypondnoteduration& dur)  { fDuration = dur; }
    void setAccidental (const std::string acc)    { fAccidental = acc; }

    const char *  name() const    { return fNote.c_str(); }
    const char *  accidental() const  { return fAccidental.c_str(); }
    char      octave() const    { return fOctave; }
    const lilypondnoteduration& duration() const { return fDuration; }

    virtual void print (std::ostream& os);

  protected:
 
    lilypondnote(unsigned short voice);
    lilypondnote(unsigned short voice, std::string name, char octave, 
                    lilypondnoteduration& dur, std::string acc="");
    virtual ~lilypondnote();
    
  private:

    std::string octaveRepresentation (char octave);
  
    std::string   fNote;
    std::string   fAccidental;
    char  fOctave;
    lilypondnoteduration fDuration;

};
typedef SMARTP<lilypondnote> Slilypondnote;

/*!
\brief Represents the current status of notes duration and octave.

    Octave and duration may be ommitted for lilypond notes. If so,
    they are infered from preceeding notes (or rests), within the same 
    sequence or chord, or assumed to have standard values.
\n
  The object is defined as a multi-voices singleton: a single
    object is allocated for a specific voice and thus it will
  not operate correctly in case of parallel formatting 
    operations on a given voice.

\todo handling the current beat value for \e *num duration form.
*/
//______________________________________________________________________________
class EXP lilypondnotestatus {
  public:
    
    enum { kMaxInstances=128 };
        
    static lilypondnotestatus* get(unsigned short voice);
    static void resetall();
    static void freeall();

    enum { defoctave=1, defnum=1, defdenom=4 };
        
    void reset()  { fOctave=defoctave; fDur.set(defnum, defdenom, 0); }
    lilypondnotestatus& operator= (const lilypondnoteduration& dur) { fDur = dur; return *this; }
    bool operator!= (const lilypondnoteduration& dur) const   { return fDur!= dur; }
            
    char                  fOctave;
    lilypondnoteduration  fDur;
//    char        fBeat;

  protected:
  
    lilypondnotestatus() :  fOctave(defoctave), fDur(defnum, defdenom, 0) {}
    
  private:
  
    static lilypondnotestatus * fInstances[kMaxInstances];
};

/*!
\brief The lilypond sequence element
*/
//______________________________________________________________________________
class EXP lilypondseq : public lilypondelement {
  public:
    
    static SMARTP<lilypondseq> create();

    void addElementToSequence (Slilypondelement elem) { fSequenceElements.push_back(elem); }

    virtual void print (std::ostream& os);

  protected:

    lilypondseq();
    virtual ~lilypondseq();
    
  private:
  
    std::vector<Slilypondelement> fSequenceElements;

};
typedef SMARTP<lilypondseq> Slilypondseq;

/*!
\brief The lilypond chord element
*/
//______________________________________________________________________________
class EXP lilypondchord : public lilypondelement {
  public:

    static SMARTP<lilypondchord> create();
    
    virtual void print (std::ostream& os);

  protected:

    lilypondchord ();
    virtual ~lilypondchord();
};
typedef SMARTP<lilypondchord> Slilypondchord;

/*!
\brief A lilypond command representation.

  A command is represented by its name and optional parameters.
  A range command contains enclosed elements. //USER ???
*/
//______________________________________________________________________________
class EXP lilypondcmd : public lilypondelement {
  public:

    enum BackSlashPrefix { kWithBackslash, kWithoutBackslash };

    static SMARTP<lilypondcmd> create(
      std::string name, 
      BackSlashPrefix backslashPrefix=kWithBackslash);

    virtual void print (std::ostream& os);

  protected:

    lilypondcmd(std::string name, BackSlashPrefix backslashPrefix=kWithBackslash);
    virtual ~lilypondcmd();
};
typedef SMARTP<lilypondcmd> Slilypondcmd;

/*!
\brief A lilypond header representation.

  A header is represented by variable/value pairs
*/
//______________________________________________________________________________
class EXP lilypondheader : public lilypondelement {
  public:

    static SMARTP<lilypondheader> create();
    
    void                    setScorePartwise   (S_score_partwise val)   { fScorePartwise = val; }
    S_score_partwise        getScorePartwise   () const                 { return fScorePartwise; }

    void                    setWorkNumber      (S_work_number val)      { fWorkNumber = val; }
    S_work_number           getWorkNumber      () const                 { return fWorkNumber; }

    void                    setWorkTitle       (S_work_title val)       { fWorkTitle = val; }
    S_work_title            getWorkTitle       () const                 { return fWorkTitle; }

    void                    setMovementNumber  (S_movement_number val)  { fMovementNumber = val; }
    S_movement_number       getMovementNumber  () const                 { return fMovementNumber; }

    void                    setMovementTitle   (S_movement_title val)   { fMovementTitle = val; }
    S_movement_title        getMovementTitle   () const                 { return fMovementTitle; }

    void                    addCreator         (S_creator val)          { fCreators.push_back(val); }
    std::vector<S_creator>  getCreators        () const                 { return fCreators; };

    void                    setRights          (S_rights val)           { fRights = val; }
    S_rights                getRights          () const                 { return fRights; }

    void                    addSoftware        (S_software val)         { fSoftwares.push_back(val); }
    std::vector<S_software> getSoftwares       () const                 { return fSoftwares; };

    void                    setEncodingDate    (S_encoding_date val)    { fEncodingDate = val; }
    S_encoding_date         getEncodingDate    () const                 { return fEncodingDate; }

    void                    setScoreInstrument (S_score_instrument val) { fScoreInstrument = val; }
    S_score_instrument      getScoreInstrument () const                 { return fScoreInstrument; }

    virtual void print (std::ostream& os);

  protected:

    lilypondheader();
    virtual ~lilypondheader();
  
  private:

    S_score_partwise        fScorePartwise; // may contain MusicXML version
    S_work_number           fWorkNumber;
    S_work_title            fWorkTitle;
    S_movement_number       fMovementNumber;
    S_movement_title        fMovementTitle;
    std::vector<S_creator>  fCreators;
    S_rights                fRights;
    std::vector<S_software> fSoftwares;
    S_encoding_date         fEncodingDate;
    S_score_instrument      fScoreInstrument;

};
typedef SMARTP<lilypondheader> Slilypondheader;

/*!
\brief A lilypond paper representation.

  A paper is represented by variable/value pairs
*/
//______________________________________________________________________________
class EXP lilypondpaper : public lilypondelement {
  public:

    static SMARTP<lilypondpaper> create();
    
    virtual void print (std::ostream& os);

  protected:

    lilypondpaper();
    virtual ~lilypondpaper();
  
  private:

 
};
typedef SMARTP<lilypondpaper> Slilypondpaper;

/*!
\brief A lilypond layout representation.

  A layout is represented by variable/value pairs
*/
//______________________________________________________________________________
class EXP lilypondlayout : public lilypondelement {
  public:

    static SMARTP<lilypondlayout> create();
    
    virtual void print (std::ostream& os);

  protected:

    lilypondlayout();
    virtual ~lilypondlayout();
  
  private:

 
};
typedef SMARTP<lilypondlayout> Slilypondlayout;

/*!
\brief A lilypond part representation.

  A part is represented by a its string contents
*/
//______________________________________________________________________________
class EXP lilypondpart : public lilypondelement {
  public:

    static SMARTP<lilypondpart> create(std::string name, bool absoluteCode);
    
    std::string      getPartName () const         { return fPartName; }
    bool             getAbsoluteCode () const     { return fPartAbsoluteCode; }
    Slilypondseq     getPartLilypondseq () const  { return fPartLilypondseq; }

    virtual void print (std::ostream& os);

  protected:

    lilypondpart(std::string name, bool absoluteCode);
    virtual ~lilypondpart();
  
  private:

    std::string      fPartName;
    bool             fPartAbsoluteCode;
    
    // the implicit sequence containing the code generated for the part
    Slilypondseq     fPartLilypondseq;
};
typedef SMARTP<lilypondpart> Slilypondpart;
typedef std::map<std::string, Slilypondpart> lilypondpartsmap;

/*!
\brief A lilypond wedge representation.

  A wedge is represented by a WedgeKind value (hairpins in LilyPond)
*/
//______________________________________________________________________________
class EXP lilypondwedge : public lilypondelement {
  public:

    enum WedgeKind { kCrescendoWedge, kDecrescendoWedge, kStopWedge };
    
    static SMARTP<lilypondwedge> create(WedgeKind kind);

    WedgeKind getWedgeKind () const        { return fWedgeKind; }

    virtual void print (std::ostream& os);

  protected:

    lilypondwedge(WedgeKind kind);
    virtual ~lilypondwedge();
  
  private:

    WedgeKind fWedgeKind;
};
typedef SMARTP<lilypondwedge> Slilypondwedge;

/*!
\brief A lilypond lyrics representation.

  A lyrics is represented by a its string contents
*/
//______________________________________________________________________________
class EXP lilypondlyrics : public lilypondelement {
  public:

    static SMARTP<lilypondlyrics> create(std::string name, std::string contents);
    
    std::string getContents () const { return fContents; }

    virtual void print (std::ostream& os);

  protected:

    lilypondlyrics(std::string name, std::string contents);
    virtual ~lilypondlyrics();
  
  private:

    std::string fName, fContents;
};
typedef SMARTP<lilypondlyrics> Slilypondlyrics;


/*! @} */

}


#endif
