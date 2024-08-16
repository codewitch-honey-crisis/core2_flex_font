#pragma once
#include <gfx_core.hpp>
#include <gfx_positioning.hpp>
#include <gfx_pixel.hpp>
#include <gfx_palette.hpp>
#include <gfx_bitmap.hpp>
#include <gfx_encoding.hpp>
#include <htcw_data.hpp>
struct font_glyph_info final {
    gfx::size16 dimensions;
    int16_t advance_width;
    gfx::spoint16 offset;
    int glyph_index1;
    int glyph_index2;
};
enum struct font_size_units {
    em = 0,
    px = 1
};
typedef gfx::gfx_result(*font_draw_callback)(gfx::spoint16 location,const gfx::const_bitmap<gfx::alpha_pixel<8>>& glyph_icon, void* state);
class font_draw_cache {
    typedef struct {
        int accessed;
        gfx::size16 dimensions;
        uint8_t* data;
    } cache_entry_t;
    using map_t = data::simple_fixed_map<int32_t,cache_entry_t,32>;
    void*(*m_allocator)(size_t);
    void*(*m_reallocator)(void*,size_t);
    void(*m_deallocator)(void*);
    bool m_initialized;
    int m_accessed;
    map_t m_cache;
    size_t m_memory_size;
    size_t m_max_memory_size;
    size_t m_max_entries;
    font_draw_cache(const font_draw_cache& rhs)=delete;
    font_draw_cache& operator=(const font_draw_cache& rhs)=delete;
    static int hash_function(const int32_t& key); 
    void expire_memory(size_t new_data_size);
    void expire_item();
    void reduce(int new_size, int new_item_size);
public:
    font_draw_cache(void*(allocator)(size_t)=::malloc, void*(reallocator)(void*,size_t)=::realloc, void(deallocator)(void*)=::free);
    font_draw_cache(font_draw_cache&& rhs);
    virtual ~font_draw_cache();
    font_draw_cache& operator=(font_draw_cache&& rhs);
    size_t max_memory_size() const;
    void max_memory_size(size_t value);
    size_t memory_size() const;
    size_t max_entries() const;
    void max_entries(size_t value);
    size_t entries() const;
    gfx::gfx_result add(int32_t codepoint, gfx::size16 dimensions, const uint8_t* data);
    gfx::gfx_result find(int32_t codepoint, gfx::size16* out_dimensions, uint8_t ** out_bitmap);
    void clear();
    gfx::gfx_result initialize();
    bool initialized() const;
    void deinitialize();
};
class font_measure_cache {
    typedef struct measure_key {
        uint8_t value[8];
        inline bool operator==(const measure_key& key) const {
            return 0==memcmp(key.value,value,sizeof(value));
        }
    } key_t;
    typedef struct {
        int accessed;
        font_glyph_info data;
    } cache_entry_t;
    using map_t = data::simple_fixed_map<key_t,cache_entry_t,64>;
    void*(*m_allocator)(size_t);
    void*(*m_reallocator)(void*,size_t);
    void(*m_deallocator)(void*);
    bool m_initialized;
    int m_accessed;
    map_t m_cache;
    size_t m_memory_size;
    size_t m_max_memory_size;
    size_t m_max_entries;
    font_measure_cache(const font_measure_cache& rhs)=delete;
    font_measure_cache& operator=(const font_measure_cache& rhs)=delete;
    static int hash_function(const key_t& key); 
    static void make_key(int32_t codepoint1, int32_t codepoint2, key_t* out_key);
    void expire_memory(size_t new_data_size);
    void expire_item();
    void reduce(int new_size, int new_item_size);
public:
    font_measure_cache(void*(allocator)(size_t)=::malloc, void*(reallocator)(void*,size_t)=::realloc, void(deallocator)(void*)=::free);
    font_measure_cache(font_measure_cache&& rhs);
    virtual ~font_measure_cache();
    font_measure_cache& operator=(font_measure_cache&& rhs);
    size_t max_memory_size() const;
    void max_memory_size(size_t value);
    size_t memory_size() const;
    size_t max_entries() const;
    void max_entries(size_t value);
    size_t entries() const;
    gfx::gfx_result add(int32_t codepoint1, int32_t codepoint2, const font_glyph_info& data);
    gfx::gfx_result find(int32_t codepoint1, int32_t codepoint2, font_glyph_info* out_glyph_info);
    void clear();
    gfx::gfx_result initialize();
    bool initialized() const;
    void deinitialize();
};

