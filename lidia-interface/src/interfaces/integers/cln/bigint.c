//
// LiDIA - a library for computational number theory
//   Copyright (c) 1996-1998 by the LiDIA Group
//
// File        : bigint.c (implementation of the cln interface)
// Author      : Thomas Papanikolaou (TP), Bruno Haible (HB)
// Last change : HB, 1996-11-17, initial version
//               HB, 1996-11-20, introduce BITOPS_ASSUME_ABS, off by default.
//               HB, 1996-11-22, call functions cl_I_to_long() etc. just
//                               introduced in CLN.
//               HB, 1998-01-24, modified for LiDIA-1.3
//               HB, 1998-01-25, BITOPS_ASSUME_ABS must be on.
//               MM, 1998-03-10, Added a constructor, Changed the return type
//                               of length() and bit_length(), Added is_odd(),
//                               ..., is_one(), abs(). Normalize the xgcd
//                               result as needed by LiDIA.
//               HB, 1998-12-13, Remove the xgcd normalization, because xgcd
//                               is fixed now. Include cl_integer_io.h instead
//                               of cl_print.h.
//               HB, 1999-02-25, Make bigint_to_string work for negative args.
//

#include <LiDIA/bigint.h>
#include <LiDIA/kernel/cl_dfloat.h>
#include <LiDIA/kernel/cl_random.h>
#include <LiDIA/kernel/cl_malloc.h>
#include <LiDIA/kernel/cl_abort.h>
#include <LiDIA/kernel/cl_integer_io.h>
#include <LiDIA/kernel/cl_spushstring.h>

/*
 * The bit operations assume a sign/magnitude representation. (The doc
 * seems to indicate this, and this is supported by the fact that libI,
 * lip, gmp all work on sign/magnitude representation. Thomas Papanikolaou
 * says the contrary, but I think he's not right about this detail.) HB
 */
#define BITOPS_ASSUME_ABS

/**
** constructors and destructor; we could leave out some of these
**/

bigint::bigint()
: I () {}

bigint::bigint(int i)
: I ((long)i) {}

bigint::bigint(long l)
: I (l) {}

bigint::bigint(unsigned long ul)
: I (ul) {}

bigint::bigint(const cl_I & a)
: I (a) {}

bigint::bigint(const bigint & a)
: I (a.I) {}

bigint::~bigint()
{}

/**
** inline member functions
**/

int bigint::bit(unsigned int i) const
{
#ifdef BITOPS_ASSUME_ABS
  if (minusp(I))
    return (int)logbitp(i,-I);
  else
#endif
    return (int)logbitp(i,I);
}

lidia_size_t bigint::length() const
{
#ifdef BITOPS_ASSUME_ABS
  if (minusp(I))
    return (integer_length(-I)+intDsize-1)/intDsize;
  else
#endif
    return (integer_length(I)+intDsize-1)/intDsize;
}

lidia_size_t bigint::bit_length() const
{
#ifdef BITOPS_ASSUME_ABS
  if (minusp(I))
    return integer_length(-I);
  else
#endif
    return integer_length(I);
}

int bigint::sign() const
{
  if (minusp(I))
    return -1;
  else if (zerop(I))
    return 0;
  else
    return 1;
}

bool bigint::is_positive() const
{ if (!minusp(I))
    if (!zerop(I))
      return (bool)1;
  return (bool)0;
}

bool bigint::is_negative() const
{ return (bool)minusp(I); }

bool bigint::is_even() const
{ return (bool)evenp(I); }

bool bigint::is_odd() const
{ return (bool)oddp(I); }

bool bigint::is_zero() const
{ return (bool)zerop(I); }

bool bigint::is_gt_zero() const
{ if (!minusp(I))
    if (!zerop(I))
      return (bool)1;
  return (bool)0;
}

bool bigint::is_ge_zero() const
{ return (bool)!minusp(I); }

bool bigint::is_lt_zero() const
{ return (bool)minusp(I); }

bool bigint::is_le_zero() const
{ if (!minusp(I))
    if (!zerop(I))
      return (bool)0;
  return (bool)1;
}

bool bigint::is_one() const
{ return (bool)(I == 1); }


