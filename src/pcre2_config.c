/*************************************************
*      Perl-Compatible Regular Expressions       *
*************************************************/

/* PCRE is a library of functions to support regular expressions whose syntax
and semantics are as close as possible to those of the Perl 5 language.

                       Written by Philip Hazel
     Original API code Copyright (c) 1997-2012 University of Cambridge
         New API code Copyright (c) 2014 University of Cambridge

-----------------------------------------------------------------------------
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of the University of Cambridge nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "pcre2_internal.h"

/* These macros are the standard way of turning unquoted text into C strings.
They allow macros like PCRE2_MAJOR to be defined without quotes, which is
convenient for user programs that want to test their values. */

#define STRING(a)  # a
#define XSTRING(s) STRING(s)


/*************************************************
* Return info about what features are configured *
*************************************************/

/* Most of the requests return an int value; others require more memory and do 
their own checks.

Arguments:
  what             what information is required
  where            where to put the information
  length           length of "where" in bytes 

Returns:           0 if data returned
                   PCRE2_ERROR_BADLENGTH if not enough memory
                   PCRE2_ERROR_BADOPTION if "where" not recognized
*/

PCRE2_EXP_DEFN int PCRE2_CALL_CONVENTION
pcre2_config(int what, void *where, size_t length)
{
if (length < sizeof(int)) return PCRE2_ERROR_BADLENGTH;

switch (what)
  {
  default: 
  return PCRE2_ERROR_BADOPTION;

  case PCRE2_CONFIG_BSR:
#ifdef BSR_ANYCRLF
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;

  case PCRE2_CONFIG_JIT:
#ifdef SUPPORT_JIT
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;

  case PCRE2_CONFIG_JITTARGET:
#ifdef SUPPORT_JIT
FIXME: This needs re-design.
  *((const char **)where) = PRIV(jit_get_target)();
#else
  *((const char **)where) = NULL;
#endif
  break;

  case PCRE2_CONFIG_LINK_SIZE:
  *((int *)where) = LINK_SIZE;
  break;

  case PCRE2_CONFIG_MATCH_LIMIT:
  if (length < sizeof(unsigned long int)) return PCRE2_ERROR_BADLENGTH;
  *((unsigned long int *)where) = MATCH_LIMIT;
  break;

  case PCRE2_CONFIG_MATCH_LIMIT_RECURSION:
  if (length < sizeof(unsigned long int)) return PCRE2_ERROR_BADLENGTH;
  *((unsigned long int *)where) = MATCH_LIMIT_RECURSION;
  break;

  case PCRE2_CONFIG_NEWLINE:
  *((int *)where) = NEWLINE_DEFAULT;
  break;

  case PCRE2_CONFIG_PARENS_LIMIT:
  if (length < sizeof(unsigned long int)) return PCRE2_ERROR_BADLENGTH;
  *((unsigned long int *)where) = PARENS_NEST_LIMIT;
  break;

  case PCRE2_CONFIG_STACKRECURSE:
#ifdef NO_RECURSE
  *((int *)where) = 0;
#else
  *((int *)where) = 1;
#endif
  break;

  case PCRE2_CONFIG_UTF:
#if defined SUPPORT_UTF
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;
  
  /* The hackery in setting "v" below is to cope with the case when 
  PCRE2_PRERELEASE is set to an empty string (which it is for real releases).
  If the second alternative is used in this case, it does not leave a space 
  before the date. On the other hand, if all four macros are put into a single
  XSTRING when PCRE2_PRERELEASE is not empty, an unwanted space is inserted. 
  There are problems using an "obvious" approach like this:
  
     XSTRING(PCRE2_MAJOR) "." XSTRING(PCRE_MINOR) 
     XSTRING(PCRE2_PRERELEASE) " " XSTRING(PCRE_DATE)

  because, when PCRE2_PRERELEASE is empty, this leads to an attempted expansion
  of STRING(). The C standard states: "If (before argument substitution) any
  argument consists of no preprocessing tokens, the behavior is undefined." It
  turns out the gcc treats this case as a single empty string - which is what
  we really want - but Visual C grumbles about the lack of an argument for the
  macro. Unfortunately, both are within their rights. As there seems to be no 
  way to test for a macro's value being empty at compile time, we have to 
  resort to a runtime test. */
  
  case PCRE2_CONFIG_VERSION:
    { 
    PCRE2_UCHAR *t = (PCRE2_UCHAR *)where;
    const char *v = (XSTRING(Z PCRE2_PRERELEASE)[1] == 0)?
      XSTRING(PCRE2_MAJOR.PCRE2_MINOR PCRE2_DATE) :
      XSTRING(PCRE2_MAJOR.PCRE2_MINOR) XSTRING(PCRE2_PRERELEASE PCRE2_DATE);
    if (strlen(v) >= BYTES2CU(length) - 1) return PCRE2_ERROR_BADLENGTH; 
    while (*v != 0) *t++ = *v++;
    *t = 0;
    return t - (PCRE2_UCHAR *)where;
    } 
  }

return 0;
}

/* End of pcre2_config.c */