// Fifth session, parked: 0x710045b158 (2,464 bytes), the integer conversion of the text formatter (the unit is
// misc/text_format.cpp). This draft compiles to 2,520 bytes. The padding loops are solved: the original's memset
// plus a loop that only counts the pointer and length up comes from put_fill below (an explicit cap == 0 path
// with the pointer and length in locals, put_byte in the other path); all six memsets come out and the first is
// at the original offset (0x228). A helper taking the pointer by value gives the memset but no counting loop.
// 0x710045baf8 (the string conversion, 860 bytes) has the same three-memset shape. Still off: the sign is built
// as a mask (lsl #30, and asr #31) and tested as a byte (tst #0xff) in the original, the a-f check keeps two
// compares around the lower test, and the stack layout is 0x10 bytes larger here.

extern "C" unsigned long strlen(const char*);

struct Settings2aae3c {
    int field_0;
    int language;             // +4
};
Settings2aae3c* callee_2aae3c();        // 0x71002aae3c
void callee_45c104(unsigned int, unsigned char*, int);        // 0x710045c104

static int sTextCap;
static int sTextLen;
static char* sTextPtr;

void scratch_text_begin(char* buffer, int size) {
    sTextPtr = buffer;
    sTextCap = size;
    sTextLen = 0;
}

static inline void put_byte(int c) {
    if (sTextCap == 0 || sTextLen < sTextCap - 1) {
        *sTextPtr = c;
        sTextPtr++;
        sTextLen++;
    }
}

static inline void put_fill(int c, int n) {
    if (sTextCap == 0) {
        char* p = sTextPtr;
        int len = sTextLen;
        for (int i = n; i > 0; i--) {
            *p++ = c;
            len++;
        }
        sTextPtr = p;
        sTextLen = len;
    } else {
        for (int i = n; i > 0; i--) {
            put_byte(c);
        }
    }
}

// 0x710045b158: an integer conversion of the text formatter: VALUE in BASE (LOWER: 0x20 for lower-case hex
// digits), with the sign, prefix, zero and padding flags of FLAGS, WIDTH and PRECISION, digits grouped by threes
// with SEPARATOR when no flag is set; returns the number of characters written.
int text_format_int(unsigned int value, unsigned int flags, int width, int precision, int base, int lower,
                    unsigned char separator) {
    int sign = (flags & 2) ? '+' : 0;
    if (flags & 8) {
        sign = ' ';
    }
    if (flags & 0x10) {
        sign = '0';
    }
    if (flags & 0x40) {
        sign = '-';
    }
    unsigned char digits[12];
    callee_45c104(value, digits, base);
    if (digits[0] >= 'a' && lower == 0 && digits[0] <= 'f') {
        digits[0] -= 0x20;
    }
    int length = static_cast<int>(strlen(reinterpret_cast<char*>(digits)));
    int shown = length > precision ? length : precision;
    int prefix = (flags >> 5) & 1;
    int pad = width - prefix - (sign != 0) - shown;
    int zeros = precision - length;
    bool center;
    int count;
    int left;
    if (flags & 1) {
        count = 0;
        if (sign != 0) {
            put_byte(sign);
            count = 1;
        }
        if (flags & 0x20) {
            put_byte('X' + lower);
            count++;
        }
        put_fill('0', zeros);
        for (const unsigned char* d = digits; *d != 0; d++) {
            put_byte(*d);
            zeros++;
        }
        put_fill(' ', pad);
        return count + pad + zeros;
    }
    if (flags & 4) {
        count = 0;
        if (sign != 0) {
            put_byte(sign);
            count = 1;
        }
        if (flags & 0x20) {
            put_byte('X' + lower);
            count++;
        }
    } else {
        count = 0;
    }
    center = (flags & 0x80) != 0;
    left = center ? pad / 2 : pad;
    put_fill((flags & 4) << 2 | ' ', left);
    count += left;
    if (!(flags & 4)) {
        int n = 0;
        if (sign != 0) {
            put_byte(sign);
            n = 1;
        }
        if (flags & 0x20) {
            put_byte('X' + lower);
            n++;
        }
        count += n;
    }
    if (flags == 0) {
        int remaining = static_cast<int>(strlen(reinterpret_cast<char*>(digits)));
        put_fill('0', zeros);
        for (const unsigned char* d = digits; *d != 0; d++) {
            put_byte(*d);
            zeros++;
            remaining--;
            if (remaining % 3 == 0) {
                if (d[1] == 0) {
                    break;
                }
                put_byte(separator);
            }
        }
    } else {
        put_fill('0', zeros);
        for (const unsigned char* d = digits; *d != 0; d++) {
            put_byte(*d);
            zeros++;
        }
    }
    count += zeros;
    if (center) {
        int right = pad - left;
        put_fill(' ', right);
        count += right;
    }
    return count;
}
