/* irt.hh
 * api for the Intermediate Representation tree
 */
#pragma once
#include <iostream>

namespace tiger {
namespace ir {

using const_t = int; //type that Const node will take

// Base IRT node class, to define the hierarchy.
class IRTNode {
  public:
    using IRTptr = const shared_ptr<IRTNode>;
    
    IRTNode() = default;
    virtual ~IRTNode() = default;
    virtual std::string toStr() const = 0;
};

inline std::ostream & operator << (std::ostream & os, const IRTNode & node){
    os << node.toStr() << std::endl;
    return os;
}
inline std::ostream & operator << (std::ostream & os, const IRTNode * node){
    os << node->toStr() << std::endl;
    return os;
}

class Eseq: public IRTNode {
  public:
    Eseq(IRTptr, IRTptr){};
    virtual ~Eseq() = default;
    virtual std::string toStr() const {return "";};
};
class Move: public IRTNode {
  public:
    Move(IRTptr, IRTptr){};
    virtual ~Move() = default;
    virtual std::string toStr() const {return "";};
};
class Mem: public IRTNode {
  public:
    Mem(IRTptr){};
    virtual ~Mem() = default;
    virtual std::string toStr() const {return "";};
};
class Const: public IRTNode {
  public:
    Const(const_t){};
    virtual ~Const() = default;
    virtual std::string toStr() const {return "";};
};


} // ir namespace
} // tiger

