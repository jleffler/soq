The header 'tree.h' is not standard anywhere.

<hr>

# C Standards

### ISO/IEC 9899:1990 (C89, C90)

The 15 standard headers in C89 are:

```none
<assert.h>  <limits.h>  <signal.h>  <stdlib.h>
<ctype.h>   <locale.h>  <stdarg.h>  <string.h>
<errno.h>   <math.h>    <stddef.h>  <time.h>
<float.h>   <setjmp.h>  <stdio.h>
```

### ISO/IEC 9899:1990/Amd.1:1995

The 3 extra headers introduced in C94<sup>*</sup> (Amendment 1) are:

```none
<iso646.h>  <wchar.h>  <wctype.h>
```

### ISO/IEC 9899:1999 (C99)

The 6 extra headers in C99 are:

```none
<complex.h>  <inttypes.h>  <stdint.h>  <tgmath.h>
<fenv.h>     <stdbool.h>
```

### ISO/IEC 9899:2011 (C11)

The 5 extra headers in C2011 (for a total of 29) are:

```none
<stdalign.h>  <stdatomic.h>  <stdnoreturn.h>  <threads.h>  <uchar.h>
```

### ISO/IEC 9899:2018 (C17, C18)

No extra headers.

### ISO/IEC 9899:2023 (C23)

The 2 extra headers in C2023 (for a total of 31) are:

```none
<stdbit.h>  <stdckdint.h>
```

Some headers become obsolescent, notably:
```
<stdalign.h>  <stdbool.h>  <stdnoreturn.h>
```
<hr>

### ISO/IEC 9045:2008 (POSIX 2008, Single Unix Specification)

Note that [POSIX.1 2008][1] requires many more headers (82, including all the
C99 headers).  The list below repeats the standard C (C99) headers.
Windows requires a different set of headers, of course.

```none
<aio.h>        <libgen.h>       <spawn.h>         <sys/time.h>
<arpa/inet.h>  <limits.h>       <stdarg.h>        <sys/times.h>
<assert.h>     <locale.h>       <stdbool.h>       <sys/types.h>
<complex.h>    <math.h>         <stddef.h>        <sys/uio.h>
<cpio.h>       <monetary.h>     <stdint.h>        <sys/un.h>
<ctype.h>      <mqueue.h>       <stdio.h>         <sys/utsname.h>
<dirent.h>     <ndbm.h>         <stdlib.h>        <sys/wait.h>
<dlfcn.h>      <net/if.h>       <string.h>        <syslog.h>
<errno.h>      <netdb.h>        <strings.h>       <tar.h>
<fcntl.h>      <netinet/in.h>   <stropts.h>       <termios.h>
<fenv.h>       <netinet/tcp.h>  <sys/ipc.h>       <tgmath.h>
<float.h>      <nl_types.h>     <sys/mman.h>      <time.h>
<fmtmsg.h>     <poll.h>         <sys/msg.h>       <trace.h>
<fnmatch.h>    <pthread.h>      <sys/resource.h>  <ulimit.h>
<ftw.h>        <pwd.h>          <sys/select.h>    <unistd.h>
<glob.h>       <regex.h>        <sys/sem.h>       <utime.h>
<grp.h>        <sched.h>        <sys/shm.h>       <utmpx.h>
<iconv.h>      <search.h>       <sys/socket.h>    <wchar.h>
<inttypes.h>   <semaphore.h>    <sys/stat.h>      <wctype.h>
<iso646.h>     <setjmp.h>       <sys/statvfs.h>   <wordexp.h>
<langinfo.h>   <signal.h>
```

Note, too, that X/Open Curses requires another set of headers.  There
was a new version (Release 7) of that specification released in November
2009 (the first update since 1996 — the primary differences are the
loss of official support for termcap and pre-standard C `<varargs.h>`
header).

```none
<curses.h>  <term.h>  <uncntrl.h>
```

### POSIX.1-2024 (IEEE Std 1003.1-2024, The Open Group Base Specifications Issue 8)

