#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef RRAPI_LIB_MAIN
#	define RRAPI_EXPORT	__declspec(dllexport)
#else
#	define RRAPI_EXPORT	__declspec(dllimport)
#endif

#ifndef RRAPI_USE_NAMESPACE
#	define RRAPI_NS_BEGIN			namespace RRAPI {
#	define RRAPI_NS_END				};
#	define RRAPI_USE_NAMESPACE
#endif

typedef unsigned long   UID;
typedef unsigned long   PAGEID;
typedef unsigned long   ORDERID;
typedef unsigned long   STATUSID;
typedef unsigned long   LBSID;
typedef unsigned long   PLACEID;
typedef unsigned long   COMMENTID;

#endif	//GLOBAL_H
