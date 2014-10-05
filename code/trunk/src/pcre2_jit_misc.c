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


#ifndef INCLUDED_FROM_PCRE2_JIT_COMPILE
#error This file must be included from pcre2_jit_compile.c.
#endif


/* FIXME: these are dummy functions */


/*************************************************
*            Free unused JIT memory              *
*************************************************/


PCRE2_EXP_DEFN void PCRE2_CALL_CONVENTION
pcre2_jit_free_unused_memory(pcre2_general_context *gcontext)
{
#ifndef SUPPORT_JIT

(void)gcontext;     /* Suppress warning */

#else  /* SUPPORT_JIT */

/* Dummy code */
SLJIT_UNUSED_ARG(gcontext);
sljit_free_unused_memory_exec();

#endif  /* SUPPORT_JIT */
}



/*************************************************
*            Allocate a JIT stack                *
*************************************************/

PCRE2_EXP_DEFN pcre2_jit_stack * PCRE2_CALL_CONVENTION
pcre2_jit_stack_alloc(pcre2_general_context *gcontext, size_t startsize,
  size_t maxsize)
{
#ifndef SUPPORT_JIT

(void)gcontext;
(void)startsize;
(void)maxsize;
return NULL;

#else  /* SUPPORT_JIT */

pcre2_jit_stack *jit_stack;

if (startsize < 1 || maxsize < 1)
  return NULL;
if (startsize > maxsize)
  startsize = maxsize;
startsize = (startsize + STACK_GROWTH_RATE - 1) & ~(STACK_GROWTH_RATE - 1);
maxsize = (maxsize + STACK_GROWTH_RATE - 1) & ~(STACK_GROWTH_RATE - 1);

jit_stack = PRIV(memctl_malloc)(sizeof(pcre2_real_jit_stack), (pcre2_memctl *)gcontext);
jit_stack->stack = sljit_allocate_stack(startsize, maxsize, &jit_stack->memctl);
return jit_stack;

#endif
}


/*************************************************
*         Assign a JIT stack to a pattern        *
*************************************************/

PCRE2_EXP_DEFN void PCRE2_CALL_CONVENTION
pcre2_jit_stack_assign(const pcre2_code *code, pcre2_jit_callback callback,
  void *callback_data)
{
#ifndef SUPPORT_JIT

(void)code;
(void)callback;
(void)callback_data;

#else  /* SUPPORT_JIT */

pcre2_real_code *re = (pcre2_real_code *)code;
executable_functions *functions;

if (re == NULL)
  return;

functions = (executable_functions *)re->executable_jit;
if (functions != NULL)
  {
  functions->callback = callback;
  functions->callback_data = callback_data;
  }

#endif  /* SUPPORT_JIT */
}


/*************************************************
*               Free a JIT stack                 *
*************************************************/

PCRE2_EXP_DEFN void PCRE2_CALL_CONVENTION
pcre2_jit_stack_free(pcre2_jit_stack *jit_stack)
{
#ifndef SUPPORT_JIT

(void)jit_stack;

#else  /* SUPPORT_JIT */

/* Dummy code */

if (jit_stack != NULL)
  {
  sljit_free_stack((struct sljit_stack *)(jit_stack->stack), &jit_stack->memctl);
  jit_stack->memctl.free(jit_stack, jit_stack->memctl.memory_data);
  }

#endif  /* SUPPORT_JIT */
}


/*************************************************
*              Get size of JIT code              *
*************************************************/

size_t
PRIV(jit_get_size)(void *executable_jit)
{
#ifndef SUPPORT_JIT

(void)executable_jit;
return 0;

#else  /* SUPPORT_JIT */

/* Dummy code */
executable_jit = executable_jit;
return 0;

#endif
}

/* End of pcre2_jit_misc.c */