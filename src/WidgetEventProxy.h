#pragma once

#include <vector>

#include <QtWidgets/QWidget>

/*
 * Any widget that should be signalled from the device side should derive this
 * class
 */
class ProxiedWidget : public QWidget {
  Q_OBJECT

public slots:
  void trigger_repaint_slot() { Invoke_Repaint(); }

public:
  using QWidget::QWidget;

  // invoke GUI update
  virtual void Invoke_Repaint() = 0;
};

/*
 * Event proxy object for signalling the GUI from device side
 */
class WidgetEventProxy : public QObject {
  Q_OBJECT

private:
  static WidgetEventProxy *mInstance;

  // vector of listeners
  std::vector<ProxiedWidget *> mListeners;

public:
  static WidgetEventProxy *Instance();

  // registers a new listener to update events
  void Register_Listener(ProxiedWidget *obj);

  // emits a new update event
  void Emit();
};
