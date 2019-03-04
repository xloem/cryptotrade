// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME OrderbookCompressedHistoryDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "OrderbookCompressedHistory.hpp"
#include "OrderbookCompressedHistoryDelta.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_OrderbookCompressedHistoryDelta(void *p = 0);
   static void *newArray_OrderbookCompressedHistoryDelta(Long_t size, void *p);
   static void delete_OrderbookCompressedHistoryDelta(void *p);
   static void deleteArray_OrderbookCompressedHistoryDelta(void *p);
   static void destruct_OrderbookCompressedHistoryDelta(void *p);
   static void streamer_OrderbookCompressedHistoryDelta(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OrderbookCompressedHistoryDelta*)
   {
      ::OrderbookCompressedHistoryDelta *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OrderbookCompressedHistoryDelta >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OrderbookCompressedHistoryDelta", ::OrderbookCompressedHistoryDelta::Class_Version(), "OrderbookCompressedHistoryDelta.hpp", 5,
                  typeid(::OrderbookCompressedHistoryDelta), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::OrderbookCompressedHistoryDelta::Dictionary, isa_proxy, 16,
                  sizeof(::OrderbookCompressedHistoryDelta) );
      instance.SetNew(&new_OrderbookCompressedHistoryDelta);
      instance.SetNewArray(&newArray_OrderbookCompressedHistoryDelta);
      instance.SetDelete(&delete_OrderbookCompressedHistoryDelta);
      instance.SetDeleteArray(&deleteArray_OrderbookCompressedHistoryDelta);
      instance.SetDestructor(&destruct_OrderbookCompressedHistoryDelta);
      instance.SetStreamerFunc(&streamer_OrderbookCompressedHistoryDelta);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OrderbookCompressedHistoryDelta*)
   {
      return GenerateInitInstanceLocal((::OrderbookCompressedHistoryDelta*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::OrderbookCompressedHistoryDelta*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_OrderbookCompressedHistory(void *p = 0);
   static void *newArray_OrderbookCompressedHistory(Long_t size, void *p);
   static void delete_OrderbookCompressedHistory(void *p);
   static void deleteArray_OrderbookCompressedHistory(void *p);
   static void destruct_OrderbookCompressedHistory(void *p);
   static void streamer_OrderbookCompressedHistory(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::OrderbookCompressedHistory*)
   {
      ::OrderbookCompressedHistory *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::OrderbookCompressedHistory >(0);
      static ::ROOT::TGenericClassInfo 
         instance("OrderbookCompressedHistory", ::OrderbookCompressedHistory::Class_Version(), "OrderbookCompressedHistory.hpp", 14,
                  typeid(::OrderbookCompressedHistory), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::OrderbookCompressedHistory::Dictionary, isa_proxy, 16,
                  sizeof(::OrderbookCompressedHistory) );
      instance.SetNew(&new_OrderbookCompressedHistory);
      instance.SetNewArray(&newArray_OrderbookCompressedHistory);
      instance.SetDelete(&delete_OrderbookCompressedHistory);
      instance.SetDeleteArray(&deleteArray_OrderbookCompressedHistory);
      instance.SetDestructor(&destruct_OrderbookCompressedHistory);
      instance.SetStreamerFunc(&streamer_OrderbookCompressedHistory);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::OrderbookCompressedHistory*)
   {
      return GenerateInitInstanceLocal((::OrderbookCompressedHistory*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::OrderbookCompressedHistory*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr OrderbookCompressedHistoryDelta::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OrderbookCompressedHistoryDelta::Class_Name()
{
   return "OrderbookCompressedHistoryDelta";
}

//______________________________________________________________________________
const char *OrderbookCompressedHistoryDelta::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OrderbookCompressedHistoryDelta*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OrderbookCompressedHistoryDelta::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OrderbookCompressedHistoryDelta*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OrderbookCompressedHistoryDelta::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OrderbookCompressedHistoryDelta*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OrderbookCompressedHistoryDelta::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OrderbookCompressedHistoryDelta*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr OrderbookCompressedHistory::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *OrderbookCompressedHistory::Class_Name()
{
   return "OrderbookCompressedHistory";
}

//______________________________________________________________________________
const char *OrderbookCompressedHistory::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OrderbookCompressedHistory*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int OrderbookCompressedHistory::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::OrderbookCompressedHistory*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *OrderbookCompressedHistory::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OrderbookCompressedHistory*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *OrderbookCompressedHistory::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::OrderbookCompressedHistory*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void OrderbookCompressedHistoryDelta::Streamer(TBuffer &R__b)
{
   // Stream an object of class OrderbookCompressedHistoryDelta.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> timestamp;
      R__b >> baseQuote;
      quotes.Streamer(R__b);
      depths.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, OrderbookCompressedHistoryDelta::IsA());
   } else {
      R__c = R__b.WriteVersion(OrderbookCompressedHistoryDelta::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << timestamp;
      R__b << baseQuote;
      quotes.Streamer(R__b);
      depths.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OrderbookCompressedHistoryDelta(void *p) {
      return  p ? new(p) ::OrderbookCompressedHistoryDelta : new ::OrderbookCompressedHistoryDelta;
   }
   static void *newArray_OrderbookCompressedHistoryDelta(Long_t nElements, void *p) {
      return p ? new(p) ::OrderbookCompressedHistoryDelta[nElements] : new ::OrderbookCompressedHistoryDelta[nElements];
   }
   // Wrapper around operator delete
   static void delete_OrderbookCompressedHistoryDelta(void *p) {
      delete ((::OrderbookCompressedHistoryDelta*)p);
   }
   static void deleteArray_OrderbookCompressedHistoryDelta(void *p) {
      delete [] ((::OrderbookCompressedHistoryDelta*)p);
   }
   static void destruct_OrderbookCompressedHistoryDelta(void *p) {
      typedef ::OrderbookCompressedHistoryDelta current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_OrderbookCompressedHistoryDelta(TBuffer &buf, void *obj) {
      ((::OrderbookCompressedHistoryDelta*)obj)->::OrderbookCompressedHistoryDelta::Streamer(buf);
   }
} // end of namespace ROOT for class ::OrderbookCompressedHistoryDelta

//______________________________________________________________________________
void OrderbookCompressedHistory::Streamer(TBuffer &R__b)
{
   // Stream an object of class OrderbookCompressedHistory.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> baseTimestamp;
      deltas.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, OrderbookCompressedHistory::IsA());
   } else {
      R__c = R__b.WriteVersion(OrderbookCompressedHistory::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << baseTimestamp;
      deltas.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_OrderbookCompressedHistory(void *p) {
      return  p ? new(p) ::OrderbookCompressedHistory : new ::OrderbookCompressedHistory;
   }
   static void *newArray_OrderbookCompressedHistory(Long_t nElements, void *p) {
      return p ? new(p) ::OrderbookCompressedHistory[nElements] : new ::OrderbookCompressedHistory[nElements];
   }
   // Wrapper around operator delete
   static void delete_OrderbookCompressedHistory(void *p) {
      delete ((::OrderbookCompressedHistory*)p);
   }
   static void deleteArray_OrderbookCompressedHistory(void *p) {
      delete [] ((::OrderbookCompressedHistory*)p);
   }
   static void destruct_OrderbookCompressedHistory(void *p) {
      typedef ::OrderbookCompressedHistory current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_OrderbookCompressedHistory(TBuffer &buf, void *obj) {
      ((::OrderbookCompressedHistory*)obj)->::OrderbookCompressedHistory::Streamer(buf);
   }
} // end of namespace ROOT for class ::OrderbookCompressedHistory

namespace {
  void TriggerDictionaryInitialization_OrderbookCompressedHistoryDict_Impl() {
    static const char* headers[] = {
"OrderbookCompressedHistory.hpp",
"OrderbookCompressedHistoryDelta.hpp",
0
    };
    static const char* includePaths[] = {
"/home/user/pkg/root/include",
"/home/user/src/cryptotrade/bitstamp/dataserver/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "OrderbookCompressedHistoryDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
struct __attribute__((annotate(R"ATTRDUMP(Delta details used within OrderbookCompressedHistory)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$OrderbookCompressedHistoryDelta.hpp")))  __attribute__((annotate("$clingAutoload$OrderbookCompressedHistory.hpp")))  OrderbookCompressedHistoryDelta;
struct __attribute__((annotate(R"ATTRDUMP(slimmed-down storage for orderbook history)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$OrderbookCompressedHistory.hpp")))  OrderbookCompressedHistory;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "OrderbookCompressedHistoryDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "OrderbookCompressedHistory.hpp"
#include "OrderbookCompressedHistoryDelta.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"OrderbookCompressedHistory", payloadCode, "@",
"OrderbookCompressedHistoryDelta", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("OrderbookCompressedHistoryDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_OrderbookCompressedHistoryDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_OrderbookCompressedHistoryDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_OrderbookCompressedHistoryDict() {
  TriggerDictionaryInitialization_OrderbookCompressedHistoryDict_Impl();
}