class font_base {
protected:
    virtual gfx::gfx_result on_measure(int32_t codepoint1,int32_t codepoint2, font_glyph_info* out_glyph_info) const=0;
    virtual gfx::gfx_result on_draw(gfx::bitmap<gfx::alpha_pixel<8>>& destination,int32_t codepoint, int glyph_index = -1) const=0;
public:
    virtual gfx::gfx_result initialize()=0;
    virtual bool initialized() const=0;
    virtual void deinitialize()=0;
    virtual uint16_t line_height() const = 0;
    virtual uint16_t line_advance() const = 0;
    virtual uint16_t base_line() const = 0;
public:
    gfx::gfx_result measure(uint16_t max_width,const char* text, gfx::size16* out_area, uint16_t tab_width = 4, gfx::gfx_encoding encoding = gfx::gfx_encoding::utf8, font_measure_cache* cache = nullptr) const;
    gfx::gfx_result draw(const gfx::srect16& bounds, const char* text,font_draw_callback callback, void* callback_state=nullptr,  uint16_t tab_width = 4, gfx::gfx_encoding encoding = gfx::gfx_encoding::utf8, font_draw_cache* draw_cache = nullptr, font_measure_cache* measure_cache = nullptr) const;
};

class tt_font : public font_base {
    void* m_info;
    gfx::stream* m_stream;
    uint16_t m_line_height;
    uint16_t m_line_advance;
    uint16_t m_base_line;
    float m_scale;
    float m_size;
    font_size_units m_units;
    bool m_kerning;
    tt_font(const tt_font& rhs)=delete;
    tt_font& operator=(const tt_font& rhs)=delete;
protected:
    virtual gfx::gfx_result on_measure(int32_t codepoint1,int32_t codepoint2, font_glyph_info* out_glyph_info) const override;
    virtual gfx::gfx_result on_draw(gfx::bitmap<gfx::alpha_pixel<8>>& destination,int codepoint, int glyph_index = -1) const override;
public:
    tt_font(gfx::stream& stream,float size, font_size_units units = font_size_units::em, bool initialize = false);
    tt_font();
    virtual ~tt_font();
    tt_font(tt_font&& rhs);
    tt_font& operator=(tt_font&& rhs);
    virtual gfx::gfx_result initialize() override;
    virtual bool initialized() const override;
    virtual void deinitialize() override;
    virtual uint16_t line_height() const override;
    virtual uint16_t line_advance() const override;
    virtual uint16_t base_line() const override;
};

class win_font : public font_base {
    gfx::stream* m_stream;
    size_t m_font_index;
    uint16_t m_line_height;
    uint16_t m_width;
    long long m_font_offset;
    uint16_t m_char_table_offset, m_char_table_len;
    char m_first_char,m_last_char;
    win_font(const win_font& rhs)=delete;
    win_font& operator=(const win_font& rhs)=delete;
    gfx::gfx_result seek_char(char ch) const;
protected:
    virtual gfx::gfx_result on_measure(int32_t codepoint1,int32_t codepoint2, font_glyph_info* out_glyph_info) const override;
    virtual gfx::gfx_result on_draw(gfx::bitmap<gfx::alpha_pixel<8>>& destination,int codepoint, int glyph_index = -1) const override;
public:
    win_font(gfx::stream& stream, size_t font_index = 0, bool initialize = false);
    win_font();
    virtual ~win_font();
    win_font(win_font&& rhs);
    win_font& operator=(win_font&& rhs);
    virtual gfx::gfx_result initialize() override;
    virtual bool initialized() const override;
    virtual void deinitialize() override;
    virtual uint16_t line_height() const override;
    virtual uint16_t line_advance() const override;
    virtual uint16_t base_line() const override;
};

class vlw_font : public font_base {
    gfx::stream* m_stream;
    size_t m_glyph_count;
    uint16_t m_line_advance;
    uint16_t m_space_width;
    int16_t m_ascent, m_descent;
    int16_t m_max_ascent, m_max_descent;
    gfx::size16 m_bmp_size_max;
    gfx::gfx_result seek_codepoint(int32_t codepoint, int* out_glyph_index = nullptr) const;
    gfx::gfx_result read_uint32(uint32_t* out) const;
protected:
    virtual gfx::gfx_result on_measure(int32_t codepoint1,int32_t codepoint2, font_glyph_info* out_glyph_info) const override;
    virtual gfx::gfx_result on_draw(gfx::bitmap<gfx::alpha_pixel<8>>& destination,int codepoint, int glyph_index = -1) const override;
public:
    vlw_font(gfx::stream& stream, bool initialize = false);
    vlw_font();
    virtual ~vlw_font();
    vlw_font(vlw_font&& rhs);
    vlw_font& operator=(vlw_font&& rhs);
    virtual gfx::gfx_result initialize() override;
    virtual bool initialized() const override;
    virtual void deinitialize() override;
    virtual uint16_t line_height() const override;
    virtual uint16_t line_advance() const override;
    virtual uint16_t base_line() const override;

};