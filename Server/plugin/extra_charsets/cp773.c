#include "translate.h"

static const t_unicode cp773_c1_chars[] = {
0x0106, 0x00fc, 0x00e9, 0x0101, 0x00e4, 0x0123, 0x00e5, 0x0107, /* 0x80-0x87 */
0x0142, 0x0113, 0x0156, 0x0157, 0x012b, 0x0179, 0x00c4, 0x00c5, /* 0x88-0x8F */
0x00c9, 0x00e6, 0x00c6, 0x014d, 0x00f6, 0x0122, 0x00a2, 0x015a, /* 0x90-0x97 */
0x015b, 0x00d6, 0x00dc, 0x00f8, 0x00a3, 0x00d8, 0x00d7, 0x00a4, /* 0x98-0x9F */
};
struct char_set cp773_c1 = {
	1,
	CHARS(cp773_c1_chars),
	0, "", 0, 32,
};

static const t_unicode cp773_g1_chars[] = {
0x0100, 0x012a, 0x00f3, 0x017b, 0x017c, 0x017a, 0x201d, 0x00a6, /* 0xA0-0xA7 */
0x00a9, 0x00ae, 0x00ac, 0x00bd, 0x00bc, 0x0141, 0x00ab, 0x00bb, /* 0xA8-0xAF */
0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556, /* 0xB0-0xB7 */
0x2555, 0x2563, 0x2551, 0x2557, 0x255d, 0x255c, 0x255b, 0x2510, /* 0xB8-0xBF */
0x2514, 0x2534, 0x252c, 0x251c, 0x2500, 0x253c, 0x255e, 0x255f, /* 0xC0-0xC7 */
0x255a, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256c, 0x2567, /* 0xC8-0xCF */
0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256b, /* 0xD0-0xD7 */
0x256a, 0x2518, 0x250c, 0x2588, 0x0104, 0x0105, 0x010c, 0x010d, /* 0xD8-0xDF */
0x00d3, 0x00df, 0x014c, 0x0143, 0x00f5, 0x00d5, 0x00b5, 0x0144, /* 0xE0-0xE7 */
0x0136, 0x0137, 0x013b, 0x013c, 0x0146, 0x0112, 0x0145, 0x2019, /* 0xE8-0xEF */
0x0118, 0x0119, 0x0116, 0x0117, 0x012e, 0x012f, 0x0160, 0x0161, /* 0xF0-0xF7 */
0x0172, 0x0173, 0x016a, 0x016b, 0x017d, 0x017e, 0x25a0, 0x00a0, /* 0xF8-0xFF */
};
struct char_set cp773_g1 = {
	1,
	CHARS(cp773_g1_chars),
	0, "", 0, 96,
};

struct char_set cp773 = {
	.c0 = &ibm_ascii_c0,
	.g0 = &ibm_ascii_g0,
	.c1 = &cp773_c1,
	.g1 = &cp773_g1,
	.names = { "cp773", 0 },
};

CONSTRUCTOR(static void init(void))
{
	register_charset(&cp773);
}
