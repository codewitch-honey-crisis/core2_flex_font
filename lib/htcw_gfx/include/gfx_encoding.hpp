#ifndef HTCW_GFX_ENCODING_HPP
#define HTCW_GFX_ENCODING_HPP
#include "gfx_core.hpp"
#include <stdint.h>
namespace gfx {
    class text_encoder {
    public:
        virtual gfx_result to_utf32(const void* in, uint32_t* out_codepoint, size_t* in_out_length) const=0;
    };
    class text_encoding {
        class utf8_encoder : public text_encoder {
        public: 
            virtual gfx_result to_utf32(const void* in, uint32_t* out_codepoint, size_t* in_out_length) const override;
        };
        class latin1_encoder : public text_encoder {
        public: 
            virtual gfx_result to_utf32(const void* in, uint32_t* out_codepoint, size_t* in_out_length) const override;
        };
        static const utf8_encoder s_utf8;
        static const latin1_encoder s_latin1;
    public:
        static const text_encoder& utf8;
        static const text_encoder& latin1;
    };
    inline gfx_result to_utf32(const char* in,uint32_t* out_codepoint, size_t* in_out_length, gfx_encoding encoding=gfx_encoding::utf8) {
        switch(encoding) {
            case gfx_encoding::utf8:
                return text_encoding::utf8.to_utf32(in,out_codepoint,in_out_length);
            case gfx_encoding::latin1:
                return text_encoding::latin1.to_utf32(in,out_codepoint,in_out_length);
            default:
                return gfx_result::invalid_argument;
        }
    }
}
#endif // HTCW_GFX_ENCODING_HPP