#ifndef OBSERVER_IMPL_BASE_H
#define OBSERVER_IMPL_BASE_H

#include <vector>

namespace DuiLib {

struct MenuParam {
  // 1: remove all
  // 2: remove the sub menu
  WPARAM wParam;
  HWND hWnd;
};

class DUILIB_API ReceiverInterface;

class DUILIB_API ObserverInterface {
 public:
  virtual void AddReceiver(ReceiverInterface* receiver) = 0;
  virtual void RemoveReceiver(ReceiverInterface* receiver) = 0;
  virtual BOOL Broadcast(MenuParam param) = 0;
  virtual BOOL RBroadcast(MenuParam param) = 0;
  virtual BOOL Notify(MenuParam param) = 0;
};

class DUILIB_API ReceiverInterface {
 public:
  virtual void AddObserver(ObserverInterface* observer) = 0;
  virtual void RemoveObserver() = 0;
  virtual BOOL Receive(MenuParam param) = 0;
  virtual BOOL Respond(MenuParam param, ObserverInterface* observer) = 0;
};

class DUILIB_API MenuReceiver;

class DUILIB_API MenuObserver : public ObserverInterface {
  friend class Iterator;

 public:
  MenuObserver();
  virtual ~MenuObserver();
  virtual void AddReceiver(ReceiverInterface* receiver);
  virtual void RemoveReceiver(ReceiverInterface* receiver);
  virtual BOOL Broadcast(MenuParam param);
  virtual BOOL RBroadcast(MenuParam param);
  virtual BOOL Notify(MenuParam param);

  class Iterator {
    MenuObserver& _tbl;
    DWORD index;
    ReceiverInterface* ptr;

   public:
    Iterator(MenuObserver& table);
    Iterator(const Iterator& v);
    ReceiverInterface* next();
  };

 protected:
  // UMU: 改为指针是为了去掉 warning
  std::vector<ReceiverInterface*>* receivers_;
};

class DUILIB_API MenuReceiver : public ReceiverInterface {
 public:
  MenuReceiver();
  virtual ~MenuReceiver();
  virtual void AddObserver(ObserverInterface* observer);
  virtual void RemoveObserver();
  virtual BOOL Receive(MenuParam param);
  virtual BOOL Respond(MenuParam param, ObserverInterface* observer);

 protected:
  // UMU: 改为指针是为了去掉 warning
  std::vector<ObserverInterface*>* observers_;
};
}
#endif  // OBSERVER_IMPL_BASE_H
