///////////////////////////////////////////////////////////////////////////////
// \author (c) Marco Paland (info@paland.com)
//             2014-2019, PALANDesign Hannover, Germany
//
// \license The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// \brief Tiny printf, sprintf and (v)snprintf implementation, optimized for speed on
//        embedded systems with a very limited resources. These routines are thread
//        safe and reentrant!
//        Use this instead of the bloated standard/newlib printf cause these use
//        malloc for printf (and may not be thread safe).
//
///////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>

#include "printf.h"


// define this globally (e.g. gcc -DPRINTF_INCLUDE_CONFIG_H ...) to include the
// printf_config.h header file
// default: undefined
#ifdef PRINTF_INCLUDE_CONFIG_H
#include "printf_config.h"
#endif


// 'ntoa' conversion buffer size, this must be big enough to hold one converted
// numeric number including padded zeros (dynamically created on stack)
// default: 32 byte
#ifndef PRINTF_NTOA_BUFFER_SIZE
#define PRINTF_NTOA_BUFFER_SIZE    32U
#endif

// 'ftoa' conversion buffer size, this must be big enough to hold one converted
// float number including padded zeros (dynamically created on stack)
// default: 32 byte
#ifndef PRINTF_FTOA_BUFFER_SIZE
#define PRINTF_FTOA_BUFFER_SIZE    32U
#endif

// support for the floating point type (%f)
// default: activated
#ifndef PRINTF_DISABLE_SUPPORT_FLOAT
#define PRINTF_SUPPORT_FLOAT
#endif

// support for exponential floating point notation (%e/%g)
// default: activated
#ifndef PRINTF_DISABLE_SUPPORT_EXPONENTIAL
#define PRINTF_SUPPORT_EXPONENTIAL
#endif

// define the default floating point precision
// default: 6 digits
#ifndef PRINTF_DEFAULT_FLOAT_PRECISION
#define PRINTF_DEFAULT_FLOAT_PRECISION  6U
#endif

// define the largest float suitable to print with %f
// default: 1e9
#ifndef PRINTF_MAX_FLOAT
#define PRINTF_MAX_FLOAT  1e9
#endif

// support for the long long types (%llu or %p)
// default: activated
#ifndef PRINTF_DISABLE_SUPPORT_LONG_LONG
#define PRINTF_SUPPORT_LONG_LONG
#endif

// support for the ptrdiff_t type (%t)
// ptrdiff_t is normally defined in <stddef.h> as long or long long type
// default: activated
#ifndef PRINTF_DISABLE_SUPPORT_PTRDIFF_T
#define PRINTF_SUPPORT_PTRDIFF_T
#endif

///////////////////////////////////////////////////////////////////////////////

// internal flag definitions
#define FLAGS_ZEROPAD   (1U <<  0U)
#define FLAGS_LEFT      (1U <<  1U)
#define FLAGS_PLUS      (1U <<  2U)
#define FLAGS_SPACE     (1U <<  3U)
#define FLAGS_HASH      (1U <<  4U)
#define FLAGS_UPPERCASE (1U <<  5U)
#define FLAGS_CHAR      (1U <<  6U)
#define FLAGS_SHORT     (1U <<  7U)
#define FLAGS_LONG      (1U <<  8U)
#define FLAGS_LONG_LONG (1U <<  9U)
#define FLAGS_PRECISION (1U << 10U)
#define FLAGS_ADAPT_EXP (1U << 11U)


// import float.h for DBL_MAX
#if defined(PRINTF_SUPPORT_FLOAT)
#include <float.h>
#endif


// output function type
typedef void (*out_fct_type)(char character, void* buffer, size_t idx, size_t maxlen);


// wrapper (used as buffer) for output function type
typedef struct {
  void  (*fct)(char character, void* arg);
  void* arg;
} out_fct_wrap_type;


// internal buffer output
static inline void _out_buffer(char character, void* buffer, size_t idx, size_t maxlen)
{
  if (idx < maxlen) {
    ((char*)buffer)[idx] = character;
  }
}


// internal null output
static inline void _out_null(char character, void* buffer, size_t idx, size_t maxlen)
{
  (void)character; (void)buffer; (void)idx; (void)maxlen;
}