[POSIX.1 2024](https://pubs.opengroup.org/onlinepubs/9799919799/) loses
a few headers, and gains a few headers compared to POSIX.1 2008.  Since
it uses the C 2018 standard, it acquires the extra C headers:
```none
<stdalign.h>  <stdatomic.h>  <stdnoreturn.h>  <threads.h>  <uchar.h>
```
It also adds three other headers:
```none
<devctl.h>  <endian.h>  <libintl.h>
```
It loses 4 headers that were previously deprecated:
```none
<stropts.h>  <trace.h>  <ulimit.h>  <utime.h>
```

### Linux Standards Base

There are other headers that you might need to use.  For example, there
is no mention of `<getopt.h>` in these lists, but if you are using GNU
Getopt (for long options, for example), you will need and use that
header.  It is standard on Linux according to the [LSB, Linux Standards
Base](http://www.linuxfoundation.org/collaborate/workgroups/lsb).  An
older version of the LSB was defined as ISO/IEC 23360:2006 in multiple
parts; as of 2025-03-16, the current version of the LSB is 5.0, which
was released June 3, 2015.  There is a section of the document that
defines which headers are included, but there is no convenient table of
the headers in the version I looked at.  It is closely aligned with
POSIX, but has extra facilities beyond what POSIX defines.

<hr>

# C++ Standards

### ISO/IEC 14882:1998 (C++98)

The standard lists 32 headers specific to C++:

```
<algorithm>   <iomanip>   <list>     <ostream>    <streambuf>
<bitset>      <ios>       <locale>   <queue>      <string>
<complex>     <iosfwd>    <map>      <set>        <typeinfo>
<deque>       <iostream>  <memory>   <sstream>    <utility>
<exception>   <istream>   <new>      <stack>      <valarray>
<fstream>     <iterator>  <numeric>  <stdexcept>  <vector>
<functional>  <limits>
```

There are also 18 headers corresponding to headers from C (corresponding to C94):

```none
<cassert>  <ciso646>  <csetjmp>  <cstdio>   <ctime>
<cctype>   <climits>  <csignal>  <cstdlib>  <cwchar>
<cerrno>   <clocale>  <cstdarg>  <cstring>  <cwctype>
<cfloat>   <cmath>    <cstddef>
```

Intriguingly, Annex D (§D.7) lists a deprecated header, `<strstream>`,
that is not mentioned earlier in the standard.  Including that header
with GCC (`g++`) 7.2.0 generates a warning:

    /opt/gcc/v7.2.0/include/c++/7.2.0/backward/backward_warning.h:32:2:
    warning: #warning This file includes at least one deprecated or antiquated
    header which may be removed without further notice at a future date.
    Please use a non-deprecated interface with equivalent functionality
    instead. For a listing of replacement headers and interfaces, consult
    the file backward_warning.h. To disable this warning use -Wno-deprecated. [-Wcpp]

The header `<strstream>` is explicitly listed in the other versions of the standard.

### ISO/IEC 14882:2011 (C++11)

The 53 C++ headers in C++11 are:

```none
<algorithm>           <initializer_list>  <numeric>           <system_error>
<array>               <iomanip>           <ostream>           <thread>
<atomic>              <ios>               <queue>             <tuple>
<bitset>              <iosfwd>            <random>            <type_traits>
<chrono>              <iostream>          <ratio>             <typeindex>
<codecvt>             <istream>           <regex>             <typeinfo>
<complex>             <iterator>          <scoped_allocator>  <unordered_map>
<condition_variable>  <limits>            <set>               <unordered_set>
<deque>               <list>              <sstream>           <utility>
<exception>           <locale>            <stack>             <valarray>
<forward_list>        <map>               <stdexcept>         <vector>
<fstream>             <memory>            <streambuf>
<functional>          <mutex>             <string>
<future>              <new>               <strstream>
```

The 26 headers related to C (C11) are:

```none
<cassert>   <cinttypes>  <csignal>    <cstdio>   <cwchar>
<ccomplex>  <ciso646>    <cstdalign>  <cstdlib>  <cwctype>
<cctype>    <climits>    <cstdarg>    <cstring>
<cerrno>    <clocale>    <cstdbool>   <ctgmath>
<cfenv>     <cmath>      <cstddef>    <ctime>
<cfloat>    <csetjmp>    <cstdint>    <cuchar>
```

### ISO/IEC 14882:2014 (C++14)

_Provisional list of headers based on draft standard N3797 found at
[ISO/IEC
JTC1/SC22/WG21](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3797.pdf)
site.  The data is from tables 14 and 15 in section 17.6.1.2
**Headers**, amended as noted below.  Since the standard has not been
published (as of 2014-09-21), this list is not yet definitive._

The 54 C++ headers in C++14 are:

```none
<algorithm>           <initializer_list>  <numeric>           <strstream>
<array>               <iomanip>           <ostream>           <system_error>
<atomic>              <ios>               <queue>             <thread>
<bitset>              <iosfwd>            <random>            <tuple>
<chrono>              <iostream>          <ratio>             <type_traits>
<codecvt>             <istream>           <regex>             <typeindex>
<complex>             <iterator>          <scoped_allocator>  <typeinfo>
<condition_variable>  <limits>            <set>               <unordered_map>
<deque>               <list>              <shared_mutex>      <unordered_set>
<exception>           <locale>            <sstream>           <utility>
<forward_list>        <map>               <stack>             <valarray>
<fstream>             <memory>            <stdexcept>         <vector>
<functional>          <mutex>             <streambuf>
<future>              <new>               <string>
```

The 26 headers related to C (C11) are unchanged compared with C++11:

```none
<cassert>   <cinttypes>  <csignal>    <cstdio>   <cwchar>
<ccomplex>  <ciso646>    <cstdalign>  <cstdlib>  <cwctype>
<cctype>    <climits>    <cstdarg>    <cstring>
<cerrno>    <clocale>    <cstdbool>   <ctgmath>
<cfenv>     <cmath>      <cstddef>    <ctime>
<cfloat>    <csetjmp>    <cstdint>    <cuchar>
```

There is one new header listed for C++14 compared to C++11, namely `<shared_mutex>`.

_NB: The draft lists a number of the headers (`<deque>`, `<istream>`,
`<stdexcept>`, `<unordered_set>`) twice.  Also, 5 headers from C++11 are
not listed in the tables in the draft, namely `<exception>`,
`<iterator>`, `<ratio>`, `<scoped_allocator>`, and `<thread>`.  Since
§18.8 defines `<exception>`, §24 defines `<iterator>`, §20.11 defines
`<ratio>`, §30 defines `<thread>`, and §30.4 defines `<shared_mutex>`,
this is an example of why you should not trust the draft standards as
being the final word — they contain errors._

### ISO/IEC 14882:2017 (C++17)

_Provisional list of headers in C++17 based on the draft
[N4659](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4659.pdf)
dated 2017-03-21.  This is a transcription of tables 16 and 17 from
section 20.5.1.2 **Headers**.  This is not the final standard; in
theory, something could change._

There are 61 C++ headers:

```none
<algorithm>           <future>            <numeric>           <strstream>
<any>                 <initializer_list>  <optional>          <system_error>
<array>               <iomanip>           <ostream>           <thread>
<atomic>              <ios>               <queue>             <tuple>
<bitset>              <iosfwd>            <random>            <type_traits>
<chrono>              <iostream>          <ratio>             <typeindex>
<codecvt>             <istream>           <regex>             <typeinfo>
<complex>             <iterator>          <scoped_allocator>  <unordered_map>
<condition_variable>  <limits>            <set>               <unordered_set>
<deque>               <list>              <shared_mutex>      <utility>
<exception>           <locale>            <sstream>           <valarray>
<execution>           <map>               <stack>             <variant>
<filesystem>          <memory>            <stdexcept>         <vector>
<forward_list>        <memory_resource>   <streambuf>
<fstream>             <mutex>             <string>
<functional>          <new>               <string_view>
```

The new headers compared to C++14 seem to be: `<any>`, `<execution>`,
`<filesystem>`, `<memory_resource>`, `<optional>`, `<string_view>`,
`<variant>`.

Again, the 26 headers related to C (C11) are unchanged compared with C++11 and C++14:

```none
<cassert>   <cinttypes>  <csignal>    <cstdio>   <cwchar>
<ccomplex>  <ciso646>    <cstdalign>  <cstdlib>  <cwctype>
<cctype>    <climits>    <cstdarg>    <cstring>
<cerrno>    <clocale>    <cstdbool>   <ctgmath>
<cfenv>     <cmath>      <cstddef>    <ctime>
<cfloat>    <csetjmp>    <cstdint>    <cuchar>
```

See also [What are the new features in
C++17?](https://stackoverflow.com/questions/38060436/what-are-the-new-features-in-c17)

Note that some of the 'C library' headers are
[deprecated](https://isocpp.org/files/papers/p0636r0.html) in C++17,
specifically `<ccomplex>`, `<cstdalign>`, `<cstdbool>`, `<ctgmath>` (and
not `<ciso646>`).  The C++ header `<codecvt>` (added in C++11) is also
deprecated in C++17.

### ISO/IEC 14882:2020 (C++20)

_Provisional list of headers in C++20 based on the draft
[N4878](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/n4878.pdf)
dated 2020-12-15.  This is a transcription from the "Index of library
headers", a new section of the document.

There are 99 C++ headers, including the 'C library' headers:

```none
<algorithm>           <csignal>           <istream>           <span>
<any>                 <cstdarg>           <iterator>          <sstream>
<array>               <cstddef>           <latch>             <stack>
<atomic>              <cstdint>           <limits>            <stacktrace>
<barrier>             <cstdio>            <list>              <stdexcept>
<bit>                 <cstdlib>           <locale>            <stop_token>
<bitset>              <cstring>           <map>               <streambuf>
<cassert>             <ctime>             <memory>            <string>
<cctype>              <cuchar>            <memory_resource>   <string_view>
<cerrno>              <cwchar>            <mutex>             <strstream>
<cfenv>               <cwctype>           <new>               <syncstream>
<cfloat>              <deque>             <numbers>           <system_error>
<charconv>            <exception>         <numeric>           <thread>
<chrono>              <execution>         <optional>          <tuple>
<cinttypes>           <filesystem>        <ostream>           <type_traits>
<climits>             <format>            <queue>             <typeindex>
<clocale>             <forward_list>      <random>            <typeinfo>
<cmath>               <fstream>           <ranges>            <unordered_map>
<codecvt>             <functional>        <ratio>             <unordered_set>
<compare>             <future>            <regex>             <utility>
<complex>             <initializer_list>  <scoped_allocator>  <valarray>
<concepts>            <iomanip>           <semaphore>         <variant>
<condition_variable>  <ios>               <set>               <vector>
<coroutine>           <iosfwd>            <shared_mutex>      <version>
<csetjmp>             <iostream>          <source_location>
```

There are also 27 'C standard `.h` headers':

```none
<assert.h>    <iso646.h>    <stdarg.h>     <string.h>
<complex.h>   <limits.h>    <stdatomic.h>  <tgmath.h>
<ctype.h>     <locale.h>    <stdbool.h>    <time.h>
<errno.h>     <math.h>      <stddef.h>     <uchar.h>
<fenv.h>      <setjmp.h>    <stdint.h>     <wchar.h>
<float.h>     <signal.h>    <stdio.h>      <wctype.h>
<inttypes.h>  <stdalign.h>  <stdlib.h>
```

### ISO/IEC 14882:2023 (C++23)

_Provisional list of headers in C++23 based on the draft
[N4928](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/n4928.pdf)
dated 2022-12-18.  This is a transcription from the "Index of library
headers".

There are 107 C++ headers, including the 'C library' headers:

```none
<algorithm>           <cstddef>           <istream>           <span>
<any>                 <cstdint>           <iterator>          <spanstream>
<array>               <cstdio>            <latch>             <sstream>
<atomic>              <cstdlib>           <limits>            <stack>
<barrier>             <cstring>           <list>              <stacktrace>
<bit>                 <ctime>             <locale>            <stdexcept>
<bitset>              <cuchar>            <map>               <stdfloat>
<cassert>             <cwchar>            <mdspan>            <stop_token>
<cctype>              <cwctype>           <memory>            <streambuf>
<cerrno>              <deque>             <memory_resource>   <string>
<cfenv>               <exception>         <mutex>             <string_view>
<cfloat>              <execution>         <new>               <strstream>
<charconv>            <expected>          <numbers>           <syncstream>
<chrono>              <filesystem>        <numeric>           <system_error>
<cinttypes>           <flat_map>          <optional>          <thread>
<climits>             <flat_set>          <ostream>           <tuple>
<clocale>             <format>            <print>             <type_traits>
<cmath>               <forward_list>      <queue>             <typeindex>
<codecvt>             <fstream>           <random>            <typeinfo>
<compare>             <functional>        <ranges>            <unordered_map>
<complex>             <future>            <ratio>             <unordered_set>
<concepts>            <generator>         <regex>             <utility>
<condition_variable>  <initializer_list>  <scoped_allocator>  <valarray>
<coroutine>           <iomanip>           <semaphore>         <variant>
<csetjmp>             <ios>               <set>               <vector>
<csignal>             <iosfwd>            <shared_mutex>      <version>
<cstdarg>             <iostream>          <source_location>
```

There are also 27 'C standard `.h` headers':
```none
<assert.h>    <iso646.h>    <stdarg.h>     <string.h>
<complex.h>   <limits.h>    <stdatomic.h>  <tgmath.h>
<ctype.h>     <locale.h>    <stdbool.h>    <time.h>
<errno.h>     <math.h>      <stddef.h>     <uchar.h>
<fenv.h>      <setjmp.h>    <stdint.h>     <wchar.h>
<float.h>     <signal.h>    <stdio.h>      <wctype.h>
<inttypes.h>  <stdalign.h>  <stdlib.h>
```

<hr>

<sup>*</sup> _The 'off by one year' issues in the dates are due to the time it
takes to process the standard after it is approved.  ANSI approved the
original C standard in [1989][2]; ISO approved it in 1990.  Amendment 1
was approved in 1994; it was released in 1995._

_This answer is available in my [SOQ](https://github.com/jleffler/soq)
(Stack Overflow Questions) repository on GitHub as file `answer.md` in
the
[src/so-0202-7991](https://github.com/jleffler/soq/tree/master/src/so-0202-7991)
sub-directory, along with supporting data files such as
`c++23-headers`._

  [1]: http://www.opengroup.org/onlinepubs/9699919799/toc.htm
  [2]: http://en.wikipedia.org/wiki/ANSI_C

