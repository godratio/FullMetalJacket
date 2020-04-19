#include "fmj_types.h"

f2 f2_create(f32 a,f32 b)
{
    f2 result = {0};
    result.x = a;
    result.y = b;
    return result;
}

f2 f2_create_f(f32 a)
{
    f2 result = {0};
    result.x = a;
    result.y = a;
    return result;
}

f2 f2_add(f2 a,f2 b)
{
    f2 r = {0};
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

f2 f2_s_add(f32 a,f2 b)
{
    f2 r = {0};
    return f2_add(f2_create(a,a),b);
}

f2 f2_add_s(f2 b,f32 a)
{
    f2 r = {0};
    return f2_add(f2_create(a,a),b);
}

f2 f2_sub(f2 a,f2 b)
{
    f2 r = {0};
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

f2 f2_s_sub(f32 a,f2 b)
{
    f2 r = {0};
    return f2_sub(f2_create(a,a),b);
}

f2 f2_sub_s(f2 a,f32 b)
{
    return f2_sub(a,f2_create(b,b));
}

f2 f2_mul(f2 a,f2 b)
{
    f2 r = {0};
    r.x = a.x * b.x;
    r.y = a.y * b.y;
    return r;
}

f2 f2_s_mul(f32 a,f2 b)
{
    return f2_mul(f2_create(a,a),b);    
}

f2 f2_mul_s(f2 b,f32 a)
{
    return f2_mul(f2_create(a,a),b);    
}

f2 f2_div(f2 a,f2 b)
{
    f2 r = {0};
    r.x = a.x / b.x;
    r.y = a.y / b.y;
    return r;
}

f2 f2_s_div(f32 a,f2 b)
{
    return f2_div(f2_create(a,a),b);
}

f2 f2_div_s(f2 a,f32 b)
{
    return f2_div(a,f2_create(b,b));
}

f3 f3_create(f32 a,f32 b,f32 c)
{
    f3 r = {0};
    r.x = a;
    r.y = b;
    r.z = c;
    return r;
}

f3 f3_create_f(f32 a)
{
    f3 r = {0};
    r.x = a;
    r.y = a;
    r.z = a;
    return r;
}

f3 f3_add(f3 a,f3 b)
{
    f3 r = {0};
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

f3 f3_s_add(f32 a,f3 b)
{
    return f3_add(f3_create(a,a,a),b);
}

f3 f3_add_s(f3 b,f32 a)
{
    return f3_add(f3_create(a,a,a),b);
}

f3 f3_sub(f3 a,f3 b)
{
    f3 r = {0};
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

f3 f3_s_sub(f32 a,f3 b)
{
    return f3_sub(f3_create(a,a,a),b);
}

f3 f3_sub_s(f3 a,f32 b)
{
    return f3_sub(a,f3_create(b,b,b));
}

f3 f3_mul(f3 a,f3 b)
{
    f3 r = {0};
    r.x = a.x * b.x;
    r.y = a.y * b.y;
    r.z = a.z * b.z;
    return r;
}

f3 f3_s_mul(f32 a,f3 b)
{
    return f3_mul(f3_create(a,a,a),b);
}

f3 f3_mul_s(f3 b,f32 a)
{
    return f3_mul(f3_create(a,a,a),b);
}

f3 f3_div(f3 a,f3 b)
{
    f3 r = {0};
    r.x = a.x / b.x;
    r.y = a.y / b.y;
    r.z = a.z / b.z;
    return r;
}

f3 f3_s_div(f32 a,f3 b)
{
    return f3_div(f3_create(a,a,a),b);
}

f3 f3_div_s(f3 a,f32 b)
{
    return f3_div(a,f3_create(b,b,b));
}

f4 f4_create(f32 a,f32 b,f32 c,f32 d)
{
    f4 r = {0};
    r.x = a;
    r.y = b;
    r.z = c;
    r.w = d;
    return r;
}

f4 f4_create_f(f32 a)
{
    f4 r = {0};
    r.x = a;
    r.y = a;
    r.z = a;
    r.w = a;
    return r;    
}

f4 f4_add(f4 a,f4 b)
{
    f4 r = {0};
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    r.w = a.w + b.w;
    return r;
}

f4 f4_s_add(f32 a,f4 b)
{
    return f4_add(f4_create(a,a,a,a),b);    
}

f4 f4_add_s(f4 b,f32 a)
{
    return f4_add(f4_create(a,a,a,a),b);    
}

f4 f4_sub(f4 a,f4 b)
{
    f4 r = {0};
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    r.w = a.w - b.w; 
    return r;
}

f4 f4_s_sub(f32 a,f4 b)
{
    return f4_sub(f4_create(a,a,a,a),b);    
}

f4 f4_sub_s(f4 a,f32 b)
{
    return f4_sub(a,f4_create(b,b,b,b));    
}

f4 f4_mul(f4 a,f4 b)
{
    f4 r = {0};
    r.x = a.x * b.x;
    r.y = a.y * b.y;
    r.z = a.z * b.z;
    r.w = a.w * b.w;
    return r;    
}

f4 f4_s_mul(f32 a,f4 b)
{
    return f4_mul(f4_create(a,a,a,a),b);
}

f4 f4_mul_s(f4 b,f32 a)
{
    return f4_mul(f4_create(a,a,a,a),b);
}

f4 f4_div(f4 a,f4 b)
{
    f4 r = {0};
    r.x = a.x / b.x;
    r.y = a.y / b.y;
    r.z = a.z / b.z;
    r.w = a.w / b.w;
    return r;    
}

f4 f4_s_div(f32 a,f4 b)
{
    return f4_div(f4_create(a,a,a,a),b);    
}

f4 f4_div_s(f4 a,f32 b)
{
    return f4_div(a,f4_create(b,b,b,b));    
}

f3 cross(f3 a, f3 b)
{
	return f3_create(a.y * b.z - a.z * b.y,
		             a.z * b.x - a.x * b.z,
		             a.x * b.y - a.y * b.x);
}

f32 safe_ratio_zero(f32 a,f32 b){ if (a == 0.0f || b == 0.0f) { return 0.0f; } else { return a / b; } }

f32 f2_sum(f2 a)
{
    return a.x + a.y;
}

f32 f3_sum(f3 a)
{
    return a.x + a.y + a.z;
}

f32 f4_sum(f4 a)
{
    return a.x + a.y + a.z + a.w;
}

f32 f2_length(f2 a)
{
    return sqrtf(f2_dot(a, a));    
}

f32 f3_length(f3 a)
{
    return sqrtf(f3_dot(a, a));
}

f32 f4_length(f4 a)
{
    return sqrtf(f4_dot(a, a));
}

f32 f2_dot(f2 a, f2 b)
{
    return f2_sum(f2_mul(a,b));    
}

f32 f3_dot(f3 a, f3 b)
{
    return f3_sum(f3_mul(a,b));
}

f32 f4_dot(f4 a, f4 b)
{
    return f4_sum(f4_mul(a,b));
}

f32 sqroot(float a) { return 1.0f / sqrt(a); }
f2  f2_sqroot(f2 a) { return f2_create(sqrt(a.x),sqrt(a.y)); }
f3  f3_sqroot(f3 a) { return f3_create(sqrt(a.x),sqrt(a.y),sqrt(a.z)); }
f4  f4_sqroot(f4 a) { return f4_create(sqrt(a.x),sqrt(a.y),sqrt(a.z),sqrt(a.w));}

f32 rsqrt(float a)  { return 1.0f / sqrt(a); }
f2  f2_rsqrt(f2 a) { return f2_s_div(1.0f,f2_sqroot(a));}
f3  f3_rsqrt(f3 a) { return f3_s_div(1.0f,f3_sqroot(a));}
f4  f4_rsqrt(f4 a) { return f4_s_div(1.0f,f4_sqroot(a));}

f2 f2_normalize(f2 a){return f2_mul_s(a,(safe_ratio_zero(1.0f , f2_length(a))));}
f3 f3_normalize(f3 a){return f3_mul_s(a,(safe_ratio_zero(1.0f , f3_length(a))));}
f4 f4_normalize(f4 a){return f4_mul_s(a,(safe_ratio_zero(1.0f , f4_length(a))));}

f32 clamp(f32 x,f32 a,f32 b){ return fmax(a, fmin(b, x));}

f32 f2_length_sq(f2 a){ return f2_dot(a, a);}
f32 f3_length_sq(f3 a){ return f3_dot(a, a);}
f32 f4_length_sq(f4 a){ return f4_dot(a, a);}

f32 lerp(f32 a,f32 b,f32 t){ return a + (b-a)*t;}
f2 f2_lerp(f2 a, f2 b,f2 t){ return f2_add(a,f2_mul(f2_sub(b,a),t));}
f3 f3_lerp(f3 a, f3 b,f3 t){ return f3_add(a,f3_mul(f3_sub(b,a),t));}
f4 f4_lerp(f4 a, f4 b,f4 t){ return f4_add(a,f4_mul(f4_sub(b,a),t));}

f32 unlerp(float  a, float  b, float  x) { return (x - a) / (b - a); }
f2 f2_unlerp(f2 a, f2 b, f2 x) { return f2_div(f2_sub(x,a),f2_sub(b,a)); }
f3 f3_unlerp(f3 a, f3 b, f3 x) { return f3_div(f3_sub(x,a),f3_sub(b,a)); }
f4 f4_unlerp(f4 a, f4 b, f4 x) { return f4_div(f4_sub(x,a),f4_sub(b,a)); }

f32 f2_distance(f2 a, f2 b){ return f2_length(f2_sub(b,a)); }
f32 f3_distance(f3 a, f3 b){ return f3_length(f3_sub(b,a)); }

f2  f2_sin(f2 x) { return f2_create(sinf(x.x), sinf(x.y)); }
f3  f3_sin(f3 x) { return f3_create(sinf(x.x), sinf(x.y), sinf(x.z)); }
f4  f4_sin(f4 x) { return f4_create(sin(x.x), sinf(x.y), sinf(x.z), sinf(x.w)); }

f2  f2_cos(f2 x) { return f2_create(cosf(x.x), cosf(x.y)); }
f3  f3_cos(f3 x) { return f3_create(cosf(x.x), cosf(x.y), cosf(x.z)); }
f4  f4_cos(f4 x) { return f4_create(cosf(x.x), cosf(x.y), cosf(x.z), cosf(x.w)); }

void  sincos(f32  x,f32* s,f32* c) { *s = sinf(x); *c = cosf(x); }
void  f2_sincos(f2 x,f2* s,f2* c) { *s = f2_sin(x); *c = f2_cos(x); }
void  f3_sincos(f3 x,f3* s,f3* c) { *s = f3_sin(x); *c = f3_cos(x); }
void  f4_sincos(f4 x,f4* s,f4* c) { *s = f4_sin(x); *c = f4_cos(x); }


f32 remap(f32  a, f32  b, f32  c, f32  d, f32  x)  { return lerp(c, d, unlerp(a, b, x)); }
f2  f2_remap(f2 a, f2 b, f2 c, f2 d, f2 x) { return f2_lerp(c, d, f2_unlerp(a, b, x)); }
f3  f3_remap(f3 a, f3 b, f3 c, f3 d, f3 x) { return f3_lerp(c, d, f3_unlerp(a, b, x)); }
f4  f4_remap(f4 a, f4 b, f4 c, f4 d, f4 x) { return f4_lerp(c, d, f4_unlerp(a, b, x)); }

f32 mad(f32  a, f32  b, f32  c) { return a * b + c; }
f2  f2_mad(f2 a, f2 b, f2 c) { return f2_add(f2_mul(a,b),c); }
f3  f3_mad(f3 a, f3 b, f3 c) { return f3_add(f3_mul(a,b),c); }
f4  f4_mad(f4 a, f4 b, f4 c) { return f4_add(f4_mul(a,b),c); }

f2  f2_tan(f2 x) { return f2_create(tanf(x.x), tanf(x.y)); }
f3  f3_tan(f3 x) { return f3_create(tanf(x.x), tanf(x.y), tanf(x.z)); }
f4  f4_tan(f4 x) { return f4_create(tanf(x.x), tanf(x.y), tanf(x.z), tanf(x.w)); }

f2  f2_atan(f2 x) { return f2_create(atanf(x.x), atanf(x.y)); }
f3  f3_atan(f3 x) { return f3_create(atanf(x.x), atanf(x.y), atanf(x.z)); }
f4  f4_atan(f4 x) { return f4_create(atanf(x.x), atanf(x.y), atanf(x.z), atanf(x.w)); }

f2  f2_atan2(f2 y, f2 x) { return f2_create(atan2f(y.x, x.x), atan2f(y.y, x.y)); }
f3  f3_atan2(f3 y, f3 x) { return f3_create(atan2f(y.x, x.x), atan2f(y.y, x.y), atan2f(y.z, x.z)); }
f4  f4_atan2(f4 y, f4 x) { return f4_create(atan2f(y.x, x.x), atan2f(y.y, x.y), atan2f(y.z, x.z), atan2f(y.w, x.w)); }

f2  f2_cosh(f2 x) { return f2_create(coshf(x.x), coshf(x.y)); }
f3  f3_cosh(f3 x) { return f3_create(coshf(x.x), coshf(x.y), coshf(x.z)); }
f4  f4_cosh(f4 x) { return f4_create(coshf(x.x), coshf(x.y), coshf(x.z), coshf(x.w)); }

f2  f2_acos(f2 x) { return f2_create(acosf(x.x), acosf(x.y)); }
f3  f3_acos(f3 x) { return f3_create(acosf(x.x), acosf(x.y), acosf(x.z)); }
f4  f4_acos(f4 x) { return f4_create(acosf(x.x), acosf(x.y), acosf(x.z), acosf(x.w)); }

f2  f2_asin(f2 x) { return f2_create(asinf(x.x), asinf(x.y)); }
f3  f3_asin(f3 x) { return f3_create(asinf(x.x), asinf(x.y), asinf(x.z)); }
f4  f4_asin(f4 x) { return f4_create(asinf(x.x), asinf(x.y), asinf(x.z), asinf(x.w)); }

f2  f2_floor(f2 x) { return f2_create(floorf(x.x), floorf(x.y)); }
f3  f3_floor(f3 x) { return f3_create(floorf(x.x), floorf(x.y), floorf(x.z)); }
f4  f4_floor(f4 x) { return f4_create(floorf(x.x), floorf(x.y), floorf(x.z), floorf(x.w)); }

f2  f2_ceil(f2 x) { return  f2_create(ceilf(x.x), ceilf(x.y)); }
f3  f3_ceil(f3 x) { return  f3_create(ceilf(x.x), ceilf(x.y), ceilf(x.z)); }
f4  f4_ceil(f4 x) { return  f4_create(ceilf(x.x), ceilf(x.y), ceilf(x.z), ceilf(x.w)); }

f2  f2_round(f2 x) { return f2_create(roundf(x.x), roundf(x.y)); }
f3  f3_round(f3 x) { return f3_create(roundf(x.x), roundf(x.y), roundf(x.z)); }
f4  f4_round(f4 x) { return f4_create(roundf(x.x), roundf(x.y), roundf(x.z), roundf(x.w)); }

f2  f2_trunc(f2 x) { return f2_create(truncf(x.x), truncf(x.y)); }
f3  f3_trunc(f3 x) { return f3_create(truncf(x.x), truncf(x.y), truncf(x.z)); }
f4  f4_trunc(f4 x) { return f4_create(truncf(x.x), truncf(x.y), truncf(x.z), truncf(x.w)); }

f32 frac(f32 x) { return x - floorf(x); }
f2  f2_frac(f2 x) { return f2_sub(x,f2_floor(x)); }
f3  f3_frac(f3 x) { return f3_sub(x,f3_floor(x)); }
f4  f4_frac(f4 x) { return f4_sub(x,f4_floor(x)); }

f32 rcp(f32 x) { return 1.0f / x; }
f2  f2_rcp(f2 x) { return f2_s_div(1.0f,x); }
f3  f3_rcp(f3 x) { return f3_s_div(1.0f,x); }
f4  f4_rcp(f4 x) { return f4_s_div(1.0f,x); }

f32  sign(f32 x) { return x == 0.0f ? 0.0f : (x > 0.0f ? 1.0f : 0.0f) - (x < 0.0f ? 1.0f : 0.0f); }
f2  f2_sign(f2 x) { return f2_create(sign(x.x), sign(x.y)); }
f3  f3_sign(f3 x) { return f3_create(sign(x.x), sign(x.y), sign(x.z)); }
f4  f4_sign(f4 x) { return f4_create(sign(x.x), sign(x.y), sign(x.z), sign(x.w)); }

f2  f2_pow(f2 x, f2 y) { return  f2_create(powf(x.x, y.x), powf(x.y, y.y)); }
f3  f3_pow(f3 x, f3 y) { return  f3_create(powf(x.x, y.x), powf(x.y, y.y), powf(x.z, y.z)); }
f4  f4_pow(f4 x, f4 y) { return  f4_create(powf(x.x, y.x), powf(x.y, y.y), powf(x.z, y.z), powf(x.w, y.w)); }

f2 f2_exp(f2 x) { return f2_create(expf(x.x), expf(x.y)); }
f3 f3_exp(f3 x) { return f3_create(expf(x.x), expf(x.y), expf(x.z)); }
f4 f4_exp(f4 x) { return f4_create(expf(x.x), expf(x.y), expf(x.z), expf(x.w)); }

 f2  f2_exp2(f2 x) { return  f2_create(exp2f(x.x), exp2f(x.y)); }
 f3  f3_exp2(f3 x) { return  f3_create(exp2f(x.x), exp2f(x.y), exp2f(x.z)); }
 f4  f4_exp2(f4 x) { return  f4_create(exp2f(x.x), exp2f(x.y), exp2f(x.z), exp2f(x.w)); }

 f2  f2_fmod(f2 x, f2 y) { return  f2_create(fmodf(x.x,y.x), fmodf(x.y , y.y)); }
 f3  f3_fmod(f3 x, f3 y) { return  f3_create(fmodf(x.x, y.x), fmodf(x.y, y.y),fmodf(x.z, y.z)); }
 f4  f4_fmod(f4 x, f4 y) { return  f4_create(fmodf(x.x,y.x), fmodf(x.y,y.y), fmodf(x.z,y.z), fmodf(x.w,y.w)); }

f2 f2_reflect(f2 i, f2 n)
{
    f32 dp = f2_dot(i,n);
    f2 ip = f2_mul_s(n,dp);
    f2 sp = f2_s_mul(2,ip);
    f2 result = f2_sub(i,sp);    
    return result;
}

f3 f3_reflect(f3 i, f3 n)
{
    f32 dp = f3_dot(i,n);
    f3 ip = f3_mul_s(n,dp);
    f3 sp = f3_s_mul(2,ip);
    f3 result = f3_sub(i,sp);
    return result;
}

f4 f4_reflect(f4 i, f4 n)
{
    f32 dp = f4_dot(i,n);
    f4 ip = f4_mul_s(n,dp);
    f4 sp = f4_s_mul(2,ip);
    f4 result = f4_sub(i,sp);
    return result;    
}

f32  radians(f32 x) { return x * 0.0174532925f; }
f2  f2_radians(f2 x) { return f2_mul_s(x,0.0174532925f); }
f3  f3_radians(f3 x) { return f3_mul_s(x,0.0174532925f); }
f4  f4_radians(f4 x) { return f4_mul_s(x,0.0174532925f); }

f32  degrees(f32 x) { return x * 57.295779513f; }
f2  f2_degrees(f2 x) { return f2_mul_s(x,57.295779513f); }
f3  f3_degrees(f3 x) { return f3_mul_s(x,57.295779513f); }
f4  f4_degrees(f4 x) { return f4_mul_s(x,57.295779513f); }

f4 f4_negate(f4 x){return f4_create(-x.x,-x.y,-x.z,-x.w);}

f3x3 f3x3_identity()
{
    f3x3 r = {0};
    r.c0 = f3_create(1,0,0);
    r.c1 = f3_create(0,1,0);
    r.c2 = f3_create(0,0,1);
    return r;
}

f3x3 f3x3_create_zero()
{
    f3x3 r = {0};
    return r;
}

f3x3 f3x3_create_row(f32 a,f32 b,f32 c)
{
    f3x3 r = {0};
    r.c0 = f3_create(a,0,0);
    r.c1 = f3_create(0,b,0);
    r.c2 = f3_create(0,0,c);
    return r;    
}

f3x3 f3x3_create_vector(f3 a,f3 b,f3 c)
{
    f3x3 r = {0};
    r.c0 = a;
    r.c1 = b;
    r.c2 = c;
    return r;        
}

f3x3 f3x3_create(f32 m00, f32 m01, f32 m02,
                 f32 m10, f32 m11, f32 m12, 
                 f32 m20, f32 m21, f32 m22)
{
    f3x3 r = {0};
    r.c0 = f3_create(m00,m01,m02);
    r.c1 = f3_create(m10,m11,m12);
    r.c2 = f3_create(m20,m21,m22);
    return r;
}

f3x3 f3x3_create_from_quaternion(quaternion a)
{
    f3x3 r = {0};
    float x = a.x * 2.0f;
	float y = a.y * 2.0f;
	float z = a.z * 2.0f;
	float xx = a.x * x;
	float yy = a.y * y;
	float zz = a.z * z;
	float xy = a.x * y;
	float xz = a.x * z;
	float yz = a.y * z;
	float wx = a.w * x;
	float wy = a.w * y;
	float wz = a.w * z;

	r.c0 = f3_create(1.0f - (yy + zz), xy + wz, xz - wy);
	r.c1 = f3_create(xy - wz, 1.0f - (xx + zz), yz + wx);
	r.c2 = f3_create(xz + wy, yz - wx, 1.0f - (xx + yy));
    //Needed due to doing row major matrices.
    r = f3x3_transpose(r);
    return r;
}

f3x3 f3x3_transpose(f3x3 a)
{
	return f3x3_create(a.c0.x, a.c1.x, a.c2.x,
		               a.c0.y, a.c1.y, a.c2.y,
		               a.c0.z, a.c1.z, a.c2.z);
}

f3x3 f3x3_look_rotation(f3 forward, f3 up)
{
    const f32 epsilon = 0.000001F;
    f3 z = forward;
    // compute u0
    f32 mag = f3_length(z);
    if (mag < epsilon)
        return f3x3_identity();
    z = f3_div_s(z,mag);

    f3 x = cross(up, z);
    mag = f3_length(x);
    if (mag < epsilon)
        return f3x3_identity();
    x = f3_div_s(x,mag);

    f3 y = cross(z, x);
    f32 y_length = f3_length(y);
    if (y_length < 0.9F || y_length > 1.1F)
        return f3x3_identity();
    return f3x3_create_vector(x, y, z);    
}

f4x4 f4x4_identity()
{
    f4x4 r = {0};
    r.c0 = f4_create(1,0,0,0);
    r.c1 = f4_create(0,1,0,0);
    r.c2 = f4_create(0,0,1,0);
    r.c3 = f4_create(0,0,0,1);
    return r;
}

f4x4 f4x4_create_zero()
{
    f4x4 r = {0};
    return r;
}

f4x4 f4x4_create_row(f32 a,f32 b,f32 c,f32 d)
{
    f4x4 r = {0};
    r.c0 = f4_create(a,0,0,0);
    r.c1 = f4_create(0,b,0,0);
    r.c2 = f4_create(0,0,c,0);
    r.c3 = f4_create(0,0,0,d);    
    return r;    
}

f4x4 f4x4_create_vector(f4 a,f4 b,f4 c,f4 d)
{
    f4x4 r = {0};
    r.c0 = a;
    r.c1 = b;
    r.c2 = c;
    r.c3 = d;
    return r;        
}

f4x4 f4x4_create(f32 m00, f32 m01, f32 m02,f32 m03,
                 f32 m10, f32 m11, f32 m12,f32 m13, 
                 f32 m20, f32 m21, f32 m22,f32 m23,
                 f32 m30, f32 m31, f32 m32,f32 m33)
{
    f4x4 r = {0};
    r.c0 = f4_create(m00,m01,m02,m03);
    r.c1 = f4_create(m10,m11,m12,m13);
    r.c2 = f4_create(m20,m21,m22,m23);
    r.c3 = f4_create(m30,m31,m32,m33);    
    return r;
}

f4x4 f4x4_create_from_quaternion_translation(quaternion r,f3 t)
{
    f4x4 result = {0};
    f3x3 rot = f3x3_create_from_quaternion(r);
	rot = f3x3_transpose(rot);
	result.c0 = f4_create(rot.c0.x,rot.c0.y,rot.c0.z,0.0f);
    result.c1 = f4_create(rot.c1.x,rot.c1.y,rot.c1.z,0.0f);
	result.c2 = f4_create(rot.c2.x,rot.c2.y,rot.c2.z,0.0f);
    result.c3 = f4_create(t.x,t.y,t.z,1.0f);
    return result;
}

f4x4 f4x4_create_from_f3x3rotation_translation(f3x3 r,f3 t)
{
    f4x4 result = {0};
    result.c0 = f4_create(r.c0.x,r.c0.y,r.c0.z,0.0f);
    result.c1 = f4_create(r.c1.x,r.c1.y,r.c1.z,0.0f);
    result.c2 = f4_create(r.c2.x,r.c2.y,r.c2.z,0.0f);
    result.c3 = f4_create(t.x,t.y,t.z,1.0f);
    return result;
}

f4x4 f4x4_create_with_scale(f32 x, f32 y, f32 z)
{
    return f4x4_create(x,    0.0f, 0.0f, 0.0f,
                       0.0f, y,    0.0f, 0.0f,
                       0.0f, 0.0f, z,    0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
}

f4x4 f4x4_create_with_translate(f3 a)
{
    return f4x4_create(1.0f,0.0f,0.0f,0.0f,
                       0.0f,1.0f,0.0f,0.0f,
                       0.0f,0.0f,1.0f,0.0f,
                       a.x,a.y,a.z,1.0f);
}

f4x4 f4x4_transpose(f4x4 a)
{
	return f4x4_create(a.c0.x, a.c1.x, a.c2.x, a.c3.x,
                       a.c0.y, a.c1.y, a.c2.y, a.c3.y,
                       a.c0.z, a.c1.z, a.c2.z, a.c3.z,
                       a.c0.w, a.c1.w, a.c2.w, a.c3.w);
}

f4x4 f4x4_mul(f4x4 a,f4x4 b)
{
	return f4x4_create_vector(
		f4_add(f4_add(f4_add(f4_mul_s(a.c0,b.c0.x),f4_mul_s(a.c1,b.c0.y)),f4_mul_s(a.c2,b.c0.z)),f4_mul_s(a.c3,b.c0.w)),
		f4_add(f4_add(f4_add(f4_mul_s(a.c0,b.c1.x),f4_mul_s(a.c1,b.c1.y)),f4_mul_s(a.c2,b.c1.z)),f4_mul_s(a.c3,b.c1.w)),
        f4_add(f4_add(f4_add(f4_mul_s(a.c0,b.c2.x),f4_mul_s(a.c1,b.c2.y)),f4_mul_s(a.c2,b.c2.z)),f4_mul_s(a.c3,b.c2.w)),
		f4_add(f4_add(f4_add(f4_mul_s(a.c0,b.c3.x),f4_mul_s(a.c1,b.c3.y)),f4_mul_s(a.c2,b.c3.z)),f4_mul_s(a.c3,b.c3.w)));
}

f4 f4x4_mul_f4(f4x4 a,f4 b)
{
	return f4_add(f4_add(f4_add(f4_mul_s(a.c0,b.x),f4_mul_s(a.c1,b.y)),f4_mul_s(a.c2,b.z)),f4_mul_s(a.c3,b.w));
}

f4 f4_mul_f4x4(f4 a,f4x4 b)
{
	return f4_create(
		a.x * b.c0.x + a.y * b.c0.y + a.z * b.c0.z + a.w * b.c0.w,
		a.x * b.c1.x + a.y * b.c1.y + a.z * b.c1.z + a.w * b.c1.w,
		a.x * b.c2.x + a.y * b.c2.y + a.z * b.c2.z + a.w * b.c2.w,
		a.x * b.c3.x + a.y * b.c3.y + a.z * b.c3.z + a.w * b.c3.w);
}

f4x4 f4x4_create_from_trs(f3 t,quaternion r,f3 s)
{
	f4x4 rotation = f4x4_create_from_quaternion_translation(r,t);
	f4x4 scale_matrix = f4x4_create_with_scale(s.x,s.y,s.z);
	return f4x4_mul(rotation,scale_matrix);
}

f4 f4_horizontal_add(f4 a,f4 b)
{
	f32 x = a.x + a.y;
	f32 y = a.z + a.w;
	f32 z = b.x + b.y;
	f32 w = b.z + b.w;
	return f4_create(x, y, z, w);
}

f4 f4_mat2mul(f4 a,f4 b)
{
    f4 t = f4_create(b.x,b.w,b.x,b.w);
    f4 t2 = f4_create(a.y,a.x,a.w,a.z);
    f4 t3 = f4_create(b.y,b.x,b.y,b.x);
    f4 aa = f4_mul(a,t);
    f4 bb = f4_mul(t2,t3);//a.yxwz() * b.yxyx();
    return f4_add(aa,bb);
}

/*
f4 f4_mat2adjmul(f4 a,f4 b)
{
    f4 t1 = f4_create(a.w,a.w,a.x,a.x);
    f4 t2 = f4_create(a.y,a.y,a.z,a.z);
    f4 t3 = f4_create(b.z,b.w,b.x,b.y);
    f4 aa = f4_mul(t1,b);//a.wwxx() * b;
    f4 bb = f4_mul(t2,t3);//a.yyzz() * b.zwxy();
    return f4_sub(aa,bb);
}

f4 f4_mat2muladj(f4 a,f4 b)
{
    f4 t1 = f4_create(b.w,b.x,b.w,b.x);
    f4 t2 = f4_create(a.y,a.x,a.w,a.z);
    f4 t3 = f4_create(b.z,b.y,b.z,b.y);
    f4 aa = f4_mul(a,t1);//b.wxwx();
    f4 bb = f4_mul(t2,t3);//a.yxwz() * b.zyzy();
    return f4_sub(aa,bb);
}

// Inverse function is the same no matter column major or row major
// this version treats it as row major
f4x4 f4x4_inverse(f4x4 a)
{
    // use block matrix method
    // A is a matrix, then i(A) or iA means inverse of A, A# (or A_ in code) means adjugate of A, |A| (or detA in code) is determinant, tr(A) is trace
    // sub matrices

	f4 A = f4_create(a.c1.z,a.c1.w,a.c0.z,a.c0.w);//float4(in_matrix.c1.zw(), in_matrix.c0.zw());
 	f4 B = f4_create(a.c1.x,a.c1.y,a.c0.x,a.c0.y);//float4(in_matrix.c1.xy(), in_matrix.c0.xy());
 	
 	f4 C = f4_create(a.c3.z,a.c3.w, a.c2.z,a.c2.w);//float4(in_matrix.c3.zw(), in_matrix.c2.zw())
	f4 D = f4_create(a.c3.x,a.c3.y, a.c2.x,a.c2.y);//float4(in_matrix.c3.xy(), in_matrix.c2.xy())


	f4 detA = f4_create_f(a.c0.x * a.c1.y - a.c0.y * a.c1.x);
	f4 detB = f4_create_f(a.c0.z * a.c1.w - a.c0.w * a.c1.z);
	f4 detC = f4_create_f(a.c2.x * a.c3.y - a.c2.y * a.c3.x);
	f4 detD = f4_create_f(a.c2.z * a.c3.w - a.c2.w * a.c3.z);

	f4x4 r;
	f4 D_C = f4_mat2adjmul(D, C);
	// A#B
	f4 A_B = f4_mat2adjmul(A, B);
	// X# = |D|A - B(D#C)
    f4 X_ = f4_sub(f4_mul(detD,A),f4_mat2mul(B, D_C));
	// W# = |A|D - C(A#B)
	f4 W_ = f4_sub(f4_mul(detA,D),f4_mat2mul(C, A_B));

	// |M| = |A|*|D| + ... (continue later)
	f4 detM = f4_mul(detA,detD);

	// Y# = |B|C - D(A#B)#
	f4 Y_ = f4_sub(f4_mul(detB,C),f4_mat2muladj(D,A_B));
	// Z# = |C|B - A(D#C)#
	f4 Z_ = f4_sub(f4_mul(detC,B),f4_mat2muladj(A, D_C));

	// |M| = |A|*|D| + |B|*|C| ... (continue later)
	detM = f4_add(detM,f4_mul(detB,detC));

	// tr((A#B)(D#C))
    f4 dc_xzyw = f4_create(D_C.x,D_C.z,D_C.y,D_C.w);//D_C.xzyw()
	f4 tr = f4_mul(A_B,(dc_xzyw));

    tr = f4_horizontal_add(tr,tr);
    tr = f4_horizontal_add(tr,tr);

	// |M| = |A|*|D| + |B|*|C| - tr((A#B)(D#C)
    detM = f4_sub(detM, tr);

	const f4 adjSignMask = f4_create(1.0f,-1.0f,-1.0f,1.0f);
	// (1/|M|, -1/|M|, -1/|M|, 1/|M|)
	f4 rDetM = f4_div(adjSignMask, detM);

	X_ = f4_mul(X_,rDetM);
	Y_ = f4_mul(Y_,rDetM);
	Z_ = f4_mul(Z_,rDetM);
	W_ = f4_mul(W_,rDetM);

	// apply adjugate and store, here we combine adjugate shuffle and store shuffle
    f4 c0 = f4_create(X_.w,X_.y,Y_.w,Y_.y);//X_.wy(), Y_.wy());//, 3, 1, 3, 1));
    f4 c1 = f4_create(X_.z,X_.x,Y_.z,Y_.x);//X_.zx(), Y_.zx());//, 2, 0, 2, 0);
    f4 c2 = f4_create(Z_.w,Z_.x,W_.w,W_.x);//Z_.wx(), W_.wx());//, 3, 1, 3, 1);
    f4 c3 = f4_create(Z_.z,Z_.x,W_.z,W_.x);//Z_.zx(), W_.zx());//, 2, 0, 2, 0);
	r = f4x4_create_vector(c0,c1,c2,c3);
 	return r;
}
*/

f4x4 f4x4_inverse(f4x4 m)
{
    f4 c0 = m.c0;
    f4 c1 = m.c1;
    f4 c2 = m.c2;
    f4 c3 = m.c3;
 
    f4 r0y_r1y_r0x_r1x = f4_create(c1.x,c1.y,c0.x,c0.y);//movelh(c1, c0);
    f4 r0z_r1z_r0w_r1w = f4_create(c2.x,c2.y,c3.x,c3.y);//movelh(c2, c3);
    f4 r2y_r3y_r2x_r3x = f4_create(c1.z,c1.w,c0.z,c0.w);//movehl(c0, c1);
    f4 r2z_r3z_r2w_r3w = f4_create(c2.z,c2.w,c3.z,c3.w);//movehl(c3, c2);

    f4 r1y_r2y_r1x_r2x = f4_create(c1.y,c1.z,c0.y,c0.z);//shuffle(c1, c0, ShuffleComponent.LeftY, ShuffleComponent.LeftZ, ShuffleComponent.RightY, ShuffleComponent.RightZ);
    f4 r1z_r2z_r1w_r2w = f4_create(c2.y,c2.z,c3.y,c3.z);//shuffle(c2, c3, ShuffleComponent.LeftY, ShuffleComponent.LeftZ, ShuffleComponent.RightY, ShuffleComponent.RightZ);
    f4 r3y_r0y_r3x_r0x = f4_create(c1.w,c1.x,c0.w,c0.x);//shuffle(c1, c0, ShuffleComponent.LeftW, ShuffleComponent.LeftX, ShuffleComponent.RightW, ShuffleComponent.RightX);
    f4 r3z_r0z_r3w_r0w = f4_create(c2.w,c2.x,c3.w,c3.x);//shuffle(c2, c3, ShuffleComponent.LeftW, ShuffleComponent.LeftX, ShuffleComponent.RightW, ShuffleComponent.RightX);

    f4 r0_wzyx = f4_create(r0z_r1z_r0w_r1w.z, r0z_r1z_r0w_r1w.x, r0y_r1y_r0x_r1x.x, r0y_r1y_r0x_r1x.z);//shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, ShuffleComponent.LeftZ, ShuffleComponent.LeftX, ShuffleComponent.RightX, ShuffleComponent.RightZ);
    f4 r1_wzyx = f4_create(r0z_r1z_r0w_r1w.w, r0z_r1z_r0w_r1w.y, r0y_r1y_r0x_r1x.y, r0y_r1y_r0x_r1x.w);//shuffle(r0z_r1z_r0w_r1w, r0y_r1y_r0x_r1x, ShuffleComponent.LeftW, ShuffleComponent.LeftY, ShuffleComponent.RightY, ShuffleComponent.RightW);
    f4 r2_wzyx = f4_create(r2z_r3z_r2w_r3w.z, r2z_r3z_r2w_r3w.x, r2y_r3y_r2x_r3x.x, r2y_r3y_r2x_r3x.z);//shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, ShuffleComponent.LeftZ, ShuffleComponent.LeftX, ShuffleComponent.RightX, ShuffleComponent.RightZ);
    f4 r3_wzyx = f4_create(r2z_r3z_r2w_r3w.w, r2z_r3z_r2w_r3w.y, r2y_r3y_r2x_r3x.y, r2y_r3y_r2x_r3x.w);//shuffle(r2z_r3z_r2w_r3w, r2y_r3y_r2x_r3x, ShuffleComponent.LeftW, ShuffleComponent.LeftY, ShuffleComponent.RightY, ShuffleComponent.RightW);
    f4 r0_xyzw = f4_create(r0y_r1y_r0x_r1x.z, r0y_r1y_r0x_r1x.x, r0z_r1z_r0w_r1w.x, r0z_r1z_r0w_r1w.z);//shuffle(r0y_r1y_r0x_r1x, r0z_r1z_r0w_r1w, ShuffleComponent.LeftZ, ShuffleComponent.LeftX, ShuffleComponent.RightX, ShuffleComponent.RightZ);

     // Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
   // Calculate remaining inner term pairs. inner terms have zw=-xy, so we only have to calculate xy and can pack two pairs per vector.
    f4 inner12_23 = f4_sub((f4_mul(r1y_r2y_r1x_r2x,r2z_r3z_r2w_r3w)),(f4_mul(r1z_r2z_r1w_r2w,r2y_r3y_r2x_r3x)));//inner12_23 = r1y_r2y_r1x_r2x * r2z_r3z_r2w_r3w - r1z_r2z_r1w_r2w * r2y_r3y_r2x_r3x;
    f4 inner02_13 = f4_sub((f4_mul(r0y_r1y_r0x_r1x,r2z_r3z_r2w_r3w)),(f4_mul(r0z_r1z_r0w_r1w,r2y_r3y_r2x_r3x)));//inner02_13 = r0y_r1y_r0x_r1x * r2z_r3z_r2w_r3w - r0z_r1z_r0w_r1w * r2y_r3y_r2x_r3x;
    f4 inner30_01 = f4_sub((f4_mul(r3z_r0z_r3w_r0w,r0y_r1y_r0x_r1x)),(f4_mul(r3y_r0y_r3x_r0x,r0z_r1z_r0w_r1w)));//inner30_01 = r3z_r0z_r3w_r0w * r0y_r1y_r0x_r1x - r3y_r0y_r3x_r0x * r0z_r1z_r0w_r1w;

    // Expand inner terms back to 4 components. zw signs still need to be flipped
    f4 inner12 = f4_create(inner12_23.x,inner12_23.z,inner12_23.z,inner12_23.x);//shuffle(inner12_23, inner12_23, ShuffleComponent.LeftX, ShuffleComponent.LeftZ, ShuffleComponent.RightZ, ShuffleComponent.RightX);
    f4 inner23 = f4_create(inner12_23.y,inner12_23.w,inner12_23.w,inner12_23.y);//shuffle(inner12_23, inner12_23, ShuffleComponent.LeftY, ShuffleComponent.LeftW, ShuffleComponent.RightW, ShuffleComponent.RightY);

    f4 inner02 = f4_create(inner02_13.x,inner02_13.z,inner02_13.z,inner02_13.x);//shuffle(inner02_13, inner02_13, ShuffleComponent.LeftX, ShuffleComponent.LeftZ, ShuffleComponent.RightZ, ShuffleComponent.RightX);
    f4 inner13 = f4_create(inner02_13.y,inner02_13.w,inner02_13.w,inner02_13.y);//shuffle(inner02_13, inner02_13, ShuffleComponent.LeftY, ShuffleComponent.LeftW, ShuffleComponent.RightW, ShuffleComponent.RightY);

    // Calculate minors
    //r3_wzyx * inner12 - r2_wzyx * inner13 + r1_wzyx * inner23;
    f4 ra = f4_mul(r3_wzyx,inner12);
    f4 ra2 = f4_mul(r2_wzyx,inner13);
    f4 ra3 = f4_mul(r1_wzyx,inner23);
    f4 sub = f4_sub(ra,ra2);    
    f4 minors0 = f4_add(sub,ra3);

    
    f4 denom = f4_mul(r0_xyzw,minors0);    
    
    // Horizontal sum of denominator. Free sign flip of z and w compensates for missing flip in inner terms.
    denom = f4_add(denom,f4_create(denom.y,denom.x,denom.w,denom.z));//shuffle(denom, denom, ShuffleComponent.LeftY, ShuffleComponent.LeftX, ShuffleComponent.RightW, ShuffleComponent.RightZ);   // x+y        x+y            z+w            z+w
    denom = f4_add(denom,f4_create(denom.z,denom.z,denom.x,denom.x));//shuffle(denom, denom, ShuffleComponent.LeftZ, ShuffleComponent.LeftZ, ShuffleComponent.RightX, ShuffleComponent.RightX);   // x+y-z-w  x+y-z-w        z+w-x-y        z+w-x-y

    f4 rcp_denom_ppnn = f4_div(f4_create_f(1.0f),denom);
    f4x4 res;
    res.c0 = f4_mul(minors0,rcp_denom_ppnn);

    f4 inner30 = f4_create(inner30_01.x,inner30_01.z,inner30_01.z,inner30_01.x);//shuffle(inner30_01, inner30_01, ShuffleComponent.LeftX, ShuffleComponent.LeftZ, ShuffleComponent.RightZ, ShuffleComponent.RightX);
    f4 inner01 = f4_create(inner30_01.y,inner30_01.w,inner30_01.w,inner30_01.y);//shuffle(inner30_01, inner30_01, ShuffleComponent.LeftY, ShuffleComponent.LeftW, ShuffleComponent.RightW, ShuffleComponent.RightY);

    f4 minors1 = f4_sub((f4_sub((f4_mul(r2_wzyx,inner30)),(f4_mul(r0_wzyx,inner23)))) , (f4_mul(r3_wzyx,inner02)));
    res.c1 = f4_mul(minors1,rcp_denom_ppnn);

    //float4 minors2 = r0_wzyx * inner13 - r1_wzyx * inner30 - r3_wzyx * inner01;
    f4 a = f4_mul(r0_wzyx,inner13);
    f4 b = f4_mul(r1_wzyx,inner30);
    f4 c = f4_mul(r3_wzyx,inner01);

    //NOTE(RAY):We have flipped the order of this subtraction to get the correct results.
    //however its still seems janky and incorrect way to do it need to investigate later.
    //def will come up.
//    f4 suba = f4_sub(a,b);    
    f4 suba = f4_sub(b,a);    
    f4 minors2 = f4_sub(suba,c);
    res.c2 = f4_mul(minors2,rcp_denom_ppnn);

    //r1_wzyx * inner02 - r0_wzyx * inner12 + r2_wzyx * inner01;
    a = f4_mul(r1_wzyx,inner02);//r1_wzyx * inner02
    b = f4_mul(r0_wzyx,inner12);//r0_wzyx * inner12
    c = f4_mul(r2_wzyx,inner01);// r2_wzyx * inner01

    //NOTE(RAY):We have flipped the order of this subtraction to get the correct results.
    //however its still seems janky and incorrect way to do it need to investigate later.
    //def will come up.     
//    f4 d = f4_sub(a,b);
    f4 d = f4_sub(b,a);    
    f4 minors3 = f4_add(d,c);
    res.c3 = f4_mul(minors3,rcp_denom_ppnn);
    return res;    
}

//END INVERSE

quaternion quaternion_create(f32 x, f32 y, f32 z, f32 w)
{
    quaternion result = {0};
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;
    return result;
}

quaternion quaternion_create_f4(f4 a)
{
    quaternion result = {0};
    result.x = a.x;
    result.y = a.y;
    result.z = a.z;
    result.w = a.w;
    return result;    
}

quaternion quaternion_create_zero()
{
    quaternion result = {0};
    return result;
}

quaternion quaternion_identity()
{
    return quaternion_create(0,0,0,1);
}

quaternion quaternion_normalize(quaternion a)
{
	float root = sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
	a = quaternion_create_f4(f4_div_s(a,root));
	return a;
}

quaternion quaternion_create_f3x3(f3x3 m)
{
    quaternion result = {0};
    f3 u = m.c0;
    f3 v = m.c1;
    f3 w = m.c2;
    if (u.x >= 0.0f)
    {
        f32 t = v.y + w.z;
        if (t >= 0.0f)
        {
            result.x = 1.0f + u.x + t;
            result.y = u.y - v.x;
            result.z = w.x - u.z;
            result.w = v.z - w.y;
        }
        else
        {
            result.x = v.z - w.y;
            result.y = w.x + u.z;
            result.z = u.y + v.x;
            result.w = 1.0f + u.x - t;
        }
    }
    else
    {
        f32 t = v.y - w.z;
        if (t >= 0.0f)
        {
            result.x = w.x - u.z;
            result.y = v.z + w.y;
            result.z = 1.0f - u.x + t;
            result.w = u.y + v.x;
        }
        else
        {
            result.x = u.y - v.x;
            result.y = 1.0f - u.x - t;
            result.z = v.z + w.y;
            result.w = w.x + u.z;
        }
    }
    f4 q = f4_normalize(f4_create(result.x,result.y,result.z,result.w));
    result.x = q.w;
    result.y = q.z;
    result.z = q.y;
    result.w = q.x;
    return result;
}

quaternion quaternion_create_f4x4(f4x4 a)
{
    f3x3 in_mat = {0};
    in_mat.c0 = f3_create(a.c0.x,a.c0.y,a.c0.z);
    in_mat.c1 = f3_create(a.c1.x,a.c1.y,a.c1.z);
    in_mat.c2 = f3_create(a.c2.x,a.c2.y,a.c2.z);
    return quaternion_create_f3x3(in_mat);
}

quaternion quaternion_look_rotation(f3 forward, f3 up)
{
    f3 dir = f3_normalize(forward);
    f3 rightdir = cross(up, dir);
    f3 updir = cross(dir, rightdir);

	f32 m00 = rightdir.x;
	f32 m01 = updir.x;
	f32 m02 = dir.x;

	f32 m10 = rightdir.y;
	f32 m11 = updir.y;
	f32 m12 = dir.y;

	f32 m20 = rightdir.z;
	f32 m21 = updir.z;
	f32 m22 = dir.z;

    f32 num8 = (m00 + m11) + m22;
    f4 q = {0};
    if (num8 > 0.0)
    {
        f32 num = sqrt(num8 + 1.0f);
        q.w = (num * 0.5f);
        num = 0.5f / num;
        q.x = ((m12 - m21) * num);
        q.y = ((m20 - m02) * num);
        q.z = ((m01 - m10) * num);
        return f4_normalize((q));
    }

    if ((m00 >= m11) && (m00 >= m22))
    {
        f32 num7 = sqrt(((1.0f + m00) - m11) - m22);
        f32 num4 = 0.5f / num7;
        q.x = (0.5f * num7);
        q.y = ((m01 + m10) * num4);
        q.z = ((m02 + m20) * num4);
        q.w = ((m12 - m21) * num4);
        return f4_normalize((q));
    }
    
    if (m11 > m22)
    {
        f32 num6 = sqrt(((1.0f + m11) - m00) - m22);
        f32 num3 = 0.5f / num6;
        q.x = ((m10 + m01) * num3);
        q.y = (0.5f * num6);
        q.z = ((m21 + m12) * num3);
        q.w = ((m20 - m02) * num3);
        return f4_normalize((q));
    }
    
    f32 num5 = sqrt(((1.0f + m22) - m00) - m11);
    f32 num2 = 0.5f / num5;
    q.x = ((m20 + m02) * num2);
    q.y = ((m21 + m12) * num2);
    q.z = (0.5f * num5);
    q.w = ((m01 - m10) * num2);
    return f4_normalize((q));
}

quaternion quaternion_mul(quaternion q1, quaternion q2)
{
	
	return quaternion_create(
		q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x,
		-q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y,
		q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z,
		-q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w
	);
}

f32 quaternion_dot(quaternion a, quaternion b)
{
    return f4_dot(f4_create(a.x,a.y,a.z,a.w),
        f4_create(b.x,b.y,b.z,b.w));
}

f32 quaternion_length(quaternion a)
{
    return sqrt(f4_dot(f4_create(a.x,a.y,a.z,a.w),
                       f4_create(a.x,a.y,a.z,a.w)
                       )
                );
}

f32 quaternion_length_sq(quaternion q){return f4_dot(f4_create(q.x,q.y,q.z,q.w), f4_create(q.x,q.y,q.z,q.w));}    
quaternion quaternion_conjugate(quaternion q)
{
    f4 result = f4_mul(f4_create(q.x,q.y,q.z,q.w),f4_create(-1.0f, -1.0f, -1.0f, 1.0f));
    return quaternion_create(result.x,result.y,result.z,result.w);
}

quaternion nlerp(quaternion q1,quaternion q2,float t)
{
    float dt = f4_dot(q1, q2);
    if(dt < 0.0f)
    {
        q2 = quaternion_create_f4(f4_negate(q2));
    }

    quaternion ql = f4_lerp(q1, q2, f4_create_f(t));
    quaternion qn = quaternion_normalize(ql);                            
    return qn;
}

quaternion inverse(quaternion q)
{
    return quaternion_conjugate(quaternion_normalize(q));
}

quaternion slerp(quaternion q1, quaternion q2, float t)
{
    float dt = f4_dot(q1, q2);
    if (dt < 0.0f)
    {
        dt = -dt;
        q2 = quaternion_create_f4(f4_negate(q2));
    }

    if (dt < 0.9995f)
    {
        float angle = acos(dt);
        float s = rsqrt(1.0f - dt * dt);    // 1.0f / sin(angle)
        float w1 = sin(angle * (1.0f - t)) * s;
        float w2 = sin(angle * t) * s;
        return quaternion_create_f4(f4_add(f4_mul_s(q1,w1),f4_mul_s(q2,w2)));
    }
    else
    {
        // if the angle is small, use linear interpolation
        return nlerp(q1, q2, t);
    }
}

f4x4 init_pers_proj_matrix(f2 buffer_dim,f32 fov_y ,f2 far_near)
{
    f32 near_clip_plane = far_near.x;
    f32 far_clip_plane = far_near.y;
	f32 tangent = tanf(radians((fov_y / 2)));
	f32 aspect_ratio = buffer_dim.x / buffer_dim.y;
	f32 z_depth_range = far_clip_plane - near_clip_plane;

    f32 a = 1.0f / (tangent * aspect_ratio);
    f32 b = 1.0f / tangent;
    f32 z = -((far_clip_plane + near_clip_plane) / z_depth_range);
    f32 z2 = -((2.0f * far_clip_plane * near_clip_plane) / z_depth_range);
	f4x4 result = f4x4_create_row(a, b, z,0);

    result.c2.w = (-1);
	result.c3.x = (0);
	result.c3.y = (0);
	result.c3.z = (z2);
	return result;
}

f4x4 init_ortho_proj_matrix(f2 size,f32 near_clip_plane ,f32 far_clip_plane)
{
	f32 r = size.x;
	f32 l = -r;
	f32 t = size.y;
	f32 b = -t;
	f32 zero = 2.0f / (r - l);
	f32 five = 2.0f / (t - b);
	f32 ten = -2.0f / (far_clip_plane - near_clip_plane);

	f4x4 result = f4x4_create_row(zero, five, ten,1);

	result.c3.x = (-((r + l)  / (r - l)));
	result.c3.y = (-((t + b)  / (t - b)));
	result.c3.z = ( 0 );
	return result;
}

f4x4 init_screen_space_matrix(f2 buffer_dim)
{
	f2 ab = f2_s_div(2.0f,buffer_dim);
	f4x4 result = f4x4_create_row(ab.x, ab.y, 1,1);
	result.c3.x = -1;
	result.c3.y = -1;
	return result;
}

f4x4 set_camera_view(f3 p,f3 d,f3 u)
{
	f3 cam_right = cross(u, d);
	f3 cam_up = cross(d, cam_right);
	d = f3_normalize(d);
 	return f4x4_create(cam_right.x,     cam_up.x,     d.x,     0,
                     cam_right.y,     cam_up.y,     d.y,     0,
                     cam_right.z,     cam_up.z,     d.z,     0,
                    -f3_dot(cam_right, p),-f3_dot(cam_up, p),-f3_dot(d, p),1.0f);
}

quaternion f3_axis_angle(f3 axis,f32 angle)
{
    f32 sina, cosa;
    sincos(0.5f * radians(angle),&sina,&cosa);
    f3 r = f3_mul_s(f3_normalize(axis),sina);
    return quaternion_create_f4(f4_create(r.x,r.y,r.z,cosa));
}

f3 f3_world_local_p(f4x4 m,f3 a)
{
    f4 result = f4x4_mul_f4(f4x4_inverse(m),f4_create(a.x,a.y,a.z,1.0f));
    return f3_create(result.x,result.y,result.z);
}

f3 f3_local_world_p(f4x4 m,f3 a)
{
    f4 result = f4x4_mul_f4(m,f4_create(a.x,a.y,a.z,1.0f));
    return f3_create(result.x,result.y,result.z);
}

f3 quaternion_mul_f3(quaternion q, f3 dir)
{
	f3 qv = f3_create(q.x,q.y,q.z);
	f3 t = f3_s_mul(2,cross(dir,qv));
    return f3_add(dir,f3_add(f3_s_mul(q.w,t),cross(t,qv)));
}

f3 quaternion_forward(quaternion q)
{
	return f3_normalize(quaternion_mul_f3(q, f3_create(0, 0, 1)));
}

f3 quaternion_up(quaternion q)
{
	return f3_normalize(quaternion_mul_f3(q, f3_create(0, 1, 0)));
}

f3 quaternion_right(quaternion q)
{
	return f3_normalize(quaternion_mul_f3(q, f3_create(1, 0, 0)));
}

f3 f3_rotate(quaternion q, f3 dir)
{
    f3 qxyz = f3_create(q.x,q.y,q.z);
    f3 c = cross(qxyz, dir);
    f3 t = f3_s_mul(2.0f,c);
    f3 a = f3_s_mul(q.w,t);
    f3 ca = cross(qxyz, t);
    return f3_add(f3_add(dir,a),ca);
}

//copy pasted from 
//https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624
f32 f32_random_range(f32 a, f32 b)
{
    f32 random = ((f32) rand()) / (f32) RAND_MAX;
    f32 diff = b - a;
    f32 r = random * diff;
    return a + r;
}

f3 f3_screen_to_world_point(f4x4 projection_matrix,f4x4 cam_matrix,f2 buffer_dim, f2 screen_xy, float z_depth)
{
	f4x4 pc_mat = f4x4_mul(projection_matrix,cam_matrix);
	f4x4 inv_pc_mat = f4x4_transpose(f4x4_inverse(pc_mat));
	f4 p = f4_create(
        2.0f * screen_xy.x / buffer_dim.x - 1.0f,
        2.0f * screen_xy.y / buffer_dim.y - 1.0f,
        z_depth,
        1.0f);

	f4 w_div = f4_mul_f4x4(p , inv_pc_mat);
    f3 f3_w_div = f3_create(w_div.x,w_div.y,w_div.z);
	f32 w = safe_ratio_zero(1.0f, w_div.w);
    return f3_mul_s(f3_w_div,w);
}

f2 f2_world_to_screen_point(f4x4 projection_matrix,f4x4 camera_matrix,f2 buffer_dim, f3 p)
{
	f4 input_p = f4_create(p.x,p.y,p.z,1.0f);
    f32 aspect_ratio = buffer_dim.x / buffer_dim.y;
	f4x4 view_projection_matrix = f4x4_mul(projection_matrix , camera_matrix);
	f4 clip = f4_mul_f4x4(input_p,view_projection_matrix);
	//w divide value should be z of output.
	clip.w = (clip.z);

	 //TODO(Ray):Use swizzlers here to help cut down on operations
	//f3 div_w = clip.xyz() / clip.www();
	f3 NDC = f3_create(
        (safe_ratio_zero( clip.x , clip.w) + 1) * aspect_ratio,
    	(safe_ratio_zero( clip.y , clip.w) + 1) * aspect_ratio,
         safe_ratio_zero( clip.z , clip.w));

	f2 Result = f2_create( NDC.x * safe_ratio_zero(buffer_dim.x , NDC.z),
                           NDC.y *  safe_ratio_zero(buffer_dim.y , NDC.z));
//	Result.x = NDC.x * buffer_dim.x / NDC.z;
//	Result.y = NDC.y * buffer_dim.y / NDC.z;
	return Result;
}