// internal _putchar wrapper
static inline void _out_char(char character, void* buffer, size_t idx, size_t maxlen)
{
  (void)buffer; (void)idx; (void)maxlen;
  if (character) {
    putchar_(character);
  }
}


// internal output function wrapper
static inline void _out_fct(char character, void* buffer, size_t idx, size_t maxlen)
{
  (void)idx; (void)maxlen;
  if (character) {
    // buffer is the output fct pointer
    ((out_fct_wrap_type*)buffer)->fct(character, ((out_fct_wrap_type*)buffer)->arg);
  }
}


// internal secure strlen
// \return The length of the string (excluding the terminating 0) limited by 'maxsize'
static inline unsigned int _strnlen_s(const char* str, size_t maxsize)
{
  const char* s;
  size_t maxsize_val = maxsize;
  for (s = str; *s && maxsize_val--; ++s);
  return (unsigned int)(s - str);
}


// internal test if char is a digit (0-9)
// \return true if char is a digit
static inline bool _is_digit(char ch)
{
  return (ch >= '0') && (ch <= '9');
}


// internal ASCII string to unsigned int conversion
static unsigned int _atoi(const char** str)
{
  unsigned int i = 0U;
  while (_is_digit(**str)) {
    i = i * 10U + (unsigned int)(*((*str)++) - '0');
  }
  return i;
}


// output the specified string in reverse, taking care of any zero-padding
static size_t _out_rev(out_fct_type out, char* buffer, size_t idx, size_t maxlen, const char* buf, size_t len, unsigned int width, unsigned int flags)
{
  const size_t start_idx = idx;
  size_t i;
  size_t idx_val = idx;
  size_t len_val = len;

  // pad spaces up to given width
  if (((flags & FLAGS_LEFT) == 0U) && ((flags & FLAGS_ZEROPAD) == 0U)) {
    for (i = len_val; i < width; i++) {
      out(' ', buffer, idx_val++, maxlen);
    }
  }

  // reverse string
  while (len_val) {
    out(buf[--len_val], buffer, idx_val++, maxlen);
  }

  // append pad spaces up to given width
  if (flags & FLAGS_LEFT) {
    while (idx_val - start_idx < width) {
      out(' ', buffer, idx_val++, maxlen);
    }
  }

  return idx_val;
}


// internal itoa format
static size_t _ntoa_format(out_fct_type out, char* buffer, size_t idx, size_t maxlen, char* buf, size_t len, bool negative, unsigned int base, unsigned int prec, unsigned int width, unsigned int flags)
{
  unsigned int width_val = width;
  size_t len_val = len;

  // pad leading zeros
  if ((flags & FLAGS_LEFT) == 0U) {
    if ((width_val != 0U) && ((flags & FLAGS_ZEROPAD) != 0U) && ((negative != (bool)false) || ((flags & (FLAGS_PLUS | FLAGS_SPACE)) != 0U))) {
      width_val--;
    }
    while ((len_val < prec) && (len_val < PRINTF_NTOA_BUFFER_SIZE)) {
      buf[len_val++] = '0';
    }
    while (((flags & FLAGS_ZEROPAD) != 0U) && (len_val < width_val) && (len_val < PRINTF_NTOA_BUFFER_SIZE)) {
      buf[len_val++] = '0';
    }
  }

  // handle hash
  if (flags & FLAGS_HASH) {
    if (((flags & FLAGS_PRECISION) == 0U) && (len_val != 0U) && ((len_val == prec) || (len_val == width_val))) {
      len_val--;
      if ((len_val != 0U) && (base == 16U)) {
        len_val--;
      }
    }
    if ((base == 16U) && ((flags & FLAGS_UPPERCASE) == 0U) && (len_val < PRINTF_NTOA_BUFFER_SIZE)) {
      buf[len_val++] = 'x';
    }
    else if ((base == 16U) && ((flags & FLAGS_UPPERCASE) != 0U) && (len_val < PRINTF_NTOA_BUFFER_SIZE)) {
      buf[len_val++] = 'X';
    }
    else
    {
        if ((base == 2U) && (len_val < PRINTF_NTOA_BUFFER_SIZE)) {
          buf[len_val++] = 'b';
        }
    }
    if (len_val < PRINTF_NTOA_BUFFER_SIZE) {
      buf[len_val++] = '0';
    }
  }

  if (len_val < PRINTF_NTOA_BUFFER_SIZE) {
    if (negative) {
      buf[len_val++] = '-';
    }
    else if (flags & FLAGS_PLUS) {
      buf[len_val++] = '+';  // ignore the space if the '+' exists
    }
    else
    {
        if (flags & FLAGS_SPACE) {
          buf[len_val++] = ' ';
        }
    }
  }

  return _out_rev(out, buffer, idx, maxlen, buf, len_val, width_val, flags);
}


