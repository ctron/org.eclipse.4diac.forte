/*******************************************************************************
 * Copyright (c) 2006 - 2014 ACIN, Profactor GmbH, fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer, Ingo Hegny, Monika Wenger,
 *    - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "RT_E_CYCLE.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "RT_E_CYCLE_gen.cpp"
#endif

DEFINE_FIRMWARE_FB(FORTE_RT_E_CYCLE, g_nStringIdRT_E_CYCLE)

const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scm_anDataInputNames[] = {g_nStringIdDT, g_nStringIdDeadline, g_nStringIdWCET};

const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scm_anDataInputTypeIds[] = {g_nStringIdTIME, g_nStringIdTIME, g_nStringIdTIME};

const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scm_anDataOutputNames[] = {g_nStringIdQO};

const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scm_anDataOutputTypeIds[] = {g_nStringIdBOOL};

const TForteInt16 FORTE_RT_E_CYCLE::scm_anEIWithIndexes[] = {0, -1};
const TDataIOID FORTE_RT_E_CYCLE::scm_anEIWith[] = {0, 1, 2, 255};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scm_anEventInputNames[] = {g_nStringIdSTART, g_nStringIdSTOP};

const TDataIOID FORTE_RT_E_CYCLE::scm_anEOWith[] = {0, 255};
const TForteInt16 FORTE_RT_E_CYCLE::scm_anEOWithIndexes[] = {-1, 0};
const CStringDictionary::TStringId FORTE_RT_E_CYCLE::scm_anEventOutputNames[] = {g_nStringIdEO};

const SFBInterfaceSpec FORTE_RT_E_CYCLE::scm_stFBInterfaceSpec = {
  2,  scm_anEventInputNames,  scm_anEIWith,  scm_anEIWithIndexes,
  1,  scm_anEventOutputNames,  scm_anEOWith, scm_anEOWithIndexes,  3,  scm_anDataInputNames, scm_anDataInputTypeIds,
  1,  scm_anDataOutputNames, scm_anDataOutputTypeIds,
  0, 0
};

FORTE_RT_E_CYCLE::FORTE_RT_E_CYCLE(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes) :
            CEventSourceFB( pa_poSrcRes, &scm_stFBInterfaceSpec,  pa_nInstanceNameId, m_anFBConnData, m_anFBVarsData){
  setEventChainExecutor(&m_oECEO);
  m_bActive = false;
  //Timeout value is correctly initialized by the constructor m_stTimeListEntry.m_nTimeOut = 0;
  m_stTimeListEntry.m_nInterval = 0;
  m_stTimeListEntry.m_pstNext = 0;
  m_stTimeListEntry.m_poTimedFB = this;
  m_stTimeListEntry.m_eType = e_Periodic;
  m_oECEO.changeExecutionState(cg_nMGM_CMD_Start);
}


void FORTE_RT_E_CYCLE::executeEvent(int pa_nEIID){
  switch(pa_nEIID){
    case cg_nExternalEventID:
      sendOutputEvent(scm_nEventEOID);
      break;
    case scm_nEventSTOPID:
      if(m_bActive){
        m_oECEO.setDeadline(static_cast<CIEC_TIME::TValueType>(0));
        CTimerHandler::sm_poFORTETimer->unregisterTimedFB(this);
        m_bActive = false;
      }
      break;
    case scm_nEventSTARTID:
      if(!m_bActive){
        m_oECEO.setDeadline(Deadline());
        CTimerHandler::sm_poFORTETimer->registerTimedFB( &m_stTimeListEntry, DT());
        m_bActive = true;
      }
      break;
    default:
      break;
  }
}

