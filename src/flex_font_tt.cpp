#include <flex_font.hpp>
#define STB_RECT_PACK_IMPLEMENTATION
#define STBRP_STATIC
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_HEAP_FACTOR_SIZE_32 50
#define STBTT_HEAP_FACTOR_SIZE_128 20
#define STBTT_HEAP_FACTOR_SIZE_DEFAULT 10
#define STBTT_malloc(x, u) ((void)(u), malloc(x))
#define STBTT_free(x, u) ((void)(u), free(x))
/* for stream support */
#define STBTT_STREAM_TYPE ttf_cb_stream_t
#define STBTT_STREAM_SEEK(s, x) ttf_cb_stream_seek(s, x);
#define STBTT_STREAM_READ(s, x, y) ttf_cb_stream_read(s, x, y);
using namespace gfx;

typedef void* ttf_cb_stream_t;

static void ttf_cb_stream_read(ttf_cb_stream_t s, void * data, size_t to_read) {
    stream* stm = (stream*)s;
    stm->read((uint8_t*)data,to_read);
}
static void ttf_cb_stream_seek(ttf_cb_stream_t s, size_t position) {
    stream* stm = (stream*)s;
    stm->seek((long long)position);
}

#include "stb_rect_pack.h"
#include "stb_truetype.h"

tt_font::tt_font(stream& stream, float size, font_size_units units, bool initialize) : m_info(nullptr), m_stream(&stream),m_size(size),m_units(units) {
    if(initialize) {
        this->initialize();
    }
}
tt_font::tt_font() : m_info(nullptr), m_stream(nullptr), m_line_height(0),m_scale(NAN),m_size(0),m_units(font_size_units::em) {
}

tt_font::~tt_font() {
    deinitialize();
}
tt_font::tt_font(tt_font&& rhs) : m_info(rhs.m_info),m_stream(rhs.m_stream), m_line_height(rhs.m_line_height),m_line_advance(rhs.m_line_advance),m_base_line(rhs.m_base_line),m_scale(rhs.m_scale),m_size(rhs.m_size),m_units(rhs.m_units) {
    rhs.m_info = nullptr;
}
tt_font& tt_font::operator=(tt_font&& rhs) {
    deinitialize();
    m_info=rhs.m_info;
    m_stream=rhs.m_stream;
    m_line_height=rhs.m_line_height;
    m_line_advance=rhs.m_line_advance;
    m_base_line=rhs.m_base_line;
    m_scale=rhs.m_scale;
    m_size=rhs.m_size;
    m_units=rhs.m_units;
    rhs.m_info = nullptr;
    return *this;
}
gfx_result tt_font::initialize() {
    if(m_info!=nullptr) {
        return gfx_result::success;
    }
    if(m_size!=m_size || 0.0f>=m_size) {
        return gfx_result::invalid_argument;
    }
    if(m_stream==nullptr) {
        return gfx_result::invalid_argument;
    }
    stbtt_fontinfo* info = (stbtt_fontinfo* )STBTT_malloc(sizeof(stbtt_fontinfo),NULL);
    if(info==nullptr) {
        return gfx_result::out_of_memory;
    }
    m_info = info;
    if(!stbtt_InitFont(info,m_stream, stbtt_GetFontOffsetForIndex(m_stream, 0))) {
        return gfx_result::invalid_format;
    }
    // check if font  has kerning tables to use, else disable kerning automatically.
    if(stbtt_KernTableCheck(info) == 0) {
        m_kerning = false; // disable kerning if font has no tables. 
    } else {
        m_kerning = true;
    }

    switch(m_units) {
    case font_size_units::px:
        m_scale = stbtt_ScaleForPixelHeight(info,m_size);
    default: // pt
        m_scale = stbtt_ScaleForMappingEmToPixels(info,m_size);
    }
    int line_gap, ascent,descent; 
    stbtt_GetFontVMetrics(info, &ascent, &descent, &line_gap);
    m_line_advance = (int)(m_scale * (ascent - descent + line_gap));
    m_base_line = (m_scale * (line_gap - descent));
    return gfx_result::success;
}
bool tt_font::initialized() const {
    return m_info!=nullptr;
}
void tt_font::deinitialize() {
    if(m_info!=nullptr) {
        STBTT_free(m_info,NULL);
        m_info = nullptr;
    }
}
gfx_result tt_font::on_measure(int codepoint1,int codepoint2, font_glyph_info* out_glyph_info) const {
    if(m_info==nullptr) {
        return gfx_result::invalid_state;
    }
    uint32_t g1 = stbtt_FindGlyphIndex((stbtt_fontinfo*)m_info,codepoint1);
    if(g1==0) {
        return gfx_result::not_supported;
    }
    out_glyph_info->glyph_index1 = g1;
    uint32_t g2 = 0;
    if(codepoint2!=0) {
        g2 = stbtt_FindGlyphIndex((stbtt_fontinfo*)m_info,codepoint2);
        if(g2==0) {
            return gfx_result::not_supported;
        }
        out_glyph_info->glyph_index2 = g2;
    }
    int x1, y1, x2, y2;
    stbtt_GetGlyphBitmapBox((stbtt_fontinfo*)m_info, g1, m_scale, m_scale, &x1, &y1, &x2, &y2);
    //printf("(%d,%d)-(%d,%d) @ %f\n",x1,y1,x2,y2,m_scale);
    out_glyph_info->dimensions.width = x2-x1+1;
    out_glyph_info->dimensions.height = y2-y1+1;
    out_glyph_info->offset.x = x1;
    out_glyph_info->offset.y = -y1;
    //printf("offset (%d,%d)\n",(int)out_glyph_info->offset.x,(int)out_glyph_info->offset.y);
    int advw=0;
    int lsb=0;
    stbtt_GetGlyphHMetrics((stbtt_fontinfo*)m_info,g1,&advw,&lsb);
    if(!m_kerning) {
        out_glyph_info->advance_width = (uint16_t)floor(((float)advw * m_scale) +
                                         0.5f); /*Horizontal space required by the glyph in [px]*/;
    } else {
        int k = stbtt_GetGlyphKernAdvance((stbtt_fontinfo*)m_info, g1, g2);
        out_glyph_info->advance_width = (uint16_t)floor((((float)advw + (float)k) * m_scale) + 0.5f);
    }
    return gfx_result::success;
}
gfx_result tt_font::on_draw(gfx::bitmap<gfx::alpha_pixel<8>>& destination,int codepoint, int glyph_index) const {
    if(m_info==nullptr) {
        return gfx_result::invalid_state;
    }
    if(glyph_index==-1) {
        glyph_index = stbtt_FindGlyphIndex((stbtt_fontinfo*)m_info,codepoint);
    }
    stbtt_MakeGlyphBitmap((stbtt_fontinfo*)m_info,(unsigned char*)destination.begin(),destination.dimensions().width,destination.dimensions().height,destination.dimensions().width,m_scale,m_scale,glyph_index);
    return gfx_result::success;
}
uint16_t tt_font::line_height() const {
    return m_line_height;
}
uint16_t tt_font::line_advance() const {
    return m_line_advance;
}
uint16_t tt_font::base_line() const {
    return m_base_line;
}