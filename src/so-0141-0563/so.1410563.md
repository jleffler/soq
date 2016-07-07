There are several good answers explaining the viewpoint of C++, but
there isn't (yet) another answer that explains how C treats declarations
and definitions with concrete reference to the C standard.  I'm using
ISO/IEC 9899:2011, so all quotes are from that.  There are differences
between C11 and earlier versions (notably, `_Thread_local` is not
relevant in C89/C90 or C99), but the gist is very much the same.

## What the standard says

The C standard has a number of sections of relevance:

* §6.2.1 Scopes of identifiers
* §6.2.2 Linkages of identifiers
* §6.2.4 Storage durations of objects
* §6.7 Declarations
* §6.9 External definitions



## §6.2.1 Scopes of identifiers

1 An identifier can denote an object; a function; a tag or a member of a structure, union, or
enumeration; a typedef name; a label name; a macro name; or a macro parameter. The
same identifier can denote different entities at different points in the program. A member
of an enumeration is called an enumeration constant. Macro names and macro
parameters are not considered further here, because prior to the semantic phase of
program translation any occurrences of macro names in the source file are replaced by the
preprocessing token sequences that constitute their macro definitions.

2 For each different entity that an identifier designates, the identifier is visible (i.e., can be
used) only within a region of program text called its scope. Different entities designated
by the same identifier either have different scopes, or are in different name spaces. There
are four kinds of scopes: function, file, block, and function prototype. (A function
prototype is a declaration of a function that declares the types of its parameters.)

3 A label name is the only kind of identifier that has function scope. It can be used (in a
goto statement) anywhere in the function in which it appears, and is declared implicitly
by its syntactic appearance (followed by a : and a statement).

4 Every other identifier has scope determined by the placement of its declaration (in a
declarator or type specifier). If the declarator or type specifier that declares the identifier
appears outside of any block or list of parameters, the identifier has file scope, which
terminates at the end of the translation unit. If the declarator or type specifier that
declares the identifier appears inside a block or within the list of parameter declarations in
a function definition, the identifier has block scope, which terminates at the end of the
associated block. If the declarator or type specifier that declares the identifier appears within the list of parameter declarations in a function prototype (not part of a function
definition), the identifier has function prototype scope, which terminates at the end of the
function declarator. If an identifier designates two different entities in the same name
space, the scopes might overlap. If so, the scope of one entity (the inner scope) will end
strictly before the scope of the other entity (the outer scope). Within the inner scope, the
identifier designates the entity declared in the inner scope; the entity declared in the outer
scope is hidden (and not visible) within the inner scope.

5 Unless explicitly stated otherwise, where this International Standard uses the term
‘‘identifier’’ to refer to some entity (as opposed to the syntactic construct), it refers to the
entity in the relevant name space whose declaration is visible at the point the identifier
occurs.

6 Two identifiers have the same scope if and only if their scopes terminate at the same
point.

7 Structure, union, and enumeration tags have scope that begins just after the appearance of
the tag in a type specifier that declares the tag. Each enumeration constant has scope that
begins just after the appearance of its defining enumerator in an enumerator list. Any
other identifier has scope that begins just after the completion of its declarator.

8 As a special case, a type name (which is not a declaration of an identifier) is considered to
have a scope that begins just after the place within the type name where the omitted
identifier would appear were it not omitted.






###§6.2.2 Linkages of identifiers


An identifier declared in different scopes or in the same scope more than once can be
made to refer to the same object or function by a process called linkage.<sup>29)</sup> There are
three kinds of linkage: external, internal, and none.

2 In the set of translation units and libraries that constitutes an entire program, each
declaration of a particular identifier with external linkage denotes the same object or
function. Within one translation unit, each declaration of an identifier with internal
linkage denotes the same object or function. Each declaration of an identifier with no
linkage denotes a unique entity.

3 If the declaration of a file scope identifier for an object or a function contains the storageclass
specifier static, the identifier has internal linkage.<sup>30)</sup>


4 For an identifier declared with the storage-class specifier extern in a scope in which a
prior declaration of that identifier is visible,<sup>31)</sup> if the prior declaration specifies internal or
external linkage, the linkage of the identifier at the later declaration is the same as the
linkage specified at the prior declaration. If no prior declaration is visible, or if the prior
declaration specifies no linkage, then the identifier has external linkage.

