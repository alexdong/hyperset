/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
#ifndef hyperset_H
#define hyperset_H

#include <TProcessor.h>
#include "hyperset_types.h"

namespace hyperset {

class hypersetIf {
 public:
  virtual ~hypersetIf() {}
  virtual int32_t calc(const std::string& query) = 0;
  virtual void add(const std::string& name, const std::vector<int32_t> & vals) = 0;
  virtual void save() = 0;
};

class hypersetNull : virtual public hypersetIf {
 public:
  virtual ~hypersetNull() {}
  int32_t calc(const std::string& /* query */) {
    int32_t _return = 0;
    return _return;
  }
  void add(const std::string& /* name */, const std::vector<int32_t> & /* vals */) {
    return;
  }
  void save() {
    return;
  }
};

class hyperset_calc_args {
 public:

  hyperset_calc_args() : query("") {
  }

  virtual ~hyperset_calc_args() throw() {}

  std::string query;

  struct __isset {
    __isset() : query(false) {}
    bool query;
  } __isset;

  bool operator == (const hyperset_calc_args & rhs) const
  {
    if (!(query == rhs.query))
      return false;
    return true;
  }
  bool operator != (const hyperset_calc_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const hyperset_calc_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_calc_pargs {
 public:


  virtual ~hyperset_calc_pargs() throw() {}

  const std::string* query;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_calc_result {
 public:

  hyperset_calc_result() : success(0) {
  }

  virtual ~hyperset_calc_result() throw() {}

  int32_t success;

  struct __isset {
    __isset() : success(false) {}
    bool success;
  } __isset;

  bool operator == (const hyperset_calc_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const hyperset_calc_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const hyperset_calc_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_calc_presult {
 public:


  virtual ~hyperset_calc_presult() throw() {}

  int32_t* success;

  struct __isset {
    __isset() : success(false) {}
    bool success;
  } __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class hyperset_add_args {
 public:

  hyperset_add_args() : name("") {
  }

  virtual ~hyperset_add_args() throw() {}

  std::string name;
  std::vector<int32_t>  vals;

  struct __isset {
    __isset() : name(false), vals(false) {}
    bool name;
    bool vals;
  } __isset;

  bool operator == (const hyperset_add_args & rhs) const
  {
    if (!(name == rhs.name))
      return false;
    if (!(vals == rhs.vals))
      return false;
    return true;
  }
  bool operator != (const hyperset_add_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const hyperset_add_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_add_pargs {
 public:


  virtual ~hyperset_add_pargs() throw() {}

  const std::string* name;
  const std::vector<int32_t> * vals;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_add_result {
 public:

  hyperset_add_result() {
  }

  virtual ~hyperset_add_result() throw() {}


  bool operator == (const hyperset_add_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const hyperset_add_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const hyperset_add_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_add_presult {
 public:


  virtual ~hyperset_add_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class hyperset_save_args {
 public:

  hyperset_save_args() {
  }

  virtual ~hyperset_save_args() throw() {}


  bool operator == (const hyperset_save_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const hyperset_save_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const hyperset_save_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_save_pargs {
 public:


  virtual ~hyperset_save_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_save_result {
 public:

  hyperset_save_result() {
  }

  virtual ~hyperset_save_result() throw() {}


  bool operator == (const hyperset_save_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const hyperset_save_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const hyperset_save_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class hyperset_save_presult {
 public:


  virtual ~hyperset_save_presult() throw() {}


  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class hypersetClient : virtual public hypersetIf {
 public:
  hypersetClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  hypersetClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t calc(const std::string& query);
  void send_calc(const std::string& query);
  int32_t recv_calc();
  void add(const std::string& name, const std::vector<int32_t> & vals);
  void send_add(const std::string& name, const std::vector<int32_t> & vals);
  void recv_add();
  void save();
  void send_save();
  void recv_save();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class hypersetProcessor : virtual public ::apache::thrift::TProcessor {
 protected:
  boost::shared_ptr<hypersetIf> iface_;
  virtual bool process_fn(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, std::string& fname, int32_t seqid);
 private:
  std::map<std::string, void (hypersetProcessor::*)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*)> processMap_;
  void process_calc(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot);
  void process_add(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot);
  void process_save(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot);
 public:
  hypersetProcessor(boost::shared_ptr<hypersetIf> iface) :
    iface_(iface) {
    processMap_["calc"] = &hypersetProcessor::process_calc;
    processMap_["add"] = &hypersetProcessor::process_add;
    processMap_["save"] = &hypersetProcessor::process_save;
  }

  virtual bool process(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot);
  virtual ~hypersetProcessor() {}
};

class hypersetMultiface : virtual public hypersetIf {
 public:
  hypersetMultiface(std::vector<boost::shared_ptr<hypersetIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~hypersetMultiface() {}
 protected:
  std::vector<boost::shared_ptr<hypersetIf> > ifaces_;
  hypersetMultiface() {}
  void add(boost::shared_ptr<hypersetIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  int32_t calc(const std::string& query) {
    uint32_t sz = ifaces_.size();
    for (uint32_t i = 0; i < sz; ++i) {
      if (i == sz - 1) {
        return ifaces_[i]->calc(query);
      } else {
        ifaces_[i]->calc(query);
      }
    }
  }

  void add(const std::string& name, const std::vector<int32_t> & vals) {
    uint32_t sz = ifaces_.size();
    for (uint32_t i = 0; i < sz; ++i) {
      ifaces_[i]->add(name, vals);
    }
  }

  void save() {
    uint32_t sz = ifaces_.size();
    for (uint32_t i = 0; i < sz; ++i) {
      ifaces_[i]->save();
    }
  }

};

} // namespace

#endif
