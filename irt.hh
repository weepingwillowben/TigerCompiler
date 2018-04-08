/* irt.hh
 * api for the Intermediate Representation tree
 */
#pragma once
#include <iostream>
#include <vector>

namespace tiger {
namespace ir {

using const_t = int; //type that Const node will take
const std::string ws = "  "; // whitespace for toStr
using label_t = std::string; // may need to get this from the temp class
using temp_t = std::string; // may need to get this from the temp class


// Base IRT node class, to define the hierarchy.
class IRTNode {
  public:
    using IRTptr = const shared_ptr<IRTNode>;
    
    IRTNode() = default;
    virtual ~IRTNode() = default;
    virtual std::string toStr(std::string spacing = "") const = 0;
};

// class for things that dont return a value
class stm: public IRTNode {
  public:
    using stmPtr = const shared_ptr<stm>;
    
    stm() = default;
    virtual ~stm() = default;
    virtual std::string toStr(std::string spacing) const = 0;
};

// class for things that do return a value
class exp: public IRTNode {
  public:
    using expPtr = const shared_ptr<exp>;
    
    exp() = default;
    virtual ~exp() = default;
    virtual std::string toStr(std::string spacing) const = 0;
};

// like an expList but with pointers
using expPtrList = std::vector<exp::expPtr>;

namespace {
    // helper functions so that our toStrings look almost the same
    std::string oneChildToStr(std::string spacing, std::string name, IRTNode::IRTptr child) {
        return spacing + name + ":\n" + child->toStr(spacing+ws);
    };
    std::string twoChildToStr(std::string spacing, std::string name, IRTNode::IRTptr child1, IRTNode::IRTptr child2) {
        return spacing + name + ":\n" + child1->toStr(spacing+ws) + "\n" + child2->toStr(spacing+ws);
    };

    // ptr names 
    // so that you can get expPtr in things that inherit from stm and vice versa
    using expPtr = exp::expPtr;
    using stmPtr = stm::stmPtr;
}

// printing stuff
inline std::ostream & operator << (std::ostream & os, const IRTNode & node){
    os << node.toStr() << std::endl;
    return os;
}
inline std::ostream & operator << (std::ostream & os, const IRTNode * node){
    os << node->toStr() << std::endl;
    return os;
}

////////////////////////////////////////////////////////////////////////////////
// Here starts the real classes
// They're all from 153-154 in Appel's book
////////////////////////////////////////////////////////////////////////////////

// holds a constant word
class Const: public exp {
  public:
    Const(const_t val): val_(val) {};
    virtual ~Const() = default;
    virtual std::string toStr(std::string spacing) const {
        return spacing + "Const: " + std::to_string(val_);
    };
  private:
    const const_t val_;
};

// symbolic constant n corresponding to an asembly language label
class Name: public exp {
  public:
    Name(label_t val): val_(val) {};
    virtual ~Name() = default;
    virtual std::string toStr(std::string spacing) const {
        return spacing + "Name: " + val_;
    };
  private:
    const label_t val_;
};

// Temportary, like a register but we have infinite of them
class Temp: public exp {
  public:
    Temp(temp_t val): val_(val) {};
    virtual ~Temp() = default;
    virtual std::string toStr(std::string spacing) const {
        return spacing + "Temp: " + val_;
    };
  private:
    const temp_t val_;
};

enum class op_k: int                {PLUS, MINUS, MUL, DIV, AND,  OR, XOR, LSHIFT, RSHIFT, ARSHIFT};
std::vector<std::string> op_names = { "+",   "-", "*", "/", "&", "|", "^",   "<<",   ">>","ARSHIFT"};

class BinOp: public exp {
  public:
    BinOp(op_k o, expPtr l, expPtr r): op_(o), l_(l), r_(r) {};
    virtual ~BinOp() = default;
    virtual std::string toStr(std::string spacing) const {
        return twoChildToStr(spacing, "BinOp " + op_names.at(static_cast<int>(op_)), l_, r_);
    };
  private:
    op_k op_;
    expPtr l_;
    expPtr r_;
};

// evauates exp_ and returns the value at that loaction
class Mem: public exp {
  public:
    Mem(expPtr e): exp_(e){};
    virtual ~Mem() = default;
    virtual std::string toStr(std::string spacing) const {
        return oneChildToStr(spacing, "Mem", exp_);
    }
  private:
    expPtr exp_;
};

// evauates exp_ and returns the value at that loaction
class Call: public exp {
  public:
    Call(expPtr f, expPtrList l): func_(f), args_(l){};
    virtual ~Call() = default;
    virtual std::string toStr(std::string spacing) const {
        std::string argsStr = spacing + ws + "args:\n";        
        for (auto arg : args_){
            argsStr += arg->toStr(spacing + ws + ws);
        }
        return oneChildToStr(spacing, "Call", func_) + argsStr;
    }
  private:
    expPtr func_;
    expPtrList args_;
};

// Sequence of two nodes
// stm_ gets evaluated for side effects
// exp_ gets evaluated for value
class Eseq: public exp {
  public:
    Eseq(stmPtr l, expPtr r): stm_(l), exp_(r)
        {};
    virtual ~Eseq() = default;
    virtual std::string toStr(std::string spacing) const {
        return twoChildToStr(spacing, "Eseq", stm_, exp_);
    };
  private:
    stmPtr stm_;
    expPtr exp_;
};
// The result of the move command will put the value from src_ into the
// memory location or temporary variable at dest_
class Move: public stm {
  public:
    Move(expPtr dest, expPtr src): dest_(dest), src_(src)
        {};
    virtual ~Move() = default;
    virtual std::string toStr(std::string spacing) const {
        return twoChildToStr(spacing, "Eseq", dest_, src_);
    };
  private:
    expPtr dest_;
    expPtr src_;

};




} // ir namespace
} // tiger