// internal itoa for 'long' type
static size_t _ntoa_long(out_fct_type out, char* buffer, size_t idx, size_t maxlen, unsigned long value, bool negative, unsigned long base, unsigned int prec, unsigned int width, unsigned int flags)
{
  char buf[PRINTF_NTOA_BUFFER_SIZE];
  size_t len = 0U;
  unsigned int flags_local = flags;
  unsigned long value_local = value;

  // no hash for 0 values
  if (value_local == 0U) {
    flags_local &= ~FLAGS_HASH;
  }

  // write if precision != 0 and value is != 0
  if (((flags_local & FLAGS_PRECISION) == 0U) || (value_local != 0U)) {
    do {
      const char digit = (char)(value_local % base);
      buf[len++] = (digit < 10) ? ('0' + digit) : ((((flags_local & FLAGS_UPPERCASE) != 0U) ? 'A' : 'a') + (digit - 10));
      value_local /= base;
    } while ((value_local != 0U) && (len < PRINTF_NTOA_BUFFER_SIZE));
  }

  return _ntoa_format(out, buffer, idx, maxlen, buf, len, negative, (unsigned int)base, prec, width, flags_local);
}


// internal itoa for 'long long' type
#if defined(PRINTF_SUPPORT_LONG_LONG)
static size_t _ntoa_long_long(out_fct_type out, char* buffer, size_t idx, size_t maxlen, unsigned long long value, bool negative, unsigned long long base, unsigned int prec, unsigned int width, unsigned int flags)
{
  char buf[PRINTF_NTOA_BUFFER_SIZE];
  size_t len = 0U;
  unsigned int flags_local = flags;
  unsigned long long value_local = value;

  // no hash for 0 values
  if (value_local == 0U) {
    flags_local &= ~FLAGS_HASH;
  }

  // write if precision != 0 and value is != 0
  if (((flags_local & FLAGS_PRECISION) == 0U) || (value_local != 0U)) {
    do {
      const char digit = (char)(value_local % base);
      buf[len++] = (digit < 10) ? ('0' + digit) : ((((flags_local & FLAGS_UPPERCASE) != 0U) ? 'A' : 'a') + (digit - 10));
      value_local /= base;
    } while (value_local && (len < PRINTF_NTOA_BUFFER_SIZE));
  }

  return _ntoa_format(out, buffer, idx, maxlen, buf, len, negative, (unsigned int)base, prec, width, flags_local);
}
#endif  // PRINTF_SUPPORT_LONG_LONG


#if defined(PRINTF_SUPPORT_FLOAT)

#if defined(PRINTF_SUPPORT_EXPONENTIAL)
// forward declaration so that _ftoa can switch to exp notation for values > PRINTF_MAX_FLOAT
static size_t _etoa(out_fct_type out, char* buffer, size_t idx, size_t maxlen, double value, unsigned int prec, unsigned int width, unsigned int flags);
#endif