bool is_odd (const bigint & a)
{ return (bool)oddp(a.I); }

bool is_even (const bigint & a)
{ return (bool)evenp(a.I); }

bool is_positive (const bigint & a)
{
  if (!minusp(a.I))
    if (!zerop(a.I))
      return (bool)1;
  return (bool)0;
}

bool is_negative (const bigint & a)
{ return (bool)minusp(a.I); }

bool is_zero (const bigint & a)
{ return (bool)zerop(a.I); }

bool is_one (const bigint & a)
{ return (bool)(a.I == 1); }



bool bigint::intify(int & i) const
{
  if (integer_length(I) >= int_bitsize)
    return (bool)1;
  i = cl_I_to_L(I);
  return (bool)0;
}

bool bigint::longify(long & i) const
{
  if (integer_length(I) >= long_bitsize)
    return (bool)1;
  i = cl_I_to_long(I);
  return (bool)0;
}

int bigint::abs_compare(const bigint & a) const
{
  return (int)cl_compare(::abs(I),::abs(a.I));
}

int bigint::compare(const bigint & a) const
{
  return (int)cl_compare(I,a.I);
}

unsigned long bigint::most_significant_digit() const
{
  if (zerop(I)) return 0;
  cl_I aI = ::abs(I);
  return cl_I_to_UL(ldb(aI,cl_byte(intDsize,((integer_length(aI)-1)/intDsize)*intDsize)));
}

unsigned long bigint::least_significant_digit() const
{
  cl_I aI = ::abs(I);
  return cl_I_to_UL(ldb(aI,cl_byte(intDsize,0)));
}

const double bigint::radix()
{ return ldexp(1.0,intDsize); }

const int bigint::bits_per_digit()
{ return intDsize; }

void bigint::absolute_value()
{ if (minusp(I)) { I = -I; } }

void bigint::abs()
{ if (minusp(I)) { I = -I; } }

void bigint::negate()
{ I = -I; }

void bigint::assign_zero()
{ I = 0; }

void bigint::assign_one()
{ I = 1; }

void bigint::assign(int i)
{ I = (long)i; }

void bigint::assign(long i)
{ I = i; }

void bigint::assign(unsigned long ui)
{ I = ui; }

void bigint::assign(double d)
{ I = round1((cl_DF)d); }

void bigint::assign(const bigint & a)
{ I = a.I; }

void bigint::multiply_by_2()
{ I = ash(I,1); }

void bigint::divide_by_2()
{ if (minusp(I)) { I = ash(plus1(I),-1); } else { I = ash(I,-1); } }

/**
** Type checking
**/

bool is_char(const bigint & a)
{ if (integer_length(a.I) < char_bitsize)
    return (bool)1;
  return (bool)0;
}

bool is_uchar(const bigint & a)
{ if (!minusp(a.I))
    if (integer_length(a.I) <= char_bitsize)
      return (bool)1;
  return (bool)0;
}

bool is_short(const bigint & a)
{ if (integer_length(a.I) < short_bitsize)
    return (bool)1;
  return (bool)0;
}

bool is_ushort(const bigint & a)
{ if (!minusp(a.I))
    if (integer_length(a.I) <= short_bitsize)
      return (bool)1;
  return (bool)0;
}

bool is_int(const bigint & a)
{ if (integer_length(a.I) < int_bitsize)
    return (bool)1;
  return (bool)0;
}

bool is_uint(const bigint & a)
{ if (!minusp(a.I))
    if (integer_length(a.I) <= int_bitsize)
      return (bool)1;
  return (bool)0;
}

bool is_long(const bigint & a)
{ if (integer_length(a.I) < long_bitsize)
    return (bool)1;
  return (bool)0;
}

bool is_ulong(const bigint & a)
{ if (!minusp(a.I))
    if (integer_length(a.I) <= long_bitsize)
      return (bool)1;
  return (bool)0;
}

/**
** assignments
**/


int bigint::operator = (int i)
{ I = (long)i; return i; }

long bigint::operator = (long l)
{ I = l; return l; }

unsigned long bigint::operator = (unsigned long ul)
{ I = ul; return ul; }

double bigint::operator = (double d)
{ I = round1((cl_DF)d); return d; }

