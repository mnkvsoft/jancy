// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#include "jnc_ct_CallConv.h"
#include "jnc_ct_FunctionArg.h"

namespace jnc {
namespace ct {

class FunctionPtrType;
class NamedType;
class ClassType;
class ClassPtrType;
class ReactorClassType;
class CdeclCallConv_msc64;
class Function;

struct FunctionPtrTypeTuple;

//.............................................................................

enum FunctionTypeFlag
{
	FunctionTypeFlag_VarArg      = 0x010000,
	FunctionTypeFlag_Throws      = 0x020000,
	FunctionTypeFlag_ByValArgs   = 0x040000,
	FunctionTypeFlag_CoercedArgs = 0x080000,
	FunctionTypeFlag_Automaton   = 0x100000,
	FunctionTypeFlag_Unsafe      = 0x200000,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

const char*
getFunctionTypeFlagString (FunctionTypeFlag flag);

//.............................................................................

enum FunctionPtrTypeKind
{
	FunctionPtrTypeKind_Normal = 0,
	FunctionPtrTypeKind_Weak,
	FunctionPtrTypeKind_Thin,
	FunctionPtrTypeKind__Count,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

const char*
getFunctionPtrTypeKindString (FunctionPtrTypeKind ptrTypeKind);

//.............................................................................

class FunctionType: public Type
{
	friend class TypeMgr;
	friend class ClassType;
	friend class CallConv;
	friend class CallConv_msc32;
	friend class CallConv_gcc32;
	friend class CdeclCallConv_msc64;
	friend class CdeclCallConv_gcc64;

protected:
	CallConv* m_callConv;
	Type* m_returnType;
	ImportType* m_returnType_i;
	sl::Array <FunctionArg*> m_argArray;
	sl::Array <uint_t> m_argFlagArray; // args can be shared between func types
	sl::String m_argSignature;
	sl::String m_typeModifierString;
	sl::String m_argString;
	FunctionType* m_shortType;
	FunctionType* m_stdObjectMemberMethodType;
	Function* m_abstractFunction;
	FunctionPtrTypeTuple* m_functionPtrTypeTuple;
	ReactorClassType* m_reactorIfaceType;

public:
	FunctionType ();

	CallConv*
	getCallConv ()
	{
		return m_callConv;
	}

	Type*
	getReturnType ()
	{
		return m_returnType;
	}

	ImportType*
	getReturnType_i ()
	{
		return m_returnType_i;
	}

	sl::Array <FunctionArg*>
	getArgArray ()
	{
		return m_argArray;
	}

	sl::Array <uint_t>
	getArgFlagArray ()
	{
		return m_argFlagArray;
	}

	sl::String
	getArgSignature ();

	sl::String
	getArgString ();

	sl::String
	getTypeModifierString ();

	bool
	isMemberMethodType ()
	{
		return !m_argArray.isEmpty () && m_argArray [0]->getStorageKind () == StorageKind_This;
	}

	Type*
	getThisArgType ()
	{
		return isMemberMethodType () ? m_argArray [0]->getType () : NULL;
	}

	DerivableType*
	getThisTargetType ();

	FunctionType*
	getShortType ()
	{
		return m_shortType;
	}

	FunctionType*
	getMemberMethodType (
		DerivableType* type,
		uint_t thisArgFlags = 0
		);

	FunctionType*
	getStdObjectMemberMethodType ();

	Function*
	getAbstractFunction ();

	FunctionPtrType*
	getFunctionPtrType (
		TypeKind typeKind,
		FunctionPtrTypeKind ptrTypeKind = FunctionPtrTypeKind_Normal,
		uint_t flags = 0
		);

	FunctionPtrType*
	getFunctionPtrType (
		FunctionPtrTypeKind ptrTypeKind = FunctionPtrTypeKind_Normal,
		uint_t flags = 0
		)
	{
		return getFunctionPtrType (TypeKind_FunctionPtr, ptrTypeKind, flags);
	}

	ClassType*
	getMulticastType ();

	static
	sl::String
	createSignature (
		CallConv* callConv,
		Type* returnType,
		Type* const* argTypeArray,
		size_t argCount,
		uint_t flags
		);

	static
	sl::String
	createSignature (
		CallConv* callConv,
		Type* returnType,
		FunctionArg* const* argArray,
		size_t argCount,
		uint_t flags
		);

	static
	sl::String
	createFlagSignature (uint_t flags);

	static
	sl::String
	createArgSignature (
		Type* const* argTypeArray,
		size_t argCount,
		uint_t flags
		);

	static
	sl::String
	createArgSignature (
		FunctionArg* const* argArray,
		size_t argCount,
		uint_t flags
		);

	sl::String
	createArgSignature ()
	{
		return createArgSignature (m_argArray, m_argArray.getCount (), m_flags);
	}

	virtual
	bool
	compile ();

protected:
	virtual
	void
	prepareTypeString ();

	virtual
	void
	prepareLlvmType ();

	virtual
	void
	prepareLlvmDiType ();

	virtual
	bool
	calcLayout ();
};

//.............................................................................

} // namespace ct
} // namespace jnc