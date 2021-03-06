/*******************************************************************************
 * Copyright (c) 2005 - 2014 ACIN, Profactor GmbH, fortiss GmbH
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *   Alois Zoitl, Gerhard Ebenhofer
 *     - initial API and implementation and/or initial documentation
 *******************************************************************************/
#include "E_DELAY.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_DELAY_gen.cpp"
#endif
#include "../../arch/timerha.h"

DEFINE_FIRMWARE_FB(E_DELAY, g_nStringIdE_DELAY)

E_DELAY::E_DELAY(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes):
         CTimedFB( pa_nInstanceNameId, pa_poSrcRes){
  m_stTimeListEntry.m_eType = e_SingleShot;
}

void E_DELAY::executeEvent(int pa_nEIID){
  if(cg_nExternalEventID == pa_nEIID ){
    sendOutputEvent(csm_nEOID);
    m_bActive = false;
  }
  else{
    if(csm_nEventSTARTID  == pa_nEIID ){
      if(!m_bActive){
        setEventChainExecutor(m_poInvokingExecEnv);  // E_DELAY will execute in the same thread on as from where it has been triggered.
      }
    }
    CTimedFB::executeEvent(pa_nEIID);
  }
}


