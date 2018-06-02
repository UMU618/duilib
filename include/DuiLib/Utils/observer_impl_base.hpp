#ifndef OBSERVER_IMPL_BASE_HPP
#define OBSERVER_IMPL_BASE_HPP

#include <map>

template <typename ReturnT, typename ParamT>
class ReceiverImplBase;

template <typename ReturnT, typename ParamT>
class ObserverImplBase {
 public:
  virtual void AddReceiver(ReceiverImplBase<ReturnT, ParamT>* receiver) = 0;
  virtual void RemoveReceiver(ReceiverImplBase<ReturnT, ParamT>* receiver) = 0;
  virtual ReturnT Broadcast(ParamT param) = 0;
  virtual ReturnT RBroadcast(ParamT param) = 0;
  virtual ReturnT Notify(ParamT param) = 0;
};

template <typename ReturnT, typename ParamT>
class ReceiverImplBase {
 public:
  virtual void AddObserver(ObserverImplBase<ReturnT, ParamT>* observer) = 0;
  virtual void RemoveObserver() = 0;
  virtual ReturnT Receive(ParamT param) = 0;
  virtual ReturnT Respond(ParamT param,
                          ObserverImplBase<ReturnT, ParamT>* observer) = 0;
};

template <typename ReturnT, typename ParamT>
class ReceiverImpl;

template <typename ReturnT, typename ParamT>
class ObserverImpl : public ObserverImplBase<ReturnT, ParamT> {
  template <typename ReturnT, typename ParamT>
  friend class Iterator;

 public:
  ObserverImpl() {
    receivers_ = new std::vector<ReceiverImplBase<ReturnT, ParamT>*>;
  }

  virtual ~ObserverImpl() { delete receivers_; }

  virtual void AddReceiver(ReceiverImplBase<ReturnT, ParamT>* receiver) {
    if (receiver == NULL)
      return;

    receivers_->push_back(receiver);
    receiver->AddObserver(this);
  }

  virtual void RemoveReceiver(ReceiverImplBase<ReturnT, ParamT>* receiver) {
    if (receiver == NULL)
      return;

    for (auto it = receivers_->begin(); it != receivers_->end(); ++it) {
      if (*it == receiver) {
        receivers_->erase(it);
        break;
      }
    }
  }

  virtual ReturnT Broadcast(ParamT param) {
    for (auto it = receivers_->begin(); it != receivers_->end(); ++it) {
      (*it)->Receive(param);
    }

    return ReturnT();
  }

  virtual ReturnT RBroadcast(ParamT param) {
    for (auto it = receivers_->rbegin(); it != receivers_->rend(); ++it) {
      (*it)->Receive(param);
    }

    return ReturnT();
  }

  virtual ReturnT Notify(ParamT param) {
    for (auto it = receivers_->begin(); it != receivers_->end(); ++it) {
      (*it)->Respond(param, this);
    }

    return ReturnT();
  }

  template <typename ReturnT, typename ParamT>
  class Iterator {
    ObserverImpl<ReturnT, ParamT>& _tbl;
    DWORD index;
    ReceiverImplBase<ReturnT, ParamT>* ptr;

   public:
    Iterator(ObserverImpl& table) : _tbl(table), index(0), ptr(NULL) {}

    Iterator(const Iterator& v) : _tbl(v._tbl), index(v.index), ptr(v.ptr) {}

    ReceiverImplBase<ReturnT, ParamT>* next() {
      if (index >= _tbl.receivers_->size())
        return NULL;

      for (; index < _tbl.receivers_->size();) {
        ptr = _tbl.receivers_->at(index++);
        if (ptr)
          return ptr;
      }
      return NULL;
    }
  };

 protected:
  // UMU: 改为指针是为了去掉 warning
  std::vector<ReceiverImplBase<ReturnT, ParamT>*>* receivers_;
};

template <typename ReturnT, typename ParamT>
class ReceiverImpl : public ReceiverImplBase<ReturnT, ParamT> {
 public:
  ReceiverImpl() {
    observers_ = new std::vector<ObserverImplBase<ReturnT, ParamT>*>;
  }

  virtual ~ReceiverImpl() { delete observers_; }

  virtual void AddObserver(ObserverImplBase<ReturnT, ParamT>* observer) {
    observers_->push_back(observer);
  }

  virtual void RemoveObserver() {
    for (auto it = observers_->begin(); it != observers_->end(); ++it) {
      (*it)->RemoveReceiver(this);
    }
  }

  virtual ReturnT Receive(ParamT param) { return ReturnT(); }

  virtual ReturnT Respond(ParamT param,
                          ObserverImplBase<ReturnT, ParamT>* observer) {
    return ReturnT();
  }

 protected:
  // UMU: 改为指针是为了去掉 warning
  std::vector<ObserverImplBase<ReturnT, ParamT>*>* observers_;
};

#endif  // OBSERVER_IMPL_BASE_HPP