// internal ftoa for fixed decimal floating point
static size_t _ftoa(out_fct_type out, char* buffer, size_t idx, size_t maxlen, double value, unsigned int prec, unsigned int width, unsigned int flags)
{
  char buf[PRINTF_FTOA_BUFFER_SIZE];
  size_t len  = 0U;
  size_t ret = 0U;
  double diff = 0.0;
  double value_local = value;
  unsigned int prec_val = prec;
  unsigned int width_val = width;

  // powers of 10
  static const double pow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

  // test for special values
  if (value_local != value_local)
  {
    return _out_rev(out, buffer, idx, maxlen, "nan", 3, width_val, flags);
  }
  if (value_local < -DBL_MAX)
  {
    return _out_rev(out, buffer, idx, maxlen, "fni-", 4, width_val, flags);
  }
  if (value_local > DBL_MAX)
  {
    return _out_rev(out, buffer, idx, maxlen, ((flags & FLAGS_PLUS) != 0U) ? "fni+" : "fni", ((flags & FLAGS_PLUS) != 0U) ? 4U : 3U, width_val, flags);
  }

  // test for very large values
  // standard printf behavior is to print EVERY whole number digit -- which could be 100s of characters overflowing your buffers == bad
  if ((value_local > PRINTF_MAX_FLOAT) || (value_local < -PRINTF_MAX_FLOAT)) {
#if defined(PRINTF_SUPPORT_EXPONENTIAL)
    return _etoa(out, buffer, idx, maxlen, value_local, prec_val, width_val, flags);
#else
    return 0U;
#endif
  }

  // test for negative
  bool negative = false;
  if (value_local < 0) {
    negative = true;
    value_local = 0 - value_local;
  }

  // set default precision, if not set explicitly
  if ((flags & FLAGS_PRECISION) == 0U) {
    prec_val = PRINTF_DEFAULT_FLOAT_PRECISION;
  }
  // limit precision to 9, cause a prec >= 10 can lead to overflow errors
  while ((len < PRINTF_FTOA_BUFFER_SIZE) && (prec_val > 9U)) {
    buf[len++] = '0';
    prec_val--;
  }

  int whole = (int)value_local;
  double tmp = (value_local - whole) * pow10[prec_val];
  unsigned long frac = (unsigned long)tmp;
  diff = tmp - frac;

  if (diff > 0.5) {
    ++frac;
    // handle rollover, e.g. case 0.99 with prec 1 is 1.0
    if (frac >= pow10[prec_val]) {
      frac = 0;
      ++whole;
    }
  }
  else if (diff < 0.5) {
  }
  else if ((frac == 0U) || ((frac & 1U) != 0U)) {
    // if halfway, round up if odd OR if last digit is 0
    ++frac;
  }
  else
  {
      /* Intentionally add to resolve static failure */
      (void)0;
  }

  if (prec_val == 0U) {
    diff = value_local - (double)whole;
    if ((!(diff < 0.5) || (diff > 0.5)) && (whole & 1)) {
      // exactly 0.5 and ODD, then round up
      // 1.5 -> 2, but 2.5 -> 2
      ++whole;
    }
  }
  else {
    unsigned int count = prec_val;
    unsigned int omit_trailing_zeros = 1U;
    unsigned int print_digit = 1U;
    char temp_buf;

    // now do fractional part, as an unsigned number
    while (len < PRINTF_FTOA_BUFFER_SIZE) {
      --count;
      temp_buf = (char)(48U + (frac % 10U));

      if (((flags & FLAGS_ADAPT_EXP) != 0U) && ((flags & FLAGS_HASH) == 0U)) {
        if(omit_trailing_zeros) {
          if(temp_buf == '0') {
              // Do nothing, omitting the trailing zero
              print_digit = 0;
          }
          else {
            omit_trailing_zeros = 0U;
            print_digit = 1;
          }
        }
      }

      if(print_digit) {
        buf[len++] = temp_buf;
      }
      frac = frac / 10U;
      if (frac == 0U) {
        break;
      }
    }

    if (((flags & FLAGS_ADAPT_EXP) != 0U) && ((flags & FLAGS_HASH) == 0U) && (omit_trailing_zeros != 0U)) {
      // Do not add extra zeros
    }
    else {
      // add extra 0s
      while ((len < PRINTF_FTOA_BUFFER_SIZE) && (count-- > 0U)) {
        buf[len++] = '0';
      }
    }
    if (len < PRINTF_FTOA_BUFFER_SIZE) {
      if (((flags & FLAGS_ADAPT_EXP) != 0U) && ((flags & FLAGS_HASH) == 0U) && (omit_trailing_zeros != 0U)) {
      // Do not add extra zeros
      }
      else {
        // add decimal
        buf[len++] = '.';
      }
    }
  }

  // do whole part, number is reversed
  while (len < PRINTF_FTOA_BUFFER_SIZE) {
    buf[len++] = (char)(48 + (whole % 10));
    whole = whole / 10;
    if (whole == 0) {
      break;
    }
  }

  // pad leading zeros
  if (((flags & FLAGS_LEFT) == 0U) && ((flags & FLAGS_ZEROPAD) != 0U)) {
    if ((width_val != 0U) && (negative || ((flags & (FLAGS_PLUS | FLAGS_SPACE)) != 0U))) {
      width_val--;
    }
    while ((len < width_val) && (len < PRINTF_FTOA_BUFFER_SIZE)) {
      buf[len++] = '0';
    }
  }

  if (len < PRINTF_FTOA_BUFFER_SIZE) {
    if (negative) {
      buf[len++] = '-';
    }
    else if (flags & FLAGS_PLUS) {
      buf[len++] = '+';  // ignore the space if the '+' exists
    }
    else
    {
        if (flags & FLAGS_SPACE) {
          buf[len++] = ' ';
        }
    }
  }

  if(len < PRINTF_FTOA_BUFFER_SIZE)
  {
    ret = _out_rev(out, buffer, idx, maxlen, buf, (size_t)len, width, flags);
  }
  
  return ret;

}


