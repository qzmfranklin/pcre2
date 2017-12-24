licenses(['notice'])


if repository_name() == '@':
    gendir = '$(GENDIR)/%s' % package_name()
else:
    gendir = '$(GENDIR)/external/%s' % repository_name.lstrip('@')

cc_library(
    name = 'pcre2',
    visibility = [
        '//visibility:public',
    ],
    srcs = [
        'src/pcre2_auto_possess.c',
        'src/pcre2_compile.c',
        'src/pcre2_config.c',
        'src/pcre2_context.c',
        'src/pcre2_convert.c',
        'src/pcre2_dfa_match.c',
        'src/pcre2_error.c',
        'src/pcre2_extuni.c',
        'src/pcre2_find_bracket.c',
        'src/pcre2_internal.h',
        'src/pcre2_intmodedep.h',
        'src/pcre2_jit_compile.c',
        'src/pcre2_maketables.c',
        'src/pcre2_match.c',
        'src/pcre2_match_data.c',
        'src/pcre2_newline.c',
        'src/pcre2_ord2utf.c',
        'src/pcre2_pattern_info.c',
        'src/pcre2_serialize.c',
        'src/pcre2_string_utils.c',
        'src/pcre2_study.c',
        'src/pcre2_substitute.c',
        'src/pcre2_substring.c',
        'src/pcre2_tables.c',
        'src/pcre2_ucd.c',
        'src/pcre2_ucp.h',
        'src/pcre2_valid_utf.c',
        'src/pcre2_xclass.c',
        'src/pcre2posix.c',
        'src/pcre2posix.h',
        'src/sljit/sljitConfig.h',
        'src/sljit/sljitConfigInternal.h',
        'src/sljit/sljitLir.h',

        # Generated files:
        ':pcre2_chartables_c',
    ],
    hdrs = [
        ':pcre2_h',
    ],
    textual_hdrs = [
        'src/pcre2_jit_compile.c',
        'src/pcre2_jit_match.c',
        'src/pcre2_jit_misc.c',
        'src/sljit/sljitExecAllocator.c',
        'src/sljit/sljitLir.c',
        'src/sljit/sljitNativeARM_32.c',
        'src/sljit/sljitNativeARM_64.c',
        'src/sljit/sljitNativeARM_T2_32.c',
        'src/sljit/sljitNativeMIPS_32.c',
        'src/sljit/sljitNativeMIPS_64.c',
        'src/sljit/sljitNativeMIPS_common.c',
        'src/sljit/sljitNativePPC_32.c',
        'src/sljit/sljitNativePPC_64.c',
        'src/sljit/sljitNativePPC_common.c',
        'src/sljit/sljitNativeSPARC_32.c',
        'src/sljit/sljitNativeSPARC_common.c',
        'src/sljit/sljitNativeTILEGX-encoder.c',
        'src/sljit/sljitNativeTILEGX_64.c',
        'src/sljit/sljitNativeX86_32.c',
        'src/sljit/sljitNativeX86_64.c',
        'src/sljit/sljitNativeX86_common.c',
        'src/sljit/sljitProtExecAllocator.c',
        'src/sljit/sljitUtils.c',
    ],
    defines = [
        # These macros need to be propagated to depending targets.

        # See the page below for a detailed explanation of these macros:
        #       https://www.pcre.org/current/doc/html/pcre2build.html

        # This is the bit-width for a character.  Valid values for this macro
        # are: 8, 16, 32.  Usually just use 8.
        'PCRE2_CODE_UNIT_WIDTH=8',

        # Use normal link size in 8-bit mode.
        'LINK_SIZE=2',
    ],
    copts = [
        # We do not use the config.h file.  Instead, explicitly pass in the
        # configuration macros here.
        #
        # How to generate all these macros?
        #   1.  By looking at the config.h file that is normally generated.
        #       grep '#define' src/config.h.generic
        #   2.  By grinding through the compiling errors.
        #
        # NOTE: Please keep this list of macros sorted.
        '-DHAVE_BCOPY=1',
        '-DHAVE_DIRENT_H=1',
        '-DHAVE_DLFCN_H=1',
        '-DHAVE_INTTYPES_H=1',
        '-DHAVE_LIMITS_H=1',
        '-DHAVE_MEMMOVE=1',
        '-DHAVE_MEMORY_H=1',
        '-DHAVE_MKOSTEMP=1',
        '-DHAVE_SECURE_GETENV=1',
        '-DHAVE_STDINT_H=1',
        '-DHAVE_STDLIB_H=1',
        '-DHAVE_STRERROR=1',
        '-DHAVE_STRINGS_H=1',
        '-DHAVE_STRING_H=1',
        '-DHAVE_SYS_STAT_H=1',
        '-DHAVE_SYS_TYPES_H=1',
        '-DHAVE_SYS_WAIT_H=1',
        '-DHAVE_UNISTD_H=1',
        '-DHAVE_VISIBILITY=1',
        '-DHAVE_ZLIB_H=1',
        '-DHEAP_LIMIT=20000000',
        '-DLINK_SIZE=2',
        '-DLT_OBJDIR=".libs/"',
        '-DMATCH_LIMIT=10000000',
        '-DMATCH_LIMIT_DEPTH=MATCH_LIMIT',
        '-DMAX_NAME_COUNT=10000',
        '-DMAX_NAME_SIZE=32',
        '-DNEWLINE_DEFAULT=2',
        '-DPACKAGE="pcre2"',
        '-DPACKAGE_BUGREPORT=""',
        '-DPACKAGE_NAME="PCRE2"',
        '-DPACKAGE_STRING="PCRE2=10.31-RC1"',
        '-DPACKAGE_TARNAME="pcre2"',
        '-DPACKAGE_URL=""',
        '-DPACKAGE_VERSION="10.31-RC1"',
        '-DPARENS_NEST_LIMIT=250',
        '-DPCRE2GREP_BUFSIZE=20480',
        '-DPCRE2GREP_MAX_BUFSIZE=1048576',
        '-DPCRE2_CONFIG_COMPILED_WIDTHS=14',
        '-DPCRE2_CONFIG_NEVER_BACKSLASH_C=13',
        '-DPCRE2_ERROR_END_BACKSLASH=101',
        '-DPCRE2_ERROR_END_BACKSLASH_C=102',
        '-DPCRE2_ERROR_MISSING_SQUARE_BRACKET=106',
        '-DPCRE2_INFO_EXTRAOPTIONS=26',
        '-DSTDC_HEADERS=1',
        '-DSUPPORT_JIT',
        '-DSUPPORT_PCRE2GREP_CALLOUT',
        '-DSUPPORT_PCRE2GREP_JIT',
        '-DSUPPORT_PCRE2_8',
        '-DSUPPORT_UNICODE',
        '-DVERSION="10.31-RC1"',
        r'-DPCRE2POSIX_EXP_DECL="extern __attribute__((visibility (\"default\")))"',
        r'-DPCRE2POSIX_EXP_DEFN="extern __attribute__((visibility (\"default\")))"',
        r'-DPCRE2_EXP_DECL="extern __attribute__((visibility (\"default\")))"',
        r'-DPCRE2_EXP_DEFN="__attribute__((visibility (\"default\")))"',

        # Include paths.
        '-I%s' % '/'.join([gendir, 'src']),
        '-I%s' % '/'.join([gendir, 'pcre2_internal']),
        '-I%s' % '/'.join(['.', package_name(), 'src']),
        '-I%s' % '/'.join(['.', package_name(), 'src/sljit']),

        # Suppress known warnings.
        '-Wno-unused-function',
    ],
    includes = [
        'pcre2_internal',
    ],
)

genrule(
    name = 'pcre2_chartables_c',
    outs = [
        'src/pcre2_chartables.c',
    ],
    srcs = [
        'src/pcre2_chartables.c.dist',
    ],
    cmd = 'cp $< $@',
)

genrule(
    name = 'pcre2_h',
    outs = [
        'pcre2_internal/pcre2.h',
    ],
    srcs = [
        'src/pcre2.h.generic',
    ],
    cmd = 'cp $< $@',
)