5 If the declaration of an identifier for a function has no storage-class specifier, its linkage
is determined exactly as if it were declared with the storage-class specifier extern. If
the declaration of an identifier for an object has file scope and no storage-class specifier,
its linkage is external.

6 The following identifiers have no linkage: an identifier declared to be anything other than
an object or a function; an identifier declared to be a function parameter; a block scope
identifier for an object declared without the storage-class specifier extern.
7 If, within a translation unit, the same identifier appears with both internal and external
linkage, the behavior is undefined

<sup>29)</sup> There is no linkage between different identifiers.

<sup>30)</sup> A function declaration can contain the storage-class specifier static only if it is at file scope; see 6.7.1.

<sup>31)</sup> As specified in 6.2.1, the later declaration might hide the prior declaration.





###§6.2.4 Storage durations of objects

1 An object has a storage duration that determines its lifetime. There are four storage
durations: static, thread, automatic, and allocated. Allocated storage is described in
7.22.3.

2 The lifetime of an object is the portion of program execution during which storage is
guaranteed to be reserved for it. An object exists, has a constant address,<sup>33)</sup> and retains
its last-stored value throughout its lifetime.<sup>34)</sup> If an object is referred to outside of its
lifetime, the behavior is undefined. The value of a pointer becomes indeterminate when
the object it points to (or just past) reaches the end of its lifetime.

3 An object whose identifier is declared without the storage-class specifier
`_Thread_local`, and either with external or internal linkage or with the storage-class
specifier static, has static storage duration. Its lifetime is the entire execution of the
program and its stored value is initialized only once, prior to program startup.

4 An object whose identifier is declared with the storage-class specifier _Thread_local
has thread storage duration. Its lifetime is the entire execution of the thread for which it
is created, and its stored value is initialized when the thread is started. There is a distinct
object per thread, and use of the declared name in an expression refers to the object
associated with the thread evaluating the expression. The result of attempting to
indirectly access an object with thread storage duration from a thread other than the one
with which the object is associated is implementation-defined.

5 An object whose identifier is declared with no linkage and without the storage-class
specifier static has automatic storage duration, as do some compound literals. The
result of attempting to indirectly access an object with automatic storage duration from a
thread other than the one with which the object is associated is implementation-defined.

_¶6, 7, 8 omitted_

<sup>33)</sup> The term ‘‘constant address’’ means that two pointers to the object constructed at possibly different
times will compare equal. The address may be different during two different executions of the same
program.


<sup>34)</sup> In the case of a volatile object, the last store need not be explicit in the program.




###§6.7 Declarations

**Constraints**

2 A declaration other than a static_assert declaration shall declare at least a declarator
(other than the parameters of a function or the members of a structure or union), a tag, or
the members of an enumeration.

3 If an identifier has no linkage, there shall be no more than one declaration of the identifier
(in a declarator or type specifier) with the same scope and in the same name space, except
that:
* a typedef name may be redefined to denote the same type as it currently does,
provided that type is not a variably modified type;
* tags may be redeclared as specified in 6.7.2.3.

4 All declarations in the same scope that refer to the same object or function shall specify
compatible types.

**Semantics**

A declaration specifies the interpretation and attributes of a set of identifiers. A _definition_
of an identifier is a declaration for that identifier that:

* for an object, causes storage to be reserved for that object;
* for a function, includes the function body;<sup>119)</sup>
* for an enumeration constant, is the (only) declaration of the identifier;
* for a typedef name, is the first (or only) declaration of the identifier.

6 The declaration specifiers consist of a sequence of specifiers that indicate the linkage,
storage duration, and part of the type of the entities that the declarators denote. The _init-declarator-list_ is a comma-separated sequence of declarators, each of which may have
additional type information, or an initializer, or both. The declarators contain the
identifiers (if any) being declared.

7 If an identifier for an object is declared with no linkage, the type for the object shall be
complete by the end of its declarator, or by the end of its init-declarator if it has an
initializer; in the case of function parameters (including in prototypes), it is the adjusted
type (see 6.7.6.3) that is required to be complete.

<sup>119)</sup> Function definitions have a different syntax, described in 6.9.1.


###§6.9 External definitions




## What that means
