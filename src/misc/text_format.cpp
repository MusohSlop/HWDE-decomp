// The text formatter (fifth session): a vsnprintf over one static buffer, with conversions for full-width key
// names. Callee names are placeholders after their address. Status: matching/README.md.

extern "C" unsigned long strlen(const char*);

struct Settings2aae3c {
    int field_0;
    int language;             // +4
};
Settings2aae3c* callee_2aae3c();        // 0x71002aae3c
int callee_45b158(unsigned int, unsigned int, int, int, int, int, int);        // 0x710045b158
int callee_45baf8(const char*, unsigned int, int, int);        // 0x710045baf8
void callee_45bf78(int, unsigned char*);        // 0x710045bf78
int callee_45c078(const char*, int);        // 0x710045c078
int text_format_key(int, unsigned int, int, int);

static int sTextCap;
static int sTextLen;
static char* sTextPtr;

static const int kSeparator[12] = {',', ',', ' ', ' ', '.', ' ', ',', ' ', ' ', ',', ',', ','};

static inline void put_byte(int c) {
    if (sTextCap == 0 || sTextLen < sTextCap - 1) {
        *sTextPtr = c;
        sTextPtr++;
        sTextLen++;
    }
}

static inline int language() {
    int language = callee_2aae3c()->language;
    return language == 6 ? 1 : language;
}

// 0x7100459ffc: vsnprintf of the text formatter: writes FORMAT with ARGS into BUFFER of SIZE bytes (0: no limit),
// with the custom conversions %w (a key name in full-width characters) and %= (centred), and the thousands
// separator of the language; returns the length written.
int text_vformat(char* buffer, int size, const char* format, __builtin_va_list args) {
    sTextPtr = buffer;
    sTextCap = size;
    __builtin_va_list ap = args;
    sTextLen = 0;
    int lang = language();
    int separator;
    if (static_cast<unsigned int>(lang) < 12) {
        separator = kSeparator[lang];
    } else {
        separator = ' ';
    }
    const unsigned char* p = reinterpret_cast<const unsigned char*>(format);
    while (*p != 0) {
        int c = *p++;
        if (c != '%') {
            put_byte(c);
            continue;
        }
        if (*p == '%') {
            p++;
            put_byte('%');
            continue;
        }
        unsigned int flags = 0;
        bool more = true;
        while (more) {
            more = false;
            switch (*p) {
            case ' ':
                flags |= 8;
                p++;
                more = true;
                break;
            case '#':
                flags |= 0x10;
                p++;
                more = true;
                break;
            case '+':
                flags |= 2;
                p++;
                more = true;
                break;
            case '-':
                flags |= 1;
                p++;
                more = true;
                break;
            case '0':
                flags |= 4;
                p++;
                more = true;
                break;
            case '=':
                flags |= 0x80;
                p++;
                more = true;
                break;
            }
        }
        if (flags & 0x81) {
            flags &= ~4;
        }
        if (flags & 2) {
            flags &= ~8;
        }
        int width = 0;
        if (*p == '*') {
            width = -1;
            p++;
        } else {
            while (static_cast<unsigned int>(*p - '0') < 10) {
                width = width * 10 + *p - '0';
                p++;
            }
        }
        if (width == -1) {
            width = __builtin_va_arg(ap, int);
        }
        int precision = 0;
        if (*p == '.') {
            p++;
            if (*p == '*') {
                precision = -1;
                p++;
            } else {
                while (static_cast<unsigned int>(*p - '0') < 10) {
                    precision = precision * 10 + *p - '0';
                    p++;
                }
            }
            if (precision == -1) {
                precision = __builtin_va_arg(ap, int);
            }
        }
        int length = 0;
        if (*p == 'l') {
            length = 1;
            p++;
        }
        if (*p == 'N') {
            length = 3;
            p++;
        }
        if (*p == 'F') {
            length = 2;
            p++;
        }
        c = *p++;
        switch (lang) {
        case 0:
        case 10:
        case 11: {
            int lower = 0;
            switch (c) {
            case 'c':
                put_byte(__builtin_va_arg(ap, int));
                break;
            case 'd':
            case 'i': {
                unsigned int f = flags & ~0x10;
                int value = length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int);
                if (value < 0) {
                    value = -value;
                    f = (f & ~0x52) | 0x40;
                }
                callee_45b158(value, f, width, precision, 10, 0, separator);
                break;
            }
            case 'o':
                flags &= ~0xa;
                callee_45b158(length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int), flags, width,
                              precision, 8, 0, separator);
                break;
            case 's':
                callee_45baf8(__builtin_va_arg(ap, char*), flags, width, precision);
                break;
            case 'u':
                flags &= ~0x10;
                callee_45b158(length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int), flags, width,
                              precision, 10, 0, separator);
                break;
            case 'w':
                text_format_key(length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int), flags & ~0x10, width,
                            precision);
                break;
            case 'x':
                lower = 0x20;
            case 'X':
                flags = ((flags & 0x10) << 1) | (flags & ~0xa);
                callee_45b158(length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int), flags, width,
                              precision, 16, lower, separator);
                break;
            }
            break;
        }
        default: {
            int lower = 0;
            switch (c) {
            case 'c':
                put_byte(__builtin_va_arg(ap, int));
                break;
            case 'd':
            case 'i':
            case 'w': {
                unsigned int f = flags & ~0x10;
                int value = length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int);
                if (value < 0) {
                    value = -value;
                    f = (f & ~0x52) | 0x40;
                }
                if (value < 10000) {
                    switch (lang) {
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                        f |= 0x100;
                        break;
                    }
                }
                callee_45b158(value, f, width, precision, 10, 0, separator);
                break;
            }
            case 'o':
                flags &= ~0xa;
                callee_45b158(length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int), flags, width,
                              precision, 8, 0, separator);
                break;
            case 's':
                callee_45baf8(__builtin_va_arg(ap, char*), flags, width, precision);
                break;
            case 'u':
                flags &= ~0x10;
                callee_45b158(length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int), flags, width,
                              precision, 10, 0, separator);
                break;
            case 'x':
                lower = 0x20;
            case 'X':
                flags = ((flags & 0x10) << 1) | (flags & ~0xa);
                callee_45b158(length == 1 ? __builtin_va_arg(ap, long) : __builtin_va_arg(ap, int), flags, width,
                              precision, 16, lower, separator);
                break;
            }
            break;
        }
        }
    }
    *sTextPtr = 0;
    return sTextLen;
}

