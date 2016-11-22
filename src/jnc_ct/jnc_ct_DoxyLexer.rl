//..............................................................................
//
//  This file is part of the Jancy toolkit.
//
//  Jancy is distributed under the MIT license.
//  For details see accompanying license.txt file,
//  the public copy of which is also available at:
//  http://tibbo.com/downloads/archive/jancy/license.txt
//
//..............................................................................

// warning C4065: switch statement contains 'default' but no 'case' labels

#pragma warning (disable: 4065)

namespace jnc {
namespace ct {

//..............................................................................

%%{

machine dox;
write data;

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# definitions
#

# whitespace

ws = [ \t\r]+;

# non-whitespace

nws = [^ \t\r\n]+;

# regular char (non-whitespace and non-escape)

rc = [^ \t\r\n\\];

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# main machine
#

main := |*

'\\enum'          { createToken (DoxyTokenKind_Enum); };
'\\enumvalue'     { createToken (DoxyTokenKind_EnumValue); };
'\\struct'        { createToken (DoxyTokenKind_Struct); };
'\\union'         { createToken (DoxyTokenKind_Union); };
'\\class'         { createToken (DoxyTokenKind_Class); };
'\\alias'         { createToken (DoxyTokenKind_Alias); };
'\\var'           { createToken (DoxyTokenKind_Variable); };
'\\variable'      { createToken (DoxyTokenKind_Variable); };
'\\field'         { createToken (DoxyTokenKind_Field); };
'\\fn'            { createToken (DoxyTokenKind_Function); };
'\\function'      { createToken (DoxyTokenKind_Function); };
'\\method'        { createToken (DoxyTokenKind_Function); };
'\\overload'      { createToken (DoxyTokenKind_Overload); };
'\\prop'          { createToken (DoxyTokenKind_Property); };
'\\property'      { createToken (DoxyTokenKind_Property); };
'\\event'         { createToken (DoxyTokenKind_Event); };
'\\typedef'       { createToken (DoxyTokenKind_Typedef); };
'\\namespace'     { createToken (DoxyTokenKind_Namespace); };
'\\group'         { createToken (DoxyTokenKind_Group); };
'\\defgroup'      { createToken (DoxyTokenKind_DefGroup); };
'\\ingroup'       { createToken (DoxyTokenKind_InGroup); };
'\\addtogroup'    { createToken (DoxyTokenKind_AddToGroup); };
'\\title'         { createToken (DoxyTokenKind_Title); };
'\\brief'         { createToken (DoxyTokenKind_Brief); };
'\\see'           { createToken (DoxyTokenKind_SeeAlso); };
'\\seealso'       { createToken (DoxyTokenKind_SeeAlso); };
'\\sa'            { createToken (DoxyTokenKind_SeeAlso); };
'\\footnote'      { createToken (DoxyTokenKind_Footnote); };

'\\' rc*          { createTextToken (DoxyTokenKind_OtherCommand); };

'@{'              { createToken (DoxyTokenKind_OpeningBrace); };
'@}'              { createToken (DoxyTokenKind_ClosingBrace); };

rc ([^\n]* nws)?  { createTextToken (DoxyTokenKind_Text); };

'\n' ws?          { createNewLineToken (), newLine (ts + 1); };
ws                ;

*|;

}%%

//..............................................................................

void
DoxyLexer::init ()
{
	%% write init;
}

void
DoxyLexer::exec ()
{
	%% write exec;
}

//..............................................................................

} // namespace ct
} // namespace jnc
