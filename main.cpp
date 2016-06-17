#include <iostream>
#include <arm_neon.h>
#include <cmath>

int main(int argc, char**argv)
{

    const int indeces[] = { 0, 1, 2, 3 };
    uint32x4_t idx = *(uint32x4_t*)indeces;
    uint32x4_t ifour = vdupq_n_u32(4);

    float _data[256];
    float _ref[256];
    for( int i = 0; i < 256; i += 4 )
    {
        float32x4_t x1 = vcvtq_f32_u32(idx);
        float32x4_t e = vrsqrteq_f32(x1);
        e = vmulq_f32(vrsqrtsq_f32(vmulq_f32(x1, e), e), e);
        e = vmulq_f32(vrsqrtsq_f32(vmulq_f32(x1, e), e), e);
        e = vmulq_f32(vcvtq_f32_u32(idx), e);
        vst1q_f32(_data + i, e);
        idx = vqaddq_u32(idx, ifour);
    }
    for( int i = 0; i < 256; i++ )
        _ref[i] = std::sqrt((float)i);

    for( int i = 0; i < 256; i ++ )
    {
        std::cout << i << '\t' << _data[i] << '\t' << _ref[i] << '\t' << (_data[i] - _ref[i]) << std::endl;
    }

    return 0;
}
