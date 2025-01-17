/*
 * Public domain
 * endian.h compatibility shim
 */

#ifndef LIBCRYPTOCOMPAT_BYTE_ORDER_H_
#define LIBCRYPTOCOMPAT_BYTE_ORDER_H_

#if defined(_WIN32)

#define LITTLE_ENDIAN  1234
#define BIG_ENDIAN 4321
#define PDP_ENDIAN	3412

/*
 * Use GCC and Visual Studio compiler defines to determine endian.
 */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define BYTE_ORDER LITTLE_ENDIAN
#else
#define BYTE_ORDER BIG_ENDIAN
#endif

#elif defined(HAVE_ENDIAN_H)
#include_next <endian.h>

#elif defined(HAVE_MACHINE_ENDIAN_H)
#include_next <machine/endian.h>

#elif defined(__sun) || defined(_AIX) || defined(__hpux)
#include <sys/types.h>
#include <arpa/nameser_compat.h>

#elif defined(__sgi)
#include <standards.h>
#include <sys/endian.h>

#endif

#ifndef __STRICT_ALIGNMENT
#define __STRICT_ALIGNMENT
#if defined(__i386)    || defined(__i386__)    || \
    defined(__x86_64)  || defined(__x86_64__)  || \
    defined(__s390__)  || defined(__s390x__)   || \
    defined(__aarch64__)                       || \
    ((defined(__arm__) || defined(__arm)) && __ARM_ARCH >= 6)
#undef __STRICT_ALIGNMENT
#endif
#endif

#if defined(__APPLE__) && !defined(HAVE_ENDIAN_H)
#include <libkern/OSByteOrder.h>
#define betoh16(x) OSSwapBigToHostInt16((x))
#define htobe16(x) OSSwapHostToBigInt16((x))
#define betoh32(x) OSSwapBigToHostInt32((x))
#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define htobe64(x) OSSwapHostToBigInt64(x)
#define letoh64(x) OSSwapLittleToHostInt64(x)
#define betoh64(x) OSSwapBigToHostInt64(x)
#endif /* __APPLE__ && !HAVE_ENDIAN_H */

#if defined(_WIN32) && !defined(HAVE_ENDIAN_H)
#include <winsock2.h>

#define betoh16(x) ntohs((x))
#define htobe16(x) htons((x))
#define betoh32(x) ntohl((x))
#define htobe32(x) ntohl((x))
#define betoh64(x) ntohll((x))

#if !defined(ntohll)
#define ntohll(x) ((1==htonl(1)) ? (x) : ((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))
#endif
#if !defined(htonll)
#define htonll(x) ((1==ntohl(1)) ? (x) : ((uint64_t)htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#endif

#define htobe64(x) ntohll((x))
#endif /* _WIN32 && !HAVE_ENDIAN_H */

#ifdef __linux__
#if !defined(betoh16)
#define betoh16	be16toh
#endif
#if !defined(betoh32)
#define betoh32	be32toh
#endif
#if !defined(betoh64)
#define betoh64	be64toh
#endif
#endif /* __linux__ */

#if defined(__FreeBSD__)
#if !defined(HAVE_ENDIAN_H)
#include <sys/endian.h>
#endif
#if !defined(betoh16)
#define betoh16	be16toh
#endif
#if !defined(betoh32)
#define betoh32	be32toh
#endif
#if !defined(betoh64)
#define betoh64	be64toh
#endif
#endif

#if defined(__NetBSD__)
#if !defined(betoh16)
#define betoh16	be16toh
#endif
#if !defined(betoh32)
#define betoh32	be32toh
#endif
#if !defined(betoh64)
#define betoh64	be64toh
#endif
#endif

#endif
