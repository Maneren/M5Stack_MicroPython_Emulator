#include "WidgetEventProxy.h"

WidgetEventProxy* WidgetEventProxy::mInstance = nullptr;

WidgetEventProxy* WidgetEventProxy::Instance() {
	if (!mInstance) {
		mInstance = new WidgetEventProxy();
	}

	return mInstance;
}

void WidgetEventProxy::Register_Listener(ProxiedWidget* obj) {
	mListeners.push_back(obj);
}

void WidgetEventProxy::Emit() {
	for (auto obj : mListeners) {
		QMetaObject::invokeMethod(obj, "trigger_repaint_slot", Qt::QueuedConnection);
	}
}