bigint & bigint::operator = (const bigint & a)
{ I = a.I; return *this; }

/**
** comparisons
**/

bool operator == (const bigint & a, const bigint & b)
{ return (bool)(a.I == b.I); }

bool operator != (const bigint & a, const bigint & b)
{ return (bool)(a.I != b.I); }

bool operator > (const bigint & a, const bigint & b)
{ return (bool)(a.I > b.I); }

bool operator >= (const bigint & a, const bigint & b)
{ return (bool)(a.I >= b.I); }

bool operator < (const bigint & a, const bigint & b)
{ return (bool)(a.I < b.I); }

bool operator <= (const bigint & a, const bigint & b)
{ return (bool)(a.I <= b.I); }

/**
** operator overloading
**/

bigint operator - (const bigint & a)
{ return bigint(-a.I); }

bigint operator + (const bigint & a, const bigint & b)
{ return bigint(a.I + b.I); }

bigint operator - (const bigint & a, const bigint & b)
{ return bigint(a.I - b.I); }

bigint operator * (const bigint & a, const bigint & b)
{ return bigint(a.I * b.I); }

bigint operator / (const bigint & a, const bigint & b)
{ return bigint(truncate1(a.I,b.I)); }

bigint operator % (const bigint & a, const bigint & b)
{ return bigint(rem(a.I,b.I)); }

bigint operator << (const bigint & a, long ui)
{
  if (ui < 0)
    lidia_error_handler("bigint", "operator<<::index is negative.");
  return bigint(ash(a.I,(cl_I)ui));
}

bigint operator >> (const bigint & a, long ui)
{
  if (ui < 0)
    lidia_error_handler("bigint", "operator>>::index is negative.");
  return bigint(ash(a.I,-(cl_I)ui));
}

bigint operator & (const bigint & a, const bigint & b)
{ return bigint(logand(a.I,b.I)); }

bigint operator | (const bigint & a, const bigint & b)
{ return bigint(logior(a.I,b.I)); }

bigint operator ^ (const bigint & a, const bigint & b)
{ return bigint(logxor(a.I,b.I)); }

bigint & bigint::operator += (const bigint & a)
{ I = I + a.I; return *this; }

bigint & bigint::operator -= (const bigint & a)
{ I = I - a.I; return *this; }

bigint & bigint::operator *= (const bigint & a)
{ I = I * a.I; return *this; }

bigint & bigint::operator /= (const bigint & a)
{ I = truncate1(I,a.I); return *this; }

bigint & bigint::operator %= (const bigint & a)
{ I = rem(I,a.I); return *this; }

bigint & bigint::operator <<= (long ui)
{
  if (ui < 0)
    lidia_error_handler("bigint", "operator<<=::index is negative.");
  I = ash(I,(cl_I)ui);
  return *this;
}

bigint & bigint::operator >>= (long ui)
{
  if (ui < 0)
    lidia_error_handler("bigint", "operator>>=::index is negative.");
  I = ash(I,-(cl_I)ui);
  return *this;
}

bigint & bigint::operator &= (const bigint & a)
{ I = logand(I,a.I); return *this; }

bigint & bigint::operator |= (const bigint & a)
{ I = logior(I,a.I); return *this; }

bigint & bigint::operator ^= (const bigint & a)
{ I = logxor(I,a.I); return *this; }

bigint & bigint::operator++ ()
{ I = plus1(I); return *this; }

bigint & bigint::operator-- ()
{ I = minus1(I); return *this; }

bigint bigint::operator++ (int)
{ bigint a = *this; I = plus1(I); return a; }

bigint bigint::operator-- (int)
{ bigint a = *this; I = minus1(I); return a; }

int bigint::operator ! () const
{ return (int)zerop(I); }

bigint bigint::operator ~ () const
{ return bigint(lognot(I)); }

/**
** Procedural versions
**/

void negate(bigint & a, const bigint & b)
{ a.I = -b.I; }

void add(bigint & c, const bigint & a, const bigint & b)
{ c.I = a.I + b.I; }

void subtract(bigint & c, const bigint & a, const bigint & b)
{ c.I = a.I - b.I; }