static inline int glyph_plus() {
    switch (language()) {
    default:
        return 0x8140;
    case 0:
        return 0x817b;
    case 0xb:
        return 0xa1cf;
    case 0xa:
        return 0xa3ab;
    }
}

static inline int glyph_space() {
    int l = language();
    if (l == 0xb) return 0xa140;
    if (l == 0xa) return 0xa1a1;
    return 0x8140;
}

static inline int glyph_zero() {
    switch (language()) {
    default:
        return 0x8140;
    case 0:
        return 0x824f;
    case 0xb:
        return 0xa2af;
    case 0xa:
        return 0xa3b0;
    }
}

static inline int glyph_minus() {
    switch (language()) {
    default:
        return 0x8140;
    case 0:
        return 0x817c;
    case 0xb:
        return 0xa1d0;
    case 0xa:
        return 0xa3ad;
    }
}

static inline int glyph_x_high() {
    switch (language()) {
    default:
        return 0x81;
    case 0:
        return 0x82;
    case 0xb:
        return 0xa3;
    case 0xa:
        return 0xa3;
    }
}

static inline int glyph_x_low() {
    switch (language()) {
    default:
        return 0x40;
    case 0:
        return 0x97;
    case 0xb:
        return 0x41;
    case 0xa:
        return 0xf8;
    }
}

static inline void put_wide(int c) {
    put_byte(c >> 8);
    put_byte(c);
}

// 0x710045a850: %w of the text formatter: the name of key KEY in full-width characters, with the sign and prefix
// flags of FLAGS, padded to WIDTH characters; returns the number of bytes written.
int text_format_key(int key, unsigned int flags, int width, int precision) {
    int sign = 0;
    if (flags & 2) {
        sign = glyph_plus();
    }
    if (flags & 8) {
        sign = glyph_space();
    }
    if (flags & 0x10) {
        sign = glyph_zero();
    }
    if (flags & 0x40) {
        sign = glyph_minus();
    }
    unsigned char name[24];
    callee_45bf78(key, name);
    if (static_cast<unsigned int>(name[0] - 'a') < 6) {
        name[0] -= 0x20;
    }
    int length = static_cast<int>(strlen(reinterpret_cast<char*>(name))) / 2;
    int digits = length > precision ? length : precision;
    int prefix = (flags >> 5) & 1;
    int pad = width - (sign != 0) - prefix - digits;
    int zeros = precision - length;
    bool center;
    int count;
    int fill;
    int left;
    if (flags & 1) {
        count = 0;
        if (sign != 0) {
            put_wide(sign);
            count = 1;
        }
        if (flags & 0x20) {
            put_byte(glyph_x_high());
            put_byte(glyph_x_low());
            count++;
        }
        int written = callee_45c078(reinterpret_cast<char*>(name), zeros);
        int space = glyph_space();
        for (int i = pad; i > 0; i--) {
            put_wide(space);
        }
        return (count + pad + written) * 2;
    }
    if (flags & 4) {
        count = 0;
        if (sign != 0) {
            put_wide(sign);
            count = 1;
        }
        if (flags & 0x20) {
            put_byte(glyph_x_high());
            put_byte(glyph_x_low());
            count++;
        }
        center = (flags & 0x80) != 0;
        left = center ? pad / 2 : pad;
        fill = glyph_zero();
    } else {
        count = 0;
        center = (flags & 0x80) != 0;
        left = center ? pad / 2 : pad;
        switch (language()) {
        default:
            fill = 0x8140;
            break;
        case 0xa:
            fill = 0xa1a1;
            break;
        case 0xb:
            fill = 0xa140;
            break;
        }
    }
    for (int i = left; i > 0; i--) {
        put_wide(fill);
    }
    count += left;
    if (!(flags & 4)) {
        int n = 0;
        if (sign != 0) {
            put_wide(sign);
            n = 1;
        }
        if (flags & 0x20) {
            put_byte(glyph_x_high());
            put_byte(glyph_x_low());
            n++;
        }
        count += n;
    }
    int total = callee_45c078(reinterpret_cast<char*>(name), zeros) + count;
    if (center) {
        int right = pad - left;
        int space = glyph_space();
        for (int i = right; i > 0; i--) {
            put_wide(space);
        }
        total += right;
    }
    return total * 2;
}
