// Fifth session, parked: 0x710045b158 (2,464 bytes), the integer conversion of the text formatter (the unit is
// misc/text_format.cpp). This draft compiles to 1,880 bytes. The original turns every single-byte padding loop
// (zeros, spaces) into a memset plus a loop that only counts the pointer and length up: LoopIdiomRecognize fired
// there because the buffer pointer was already promoted to a register by the first LICM. Here the promotion only
// happens in the late LICM, after LoopIdiom has run, so the loops stay byte stores. tools/s5 has no answer yet;
// a source form that lets the early LICM see the stores through the buffer pointer as not aliasing the length
// and pointer statics is what is missing. The rest of the structure follows 45a850.

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
        for (int i = zeros; i > 0; i--) {
            put_byte('0');
        }
        for (const unsigned char* d = digits; *d != 0; d++) {
            put_byte(*d);
            zeros++;
        }
        for (int i = pad; i > 0; i--) {
            put_byte(' ');
        }
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
    for (int i = left; i > 0; i--) {
        put_byte((flags & 4) << 2 | ' ');
    }
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
        for (int i = zeros; i > 0; i--) {
            put_byte('0');
        }
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
        for (int i = zeros; i > 0; i--) {
            put_byte('0');
        }
        for (const unsigned char* d = digits; *d != 0; d++) {
            put_byte(*d);
            zeros++;
        }
    }
    count += zeros;
    if (center) {
        int right = pad - left;
        for (int i = right; i > 0; i--) {
            put_byte(' ');
        }
        count += right;
    }
    return count;
}
