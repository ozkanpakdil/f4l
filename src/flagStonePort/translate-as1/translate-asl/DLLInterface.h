/*
 * DLL Interface classes for C++ Binary Compatibility article
 * article at http://aegisknight.org/cppinterface.html
 *
 * code author:     Ben Scott   (bscott@iastate.edu)
 * article author:  Chad Austin (aegis@aegisknight.org)
 */
#ifndef DLL_INTERFACE_H
#define DLL_INTERFACE_H

namespace translate
{
class DLLInterface 
{
protected:
  virtual void CALL destroy() = 0;

public:
  void operator delete(void* p) {
    if (p) {
      DLLInterface* i = static_cast<DLLInterface*>(p);
      i->destroy();
    }
  }
};


template<class Interface>
class DLLImpl : public Interface 
{
public:
  virtual ~DLLImpl() { }
  virtual void CALL destroy() {
    delete this;
  }
  void operator delete(void* p) {
    ::operator delete(p);
  }
};

}

#endif
