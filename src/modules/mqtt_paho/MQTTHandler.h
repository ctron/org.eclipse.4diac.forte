/*******************************************************************************
 * Copyright (c) 2013, 2014 ACIN
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 * Martin Melik Merkumians - initial API and implementation and/or initial documentation
 *******************************************************************************/


#ifndef MQTTHANDLER_H_
#define MQTTHANDLER_H_

#include <singlet.h>
#include <extevhan.h>
#include <fortelist.h>
#include <MQTTComLayer.h>
#include <forte_sync.h>
#include <forte_string.h>
#include <forte_thread.h>
#include <forte_sem.h>

extern "C" {
#include <MQTTAsync.h>
}

enum MQTTStates {
  NOT_CONNECTED,
  CONNECTION_ASKED,
  SUBSCRIBING,
  ALL_SUBSCRIBED,
};

class MQTTHandler : public CExternalEventHandler, public CThread {
	DECLARE_SINGLETON(MQTTHandler)
public:
	enum RegisterLayerReturnCodes {
		eRegisterLayerSucceeded,
		eWrongClientID,
		eConnectionFailed
	};
	int registerLayer(char* paAddress, char* paClientId, MQTTComLayer* paLayer);

	void unregisterLayer(MQTTComLayer* paLayer);

	MQTTAsync& getClient(void) {
		return smClient;
	}

	//void mqttMessageProcessed(void);

    virtual void enableHandler(void);
    /*!\brief Disable this event source
     */
    virtual void disableHandler(void);
    /*!\brief Sets the priority of the event source
     *
     * \param pa_nPriority new priority of the event source
     */
    virtual void setPriority(int pa_nPriority);
    /*!\brief Get the current priority of the event source
     *
     * \return current priority
     */
    virtual int getPriority(void) const;

protected:
    virtual void run();

private:

    int mqttSubscribe(MQTTComLayer* pa_comLayer);
    int mqttConnect();

    void popLayerFromList(MQTTComLayer* paLayer, CSinglyLinkedList<MQTTComLayer*> *pa_list);

    void resumeSelfSuspend();
    void selfSuspend();

    static void onMqttConnectionLost(void* context, char* cause);

    static int onMqttMessageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message);

    static void onMqttConnectionSucceed(void *context, MQTTAsync_successData *response);
    static void onMqttConnectionFailed(void *context, MQTTAsync_failureData *response);

    static void onSubscribeSucceed(void* context, MQTTAsync_successData* response);
    static void onSubscribeFailed(void* context, MQTTAsync_failureData* response);

    static CIEC_STRING smClientId;
    static CIEC_STRING smAddress;

    static CSyncObject smMQTTMutex;

    static MQTTAsync smClient;
    static MQTTAsync_connectOptions smClientConnectionOptions;

    CSinglyLinkedList<MQTTComLayer*> mlayers;

    CSinglyLinkedList<MQTTComLayer*> mToResubscribe;

    static forte::arch::CSemaphore mStateSemaphore;

    static bool mIsSemaphoreEmpty;

    static MQTTStates smMQTTS_STATE;

};

#endif /* MQTTHANDLER_H_ */
