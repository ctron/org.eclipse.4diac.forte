/*******************************************************************************
 * Copyright (c) 2009 - 2013 ACIN, fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *   Monika Wenger, Alois Zoitl, Ingo Hengy
 *   - initial API and implementation and/or initial documentation
 *******************************************************************************/
#ifndef _FB_TOF_H_
#define _FB_TOF_H_

#include <funcbloc.h>
#include <forte_time.h>
#include "../../arch/timerha.h"
#include <forte_bool.h>
#include <forte_array.h>

// cppcheck-suppress noConstructor
class FB_TOF: public CFunctionBlock{
  DECLARE_FIRMWARE_FB(FB_TOF)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[], scm_aunDIDataTypeIds[];
  static const CStringDictionary::TStringId scm_anDataOutputNames[], scm_aunDODataTypeIds[];
  static const TEventID scm_nEventREQID = 0;
  static const TForteInt16 scm_anEIWithIndexes[];
  static const TDataIOID scm_anEIWith[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];

  static const TEventID scm_nEventCNFID = 0;
  static const TForteInt16 scm_anEOWithIndexes[];
  static const TDataIOID scm_anEOWith[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

  FORTE_FB_DATA_ARRAY(1,2,2, 0);

  bool fallingEdge;
  bool notFirstRisingEdge;
  CIEC_TIME start;
  CIEC_TIME count;

  void executeEvent(int pa_nEIID);

  CIEC_BOOL& IN() {
   	return *static_cast<CIEC_BOOL*>(getDI(0));
  }  

  CIEC_TIME& PT() {
   	return *static_cast<CIEC_TIME*>(getDI(1));
  }  

  CIEC_BOOL& Q() {
   	return *static_cast<CIEC_BOOL*>(getDO(0));
  }  

  CIEC_TIME& ET() {
   	return *static_cast<CIEC_TIME*>(getDO(1));
  } 

public:
  FUNCTION_BLOCK_CTOR(FB_TOF){};
  virtual ~FB_TOF(){};

};

#endif //close the ifdef sequence from the beginning of the file