void multiply(bigint & c, const bigint & a, const bigint & b)
{ c.I = a.I * b.I; }

void divide(bigint & c, const bigint & a, const bigint & b)
{ c.I = truncate1(a.I,b.I); }

void remainder(bigint & c, const bigint & a, const bigint & b)
{ c.I = rem(a.I,b.I); }

void div_rem(bigint & q, bigint & r, const bigint & a, const bigint & b)
{
  cl_I_div_t q_r = truncate2(a.I,b.I);
  q.I = q_r.quotient;
  r.I = q_r.remainder;
}

void invert(bigint & a, const bigint & b)
{
  if ((b.I == 1) || (b.I == -1))
    a.I = b.I;
  else
    lidia_error_handler("bigint", "invert::inverting of a non-unit.");
}

void shift_left(bigint & c, const bigint & a, long ui)
{
  if (ui < 0)
    lidia_error_handler("bigint", "shift_left()::index is negative.");
  c.I = ash(a.I,(cl_I)ui);
}

void shift_right(bigint & c, const bigint & a, long ui)
{
  if (ui < 0)
    lidia_error_handler("bigint", "shift_right()::index is negative.");
  c.I = ash(a.I,-(cl_I)ui);
}

void power(bigint & c, const bigint & a, const bigint & b)
{
  if ((a.I == 1) || (a.I == -1))
    {
      if (b.is_odd())
        c.I = a.I;
      else
        c.assign_one();
    }
  else if (b.is_negative())
    c.assign_zero();
  else if (b.is_zero())
    c.assign_one();
  else
    c.I = expt_pos(a.I,b.I);
}

void power(bigint & c, const bigint & a, long i)
{
  if ((a.I == 1) || (a.I == -1))
    {
      if (i&1)
        c.I = a.I;
      else
        c.assign_one();
    }
  else if (i < 0)
    c.assign_zero();
  else if (i == 0)
    c.assign_one();
  else
    c.I = expt_pos(a.I,(cl_I)i);
}

void and(bigint & c, const bigint & a, const bigint & b)
{ c.I = logand(a.I,b.I); }

void or(bigint & c, const bigint & a, const bigint & b)
{ c.I = logior(a.I,b.I); }

void xor(bigint & c, const bigint & a, const bigint & b)
{ c.I = logxor(a.I,b.I); }

void not(bigint & b, const bigint & a)
{ b.I = lognot(a.I); }

void inc(bigint & c)
{ c.I = plus1(c.I); }

void dec(bigint & c)
{ c.I = minus1(c.I); }

void add(bigint & c, const bigint & a, long i)
{ c.I = a.I + i; }

void subtract(bigint & c, const bigint & a, long i)
{ c.I = a.I - i; }

void multiply(bigint & c, const bigint & a, long i)
{ c.I = a.I * i; }

void divide(bigint & c, const bigint & a, long i)
{ c.I = truncate1(a.I,i); }

void remainder(long &r, const bigint & a, long i)
{
  r = cl_I_to_long(rem(a.I,i));
}

long remainder(const bigint & a, long i)
{
  return cl_I_to_long(rem(a.I,i));
}

void div_rem(bigint & q, long &r, const bigint & a, long i)
{
  cl_I_div_t q_r = truncate2(a.I,i);
  q.I = q_r.quotient;
  r = cl_I_to_long(q_r.remainder);
}

/**
** gcd's
**/

bigint gcd(const bigint & a, const bigint & b)
{ return bigint(gcd(a.I,b.I)); }

bigint bgcd(const bigint & a, const bigint & b)
{ return bigint(gcd(a.I,b.I)); }

bigint dgcd(const bigint & a, const bigint & b)
{ return bigint(gcd(a.I,b.I)); }

bigint xgcd(bigint & u, bigint & v, const bigint & a, const bigint & b)
{
#if 0
  // In the case abs(a) == abs(b), LiDIA wants to have u=0, abs(v)=1.
  // But CLN returns abs(u)=1, v=0. Therefore we swap the arguments.
  return bigint(xgcd(b.I,a.I,&v.I,&u.I));
#else
  // I think the above special case is unimportant, and it's more important
  // to be consistent with xgcd_left and xgcd_right below.
  return bigint(xgcd(a.I,b.I,&u.I,&v.I));
#endif
}