#if defined(PRINTF_SUPPORT_EXPONENTIAL)
// internal ftoa variant for exponential floating-point type, contributed by Martijn Jasperse <m.jasperse@gmail.com>
static size_t _etoa(out_fct_type out, char* buffer, size_t idx, size_t maxlen, double value, unsigned int prec, unsigned int width, unsigned int flags)
{
  unsigned int prec_val = prec;
  unsigned int flags_local = flags;
  size_t idx_val = idx;
  double value_local = value;

  // check for NaN and special values
  if ((value_local != value_local) || (value_local > DBL_MAX) || (value_local < -DBL_MAX) || ((value_local == 0.0) && ((flags_local & FLAGS_ADAPT_EXP) != 0U))) {
    return _ftoa(out, buffer, idx_val, maxlen, value_local, prec_val, width, flags_local);
  }

  // determine the sign
  const bool negative = value_local < 0;
  if (negative) {
    value_local = -value_local;
  }

  // default precision
  if ((flags_local & FLAGS_PRECISION) == 0U) {
    prec_val = PRINTF_DEFAULT_FLOAT_PRECISION;
  }

  // determine the decimal exponent
  // based on the algorithm by David Gay (https://www.ampl.com/netlib/fp/dtoa.c)
  union {
    uint64_t U;
    double   F;
  } conv;

  conv.F = value_local;
  int exp2 = (int)((conv.U >> 52U) & 0x07FFU) - 1023;           // effectively log2
  conv.U = (conv.U & ((1ULL << 52U) - 1U)) | (1023ULL << 52U);  // drop the exponent so conv.F is now in [1,2)
  // now approximate log10 from the log2 integer part and an expansion of ln around 1.5
  int expval = (int)(0.1760912590558 + exp2 * 0.301029995663981 + (conv.F - 1.5) * 0.289529654602168);
  // now we want to compute 10^expval but we want to be sure it won't overflow
  exp2 = (int)(expval * 3.321928094887362 + 0.5);
  const double z  = expval * 2.302585092994046 - exp2 * 0.6931471805599453;
  const double z2 = z * z;
  conv.U = ((uint64_t)(exp2) + 1023U) << 52U;
  // compute exp(z) using continued fractions, see https://en.wikipedia.org/wiki/Exponential_function#Continued_fractions_for_ex
  conv.F *= 1 + 2 * z / (2 - z + (z2 / (6 + (z2 / (10 + z2 / 14)))));
  // correct for rounding errors
  if (value_local < conv.F) {
    expval--;
    conv.F /= 10;
  }

  /* if value is zero exponent value should be zero */
  if((value_local) == 0.0){
    expval = 0;
  }
  // the exponent format is "%+03d" and largest value is "307", so set aside 4-5 characters
  unsigned int minwidth = ((expval < 100) && (expval > -100)) ? 4U : 5U;

  // in "%g" mode, "prec" is the number of *significant figures* not decimals
  if (flags_local & FLAGS_ADAPT_EXP) {
    // do we want to fall-back to "%f" mode?
    if ((value_local >= 1e-4) && (value_local < 1e6)) {
      if ((int)prec_val > expval) {
        prec_val = (unsigned)((int)prec_val - expval - 1);
      }
      else {
        prec_val = 0;
      }
      flags_local |= FLAGS_PRECISION;   // make sure _ftoa respects precision
      // no characters in exponent
      minwidth = 0U;
      expval   = 0;
    }
    else {
      // we use one sigfig for the whole part
      if ((prec_val > 0) && ((flags_local & FLAGS_PRECISION) != 0U)) {
        --prec_val;
      }
    }
  }

  // will everything fit?
  unsigned int fwidth = width;
  if (width > minwidth) {
    // we didn't fall-back so subtract the characters required for the exponent
    fwidth -= minwidth;
  } else {
    // not enough characters, so go back to default sizing
    fwidth = 0U;
  }
  if (((flags_local & FLAGS_LEFT) != 0U) && (minwidth != 0U)) {
    // if we're padding on the right, DON'T pad the floating part
    fwidth = 0U;
  }

  // rescale the float value
  if (expval) {
    value_local = value_local / conv.F;
  }

  // output the floating part
  const size_t start_idx = idx_val;
  idx_val = _ftoa(out, buffer, idx_val, maxlen, negative ? -value_local : value_local, prec_val, fwidth, flags_local);

  // output the exponent part
  if (minwidth) {
    // output the exponential symbol
    out(((flags_local & FLAGS_UPPERCASE) != 0U) ? 'E' : 'e', buffer, idx_val++, maxlen);
    // output the exponent value
    idx_val = _ntoa_long(out, buffer, idx_val, maxlen, (expval < 0) ? -expval : expval, expval < 0, 10, 0, minwidth-1, FLAGS_ZEROPAD | FLAGS_PLUS);
    // might need to right-pad spaces
    if (flags_local & FLAGS_LEFT) {
      while (idx_val - start_idx < width) out(' ', buffer, idx_val++, maxlen);
    }
  }
  return idx_val;
}
#endif  // PRINTF_SUPPORT_EXPONENTIAL
#endif  // PRINTF_SUPPORT_FLOAT