bigint xgcd_left(bigint & u, const bigint & a, const bigint & b)
{ cl_I v; return bigint(xgcd(a.I,b.I,&u.I,&v)); }

bigint xgcd_right(bigint & v, const bigint & a, const bigint & b)
{ cl_I u; return bigint(xgcd(a.I,b.I,&u,&v.I)); }

/**
** functions
**/

bigint abs(const bigint & a)
{ return bigint(abs(a.I)); }

void seed(const bigint & a)
{
  cl_default_random_state.seed.lo = cl_I_to_UL(ldb(a.I,cl_byte(32,0)));
  cl_default_random_state.seed.hi = cl_I_to_UL(ldb(a.I,cl_byte(32,32)));
}

void bigint::randomize(const bigint & a)
{
  if (minusp(a.I))
    *this = bigint(-random_I(-a.I));
  else
    *this = bigint(random_I(a.I));
}

bigint randomize(const bigint & a)
{
  if (minusp(a.I))
    return bigint(-random_I(-a.I));
  else
    return bigint(random_I(a.I));
}

double dbl(const bigint & a)
{ return cl_double_approx(a.I); }

xdouble xdbl(const bigint & a)
{
  double d1 = dbl(a);
  bigint a1; a1.assign(d1);
  double d2 = dbl(a - a1);
  return (xdouble)d1 + (xdouble)d2;
}

void sqrt(bigint & a, const bigint & b)
{ a.I = isqrt(b.I); }

void square(bigint & a, const bigint & b)
{ a.I = square(b.I); }

void swap(bigint & a, bigint & b)
{
  void* tmp = a.I.pointer;
  a.I.pointer = b.I.pointer;
  b.I.pointer = tmp;
}

/**
** input / output
**/

istream & operator >> (istream & in, bigint & a)
{
  a.scan (in);
  return (in);
}

ostream & operator << (ostream & out, const bigint & a)
{ out << a.I; return out; }

int string_to_bigint(const char *s, bigint & a)
{
  int n = strlen(s);
  char c[n+1];
  for (int i = 0; i < n; i++)
    switch (s[i])
    {
      case '+': case '-': case '.':
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
      case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
      case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
      case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
      case 'V': case 'W': case 'X': case 'Y': case 'Z':
      case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
      case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
      case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
      case 'v': case 'w': case 'x': case 'y': case 'z':
        c[i] = s[i]; break;
      default:
        c[i] = '\0'; goto eos;
    }
  c[n] = '\0';
eos:
  n = strlen(c);
  if (n == 0) return -1;
  a = (bigint)(cl_I)c; return n;
}

int bigint_to_string(const bigint & a, char *s)
{
  char* r = print_integer_to_string(10,a.I);
  strcpy(s,r);
  cl_free_hook(r);
  return strlen(s);
}

/**
** using fread/fwrite
**/

void bigint::read_from_file(FILE * fp)
{
  scan_from_file(fp);
  int c = getc(fp); if (c != EOF && c != '\n') { ungetc(c,fp); }
}

void bigint::write_to_file(FILE * fp)
{
  print_to_file(fp);
  putc('\n',fp);
}

/**
** using fscanf/fprintf
**/

void bigint::scan_from_file(FILE * fp)
{
  cl_spushstring buffer;
  int c;
  while ((c = getc(fp)) != EOF)
    if (!(c=='\n' || c=='\t' || c==' '))
      { ungetc(c,fp); break; }
  while ((c = getc(fp)) != EOF) {
    switch (c)
      { case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '+': case '-':
          buffer.push((char)c); break;
        default:
          ungetc(c,fp); goto end;
      }
  }
end:
  char* s = buffer.contents();
  if (s[0] != '\0')
    I = (cl_I)s;
  cl_free_hook(s);
}

void bigint::print_to_file(FILE * fp)
{
  char* s = print_integer_to_string(10,I);
  fprintf(fp,"%s",s);
  cl_free_hook(s);
}

/**
** Error handler
**/

void cl_abort (void)
{
  lidia_error_handler("cln", "cl_abort() called");
}