// internal vsnprintf
static int _vsnprintf(out_fct_type out, char* buffer, const size_t maxlen, const char* format, va_list va)
{
  unsigned int flags, width, precision, n;
  size_t idx = 0U;
  out_fct_type out_val = out;
  const char* format_val = format;

  if (!buffer) {
    // use null output function
    out_val = _out_null;
  }

  while (*format_val)
  {
    // format specifier?  %[flags][width][.precision][length]
    if (*format_val != '%') {
      // no
      out(*format_val, buffer, idx++, maxlen);
      format_val++;
      continue;
    }
    else {
      // yes, evaluate it
      format_val++;
    }

    // evaluate flags
    flags = 0U;
    do {
      switch (*format_val) {
        case '0': flags |= FLAGS_ZEROPAD; format_val++; n = 1U; break;
        case '-': flags |= FLAGS_LEFT;    format_val++; n = 1U; break;
        case '+': flags |= FLAGS_PLUS;    format_val++; n = 1U; break;
        case ' ': flags |= FLAGS_SPACE;   format_val++; n = 1U; break;
        case '#': flags |= FLAGS_HASH;    format_val++; n = 1U; break;
        default :                                   n = 0U; break;
      }
    } while (n);

    // evaluate width field
    width = 0U;
    if (_is_digit(*format_val)) {
      width = _atoi(&format_val);
    }
    else if (*format_val == '*') {
      const int w = va_arg(va, int);
      if (w < 0) {
        flags |= FLAGS_LEFT;    // reverse padding
        width = (unsigned int)-w;
      }
      else {
        width = (unsigned int)w;
      }
      format_val++;
    }
    else
    {
        /* Intentionally add to resolve static failure */
        (void)0;
    }

    // evaluate precision field
    precision = 0U;
    if (*format_val == '.') {
      flags |= FLAGS_PRECISION;
      format_val++;
      if (_is_digit(*format_val)) {
        precision = _atoi(&format_val);
      }
      else if (*format_val == '*') {
        const int prec = (int)va_arg(va, int);
        precision = prec > 0 ? (unsigned int)prec : 0U;
        format_val++;
      }
      else
      {
          /* Intentionally add to resolve static failure */
          (void)0;
      }
    }

    // evaluate length field
    switch (*format_val) {
      case 'l' :
        flags |= FLAGS_LONG;
        format_val++;
        if (*format_val == 'l') {
          flags |= FLAGS_LONG_LONG;
          format_val++;
        }
        break;
      case 'h' :
        flags |= FLAGS_SHORT;
        format_val++;
        if (*format_val == 'h') {
          flags |= FLAGS_CHAR;
          format_val++;
        }
        break;
#if defined(PRINTF_SUPPORT_PTRDIFF_T)
      case 't' :
        flags |= (sizeof(ptrdiff_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
        format_val++;
        break;
#endif
      case 'j' :
        flags |= (sizeof(intmax_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
        format_val++;
        break;
      case 'z' :
        flags |= (sizeof(size_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
        format_val++;
        break;
      default :
        break;
    }

    // evaluate specifier
    switch (*format_val) {
      case 'd' :
      case 'i' :
      case 'u' :
      case 'x' :
      case 'X' :
      case 'o' :
      case 'b' : {
        // set the base
        unsigned int base;
        if (*format_val == 'x' || *format_val == 'X') {
          base = 16U;
        }
        else if (*format_val == 'o') {
          base =  8U;
        }
        else if (*format_val == 'b') {
          base =  2U;
        }
        else {
          base = 10U;
          flags &= ~FLAGS_HASH;   // no hash for dec format_val
        }
        // uppercase
        if (*format_val == 'X') {
          flags |= FLAGS_UPPERCASE;
        }

        // no plus or space flag for u, x, X, o, b
        if ((*format_val != 'i') && (*format_val != 'd')) {
          flags &= ~(FLAGS_PLUS | FLAGS_SPACE);
        }

        // ignore '0' flag when precision is given
        if (flags & FLAGS_PRECISION) {
          flags &= ~FLAGS_ZEROPAD;
        }

        // convert the integer
        if ((*format_val == 'i') || (*format_val == 'd')) {
          // signed
          if (flags & FLAGS_LONG_LONG) {
#if defined(PRINTF_SUPPORT_LONG_LONG)
            const long long value = va_arg(va, long long);
            idx = _ntoa_long_long(out_val, buffer, idx, maxlen, (unsigned long long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags);
#endif
          }
          else if (flags & FLAGS_LONG) {
            const long value = va_arg(va, long);
            idx = _ntoa_long(out_val, buffer, idx, maxlen, (unsigned long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags);
          }
          else {
            const int value = ((flags & FLAGS_CHAR) != 0U) ? (char)va_arg(va, int) : ((flags & FLAGS_SHORT) != 0U) ? (short int)va_arg(va, int) : va_arg(va, int);
            idx = _ntoa_long(out_val, buffer, idx, maxlen, (unsigned int)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags);
          }
        }
        else {
          // unsigned
          if (flags & FLAGS_LONG_LONG) {
#if defined(PRINTF_SUPPORT_LONG_LONG)
            idx = _ntoa_long_long(out_val, buffer, idx, maxlen, va_arg(va, unsigned long long), false, base, precision, width, flags);
#endif
          }
          else if (flags & FLAGS_LONG) {
            idx = _ntoa_long(out_val, buffer, idx, maxlen, va_arg(va, unsigned long), false, base, precision, width, flags);
          }
          else {
            const unsigned int value = ((flags & FLAGS_CHAR) != 0U) ? (unsigned char)va_arg(va, unsigned int) : ((flags & FLAGS_SHORT) != 0U) ? (unsigned short int)va_arg(va, unsigned int) : va_arg(va, unsigned int);
            idx = _ntoa_long(out_val, buffer, idx, maxlen, value, false, base, precision, width, flags);
          }
        }
        format_val++;
        break;
      }
#if defined(PRINTF_SUPPORT_FLOAT)
      case 'f' :
      case 'F' :
        if (*format_val == 'F') {flags |= FLAGS_UPPERCASE;}
        idx = _ftoa(out_val, buffer, idx, maxlen, va_arg(va, double), precision, width, flags);
        format_val++;
        break;
#if defined(PRINTF_SUPPORT_EXPONENTIAL)
      case 'e':
      case 'E':
      case 'g':
      case 'G':
        if ((*format_val == 'g')||(*format_val == 'G')) {flags |= FLAGS_ADAPT_EXP;}
        if ((*format_val == 'E')||(*format_val == 'G')) {flags |= FLAGS_UPPERCASE;}
        idx = _etoa(out_val, buffer, idx, maxlen, va_arg(va, double), precision, width, flags);
        format_val++;
        break;
#endif  // PRINTF_SUPPORT_EXPONENTIAL
#endif  // PRINTF_SUPPORT_FLOAT
      case 'c' : {
        unsigned int l = 1U;
        // pre padding
        if ((flags & FLAGS_LEFT) == 0U) {
          while (l++ < width) {
            out(' ', buffer, idx++, maxlen);
          }
        }
        // char output
        out((char)va_arg(va, int), buffer, idx++, maxlen);
        // post padding
        if (flags & FLAGS_LEFT) {
          while (l++ < width) {
            out(' ', buffer, idx++, maxlen);
          }
        }
        format_val++;
        break;
      }

      case 's' : {
        const char* p = va_arg(va, char*);
        unsigned int l = _strnlen_s(p, (precision != 0U) ? precision : ((size_t)-1));
        // pre padding
        if (flags & FLAGS_PRECISION) {
          l = (l < precision ? l : precision);
        }
        if ((flags & FLAGS_LEFT) == 0U) {
          while (l++ < width) {
            out(' ', buffer, idx++, maxlen);
          }
        }
        // string output
        while ((*p != 0) && (((flags & FLAGS_PRECISION) == 0U) || precision--)) {
          out(*(p++), buffer, idx++, maxlen);
        }
        // post padding
        if (flags & FLAGS_LEFT) {
          while (l++ < width) {
            out(' ', buffer, idx++, maxlen);
          }
        }
        format_val++;
        break;
      }

      case 'p' : {
        width = sizeof(void*) * 2U;
        flags |= FLAGS_ZEROPAD | FLAGS_UPPERCASE;
#if defined(PRINTF_SUPPORT_LONG_LONG)
        const bool is_ll = sizeof(uintptr_t) == sizeof(long long);
        if (is_ll) {
          idx = _ntoa_long_long(out_val, buffer, idx, maxlen, (uintptr_t)va_arg(va, void*), false, 16U, precision, width, flags);
        }
        else {
#endif
          idx = _ntoa_long(out_val, buffer, idx, maxlen, (unsigned long)((uintptr_t)va_arg(va, void*)), false, 16U, precision, width, flags);
#if defined(PRINTF_SUPPORT_LONG_LONG)
        }
#endif
        format_val++;
        break;
      }

      case '%' :
        out('%', buffer, idx++, maxlen);
        format_val++;
        break;

      default :
        out(*format_val, buffer, idx++, maxlen);
        format_val++;
        break;
    }
  }

  // termination
  out((char)0, buffer, idx < maxlen ? idx : maxlen - 1U, maxlen);

  // return written chars without terminating \0
  return (int)idx;
}


///////////////////////////////////////////////////////////////////////////////

int printf_(const char* format, ...)
{
  va_list va;
  va_start(va, format);
  char buffer[1];
  const int ret = _vsnprintf(_out_char, buffer, (size_t)-1, format, va);
  va_end(va);
  return ret;
}


int sprintf_(char* buffer, const char* format, ...)
{
  va_list va;
  va_start(va, format);
  const int ret = _vsnprintf(_out_buffer, buffer, (size_t)-1, format, va);
  va_end(va);
  return ret;
}


int snprintf_(char* buffer, size_t count, const char* format, ...)
{
  va_list va;
  va_start(va, format);
  const int ret = _vsnprintf(_out_buffer, buffer, count, format, va);
  va_end(va);
  return ret;
}


int vprintf_(const char* format, va_list va)
{
  char buffer[1];
  return _vsnprintf(_out_char, buffer, (size_t)-1, format, va);
}


int vsnprintf_(char* buffer, size_t count, const char* format, va_list va)
{
  return _vsnprintf(_out_buffer, buffer, count, format, va);
}


int fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...)
{
  va_list va;
  va_start(va, format);
  const out_fct_wrap_type out_fct_wrap = { out, arg };
  const int ret = _vsnprintf(_out_fct, (char*)(uintptr_t)&out_fct_wrap, (size_t)-1, format, va);
  va_end(va);
  return ret;
}
